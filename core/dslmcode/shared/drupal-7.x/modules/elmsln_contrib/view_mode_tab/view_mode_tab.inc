<?php

/**
 * Loads all the view modes for this node and then outputs them.
 */
function _view_mode_tab_load($node) {
  $output = '';
  $settings = variable_get('view_mode_tab_settings__' . $node->type, array());

  $entity_info = entity_get_info();

  if (!empty($entity_info['node']['view modes'])) {
    $view_modes = array_keys($entity_info['node']['view modes']);

    $header = array();
    $rendered_node = array();
    foreach ($view_modes as $view_mode) {
      if (!isset($settings[$view_mode]) || $settings[$view_mode] !== 0) {
        $id = drupal_html_id($view_mode);
        $header[] = l($view_mode, 'node/' . $node->nid . '/view_modes', array('fragment' => $id));
        $rendered_node[$view_mode] = array(
          'view_mode' => node_view($node, $view_mode),
          'header_id' => $id,
        );
      }
    }

    $output .= theme('item_list', array('items' => $header));
    $output .= theme('view_mode_tab_display', array('view_modes' => $rendered_node, 'node' => $node));
  }
  return $output;
}
