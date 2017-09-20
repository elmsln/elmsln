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
      'drush git-book-create https://github.com/elmsln/elmsln.git rtd master' => 'Import and process the git repo as if the node was created via the front-end.',
    ),
    'arguments' => array(
      'repo_url' => 'git repo url to import',
      'parser' => 'parser machine name to use',
      'branch' => 'branch to checkout'
    ),
    'options' => array(
      'push' => 'Boolean to set the repo to push on node changes.',
    ), 
  );
  $commands['git-book-sync'] = array(
    'callback' => 'drush_git_book_sync',
    'aliases' => array('gcs'),
    'description' => dt('Sync existing git book'),
    'arguments' => array(
      'name' => 'unique name of the gitbook.'
    ),
  );

  return $commands;
}

/**
 * Callback for command git-book-create.
 */
function drush_git_book_create($repo_url, $parser, $branch) {
  // get the push option
  $push = drush_get_option('push', FALSE);
  $push = ($push ? 1 : 0);
  // make a path out of the repo name
  $tmp = explode('/', str_replace('.git', '', $repo_url));
  $title = array_pop($tmp);
  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'git_book')
    ->propertyCondition('title', $title)
    ->execute();
  if (empty($entities['node'])) {
    $node = new stdClass();
    $node->type = 'git_book';
    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;
    $node->title = $title;
    $node->uid = 1;
    $node->status = 1;
    $node->promote = 0;
    $node->revision = 1;
    // set the git repo
    $node->field_git_repo[LANGUAGE_NONE][0]['value'] = $repo_url;
    $node->field_git_parser[LANGUAGE_NONE][0]['value'] = $parser;
    $node->field_git_branch[LANGUAGE_NONE][0]['value'] = $branch;
    $node->field_git_push[LANGUAGE_NONE][0]['value'] = $push;
    // save which will kick off processing of the node
    node_save($node);
    drush_print(dt('git book @repo_url successfully imported as @title', array('@repo_url' => $repo_url, '@title' => $title)));
    drupal_flush_all_caches();
  }
  else {
    drush_print(dt('A gitbook with the name @title already exists.', array('@title' => $title)));
  }
}

/**
 * Callback for command git-book-sync
 */
function drush_git_book_sync($name) {
  // if we had a new selected node
  $book = _git_book_drush_get_book_by_name($name);
  if ($book) {
    $path = _git_book_get_path($book);
    // make sure we have a branch to pull from
    if (isset($book->field_git_branch[LANGUAGE_NONE][0]['value'])) {
      // get the branch
      $branch = $book->field_git_branch[LANGUAGE_NONE][0]['value'];
      // load the repo from the book
      $repo = _git_book_get_repo($book);
      // attempt to pull
      $pull = _git_book_pull($repo, 'origin', $branch);
      // update the nodes
      git_book_gb_git_book_parse($path, $book);
      drupal_flush_all_caches();
    }
    else {
      drush_print(dt('You must specify a branch in your git_book.'));
    }
  }
  else {
    drush_print(dt('Book not found.'));
  }
}

/**
 * Helper function to retrieve a single book by name. Uses drush options to allow
 * the user to select which book they want.
 * @return  mixed    Returns book object or false if no book was found.
 */
function _git_book_drush_get_book_by_name($name) {
  $books = _git_book_get_books_by_name($name);
  if ($books && !empty($books)) {
    if (count($books) == 1) {
      // if there is only one then pop the book off of the array and return it
      return array_pop($books);
    }
    // if there is more than one node then we need to propmpt the user
    // to choose.
    else {
      foreach ($books as $node) {
        $drush_options[$node->nid] = $node->nid;
      }
      if (count($drush_options) > 1) {
        $nid = drush_choice($drush_options, dt('Multple books with that name found. Which git book node would you like to update?'), '!value');
        return $books[$nid];
      }
    }
  }
  return false;
}