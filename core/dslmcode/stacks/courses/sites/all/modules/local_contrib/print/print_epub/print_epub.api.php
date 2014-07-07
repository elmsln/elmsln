<?php

/**
 * @file
 * Hooks provided by the EPUB version module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Generate a EPUB version of the provided HTML.
 *
 * @param string $html
 *   HTML content of the EPUB
 * @param array $meta
 *   Meta information to be used in the EPUB
 *   - url: original URL
 *   - name: author's name
 *   - title: Page title
 *   - node: node object
 * @param string $filename
 *   (optional) Filename of the generated EPUB
 *
 * @return
 *   generated EPUB page, or NULL in case of error
 *
 * @see print_epub_controller_html()
 * @ingroup print_hooks
 */
function hook_print_epub_generate($html, $meta, $filename = NULL) {
  $epub = new EPUB();
  $epub->writeHTML($html);
  if ($filename) {
    $epub->Output($filename);
    return TRUE;
  }
  else {
    return $epub->Output();
  }
}

/**
 * Alters the list of available EPUB libraries.
 *
 * During the configuration of the EPUB library to be used, the module needs
 * to discover and display the available libraries. This function should use
 * the internal _print_scan_libs() function which will scan both the module
 * and the libraries directory in search of the unique file pattern that can
 * be used to identify the library location.
 *
 * @param array $epub_tools
 *   An associative array using as key the format 'module|path', and as value
 *   a string describing the discovered library, where:
 *   - module: the machine name of the module that handles this library.
 *   - path: the path where the library is installed, relative to DRUPAL_ROOT.
 *     If the recommended path is used, it begins with sites/all/libraries.
 *   As a recommendation, the value should contain in parantheses the path
 *   where the library was found, to allow the user to distinguish between
 *   multiple install paths of the same library version.
 *
 * @ingroup print_hooks
 */
function hook_print_epub_available_libs_alter(&$epub_tools) {
  module_load_include('inc', 'print', 'includes/print');
  $tools = _print_scan_libs('foo', '!^foo.php$!');

  foreach ($tools as $tool) {
    $epub_tools['print_epub_foo|' . $tool] = 'foo (' . dirname($tool) . ')';
  }
}

/**
 * Alters the EPUB filename.
 *
 * Changes the value of the EPUB filename variable, just before it is used to
 * create the file. When altering the variable, do not suffix it with the
 * '.epub' extension, as the module will do that automatically.
 *
 * @param string $epub_filename
 *   current value of the epub_filename variable, after processing tokens and
 *   any transliteration steps.
 * @param string $path
 *   original alias/system path of the page being converted to EPUB.
 *
 * @ingroup print_hooks
 */
function hook_print_epub_filename_alter(&$epub_filename, &$path) {
  $epub_filename = 'foo';
}

/**
 * @} End of "addtogroup hooks".
 */
