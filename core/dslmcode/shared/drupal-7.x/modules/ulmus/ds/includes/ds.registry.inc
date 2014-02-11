<?php

/**
 * @file
 * Registry file for Display Suite.
 */

/**
 * Implements hook_menu().
 */
function _ds_menu() {
  $items = array();

  // Layout overview.
  $items['admin/structure/ds'] = array(
    'title' => 'Display Suite',
    'description' => 'Manage layouts for entities and configure fields, view modes etc.',
    'page callback' => 'ds_layout_list',
    'file' => 'includes/ds.displays.inc',
    'access arguments' => array('admin_display_suite'),
  );

  // Layout overview, primary tab.
  $items['admin/structure/ds/list'] = array(
    'title' => 'Displays',
    'weight' => -10,
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // Layout overview, secondary tab.
  $items['admin/structure/ds/list/list'] = array(
    'title' => 'List',
    'weight' => -10,
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // Emergency page
  $items['admin/structure/ds/list/emergency'] = array(
    'title' => 'Emergency',
    'description' => 'In case you have errors via Display Suite, visit this page.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_emergency'),
    'access arguments' => array('admin_display_suite'),
    'file' => 'includes/ds.displays.inc',
    'type' => MENU_LOCAL_TASK,
    'weight' => 100,
  );

  // Change layout.
  $items['admin/structure/ds/change-layout'] = array(
    'title' => 'Change layout',
    'description' => 'Act on layout change to move fields elsewhere',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_field_ui_layout_change'),
    'access arguments' => array('admin_display_suite'),
    'file' => 'includes/ds.field_ui.inc',
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );

  // Revert layout.
  $items['admin/structure/ds/revert-layout'] = array(
    'title' => 'Revert layout',
    'description' => 'Revert layout and field settings.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_revert_layout_field_settings_form'),
    'file' => 'includes/ds.field_ui.inc',
    'access arguments' => array('admin_display_suite'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );

  // Disable layout.
  $items['admin/structure/ds/disable'] = array(
    'title' => 'Disable layout',
    'description' => 'Disable layout and field settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_disable_layout_field_settings_form'),
    'file' => 'includes/ds.field_ui.inc',
    'access arguments' => array('admin_display_suite'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );

  // Enable layout.
  $items['admin/structure/ds/enable'] = array(
    'title' => 'Enable layout',
    'description' => 'Enable layout and field settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_enable_layout_field_settings_form'),
    'file' => 'includes/ds.field_ui.inc',
    'access arguments' => array('admin_display_suite'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );

  // CTools content.
  $items['admin/structure/ds/fields/manage_ctools/content'] = array(
    'title' => 'Ctools field content',
    'page callback' => 'ds_ctools_content',
    'file' => 'includes/ds.field_ui.inc',
    'access arguments' => array('admin_display_suite'),
    'type' => MENU_CALLBACK,
  );

  // Contextual links.
  if (module_exists('contextual') && module_exists('field_ui')) {
    $items['node/%node/display'] = array(
      'title' => 'Manage display',
      'description' => 'Manage display of this content.',
      'page callback' => 'ds_contextual_page_tab',
      'page arguments' => array(1, 'node'),
      'file' => 'includes/ds.contextual.inc',
      'access arguments' => array('administer content types'),
      'type' => MENU_LOCAL_TASK,
    );

    $items['user/%user/display'] = array(
      'title' => 'Manage display',
      'description' => 'Manage display of this user profile.',
      'page callback' => 'ds_contextual_page_tab',
      'page arguments' => array(1, 'user'),
      'file' => 'includes/ds.contextual.inc',
      'access arguments' => array('administer users'),
      'type' => MENU_LOCAL_TASK,
    );

    if (module_exists('taxonomy')) {
      $items['taxonomy/term/%taxonomy_term/display'] = array(
        'title' => 'Manage display',
        'description' => 'Manage display of this term.',
        'page callback' => 'ds_contextual_page_tab',
        'page arguments' => array(2, 'taxonomy_term'),
        'access arguments' => array('administer taxonomy'),
        'type' => MENU_LOCAL_TASK,
        'weight' => 11,
        'file' => 'includes/ds.contextual.inc',
      );
    }
  }

  return $items;
}

/**
 * Implements hook_theme().
 */
function _ds_theme() {
  $theme_functions = array();

  // Layouts
  $layouts = ds_get_layout_info();
  foreach ($layouts as $key => $layout) {

    // We don't need panel layouts to be registered.
    if (isset($layout['module']) && $layout['module'] == 'panels') {
      continue;
    }

    $theme_functions[$key] = array(
      'render element' => 'elements',
      'template' => strtr($key, '_', '-'),
      'path' => $layout['path'],
    );
  }

  // Field templates
  $field_functions = module_invoke_all('ds_field_theme_functions_info');
  foreach ($field_functions as $key => $label) {
    $theme_functions[$key] = array(
      'render element' => 'element',
      'function' => $key,
    );
  }

  return $theme_functions;
}

/**
 * Implements hook_features_api().
 */
function _ds_features_api() {
  static $api = FALSE;

  if (!$api) {
    module_load_include('inc', 'features', 'includes/features.ctools');
    $api = ctools_component_features_api('ds');
    foreach ($api as $key => $value) {
      switch ($key) {
        case 'ds_field_settings':
          $api[$key]['name'] = 'Display Suite field settings';
          break;
        case 'ds_layout_settings':
          $api[$key]['name'] = 'Display Suite layout settings';
          break;
        case 'ds_view_modes':
          $api[$key]['name'] = 'Display Suite view modes';
          break;
        case 'ds_fields':
          $api[$key]['name'] = 'Display Suite fields';
          break;
      }
    }
  }

  return $api;
}

/**
 * Remove or rename layout & field settings on entity machine name update.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $info
 *   The entity info.
 * @param $action
 *   The action, either update or delete.
 */
function _ds_entity_type_update($entity_type, $info, $action) {

  // Delete settings.
  if ($action == 'delete') {
    db_delete('ds_layout_settings')
      ->condition('entity_type', $entity_type)
      ->condition('bundle', $info->type)
      ->execute();
    db_delete('ds_field_settings')
      ->condition('entity_type', $entity_type)
      ->condition('bundle', $info->type)
      ->execute();
  }

  // Update settings.
  if ($action == 'update') {
    $records = db_query('SELECT * FROM {ds_layout_settings} WHERE entity_type = :entity_type AND bundle = :bundle', array(':entity_type' => $entity_type, ':bundle' => $info->old_type));
    foreach ($records as $record) {
      $old_id = $entity_type . '|' . $info->old_type . '|' . $record->view_mode;
      $new_id = $entity_type . '|' . $info->type . '|' . $record->view_mode;
      db_update('ds_layout_settings')
        ->fields(array(
          'id' => $new_id,
          'bundle' => $info->type)
        )
        ->condition('id', $old_id)
        ->execute();
    }
    $records = db_query('SELECT * FROM {ds_field_settings} WHERE entity_type = :entity_type AND bundle = :bundle', array(':entity_type' => $entity_type, ':bundle' => $info->old_type));
    foreach ($records as $record) {
      $old_id = $entity_type . '|' . $info->old_type . '|' . $record->view_mode;
      $new_id = $entity_type . '|' . $info->type . '|' . $record->view_mode;
      db_update('ds_field_settings')
        ->fields(array(
          'id' => $new_id,
          'bundle' => $info->type)
        )
        ->condition('id', $old_id)
        ->execute();
    }
  }

  // Clear cache.
  cache_clear_all('ds_fields:', 'cache', TRUE);
  cache_clear_all('ds_field_settings', 'cache');
  field_info_cache_clear();
}

/**
 * Implements hook_theme_registry_alter().
 */
function _ds_theme_registry_alter(&$theme_registry) {

  // Inject ds_entity_variables in all entity theming functions.
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity => $info) {
    if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {

      // User uses user_profile for theming.
      if ($entity == 'user') $entity = 'user_profile';

      // Only add preprocess functions if entity exposes theme function.
      if (isset($theme_registry[$entity])) {
        $theme_registry[$entity]['preprocess functions'][] = 'ds_entity_variables';
      }
    }
  }

  // Support for File Entity.
  if (isset($theme_registry['file_entity'])) {
    $theme_registry['file_entity']['preprocess functions'][] = 'ds_entity_variables';
  }

  // Support for Entity API.
  if (isset($theme_registry['entity'])) {
    $theme_registry['entity']['preprocess functions'][] = 'ds_entity_variables';
  }
}

