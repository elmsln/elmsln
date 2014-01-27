<?php

/**
 * @file
 * This include file implements coder functionality for style I prefer, Drupl'Art.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_druplart_reviews() {
  $rules['andor_assignment'] = array(
    '#type' => 'regex',
    '#value' => 'if\s+\(.*(&&|\|\|)\s+\$\w+\s+[\+\-\*\/\.]?=\s+.*\)',
    '#warning' => 'Dangerous assignment inside conditional may never happen, consider first putting on a separate line, or at the very least, use parenthesis to force precedence.',
    '#severity' => 'minor',
  );
  $rules['not_paren'] = array(
    '#type' => 'regex',
    '#value' => 'if \(\!\(.*\s+=\s+.*\)\)',
    '#warning' => 'Consider removing the extra parenthesis, instead use if (!$foo = bar()) {.',
    '#severity' => 'minor',
  );
  $rules['conditional_assignment'] = array(
    '#type' => 'regex',
    '#value' => 'if\s+\(.*\$\w+\s+[\+\-\*\/\.]?=\s+.*\)',
    // Don't display this if we match either of the regex's above.
    '#not' => '(' . $rules['andor_assignment']['#value'] . '|' . $rules['not_paren']['#value'] . ')',
    '#warning' => 'Consider putting the assignment on a line above the conditional for better readability.',
    '#severity' => 'minor',
  );
  $rules['user'] = array(
    '#type' => 'regex',
    '#value' => 'global\s+\$user;',
    '#warning' => 'Consider $GLOBALS[\'user\'] instead of global $user.',
    '#severity' => 'minor',
  );
  $rules['submit'] = array(
    '#type' => 'regex',
    '#function' => '_(submit|validate)$',
    '#value' => '\s+return\s+(TRUE|FALSE)',
    '#warning' => 'Submit and validate handlers return values are ignored.',
  );
  $rules['array_init'] = array(
    '#type' => 'regex',
    '#function' => '_menu$',
    '#value' => '\s+\$items\s+=\s+array\(\)',
    '#warning' => 'Array initialization may be unnecessary if the array is assigned in all code paths.',
    '#severity' => 'minor',
  );
  $rules['unary'] = array(
    '#type' => 'regex',
    '#value' => '\$\w+(\+\+|--)\s*;',
    '#warning' => 'Consider using $++foo instead of $foo++ when simply incrementing or decrementing.',
    '#severity' => 'minor',
  );

  $review = array(
    '#title' => "Drupl'Art Coding Style",
    '#link' => 'http://drupalwatchdog.com/2/1/druplart',
    '#rules' => $rules,
    '#description' => 'Optional; Checks for coding style suggested by the author.',
    '#version' => 2,
    '#image' => 'images/druplart.png',
  );
  return array('druplart' => $review);
}
