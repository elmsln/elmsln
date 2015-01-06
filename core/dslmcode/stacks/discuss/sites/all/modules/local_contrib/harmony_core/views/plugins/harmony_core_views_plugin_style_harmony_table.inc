<?php

/**
 * @file
 * Contains the harmony_table style plugin.
 */

/**
 * Style plugin to render each item as a row in a responsive table.
 *
 * @ingroup views_style_plugins
 */
class harmony_core_views_plugin_style_harmony_table extends views_plugin_style_table {

  /**
   * Render the given style, let table do near all of the work.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure your table settings') . '</div>',
      );
      return;
    }

    // Change the description text.
    $form['description_markup'] = array(
      '#markup' => '<div class="description form-item">' . t('Place fields into columns; you may combine multiple fields into the same column. If you do, the separator in the column specified will be used to separate the fields. Check the sortable box to make that column click sortable, and check the default sort radio to determine which column will be sorted by default, if any. You may control column order and field labels in the fields section. You can also set fields as "Meta" fields which means on mobile they will queue left aligned below other content.') . '</div>',
    );

    // We need to use our own theme function to add in a few extra headers.
    $form['#theme'] = 'harmony_core_views_style_plugin_harmony_table_ui';

    $columns = $this->sanitize_columns($this->options['columns']);

    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      // the $id of the column for dependency checking.
      $id = 'edit-style-options-columns-' . $safe;

      $form['info'][$field]['align']['#options'] = array(
        '' => t('None'),
        'text-left' => t('Left'),
        'text-center' => t('Center'),
        'text-right' => t('Right'),
      );
      $form['info'][$field]['cell_class'] = array(
        '#type' => 'textfield',
        '#size' => 10,
        '#default_value' => isset($this->options['info'][$field]['cell_class']) ? $this->options['info'][$field]['cell_class'] : '',
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['meta_field'] = array(
        '#type' => 'checkbox',
        '#default_value' => isset($this->options['info'][$field]['meta_field']) ? $this->options['info'][$field]['meta_field'] : FALSE,
        '#dependency' => array($id => array($field)),
      );
    }
  }
}
