<?php

/**
 * @file
 * Implement a video field.
 */

/**
 * Implements hook_field_info().
 */
function video_embed_field_field_info() {
  return array(
    'video_embed_field' => array(
      'label' => 'Video Embed',
      'description' => 'Embed videos from youtube or vimeo',
      'settings' => array(),
      'instance_settings' => array(
        'description_field' => 0,
        'description_length' => 128,
        'allowed_providers' => array_keys(video_embed_get_handlers()),
      ),
      'default_widget' => 'video_embed_field_video',
      'default_formatter' => 'video_embed_field',
      'property_type' => 'video_embed_field',
      'property_callbacks' => array('video_embed_field_property_info_callback'),
    ),
  );
}

/**
 * Property callback for the Entity Metadata framework.
 */
function video_embed_field_property_info_callback(&$info, $entity_type, $field, $instance, $field_type) {
  // Apply the default.
  entity_metadata_field_default_property_callback($info, $entity_type, $field, $instance, $field_type);

  // Finally add in instance specific property info.
  $name = $field['field_name'];
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$name];
  $property['type'] = ($field['cardinality'] != 1) ? 'list<video_embed_field>' : 'video_embed_field';
  $property['property info'] = video_embed_field_data_property_info('Video embed');
  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  $property['setter callback'] = 'entity_metadata_field_verbatim_set';
}

/**
 * Defines info for the properties of the video_embed_field data structure.
 */
function video_embed_field_data_property_info($name = NULL) {
  // Build an array of basic property information for video_embed_field.
  $properties = array(
    'video_url' => array(
      'label' => 'Video URL',
      'type' => 'uri',
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'thumbnail_path' => array(
      'label' => 'Thumbnail path',
      'type' => 'uri',
      'getter callback' => 'entity_property_verbatim_get_url',
    ),
    'description' => array(
      'label' => 'Description',
      'type' => 'text',
      'setter callback' => 'entity_property_verbatim_set',
    ),
  );

  // Add the default values for each of the video_embed_field properties.
  foreach ($properties as $key => &$value) {
    $value += array(
      'description' => !empty($name) ? t('!label of field %name', array('!label' => $value['label'], '%name' => $name)) : '',
    );
  }

  return $properties;
}

/**
 * Gets the property just as it is set in the data and converts to absolute url.
 */
function entity_property_verbatim_get_url($data, array $options, $name, $type, $info) {
  $property = entity_property_verbatim_get($data, $options, $name, $type, $info);
  return file_create_url($property);
}

/**
 * Implements hook_field_instance_settings_form().
 */
function video_embed_field_field_instance_settings_form($field, $instance) {
  $settings = $instance['settings'];

  $providers = video_embed_get_handlers();
  $allowed_providers = array();
  foreach ($providers as $provider_id => $definition) {
    $allowed_providers[$provider_id] = $definition['title'];
  }

  $form['allowed_providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select the allowed video providers'),
    '#options' => $allowed_providers,
    '#default_value' => isset($settings['allowed_providers']) ? $settings['allowed_providers'] : array(),
    '#weight' => 10,
  );

  $form['description_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Description</em> field'),
    '#default_value' => isset($settings['description_field']) ? $settings['description_field'] : '',
    '#description' => t('The description field allows users to enter a description about the video.'),
    '#weight' => 11,
  );

  $form['description_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Max description length'),
    '#default_value' => isset($settings['description_length']) ? $settings['description_length'] : 128,
    '#weight' => 12,
    '#size' => 5,
    '#maxlength' => 5,
    '#states' => array(
      'visible' => array(
        ':input[id="edit-instance-settings-description-field"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $form;
}

/**
 * Implements hook_field_widget_info().
 */
function video_embed_field_field_widget_info() {
  return array(
    'video_embed_field_video' => array(
      'label' => 'Video',
      'description' => 'Provides a video embed field',
      'field types' => array('video_embed_field'),
      'settings' => array(),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function video_embed_field_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // Don't need to check the type right now because we're only defining one.
  $element += array(
    '#type' => 'fieldset',
  );

  $element['video_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Video URL'),
    '#attributes' => array('class' => array('video_embed_url')),
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'video_embed_field') . '/video_embed_field.form.css',
      ),
    ),
    '#default_value' => isset($items[$delta]['video_url']) ? $items[$delta]['video_url'] : '',
    '#required' => $element['#required'],
    '#maxlength' => 255,
  );

  // Add the description field if enabled.
  if (!empty($instance['settings']['description_field'])) {
    $element['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#default_value' => isset($items[$delta]['description']) ? $items[$delta]['description'] : '',
      '#description' => t('The description which may be used as a label.'),
      '#maxlength' => $instance['settings']['description_length'],
    );
  }

  return $element;
}

