<?php

/**
 * @file
 * Contains the administrative functions of the print_pdf_dompdf sub-module.
 *
 * This file is included by the print_pdf_dompdf module, and includes the
 * settings form.
 *
 * @ingroup print
 */

/**
 * Form constructor for the dompdf options settings form.
 *
 * @ingroup forms
 */
function print_pdf_dompdf_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('dompdf options'),
  );

  $form['settings']['print_pdf_dompdf_unicode'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use dompdf's Unicode Mode"),
    '#default_value' => variable_get('print_pdf_dompdf_unicode', PRINT_PDF_DOMPDF_UNICODE_DEFAULT),
    '#description' => t("If enabled, dompdf's Unicode mode is used. If not, the module will attempt to convert some non-ASCII chars to ISO-8859-1."),
  );
  $form['settings']['print_pdf_dompdf_font_subsetting'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable font subsetting'),
    '#default_value' => variable_get('print_pdf_dompdf_font_subsetting', PRINT_PDF_DOMPDF_FONT_SUBSETTING_DEFAULT),
    '#description' => t('Only embed those font characters that are actually used.  This can generates smaller PDF files but may significantly slow down processing.'),
  );

  return system_settings_form($form);
}
