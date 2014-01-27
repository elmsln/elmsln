<?php

/**
 * @file
 * This include file implements coder functionality for comments.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_comment_reviews() {
  $rules['cvsid'] = array(
    '#type' => 'grep',
    '#source' => 'comment',
    '#value' => '$Id',
    '#case-sensitive' => TRUE,
    '#warning' => array(
      '#text' => 'Commits to the Git repository do not require the CVS $Id' . '$ keyword in each file.',
      '#link' => _drupalnode(318),
    ),
    '#severity' => 'minor',
  );
  $rules['comment_indent'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '^\*',
    '#warning' => 'indent secondary line of comment one space ',
    '#severity' => 'minor',
  );
  $rules['comment_shell'] = array(
    '#type' => 'regex',
    '#source' => 'all',
    '#value' => '^\s*#',
    '#warning' => array(
      '#text' => 'Use of Perl/shell style comments (#) is discouraged.',
      '#link' => _drupalnode(1354, 'inline'),
    ),
    '#severity' => 'minor',
  );
  $rules['comment_space'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '^\s*\*.+|^\/\*.+',
    '#not' => '^\s*\*\s+|^\/\*\s+|^\/\*\*|^\s*\*\/',
    '#warning' => 'put a space between the asterisk and the comment text',
    '#severity' => 'minor',
  );
  $rules['comment_see_inline'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '.*\@see\s*',
    '#not' => '^(\s*\*|\/\/)\s*\@see.*$',
    '#warning' => array(
      '#text' => '@see should always be at the beginning of a line, never inline in other comments.',
      '#link' => _drupalnode(1354),
    ),
    '#severity' => 'minor',
  );
  // @todo: make this handle: see http://drupal.org/node/224333#block_optional
  $rules['comment_see'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '\@see\s*.*',
    '#not' => '^\@see\s+((\w+\(\)|[\w\.\-\?\/:\#\&=]+\.[\w\.\->\?\/:\#\&=]+)[,\s]+)*(\w+\(\)|[\w\.\->\?\/:\#\&=]+\.[\w\.\->\?\/:\#\&=]+)\W*$',
    '#warning' => array(
      '#text' => '@see should always be followed by a filename, a URL, class/interface name (optionally including method), or a function name including ().',
      '#link' => _drupalnode(1354),
    ),
    '#severity' => 'minor',
  );
  $rules['comment_see_sep'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '\@see\s*\w+.*$',
    '#not' => '^\@see\s+([\w\.\-\(\)\?\/:\#\&=]+,\s)*[\w\.\-\(\)\?\/:\#\&=]+?[\w\(\)\/]$',
    '#warning' => array(
      '#text' => '@see references should be separated by "," followed by a single space and with no trailing punctuation',
      '#link' => _drupalnode(1354),
    ),
    '#severity' => 'minor',
  );
  $rules['comment_see_space'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '\@see\s.*$',
    '#not' => '^\@see [^\s]',
    '#warning' => array(
      '#text' => '@see should be separated from the references by one space only',
      '#link' => _drupalnode(1354),
    ),
    '#severity' => 'minor',
  );
  $rules['docblock_file'] = array(
    '#type' => 'grep_invert',
    '#source' => 'comment',
    '#value' => '@' . 'file',
    '#warning' => array(
      '#text' => '@' . 'file block missing',
      '#link' => _drupalnode(1354, 'files'),
    ),
    '#filename-not' => array('patch'),
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_comment_install_file_block_callback',
  );
  $rules['comment_file'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '@' . 'file\s+.+$',
    '#warning' => array(
      '#text' => '@' . 'file description should be on the following line',
      '#link' => _drupalnode(1354, 'files'),
    ),
    '#severity' => 'minor',
  );
  $rules['comment_implements_period'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => 'Implements*\s+hook_\w+\(\)\s*$',
    '#warning' => 'Missing period',
    '#severity' => 'minor',
  );
  $rules['comment_implements_paren'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => 'Implements*\s+hook_\w+\s*\.*$',
    '#warning' => 'Missing parenthesis after function name',
    '#severity' => 'minor',
  );
  $rules['comment_implementation'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '\s*(Implementation|Implement|Implements)\s+of\s+hook_\w+',
    '#warning' => 'Comment should be read "Implements hook_foo()."',
    '#severity' => 'minor',
  );
  $rules['comment_implements'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '^.*?\*\s*Implements\s+hook_\w+\(\)\.',
    '#not' => '^\s\*\sImplements*\s+hook_\w+',
    '#warning' => 'Format should be <code>* Implements hook_foo().</code>',
    '#severity' => 'minor',
  );
  $rules['comment_implements_docblock'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => '\/\/\s*Implements\s+hook_\w+\(\)\.',
    '#warning' => 'Implements comment should be in a comment block.',
    '#severity' => 'minor',
  );
  $rules['comment_implements_cap'] = array(
    '#type' => 'regex',
    '#source' => 'comment',
    '#value' => 'implements\s+hook_\w+',
    '#warning' => '\'Implements\' should be at the start of the sentence and begin with a capitialized letter',
    '#severity' => 'minor',
    '#case-sensitive' => TRUE,
  );
  $rules['docblock_comment'] = array(
    '#type' => 'regex',
    '#source' => 'all',
    '#value' => '^\s*\/\*$',
    '#warning' => 'Block comments should begin with /** and not /*',
    '#function-not' => '.+',
    // @todo: this rule misses function header comments inside a class
    // because we can't tell the difference between a comment above a function and one above a variable.
    '#class-not' => '.+',
    '#severity' => 'minor',
  );
  $rules['docblock_function'] = array(
    '#type' => 'regex',
    '#source' => 'all',
    '#value' => '^\s*\/\*\*',
    '#warning' => 'Block comments should not be used within functions, instead just use C style /* instead of /**.',
    '#function' => '.+',
    '#severity' => 'minor',
  );
  $rules['comment_eg'] = array(
    '#type' => 'regex',
    '#source' => array('comment', 'quote'),
    '#value' => '(e\.g\. |\(eg)',
    '#warning' => "The correct use of the string is 'e.g.,' (with a comma after it). However, for clarity, consider changing 'e.g.' to 'for example,'.",
    '#severity' => 'minor',
    '#case-sensitive' => TRUE,
  );
  $rules['comment_ie'] = array(
    '#type' => 'regex',
    '#source' => array('comment', 'quote'),
    '#warning' => "The correct use of the string is 'i.e.' (with no comma after it). However, for clarity, consider changing 'i.e.' to 'for example,' or 'that is'.",
    '#value' => '(i\.e\.,| ie |\(ie |^ie )',
    '#severity' => 'minor',
    '#case-sensitive' => TRUE,
  );
  $rules['comment_docblock_missing'] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_comment_missing_docblock',
    '#severity' => 'minor',
  );

  $review = array(
    '#title' => 'Drupal Commenting Standards',
    '#link' => _drupalnode(318, 'comment'),
    '#rules' => $rules,
    '#description' => 'Checks for the Drupal commenting standards; every developer should use this.',
    '#version' => 2,
    '#image' => 'images/comment.png',
    '#js' => TRUE,
  );
  return array('comment' => $review);
}

/**
 * Rule callback: Checks for comment install file block.
 *
 * @see do_coder_review_callback()
 */
