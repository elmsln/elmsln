<?php

/**
 * @file
 * Implement coder functionality to check for debugging in production releases.
 */

function coder_review_production_reviews() {
  // Look for Built-in PHP debugging calls.
  $rules['php'] = array(
    '#type'    => 'regex',
    '#source'  => 'php',
    '#value'   => '\s*(?<!d)(?:print_r|var_dump)\s*\([^\)]+\)',
    '#not'     => 'print_r\s*\([^,]+,\s*true\s*\)',
    '#warning' => 'Remove PHP debugging function calls.',
  );
  // Look for Debugging calls provided by devel, skip function definitions.
  $rules['devel'] = array(
    '#type'    => 'regex',
    '#source'  => 'php',
    '#value'   => '\s*(?:\S+\s*)?(?:dargs|dpm|dpr|dprint_r|db_queryd|dsm|dvm|dvr)\s*\([^\)]+\)',
    '#not'     => 'function.*|(?:(?:dpr|dprint_r)\s*\([^,]+,\s*true)',
    '#warning' => 'Remove devel.module debugging function calls.',
  );
  // Look for code in comments that should be removed.
  $rules['code'] = array(
    '#type'    => 'regex',
    '#source'  => 'comment',
    '#value'   => '.*(?:\(|\);|\{|\})\s*$',
    '#not'     => '[^@]@(?:\{|see).*',
    '#warning' => 'Comments containing code should be removed for releases.',
  );

  $review = array(
    '#title' => 'Release standards',
    '#rules' => $rules,
    '#description' => 'Prepare modules for production by removing debugging function calls.',
  );
  return array('production' => $review);
}
