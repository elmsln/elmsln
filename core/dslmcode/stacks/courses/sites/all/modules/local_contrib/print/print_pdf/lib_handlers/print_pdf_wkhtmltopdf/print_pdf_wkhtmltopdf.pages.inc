<?php

/**
 * @file
 * Generates the PDF version using wkhtmltopdf.
 *
 * This file is included by the print_pdf_wkhtmltopdf module and includes the
 * functions that interface with the wkhtmltopdf library.
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
  $wkhtmltopdf_options = variable_get('print_pdf_wkhtmltopdf_options', PRINT_PDF_WKHTMLTOPDF_OPTIONS);

  $dpi = 96;

  if (!empty($wkhtmltopdf_options) && isset($meta['node'])) {
    $wkhtmltopdf_options = token_replace($wkhtmltopdf_options, array('node' => $meta['node']), array('clear' => TRUE));
  }

  // Build array of single quoted parts, and the same escaped.
  preg_match_all("!'.+?'!", $wkhtmltopdf_options, $matches);
  $quoted = array();
  foreach ($matches[0] as $match) {
    $quoted[escapeshellcmd($match)] = $match;
  }

  // Prevent options that could result in execution of arbitrary commands.
  $wkhtmltopdf_options = escapeshellcmd($wkhtmltopdf_options);

  // Replace sections that were single quoted with original content.
  foreach ($quoted as $search => $replace) {
    $wkhtmltopdf_options = str_replace($search, $replace, $wkhtmltopdf_options);
  }

  $version = print_pdf_wkhtmltopdf_pdf_tool_version($pdf_tool[1], FALSE);

  // 0.10.0 beta2 identifies itself as 0.9.9.
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

  // Use basic http authentication to fetch included CSS, etc.
  if (isset($_SERVER['PHP_AUTH_USER']) && isset($_SERVER['PHP_AUTH_PW'])) {
    $wkhtmltopdf_options .= ' --username ' . escapeshellarg($_SERVER['PHP_AUTH_USER']) . ' --password ' . escapeshellarg($_SERVER['PHP_AUTH_PW']);
  }

  $use_input_file = variable_get('print_pdf_wkhtmltopdf_use_input_file', PRINT_PDF_WKHTMLTOPDF_USE_INPUT_FILE_DEFAULT);
  if ($use_input_file) {
    $temp_html = file_unmanaged_save_data($html, drupal_tempnam('temporary://', 'c_html_') . '.html', FILE_EXISTS_RENAME);
    if ($temp_html === FALSE) {
      watchdog('print_pdf', 'wkhtmltopdf: could not create temporary html file: %file', array('%file' => $temp_html));
      drupal_goto($meta['url']);
      return NULL;
    }
    $html_input_parameter = drupal_realpath($temp_html);
  }
  else {
    $temp_html = '';
    $html_input_parameter = '-';
  }

  $descriptor = array(
    0 => array('pipe', 'r'),
    1 => array('pipe', 'w'),
    2 => array('pipe', 'a'),
  );
  $cmd = '"' . realpath($pdf_tool[1]) . "\" -q --page-size $paper_size --orientation $page_orientation --dpi $dpi $wkhtmltopdf_options $html_input_parameter -";

  $process = proc_open($cmd, $descriptor, $pipes, NULL, NULL);

  if (is_resource($process)) {
    if (!$use_input_file) {
      fwrite($pipes[0], $html);
      fclose($pipes[0]);
    }

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
      watchdog('print_pdf', 'wkhtmltopdf [%cmd] (returned %ret): %error',
        array('%cmd' => $cmd, '%ret' => $retval, '%error' => $error));
    }
  }
  if ($use_input_file) {
    file_unmanaged_delete($temp_html);
  }

  if (!empty($pdf)) {
    // Remove anything before actual PDF content.
    $pdf = substr($pdf, strpos($pdf, '%PDF-'));

    return $pdf;
  }
  else {
    drupal_set_message(t('Unable to generate PDF file.'), 'error');
    drupal_goto($meta['url']);
    return NULL;
  }
}
