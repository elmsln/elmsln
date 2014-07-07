<?php

/**
 * @file
 * Contains the administrative functions of the print_pdf_tcpdf sub-module.
 *
 * This file is included by the print_pdf_tcpdf module, and includes the
 * settings form.
 *
 * @ingroup print
 */

/**
 * Form constructor for the TCPDF options settings form.
 *
 * @ingroup forms
 */
function print_pdf_tcpdf_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('TCPDF options'),
  );

  $form['settings']['print_pdf_font_family'] = array(
    '#type' => 'textfield',
    '#title' => t('Font family'),
    '#default_value' => variable_get('print_pdf_font_family', PRINT_PDF_TCPDF_FONT_FAMILY_DEFAULT),
    '#size' => 60,
    '#maxlength' => 250,
    '#description' => t('Set the font family to be used. Examples: %examples.', array('%examples' => 'helvetica, times, courier, dejavusans, dejavuserif, freesans, freeserif, freemono')) . '<br />' .
                      t("CAUTION: TCPDF embeds the complete font in the generated PDF. If you're not using Unicode, then helvetica or times are safe choices that will keep the PDF small. Unicode fonts can increase the size of the PDF to the 1MB region."),
  );
  $form['settings']['print_pdf_font_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Font size'),
    '#default_value' => variable_get('print_pdf_font_size', PRINT_PDF_TCPDF_FONT_SIZE_DEFAULT),
    '#size' => 2,
    '#maxlength' => 3,
    '#description' => t('Set the font size to be used for normal text. This is the base value for the scaling applied to other text styles.'),
  );
  $form['settings']['print_pdf_font_subsetting'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable font subsetting'),
    '#default_value' => variable_get('print_pdf_font_subsetting', PRINT_PDF_TCPDF_FONT_SUBSETTING_DEFAULT),
    '#description' => t('Only embed those font characters that are actually used.  This can generates smaller PDF files but may significantly slow down processing.'),
  );

  $form['#validate'][] = '_print_pdf_tcpdf_settings_validate';

  return system_settings_form($form);
}

/**
 * Form validation handler for print_pdf_tcpdf_settings().
 *
 * @see print_pdf_tcpdf_settings()
 * @ingroup forms
 */
function _print_pdf_tcpdf_settings_validate($form, &$form_state) {
  if ($form_state['values']['print_pdf_font_size'] < 1) {
    form_set_error('print_pdf_font_size', t("Font size must be at least 1."));
  }
}
