<?php

/**
 * @file
 * Functions related to the WYSIWYG editor and the media input filter.
 *
 * @TODO: Rename this file?
 */

define('MEDIA_TOKEN_REGEX', '/\[\[.*?\]\]/s');
define('MEDIA_TOKEN_REGEX_ALT', '/%7B.*?%7D/s');

/**
 * Implements hook_wysiwyg_include_directory().
 */
function media_wysiwyg_include_directory($type) {
  switch ($type) {
    case 'plugins':
      return 'wysiwyg_plugins';

    break;
  }
}

/**
 * Implements hook_field_attach_insert().
 *
 * Track file usage for media files included in formatted text. Note that this
 * is heavy-handed, and should be replaced when Drupal's filter system is
 * context-aware.
 */
function media_field_attach_insert($entity_type, $entity) {
  _media_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Implements hook_field_attach_update().
 *
 * @see media_field_attach_insert().
 */
function media_field_attach_update($entity_type, $entity) {
  _media_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Add file usage from file references in an entity's text fields.
 */
function _media_filter_add_file_usage_from_fields($entity_type, $entity) {
  // Track the total usage for files from all fields combined.
  $entity_files = media_entity_field_count_files($entity_type, $entity);

  list($entity_id, $entity_vid, $entity_bundle) = entity_extract_ids($entity_type, $entity);

  // When an entity has revisions and then is saved again NOT as new version the
  // previous revision of the entity has be loaded to get the last known good
  // count of files. The saved data is compared against the last version
  // so that a correct file count can be created for that (the current) version
  // id. This code may assume some things about entities that are only true for
  // node objects. This should be reviewed.
  // @TODO this conditional can probably be condensed
  if (empty($entity->revision) && empty($entity->old_vid) && empty($entity->is_new) && ! empty($entity->original)) {
    $old_files = media_entity_field_count_files($entity_type, $entity->original);
    foreach ($old_files as $fid => $old_file_count) {
      // Were there more files on the node just prior to saving?
      if (empty($entity_files[$fid])) {
        $entity_files[$fid] = 0;
      }
      if ($old_file_count > $entity_files[$fid]) {
        $deprecate = $old_file_count - $entity_files[$fid];
        // Now deprecate this usage
        $file = file_load($fid);
        if ($file) {
          file_usage_delete($file, 'media', $entity_type, $entity_id, $deprecate);
        }
        // Usage is deleted, nothing more to do with this file
        unset($entity_files[$fid]);
      }
      // There are the same number of files, nothing to do
      elseif ($entity_files[$fid] ==  $old_file_count) {
        unset($entity_files[$fid]);
      }
      // There are more files now, adjust the difference for the greater number.
      // file_usage incrementing will happen below.
      else {
        // We just need to adjust what the file count will account for the new
        // images that have been added since the increment process below will
        // just add these additional ones in
        $entity_files[$fid] = $entity_files[$fid] - $old_file_count;
      }
    }
  }

  // Each entity revision counts for file usage. If versions are not enabled
  // the file_usage table will have no entries for this because of the delete
  // query above.
  foreach ($entity_files as $fid => $entity_count) {
    if ($file = file_load($fid)) {
      file_usage_add($file, 'media', $entity_type, $entity_id, $entity_count);
    }
  }

}

/**
 * Parse file references from an entity's text fields and return them as an array.
 */
function media_filter_parse_from_fields($entity_type, $entity) {
  $file_references = array();

  foreach (_media_filter_fields_with_text_filtering($entity_type, $entity) as $field_name) {
    if ($field_items = field_get_items($entity_type, $entity, $field_name)) {
      foreach ($field_items as $field_item) {
        preg_match_all(MEDIA_TOKEN_REGEX, $field_item['value'], $matches);
        foreach ($matches[0] as $tag) {
          $tag = str_replace(array('[[', ']]'), '', $tag);
          $tag_info = drupal_json_decode($tag);
          if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
            $file_references[] = $tag_info;
          }
        }

        preg_match_all(MEDIA_TOKEN_REGEX_ALT, $field_item['value'], $matches_alt);
        foreach ($matches_alt[0] as $tag) {
          $tag = urldecode($tag);
          $tag_info = drupal_json_decode($tag);
          if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
            $file_references[] = $tag_info;
          }
        }
      }
    }
  }

  return $file_references;
}

/**
 * Returns an array containing the names of all fields that perform text filtering.
 */
