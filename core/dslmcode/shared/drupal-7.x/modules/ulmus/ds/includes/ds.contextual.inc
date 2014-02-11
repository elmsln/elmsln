<?php

/**
 * @file
 * Menu callbacks for contextual links and tabs added by DS.
 */

/**
 * Menu callback: redirect to manage display.
 */
function ds_contextual_page_tab($object, $entity_type) {

  switch ($entity_type) {
    case 'node':
      $bundle = $object->type;
      $view_mode = (!empty($object->ds_switch)) ? $object->ds_switch : 'full';

      // Let's always go back to the node page.
      $destination = 'node/' . $object->nid;
      break;
    case 'user':
      $bundle = 'user';
      $view_mode = 'full';
      $destination = 'user/' . $object->uid;
      break;
    case 'taxonomy_term':
      $bundle = $object->vocabulary_machine_name;
      $view_mode = 'full';
      $destination = 'taxonomy/term/' . $object->tid;
      break;
  }

  // Check if we have a configured layout. Do not fallback to default.
  $layout = ds_get_layout($entity_type, $bundle, $view_mode, FALSE);

  // Get the manage display URI.
  $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);

  // Check view mode settings.
  $view_mode_settings = field_view_mode_settings($entity_type, $bundle);
  $overriden = (!empty($view_mode_settings[$view_mode]['custom_settings']) ? TRUE : FALSE);

  if (empty($layout) && !$overriden) {
    $admin_path .= '/display';
  }
  else {
    $admin_path .= '/display/' . $view_mode;
  }

  drupal_goto($admin_path, array('query' => array('destination' => $destination)));
}
