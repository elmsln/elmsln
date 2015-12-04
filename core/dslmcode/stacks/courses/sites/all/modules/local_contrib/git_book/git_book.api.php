<?php
/**
 * @file
 * API for the Git Book feature.
 */

/**
 * Implements hook_git_book_parse().
 * Example taken from git_book_rtd
 * @param  object $repo Git.php object
 * @param  string $path filepath
 * @param  object $node git_book node that was created
 * @return array        structure of what we parsed
 */
function hook_git_book_parse($repo, $path, $node) {
  $ymlstructure = $path . '/mkdocs.yml';
  if (file_exists($ymlstructure)) {
    $mkdocs = yaml_parse_file($ymlstructure);
    if (isset($mkdocs['pages']) && is_array($mkdocs['pages'])) {
      // recursively parse and create nodes
      _git_book_rtd_parse($mkdocs['pages'], $path .'/docs/', $node);
      return $mkdocs['pages'];
    }
  }
}

/**
 * Implements hook_git_book_parse_alter().
 * @param  array &$gitcontent what was parsed and created from the repo
 */
function hook_git_book_parse_alter(&$gitcontent) {
  // do some manipulation after the git tree has been parsed
}