function _coder_review_comment_install_file_block_callback(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  // Only perform this check on install files.
  $pathinfo = pathinfo($coder_args['#filename']);
  if ($pathinfo['extension'] == 'install') {
    $file_found = 0;
    $invalid_file_message = 0;
    foreach ($lines as $lineno => $line) {
      if (preg_match('/^ * @file/', $line[0])) {
        $file_found = 1;
      }
      // Immediately reset $file_found on the next line, and check if the
      // comment matches the required format.
      elseif ($file_found == 1) {
        if (!preg_match('/^ * Install, update and uninstall functions for the \w+ module./', $line[0])) {
          $invalid_file_message = 1;
        }
        $file_found = 0;
      }
    }
    if ($invalid_file_message) {
      $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
      $tmprule = $rule;
      $tmprule['#warning'] = array(
        '#text' => 'For .install files, the @file description should be of the format "Install, update and uninstall functions for the foo module.".',
        '#link' => _drupalnode(318),
      );
      _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
    }
  }
}

/**
 * Rule callback: Checks for missing docblocks.
 *
 * @see do_coder_review_callback()
 */
function _coder_review_comment_missing_docblock(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  // Setup variable to display warnings.
  $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
  $tmprule = $rule;

  // Look for where all the classes and functions start.
  $alllines = $coder_args['#all_array_lines'];
  $prev_stack = array('', '');
  foreach ($coder_args['#stack'] as $lineno => $current_stack) {
    $anchor = NULL;
    if ($current_stack[0] && $current_stack[0] != $prev_stack[0]) {
      if (!isset($alllines[$lineno - 1]) || substr($alllines[$lineno - 1][0], -2) != '*/') {
        $anchor = 'classes';
      }
    }
    elseif ($current_stack[1] && $current_stack[1] != $prev_stack[1]) {
      if (!isset($alllines[$lineno - 1]) || substr($alllines[$lineno - 1][0], -2) != '*/') {
        $anchor = $current_stack[0] ? 'classes' : 'functions';
      }
    }
    if ($anchor) {
      $tmprule['#warning'] = array(
        '#text' => "Docblock should be immediately above @ref",
        '#args' => array(
          '@ref' => implode('::', array_filter($current_stack)),
        ),
        '#link' => _drupalnode(1354, $anchor),
      );
      _coder_review_error($results, $tmprule, $severity_name, $lineno, $alllines[$lineno][0], $coder_args['#ignores']);
    }
    $prev_stack = $current_stack;
  }
}
