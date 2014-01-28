<?php

/**
 * @file
 * Drush integration for Book Copy module.
 */

/**
 * Implements hook_drush_command().
 */
function book_copy_drush_command() {
  $items['copy-book'] = array(
    'description' => dt('Copy all items in the book outline below an associated node id.'),
    'arguments' => array(
      'nid' => dt('Node id of the item to copy along with everything below it.'),
      'title' => dt('The new title for the copied book / outline'),
    ),
    'aliases' => array('copyb'),
    'examples' => array(
      'drush copy-book 1 "Cool Stuff"' => 'Copy book outline with node id 1 and rename it to Cool Stuff.',
      'drush copyb 10' => 'Copy book ouline with node id 10 and keep the name the same as the original.',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function book_copy_drush_help($section) {
  switch ($section) {
    case 'drush:copy-book':
      return dt('Copy a book or part of a book outline');
  }
}

/**
 * Drush command callback for copying a book or part of a book
 */
function drush_book_copy_copy_book($nid, $title = NULL) {
  if (empty($nid)) {
    drush_log(dt('Node id is required in order to copy anything'), 'error');
    return FALSE;
  }
  else {
    $node = node_load($nid);
    // exact copy if no title was defined
    if (is_null($title)) {
      $title = $node->title;
    }
    book_copy_process_copy($nid, $node->title, $title, FALSE);
    drush_log(dt("Outline @title successfully copied to @newtitle!", array('@title' => $node->title, '@newtitle' => $title)), 'ok');
    return TRUE;
  }
}