function _media_filter_fields_with_text_filtering($entity_type, $entity) {
  list($entity_id, $revision_id, $bundle) = entity_extract_ids($entity_type, $entity);
  $fields = field_info_instances($entity_type, $bundle);

  // Get all of the fields on this entity that allow text filtering.
  $fields_with_text_filtering = array();
  foreach ($fields as $field_name => $field) {
    if (!empty($field['settings']['text_processing'])) {
      $fields_with_text_filtering[] = $field_name;
    }
  }

  return $fields_with_text_filtering;
}

/**
 * Utility function to get the file count in this entity
 *
 * @param type $entity
 * @param type $entity_type
 * @return int
 */
function media_entity_field_count_files($entity_type, $entity) {
  $entity_files = array();
  foreach (media_filter_parse_from_fields($entity_type, $entity) as $file_reference) {
    if (empty($entity_files[$file_reference['fid']])) {
      $entity_files[$file_reference['fid']] = 1;
    }
    else {
      $entity_files[$file_reference['fid']]++;
    }
  }
  return $entity_files;
}

/**
 * Implements hook_entity_delete().
 */
function media_entity_delete($entity, $type) {
  list($entity_id) = entity_extract_ids($type, $entity);

  db_delete('file_usage')
    ->condition('module', 'media')
    ->condition('type', $type)
    ->condition('id', $entity_id)
    ->execute();
}

/**
 * Implements hook_field_attach_delete_revision().
 *
 * @param type $entity_type
 * @param type $entity
 */
function media_field_attach_delete_revision($entity_type, $entity) {
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  $files = media_entity_field_count_files($entity_type, $entity);
  foreach ($files as $fid => $count) {
    if ($file = file_load($fid)) {
      file_usage_delete($file, 'media', $entity_type , $entity_id, $count);
    }
  }
}

/**
 * Filter callback for media markup filter.
 *
 * @TODO check for security probably pass text through filter_xss
 */
