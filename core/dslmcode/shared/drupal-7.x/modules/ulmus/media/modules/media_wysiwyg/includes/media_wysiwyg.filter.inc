<?php

/**
 * @file
 * Functions related to the WYSIWYG editor and the media input filter.
 */

define('MEDIA_WYSIWYG_TOKEN_REGEX', '/\[\[.*?\]\]/s');

/**
 * Filter callback for media markup filter.
 *
 * @TODO check for security probably pass text through filter_xss
 */
function media_wysiwyg_filter($text, $filter = NULL, $format = NULL, $langcode = NULL, $cache = NULL, $cache_id = NULL) {
  $replacements = array();
  $patterns = array();
  $rendered_text = $text;
  $count = 1;
  preg_match_all(MEDIA_WYSIWYG_TOKEN_REGEX, $text, $matches);
  if (!empty($matches[0])) {
    foreach ($matches[0] as $match) {
      $replacement = media_wysiwyg_token_to_markup(array($match), FALSE, $langcode);
      $rendered_text = str_replace($match, $replacement, $rendered_text, $count);
    }
  }
  return $rendered_text;
}

/**
 * Filter callback to remove paragraph tags surrounding embedded media.
 */
function media_wysiwyg_filter_paragraph_fix($text) {
  $html_dom = filter_dom_load($text);
  foreach ($html_dom->getElementsByTagName('p') as $paragraph) {
    if (preg_match(MEDIA_WYSIWYG_TOKEN_REGEX, $paragraph->nodeValue)) {
      $sibling = $paragraph->firstChild;
      do {
        $next = $sibling->nextSibling;
        $paragraph->parentNode->insertBefore($sibling, $paragraph);
      } while ($sibling = $next);
      $paragraph->parentNode->removeChild($paragraph);
    }
  }
  $text = filter_dom_serialize($html_dom);
  return $text;
}

/**
 * Parses the contents of a CSS declaration block.
 *
 * @param string $declarations
 *   One or more CSS declarations delimited by a semicolon. The same as a CSS
 *   declaration block (see http://www.w3.org/TR/CSS21/syndata.html#rule-sets),
 *   but without the opening and closing curly braces. Also the same as the
 *   value of an inline HTML style attribute.
 *
 * @return array
 *   A keyed array. The keys are CSS property names, and the values are CSS
 *   property values.
 */
function media_wysiwyg_parse_css_declarations($declarations) {
  $properties = array();
  foreach (array_map('trim', explode(";", $declarations)) as $declaration) {
    if ($declaration != '') {
      list($name, $value) = array_map('trim', explode(':', $declaration, 2));
      $properties[strtolower($name)] = $value;
    }
  }
  return $properties;
}

/**
 * Replace callback to convert a media file tag into HTML markup.
 *
 * @param string $match
 *   Takes a match of tag code
 * @param bool $wysiwyg
 *   Set to TRUE if called from within the WYSIWYG text area editor.
 *
 * @return string
 *   The HTML markup representation of the tag, or an empty string on failure.
 *
 * @see media_wysiwyg_get_file_without_label()
 * @see hook_media_wysiwyg_token_to_markup_alter()
 */
