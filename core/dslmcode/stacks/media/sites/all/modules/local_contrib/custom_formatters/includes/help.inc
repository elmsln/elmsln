<?php

/**
 * @file
 * Help module integration.
 */

/**
 * Implements hook_help().
 */
function custom_formatters_help($path, $arg) {
  switch ($path) {
    case 'admin/help#custom_formatters':
      return t('Read the manual at: <a href="https://www.drupal.org/node/2514412">drupal.org/node/2514412</a>');
  }
}
