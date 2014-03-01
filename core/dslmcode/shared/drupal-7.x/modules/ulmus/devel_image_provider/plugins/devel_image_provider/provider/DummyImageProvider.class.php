<?php
/**
 * @file
 * Dummy image support class.
 */

/**
 * Add support for dummyimage.com.
 */
class DummyImageProvider extends DevelImagesProviderBase {

  public function __construct($plugin) {
    parent::__construct($plugin);
    $this->provider_base_url = 'http://dummyimage.com';
  }

  function settingsForm() {
    $form = parent::settingsForm();

    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_background_color'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom Background Color'),
      '#description' => t('Optional: Enter a background color in hex notation (e.g. #BADA55).'),
      '#default_value' => isset($this->settings['devel_image_provider_background_color']) ? $this->settings['devel_image_provider_background_color'] : NULL,
    );
    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_text_color'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom Text Color'),
      '#description' => t('Optional: Enter a text color in hex notation (e.g. #B00B00). Note that text color requires a background color to be specified as well.'),
      '#default_value' => isset($this->settings['devel_image_provider_text_color']) ? $this->settings['devel_image_provider_text_color'] : NULL,
    );
    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_include_text'] = array(
      '#type' => 'radios',
      '#title' => t('Choose the text added inside the generated image'),
      '#default_value' => isset($this->settings['devel_image_provider_include_text']) ? $this->settings['devel_image_provider_include_text'] : 'default',
      '#options' => array(
        'default' => t('Default (image dimensions)'),
        'random' => t('Random text'),
        'custom' => t('Custom text'),
      ),
    );
    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_custom_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom Text'),
      '#maxlength' => 255,
      '#description' => t('Enter some custom text to be rendered instead of the default image dimensions.'),
      '#default_value' => isset($this->settings['devel_image_provider_custom_text']) ? $this->settings['devel_image_provider_custom_text'] : NULL,
      '#states' => array(
        'visible' => array(
          ':input[name="config_providers[devel_image_provider_' . $this->plugin['name'] . '][devel_image_provider_include_text]"]' => array('value' => 'custom'),
        ),
      ),
    );

    return $form;
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

        $background_color = isset($this->settings['devel_image_provider_background_color']) ? $this->settings['devel_image_provider_background_color'] : FALSE;
        if ($background_color) {
          if (preg_match('/^#[a-f0-9]{6}$/i', $background_color)) {  // Check for valid hex number
            $background_color = "/" . str_replace('#', '', check_plain($background_color));  // Strip out #
          }
          else {
            $background_color = '';
          }
        }
        else {
          $background_color = '';
        }

        $text_color = isset($this->settings['devel_image_provider_text_color']) ? $this->settings['devel_image_provider_text_color'] : FALSE;
        if ($text_color) {
          // Check for valid hex number.
          if (preg_match('/^#[a-f0-9]{6}$/i', $text_color)) {
            // Strip out # character.
            $text_color = "/" . str_replace('#', '', check_plain($text_color));
          }
          else {
            $text_color = '';
          }
        }
        else {
          $text_color = '';
        }

        $include_text = isset($this->settings['devel_image_provider_include_text']) ? $this->settings['devel_image_provider_include_text'] : FALSE;
        switch ($include_text) {
          case 'custom':
            $custom_text = isset($this->settings['devel_image_provider_custom_text']) ? $this->settings['devel_image_provider_custom_text'] : '';
            break;
          case 'random':
            // Small random text as text size is depending on the image size.
            $custom_text = trim(substr(devel_create_greeking(mt_rand(1, 3)), 0, 8));
            break;
          case 'default':
          default:
            $custom_text = '';
            break;
        }
        if (!empty($custom_text)) {
          //Replace the spaces with + as per provider specifications
          $custom_text = "&text=" . str_replace(' ', '+', check_plain($custom_text));
        }

        $url = "$this->provider_base_url/" . $width . "x" . $height . '/' . $background_color . '/' . $text_color . '&text=' . $custom_text;

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