/**
 * Validates video URL.
 */
function video_embed_field_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $delta => $item) {
    if (!empty($item['video_url'])) {
      $item['video_url'] = trim($item['video_url']);
      if (stristr($item['video_url'], '.') && !stristr($item['video_url'], 'http://') && !stristr($item['video_url'], 'https://')) {
        $item['video_url'] = 'http://' . $item['video_url'];
      }

      $parts = parse_url($item['video_url']);
      if (!$parts || !isset($parts['host'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => t('Invalid Url'),
          'message' => t('Video: Invalid Video URL.', array('%name' => $instance['label'])),
        );
      }
      else {
        $host = $parts['host'];
        if (stripos($host, 'www.') > -1) {
          $host = substr($host, 4);
        }
        $domains = _video_embed_field_get_instance_provider_domains($instance);
        if (!array_key_exists($host, $domains)) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => t('Unsupported Video Provider'),
            'message' => t('%name: This video provider is not currently supported.', array('%name' => $instance['label'])),
          );
        }
      }
    }
  }
}

/**
 * Implements hook_field_presave().
 *
 * Download and save the thumbnail if it hasn't already been stored.
 * Get video data.
 */
function video_embed_field_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  foreach ($items as $delta => $item) {
    // Trim whitespace from the video URL.
    $items[$delta]['video_url'] = trim($item['video_url']);

    // Try to load thumbnail URL.
    $info = video_embed_field_thumbnail_url($item['video_url']);
    if (isset($info['url']) && $info['url']) {
      $thumb_url = $info['url'];
      $thumb_extension = pathinfo($thumb_url, PATHINFO_EXTENSION);
      $local_path = "public://video_embed_field_thumbnails/{$info['handler']}/{$info['id']}.$thumb_extension";

      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

      $response = drupal_http_request($thumb_url);
      if (!isset($response->error)) {
        file_save_data($response->data, $local_path, FILE_EXISTS_REPLACE);
      }
      else {
        @copy($thumb_url, $local_path);
      }

      $items[$delta]['thumbnail_path'] = $local_path;
      // Delete any image derivatives at the original image path.
      image_path_flush($local_path);
    }
    // Couldn't get the thumbnail for whatever reason.
    else {
      $items[$delta]['thumbnail_path'] = '';
    }

    // Try to load video data.
    $data = video_embed_field_get_video_data($item['video_url']);
    if (is_array($data) && !empty($data)) {
      $items[$delta]['video_data'] = serialize($data);
    }
    else {
      $items[$delta]['video_data'] = NULL;
    }

  }
}

/**
 * Implements hook_field_is_empty().
 */
function video_embed_field_field_is_empty($item, $field) {
  return empty($item) || empty($item['video_url']) || $item['video_url'] === '';
}

/**
 * Implements hook_field_formatter_info().
 */