/**
 * Implements hook_entity_info_alter().
 */
function _ds_entity_info_alter(&$entity_info) {

  // Make sure ds_view_modes table exists.
  if (!db_table_exists('ds_view_modes')) {
    return;
  }

  ctools_include('export');

  // Add custom view modes to entities.
  $custom_view_modes = ctools_export_crud_load_all('ds_view_modes');
  foreach ($custom_view_modes as $view_mode_key => $view_mode_value) {
    $view_mode = array(
      'label' => check_plain($view_mode_value->label),
      'custom settings' => FALSE,
    );
    foreach ($view_mode_value->entities as $entity_type) {
      if (isset($entity_info[$entity_type])) {
        $entity_info[$entity_type]['view modes'][$view_mode_key] = $view_mode;
      }
    }
  }

  // Add layout if applicable.
  $ds_layouts = ds_get_layout_info();
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  foreach ($ds_layout_settings as $row) {

    // Don't store any configuration if the layout is disabled.
    if (!empty($row->disabled)) {
      continue;
    }

    // Don't store any configuration with layouts that don't exist anymore.
    if (!isset($ds_layouts[$row->layout])) {
      continue;
    }

    // Don't store any configuration if the entity type is not defined.
    if (!isset($entity_info[$row->entity_type])) {
      continue;
    }

    // Don't store any configuration if the bundle doesn't exist.
    if (!isset($entity_info[$row->entity_type]['bundles'][$row->bundle])) {
      continue;
    }

    $layout = $ds_layouts[$row->layout];
    $layout['layout'] = $row->layout;
    $layout['settings'] = $row->settings;
    $entity_info[$row->entity_type]['bundles'][$row->bundle]['layouts'][$row->view_mode] = $layout;
  }


  $revision = array(
    'label' => 'Revision',
    'custom settings' => FALSE,
  );
  $entity_info['node']['view modes']['revision'] = $revision;
}

