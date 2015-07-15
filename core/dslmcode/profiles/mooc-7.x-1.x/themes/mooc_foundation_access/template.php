<?php

/**
 * Implements theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function mooc_foundation_access_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $breadcrumbs = '<div class="content-element-region small-12 medium-12 large-centered large-10 columns book-parent-nav-container">
    <h2 class="element-invisible">' . t('You are here') . '</h2>';

    $breadcrumbs .= '<ul class="breadcrumbs">';

    foreach ($breadcrumb as $key => $value) {
      $breadcrumbs .= '<li><h3 class="book-parent-nav-item"><div class="icon-content-outline-black outline-nav-icon"></div>' . strip_tags(htmlspecialchars_decode($value), '<br><br/><a></a><span></span>') . '</h3></li>';
    }

    $breadcrumbs .= '</ul><hr class="book-parent-container"/></div>';

    return $breadcrumbs;
  }
}

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
  if ($node && isset($node->book) && (user_access('add content to books') || user_access('administer book outlines')) && node_access('create', $child_type) && $node->status == 1 && $node->book['depth'] < MENU_MAX_DEPTH) {
    $variables['tabs_extras'][200][] = '<hr>';
    $variables['tabs_extras'][200][] = l(t('Add child page'), 'node/add/' . str_replace('_', '-', $child_type), array('query' => array('parent' => $node->book['mlid'])));
  }
  if (user_access('access contextual links')) {
    $variables['tabs_extras'][0][] = '<li class="cis_accessibility_check"></li>';
  }
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
