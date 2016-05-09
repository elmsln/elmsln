<?php
/**
 * @file
 * ecd_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ecd_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_ds_layout_settings_info_alter().
 */
function ecd_types_ds_layout_settings_info_alter(&$data) {
  if (isset($data['node|cis_course|form'])) {
    $data['node|cis_course|form']->settings['fields']['field_accessibility_audit'] = 'right'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['field_cis_course_uuid'] = 'left'; /* WAS: 'right' */
    $data['node|cis_course|form']->settings['fields']['field_copyright_audit'] = 'right'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['field_course_address'] = 'left'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['field_course_machine_name'] = 'left'; /* WAS: 'right' */
    $data['node|cis_course|form']->settings['fields']['field_last_quality_date'] = 'right'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['field_notes'] = 'footer'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['field_quality_audit'] = 'right'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['field_resource_uuid_bind'] = 'footer'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['group_audits'] = 'right'; /* WAS: '' */
    $data['node|cis_course|form']->settings['fields']['path'] = 'hidden'; /* WAS: 'footer' */
    $data['node|cis_course|form']->settings['regions']['footer'][5] = 'field_notes'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['footer'][6] = 'field_resource_uuid_bind'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['hidden'][7] = 'path'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['hidden'][8] = '_add_existing_field'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['left'][1] = 'field_course_machine_name'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['left'][2] = 'field_cis_course_uuid'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['left'][3] = 'field_course_address'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['right'][10] = 'field_copyright_audit'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['right'][11] = 'field_quality_audit'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['right'][12] = 'field_last_quality_date'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['right'][4] = 'group_audits'; /* WAS: '' */
    $data['node|cis_course|form']->settings['regions']['right'][9] = 'field_accessibility_audit'; /* WAS: '' */
    unset($data['node|cis_course|form']->settings['regions']['footer'][3]);
    unset($data['node|cis_course|form']->settings['regions']['right'][1]);
    unset($data['node|cis_course|form']->settings['regions']['right'][2]);
  }
}

/**
 * Implements hook_node_info().
 */
function ecd_types_node_info() {
  $items = array(
    'cis_system' => array(
      'name' => t('System'),
      'base' => 'node_content',
      'description' => t('Systems used in ELMS Learning Network as reported by CIS.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ecd_asset' => array(
      'name' => t('Asset'),
      'base' => 'node_content',
      'description' => t('An asset is an item that needs certification / validation to be part of a full compliance audit. It is associated to a Course in some manner'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ecd_documentation' => array(
      'name' => t('Documentation'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
