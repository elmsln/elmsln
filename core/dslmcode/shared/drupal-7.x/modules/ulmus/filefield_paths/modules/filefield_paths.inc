<?php

/**
 * @file
 * File (Field) Paths module integration.
 */

/**
 * Implements hook_filefield_paths_field_settings().
 *
 * @param $field
 * @param $instance
 *
 * @return array
 */
function filefield_paths_filefield_paths_field_settings($field, $instance) {
  return array(
    'file_path' => array(
      'title' => 'File path',
      'form'  => array(
        'value' => array(
          '#type'             => 'textfield',
          '#title'            => t('File path'),
          '#maxlength'        => 512,
          '#size'             => 128,
          '#element_validate' => array('_file_generic_settings_file_directory_validate'),
          '#default_value'    => $instance['settings']['file_directory'],
        ),
      ),
    ),
    'file_name' => array(
      'title' => 'File name',
      'form'  => array(
        'value' => array(
          '#type'          => 'textfield',
          '#title'         => t('File name'),
          '#maxlength'     => 512,
          '#size'          => 128,
          '#default_value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
        ),
      ),
    )
  );
}

/**
 * Implements hook_filefield_paths_process_file().
 *
 * @param $type
 * @param $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 */
function filefield_paths_filefield_paths_process_file($type, $entity, $field, $instance, $langcode, &$items) {
  if (isset($instance['settings']['filefield_paths'])) {
    $settings = $instance['settings']['filefield_paths'];

    // Check that the destination is writeable.
    $wrappers = file_get_stream_wrappers(STREAM_WRAPPERS_WRITE);
    foreach ($items as &$file) {
      $source_scheme = file_uri_scheme($file['uri']);
      $temporary_scheme = file_uri_scheme(variable_get('filefield_paths_temp_location', 'public://filefield_paths'));
      $destination_scheme = $field['settings']['uri_scheme'];
      if (in_array($source_scheme, array($temporary_scheme, $destination_scheme)) && !empty($wrappers[$destination_scheme])) {
        // Process file if this is a new entity, 'Active updating' is set or
        // file wasn't previously attached to the entity.
        if (isset($entity->original) && empty($settings['active_updating']) && !empty($entity->original->{$field['field_name']}[$langcode])) {
          foreach ($entity->original->{$field['field_name']}[$langcode] as $original_file) {
            if ($original_file['fid'] == $file['fid']) {
              continue(2);
            }
          }
        }

        $token_data = array(
          'file' => (object) $file,
          $type  => $entity
        );

        // Copy the original file for comparison purposes.
        $old_file = $file;

        // Process filename.
        $settings['file_name']['options']['context'] = 'file_name';
        $file['filename']                            = !empty($settings['file_name']['value']) ? filefield_paths_process_string($settings['file_name']['value'], $token_data, $settings['file_name']['options']) : $file['filename'];

        // Process filepath.
        $settings['file_path']['options']['context'] = 'file_path';
        $path                                        = filefield_paths_process_string($settings['file_path']['value'], $token_data, $settings['file_path']['options']);
        $file['uri']                                 = file_stream_wrapper_uri_normalize("{$destination_scheme}://{$path}/{$file['filename']}");

        // Ensure file uri is no more than 255 characters.
        if (drupal_strlen($file['uri']) > 255) {
          watchdog('filefield_paths', 'File path was truncated.', array(), WATCHDOG_INFO);
          $pathinfo    = pathinfo($file['uri']);
          $file['uri'] = drupal_substr($file['uri'], 0, 254 - drupal_strlen($pathinfo['extension'])) . ".{$pathinfo['extension']}";
        }

        // Finalize file if necessary.
        if ($file !== $old_file) {
          $dirname = drupal_dirname($file['uri']);
          if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY) && $new_file = file_move((object) $old_file, $file['uri'])) {
            // Process regular expression.
            _filefield_paths_replace_path($old_file['uri'], $file['uri'], $entity);

            // Create redirect from old location.
            if (module_exists('redirect') && !empty($settings['redirect']) && $settings['active_updating']) {
              _filefield_paths_create_redirect($old_file['uri'], $new_file->uri);
            }

            // Remove any old empty directories.
            $paths  = explode('/', str_replace("{$source_scheme}://", '', drupal_dirname($old_file['uri'])));
            while ($paths) {
              if (@drupal_rmdir("{$source_scheme}://" . implode('/', $paths)) == TRUE) {
                array_pop($paths);
                continue;
              }
              break;
            }
          }
          else {
            watchdog('filefield_paths', 'The file %old could not be moved to the destination of %new. Ensure your permissions are set correctly.', array(
              '%old' => $old_file['uri'],
              '%new' => $file['uri'],
            ));
          }
        }
      }
    }
  }
}
