<?php
/**
 * @file
 * File (Field) Paths module integration.
 */

/**
 * Implements hook_filefield_paths_field_settings().
 */
function filefield_paths_filefield_paths_field_settings() {
  return array(
    'file_path' => array(
      'title' => 'File path',
      'sql' => 'filepath',

      'form' => array(
        'value' => array(
          '#type' => 'textfield',
          '#title' => t('File path'),
          '#maxlength' => 512,
          '#size' => 128,
        ),
      ),
    ),

    'file_name' => array(
      'title' => 'File name',
      'sql' => 'filename',

      'form' => array(
        'value' => array(
          '#type' => 'textfield',
          '#title' => t('File name'),
          '#maxlength' => 512,
          '#size' => 128,
          '#default_value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
        ),
      ),
    )
  );
}

/**
 * Implements hook_filefield_paths_process_file().
 */
function filefield_paths_filefield_paths_process_file($type, $entity, $field, $instance, $langcode, &$items) {
  if (isset($instance['settings']['filefield_paths'])) {
    $settings = $instance['settings']['filefield_paths'];
    foreach ($items as &$file) {
      if (filefield_paths_uri_is_local($file['uri']) && ($file['timestamp'] == REQUEST_TIME || $settings['active_updating'])) {
        $token_data = array(
          'file' => (object) $file,
          $type => $entity
        );

        // Copy the original file for comparision purposes.
        $old_file = $file;

        // Process filename.
        $file['filename'] = !empty($settings['file_name']['value'])
          ? filefield_paths_process_string($settings['file_name']['value'], $token_data, $settings['file_name']['options'])
          : $file['filename'];

        // Process filepath.
        $file['uri'] = "{$field['settings']['uri_scheme']}://" . ltrim(filefield_paths_process_string($settings['file_path']['value'], $token_data, $settings['file_path']['options']) . "/{$file['filename']}", '/');

        // Finalize file if necessary.
        if ($file !== $old_file) {
          $dirname = drupal_dirname($file['uri']);
          if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY) && file_move((object) $old_file, $file['uri'])) {
            // Process regular expression.
            _filefield_paths_replace_path($old_file['uri'], $file['uri'], $entity);

            // Remove any old empty directories.
            $scheme = file_uri_scheme($old_file['uri']);
            $paths = explode('/', str_replace("{$scheme}://", '', drupal_dirname($old_file['uri'])));
            while ($paths) {
              if (@drupal_rmdir("{$scheme}://" . implode('/', $paths)) == TRUE) {
                array_pop($paths);
                continue;
              }
              break;
            }
          }
        }
      }
    }
  }
}
