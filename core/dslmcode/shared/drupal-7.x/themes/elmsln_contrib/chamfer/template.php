<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
 
/**
 * Implements template_process_html().
 *
 * Override or insert variables into the page template for HTML output.
 */
function chamfer_process_html(&$variables) {
 // Hook into color.module.
 if (module_exists('color')) {
 _color_html_alter($variables);
 }
}
 
/*
 * Implements template_process_page().
 */
function chamfer_process_page(&$variables, $hook) {
 // Hook into color.module.
 if (module_exists('color')) {
 _color_page_alter($variables);
 }
}

/**
 * Implements hook_process_zone().
 */
function chamfer_process_zone(&$vars) {
  $theme = alpha_get_theme();
  if ($vars['elements']['#zone'] == 'menu') {
    $vars['logo'] = $theme->page['logo'];
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function chamfer_preprocess_links(&$vars) {
  if (isset($vars['links']['book_add_child'])) {
    unset($vars['links']['book_add_child']);
  }
  if (isset($vars['links']['book_printer'])) {
    $vars['links']['book_printer']['title'] = t('Print page');
  }
}