<?php

/**
 * @file
 * Functions related to features integration.
 */

/**
 * Implements hook_features_api().
 */
function media_wysiwyg_features_api() {
  return array(
    'media_wysiwyg' => array(
      'name' => t('Media WYSIWYG'),
      'feature_source' => TRUE,
      'default_hook' => 'media_wysiwyg_defaults',
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
    ),
  );
}

/**
 * Implements hook_features_export_options().
 *
 * Defines what shows up in the feature creation interface
 */
function media_wysiwyg_features_export_options() {
  $options = array();
  $entity_info = entity_get_info('file');
  foreach ($entity_info['bundles'] as $file_type => $file_type_info) {
    $file_type_label = check_plain($file_type_info['label']);
    $options[$file_type . '_wysiwyg_view_mode'] =
      t('@file_type WYSIWYG view mode', array('@file_type' => $file_type_label));

    $view_mode_settings = field_view_mode_settings('file', $file_type);
    foreach ($entity_info['view modes'] as $view_mode => $view_mode_info) {
      if (!empty($view_mode_settings[$view_mode]['custom_settings'])) {
        $options[$file_type . '_' . $view_mode . '_restrict_wysiwyg'] =
          t('@file_type view mode restriction: @view_mode',
          array('@file_type' => $file_type_label, '@view_mode' => $view_mode_info['label']));
      }
    }
    // Add default option.
    $options[$file_type . '_default_restrict_wysiwyg'] =
      t('@file_type view mode restriction: Default',  array(
        '@file_type' => $file_type_label,
      ));
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function media_wysiwyg_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['media_wysiwyg'] = 'media_wysiwyg';

  $entity_info = entity_get_info('file');
  foreach ($entity_info['bundles'] as $file_type => $file_type_info) {

    // Export the wysiwyg view mode setting for the file type.
    $mode_data_key = $file_type . '_wysiwyg_view_mode';
    if (in_array($mode_data_key, $data, TRUE)) {
      $view_mode = _media_wysiwyg_get_wysiwyg_mode($file_type);
      $export['features']['media_wysiwyg'][$mode_data_key] = $mode_data_key;
    }
    // Export the restricted view modes for the file type.
    $view_modes = array_keys($entity_info['view modes']);
    array_push($view_modes, 'default');
    foreach ($view_modes as $view_mode) {
      $restrict_data_key = $file_type . '_' . $view_mode . '_restrict_wysiwyg';
      if (in_array($restrict_data_key, $data, TRUE)) {
        $export['features']['media_wysiwyg'][$restrict_data_key] = $restrict_data_key;
      }
    }
  }
}

/**
 * Implements hook_features_export_render().
 */
function media_wysiwyg_features_export_render($module_name = '', $data, $export = NULL) {
  $code = array();
  $code[] = '  $media_wysiwyg = array();';
  $code[] = '';

  $entity_info = entity_get_info('file');
  foreach ($entity_info['bundles'] as $file_type => $file_type_info) {

    // Render the wysiwyg view mode setting for the file type.
    $mode_data_key = $file_type . '_wysiwyg_view_mode';
    if (array_key_exists($mode_data_key, $data) || in_array($mode_data_key, $data, TRUE)) {
      $view_mode = _media_wysiwyg_get_wysiwyg_mode($file_type);
      $view_mode_export =  (!empty($view_mode) ? features_var_export($view_mode) : "'none'");
      $code[] = "  // WYSIWYG view mode for $file_type files.";
      $code[] = "  \$media_wysiwyg['{$mode_data_key}'] = {$view_mode_export};";
      $code[] = "";
    }

    // Export the restricted view modes for the file type.
    $restriction_code = array();
    $restricted_view_modes = _media_wysiwyg_get_restricted_modes($file_type);
    $view_modes = array_keys($entity_info['view modes']);
    array_push($view_modes, 'default');
    foreach ($view_modes as $view_mode) {
      $restrict_data_key = $file_type . '_' . $view_mode . '_restrict_wysiwyg';
      if (array_key_exists($restrict_data_key, $data) || in_array($restrict_data_key, $data, TRUE)) {
        $displays_export = in_array($view_mode, $restricted_view_modes) ? 'TRUE' : 'FALSE';
        $restriction_code[] = "  \$media_wysiwyg['{$restrict_data_key}'] = {$displays_export};";
      }
    }
    if (!empty($restriction_code)) {
      array_unshift($restriction_code, "  // Restricted view modes for $file_type files.");
      $restriction_code[] = "";
      $code = array_merge($code, $restriction_code);
    }
  }

  $code[] = '  return $media_wysiwyg;';
  $code = implode("\n", $code);

  return array('media_wysiwyg_defaults' => $code);
}

/**
 * Implements hook_features_revert().
 */
function media_wysiwyg_features_revert($module) {
  if ($defaults = features_get_default('media_wysiwyg', $module)) {

    $entity_info = entity_get_info('file');
    foreach ($entity_info['bundles'] as $file_type => $file_type_info) {

      $mode_data_key = $file_type . '_wysiwyg_view_mode';
      if (isset($defaults[$mode_data_key])) {
        $view_mode = $defaults[$mode_data_key];
        db_delete('media_view_mode_wysiwyg')
          ->condition('type', $file_type)
          ->execute();
        if ($view_mode != 'none') {
          $record = array('type' => $file_type, 'view_mode' => $view_mode);
          drupal_write_record('media_view_mode_wysiwyg', $record);
        }
      }

      $view_modes = array_keys($entity_info['view modes']);
      array_push($view_modes, 'default');
      foreach ($view_modes as $view_mode) {
        $restrict_data_key = $file_type . '_' . $view_mode . '_restrict_wysiwyg';
        if (isset($defaults[$restrict_data_key])) {
          db_delete('media_restrict_wysiwyg')
            ->condition('type', $file_type)
            ->condition('display', $view_mode)
            ->execute();
          if ($defaults[$restrict_data_key]) {
            $record = array(
              'type' => $file_type,
              'display' => $view_mode);
            drupal_write_record('media_restrict_wysiwyg', $record);
          }
        }
      }
    }
  }
}

/**
 * Implements hook_features_rebuild().
 */
function media_wysiwyg_features_rebuild($module) {
  media_wysiwyg_features_revert($module);
}

/**
 * Implements hook_features_enable_feature().
 */
function media_wysiwyg_features_enable_feature($module) {
  media_wysiwyg_features_revert($module);
}

/**
 * Retrieve the WYSIWYG view mode for the specified file type.
 *
 * @param string $file_type
 *   The machine name of the file type.
 */
function _media_wysiwyg_get_wysiwyg_mode($file_type) {
  $view_mode = db_query(
    'SELECT view_mode FROM {media_view_mode_wysiwyg} WHERE type = :type',
    array(':type' => $file_type))
    ->fetchField();
  return $view_mode;
}

/**
 * Retrieve a list of view modes that should not be available in the WYSIWYG for
 * the specified file type.
 *
 * @param string $file_type
 *   The machine name of the file type.
 */
function _media_wysiwyg_get_restricted_modes($file_type) {
  $restricted_view_modes = db_query(
    'SELECT display FROM {media_restrict_wysiwyg} WHERE type = :type',
    array(':type' => $file_type))
    ->fetchCol();
  return $restricted_view_modes;
}
