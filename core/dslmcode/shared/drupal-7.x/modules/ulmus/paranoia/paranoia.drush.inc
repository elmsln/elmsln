<?php

/**
 * @file
 * Drush integration for the paranoia module.
 */

/**
 * Implements hook_drush_command().
 */
function paranoia_drush_sql_sync_sanitize($site) {
  // Don't use DBTNG here so this mostly workis across old versions of Drupal.
  drush_sql_register_post_sync_op('flood',
    dt('Delete all flood table entries (contains IP address and event).'),
    "TRUNCATE flood;");
  drush_sql_register_post_sync_op('sessions',
    dt('Delete all sessions table entries (contains IP address and potentially sensitive arbitrary session data).'),
    "TRUNCATE sessions;");
  // This next one is a bit harsh.
  // The intent is to remove things like API keys or credentials for services.
  drush_sql_register_post_sync_op('variable_keys',
    dt('Remove variables that contain names that indicate potential sensitive data.'),
    "DELETE FROM variable WHERE name LIKE '%key%' OR name LIKE '%token%';");
  drush_sql_register_post_sync_op('history',
    dt('Remove history, which contains info on where users have browsed on a site.'),
    "TRUNCATE history;");
  // Since people may not enable the dblog module, ensure it exists first.
  drupal_bootstrap(DRUPAL_BOOTSTRAP_VARIABLES);
  if (db_table_exists('watchdog')) {
    drush_sql_register_post_sync_op('watchdog',
      dt('Watchdog usually contains user id, IP, e-mail addresses, filesystem paths.'),
      "TRUNCATE watchdog;");
  }
  drush_sql_register_post_sync_op('authmap',
    dt('Authmap correlates Drupal accounts to external services. The map may contain private data like emails.'),
    "TRUNCATE authmap;");
  drush_sql_register_post_sync_op('users_data',
    dt('The magical fairy puts a lot of junk into users.data. We cannot trust it to be only non-sensitive data. Dang magic.'),
    "UPDATE users SET data = '';");
  // Make the purging inactive users optional.
  if (variable_get('paranoia_delete_blocked_users', 1)) {
    drush_sql_register_post_sync_op('users_blocked',
      dt('Blocked user accounts may contain inappropriate information and are not accessible to the public in general.'),
      "DELETE FROM users WHERE status <> 1 AND uid NOT IN (0, 1);");
    drush_sql_register_post_sync_op('users_blocked_roles',
      dt('Blocked users were deleted, now lets delete their associated roles.'),
      "DELETE users_roles FROM users_roles LEFT JOIN users ON users_roles.uid = users.uid WHERE users.uid IS NULL;");
  }
  drush_sql_register_post_sync_op('email-in-username',
    dt('Sanitize email-based names in user table'),
    "UPDATE users SET name = uid WHERE name LIKE '%@%';");
  drush_sql_register_post_sync_op('cron-key',
    dt('Reset cron key'),
    "UPDATE variable SET value = NULL WHERE name = 'cron_key';");

  // Truncate core cache tables.
  $cache_tables = array(
    'cache',
    'cache_page',
    'cache_bootstrap',
    'cache_field',
    'cache_filter',
    'cache_form',
    'cache_menu',
    'cache_path',
  );
  if (db_table_exists('cache_block')) {
    $cache_tables[] = 'cache_block';
  }
  if (db_table_exists('cache_update')) {
    $cache_tables[] = 'cache_update';
  }
  $trucate_caches_query = implode(';', preg_filter('/^/', 'TRUNCATE ', $cache_tables)) . ';';
  drush_sql_register_post_sync_op('core_cache_tables',
    dt('Truncate core cache tables.'),
    $trucate_caches_query);
}
