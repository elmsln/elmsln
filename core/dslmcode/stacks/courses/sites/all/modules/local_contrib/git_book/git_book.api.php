<?php
/**
 * @file
 * API for the Git Book feature.
 */

/**
 * Implements hook_git_book_parser().
 */
function hook_git_book_parser() {
  // all functions below are handed $path, $node variables
  // $path is the path on the file system to the repo
  // $node is the git_book mapped to this repo
  $parser['rtd'] = array(
    // name to present in lists
    'name'   => t('Read the Docs'),
    // callback for initialization, this allows you to run functionality when a repo is
    // created from the system itself
    'init'   => '_git_book_rtd_make_yml',
    // callback to parse the repo, this will have access to:
    'parser' => 'git_book_rtd_git_book_parse',
    // callback to construct the path / title of repo items, this will have access to:
    'path'   => 'git_book_rtd_construct_path',
  );
  return $parser;
}

/**
 * Implements hook_git_book_parse_alter().
 */
function hook_git_book_parser_alter(&$parsers) {
  // modify the way a core parser works
}

