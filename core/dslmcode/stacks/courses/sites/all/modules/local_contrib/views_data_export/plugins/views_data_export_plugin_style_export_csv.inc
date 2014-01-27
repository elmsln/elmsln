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
class views_data_export_plugin_style_export_csv extends views_data_export_plugin_style_export {

  /**
   * Set options fields and default values.
   *
   * @return
   * An array of options information.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['separator'] = array(
      'default' => ',',
      'translatable' => TRUE,
    );
    $options['quote'] = array(
      'default' => TRUE,
      'translatable' => TRUE,
    );
    $options['trim'] = array(
      'default' => FALSE,
      'translatable' => FALSE,
    );
    $options['replace_newlines'] = array(
      'default' => FALSE,
      'translatable' => FALSE,
    );
    $options['newline_replacement'] = array(
      'default' => ', ',
      'translatable' => FALSE,
    );
    $options['header'] = array(
      'default' => TRUE,
      'translatable' => FALSE,
    );
    $options['encoding'] = array(
      'default' => '',
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

    $form['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => !empty($this->options['separator']) ? $this->options['separator'] : ',',
      '#description' => t('This is the separator that is used to separate fields. CSV implies comma separated fields so this should not be changed unless you have specific requirements'),
    );
    $form['quote'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['quote']),
      '#title' => t('Quote values. Useful for output that might contain your separator as part of one of the values.'),
    );
    $form['trim'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['trim']),
      '#title' => t('Trim whitespace from rendered fields. Can be useful for some themes where output results in extra newlines.'),
    );
    $form['replace_newlines'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['replace_newlines']),
      '#title' => t('Replace newlines in rendered fields.'),
    );
    $form['newline_replacement'] = array(
      '#prefix' => '<div><div id="edit-options-newline-replacement">',
      '#suffix' => '</div></div>',
      '#type' => 'textfield',
      '#title' => t('Replacement'),
      '#default_value' => $this->options['newline_replacement'],
      '#process' => array('form_process_checkboxes', 'ctools_dependent_process'),
      '#dependency' => array('edit-style-options-replace-newlines' => array(TRUE)),
    );
    $form['header'] = array(
      '#type' => 'checkbox',
      '#title' => t('Make first row a list of column headers.'),
      '#default_value' => !empty($this->options['header']),
    );
    $form['encoding'] = array(
      '#type' => 'select',
      '#default_value' => !empty($this->options['encoding']) ? $this->options['encoding'] : '',
      '#title' => t('Character encoding conversion'),
      '#options' => array (
        '' => t('No conversion'),
        'ASCII' => t('ASCII'),
      ),
      '#description' => t('Optionally specify a character conversion that some CSV file readers need. Note, using an external tool is always preferred and you should only use this option as a last resort. This feature requires the "iconv" PHP extension.'),
    );
  }
}