function media_wysiwyg_token_to_markup($match, $wysiwyg = FALSE, $langcode = NULL) {
  static $recursion_stop;
  $settings = array();
  $match = str_replace("[[", "", $match);
  $match = str_replace("]]", "", $match);
  $tag = $match[0];

  try {
    if (!is_string($tag)) {
      throw new Exception('Unable to find matching tag');
    }

    $tag_info = drupal_json_decode($tag);

    if (!isset($tag_info['fid'])) {
      throw new Exception('No file Id');
    }

    // Ensure the 'link_text' key is always defined.
    if (!isset($tag_info['link_text'])) {
      $tag_info['link_text'] = NULL;
    }

    // Ensure a valid view mode is being requested.
    if (!isset($tag_info['view_mode'])) {
      $tag_info['view_mode'] = variable_get('media_wysiwyg_wysiwyg_default_view_mode', 'full');
    }
    elseif ($tag_info['view_mode'] != 'default') {
      $file_entity_info = entity_get_info('file');
      if (!in_array($tag_info['view_mode'], array_keys($file_entity_info['view modes']))) {
        // Media 1.x defined some old view modes that have been superseded by
        // more semantically named ones in File Entity. The media_update_7203()
        // function updates field settings that reference the old view modes,
        // but it's impractical to update all text content, so adjust
        // accordingly here.
        static $view_mode_updates = array(
          'media_preview' => 'preview',
          'media_small' => 'teaser',
          'media_large' => 'full',
        );
        if (isset($view_mode_updates[$tag_info['view_mode']])) {
          $tag_info['view_mode'] = $view_mode_updates[$tag_info['view_mode']];
        }
        else {
          throw new Exception('Invalid view mode');
        }
      }
    }

    $file = file_load($tag_info['fid']);
    if (!$file) {
      throw new Exception('Could not load media object');
    }
    // Check if we've got a recursion. Happens because a file_load() may
    // triggers file_entity_is_page() which then again triggers a file load.
    if (isset($recursion_stop[$file->fid])) {
      return '';
    }
    $recursion_stop[$file->fid] = TRUE;

    $tag_info['file'] = $file;

    // The class attributes is a string, but drupal requires it to be
    // an array, so we fix it here.
    if (!empty($tag_info['attributes']['class'])) {
      $tag_info['attributes']['class'] = explode(" ", $tag_info['attributes']['class']);
    }

    // Grab the potentially overridden fields from the file.
    $fields = media_wysiwyg_filter_field_parser($tag_info);
    foreach ($fields as $key => $value) {
      $file->{$key} = $value;
    }

    if (array_key_exists('attributes', $tag_info) && is_array($tag_info['attributes'])) {
      $attributes = $tag_info['attributes'];
    }
    else {
      $attributes = array();
    }
    $attribute_whitelist = media_wysiwyg_allowed_attributes();
    $settings['attributes'] = array_intersect_key($attributes, array_flip($attribute_whitelist));
    $settings['fields'] = $fields;

    if (!empty($tag_info['attributes']) && is_array($tag_info['attributes'])) {
      $settings['attributes'] = array_intersect_key($tag_info['attributes'], array_flip($attribute_whitelist));

      // Many media formatters will want to apply width and height independently
      // of the style attribute or the corresponding HTML attributes, so pull
      // these two out into top-level settings. Different WYSIWYG editors have
      // different behavior with respect to whether they store user-specified
      // dimensions in the HTML attributes or the style attribute - check both.
      // Per http://www.w3.org/TR/html5/the-map-element.html#attr-dim-width, the
      // HTML attributes are merely hints: CSS takes precedence.
      if (isset($settings['attributes']['style'])) {
        $css_properties = media_wysiwyg_parse_css_declarations($settings['attributes']['style']);
        foreach (array('width', 'height') as $dimension) {
          if (isset($css_properties[$dimension]) && substr($css_properties[$dimension], -2) == 'px') {
            $settings[$dimension] = substr($css_properties[$dimension], 0, -2);
          }
          elseif (isset($settings['attributes'][$dimension])) {
            $settings[$dimension] = $settings['attributes'][$dimension];
          }
        }
      }
      foreach (array('title', 'alt') as $field_type) {
        if (isset($settings['attributes'][$field_type])) {
          $settings['attributes'][$field_type] = decode_entities($settings['attributes'][$field_type]);
        }
      }
    }
    // Update file metadata from the potentially overridden tag info.
    foreach (array('width', 'height') as $dimension) {
      if (isset($settings['attributes'][$dimension])) {
        $file->metadata[$dimension] = $settings['attributes'][$dimension];
      }
    }
  }
  catch (Exception $e) {
    watchdog('media', 'Unable to render media from %tag. Error: %error', array('%tag' => $tag, '%error' => $e->getMessage()));
    return '';
  }

  // Remove any alignment classes from $settings, because it will be added later
  // in this function to the media's wrapper, and we don't want to confuse CSS
  // by having it on both the wrapper and the element.
  if (isset($settings['attributes']['class'])) {
    $alignment_classes = array(
      'media-wysiwyg-align-left',
      'media-wysiwyg-align-right',
      'media-wysiwyg-align-center',
    );
    $settings['attributes']['class'] = array_diff($settings['attributes']['class'], $alignment_classes);
  }

  // If the tag has link text stored with it, override the filename with it for
  // the rest of this function, so that if the file is themed as a link, the
  // desired text will be used (see, for example, theme_file_link()).
  // @todo: Try to find a less hacky way to do this.
  if (isset($tag_info['link_text']) && variable_get('media_wysiwyg_use_link_text_for_filename', 1)) {
    // The link text will have characters such as "&" encoded for HTML, but the
    // filename itself needs the raw value when it is used to build the link,
    // in order to avoid double encoding.
    $file->filename = decode_entities($tag_info['link_text']);
  }

  if ($wysiwyg) {
    $settings['wysiwyg'] = $wysiwyg;

    // Render file in WYSIWYG using appropriate view mode.
    $view_mode = db_query('SELECT view_mode FROM {media_view_mode_wysiwyg} WHERE type = :type', array(
      ':type' => $file->type,
    ))
      ->fetchField();
    if (empty($view_mode)) {
      $view_mode = $tag_info['view_mode'];
    }

    // If sending markup to a WYSIWYG, we need to pass the file information so
    // that an inline macro can be generated when the WYSIWYG is detached.
    // The WYSIWYG plugin is expecting this information in the
    // Drupal.settings.mediaDataMap variable.
    $element = media_wysiwyg_get_file_without_label($file, $view_mode, $settings, $langcode);
    $data = array(
      'type' => 'media',
      'fid'  => $file->fid,
      'view_mode' => $tag_info['view_mode'],
      'link_text' => $tag_info['link_text'],
    );
    drupal_add_js(array('mediaDataMap' => array($file->fid => $data)), 'setting');
    $element['#attributes']['data-fid'] = $file->fid;
    $element['#attributes']['data-media-element'] = '1';
    $element['#attributes']['class'][] = 'media-element';
  }
  else {
    // Display the field elements.
    $element = array();
    // Render the file entity, for sites using the file_entity rendering method.
    if (variable_get('media_wysiwyg_default_render', 'file_entity') == 'file_entity') {
      $element['content'] = file_view($file, $tag_info['view_mode']);
    }
    $element['content']['file'] = media_wysiwyg_get_file_without_label($file, $tag_info['view_mode'], $settings, $langcode);
    // Overwrite or set the file #alt attribute if it has been set in this
    // instance.
    if (!empty($element['content']['file']['#attributes']['alt'])) {
      $element['content']['file']['#alt'] = $element['content']['file']['#attributes']['alt'];
    }
    // Overwrite or set the file #title attribute if it has been set in this
    // instance.
    if (!empty($element['content']['file']['#attributes']['title'])) {
      $element['content']['file']['#title'] = $element['content']['file']['#attributes']['title'];
    }
    // For sites using the legacy field_attach rendering method, attach fields.
    if (variable_get('media_wysiwyg_default_render', 'file_entity') == 'field_attach') {
      field_attach_prepare_view('file', array($file->fid => $file), $tag_info['view_mode'], $langcode);
      entity_prepare_view('file', array($file->fid => $file), $langcode);
      $element['content'] += field_attach_view('file', $file, $tag_info['view_mode'], $langcode);
    }
    if (count(element_children($element['content'])) > 1) {
      // Add surrounding divs to group them together.
      // We don't want divs when there are no additional fields to allow files
      // to display inline with text, without breaking p tags.
      $element['content']['#type'] = 'container';
      $element['content']['#attributes']['class'] = array(
        'media',
        'media-element-container',
        'media-' . $element['content']['file']['#view_mode'],
      );
    }

    // Conditionally add a pre-render if the media filter output is be cached.
    $filters = filter_get_filters();
    if (!isset($filters['media_filter']['cache']) || $filters['media_filter']['cache']) {
      $element['#pre_render'][] = 'media_wysiwyg_pre_render_cached_filter';
    }
  }
  if (!empty($element['content']) && !empty($tag_info['fields']['alignment'])) {
    // Set a CSS class if an alignment has been specified and is correct.
    $alignment = $tag_info['fields']['alignment'];
    if (in_array($alignment, array('left', 'right', 'center'))) {
      $alignment_class = 'media-wysiwyg-align-' . $alignment;
      $element['content']['#attributes']['class'][] = $alignment_class;
    }
  }
  drupal_alter('media_wysiwyg_token_to_markup', $element, $tag_info, $settings, $langcode);
  $output = drupal_render($element);
  unset($recursion_stop[$file->fid]);
  return $output;
}

