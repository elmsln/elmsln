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
 * Example for Drupal 8.x.x
 */
use Drupal\node\Entity\Node;
function _cms_hax_drupal8xx($nid, $body) {
  $return = array();
  $node = Node::load($nid);
  $node->body->value = $body;
  $node->save();
  return array(
    'status' => 200,
    'message' => t('Save successful!'),
    'data' => $node,
  );
}

/**
 * Example for Wordpress 4.x.x
 */
function _cms_hax_wordpress4xx($pid, $body) {
  $return = array();
  $post = get_post($pid);
  $post->post_content = $body;
  wp_insert_post($node);
  return array(
    'status' => 200,
    'message' => t('Save successful!'),
    'data' => $post,
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
