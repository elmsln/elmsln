<?php

/**
 * @file
 * Display Suite Extras page functions.
 */

/**
 * Menu callback: show an individual node with the Switch field.
 */
function ds_extras_node_page_view($node) {

  // If there is a menu link to this node, the link becomes the last part
  // of the active trail, and the link name becomes the page title.
  // Thus, we must explicitly set the page title to be the node title.
  drupal_set_title($node->title);
  $uri = entity_uri('node', $node);
  // Set the node path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);

  // Update the history table, stating that this user viewed this node.
  node_tag_new($node);

  if (empty($node->ds_switch)) {
    // When not set fall back to full
    $view_mode = 'full';
  }
  elseif ($node->ds_switch == 'default') {
    // When default set fall back to full
    $view_mode = 'full';
  }
  else {
    $view_mode = $node->ds_switch;
  }

  // It's also possible to use $_GET['v'] to switch view modes.
  if (isset($_GET['v']) && !empty($_GET['v'])) {
    $view_mode = $_GET['v'];
  }
  drupal_static('ds_extras_view_mode', $view_mode);

  // For markup consistency with other pages, use node_view_multiple() rather than node_view().
  return node_view_multiple(array($node->nid => $node), $view_mode);
}

/**
 * Menu callback: switches to another view mode inline.
 */
function ds_switch_view_mode_inline() {

  $content = '';
  $status = TRUE;
  $error = FALSE;

  $id = $_REQUEST['id'];
  $view_mode = $_REQUEST['view_mode'];
  $entity_type = $_REQUEST['entity_type'];
  $entity = entity_load($entity_type, array($id));

  if (!isset($entity[$id])) {
    $status = FALSE;
    $error = t('Content was not found.');
  }
  else {
    if (node_access('view', $entity[$id])) {
      $element = node_view($entity[$id], $view_mode);
      $content = drupal_render($element);
    }
    else {
      $error = t('Access denied');
    }
  }

  drupal_add_http_header('Content-Type', 'text/javascript; charset=utf-8');
  print drupal_json_encode(array(
    'status' => $status,
    'content' => $content,
    'errorMessage' => $error,
  ));
  exit();
}
