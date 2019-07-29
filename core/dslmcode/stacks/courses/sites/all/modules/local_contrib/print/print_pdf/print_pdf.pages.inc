<?php

/**
 * @file
 * Generates the PDF versions of the pages.
 *
 * This file is included by the print_pdf module and includes the
 * functions that interface with the PDF generation packages.
 *
 * @ingroup print
 */

module_load_include('inc', 'print', 'print.pages');

/**
 * Generate a PDF version of the printer-friendly page.
 *
 * @see print_controller()
 * @see _print_pdf_dompdf()
 * @see _print_pdf_tcpdf()
 */
function print_pdf_controller() {
  // Disable caching for generated PDFs, as Drupal doesn't output the proper
  // headers from the cache.
  $GLOBALS['conf']['cache'] = FALSE;

  $args = func_get_args();
  $path = filter_xss(implode('/', $args));
  $cid = isset($_GET['comment']) ? (int) $_GET['comment'] : NULL;

  // Handle the query.
  $query = $_GET;
  unset($query['q']);

  $node = NULL;
  if (!empty($path)) {
    if ($alias = drupal_lookup_path('source', $path)) {
      // Alias.
      $path_arr = explode('/', $alias);
      $node = node_load($path_arr[1]);
    }
    elseif (ctype_digit($args[0])) {
      // Normal nid.
      $node = node_load($args[0]);
    }

    $pdf_filename = variable_get('print_pdf_filename', PRINT_PDF_FILENAME_DEFAULT);
    if (!empty($pdf_filename) && !empty($node)) {
      $pdf_filename = token_replace($pdf_filename, array('node' => $node), array('clear' => TRUE));
    }
    else {
      $pdf_filename = token_replace($pdf_filename, array('site'), array('clear' => TRUE));
      if (empty($pdf_filename)) {
        // If empty, use a fallback solution.
        $pdf_filename = str_replace('/', '_', $path);
      }
    }
  }
  else {
    $pdf_filename = 'page';
  }

  if (function_exists('transliteration_clean_filename')) {
    $pdf_filename = transliteration_clean_filename($pdf_filename, language_default('language'));
  }

  drupal_alter('print_pdf_filename', $pdf_filename, $path);

  $pdf = print_pdf_generate_path($path, $query, $cid, $pdf_filename . '.pdf');
  if ($pdf == NULL) {
    drupal_goto($path);
    exit;
  }

  $nodepath = (isset($node->nid)) ? 'node/' . $node->nid : drupal_get_normal_path($path);
  db_merge('print_pdf_page_counter')
    ->key(array('path' => substr($nodepath, 0, 255)))
    ->fields(array(
      'totalcount' => 1,
      'timestamp' => REQUEST_TIME,
    ))
    ->expression('totalcount', 'totalcount + 1')
    ->execute();

  drupal_exit();
}

/**
 * Gennerate a PDF for a given Drupal path.
 *
 * @param string $path
 *   path of the page to convert to PDF.
 * @param array $query
 *   (Optional) array of key/value pairs as used in the url() function for the
 *   query.
 * @param int $cid
 *   (Optional) comment ID of the comment to render.
 * @param string $pdf_filename
 *   (Optional) filename of the generated PDF.
 * @param string $view_mode
 *   (Optional) view mode to be used when rendering the content.
 *
 * @return string|null
 *   generated PDF page, or NULL in case of error
 *
 * @see print_pdf_controller()
 */
function print_pdf_generate_path($path, $query = NULL, $cid = NULL, $pdf_filename = NULL, $view_mode = PRINT_VIEW_MODE) {
  global $base_url;

  $link = print_pdf_print_link();
  $node = print_controller($path, $link['format'], $cid, $view_mode);
  if ($node) {
    // Call the tool's hook_pdf_tool_info(), to see if CSS must be expanded.
    $pdf_tool = explode('|', variable_get('print_pdf_pdf_tool', PRINT_PDF_PDF_TOOL_DEFAULT));
    $cache_enabled = variable_get('print_pdf_cache_enabled', PRINT_PDF_CACHE_ENABLED_DEFAULT);

    $function = $pdf_tool[0] . '_pdf_tool_info';
    $info = function_exists($function) ? $function() : array();
    $expand = isset($info['expand_css']) ? $info['expand_css'] : FALSE;

    $html = theme('print', array(
      'node' => $node,
      'query' => $query,
      'expand_css' => $expand,
      'format' => $link['format'],
    ));

    // Img elements must be set to absolute.
    $pattern = '!<(img\s[^>]*?)>!is';
    $html = preg_replace_callback($pattern, '_print_rewrite_urls', $html);

    // Convert the a href elements, to make sure no relative links remain.
    $pattern = '!<(a\s[^>]*?)>!is';
    $html = preg_replace_callback($pattern, '_print_rewrite_urls', $html);
    // And make anchor links relative again, to permit in-PDF navigation.
    $html = preg_replace("!${base_url}/" . $link['path'] . '/.*?#!', '#', $html);

    $meta = array(
      'node' => $node,
      'url' => url(drupal_get_path_alias(empty($node->nid) ? $node->path : "node/$node->nid"), array('absolute' => TRUE)),
    );
    if (isset($node->name)) {
      $meta['name'] = $node->name;
    }
    if (isset($node->title)) {
      $meta['title'] = $node->title;
    }

    $paper_size = isset($node->print_pdf_size) ? $node->print_pdf_size : NULL;
    $page_orientation = isset($node->print_pdf_orientation) ? $node->print_pdf_orientation : NULL;

    $pdf = '';
    $cachemiss = FALSE;
    $cachefile = '';
    if ($cache_enabled && isset($node->nid)) {
      // See if the file exists in the cache.
      $cachefile = drupal_realpath(print_pdf_cache_dir()) . '/' . $node->nid . '.pdf';
      if (is_readable($cachefile)) {
        // Get the PDF content from the cached file.
        $pdf = file_get_contents($cachefile);
        if ($pdf === FALSE) {
          watchdog('print_pdf', 'Failed to read from cached file %file', array('%file' => $cachefile), WATCHDOG_ERROR);
        }
      }
      else {
        $cachemiss = TRUE;
      }
    }

    // If cache is off or file is not cached, generate one from scratch.
    if (empty($pdf)) {
      $pdf = print_pdf_generate_html($html, $meta, NULL, $paper_size, $page_orientation);
    }

    if (!empty($pdf)) {
      // A PDF was created, save it to cache if configured.
      if ($cachemiss) {
        if (file_unmanaged_save_data($pdf, $cachefile, FILE_EXISTS_REPLACE) == FALSE) {
          watchdog('print_pdf', 'Failed to write to "%f".', array('%f' => $cachefile), WATCHDOG_ERROR);
        }
      }

      return $pdf_filename ? print_pdf_dispose_content($pdf, $pdf_filename) : $pdf;
    }
  }
  return NULL;
}
