<?php
/**
 * @file
 * Definition of cis_connector_views_plugin_display_extender.
 */

/**
 * Adds the CIS connector options to the display
 *
 * @ingroup views_display_plugins
 * @ignore style_class_names*/
class cis_connector_views_plugin_display_extender extends views_plugin_display_extender {
  function add_signature(&$view) {}
  /**
   * Provide a form to edit options for this plugin.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['cis_bucket'] = array('default' => '-none-');
    $options['cis_instance'] = array('default' => TRUE);
    return $options;
  }
  /**
   * Alter the options to allow for defaults.
   */
  function options_definition_alter(&$options) {
    $options['cis_bucket'] = array('default' => '-none-');
    $options['cis_instance'] = array('default' => TRUE);
  }
  /**
   * Provide a form to edit options for this plugin.
   */
  function options_form(&$form, &$form_state) {
    if ($form['#section'] == 'page-cis_connector') {
      $registry = _cis_connector_build_registry();
      $options = array('-none-' => '-none-');
      foreach ($registry as $key => $option) {
        // only display things we can connect to via backend calls
        if (isset($option['service_address'])) {
          $options[$key] = $key . ' (' . $option['address'] . ')';
        }
      }
      // allow for selection of the bucket to connect to
      $form['cis_bucket'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => t('Connector bucket'),
        '#description' => t('Which service instance should this view connect to'),
        '#weight' => 0,
        '#default_value' => $this->display->get_option('cis_bucket'),
      );
      // allow for designation of a related instance or if this is a single service
      $form['cis_instance'] = array(
        '#type' => 'checkbox',
        '#title' => t('Instance'),
        '#description' => t('Is this an instance of a service or a central service?'),
        '#weight' => 1,
        '#default_value' => $this->display->get_option('cis_instance'),
      );
    }
  }

  /**
   * Handle any special handling on the validate form.
   */
  function options_submit(&$form, &$form_state) {
    if (isset($form_state['values']['cis_bucket'])) {
      $this->display->set_option('cis_bucket', $form_state['values']['cis_bucket']);
      $this->display->set_option('cis_instance', $form_state['values']['cis_instance']);
    }
  }

  /**
   * Provide the default summary for options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    if ($this->view->base_table == 'xml') {
      $bucket = check_plain(trim($this->display->get_option('cis_bucket')));
      $options['cis_connector'] = array(
        'category' => 'other',
        'title' => t('CIS connector'),
        'value' => $bucket,
        'desc' => t('CIS connector settings to modify request address dynamically.'),
      );
    }
  }
  /**
   * Inject anything into the query that the display_extender handler needs.
   */
  function query() {
    if ($this->view->base_table == 'xml') {
      $options = $this->view->display_handler->options;
      $this->view->query->options['cis_bucket'] = $options['cis_bucket'];
      $this->view->query->options['cis_instance'] = $options['cis_instance'];
    }
  }
}
