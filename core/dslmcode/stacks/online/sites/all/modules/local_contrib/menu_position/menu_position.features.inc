<?php
/**
 * @file
 * Integration with the Features module.
 */

/**
 * Implements hook_features_export().
 */
function menu_position_features_export($data, &$export, $module_name = '') {
  foreach ($data as $machine_name) {
    $export['features']['menu_position'][$machine_name] = $machine_name;
  }
  return array();
}

/**
 * Implements hook_features_export_options().
 */
function menu_position_features_export_options() {
  $options = array();

  $fields = db_select('menu_position_rules', 'm')
    ->fields('m', array('machine_name', 'admin_title'))
    ->execute();

  foreach ($fields as $row) {
    $options[$row->machine_name] = $row->admin_title;
  }

  return $options;
}

/**
 * Implements hook_features_export_render().
 */
function menu_position_features_export_render($module_name, $data) {
  $items = array();
  foreach ($data as $id => $machine_name) {
    $query = db_select('menu_position_rules', 'm')
      ->fields('m', array(
        'admin_title',
        'enabled',
        'conditions',
        'menu_name',
        'plid',
        'mlid',
        'weight',
        'machine_name',
      ))
      ->condition('machine_name', $machine_name)
      ->execute();
    $field = $query->fetchAssoc();
    $items[$machine_name] = $field;
  }
  $code = "  \$items = " . features_var_export($items, '  ') . ";\n";
  $code .= '  return $items;';
  return array('menu_position_default_menu_positions' => $code);
}

/**
 * Implements hook_features_revert().
 */
function menu_position_features_revert($module) {
  $defaults = features_get_default('menu_position', $module);
  if (empty($defaults)) {
    return;
  }
  // Revert.
  foreach ($defaults as $object) {
    _menu_position_save_rule($object);
  }
}

/**
 * Saves a menu position to the database.
 *
 * @param array $field_data
 *   The field data to save.
 */
function _menu_position_save_rule($field_data) {
  module_load_include('inc', 'menu_position', 'menu_position.admin');

  // Update/insert the rule.
  db_merge('menu_position_rules')
    ->key(array('machine_name' => $field_data['machine_name']))
    ->fields($field_data)
    ->execute();

  // Update the menu link.
  $result = db_query('SELECT rid FROM {menu_position_rules} WHERE machine_name = :machine_name', array(
    ':machine_name' => $field_data['machine_name'],
  ))->fetchAssoc();
  menu_position_edit_menu_link($result['rid'], $field_data['mlid'], $field_data['plid'], $field_data['admin_title']);

  // Override the menu link id.
  $query = db_update('menu_links')
    ->fields(array(
      'mlid' => $field_data['mlid'],
    ))
    ->condition('menu_name', $field_data['menu_name'])
    ->condition('plid', $field_data['plid'])
    ->condition('module', 'menu_position');
    $query->execute();
}
