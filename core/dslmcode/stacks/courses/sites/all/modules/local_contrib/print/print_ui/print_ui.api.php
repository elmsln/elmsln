<?php

/**
 * @file
 * Hooks provided by the Print UI module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Provides the format-specific info to be used by the print_ui module.
 *
 * The print_ui module manages all the generic link management of the print
 * package sub-modules. In order to keep the code as generic as possible, all
 * the identified information necessary to build the link is provided as an
 * array, from which each of the print_ui functions can access the necessary
 * details. The print_ui module will iterate over all modules that implement
 * this hook and build a link pointing to the indicated path + node id (or url
 * alias). For convenience, this function should be called directly inside the
 * hook_menu call for each module, and the returned path value used as the
 * main entry point of the specific functionality.
 *
 * @return array
 *   An associative array containing:
 *   - format: The format identifier, must be unique among all modules.
 *     Examples: 'html', 'mail, 'pdf'.
 *   - text: The default string used in the link text. Overridable by the user
 *     configuration settings in the sub-module page.
 *   - description: The text shown when hovering over the link.
 *   - path: The unique path used to call the main handler.
 *   - class: The default value of the CSS class used in the 'a' tag of the
 *     link. Overridable by the user configuration settings in the sub-module
 *     page.
 *   - icon: the filename of the image used as the link icon.
 *   - module: the name of the module. Used to call common functions or access
 *     tables, as not all module names follow the 'print_format' template (e.g.
 *     print.module and not print_html.module).
 *
 * @ingroup print_hooks
 */
function hook_print_link() {
  return array(
    'format' => 'foo',
    'text' => t('Foo version'),
    'description' => t('Display the foo version of this page.'),
    'path' => 'printfoo',
    'class' => 'print-foo',
    'icon' => 'foo_icon.png',
    'module' => 'print_foo',
  );
}

/**
 * Checks if the link is allowed according to the appropriate sub-module.
 *
 * Normally checks if the user holds the required access permission, but can
 * be used for extra checks, such as the proper module configuration, etc.
 *
 * @param array $args
 *   An associative array containing:
 *   - path: path to the non-node page being displayed.
 *   - node: path to the node beign displayed.
 *   - view_mode: current view mode of the node being displayed.
 *   - type: 'node' or 'comment'.
 *
 * @return bool
 *   FALSE if not allowed, TRUE otherwise
 *
 * @ingroup print_hooks
 */
function hook_link_allowed($args) {
  return (user_access('access foo'));
}

/**
 * Allows the user to change the new window behaviour.
 *
 * @param string $new_window
 *   New window status.
 * @param string $format
 *   Format being processed.
 *
 * @ingroup print_hooks
 */
function hook_print_new_window_alter(&$new_window, $format) {
  if ($format == 'foo') {
    $new_window = variable_get('print_foo_new_window', FALSE);
  }
}

/**
 * @} End of "addtogroup hooks".
 */
