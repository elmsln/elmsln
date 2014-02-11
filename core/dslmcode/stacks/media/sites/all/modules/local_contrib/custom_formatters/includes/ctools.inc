<?php
/**
 * @file
 * Chaos tool suite module integration.
 */

/**
 * Implements hook_custom_formatters_init() on behalf of ctools.module.
 */
function ctools_custom_formatters_init() {
  if (strstr(request_uri(), 'system/ajax') && in_array($_POST['form_id'], array('ctools_export_ui_edit_item_form', 'custom_formatters_export_ui_export_form'))) {
    require_once drupal_get_path('module', 'custom_formatters') . '/plugins/export_ui/custom_formatters.inc';

    /**
     * Temporary fix for CTools #AJAX issue.
     * @See http://drupal.org/node/1142812
     */
    ctools_include('export');
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function custom_formatters_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == 'custom_formatters' && $api == 'custom_formatters') {
    return array('version' => 2);
  }
}

/**
 * Implements hook_ctools_plugin_directory().
 */
function custom_formatters_ctools_plugin_directory($module, $plugin) {
  if ($module == 'ctools' && !empty($plugin)) {
    return "plugins/{$plugin}";
  }
}

/**
 * Implements hook_custom_formatters_theme_alter() on behalf of ctools.module.
 */
function ctools_custom_formatters_theme_alter(&$theme) {
  $theme['custom_formatters_export_ui_form_preview'] = array(
    'render element' => 'form',
    'file' => 'custom_formatters.inc',
    'path' => drupal_get_path('module', 'custom_formatters') . '/plugins/export_ui'
  );
}
