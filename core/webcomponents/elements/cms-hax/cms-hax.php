<?php
/**
 * Example for Drupal 6.x
 */
function _cms_hax_drupal6x($nid, $body) {
  $return = array();
  $node = node_load($nid);
  $node->body = $body;
  node_save($node);
  return array(
    'status' => 200,
    'message' => t('Save successful!'),
    'data' => $node,
  );
}

/**
 * Example for Drupal 7.x
 */
function _cms_hax_drupal7x($nid, $body) {
  $return = array();
  $node = node_load($nid);
  $node->body['und'][0]['value'] = $body;
  node_save($node);
  return array(
    'status' => 200,
    'message' => t('Save successful!'),
    'data' => $node,
  );
}

/**
 * Example for Backdrop 1xx
 */
function _cms_hax_backdrop1xx($nid, $body) {
  $return = array();
  $node = node_load($nid);
  $node->body['und'][0]['value'] = $body;
  node_save($node);
  return array(
    'status' => 200,
    'message' => t('Save successful!'),
    'data' => $node,
  );
}
