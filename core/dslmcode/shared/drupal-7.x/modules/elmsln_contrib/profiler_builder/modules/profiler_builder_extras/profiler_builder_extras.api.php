<?php
/**
 * @file
 * Profiler Builder Extras API examples and documentation.
 */

/**
 * Implements hook_profiler_builder_extras_db_ignore().
 *
 * Queries that we want to ignore. It is not required that they be keyed but
 * it would allow others to modify and group them more easily
 *
 * @return [array] start of queries that should be ignored.
 */
function hook_profiler_builder_extras_db_ignore() {
  // example from profiler_builder_extras
   $ignore_list = array(
    // ignore all select statements as they add nothing
    '__select'             => 'SELECT',
    // last user access is stupid to track
    '__update_user_access' => 'UPDATE users SET access'
  );
  // tables to ignore all update and insert statements
  $ignore_tables = array(
    'advagg_',
    'history',
    'cache',
    'queue',
    'search_',
    'semaphore',
    'sessions',
    'watchdog',
  );
  // build insert and update statements to ignore dynamically
  foreach ($ignore_tables as $table) {
    $ignore_list['insert_' . $table] = 'INSERT INTO ' . $table;
    $ignore_list['update_' . $table] = 'UPDATE ' . $table;
  }
}

/**
 * Implements hook_profiler_builder_extras_load_queries_alter().
 *
 * @param  [array] $queries queries with associated arguments to be assembled
 */
function hook_profiler_builder_extras_load_queries_alter(&$queries) {
  // use this to modify what queries get logged without all the logic in place
  // this could be useful if you had a specific type of query you wanted to
  // monitor such as only capturing variable changes or changes that modified
  // the roles that a user was granted.
}

/**
 * Implements hook_profiler_builder_extras_db_ignore_alter()
 * @param  [array] $list previously assembled array of things to ignore
 */
function hook_profiler_builder_extras_db_ignore_alter(&$list) {
  // example call because we don't want to ignore cache bins
  // this is a silly example, you'd never care about cache bins
  unset($list['insert_cache']);
  unset($list['update_cache']);
}
