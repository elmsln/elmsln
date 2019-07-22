<?php

/**
 * @file
 * Provides the field_collection module admin pages.
 */

/**
 * Menu callback; list all field collections on this site.
 */
function field_collections_overview() {
  $instances = field_info_instances();
  $field_types = field_info_field_types();
  $bundles = field_info_bundles();
  $header = array(
    t('Field name'),
    t('Used in'),
    array('data' => t('Operations'), 'colspan' => '2'),
  );
  $rows = array();
  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {
        $field = field_info_field($field_name);
        if ($field['type'] == 'field_collection') {
          $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);
          $rows[$field_name]['class'] = $field['locked'] ? array('menu-disabled') : array('');

          $rows[$field_name]['data'][0] = $field['locked'] ? t('@field_name (Locked)', array('@field_name' => $field_name)) : $field_name;
          $rows[$field_name]['data'][1][] = l($bundles[$entity_type][$bundle]['label'], $admin_path . '/fields');
        }
      }
    }
  }
  foreach ($rows as $field_name => $cell) {
    $rows[$field_name]['data'][1] = implode(', ', $cell['data'][1]);

    $field_name_url_str = strtr($field_name, array('_' => '-'));
    $rows[$field_name]['data'][2] = l(t('manage fields'), 'admin/structure/field-collections/' . $field_name_url_str . '/fields');
    $rows[$field_name]['data'][3] = l(t('manage display'), 'admin/structure/field-collections/' . $field_name_url_str . '/display');
  }
  if (empty($rows)) {
    $output = t('No field collections have been defined yet. To do so attach a field collection field to any entity.');
  }
  else {
    // Sort rows by field name.
    ksort($rows);
    $output = theme('table', array('header' => $header, 'rows' => $rows));
  }
  return $output;
}