function media_filter($text) {
  $text = preg_replace_callback(MEDIA_TOKEN_REGEX, 'media_token_to_markup', $text);
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
function media_parse_css_declarations($declarations) {
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
 * @see media_get_file_without_label()
 * @see hook_media_token_to_markup_alter()
 */
function media_token_to_markup($match, $wysiwyg = FALSE) {
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
      $tag_info['view_mode'] = variable_get('media__wysiwyg_default_view_mode', 'full');
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
    $tag_info['file'] = $file;

    // The class attributes is a string, but drupal requires it to be
    // an array, so we fix it here.
    if (!empty($tag_info['attributes']['class'])) {
      $tag_info['attributes']['class'] = explode(" ", $tag_info['attributes']['class']);
    }

    // Grab the potentially overrided fields from the file.
    $fields = media_filter_field_parser($tag_info);

    $attributes = is_array($tag_info['attributes']) ? $tag_info['attributes'] : array();
    $attribute_whitelist = variable_get('media__wysiwyg_allowed_attributes', array('height', 'width', 'hspace', 'vspace', 'border', 'align', 'style', 'class', 'id', 'usemap', 'data-picture-group', 'data-picture-align'));
    $settings['attributes'] = array_intersect_key($attributes, array_flip($attribute_whitelist));
    $settings['fields'] = $fields;

    if (!empty($tag_info['attributes']) && is_array($tag_info['attributes'])) {
      $attribute_whitelist = variable_get('media__wysiwyg_allowed_attributes', array('height', 'width', 'hspace', 'vspace', 'border', 'align', 'style', 'class', 'id', 'usemap', 'data-picture-group', 'data-picture-align'));
      $settings['attributes'] = array_intersect_key($tag_info['attributes'], array_flip($attribute_whitelist));
      $settings['fields'] = $fields;

      // Many media formatters will want to apply width and height independently
      // of the style attribute or the corresponding HTML attributes, so pull
      // these two out into top-level settings. Different WYSIWYG editors have
      // different behavior with respect to whether they store user-specified
      // dimensions in the HTML attributes or the style attribute - check both.
      // Per http://www.w3.org/TR/html5/the-map-element.html#attr-dim-width, the
      // HTML attributes are merely hints: CSS takes precedence.
      if (isset($settings['attributes']['style'])) {
        $css_properties = media_parse_css_declarations($settings['attributes']['style']);
        foreach (array('width', 'height') as $dimension) {
          if (isset($css_properties[$dimension]) && substr($css_properties[$dimension], -2) == 'px') {
            $settings[$dimension] = substr($css_properties[$dimension], 0, -2);
          }
          elseif (isset($settings['attributes'][$dimension])) {
            $settings[$dimension] = $settings['attributes'][$dimension];
          }
        }
      }
    }
  }
  catch (Exception $e) {
    watchdog('media', 'Unable to render media from %tag. Error: %error', array('%tag' => $tag, '%error' => $e->getMessage()));
    return '';
  }

  // If the tag has link text stored with it, override the filename with it for
  // the rest of this function, so that if the file is themed as a link, the
  // desired text will be used (see, for example, theme_file_link()).
  // @todo: Try to find a less hacky way to do this.
  if (isset($tag_info['link_text'])) {
    // The link text will have characters such as "&" encoded for HTML, but the
    // filename itself needs the raw value when it is used to build the link,
    // in order to avoid double encoding.
    $file->filename = decode_entities($tag_info['link_text']);
  }

  if ($wysiwyg) {
    $settings['wysiwyg'] = $wysiwyg;
    // If sending markup to a WYSIWYG, we need to pass the file infomation so
    // that a inline macro can be generated when the WYSIWYG is detached.
    // The WYSIWYG plugin is expecting this information in the format of a
    // urlencoded JSON string stored in the data-file_info attribute of the
    // element.
    $element = media_get_file_without_label($file, $tag_info['view_mode'], $settings);
    $data = drupal_json_encode(array(
      'type' => 'media',
      'fid' => $file->fid,
      'view_mode' => $tag_info['view_mode'],
      'link_text' => $tag_info['link_text'],
    ));
    $element['#attributes']['data-file_info'] = urlencode($data);
    $element['#attributes']['class'][] = 'media-element';
  }
  else {
    // Display the field elements.
    $element = array();
    $element['content']['file'] = media_get_file_without_label($file, $tag_info['view_mode'], $settings);
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
    field_attach_prepare_view('file', array($file->fid => $file), $tag_info['view_mode']);
    entity_prepare_view('file', array($file->fid => $file));
    $element['content'] += field_attach_view('file', $file, $tag_info['view_mode']);
    if (count(element_children($element['content'])) > 1) {
      // Add surrounding divs to group them together.
      // We dont want divs when there are no additional fields to allow files
      // to display inline with text, without breaking p tags.
      $element['content']['#type'] = 'container';
      $element['content']['#attributes']['class'] = array(
        'media',
        'media-element-container',
        'media-' . $element['content']['file']['#view_mode']
      );
    }
  }
  drupal_alter('media_token_to_markup', $element, $tag_info, $settings);
  return drupal_render($element);
}

/**
 * Parse the field array from the collapsed AJAX string.
 */
function media_filter_field_parser($tag_info) {
  $fields = array();
  if (isset($tag_info['fields'])) {
    foreach($tag_info['fields'] as $field_name => $field_value) {
      if (strpos($field_name, 'field_') === 0) {
        $parsed_field = explode('[', str_replace(']', '', $field_name));
        if(isset($parsed_field[2])) {
          if(isset($parsed_field[3])) {
            $fields[$parsed_field[0]][$parsed_field[1]][$parsed_field[2]][$parsed_field[3]] = $field_value;
          } else {
            $fields[$parsed_field[0]][$parsed_field[1]][$parsed_field[2]] = $field_value;
          }
        } else {
          $fields[$parsed_field[0]][$parsed_field[1]] = $field_value;
        }
      }
    }
  }
  return $fields;
}
/**
 * Builds a map of media tags in the element.
 *
 * Builds a map of the media tags in an element that are being rendered to their
 * rendered HTML. The map is stored in JS, so we can transform them when the
 * editor is being displayed.
 */
function media_pre_render_text_format($element) {
  // filter_process_format() copies properties to the expanded 'value' child
  // element.
  if (!isset($element['format'])) {
    return $element;
  }

  $field = &$element['value'];
  $settings = array(
    'field' => $field['#id'],
  );

  $tagmap = _media_generate_tagMap($field['#value']);

  if (isset($tagmap)) {
    drupal_add_js(array('tagmap' => $tagmap), 'setting');
  }
  return $element;
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
function _media_generate_tagMap($text) {
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
      if ($markup_for_media = media_token_to_markup($match, TRUE)) {
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
 */
function media_get_wysiwyg_allowed_view_modes($file) {
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
  drupal_alter('media_wysiwyg_allowed_view_modes', $view_modes, $file);
  return $view_modes;
}

/**
 * Form callback used when embedding media.
 *
 * Allows the user to pick a format for their media file.
 * Can also have additional params depending on the media type.
 */
function media_format_form($form, $form_state, $file) {
  $form = array();
  $form['#media'] = $file;

  // Allow for overrides to the fields.
  $query_fields = isset($_GET['fields']) ? drupal_json_decode($_GET['fields']) : array();
  $fields = media_filter_field_parser(array('fields' => $query_fields), $file);

  $view_modes = media_get_wysiwyg_allowed_view_modes($file);
  $formats = $options = array();
  foreach ($view_modes as $view_mode => $view_mode_info) {
    // @TODO: Display more verbose information about which formatter and what it
    // does.
    $options[$view_mode] = $view_mode_info['label'];
    $element = media_get_file_without_label($file, $view_mode, array('wysiwyg' => TRUE));

    // Make a pretty name out of this.
    $formats[$view_mode] = drupal_render($element);
  }

  // Add the previews back into the form array so they can be altered.
  $form['#formats'] = &$formats;

  if (!count($formats)) {
    throw new Exception('Unable to continue, no available formats for displaying media.');
    return;
  }

  // Allow for overrides to the display format.
  $default_view_mode = is_array($query_fields) && isset($query_fields['format']) ? $query_fields['format'] : variable_get('media__wysiwyg_default_view_mode', 'full');
  if (!isset($formats[$default_view_mode])) {
    $default_view_mode = key($formats);
  }

  // Add the previews by reference so that they can easily be altered by
  // changing $form['#formats'].
  $settings['media']['formatFormFormats'] = &$formats;
  $form['#attached']['js'][] = array('data' => $settings, 'type' => 'setting');

  // Add the required libraries, JavaScript and CSS for the form.
  $form['#attached']['library'][] = array('media', 'media_base');
  $form['#attached']['library'][] = array('system', 'form');
  $form['#attached']['js'][] = drupal_get_path('module', 'media') . '/js/media.format_form.js';

  $form['title'] = array(
    '#markup' => t('Embedding %filename', array('%filename' => $file->filename)),
  );

  $preview = media_get_thumbnail_preview($file);

  $form['preview'] = array(
    '#type' => 'markup',
    '#title' => check_plain(basename($file->uri)),
    '#markup' => drupal_render($preview),
  );

  // These will get passed on to WYSIWYG.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('options'),
  );

  $form['options']['format'] = array(
    '#type' => 'select',
    '#title' => t('Display as'),
    '#options' => $options,
    '#default_value' => $default_view_mode,
    '#description' => t('Choose the type of display you would like for this
      file. Please be aware that files may display differently than they do when
      they are inserted into an editor.')
  );

  // Add fields from the file, so that we can override them if neccesary.
  $form['options']['fields'] = array();
  foreach ($fields as $field_name => $field_value) {
    $file->{$field_name} = $field_value;
  }
  field_attach_form('file', $file, $form['options']['fields'], $form_state);
  $instance = field_info_instances('file', $file->type);
  foreach ($instance as $field_name => $field_value) {
    if (isset($instance[$field_name]['settings']) && isset($instance[$field_name]['settings']['wysiwyg_override']) && !$instance[$field_name]['settings']['wysiwyg_override']) {
      unset($form['options']['fields'][$field_name]);
    }
  }

  // Similar to a form_alter, but we want this to run first so that
  // media.types.inc can add the fields specific to a given type (like alt tags
  // on media). If implemented as an alter, this might not happen, making other
  // alters not be able to work on those fields.
  // @todo: We need to pass in existing values for those attributes.
  drupal_alter('media_format_form_prepare', $form, $form_state, $file);

  if (!element_children($form['options'])) {
    $form['options']['#attributes'] = array('style' => 'display:none');
  }

  return $form;
}

/**
 * Returns a drupal_render() array for just the file portion of a file entity.
 *
 * Optional custom settings can override how the file is displayed.
 */
function media_get_file_without_label($file, $view_mode, $settings = array()) {
  $file->override = $settings;

  $element = file_view_file($file, $view_mode);

  // The formatter invoked by file_view_file() can use $file->override to
  // customize the returned render array to match the requested settings. To
  // support simple formatters that don't do this, set the element attributes to
  // what was requested, but not if the formatter applied its own logic for
  // element attributes.
  if (!isset($element['#attributes']) && isset($settings['attributes'])) {
    $element['#attributes'] = $settings['attributes'];

    // While this function may be called for any file type, images are a common
    // use-case. theme_image() and theme_image_style() require the 'alt'
    // attribute to be passed separately from the 'attributes' array (see
    // http://drupal.org/node/999338). Until that's fixed, implement this
    // special-case logic. Image formatters using other theme functions are
    // responsible for their own 'alt' attribute handling. See
    // theme_media_formatter_large_icon() for an example.
    if (isset($settings['attributes']['alt']) && !isset($element['#alt']) && isset($element['#theme']) && in_array($element['#theme'], array('image', 'image_style'))) {
      $element['#alt'] = $settings['attributes']['alt'];
    }
  }

  return $element;
}

/**
 * Implements hook_entity_dependencies().
 */
function media_entity_dependencies($entity, $entity_type) {
  // Go through all the entity's text fields and add a dependency on any files
  // that are referenced there.
  $dependencies = array();
  foreach (media_filter_parse_from_fields($entity_type, $entity) as $file_reference) {
    $dependencies[] = array('type' => 'file', 'id' => $file_reference['fid']);
  }
  return $dependencies;
}

/**
 * Implements hook_entity_uuid_load().
 */
function media_entity_uuid_load(&$entities, $entity_type) {
  // Go through all the entity's text fields and replace file IDs in media
  // tokens with the corresponding UUID.
  foreach ($entities as $entity) {
    media_filter_replace_tokens_in_all_text_fields($entity_type, $entity, 'media_token_fid_to_uuid');
  }
}

/**
 * Implements hook_entity_uuid_presave().
 */
function media_entity_uuid_presave(&$entity, $entity_type) {
  // Go through all the entity's text fields and replace UUIDs in media tokens
  // with the corresponding file ID.
  media_filter_replace_tokens_in_all_text_fields($entity_type, $entity, 'media_token_uuid_to_fid');
}

/**
 * Replaces media tokens in an entity's text fields, using the specified callback function.
 */
function media_filter_replace_tokens_in_all_text_fields($entity_type, $entity, $callback) {
  $text_field_names = _media_filter_fields_with_text_filtering($entity_type, $entity);
  foreach ($text_field_names as $field_name) {
    if (!empty($entity->{$field_name})) {
      $field = field_info_field($field_name);
      $all_languages = field_available_languages($entity_type, $field);
      $field_languages = array_intersect($all_languages, array_keys($entity->{$field_name}));
      foreach ($field_languages as $language) {
        if (!empty($entity->{$field_name}[$language])) {
          foreach ($entity->{$field_name}[$language] as &$item) {
            $item['value'] = preg_replace_callback(MEDIA_TOKEN_REGEX, $callback, $item['value']);
          }
        }
      }
    }
  }
}

/**
 * Callback to replace file IDs with UUIDs in a media token.
 */
function media_token_fid_to_uuid($matches) {
  return _media_token_uuid_replace($matches, 'entity_get_uuid_by_id');
}

/**
 * Callback to replace UUIDs with file IDs in a media token.
 */
function media_token_uuid_to_fid($matches) {
  return _media_token_uuid_replace($matches, 'entity_get_id_by_uuid');
}

/**
 * Helper function to replace UUIDs with file IDs or vice versa.
 *
 * @param array $matches
 *   An array of matches for media tokens, from a preg_replace_callback()
 *   callback function.
 * @param string $entity_uuid_function
 *   Either 'entity_get_uuid_by_id' (to replace file IDs with UUIDs in the
 *   token) or 'entity_get_id_by_uuid' (to replace UUIDs with file IDs).
 *
 * @return string
 *   A string representing the JSON-encoded token, with the appropriate
 *   replacement between file IDs and UUIDs.
 */
function _media_token_uuid_replace($matches, $entity_uuid_function) {
  $tag = $matches[0];
  $tag = str_replace(array('[[', ']]'), '', $tag);
  $tag_info = drupal_json_decode($tag);
  if (isset($tag_info['fid'])) {
    if ($new_ids = $entity_uuid_function('file', array($tag_info['fid']))) {
      $new_id = reset($new_ids);
      $tag_info['fid'] = $new_id;
    }
  }
  return '[[' . drupal_json_encode($tag_info) . ']]';
}
