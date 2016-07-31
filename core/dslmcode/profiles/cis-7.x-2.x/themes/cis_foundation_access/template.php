<?php
/**
 * Implements hook_page_build().
 */
function cis_foundation_access_page_build(&$page) {
  drupal_add_css(drupal_get_path('theme', 'cis_foundation_access') . '/css/cis_styles.css');
}