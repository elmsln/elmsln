<?php

/**
 * @file
 * Contains the table style plugin.
 */

/**
 * Style plugin to render each item as a row in a table.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_table_responsive extends views_plugin_style_table {

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    foreach (element_children($form['info']) as $field) {
      $form['info'][$field]['responsive'] = array(
        '#type' => 'select',
        '#default_value' => isset($this->options['info'][$field]['responsive']) ? $this->options['info'][$field]['responsive'] : '',
        '#options' => array('' => t('None'), RESPONSIVE_PRIORITY_MEDIUM => t('Medium'), RESPONSIVE_PRIORITY_LOW => t('Low')),
        '#dependency' => $form['info'][$field]['empty_column']['#dependency'],
      );
    }
  }
}
