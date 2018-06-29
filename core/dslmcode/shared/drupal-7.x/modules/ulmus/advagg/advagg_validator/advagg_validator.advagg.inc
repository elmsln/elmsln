<?php

/**
 * @file
 * Advanced CSS/JS aggregation validator module.
 */

/**
 * @addtogroup advagg_hooks
 * @{
 */

/**
 * Implements hook_advagg_update_github_versions_alter().
 */
function advagg_validator_advagg_update_github_versions_alter(&$projects) {
  $projects['csslint'] = array(
    'callback' => 'advagg_get_github_version',
    'url' => 'https://rawgit.com/CSSLint/csslint/master/package.json',
    'variable_name' => 'advagg_validator_github_version_csslint',
  );
  $projects['jshint'] = array(
    'callback' => 'advagg_get_github_version',
    'url' => 'https://rawgit.com/jshint/jshint/master/package.json',
    'variable_name' => 'advagg_validator_github_version_jshint',
  );
}

/**
 * @} End of "addtogroup advagg_hooks".
 */
