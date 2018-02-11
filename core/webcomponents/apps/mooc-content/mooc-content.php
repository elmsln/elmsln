<?php
/**
 * @file
 * Code for MOOC content app
 */
// hook up the book service
define('__ROOT__', dirname(dirname(dirname(__FILE__))));
require_once(__ROOT__.'/services/LRNAppBookService.php');

/**
 * Callback for apps/mooc-content/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _mooc_content_data($machine_name, $app_route, $params, $args) {
  $status = 404;
  $return = array();
  $service = new LRNAppBookService();
  $node = $service->loadActiveNode();
  if (isset($node->nid)) {
    // render navigation
    $vars = _mooc_helper_book_nav_build($node);
    // output contents by passing through the wrapper theme function
    $tmp = theme('book_sibling_nav_wrapper', $vars);
    $navigation = render($tmp);

    // render content
    $content = drupal_render(node_view($node));

    // render outline
    $outline = _mooc_nav_block_mooc_nav_block($node);
    $return = array(
      'title' => $node->title,
      'navigation' => $navigation,
      'content' => $content,
      'outline' => $outline,
      //'pageObject' => $service->getPage($node->nid),
    );
    $status = 200;
  }
  return array(
    'status' => $status,
    'data' => $return
  );
}
