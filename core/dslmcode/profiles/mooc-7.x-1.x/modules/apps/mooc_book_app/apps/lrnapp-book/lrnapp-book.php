<?php
/**
 * @file
 * Code for LRNApp book
 */

// hook up the book service
define('__ROOT__', dirname(dirname(__FILE__)));
require_once(__ROOT__.'/services/LRNAppBookService.php');
require_once(dirname(__FILE__).'/LRNAppBookProperties.php');

/**
 * Callback for apps/lrnapp-book/data/outline.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _lrnapp_book_outline_data($machine_name, $app_route, $params, $args) {
  $return = array();
  $items = array();
  $status = 404;
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  if (isset($node->nid)) {
    $page = $service->getPage($node->nid);
    $outline = $service->getOutline($node->nid);
    $items = $service->encodeOutline($outline, $app_route . '/');
    $return['outlineTitle'] = $page->attributes->title;
  }
  $return['items'] = $items;
  // verify this is a node
  if (isset($node->nid)) {
    $status = 200;
  }

  return array(
    'status' => $status,
    'data' => $return
  );
}

/**
 * Callback for apps/lrnapp-book/data/book.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _lrnapp_book_book_data($machine_name, $app_route, $params, $args) {
  $return = array();
  $items = array();
  $status = 404;
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  if (isset($node->nid)) {
    $page = $service->getPage($node->nid);
    // treat as a book outline instead of in depth outline
    $outline = $service->getOutline($node->nid, TRUE);
    $items = $service->encodeOutline($outline, $app_route . '/');
  }
  $return = array(
    "items" => $items
  );
  // verify this is a node
  if (isset($node->nid)) {
    $status = 200;
  }

  return array(
    'status' => $status,
    'data' => $return
  );
}

/**
 * Callback for apps/lrnapp-book/data/book.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _lrnapp_book_page_data($machine_name, $app_route, $params, $args) {
  $status = 404;
  $service = new LRNAppBookService();
  $node = $service->loadActivePage();
  $return = array(
    'title' => _lrnapp_book_render_active_title(),
    'content' => _lrnapp_book_render_active_node(),
    'node' => $node,
  );
  if (!empty($return['title'])) {
    $status = 200;
  }
  return array(
    'status' => $status,
    'data' => $return
  );
}
