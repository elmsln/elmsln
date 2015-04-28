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
  $variables['tabs_extras'] = '<hr>
    <li>' . l(t('Print'), 'book/export/html/' . arg(1)) . '</li>';
  }
  if (user_access('access contextual links')) {
    $variables['tabs_extras'] .= '<hr>
    <li class="cis_accessibility_check"></li>
    <hr>
    <li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">' . t('Course Settings') . '</a></li>';
  }
  // wrap non-node content in an article tag
  if (isset($variables['page']['content']['system_main']['main'])) {
    $variables['page']['content']['system_main']['main']['#markup'] = '<article class="large-12 columns view-mode-full">' . $variables['page']['content']['system_main']['main']['#markup'] . '</article>';
  }
}