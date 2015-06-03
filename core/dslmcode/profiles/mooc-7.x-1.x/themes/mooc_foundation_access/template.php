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
