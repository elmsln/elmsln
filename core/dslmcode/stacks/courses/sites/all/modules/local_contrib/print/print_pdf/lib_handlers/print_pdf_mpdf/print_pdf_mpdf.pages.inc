<?php

/**
 * @file
 * Generates the PDF version using mPDF
 *
 * This file is included by the print_pdf_mpdf module and includes the
 * functions that interface with the mPDF library
 *
 * @ingroup print
 */

/**
 * Implements hook_print_pdf_generate().
 */
function print_pdf_mpdf_print_pdf_generate($html, $meta, $paper_size = NULL, $page_orientation = NULL) {
  module_load_include('inc', 'print', 'includes/print');

  $pdf_tool = explode('|', variable_get('print_pdf_pdf_tool', PRINT_PDF_PDF_TOOL_DEFAULT));
  if (empty($paper_size)) {
    $paper_size = variable_get('print_pdf_paper_size', PRINT_PDF_PAPER_SIZE_DEFAULT);
  }
  if (empty($page_orientation)) {
    $page_orientation = variable_get('print_pdf_page_orientation', PRINT_PDF_PAGE_ORIENTATION_DEFAULT);
  }
  $content_disposition = variable_get('print_pdf_content_disposition', PRINT_PDF_CONTENT_DISPOSITION_DEFAULT);
  $images_via_file = variable_get('print_pdf_images_via_file', PRINT_PDF_IMAGES_VIA_FILE_DEFAULT);

  if (variable_get('print_pdf_autoconfig', PRINT_PDF_AUTOCONFIG_DEFAULT)) {
    if (!defined('_MPDF_TTFONTDATAPATH')) define('_MPDF_TTFONTDATAPATH', drupal_realpath('public://print_pdf/print_pdf_mpdf/ttfontdata/'));
    if (!defined('_MPDF_TEMP_PATH')) define('_MPDF_TEMP_PATH', drupal_realpath('public://print_pdf/print_pdf_mpdf/tmp/'));
  }

  require_once(DRUPAL_ROOT . '/' . $pdf_tool[1]);

  $format = ($page_orientation == "landscape") ? $paper_size . "-L" : $paper_size;

  // Try to use local file access for image files
  $html = _print_access_images_via_file($html, $images_via_file);

  // set document information
  $mpdf = new mPDF('UTF-8', $format);

  $mpdf->SetAuthor(strip_tags($meta['name']));
  $mpdf->SetCreator(variable_get('site_name', 'Drupal'));
  // Pulled from the HTML meta data
  // $mpdf->SetTitle(html_entity_decode($meta['title'], ENT_QUOTES, 'UTF-8'));

//  $keys = implode(' ', explode("\n", trim(strip_tags($print['taxonomy']))));
//  $mpdf->SetKeywords($keys);

  // Encrypt the file and grant permissions to the user to copy and print
  // No password is required to open the document
  // Owner has full rights using the password "MyPassword"
  // $mpdf->SetProtection(array('copy', 'print'), '', 'MyPassword');
  // $mpdf->SetProtection(array('copy', 'print', 'print-highres'), '', '');
  drupal_alter('print_pdf_mpdf', $mpdf, $html, $meta);

  $mpdf->WriteHTML($html);

  // try to recover from any warning/error
  ob_clean();

  return $mpdf->Output('', 'S');
}