/**
 * Parse the field array from the collapsed AJAX string.
 */
function media_wysiwyg_filter_field_parser($tag_info) {
  $fields = array();
  if (isset($tag_info['fields'])) {
    // Field names that end in [format] are associated with long-text fields that may have HTML Entities.
    // Those values will need to be URLDecoded as well as HTMLDecoded.
    $url_encoded_fields = array();
    foreach($tag_info['fields'] as $field_name => $field_value) {
      if (preg_match('/\[format\]$/', $field_name) > 0){
        $url_encoded_fields[] = preg_replace('/\[format\]$/', '[value]', $field_name);
      }
    }

    foreach($tag_info['fields'] as $field_name => $field_value) {
      if (strpos($field_name, 'field_') === 0) {
        $parsed_field = explode('[', str_replace(']', '', $field_name));
        $ref = &$fields;

        // Certain types of fields, because of differences in markup, end up
        // here with incomplete arrays. Make a best effort to support as many
        // types of fields as possible.
        // Single-value select lists show up here with only 2 array items.
        if (count($parsed_field) == 2) {
          $info = field_info_field($parsed_field[0]);
          if ($info && !empty($info['columns'])) {
            // Assume single-value.
            $parsed_field[] = 0;
            // Next tack on the column for this field.
            $parsed_field[] = key($info['columns']);
          }
        }
        // Multi-value select lists show up here with 3 array items.
        elseif (count($parsed_field) == 3 && (empty($parsed_field[2]) || is_numeric($parsed_field[2]))) {
          $info = field_info_field($parsed_field[0]);
          // They just need the value column.
          $parsed_field[3] = key($info['columns']);
        }

        // Each key of the field needs to be the child of the previous key.
        foreach ($parsed_field as $key) {
          if (!isset($ref[$key])) {
            $ref[$key] = array();
          }
          $ref = &$ref[$key];
        }

        // The value should be set at the deepest level.
        if (in_array($field_name, $url_encoded_fields)){
          // Fields that use rich-text markup will be urlencoded.
          $ref = urldecode(decode_entities($field_value));
        }
        else {
          // Only entities need to be decoded.
          $ref = decode_entities($field_value);
        }
      }
    }
  }
  return $fields;
}

