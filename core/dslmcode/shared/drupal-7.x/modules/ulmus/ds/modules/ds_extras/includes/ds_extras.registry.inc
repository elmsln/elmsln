<?php

/**
 * @file
 * Display Suite Extras registry file.
 */

/**
 * Implements hook_menu_alter().
 */
function _ds_extras_menu_alter(&$items) {

  // Switch view mode.
  if (variable_get('ds_extras_switch_view_mode', FALSE)) {

    // Check if page manager is overriding.
    $skip_node_override = FALSE;
    if (module_exists('page_manager')) {
      if ($task = page_manager_get_task('node_view')) {
        if (isset($task['disabled']) && !$task['disabled']) {
          $skip_node_override = TRUE;
        }
      }
    }

    if (!$skip_node_override) {
      $items['node/%node']['page callback'] = 'ds_extras_node_page_view';
      $items['node/%node']['file'] = 'includes/ds_extras.pages.inc';
      $items['node/%node']['file path'] = drupal_get_path('module', 'ds_extras');
    }
  }
}

/**
 * Implements hook_entity_info().
 */
function _ds_extras_entity_info() {

  if (!variable_get('ds_extras_vd', FALSE)) {
    return;
  }

  $bundles = array();
  ctools_include('export');
  $vd_settings = ctools_export_crud_load_all('ds_vd');
  foreach ($vd_settings as $key => $vd) {
    $bundles[$vd->vd] = array(
      'label' => check_plain($vd->label),
      'admin' => array('path' => 'admin/structure/ds/vd/manage/' . $vd->vd),
    );
  }

  // Register a views entity on behalf of Views.
  $return = array(
    'ds_views' => array(
      'label' => t('Display Suite Views'),
      'bundles' => $bundles,
      'ds_display' => TRUE,
      'base table' => 'views_view',
      'entity keys' => array(
        'id' => 'vid',
        'label' => 'name',
      ),
    ),
  );

  return $return;
}

/**
 * Implements hook_theme_registry_alter().
 */
function _ds_extras_theme_registry_alter(&$theme_registry) {

  // Add views preprocess layout.
  if (variable_get('ds_extras_vd', FALSE)) {
    $theme_registry['views_view']['preprocess functions'][] = 'ds_extras_preprocess_view_layout';
  }

  // Add process page function.
  if (variable_get('ds_extras_hide_page_title', FALSE)) {
    $theme_registry['page']['process functions'][] = 'ds_extras_process_page_title';
  }

  // Remove ds_preprocess_field in case field templates is not enabled.
  if (!variable_get('ds_extras_field_template', FALSE)) {
    $key = array_search('ds_extras_preprocess_field', $theme_registry['field']['preprocess functions']);
    if (!empty($key)) {
      unset($theme_registry['field']['preprocess functions'][$key]);
    }
  }
}

/**
 * Implements hook_module_implements_alter().
 */
function _ds_extras_module_implements_alter(&$implementations, $hook) {

  // Because it's possible to turn on/off features for DS extras,
  // we'll unset hooks here if necessary which otherwhise do nothing at all.

  // Field template
  $ft_hooks = array(
    'ds_field_settings_alter',
    'form_ds_classes_form_alter',
    'form_field_ui_field_edit_form_alter',
    'theme',
  );
  if (!variable_get('ds_extras_field_template', FALSE) && in_array($hook, $ft_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Region to block
  $region_hooks = array(
    'ds_layout_region_alter',
    'field_attach_view_alter',
    'block_info',
    'block_view'
  );
  if (!variable_get('ds_extras_region_to_block', FALSE) && in_array($hook, $region_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Switch view mode
  $switch_hooks = array(
    'form_node_form_alter',
  );
  if (!variable_get('ds_extras_switch_view_mode', FALSE) && in_array($hook, $switch_hooks)) {
    unset($implementations['ds_extras']);
  }

  // Views displays
  $vd_hooks = array(
    'entity_info',
    'ctools_plugin_api',
    'ds_fields_ui_alter',
  );
  if (!variable_get('ds_extras_vd', FALSE) && in_array($hook, $vd_hooks)) {
    unset($implementations['ds_extras']);
  }
}
