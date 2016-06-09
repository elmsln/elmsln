<?php
/**
 * @file
 * API for ELMSLN Core.
 */

/**
 * Implements hook_icon_library().
 * This allows you to tell elmsln about different icon libraries
 * that you want to use. Useful for if you are pulling them into our
 * menuing systems for example.
 */
function hook_icon_library() {
  return array(
    // @todo add support for new files being added automatically that are
    // associated with thes libraries like css files. Also any wrapper
    // code needed to implement the icon library would be good to have.
    'foundation_access' => array(
      'title' => t('Foundation access'),
    ),
    'material' => array(
      'title' => t('Material'),
    ),
  );
}

/**
 * Implements hook_icon_library_alter().
 */
function hook_icon_library_alter(&$libraries) {
  $libraries['custom_stuff']['title'] = t('things');
}