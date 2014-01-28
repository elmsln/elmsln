<?php
/**
 * @file
 * Copied from the table style plugin and from views_calc module.
 */

/**
 * Style plugin to render each item as a row in a table.
 *
 * @ingroup views_style_plugins
 */
class views_field_calc_table extends views_plugin_style_table {
  /**
   * Define default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['detailed_values'] = array('default' => 0);
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['#theme'] = 'views_field_calc_ui_table';

    $form['detailed_values'] = array(
      '#title' => t('Show details'),
      '#type' => 'select',
      '#options' => array(
        0 => t('Yes'),
        1 => t('No'),
      ),
      '#default_value' => $this->options['detailed_values'],
      '#description' => t("Select 'Yes' to show detailed values followed by column calculations, 'No' to surpress details and show only calculated column totals."),
    );

    $handlers = $this->display->handler->get_handlers('field');
    $columns = $this->sanitize_columns($this->options['columns']);

    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      $id = 'edit-style-options-columns-' . $safe;
      $form['info'][$field]['has_calc'] = array(
        '#type' => 'checkbox',
        '#title' => t('Display calculation'),
        '#default_value' => isset($this->options['info'][$field]['has_calc']) ? $this->options['info'][$field]['has_calc'] : 0,
      );

      $options = _views_field_calc_calc_options();
      $form['info'][$field]['calc'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($this->options['info'][$field]['calc']) ? $this->options['info'][$field]['calc'] : array(),
        '#states' => array(
          'visible' => array(':checkbox[name="style_options[info][' . $field . '][has_calc]"]' => array('checked' => TRUE), ), // condition
        ),
        '#multiple' => TRUE,
      );
    }
  }
}
