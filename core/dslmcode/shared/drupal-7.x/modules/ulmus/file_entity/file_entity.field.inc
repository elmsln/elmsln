<?php

/**
 * @file
 * Field API integration for the file_entity module.
 */

/**
 * Implements hook_field_formatter_info().
 */
function file_entity_field_formatter_info() {
  $info['file_rendered'] = array(
    'label' => t('Rendered file'),
    'description' => t('Display the file in a specific view mode'),
    'field types' => array('file', 'image'),
    'settings' => array(
      'file_view_mode' => 'default',
    ),
    'file formatter' => array(
      'hidden' => TRUE,
    ),
  );
  $info['file_download_link'] = array(
    'label' => t('Download link'),
    'description' => t('Displays a link that will force the browser to download the file.'),
    'field types' => array('file', 'image'),
    'settings' => array(
      'text' => t('Download [file:name]'),
    ),
  );
  $info['file_audio'] = array(
    'label' => t('Audio'),
    'description' => t('Render the file using an HTML5 audio tag.'),
    'field types' => array('file'),
    'settings' => array(
      'controls' => TRUE,
      'controls_list' => array(
        'download' => 'download',
        'remote_playback' => 'remote_playback',
      ),
      'autoplay' => FALSE,
      'loop' => FALSE,
      'preload' => '',
      'multiple_file_behavior' => 'tags',
    ),
    'file formatter' => array(
      'mime types' => array('audio/*'),
    ),
  );
  $info['file_video'] = array(
    'label' => t('Video'),
    'description' => t('Render the file using an HTML5 video tag.'),
    'field types' => array('file'),
    'settings' => array(
      'controls' => TRUE,
      'controls_list' => array(
        'fullscreen' => 'fullscreen',
        'download' => 'download',
        'remote_playback' => 'remote_playback',
      ),
      'autoplay' => FALSE,
      'playsinline' => FALSE,
      'loop' => FALSE,
      'muted' => FALSE,
      'width' => NULL,
      'height' => NULL,
      'preload' => '',
      'multiple_file_behavior' => 'tags',
    ),
    'file formatter' => array(
      'mime types' => array('video/*'),
    ),
  );
  return $info;
}

/**
 * Implements hook_field_formatter_info_alter().
 */
