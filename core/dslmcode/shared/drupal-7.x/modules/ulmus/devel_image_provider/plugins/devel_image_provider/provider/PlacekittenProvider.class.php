<?php
  /**
   * @file
   * Placekitten support class.
   */

/**
 * Add support for placekiten.com.
 */
class PlacekittenProvider extends DevelImagesProviderBase {

  public function __construct($plugin) {
    parent::__construct($plugin);
    $this->provider_base_url = 'http://placekitten.com';
  }

  public function generateImage($object, $field, $instance, $bundle) {
    static $images = array();

    $min_resolution = empty($instance['settings']['min_resolution']) ? '100x100' : $instance['settings']['min_resolution'];
    $max_resolution = empty($instance['settings']['max_resolution']) ? '600x600' : $instance['settings']['max_resolution'];
    $extension = 'jpg';

    if (!isset($images[$extension][$min_resolution][$max_resolution]) || count($images[$extension][$min_resolution][$max_resolution]) <= DEVEL_GENERATE_IMAGE_MAX) {
      if ($tmp_file = drupal_tempnam('temporary://', 'imagefield_')) {
        $destination = $tmp_file . '.' . $extension;
        file_unmanaged_move($tmp_file, $destination, FILE_CREATE_DIRECTORY);

        $min = explode('x', $min_resolution);
        $max = explode('x', $max_resolution);
        $max[0] = $max[0] < $min[0] ? $min[0] : $max[0];
        $max[1] = $max[1] < $min[1] ? $min[1] : $max[1];

        $width = rand((int) $min[0], (int) $max[0]);
        $height = rand((int) $min[1], (int) $max[1]);

        $gray = isset($this->settings['devel_image_provider_gray']) ? $this->settings['devel_image_provider_gray'] : NULL;
        $gray_part = $gray ? '/g' : '';

        $url = "$this->provider_base_url" . $gray_part . "/$width/$height";

        $method = isset($this->settings['devel_image_provider_get_method']) ? $this->settings['devel_image_provider_get_method'] : 'file_get_contents';
        $path = devel_image_provider_get_file($url, $destination, $method);

        $source = new stdClass();
        $source->uri = $path;
        $source->uid = 1; // TODO: randomize? Use case specific.
        $source->filemime = 'image/jpg';
        if (!empty($instance['settings']['file_directory'])) {
          $instance['settings']['file_directory'] = $instance['settings']['file_directory'] . '/';
        }
        $destination_dir = $field['settings']['uri_scheme'] . '://' . $instance['settings']['file_directory'];
        file_prepare_directory($destination_dir, FILE_CREATE_DIRECTORY);
        $destination = $destination_dir . basename($path);
        $file = file_move($source, $destination, FILE_CREATE_DIRECTORY);
      }
      else {
        return FALSE;
      }
    }
    else {
      // Select one of the images we've already generated for this field.
      $file = new stdClass();
      $file->fid = array_rand($images[$extension][$min_resolution][$max_resolution]);
    }

    $object_field['fid'] = $file->fid;
    $object_field['alt'] = devel_create_greeking(4);
    $object_field['title'] = devel_create_greeking(4);
    return $object_field;
  }

}