function video_embed_field_field_formatter_info() {
  $info = array(
    'video_embed_field' => array(
      'label' => t('Video Player'),
      'field types' => array('video_embed_field'),
      'settings' => array(
        'video_style' => 'normal',
        'description' => 1,
        'description_position' => 'bottom',
      ),
    ),
    'video_embed_field_url' => array(
      'label' => t('URL to Video'),
      'field types' => array('video_embed_field'),
      'settings' => array(),
    ),
    'video_embed_field_thumbnail' => array(
      'label' => t('Thumbnail Preview'),
      'field types' => array('video_embed_field'),
      'settings' => array(
        'image_style' => '',
        'description' => 1,
        'description_position' => 'bottom',
        'image_link' => 'none',
      ),
    ),
  );
  if (module_exists('colorbox')) {
    $info['video_embed_field_thumbnail_colorbox'] = array(
      'label' => t('Thumbnail Preview w/Colorbox'),
      'field types' => array('video_embed_field'),
      'settings' => array(
        'video_style' => 'normal',
        'image_style' => '',
        'description' => 1,
        'description_position' => 'bottom',
      ),
    );
    $info['video_embed_field_url_colorbox'] = array(
      'label' => t('URL to Video w/Colorbox'),
      'field types' => array('video_embed_field'),
      'settings' => array(
        'video_style' => 'normal',
      ),
    );
  }
  return $info;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function video_embed_field_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  if ($display['type'] == 'video_embed_field' || $display['type'] == 'video_embed_field_thumbnail_colorbox' || $display['type'] == 'video_embed_field_url_colorbox') {
    $video_styles = video_embed_field_video_style_options(FALSE);
    $element['video_style'] = array(
      '#title' => t('Video style'),
      '#type' => 'select',
      '#default_value' => $settings['video_style'],
      '#options' => $video_styles,
    );
  }
  if ($display['type'] == 'video_embed_field_thumbnail' || $display['type'] == 'video_embed_field_thumbnail_colorbox') {
    $element['image_style'] = array(
      '#title' => t('Image style'),
      '#type' => 'select',
      '#options' => image_style_options(FALSE),
      '#default_value' => $settings['image_style'],
      '#empty_option' => t('None (original image)'),
    );
  }

  if ($display['type'] == 'video_embed_field_thumbnail') {
    $link_types = array(
      'content' => t('Content'),
      'source' => t('Video Source'),
    );
    $element['image_link'] = array(
      '#title' => t('Link thumbnail to'),
      '#type' => 'select',
      '#default_value' => $settings['image_link'],
      '#empty_option' => t('Nothing'),
      '#options' => $link_types,
    );
  }

  if ($instance['settings']['description_field'] && $display['type'] != 'video_embed_field_url' && $display['type'] != 'video_embed_field_url_colorbox') {
    $element['description'] = array(
      '#title' => t('Show description'),
      '#type' => 'checkbox',
      '#default_value' => $settings['description'],
    );

    $element['description_position'] = array(
      '#title' => t('Description Position'),
      '#type' => 'select',
      '#options' => array(
        'top' => t('Top'),
        'bottom' => t('Bottom'),
      ),
      '#default_value' => $settings['description_position'],
      '#states' => array(
        'visible' => array(
          ':input[name="fields[' . $field['field_name'] . '][settings_edit_form][settings][description]"]' => array('checked' => TRUE),
        ),
      ),
    );
  }
  return $element;
}
/**
 * Implements hook_field_formatter_settings_summary().
 */