/**
 * Implements hook_ds_layout_info().
 */
function _ds_ds_layout_info() {
  $path = drupal_get_path('module', 'ds');
  $layouts = array(
    'ds_1col' => array(
      'label' => t('One column'),
      'path' => $path . '/layouts/ds_1col',
      'regions' => array(
        'ds_content' => t('Content'),
      ),
      'image' => TRUE,
    ),
    'ds_1col_wrapper' => array(
      'label' => t('One column + wrapper'),
      'path' => $path . '/layouts/ds_1col_wrapper',
      'regions' => array(
        'ds_content' => t('Content'),
      ),
      'image' => TRUE,
    ),
    'ds_2col' => array(
      'label' => t('Two column'),
      'path' => $path . '/layouts/ds_2col',
      'regions' => array(
        'left' => t('Left'),
        'right' => t('Right')
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_2col_fluid' => array(
      'label' => t('Fluid two column'),
      'path' => $path . '/layouts/ds_2col_fluid',
      'regions' => array(
        'left' => t('Left'),
        'right' => t('Right')
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_2col_stacked' => array(
      'label' => t('Two column stacked'),
      'path' => $path . '/layouts/ds_2col_stacked',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_2col_stacked_fluid' => array(
      'label' => t('Fluid two column stacked'),
      'path' => $path . '/layouts/ds_2col_stacked_fluid',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_3col' => array(
      'label' => t('Three column - 25/50/25'),
      'path' => $path . '/layouts/ds_3col',
      'regions' => array(
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_3col_equal_width' => array(
      'label' => t('Three column - equal width'),
      'path' => $path . '/layouts/ds_3col_equal_width',
      'regions' => array(
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_3col_stacked' => array(
      'label' => t('Three column stacked - 25/50/25'),
      'path' => $path . '/layouts/ds_3col_stacked',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_3col_stacked_fluid' => array(
      'label' => t('Fluid three column stacked - 25/50/25'),
      'path' => $path . '/layouts/ds_3col_stacked_fluid',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_3col_stacked_equal_width' => array(
      'label' => t('Three column stacked - equal width'),
      'path' => $path . '/layouts/ds_3col_stacked_equal_width',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_4col' => array(
      'label' => t('Four column - equal width'),
      'path' => $path . '/layouts/ds_4col',
      'regions' => array(
        'first' => t('First'),
        'second' => t('Second'),
        'third' => t('Third'),
        'fourth' => t('Fourth'),
      ),
      'css' => TRUE,
      'image' => TRUE,
    ),
    'ds_reset' => array(
      'label' => t('Reset'),
      'path' => $path . '/layouts/ds_reset',
      'regions' => array(
        'ds_content' => t('Content'),
      ),
      'image' => TRUE,
    ),
  );

  // Support for panels.
  if (module_exists('panels')) {
    ctools_include('plugins', 'panels');
    $panel_layouts = panels_get_layouts();
    foreach ($panel_layouts as $key => $layout) {
      // The easy ones.
      if (isset($layout['regions'])) {
        $layouts['panels-' . $key] = array(
          'label' => $layout['title'],
          'path' => $layout['path'],
          'module' => 'panels',
          // We need the Panels plugin info array to correctly include the
          // layout and its CSS files later on.
          'panels' => $layout,
          'flexible' => FALSE,
          'regions' => $layout['regions'],
        );
        if (!empty($layout['css'])) {
          $layouts['panels-' . $key]['css'] = TRUE;
        }
      }
      // Flexible panel layouts, ignore the default flexible.
      else {
        if ($layout['name'] != 'flexible') {
          $regions = panels_flexible_panels(array(), array(), $layout);
          $layouts['panels-' . $key] = array(
            'label' => $layout['title'],
            'path' => $layout['path'],
            'module' => 'panels',
            'panels' => $layout,
            'flexible' => TRUE,
            'regions' => $regions,
          );
        }
      }
    }
  }

  // Get layouts defined in the active theme and base theme (if applicable).
  $themes = list_themes();
  $theme = variable_get('theme_default', 'bartik');

  $base_theme = array();
  $ancestor = $theme;
  while ($ancestor && isset($themes[$ancestor]->base_theme)) {
    $ancestor = $themes[$ancestor]->base_theme;
    $base_theme[] = $themes[$ancestor];
  }

  foreach (array_reverse($base_theme) as $base) {
    _ds_layouts_scan_theme($base->name, $layouts);
  }
  _ds_layouts_scan_theme($theme, $layouts);

  return $layouts;
}

function _ds_layouts_scan_theme($theme, &$layouts) {
  $theme_layouts = file_scan_directory(drupal_get_path('theme', $theme) . '/ds_layouts', '/inc$/');
  foreach ($theme_layouts as $file => $values) {
    include_once(DRUPAL_ROOT . '/' . $file);
    $function = 'ds_' . $values->name;
    $layouts[$values->name] = $function();
    $layouts[$values->name]['path'] = str_replace('/' . $values->filename, '', $file);
  }
}

/**
 * Implements hook_menu_alter().
 */
function _ds_menu_alter(&$items) {
  // Do not conflict with the revisioning module.
  if (module_exists('revisioning')) {
    $items['node/%node/revisions/%vid/view']['page callback'] = 'ds_revision_node_show';
    $items['node/%node/revisions/%vid/view']['file'] = 'includes/ds.revision.inc';
    $items['node/%node/revisions/%vid/view']['file path'] = drupal_get_path('module', 'ds');
  }
  else {
    $items['node/%node/revisions/%/view']['page callback'] = 'ds_revision_node_show';
    $items['node/%node/revisions/%/view']['file'] = 'includes/ds.revision.inc';
    $items['node/%node/revisions/%/view']['file path'] = drupal_get_path('module', 'ds');
  }
}
