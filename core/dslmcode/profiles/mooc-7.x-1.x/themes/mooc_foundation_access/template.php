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
  if (user_access('access printer-friendly version')) {
    $variables['tabs_extras'][0][] = l(t('Print'), 'book/export/html/' . arg(1));
  }
  if (user_access('access contextual links')) {
    $variables['tabs_extras'][0][] = '<li class="cis_accessibility_check"></li>';
  }
}

/**
 * Implements template_preprocess_region.
 */
function mooc_foundation_access_preprocess_region(&$variables) {
// add in the chevron contextual options for the high level
  if ($variables['region'] == 'left_menu' && function_exists('_cis_service_connection_active_outline') && user_access('access contextual links')) {
    $node = _cis_service_connection_active_outline();
    if (isset($node->nid)) {
      $variables['button_group'][0][] = l(t('Outline'), 'admin/content/book/' . $node->nid);
      $variables['button_group'][0][] = l(t('Print'), 'book/export/html/' . $node->nid);
      $variables['button_group'][0][] = l(t('Duplicate'), 'admin/content/book/copy/' . $node->nid);
    }
  }
}