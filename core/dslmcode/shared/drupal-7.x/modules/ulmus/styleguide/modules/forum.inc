<?php

/**
 * @file
 * Style Guide plugin file for the Forum module.
 */

/**
 * Implements hook_styleguide().
 */
function forum_styleguide() {
  $items = array();

  // Ensure that the functions are loaded.
  module_load_include('inc', 'forum', 'forum.pages');
  module_load_include('inc', 'forum', 'forum.admin');

  // Load the base forum, if it exists.
  $root = forum_forum_load(0);
  if (count($root->forums) > 0) {
    // Grab a sample forum from the list.
    $child = forum_forum_load(array_rand($root->forums, 1));
  }
  $items['forum_list'] = array(
    'title' => t('Forum list'),
    'content' => forum_page($root),
    'group' => t('Forum')
  );
  $items['forum_topic_list'] = array(
    'title' => t('Forum topic list'),
    'content' => (isset($child)) ? forum_page($child) : t('Please create a forum first.'),
    'group' => t('Forum')
  );
  $items['forum_form'] = array(
    'title' => t('Forum form'),
    'content' => forum_form_main('forum'),
    'group' => t('Forum')
  );

  return $items;
}
