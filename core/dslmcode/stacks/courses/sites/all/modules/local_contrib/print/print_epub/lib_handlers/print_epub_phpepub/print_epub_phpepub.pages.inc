<?php

/**
 * @file
 * Generates the EPUB version using PHPePub
 *
 * This file is included by the print_epub_phpepub module and includes the
 * functions that interface with the PHPePub library
 *
 * @ingroup print
 */

/**
 * Implements hook_print_epub_generate().
 */
function print_epub_phpepub_print_epub_generate($html, $meta, $filename = NULL) {
  global $language, $base_url;

  module_load_include('inc', 'print', 'includes/print');

  $epub_tool = explode('|', variable_get('print_epub_epub_tool', PRINT_EPUB_EPUB_TOOL_DEFAULT));
  $images_via_file = variable_get('print_epub_images_via_file', PRINT_EPUB_IMAGES_VIA_FILE_DEFAULT);

  require_once(DRUPAL_ROOT . '/' . $epub_tool[1]);

  // Try to use local file access for image files
  $html = _print_access_images_via_file($html, $images_via_file);

  // set document information
  $epub = new EPub();

  $epub->setTitle(html_entity_decode($meta['title'], ENT_QUOTES, 'UTF-8'));
  $epub->setIdentifier($meta['url'], EPub::IDENTIFIER_URI);
  $epub->setLanguage($language->language);
  if (isset($meta['name'])) {
    $epub->setAuthor(strip_tags($meta['name']), strip_tags($meta['name']));
  }
  $epub->setPublisher(variable_get('site_name', 'Drupal'), $base_url);
  $epub->setSourceURL($meta['url']);

  @$epub->addChapter("Chapter", "epub.html", $html, FALSE);

  $epub->finalize(); // Finalize the book, and build the archive.

  // Close and output EPUB document
  $epub->sendBook(empty($filename) ? 'page' : $filename);
  return TRUE;
}
