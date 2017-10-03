<?php
/**
 * @file
 * Code for calculating all the properties on the lrnapp-book element.
 */
/**
 * Complete sound path.
 */
function _lrnapp_book_complete_sound() {
  $app = webcomponents_app_load_app_definitions('lrnapp-book');
  return base_path() . $app['path'] . 'bower_components/lrnsys-progress/assets/complete.mp3';
}

/**
 * Finished sound path.
 */
function _lrnapp_book_finish_sound() {
  $app = webcomponents_app_load_app_definitions('lrnapp-book');
  return base_path() . $app['path'] . 'bower_components/lrnsys-progress/assets/finished.mp3';
}

/**
 * Return the active node's parent title.
 * @return [type] [description]
 */
function _lrnapp_book_render_active_title() {
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  if ($node) {
    return $node->title;
  }
  return '';
}

/**
 * Return the active node's parent title.
 * @return [type] [description]
 */
function _lrnapp_book_render_outline_title() {
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  $page = $service->getPage($node->nid);
  if ($page) {
    return $page->relationships->parent->title;
  }
  return '';
}

/**
 * Return the active node
 */
function _lrnapp_book_render_active_node() {
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  // return node content if they can see this
  if ($node && node_access('view', $node)) {
    return check_markup($node->body['und'][0]['value'], $node->body['und'][0]['format']);
  }
  return '';
}

/**
 * Return th active parameters to get things kicked off.
 */
function _lrnapp_book_render_active_params() {
  $return = array();
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  // return node content if they can see this
  if ($node && node_access('view', $node)) {
    $return = array('node' => $node->nid);
  }
  return drupal_json_encode($return);
}