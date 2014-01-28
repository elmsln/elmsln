<?php
/**
 * Implements hook_textbook_style().
 *
 * Define a new style of textbook to apply
 *
 * @return $styles
 *   An array defining the files to apply per the style.
 *   textbook_core - machine ID of the style
 *   name - Translated, human readable name
 *   node - css, js, and reset styles when viewing a node
 *   print - css, js, and reset styles when printing
 */
function hook_textbook_style() {
  // default path
  $tpath = drupal_get_path('module', 'textbook') .'/css/';
  $styles = array(
    'textbook_core' => array(
      'name' => t('Textbook core: Default style'),
      'node' => array(
        'css' => array(
          $tpath .'textbook.css',
          $tpath .'textbook_tables.css',
          $tpath .'textbook_lists.css',
        ),
        'js' => array(),
        'reset' => array(
          $tpath .'reset.css',
        ),
      ),
      'print' => array(
        'css' => array(
          $tpath .'reset.css',
        ),
        'reset' => array(),
      ),
    ),
  );
  return $styles;
}

/**
 * Implements hook_textbook_active_style_alter().
 *
 * Developer hook to modify calculated active textbook style
 *
 * @param $active
 *   The active textbook style to apply, passed by reference.
 *
 */
function hook_textbook_active_style_alter(&$active) {
  global $user;
  // if user is 10, change their textbook style
  if ($user->uid == 10) {
    $active = 'cool_stuff';
  }
}
?>