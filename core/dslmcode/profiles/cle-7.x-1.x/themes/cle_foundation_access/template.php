<?php

/**
 * Implements theme_breadrumb().
 */
function cle_foundation_access_breadcrumb($variables) {
  // hide breadcrumbs
}

/**
 * Implements template_preprocess_page.
 */
function cle_foundation_access_preprocess_page(&$variables) {
  // add class for page title if this is student work
  if (isset($variables['node']) && isset($variables['node']->type) && in_array($variables['node']->type, array('cle_submission', 'cle_critique'))) {
    $variables['title_prefix'] = '<div class="ferpa-protect">';
    $variables['title_suffix'] = '</div>';
  }
}