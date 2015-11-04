<?php
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 *
 * @ingroup views_style_plugins
 */
class views_data_export_plugin_style_export_xml extends views_data_export_plugin_style_export {

  /**
   * Initialize a style plugin.
   */
  function init(&$view, &$display, $options = NULL) {
    // View is not set in option_definition(), so we fill defaults here if
    // options are empty.
    if (empty($options['root_node']) || empty($options['item_node'])) {
      $base_object_name = rtrim($view->base_table, 's');

      if (empty($options['root_node'])) {
        $options['root_node'] = $base_object_name . 's';
      }
      if (empty($options['item_node'])) {
        $options['item_node'] = $base_object_name;
      }
    }

    parent::init($view, $display, $options);
  }

  /**
   * Set options fields and default values.
   *
   * @return
   * An array of options information.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['transform'] = array(
      'default' => TRUE,
      'translatable' => FALSE,
    );
    $options['transform_type'] = array(
      'default' => 'dash',
      'translatable' => FALSE,
    );
    $options['root_node'] = array(
      'default' => '',
      'translatable' => FALSE,
    );
    $options['item_node'] = array(
      'default' => '',
      'translatable' => FALSE,
    );
    $options['no_entity_encode'] = array(
      'default' => array(),
      'translatable' => FALSE,
    );
    $options['cdata_wrapper'] = array(
      'default' => array(),
      'translatable' => FALSE,
    );

    return $options;
  }

  /**
   * Options form mini callback.
   *
   * @param $form
   * Form array to add additional fields to.
   * @param $form_state
   * State of the form.
   * @return
   * None.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['transform'] = array(
      '#type' => 'checkbox',
      '#title' => t('Transform spaces'),
      '#default_value' => $this->options['transform'],
      '#description' => t('Transform spaces to valid XML in field labels (spaces create invalid XML markup). Note that invalid XML tag characters will always be converted.'),
    );
    $form['transform_type'] = array(
      '#type' => 'select',
      '#title' => t('Transform type'),
      '#default_value' => $this->options['transform_type'],
      '#options' => array(
        'dash' => t('Dash'),
        'underline' => t('Underline'),
        'camel' => t('camelCase'),
        'pascal' => t('PascalCase'),
      ),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'edit-style-options-transform' => array(TRUE),
      ),
    );
    $form['root_node'] = array(
      '#type' => 'textfield',
      '#title' => t('Root node'),
      '#default_value' => $this->options['root_node'],
      '#description' => t('The XML tag for the root node.'),
    );
    $form['item_node'] = array(
      '#type' => 'textfield',
      '#title' => t('Item node'),
      '#default_value' => $this->options['item_node'],
      '#description' => t('The XML tag for an item node.'),
    );

    $field_labels = $this->display->handler->get_field_labels();

    if (!empty($field_labels)) {
      $options = $field_labels;
      if (empty($this->options['no_entity_encode'])) {
        $this->options['no_entity_encode'] = array();
      }

      $form['no_entity_encode'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Disable encoding of XML entities for these fields'),
        '#options' => $options,
        '#default_value' => $this->options['no_entity_encode'],
        '#description' => t('If checked field contents will be outputted '.
                            '<em>without encoding</em> of XML entities. This is '.
                            'useful when when used in conjunction with a field '.
                            'formatter that outputs properly formatted and '.
                            'encoded XML data.'),
      );

      if (empty($this->options['cdata_wrapper'])) {
        $this->options['cdata_wrapper'] = array();
      }

      $form['cdata_wrapper'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Fields value to wrapped using CDATA'),
        '#options' => $options,
        '#default_value' => $this->options['cdata_wrapper'],
        '#description' => t('If checked the fields content will be wrapped using the CDATA tag.'),
      );
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   *
   * @param $form
   * @param $form_state
   */
  function options_submit(&$form, &$form_state) {
    if (isset($form_state['values']['style_options']['no_entity_encode'])) {
      // Remove any options values set to 0
      $form_state['values']['style_options']['no_entity_encode'] = array_filter($form_state['values']['style_options']['no_entity_encode']);
    }
    if (isset($form_state['values']['style_options']['cdata_wrapper'])) {
      // Remove any options values set to 0
      $form_state['values']['style_options']['cdata_wrapper'] = array_filter($form_state['values']['style_options']['cdata_wrapper']);
    }
  }
}
