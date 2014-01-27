<?php

/**
* Implements hook_views_data_alter()
*/
function clone_views_data_alter(&$views_data) {
  $views_data['node']['clone_node'] = array(
    'field' => array(
      'title' => t('Clone link'),
      'help' => t('Provide a simple link to clone the node.'),
      'handler' => 'views_handler_field_node_link_clone',
    ),
  );
}