/**
 * Creates map of inline media tags.
 *
 * Generates an array of [inline tags] => <html> to be used in filter
 * replacement and to add the mapping to JS.
 *
 * @param string $text
 *   The String containing text and html markup of textarea
 *
 * @return array
 *   An associative array with tag code as key and html markup as the value.
 *
 * @see media_process_form()
 * @see media_token_to_markup()
 */
function _media_wysiwyg_generate_tagMap($text) {
  // Making $tagmap static as this function is called many times and
  // adds duplicate markup for each tag code in Drupal.settings JS,
  // so in media_process_form it adds something like tagCode:<markup>,
  // <markup> and when we replace in attach see two duplicate images
  // for one tagCode. Making static would make function remember value
  // between function calls. Since media_process_form is multiple times
  // with same form, this function is also called multiple times.
  static $tagmap = array();
  preg_match_all("/\[\[.*?\]\]/s", $text, $matches, PREG_SET_ORDER);
  foreach ($matches as $match) {
    // We see if tagContent is already in $tagMap, if not we add it
    // to $tagmap.  If we return an empty array, we break embeddings of the same
    // media multiple times.
    if (empty($tagmap[$match[0]])) {
      // @TODO: Total HACK, but better than nothing.
      // We should find a better way of cleaning this up.
      if ($markup_for_media = media_wysiwyg_token_to_markup($match, TRUE)) {
        $tagmap[$match[0]] = $markup_for_media;
      }
      else {
        $missing = file_create_url(drupal_get_path('module', 'media') . '/images/icons/default/image-x-generic.png');
        $tagmap[$match[0]] = '<div><img src="' . $missing . '" width="100px" height="100px"/></div>';
      }
    }
  }
  return $tagmap;
}

