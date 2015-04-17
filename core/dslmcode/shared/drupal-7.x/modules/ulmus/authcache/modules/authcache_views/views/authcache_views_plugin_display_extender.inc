<?php
/**
 * @file
 * Defines views display extender plugin.
 */

// Adhere to Views coding style here.
// @ignore sniffer_namingconventions_validclassname_startwithcaptial:file
// @ignore sniffer_namingconventions_validfunctionname_scopenotlowercamel:file
// @ignore style_class_names:file
/**
 * Expose authcache settings to views_ui.
 *
 * @ingroup views_display_plugins
 */
class authcache_views_plugin_display_extender extends views_plugin_display_extender {
  /**
   * Provide a form to edit options for this plugin.
   */
  public function options_definition_alter(&$options) {
    // Keep this in sync with the default values given in
    // authcache_p13n_process_settings.
    $options['authcache'] = array(
      'default' => authcache_p13n_config_defaults(),
    );
  }

  /**
   * Provide the form to set new option.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    if ($form_state['section'] === 'authcache') {
      $form['#title'] .= t('Authcache settings');

      $defaults = $this->display->get_option('authcache');
      $form['authcache'] = array(
        '#type' => 'authcache_p13n_config',
        '#default_value' => $defaults,
        '#attached' => array(
          'js' => array(drupal_get_path('module', 'authcache_views') . '/authcache_views.admin.js'),
        ),
      );
    }
  }

  /**
   * Inserts the code into the view display.
   */
  public function options_submit(&$form, &$form_state) {
    if ($form_state['section'] === 'authcache') {
      $this->display->set_option('authcache', $form_state['values']['authcache']);
    }
  }

  /**
   * Summarizes new option.
   *
   * Lists the fields as either 'Yes' if there is text or 'None' otherwise and
   * categorizes the fields under the 'Other' category.
   */
  public function options_summary(&$categories, &$options) {
    $settings = $this->display->get_option('authcache');
    $status = $settings['status'] ? t('Enabled') : t('Disabled');
    $options['authcache'] = array(
      'category' => 'other',
      'title'    => t('Authcache'),
      'value'    => $status,
      'desc'     => t('Edit settings for personalized views.'),
    );
  }
}
