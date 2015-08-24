<?php

/**
 * Implements template_preprocess_page.
 */
function mooc_foundation_access_preprocess_page(&$variables) {
  // speedreader is enabled
  if (module_exists('speedreader')) {
    $variables['speedreader'] = TRUE;
  }
  // mespeak is enabled
  if (module_exists('mespeak')) {
    $variables['mespeak'] = TRUE;
  }
  // support for add child page shortcut
  $node = menu_get_object();
  if (user_access('access printer-friendly version')) {
    $variables['tabs_extras'][200][] = '<hr>';
    $variables['tabs_extras'][200][] = l(t('Print'), 'book/export/html/' . arg(1));
  }
  $child_type = variable_get('book_child_type', 'book');
  if ($node && !empty($node->book) && (user_access('add content to books') || user_access('administer book outlines')) && node_access('create', $child_type) && $node->status == 1 && isset($node->book['depth']) && $node->book['depth'] < MENU_MAX_DEPTH) {
    $variables['tabs_extras'][200][] = '<hr>';
    $variables['tabs_extras'][200][] = l(t('Add child page'), 'node/add/' . str_replace('_', '-', $child_type), array('query' => array('parent' => $node->book['mlid'])));
  }
  if (user_access('access contextual links')) {
    $variables['tabs_extras'][0][] = '<li class="cis_accessibility_check"></li>';
  }
}

/**
 * Implements menu_link__cis_service_connection_active_outline().
 */
function mooc_foundation_access_menu_link__cis_service_connection_active_outline($variables) {
  switch(theme_get_setting('mooc_foundation_access_outline_labeling')) {
    case 'auto_both':
      $word = theme_get_setting('mooc_foundation_access_outline_label');
      $number = TRUE;
    break;
    case 'auto_num':
      $word = FALSE;
      $number = TRUE;
    break;
    case 'auto_text':
      $word = theme_get_setting('mooc_foundation_access_outline_label');
      $number = FALSE;
    break;
    case 'none':
      $word = FALSE;
      $number = FALSE;
    break;
    default :
      $word = t('Lesson');
      $number = TRUE;
    break;
  }
  return _foundation_access_menu_outline($variables, $word, $number);
}

/**
 * Implements menu_link__cis_service_connection_all_active_outline().
 */
function mooc_foundation_access_menu_link__cis_service_connection_all_active_outline($variables) {
  switch(theme_get_setting('mooc_foundation_access_outline_labeling')) {
    case 'auto_both':
      $word = theme_get_setting('mooc_foundation_access_outline_label');
      $number = TRUE;
    break;
    case 'auto_num':
      $word = FALSE;
      $number = TRUE;
    break;
    case 'auto_text':
      $word = theme_get_setting('mooc_foundation_access_outline_label');
      $number = FALSE;
    break;
    case 'none':
      $word = FALSE;
      $number = FALSE;
    break;
    default :
      $word = t('Lesson');
      $number = TRUE;
    break;
  }
  return _foundation_access_menu_outline($variables, $word, $number);
}

/**
 * Implements theme_breadrumb().
 */
function mooc_foundation_access_breadcrumb($variables) {
  // hide breadcrumbs
}