/**
 * Return a list of view modes allowed for a file embedded in the WYSIWYG.
 *
 * @param object $file
 *   A file entity.
 *
 * @return array
 *   An array of view modes that can be used on the file when embedded in the
 *   WYSIWYG.
 *
 * @deprecated
 */
function media_wysiwyg_get_wysiwyg_allowed_view_modes($file) {
  $enabled_view_modes = &drupal_static(__FUNCTION__, array());

  // @todo Add more caching for this.
  if (!isset($enabled_view_modes[$file->type])) {
    $enabled_view_modes[$file->type] = array();

    // Add the default view mode by default.
    $enabled_view_modes[$file->type]['default'] = array('label' => t('Default'), 'custom settings' => TRUE);

    $entity_info = entity_get_info('file');
    $view_mode_settings = field_view_mode_settings('file', $file->type);
    foreach ($entity_info['view modes'] as $view_mode => $view_mode_info) {
      // Do not show view modes that don't have their own settings and will
      // only fall back to the default view mode.
      if (empty($view_mode_settings[$view_mode]['custom_settings'])) {
        continue;
      }

      // Don't present the user with an option to choose a view mode in which
      // the file is hidden.
      $extra_fields = field_extra_fields_get_display('file', $file->type, $view_mode);
      if (empty($extra_fields['file']['visible'])) {
        continue;
      }

      // Add the view mode to the list of enabled view modes.
      $enabled_view_modes[$file->type][$view_mode] = $view_mode_info;
    }
  }

  $view_modes = $enabled_view_modes[$file->type];
  media_wysiwyg_wysiwyg_allowed_view_modes_restrict($view_modes, $file);
  drupal_alter('media_wysiwyg_allowed_view_modes', $view_modes, $file);
  // Invoke the deprecated/misspelled alter hook as well.
  drupal_alter('media_wysiwyg_wysiwyg_allowed_view_modes', $view_modes, $file);
  return $view_modes;
}
/**
 * Do not show restricted view modes.
 */
function media_wysiwyg_wysiwyg_allowed_view_modes_restrict(&$view_modes, &$file) {
  $restricted_view_modes = db_query('SELECT display FROM {media_restrict_wysiwyg} WHERE type = :type', array(':type' => $file->type))->fetchCol();
  foreach ($restricted_view_modes as $restricted_view_mode) {
    if (array_key_exists($restricted_view_mode, $view_modes)) {
      unset($view_modes[$restricted_view_mode]);
    }
  }
}
/**
 * #pre_render callback: Modify the element if the render cache is filtered.
 */
function media_wysiwyg_pre_render_cached_filter($element) {
  // Remove contextual links since they are not compatible with cached filtered
  // text.
  if (isset($element['content']['#contextual_links'])) {
    unset($element['content']['#contextual_links']);
  }

  return $element;
}