function video_embed_field_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();
  if ($display['type'] == 'video_embed_field' || $display['type'] == 'video_embed_field_thumbnail_colorbox' || $display['type'] == 'video_embed_field_url_colorbox') {
    $video_styles = video_embed_field_video_style_options(FALSE);
    // Styles could be lost because of enabled/disabled modules that defines
    // their styles in code.
    if (isset($video_styles[$settings['video_style']])) {
      $summary[] = t('Video style: @style', array('@style' => $video_styles[$settings['video_style']]));
    }
  }
  if ($display['type'] == 'video_embed_field_thumbnail' || $display['type'] == 'video_embed_field_thumbnail_colorbox') {
    $image_styles = image_style_options(FALSE);
    if (isset($image_styles[$settings['image_style']])) {
      $summary[] = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
    }
    // No Image style (original image).
    else {
      $summary[] = t('Original Image.');
    }
    if (isset($settings['image_link'])) {
      $summary[] = t('Image link: @image_link', array('@image_link' => $settings['image_link']));
    }
    else {
      $summary[] = t('Image link: none');
    }
  }

  if (isset($settings['description'])) {
    if ($settings['description'] && $instance['settings']['description_field']) {
      $summary[] = t('Show description');
    }
    elseif ($instance['settings']['description_field']) {
      $summary[] = t('Hide description');
    }
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function video_embed_field_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  if ($display['type'] == 'video_embed_field_thumbnail' && $display['settings']['image_link'] == 'content') {
    $path = entity_uri($entity_type, $entity);
  }

  foreach ($items as $delta => $item) {
    // Create the render array for the description.
    if (isset($item['description']) && $item['description'] && $settings['description'] && $instance['settings']['description_field']) {
      $description = array(
        '#prefix' => '<div class="video-embed-description">',
        '#markup' => check_plain($item['description']),
        '#suffix' => '</div>',
      );
      $alt = $item['description'];
    }
    else {
      $description = array();
      $alt = '';
    }

    // Render the field.
    if ($display['type'] == 'video_embed_field') {
      $element[$delta] = array(
        array(
          '#theme' => 'video_embed_field_embed_code',
          '#url' => $item['video_url'],
          '#style' => $settings['video_style'],
          '#video_data' => !empty($item['video_data']) ? unserialize($item['video_data']) : array(),
        ),
      );
    }
    elseif ($display['type'] == 'video_embed_field_url') {
      $element[$delta] = array(
        array(
          '#markup' => url($item['video_url']),
        ),
      );
    }
    elseif ($display['type'] == 'video_embed_field_thumbnail') {
      if (isset($item['thumbnail_path'])) {
        if ($display['settings']['image_link'] == 'source') {
          if ($ret = parse_url($item['video_url'])) {
            if (!isset($ret["scheme"])) {
              $item['video_url'] = "http://{$item['video_url']}";
            }
          }
          $path = array(
            'path' => $item['video_url'],
            'options' => array(),
          );
        }

        $element[$delta] = array(
          '#theme' => 'image_formatter',
          '#item' => array('uri' => $item['thumbnail_path'], 'alt' => $alt),
          '#image_style' => $display['settings']['image_style'],
          '#path' => isset($path) ? $path : '',
        );
      }
      // Incase no thumbnail was downloaded/provider doesn't support thumbnails.
      else {
        $element[$delta] = array();
      }
    }
    elseif ($display['type'] == 'video_embed_field_thumbnail_colorbox') {
      if (isset($item['thumbnail_path'])) {
        if ($ret = parse_url($item['video_url'])) {
          if (!isset($ret["scheme"])) {
            $item['video_url'] = "http://{$item['video_url']}";
          }
        }
        $element[$delta] = array(
          array(
            '#theme' => 'video_embed_field_colorbox_code',
            '#image_url' => $item['thumbnail_path'],
            '#image_style' => $display['settings']['image_style'],
            '#image_alt' => $alt,
            '#video_url' => $item['video_url'],
            '#video_style' => $display['settings']['video_style'],
            '#video_data' => unserialize($item['video_data']),
          ),
        );
      }
      // Incase no thumbnail was downloaded/provider doesn't support thumbnails.
      else {
        $element[$delta] = array();
      }
    }
    elseif ($display['type'] == 'video_embed_field_url_colorbox') {
      $path = video_embed_field_get_ajax_url($item['video_url'], $display['settings']['video_style']);

      $element[$delta] = array(
        array(
          '#markup' => url($path['path'], $path['options']),
        ),
      );
    }
    // Get the HTML instead of the array, because we append it to the suffix.
    // This way, the thumbnail link doesn't make the description a link as well.
    $description_html = drupal_render($description);

    $pos = isset($settings['description_position']) ? $settings['description_position'] : 'bottom';
    if ($pos == 'top') {
      $element[$delta]['#prefix'] = isset($element[$delta]['#prefix']) ? $element[$delta]['#prefix'] : '';
      $element[$delta]['#prefix'] = $description_html . $element[$delta]['#prefix'];
    }
    else {
      $element[$delta]['#suffix'] = isset($element[$delta]['#suffix']) ? $element[$delta]['#suffix'] : '';
      $element[$delta]['#suffix'] .= $description_html;
    }
  }

  return $element;
}
