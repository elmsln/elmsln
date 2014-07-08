<?php

/**
 * @file
 * Generates the PDF version using wkhtmltopdf
 *
 * This file is included by the print_pdf_wkhtmltopdf module and includes the
 * functions that interface with the wkhtmltopdf library
 *
 * @ingroup print
 */

/**
 * Implements hook_print_pdf_generate().
 */
function print_pdf_wkhtmltopdf_print_pdf_generate($html, $meta, $paper_size = NULL, $page_orientation = NULL) {
  $pdf_tool = explode('|', variable_get('print_pdf_pdf_tool', PRINT_PDF_PDF_TOOL_DEFAULT));
  if (empty($paper_size)) {
    $paper_size = variable_get('print_pdf_paper_size', PRINT_PDF_PAPER_SIZE_DEFAULT);
  }
  if (empty($page_orientation)) {
    $page_orientation = variable_get('print_pdf_page_orientation', PRINT_PDF_PAGE_ORIENTATION_DEFAULT);
  }
  $content_disposition = variable_get('print_pdf_content_disposition', PRINT_PDF_CONTENT_DISPOSITION_DEFAULT);
  $wkhtmltopdf_options = variable_get('print_pdf_wkhtmltopdf_options', PRINT_PDF_WKHTMLTOPDF_OPTIONS);

  $dpi = 96;

  if (!empty($wkhtmltopdf_options) && isset($meta['node'])) {
    $wkhtmltopdf_options = token_replace($wkhtmltopdf_options, array('node' => $meta['node']), array('clear' => TRUE));
  }

  $version = print_pdf_wkhtmltopdf_pdf_tool_version($pdf_tool[1]);

  // 0.10.0 beta2 identifies itself as 0.9.9
  if (version_compare($version, '0.9.9', '>=')) {
    $wkhtmltopdf_options = '--disable-local-file-access ' . $wkhtmltopdf_options;
  }
  elseif (version_compare($version, '0.9.6', '>=')) {
    $wkhtmltopdf_options = '--disallow-local-file-access ' . $wkhtmltopdf_options;
  }
  else {
    drupal_goto($meta['url']);
    exit;
  }

  // use basic http authentication to fetch included CSS, etc
  if (isset($_SERVER['PHP_AUTH_USER']) && isset($_SERVER['PHP_AUTH_PW'])) {
    $wkhtmltopdf_options .= ' --username ' . check_plain($_SERVER['PHP_AUTH_USER']) . ' --password ' . check_plain($_SERVER['PHP_AUTH_PW']);
  }

  $descriptor = array(0 => array('pipe', 'r'), 1 => array('pipe', 'w'), 2 => array('pipe', 'a'));
  $cmd = '"' . realpath($pdf_tool[1]) . "\" --page-size $paper_size --orientation $page_orientation --dpi $dpi $wkhtmltopdf_options - -";

  $process = proc_open($cmd, $descriptor, $pipes, NULL, NULL);

  if (is_resource($process)) {
    fwrite($pipes[0], $html);
    fclose($pipes[0]);

    $pdf = stream_get_contents($pipes[1]);
    fclose($pipes[1]);

    stream_set_blocking($pipes[2], 0);
    $error = stream_get_contents($pipes[2]);
    fclose($pipes[2]);

    $retval = proc_close($process);
    if (!empty($error) || ($retval != 0)) {
      if (empty($error)) {
        $error = 'No stderr output available.';
      }
      watchdog('print_pdf', 'wkhtmltopdf [%cmd] (returned %ret): %error', array('%cmd' => $cmd, '%ret' => $retval, '%error' => $error));
    }
  }

  if (!empty($pdf)) {
    return $pdf;
  }
  else {
    drupal_set_message(t('Unable to generate PDF file.'), 'error');
    drupal_goto($meta['url']);
    return NULL;
  }
}
