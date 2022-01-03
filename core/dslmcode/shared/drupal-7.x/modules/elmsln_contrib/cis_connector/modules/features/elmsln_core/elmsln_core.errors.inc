<?php

/**
 * Error title callback
 */
function _elmsln_core_error_title($code) {
  switch ($code) {
    case '403':
      return t('Access denied');
    break;
    case '404':
      return t('Page not found');
    break;
  }
}

/**
 * Error page callback
 */
function _elmsln_core_error_page($code) {
  drupal_add_css(drupal_get_path('module', 'cis_lmsless') . '/css/cis_lmsless_haxcms.css');
  $output = '<div class="elmsln-error-page">';
  $output .= '<div class="error-' . $code . '">';
  switch ($code) {
    case '403':
      $output .= t('Access denied, please log into your account.');
    break;
    case '404':
      $output .= t('Sorry, page not found.');
    break;
  }
  $output .= '</div></div>';
  drupal_alter("elmsln_access_denied_output", $output, $code);
  return $output;
}