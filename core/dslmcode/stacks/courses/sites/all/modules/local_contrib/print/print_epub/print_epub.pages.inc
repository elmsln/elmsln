<?php

/**
 * @file
 * Generates the EPUB versions of the pages
 *
 * This file is included by the print_epub module and includes the
 * functions that interface with the EPUB generation packages.
 *
 * @ingroup print
 */

module_load_include('inc', 'print', 'print.pages');

/**
 * Generate a EPUB version of the printer-friendly page
 *
 * @see print_controller()
 * @see _print_epub_domepub()
 * @see _print_epub_tcepub()
 */
function print_epub_controller() {
  // Disable caching for generated EPUBs, as Drupal doesn't ouput the proper headers from the cache
  $GLOBALS['conf']['cache'] = FALSE;

  $args = func_get_args();
  $path = filter_xss(implode('/', $args));
  $cid = isset($_GET['comment']) ? (int)$_GET['comment'] : NULL;

  // Handle the query
  $query = $_GET;
  unset($query['q']);

  if (!empty($path)) {
    if ($alias = drupal_lookup_path('source', $path)) {
      // Alias
      $path_arr = explode('/', $alias);
      $node = node_load($path_arr[1]);
    }
    elseif (ctype_digit($args[0])) {
      // normal nid
      $node = node_load($args[0]);
    }

    $epub_filename = variable_get('print_epub_filename', PRINT_EPUB_FILENAME_DEFAULT);
    if (!empty($epub_filename) && !empty($node)) {
      $epub_filename = token_replace($epub_filename, array('node' => $node), array('clear' => TRUE));
    }
    else {
      $epub_filename = token_replace($epub_filename, array('site'), array('clear' => TRUE));
      if (empty($epub_filename)) {
        // If empty, use a fallback solution
        $epub_filename = str_replace('/', '_', $path);
      }
    }
  }
  else {
    $epub_filename = 'page';
  }

  if (function_exists('transliteration_clean_filename')) {
    $epub_filename = transliteration_clean_filename($epub_filename, language_default('language'));
  }

  drupal_alter('print_epub_filename', $epub_filename, $path);

  $epub = print_epub_generate_path($path, $query, $cid, $epub_filename . '.epub');
  if ($epub == NULL) {
    drupal_goto($path);
    exit;
  }

  $nodepath = (isset($node->nid)) ? 'node/' . $node->nid : drupal_get_normal_path($path);
  db_merge('print_epub_page_counter')
    ->key(array('path' => $nodepath))
    ->fields(array(
        'totalcount' => 1,
        'timestamp' => REQUEST_TIME,
    ))
    ->expression('totalcount', 'totalcount + 1')
    ->execute();

  drupal_exit();
}

/**
 * Gennerate a EPUB for a given Drupal path.
 *
 * @param string $path
 *   path of the page to convert to EPUB
 * @param array $query
 *   (optional) array of key/value pairs as used in the url() function for the
 *   query
 * @param int $cid
 *   (optional) comment ID of the comment to render.
 * @param string $epub_filename
 *   (optional) filename of the generated EPUB
 * @param string $view_mode
 *   (optional) view mode to be used when rendering the content
 *
 * @return
 *   generated EPUB page, or NULL in case of error
 *
 * @see print_epub_controller()
 */
function print_epub_generate_path($path, $query = NULL, $cid = NULL, $epub_filename = NULL, $view_mode = PRINT_VIEW_MODE) {
  global $base_url;

  $link = print_epub_print_link();
  $node = print_controller($path, $link['format'], $cid, $view_mode);
  if ($node) {
    $html = theme('print', array('node' => $node, 'query' => $query, 'expand_css' => TRUE, 'format' => $link['format']));

    $meta = array(
      'node' => $node,
      'url' => url(drupal_get_path_alias(empty($node->nid) ? $node->path : "node/$node->nid"), array('absolute' => TRUE)),
    );
    if (isset($node->name)) $meta['name'] = $node->name;
    if (isset($node->title)) $meta['title'] = $node->title;

    return print_epub_generate_html($html, $meta, $epub_filename);
  }
  else {
    return NULL;
  }
}
