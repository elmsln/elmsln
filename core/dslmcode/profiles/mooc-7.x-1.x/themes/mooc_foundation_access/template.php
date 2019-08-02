<?php

/**
 * Implements template_preprocess_page.
 */
function mooc_foundation_access_preprocess_page(&$variables) {
  // speedreader is enabled
  if (module_exists('speedreader')) {
    $variables['speedreader'] = TRUE;
  }
  // drop some tabs that don't seem to go away on their own
  if (isset($variables['tabs']['#primary']) && !empty($variables['tabs']['#primary'])) {
    foreach ($variables['tabs']['#primary'] as $key => $value) {
      if (in_array($value['#link']['path'], array('node/%/display', 'node/%/outline', 'node/%/log'))) {
        unset($variables['tabs']['#primary'][$key]);
      }
    }
    // for now drop secondary entirely for nodes
    if (arg(0) == 'node' && isset($variables['tabs']['#secondary'])) {
      unset($variables['tabs']['#secondary']);
    }
  }
  $child_type = variable_get('book_child_type', 'book');
  $node = menu_get_object();
  if ($node && !empty($node->book) && (user_access('add content to books') || user_access('administer book outlines')) && node_access('create', $child_type) && $node->status == 1 && isset($node->book['depth']) && $node->book['depth'] < MENU_MAX_DEPTH) {
    $variables['tabs_extras'][200][] = l(t('Edit child outline'), 'node/' . $node->book['nid'] . '/outline/children');
    $variables['tabs_extras'][200][] = l(t('Edit course outline'), 'admin/content/book/' . $node->book['bid']);
  }
  // remove the prefix that provides a link to the home page
  // as MOOC is the thing that currently provides support directly for this
  // and slightly overrides the behavior
  $keys = array_keys($variables['page']['header']);
  $keyname = array_shift($keys);
  unset($variables['page']['header'][$keyname]['#prefix']);

  // Remove title from a page when a gitbook markdown filter is present.
  if(isset($variables['page']['content']['system_main']['nodes'])) {
    foreach($variables['page']['content']['system_main']['nodes'] as $node) {
      if(isset($node['body']['#object'])) {
        if($node['body']['#object']->body['und'][0]['format'] == "git_book_markdown") {
          $variables['title'] = "";
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_node.
 */
function mooc_foundation_access_preprocess_node(&$variables) {
  // Remove title from a page when a gitbook markdown filter is present.
  if(isset($variables['body'][0]['format'])) {
    if($variables['body'][0]['format'] == "git_book_markdown") {
      $variables['title'] = "";
    }
  }
}

/**
 * Implements theme_breadrumb().
 */
function mooc_foundation_access_breadcrumb($variables) {
  // hide breadcrumbs
}

/**
 * Implements menu_tree__menu_elmsln_add.
 */
function mooc_foundation_access_menu_tree__menu_elmsln_add($variables) {
  $links = '';
  // make sure nothing shows up if this is the new book
  if (arg(1) != 'lrnapp-book') {
    if (user_access('add item in context')) {
      $links = _elmsln_core_in_context_list();
      $links = implode("\n", $links);
    }
    return '<ul role="menu" aria-hidden="false" tabindex="-1" class="elmsln-add-menu-items">' . $links . $variables['tree'] . '</ul>';
  }
  return FALSE;
}
