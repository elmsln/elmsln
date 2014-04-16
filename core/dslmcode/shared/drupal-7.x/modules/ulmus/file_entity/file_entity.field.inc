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
      'autoplay' => FALSE,
      'loop' => FALSE,
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
      'autoplay' => FALSE,
      'loop' => FALSE,
      'muted' => FALSE,
      'width' => NULL,
      'height' => NULL,
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
    }
    if (isset($settings['autoplay'])) {
      $summary[] = t('Autoplay: %autoplay', array('%autoplay' => $settings['autoplay'] ? t('yes') : t('no')));
    }
    if (isset($settings['loop'])) {
      $summary[] = t('Loop: %loop', array('%loop' => $settings['loop'] ? t('yes') : t('no')));
    }
    if (isset($settings['multiple_file_behavior'])) {
      $summary[] = t('Multiple files: %multiple', array('%multiple' => $settings['multiple_file_behavior']));
    }

  }
  elseif ($display['type'] === 'file_video') {
    $summary_items = array();
    if (isset($settings['controls'])) {
      $summary[] = t('Controls: %controls', array('%controls' => $settings['controls'] ? 'visible' : 'hidden'));
    }
    if (isset($settings['autoplay'])) {
      $summary[] = t('Autoplay: %autoplay', array('%autoplay' => $settings['autoplay'] ? t('yes') : t('no')));
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
    if (isset($settings['multiple_file_behavior'])) {
      $summary[] = t('Multiple files: %multiple', array('%multiple' => $settings['multiple_file_behavior']));
    }
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function file_entity_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $settings = $display['settings'];
  $element = array();

  if ($display['type'] == 'file_rendered') {
    $view_mode = $settings['file_view_mode'];

    // To prevent infinite recursion caused by reference cycles, we store
    // diplayed nodes in a recursion queue.
    $recursion_queue = &drupal_static(__FUNCTION__, array());

    // If no 'referencing entity' is set, we are starting a new 'reference
    // thread' and need to reset the queue.
    // @todo Bug: $entity->referencing_entity on files referenced in a different
    // thread on the page.
    // E.g: 1 references 1+2 / 2 references 1+2 / visit homepage.
    // We'd need a more accurate way...
    if (!isset($entity->referencing_entity)) {
      $recursion_queue = array();
    }

    // The recursion queue only needs to track files.
    if ($entity_type == 'file') {
      list($id) = entity_extract_ids($entity_type, $entity);
      $recursion_queue[$id] = $id;
    }

    // Prevent 'empty' fields from causing a WSOD.
    $items = array_filter($items);

    // Check the recursion queue to determine which nodes should be fully
    // displayed, and which nodes will only be displayed as a title.
    $files_display = array();
    foreach ($items as $delta => $item) {
      if (!isset($recursion_queue[$item['fid']])) {
        $files_display[$item['fid']] = file_load($item['fid']);
        if (!empty($item['description'])) {
          $files_display[$item['fid']]->description = $item['description'];
        }
      }
    }

    // Load and build the fully displayed nodes.
    if ($files_display) {
      foreach ($files_display as $fid => $file) {
        $files_display[$fid]->referencing_entity = $entity;
        $files_display[$fid]->referencing_field = $field['field_name'];
      }
      $output = file_view_multiple($files_display, $view_mode);
      // Remove the first level from the output array.
      $files_built = reset($output);
    }

    // Assemble the render array.
    foreach ($items as $delta => $item) {
      if (isset($files_built[$item['fid']])) {
        $element[$delta] = $files_built[$item['fid']];
      }
    }
  }
  elseif ($display['type'] == 'file_download_link') {
    foreach ($items as $delta => $item) {
      $file = (object) $item;
      if (file_entity_file_is_local($file) && file_entity_access('download', $file)) {
        $element[$delta] = array(
          '#theme' => 'file_entity_download_link',
          '#file' => $file,
          '#text' => $settings['text'],
        );
      }
    }
  }
  elseif ($display['type'] == 'file_audio') {
    $multiple_file_behavior = $settings['multiple_file_behavior'];

    // Prevent 'empty' fields from causing a WSOD.
    $items = array_filter($items);

    // Build an array of sources for each <audio> element.
    $source_lists = array();
    if ($multiple_file_behavior == 'tags') {
      foreach ($items as $delta => $item) {
        if ($item['type'] == 'audio') {
          $source_lists[] = array($item);
        }
      }
    }
    else {
      foreach ($items as $delta => $item) {
        if ($item['type'] == 'audio') {
          $source_lists[0][] = $item;
        }
      }
    }

    // Render each source list as an <audio> element.
    foreach ($source_lists as $delta => $sources) {
      $element[$delta] = array(
        '#theme' => 'file_entity_file_audio',
        '#files' => $sources,
        '#controls' => $settings['controls'],
        '#autoplay' => $settings['autoplay'],
        '#loop' => $settings['loop'],
      );
    }
  }
  elseif ($display['type'] == 'file_video') {
    $multiple_file_behavior = $settings['multiple_file_behavior'];

    // Prevent 'empty' fields from causing a WSOD.
    $items = array_filter($items);

    // Build an array of sources for each <video> element.
    $source_lists = array();
    if ($multiple_file_behavior == 'tags') {
      foreach ($items as $delta => $item) {
        if ($item['type'] == 'video') {
          $source_lists[] = array($item);
        }
      }
    }
    else {
      foreach ($items as $delta => $item) {
        if ($item['type'] == 'video') {
          $source_lists[0][] = $item;
        }
      }
    }

    // Render each source list as an <video> element.
    foreach ($source_lists as $delta => $sources) {
      $width = $settings['width'];
      $height = $settings['height'];
      $element[$delta] = array(
        '#theme' => 'file_entity_file_video',
        '#files' => $sources,
        '#controls' => $settings['controls'],
        '#autoplay' => $settings['autoplay'],
        '#loop' => $settings['loop'],
        '#muted' => $settings['muted'],
        '#width' => ($width && $height) ? $width : NULL,
        '#height' => ($width && $height) ? $height : NULL,
      );
    }
  }

  return $element;
}