function file_entity_field_formatter_info_alter(&$info) {
  // Add descriptions to core formatters.
  $descriptions = array(
    'file_default' => t('Create a simple link to the file. The link is prefixed by a file type icon and the name of the file is used as the link text'),
    'file_table' => t('Build a two-column table where the first column contains a generic link to the file and the second column displays the size of the file.'),
    'file_url_plain' => t('Display a plain text URL to the file.'),
    'image' => t('Format the file as an image. The image can be displayed using an image style and can optionally be linked to the image file itself or its parent content.'),
  );
  foreach ($descriptions as $key => $description) {
    if (isset($info[$key]) && empty($info[$key]['description'])) {
      $info[$key]['description'] = $description;
    }
  }

  // Formatters that can be used for images but not files, should have a
  // default mimetype restriction added to the image/* mime type for use with
  // file formatters.
  foreach ($info as &$formatter) {
    if (!isset($formatter['file formatter']) && in_array('image', $formatter['field types']) && !in_array('file', $formatter['field types'])) {
      $formatter['file formatter']['mime types'] = array('image/*');
    }
  }
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function file_entity_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  if ($display['type'] == 'file_rendered') {
    $element['file_view_mode'] = array(
      '#title'   => t('View mode'),
      '#type'    => 'select',
      '#options' => file_entity_view_mode_labels(),
      '#default_value' => $settings['file_view_mode'],
      // Never empty, so no #empty_option
    );
  }
  elseif ($display['type'] == 'file_download_link') {
    $element['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link text'),
      '#description' => t('This field support tokens.'),
      '#default_value' => $settings['text'],
      '#required' => TRUE,
    );
  }
  elseif ($display['type'] == 'file_audio') {
    $element['controls'] = array(
      '#title' => t('Show audio controls'),
      '#type' => 'checkbox',
      '#default_value' => $settings['controls'],
    );
    $element['controls_list'] = array(
      '#title' => t('Controls list'),
      '#type' => 'checkboxes',
      '#options' => array(
        'download' => t('Download'),
        'remote_playback' => t('Remote playback'),
      ),
      '#default_value' => $settings['controls_list'],
      '#description' => t("Customize native media controls such as the download and remoteplayback buttons. Valid only if above \"Show audio controls\" setting is enabled.<br>Please note that not all browsers support this feature. Only Chrome 58+ and Opera 45+ supports it."),
    );
    $element['autoplay'] = array(
      '#title' => t('Autoplay'),
      '#type' => 'checkbox',
      '#default_value' => $settings['autoplay'],
    );
    $element['loop'] = array(
      '#title' => t('Loop'),
      '#type' => 'checkbox',
      '#default_value' => $settings['loop'],
    );
    $element['preload'] = array(
      '#title' => t('Preload'),
      '#type' => 'select',
      '#default_value' => $settings['preload'],
      '#options' => drupal_map_assoc(array('none', 'auto', 'metadata')),
      '#empty_option' => 'unspecified',
    );
    $element['multiple_file_behavior'] = array(
      '#title' => t('Display of multiple files'),
      '#type' => 'radios',
      '#options' => array(
        'tags' => t('Use multiple @tag tags, each with a single source', array('@tag' => '<audio>')),
        'sources' => t('Use multiple sources within a single @tag tag', array('@tag' => '<audio>')),
      ),
      '#default_value' => $settings['multiple_file_behavior'],
      // Hide this setting in the manage file display configuration.
      '#access' => !empty($field),
    );

  }
  elseif ($display['type'] == 'file_video') {
    $element['controls'] = array(
      '#title' => t('Show video controls'),
      '#type' => 'checkbox',
      '#default_value' => $settings['controls'],
    );
    $element['controls_list'] = array(
      '#title' => t('Controls list'),
      '#type' => 'checkboxes',
      '#options' => array(
        'fullscreen' => t('Fullscreen'),
        'download' => t('Download'),
        'remote_playback' => t('Remote playback'),
      ),
      '#default_value' => $settings['controls_list'],
      '#description' => t("Customize native media controls such as the download, fullscreen and remoteplayback buttons. Valid only if above \"Show video controls\" setting is enabled.<br>Please note that not all browsers support this feature. Only Chrome 58+ and Opera 45+ supports it."),
    );
    $element['autoplay'] = array(
      '#title' => t('Autoplay'),
      '#type' => 'checkbox',
      '#default_value' => $settings['autoplay'],
    );
    $element['playsinline'] = array(
      '#title' => t('Plays inline'),
      '#type' => 'checkbox',
      '#default_value' => $settings['playsinline'],
    );
    $element['loop'] = array(
      '#title' => t('Loop'),
      '#type' => 'checkbox',
      '#default_value' => $settings['loop'],
    );
    $element['muted'] = array(
      '#title' => t('Muted'),
      '#type' => 'checkbox',
      '#default_value' => $settings['muted'],
    );
    $element['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $settings['width'],
      '#size' => 5,
      '#maxlength' => 5,
      '#field_suffix' => t('pixels'),
    );
    $element['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $settings['height'],
      '#size' => 5,
      '#maxlength' => 5,
      '#field_suffix' => t('pixels'),
    );
    $element['preload'] = array(
      '#title' => t('Preload'),
      '#type' => 'select',
      '#default_value' => $settings['preload'],
      '#options' => drupal_map_assoc(array('none', 'auto', 'metadata')),
      '#empty_option' => 'unspecified',
    );
    $element['multiple_file_behavior'] = array(
      '#title' => t('Display of multiple files'),
      '#type' => 'radios',
      '#options' => array(
        'tags' => t('Use multiple @tag tags, each with a single source', array('@tag' => '<video>')),
        'sources' => t('Use multiple sources within a single @tag tag', array('@tag' => '<video>')),
      ),
      '#default_value' => $settings['multiple_file_behavior'],
      // Hide this setting in the manage file display configuration.
      '#access' => !empty($field),
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function file_entity_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = array();

  if ($display['type'] === 'file_rendered') {
    $view_mode_label = file_entity_view_mode_label($settings['file_view_mode'], t('Unknown'));
    $summary[] = t('View mode: %mode', array('%mode' => $view_mode_label));
  }
  elseif ($display['type'] == 'file_download_link') {
    $summary[] = t('Link text: %text', array('%text' => $settings['text']));
  }
  elseif ($display['type'] === 'file_audio') {
    if (isset($settings['controls'])) {
      $summary[] = t('Controls: %controls', array('%controls' => $settings['controls'] ? 'visible' : 'hidden'));
      if (!empty($settings['controls_list'])) {
        $controls_list = array();
        foreach ($settings['controls_list'] as $key => $value) {
          if ($value) {
            $controls_list[] = ucfirst(str_replace('_', ' ', $key));
          }
        }
        if (!empty($controls_list)) {
          $summary[] = t('Controls list: %controls_list', array('%controls_list' => implode(', ', $controls_list)));
        }
      }
    }
    if (isset($settings['autoplay'])) {
      $summary[] = t('Autoplay: %autoplay', array('%autoplay' => $settings['autoplay'] ? t('yes') : t('no')));
    }
    if (isset($settings['loop'])) {
      $summary[] = t('Loop: %loop', array('%loop' => $settings['loop'] ? t('yes') : t('no')));
    }
    if (!empty($settings['preload'])) {
      $summary[] = t('Preload: %preload', array('%preload' => $settings['preload']));
    }
    if (isset($settings['multiple_file_behavior'])) {
      $summary[] = t('Multiple files: %multiple', array('%multiple' => $settings['multiple_file_behavior']));
    }
  }
  elseif ($display['type'] === 'file_video') {
    if (isset($settings['controls'])) {
      $summary[] = t('Controls: %controls', array('%controls' => $settings['controls'] ? 'visible' : 'hidden'));
      if (!empty($settings['controls_list'])) {
        $controls_list = array();
        foreach ($settings['controls_list'] as $key => $value) {
          if ($value) {
            $controls_list[] = ucfirst(str_replace('_', ' ', $key));
          }
        }
        if (!empty($controls_list)) {
          $summary[] = t('Controls list: %controls_list', array('%controls_list' => implode(', ', $controls_list)));
        }
      }
    }
    if (isset($settings['autoplay'])) {
      $summary[] = t('Autoplay: %autoplay', array('%autoplay' => $settings['autoplay'] ? t('yes') : t('no')));
    }
    if (isset($settings['playsinline'])) {
      $summary[] = t('Plays inline: %playsinline', array('%playsinline' => $settings['playsinline'] ? t('yes') : t('no')));
    }
    if (isset($settings['loop'])) {
      $summary[] = t('Loop: %loop', array('%loop' => $settings['loop'] ? t('yes') : t('no')));
    }
    if (isset($settings['muted'])) {
      $summary[] = t('Muted: %muted', array('%muted' => $settings['muted'] ? t('yes') : t('no')));
    }
    if ($settings['width'] && $settings['height']) {
      $summary[] = t('Size: %width x %height', array('%width' => $settings['width'], '%height' => $settings['height']));
    }
    if (!empty($settings['preload'])) {
      $summary[] = t('Preload: %preload', array('%preload' => $settings['preload']));
    }
    if (isset($settings['multiple_file_behavior'])) {
      $summary[] = t('Multiple files: %multiple', array('%multiple' => $settings['multiple_file_behavior']));
    }
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function file_entity_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  // File and image fields set item values to NULL if a file cannot be loaded.
  // Remove those empty items so we can simply iterate through $items normally
  // in file_entity_field_formatter_view().
  foreach (array_keys($entities) as $id) {
    $items[$id] = array_filter($items[$id]);
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function file_entity_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  switch ($display['type']) {
    case 'file_rendered':
      foreach ($items as $delta => $item) {
        if (!empty($item)) {
          // The repeat-rendering protection may be disabled if necessary.
          if (variable_get('file_entity_protect_repeated_render', TRUE)) {
            // Protect ourselves from repeated rendering.
            static $repeated_render_depth = array();
            list($entity_id) = entity_extract_ids($entity_type, $entity);
            $repeated_render_id = $entity_type . $entity_id . $field['field_name'] . $item['fid'];
            if (isset($repeated_render_depth[$repeated_render_id])) {
              $repeated_render_depth[$repeated_render_id]++;
            }
            else {
              $repeated_render_depth[$repeated_render_id] = 1;
            }

            if ($repeated_render_depth[$repeated_render_id] > 20) {
              watchdog(
                'file_entity',
                'Repeated rendering detected when rendering entity %entity_type: %entity_id, using the %field_name field. Aborting rendering.',
                array(
                  '%entity_type' => 'file',
                  '%entity_id' => $item['fid'],
                  '%field_name' => $field['field_name'],
                ),
                WATCHDOG_ERROR
              );
              return $element;
            }
          }

          $file = file_load($item['fid']);
          if (isset($item['display'])) {
            $file->display = $item['display'];
          }
          if (isset($item['description'])) {
            $file->description = $item['description'];
          }

          // Add some references to the referencing entity.
          // @see https://www.drupal.org/node/2333107
          $file->referencing_entity = $entity;
          $file->referencing_entity_type = $entity_type;
          $file->referencing_field = $field['field_name'];

          // Prevent recursion by checking if the referencing entity is itself
          // do not display it again (return an empty array).
          // This senario is created a few lines below when file_view is called
          // it returns an array containing a referncing entity that is itself.
          // This is likely treating the symptom and not the root cause which is
          // probably buried in some hook_file_view() setting the referencing
          // entity.
          if (!empty($entity->fid) && $entity->fid === $item['fid']) {
            return $element;
          }
          // Untranslatable fields are rendered with no language code, fall back
          // to the content language in that case.
          $element[$delta] = file_view($file, $settings['file_view_mode'], $langcode !== LANGUAGE_NONE ? $langcode : NULL);
        } else {
          watchdog(
            'file_entity',
            'In the %referencing_entity_type, the %field_name field refers to a %entity_type which does not exist. Aborting the render for it.',
            array(
              '%referencing_entity_type' => $entity_type,
              '%field_name' => $field['field_name'],
              '%entity_type' => 'file',
            ),
            WATCHDOG_ERROR
          );
        }
      }
      break;

    case 'file_download_link':
      // Prevent 'empty' fields from causing a WSOD.
      $items = array_filter($items);
      foreach ($items as $delta => $item) {
        if (!empty($item['fid']) && ($file = file_load($item['fid'])) && file_entity_access('download', $file)) {
          if (isset($item['display'])) {
            $file->display = $item['display'];
          }
          if (isset($item['description'])) {
            $file->description = $item['description'];
          }
          $element[$delta] = array(
            '#theme' => 'file_entity_download_link',
            '#file' => $file,
            '#text' => $settings['text'],
          );
        }
      }
      break;

    case 'file_audio':
      $multiple_file_behavior = $settings['multiple_file_behavior'];

      // Build an array of sources for each <audio> element.
      $source_lists = array();
      if ($multiple_file_behavior == 'tags') {
        foreach ($items as $delta => $item) {
          if (file_entity_file_get_mimetype_type($item) == 'audio') {
            $source_lists[$delta] = array($item);
          }
        }
      }
      else {
        foreach ($items as $delta => $item) {
          if (file_entity_file_get_mimetype_type($item) == 'audio') {
            $source_lists[0][$delta] = $item;
          }
        }
      }

      // Render each source list as an <audio> element.
      foreach ($source_lists as $delta => $sources) {
        $element[$delta] = array(
          '#theme' => 'file_entity_file_audio',
          '#files' => $sources,
          '#controls' => $settings['controls'],
          '#controls_list' => $settings['controls_list'],
          '#autoplay' => $settings['autoplay'],
          '#loop' => $settings['loop'],
          '#preload' => $settings['preload'],
        );
      }
      break;

    case 'file_video':
      $multiple_file_behavior = $settings['multiple_file_behavior'];

      // Build an array of sources for each <video> element.
      $source_lists = array();
      if ($multiple_file_behavior == 'tags') {
        foreach ($items as $delta => $item) {
          if (file_entity_file_get_mimetype_type($item) == 'video') {
            $source_lists[$delta] = array($item);
          }
        }
      }
      else {
        foreach ($items as $delta => $item) {
          if (file_entity_file_get_mimetype_type($item) == 'video') {
            $source_lists[0][$delta] = $item;
          }
        }
      }

      // Render each source list as an <video> element.
      foreach ($source_lists as $delta => $sources) {
        $element[$delta] = array(
          '#theme' => 'file_entity_file_video',
          '#files' => $sources,
          '#controls' => $settings['controls'],
          '#controls_list' => $settings['controls_list'],
          '#autoplay' => $settings['autoplay'],
          '#playsinline' => $settings['playsinline'],
          '#loop' => $settings['loop'],
          '#muted' => $settings['muted'],
          '#width' => $settings['width'],
          '#height' => $settings['height'],
          '#preload' => $settings['preload'],
        );
      }
      break;
  }

  return $element;
}
