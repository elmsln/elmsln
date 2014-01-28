<?php
/**
 * @file
 * cis_helpdesk_issue.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_helpdesk_issue_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cis_helpdesk_issue_node_info() {
  $items = array(
    'cis_helpdesk_issue' => array(
      'name' => t('Issue'),
      'base' => 'node_content',
      'description' => t('CIS Helpdesk issue'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
