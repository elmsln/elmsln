<?php

/**
 * Callback to return available display modes for a nid
 */
function elmsmedia_helper_elmsln_api_callback_elmsmedia_display_modes() {
  global $_elmsln;
  $params = $_elmsln['args'];
  $node = node_load($params['nid']);
  // view mode tabs which allow filtering out available
  $settings = variable_get('view_mode_tab_settings__' . $node->type, array());
  $entity_info = entity_get_info();
  if (!empty($entity_info['node']['view modes'])) {
    $view_modes = array_keys($entity_info['node']['view modes']);
    foreach ($view_modes as $view_mode) {
      if (!isset($settings[$view_mode]) || $settings[$view_mode] !== 0) {
        $display_modes[$view_mode] = $view_mode;
      }
    }
  }
  return array(
    'elmsmedia_display_modes' => TRUE,
    'display_modes' => $display_modes,
    'message' => "Available display modes returned",
  );
}
