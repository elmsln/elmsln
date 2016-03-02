<?php

/**
 * @file
 * Drush interface to git_book functionalities.
 */

/**
 * Implements hook_drush_command().
 */
function git_book_drush_command() {
  $commands = array();

  $commands['git-book-create'] = array(
    'callback' => 'drush_git_book_create',
    'aliases' => array('gbc'),
    'description' => dt('Create a git book'),
    'examples' => array(
      'drush git-book-create https://github.com/elmsln/elmsln.git' => 'Import and process the git repo as if the node was created via the front-end.',
    ),
    'arguments' => array(
      'repo_url' => 'git repo url to import',
    ),
  );

  return $commands;
}

/**
 * Callback for command git-book-create.
 */
function drush_git_book_create($repo_url) {
  $node = new stdClass();
  $node->type = 'git_book';
  node_object_prepare($node);
  $node->language = LANGUAGE_NONE;
  $node->uid = 1;
  $node->status = 1;
  $node->promote = 0;
  $node->revision = 1;
  // make a path out of the repo name
  $tmp = explode('/', str_replace('.git', '', $repo_url));
  $title = array_pop($tmp);
  $node->title = $title;
  // set the git repo
  $node->field_git_repo[LANGUAGE_NONE][0]['value'] = $repo_url;
  // save which will kick off processing of the node
  node_save($node);
  drush_print(dt('git book @repo_url successfully imported as @title', array('@repo_url' => $repo_url, '@title' => $title)));
}
