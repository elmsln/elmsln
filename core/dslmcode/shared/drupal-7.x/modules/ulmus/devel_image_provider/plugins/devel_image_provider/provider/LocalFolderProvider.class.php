<?php
/**
 * @file
 * Local folder support class.
 */

/**
 * Add support for local images.
 */
class LocalFolderProvider extends DevelImagesProviderBase {

  function availableMethods() {
    // No fetch method as it grabs the images from local folder.
    return array();
  }

  function settingsForm() {
    $form = parent::settingsForm();
    unset($form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_gray']);

    // Provider specific settings.
    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to folder'),
      '#description' => t('Enter full path of the folder. Example: /home/user1011/images'),
      '#size' => 90,
      '#default_value' => isset($this->settings['devel_image_provider_path']) ? $this->settings['devel_image_provider_path'] : '',
    );
    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_no_alter'] = array(
      '#type' => 'checkbox',
      '#title' => t('Do not alter images when picking them from the source directory.'),
      '#description' => t('Use for performance reasons, if checked, the images will be used as they are present in the source directory bypassing all field or instance settings such as file size or dimensions.'),
      '#default_value' => isset($this->settings['devel_image_no_alter']) ? $this->settings['devel_image_no_alter'] : '',
    );

    return $form;
  }

  public function settingsFormValidate(&$form, &$form_state) {
    if (empty($form_state['values']['config_providers']['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_path'])) {
      form_error($form['config_providers']['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_path'], t('Path cannot be empty'));
      return FALSE;
    }
    if (!is_readable($form_state['values']['config_providers']['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_path'])) {
      form_error($form['config_providers']['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_path'], t('Specified folder is not valid or not readable'));
    }
  }

  public function generateImage($object, $field, $instance, $bundle) {
    $object_field = array();
    static $available_images = array();
    if (empty($available_images)) {
      $available_images = $this->getImages();
    }
    if (empty($available_images)) {
      $args = func_get_args();
      return call_user_func_array('_image_devel_generate', $args);
    }

    $extension = array_rand(array('jpg' => 'jpg', 'png' => 'png'));
    $min_resolution = empty($instance['settings']['min_resolution']) ? '100x100' : $instance['settings']['min_resolution'];
    $max_resolution = empty($instance['settings']['max_resolution']) ? '600x600' : $instance['settings']['max_resolution'];
    if (FALSE === ($tmp_file = drupal_tempnam('temporary://', 'imagefield_'))) {
      return FALSE;
    }
    $destination = $tmp_file . '.' . $extension;
    file_unmanaged_move($tmp_file, $destination, FILE_EXISTS_REPLACE);
    $rand_file = array_rand($available_images);
    if (!empty($instance['settings']['file_directory'])) {
      $instance['settings']['file_directory'] = $instance['settings']['file_directory'] . '/';
    }
    $destination_dir = $field['settings']['uri_scheme'] . '://' . $instance['settings']['file_directory'];
    file_prepare_directory($destination_dir, FILE_CREATE_DIRECTORY);
    if ($this->settings['devel_image_no_alter']) {
      $file = $available_images[$rand_file];
      $file = file_copy($file, $destination_dir);
    }
    else {
      $image = image_load($rand_file);
      $min = explode('x', $min_resolution);
      $max = explode('x', $max_resolution);
      $max[0] = $max[0] < $min[0] ? $min[0] : $max[0];
      $max[1] = $max[1] < $min[1] ? $min[1] : $max[1];
      $width = rand((int) $min[0], (int) $max[0]);
      $height = rand((int) $min[1], (int) $max[1]);
      if (!image_scale_and_crop($image, $width, $height)) {
        return FALSE;
      }
      // Use destination image type.
      $image->info['extension'] = $extension;
      if (!image_save($image, $destination)) {
        return FALSE;
      }
      $source = new stdClass();
      $source->uri = $destination;
      $source->uid = 1; // TODO: randomize? Use case specific.
      $source->filemime = $image->info['mime_type'];
      $source->filename = drupal_basename($image->source);
      $destination = $destination_dir . basename($destination);
      $file = file_move($source, $destination, FILE_CREATE_DIRECTORY);
    }
    $object_field['fid'] = $file->fid;
    $object_field['alt'] = devel_create_greeking(4);
    $object_field['title'] = devel_create_greeking(4);
    return $object_field;
  }

  /**
   * Helper function to get all the images from the configured folder.
   */
  private function getImages() {
    if ($files = cache_get('devel_image_provider_local')) {
      return $files->data;
    }
    $files = array();
    $count = 1;
    // Limiting number of images to find to 100.
    // @TODO: add this as a setting.
    $max_count = 100;
    // Remove trailing slash.
    $dir = rtrim($this->settings['devel_image_provider_path'], '/');
    if (is_dir($dir) && $handle = opendir($dir)) {
      while (FALSE !== ($filename = readdir($handle)) && ($count <= $max_count)) {
        $path = "$dir/$filename";
        if (($filename[0] != '.') && preg_match('/.*\.(jpg|jpeg|png)$/i', $filename) && ($image = image_get_info($path))) {
          $file = new stdClass();
          $file->uri = file_stream_wrapper_uri_normalize($path);
          $file->filename = $filename;
          $file->filemime = $image['mime_type'];
          $file->name = pathinfo($filename, PATHINFO_FILENAME);
          $files[$file->uri] = $file;
          $count++;
        }
      }
      closedir($handle);
    }
    cache_set('devel_image_provider_local', $files, 'cache', CACHE_TEMPORARY);
    return $files;
  }

}
