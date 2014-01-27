<?php
/**
 * @file
 * This include file implements coder_review functionality for 4.6 -> 4.7 upgrades.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_47_reviews() {
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+\w+(_node_name|_node_type)\s*\(',
    '#warning' => array(
      '#text' => 'implement !hook_node_info() to create a module which defines node type(s)',
      '#args' => array(
        '!hook_node_info' => _drupalapi('hook_node_info', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_load\s*\(\s*array\s*\(',
    '#warning' => array(
      '#text' => 'use !node_load($nid) instead of !node_load(array(\'nid\' => $nid))',
      '#args' => array(
        '!node_load' => _drupalapi('node_load', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_list\s*\(',
    '#warning' => array(
      '#text' => '!node_list() became node_get_types and now returns an associative array about node types',
      '#args' => array(
        '!node_list' => _drupalapi('node_list', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]module_get_node_name\s*\(',
    '#warning' => array(
      '#text' => '!module_get_node_name() deprecated and now handled by !node_get_base().',
      '#args' => array(
        '!module_get_node_name' => _drupalapi('module_get_node_name', 4.6),
        '!node_get_base' => _drupalapi('node_get_base', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]format_name\s*\(',
    '#warning' => array(
      '#text' => '!format_name() was renamed to !theme_username()',
      '#args' => array(
        '!format_name' => _drupalapi('format_name', 4.6),
        '!theme_username' => _drupalapi('theme_username', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '^\s*(taxonomy_save_vocabulary|taxonomy_save_term)\s*\(',
    '#warning' => 'check the return and display a status message',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]message_access\s*\(',
    '#warning' => array(
      '#text' => '!message_access() was removed, replace with a nice case error message',
      '#args' => array(
        '!message_access' => _drupalapi('message_access', 4.6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](strlen|strtolower|strtoupper|substr|ucfirst)\s*\(',
    '#warning' => 'in most cases, replace the string function with the drupal_ equivalent string functions',
    '#severity' => 'minor',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]conf_url_rewrite\s*\(',
    '#warning' => array(
      '#text' => '!conf_url_rewrite() became !custom_url_rewrite()',
      '#args' => array(
        '!conf_url_rewrite' => _drupalapi('conf_url_rewrite', 4.6),
        '!custom_url_rewrite' => _drupalapi('custom_url_rewrite', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_delete\s*\(\s*array\s*\(',
    '#warning' => array(
      '#text' => 'use !node_delete($nid) instead of !node_delete(array(\'nid\' => $nid))',
      '#args' => array(
        '!node_delete' => _drupalapi('node_delete', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]variable_get\s*\(\s*[\'"]+file_directory_temp[\'"]+\s*,',
    '#warning' => array(
      '#text' => 'use !file_directory_temp() function instead of variable',
      '#args' => array(
        '!file_directory_temp' => _drupalapi('file_directory_temp', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]variable_get\s*\(\s*[\'"]+file_directory_path[\'"]+\s*,',
    '#warning' => array(
      '#text' => 'use !file_directory_path() function instead of variable',
      '#args' => array(
        '!file_directory_path' => _drupalapi('file_directory_path', 4.7),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]array2object\s*\(',
    '#warning' => array(
      '#text' => '!array2object() replaced by native PHP type conversion (typecase to (object)',
      '#args' => array(
        '!array2object' => _drupalapi('array2object', 4.6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+\w+_onload\s*\(',
    '#warning' => array(
      '#text' => '!hook_onload() replaced by javascript addLoadEvent()',
      '#args' => array(
        '!hook_onload' => _drupalapi('hook_onload', 4.6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_validate_title\s*\(',
    '#warning' => array(
      '#text' => '!node_validate_title() was removed',
      '#args' => array(
        '!node_validate_title' => _drupalapi('node_validate_title', 4.6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]tablesort_pager\s*\(',
    '#warning' => array(
      '#text' => '!tablesort_pager() was removed',
      '#args' => array(
        '!tablesort_pager' => _drupalapi('tablesort_pager', 4.6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]form_(textfield|radio|group|select|checkbox|textarea)\s*\(',
    '#warning' => 'replace form_ functions with the forms api',
  );

  $review = array(
    '#title' => 'Converting 4.6.x modules to 4.7.x',
    '#link' => _drupalnode(22218),
    '#rules' => $rules,
    '#severity' => 'critical',
    '#version' => 2,
    '#image' => 'images/47.png',
  );
  return array('upgrade47' => $review);
}
