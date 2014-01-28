<?php
/**
 * @file
 * Thumbnav API functions.
 */

/**
 * Implements hook_thumbnav_lib().
 *
 * Developer hook to add support for a new library.
 *
 * @return $touch_libs
 *   an array of values to define a new mobile mode.
 */
function hook_thumbnav_lib() {
  $touch_libs = array();
  // account for quojs being installed
  if (module_exists('quojs')) { // check library has been added
    $touch_libs['quojs'] = array(
      'name' => 'Quo.js', // human name of the project
      'location' => drupal_get_path('module', 'thumbnav') . '/thumbnav_libs/quojs/thumbnav_quo.js', // optional: location of the library implementation to load
      'style' => drupal_get_path('module', 'thumbnav') . '/thumbnav_libs/quojs/thumbnav_quo.css', // optional: stylesheet to apply for this library instance
      'controls' => array('leftright'), // array of control areas, left, right, and leftright are supported
    );
  }
  return $touch_libs;
}

/**
 * Implements hook_thumbnav_widget().
 *
 * Hook to add actions to the controller activated by swiping.
 *
 * @return $widgets
 *   array of available widgets for inclusion with a mobile mode.
 */
function hook_thumbnav_widget() {
  $widgets = array(
    'mooc_thumbnav_bookmark' => array( // key name, needs to be unique
      'icon' => base_path() . drupal_get_path('module', 'mooc_thumbnav') . '/images/bookmark.png', // optional full path to icon
      'title' => t('Bookmark page'), // human readable name
      'inc' => base_path() . drupal_get_path('module', 'mooc_thumbnav') . '/js/mooc_thumbnav_bookmark.js', // optional js to include
      'weight' => 1, // weight of the item to appear
      'side' => 'left', // prefered side for rendering
      'link' => 'node/5', // href to link this item to
      'fragment' => 'anchor_link', // useful when link undefined to include after #
    ),
    'book_touch_next' => array(
      'icon' => base_path() . drupal_get_path('module', 'book_touch') . '/images/nextpage.png',
      'title' => t('Next page'),
      'inc' => base_path() . drupal_get_path('module', 'book_touch') . '/js/book_touch_next.js',
      'weight' => 0,
      'side' => 'right',
    ),
  );
  return $widgets;
}