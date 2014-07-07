<?php

/**
 * @file
 * Contains the administrative functions of the print_pdf_wkhtmltopdf module.
 *
 * This file is included by the print_pdf_wkhtmltopdf module, and includes the
 * settings form.
 *
 * @ingroup print
 */

/**
 * Form constructor for the wkhtmltopdf options settings form.
 *
 * @ingroup forms
 */
function print_pdf_wkhtmltopdf_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('wkhtmltopdf options'),
  );

  $form['settings']['print_pdf_wkhtmltopdf_options'] = array(
    '#type' => 'textfield',
    '#title' => t('wkhtmltopdf options'),
    '#size' => 60,
    '#maxlength' => 500,
    '#default_value' => variable_get('print_pdf_wkhtmltopdf_options', PRINT_PDF_WKHTMLTOPDF_OPTIONS),
    '#description' => t('(wkhtmltopdf only) Set any additional options to be passed to the wkhtmltopdf executable. Tokens may be used in these options (see list below).'),
  );

  if (module_exists('token')) {
    $form['settings']['print_pdf_filename_patterns'] = array(
      '#type' => 'fieldset',
      '#title' => t('Replacement patterns'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['settings']['print_pdf_filename_patterns']['descriptions'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node'),
    );
  }

  return system_settings_form($form);
}
