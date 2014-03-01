<?php
/**
 * @file
 * Base devel image providers plugin class.
 */

/**
 * Abstraction of the handling logic of a provider.
 */
interface DevelImagesProviderInterface {

  /**
   * Sets the available methods to get the images from this provider.
   */
  public function availableMethods();

  /**
   * Generates a settings form for this handler.
   */
  public function settingsForm();

  /**
   * Generates a settings form validate function for this handler.
   */
  public function settingsFormValidate(&$form, &$form_state);

  /**
   * Generates a settings form submit function for this handler.
   */
  public function settingsFormSubmit(&$form, &$form_state);

  /**
   * Image generation handler.
   */
  public function generateImage($object, $field, $instance, $bundle);
}

/**
 * An abstract implementation of DevelImagesProviderInterface.
 */
abstract class DevelImagesProviderBase implements DevelImagesProviderInterface {

  /**
   * The provider url.
   *
   * @var string
   */
  protected $provider_base_url;

  /**
   * Defined settings for the method.
   *
   * @var string
   */
  protected $settings;

  public function __construct($plugin) {
    $this->plugin = $plugin;
    $this->settings  = variable_get('devel_image_provider_settings_' . $this->plugin['name'], array());
  }

  public function availableMethods() {
    return drupal_map_assoc(array('curl', 'gd', 'file_get_contents'));
  }

  public function settingsForm() {
    $form['devel_image_provider_' . $this->plugin['name']] = array(
      '#type' => 'fieldset',
      '#title' => t('Provider settings'),
      '#states' => array(
        'visible' => array(
          ':input[name="available_providers[devel_image_provider_method_selected]"]' => array('value' => $this->plugin['name']),
        ),
      ),
    );

    $methods = $this->availableMethods();
    if (!empty($methods)) {
      $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_get_method'] = array(
        '#type' => 'radios',
        '#title' => t('Method to get files'),
        '#default_value' => isset($this->settings['devel_image_provider_get_method']) ? $this->settings['devel_image_provider_get_method'] : 'file_get_contents',
        '#options' => $this->availableMethods(),
      );
    }
    $form['devel_image_provider_' . $this->plugin['name']]['devel_image_provider_gray'] = array(
      '#type' => 'checkbox',
      '#title' => t('Gray version'),
      '#default_value' => isset($this->settings['devel_image_provider_gray']) ? $this->settings['devel_image_provider_gray'] : NULL,
    );

    return $form;
  }

  public function settingsFormValidate(&$form, &$form_state) {}

  public function settingsFormSubmit(&$form, &$form_state) {
    $values = $form_state['values']['config_providers']['devel_image_provider_' . $this->plugin['name']];
    variable_set('devel_image_provider_settings_' . $this->plugin['name'], $values);
  }

  public function generateImage($object, $field, $instance, $bundle) {}

}
