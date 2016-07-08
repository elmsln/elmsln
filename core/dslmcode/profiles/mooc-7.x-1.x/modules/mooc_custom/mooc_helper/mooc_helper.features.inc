<?php
/**
 * @file
 * mooc_helper.features.inc
 */

/**
 * Implements hook_views_default_views_alter().
 */
function mooc_helper_views_default_views_alter(&$data) {
  if (isset($data['cis_section_list'])) {
    $data['cis_section_list']->display['default']->display_options['fields']['field_instructional_outlines'] = array(
      'id' => 'field_instructional_outlines',
      'table' => 'field_data_field_instructional_outlines',
      'field' => 'field_instructional_outlines',
      'label' => 'Outline',
      'settings' => array(
        'link' => 1,
      ),
      'delta_offset' => 0,
    ); /* WAS: '' */
  }
}
