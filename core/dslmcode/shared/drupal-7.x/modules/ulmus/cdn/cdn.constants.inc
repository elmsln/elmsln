<?php

/**
 * @file
 * Constants used by the CDN module.
 */


define('CDN_DISABLED', 0);
define('CDN_TESTING', 1);
define('CDN_ENABLED', 2);

// Permissions.
define('CDN_PERM_ACCESS_STATS',   'access per-page statistics');
define('CDN_PERM_ACCESS_TESTING', 'access files on CDN when in testing mode');
define('CDN_PERM_TOUCH',          'touch files');
define('CDN_PERM_ADMIN',          'administer CDN configuration');

// Variables and values.
define('CDN_MODE_VARIABLE', 'cdn_mode');
define('CDN_MODE_BASIC', 'basic');
define('CDN_MODE_ADVANCED', 'advanced');
define('CDN_STATUS_VARIABLE', 'cdn_status');
define('CDN_STATS_VARIABLE', 'cdn_stats');
define('CDN_DRUPAL_ROOT_VARIABLE', 'cdn_drupal_root');
define('CDN_HTTPS_SUPPORT_VARIABLE', 'cdn_https_support');
define('CDN_PICK_SERVER_PHP_CODE_VARIABLE', 'CDN_PICK_SERVER_PHP_CODE_VARIABLE');

// Variables for exceptions.
define('CDN_EXCEPTION_FILE_PATH_BLACKLIST_VARIABLE', 'cdn_exception_file_path_blacklist');
define('CDN_EXCEPTION_FILE_PATH_BLACKLIST_DEFAULT',  "");
define('CDN_EXCEPTION_FILE_PATH_WHITELIST_VARIABLE', 'cdn_exception_file_path_whitelist');
define('CDN_EXCEPTION_FILE_PATH_WHITELIST_DEFAULT',  "misc/*.js\nmodules/*.js");
define('CDN_EXCEPTION_DRUPAL_PATH_BLACKLIST_VARIABLE', 'cdn_exception_drupal_path_blacklist');
define('CDN_EXCEPTION_DRUPAL_PATH_BLACKLIST_DEFAULT',  '');
define('CDN_EXCEPTION_AUTH_USERS_BLACKLIST_VARIABLE', 'cdn_exception_auth_users_blacklist');
define('CDN_EXCEPTION_AUTH_USERS_BLACKLIST_DEFAULT', 'admin*');

// Variables for basic mode.
define('CDN_BASIC_MAPPING_VARIABLE', 'cdn_basic_mapping');
define('CDN_BASIC_MAPPING_HTTPS_VARIABLE', 'cdn_basic_mapping_https');
define('CDN_BASIC_FARFUTURE_VARIABLE', 'cdn_farfuture_status');
define('CDN_BASIC_FARFUTURE_DEFAULT', FALSE);
define('CDN_BASIC_FARFUTURE_EXTENSIONS_VARIABLE', "cdn_farfuture_extensions");
define('CDN_BASIC_FARFUTURE_EXTENSIONS_DEFAULT', "css\njs\nsvg\nico\ngif\njpg\njpeg\npng\notf\nttf\neot\nwoff\nflv\nswf");
define('CDN_BASIC_FARFUTURE_GZIP_EXTENSIONS', "css\njs\nico\nsvg\neot\notf\nttf");
define('CDN_BASIC_FARFUTURE_GZIP_DIRECTORY', "cdn/farfuture/gzip");
define('CDN_BASIC_FARFUTURE_REMOVE_HEADERS', "Set-Cookie\nETag");
define('CDN_BASIC_FARFUTURE_UNIQUE_IDENTIFIER_MAPPING_VARIABLE', 'cdn_farfuture_unique_identifier_mapping');
define('CDN_BASIC_FARFUTURE_UNIQUE_IDENTIFIER_MAPPING_DEFAULT', "misc/*:modules/*:themes/*|drupal_version\nsites/*|mtime\nsites/*|.avi .m4v .mov .mp4 .wmv .flv|perpetual");
define('CDN_BASIC_FARFUTURE_UNIQUE_IDENTIFIER_DEFAULT', 'mtime');

// Variables for advanced mode.
define('CDN_ADVANCED_PID_FILE_VARIABLE', 'cdn_advanced_pid_file');
define('CDN_ADVANCED_SYNCED_FILES_DB_VARIABLE', 'cdn_advanced_synced_files_db');

// Hardcoded settings for accessing the daemon's metadata, to show statistics.
define('CDN_DAEMON_SYNCED_FILES_DB', 'synced_files.db');
define('CDN_DAEMON_PERSISTENT_DATA_DB', 'persistent_data.db');
define('CDN_DAEMON_FSMONITOR_DB', 'fsmonitor.db');
