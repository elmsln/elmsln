
------------------------------------------
Asynchronous Prefetch Database Query Cache
------------------------------------------


CONTENTS OF THIS FILE
---------------------

 - Requirements
 - Installation
 - Features & benefits
 - Configuration
 - Troubleshooting


REQUIREMENTS
------------

 - MySQL 5.5+
 - mysqlnd Driver
 - PHP 5.3+


INSTALLATION
------------

The quick and easy way to set this up is to install the module and go to the
status report page `admin/reports/status`. Works with MySQL only at this point.

Below is what you'll typically need to add to your settings.php file.

    $databases['default']['default']['init_commands']['isolation'] = "SET SESSION tx_isolation='READ-COMMITTED'";
    $databases['default']['default']['init_commands']['lock_wait_timeout'] = "SET SESSION innodb_lock_wait_timeout = 20";
    $databases['default']['default']['init_commands']['wait_timeout'] = "SET SESSION wait_timeout = 600";
    $conf['cache_backends'][] = 'sites/all/modules/apdqc/apdqc.cache.inc';
    $conf['cache_default_class'] = 'APDQCache';
    $conf['lock_inc'] = 'sites/all/modules/apdqc/apdqc.lock.inc';
    $conf['session_inc'] = 'sites/all/modules/apdqc/apdqc.session.inc';

If you are using memcache or apcu then using the status report page is
recommended.


FEATURES & BENEFITS
-------------------

 - Eliminates deadlocks & metadata locks for all cache tables.
 - Faster page load times for logged in and anonymous users due to cache
   prefetching.
 - Outputs query information to the devel query log. Will output prefetch info
   as well.
 - Better handing of the minimum cache lifetime; does smarter garbage collection
   of the cache bins. Purges caches based on individual records' timestamps
   instead of just using the expire column, the created column is used as well.
 - Changes the collation of cache tables to utf8_bin. Using the utf8_bin
   collation is faster and more accurate when matching cache ids since no
   unicode normalization is done to cache query conditions. D8 backport.
 - Changes the semaphore table to use the MEMORY engine if using MySQL 5.5 or
   lower. This will speed up writes to the lock table for older versions of
   MySQL.


CONFIGURATION
-------------

Settings page is located at:
`admin/config/development/performance/apdqc`

**Global Options**

 - Cache garbage collection frequency: The frequency with which cache bins are
   cleared on cron.
 - Prefetch cached data: Control prefetching of cache items.
 - Devel - Output prefetch info from apdqc: Display prefetch info in the devel
   query log output.

**Operations page**

Located at `admin/config/development/performance/apdqc/operations`. This is a
collection of things to do for the semaphore & cache tables; better optimizing
them. There are no configuration options here.
 - Convert semaphore table: Convert the table to use InnoDB or MEMORY depending
   on the version of MySQL installed.
 - Convert cache tables collations: Using the utf8_bin collation is faster and
   more accurate when matching cache ids since no unicode normalization is done
   to cache queries

**Hidden Settings**

The following settings are not configurable from the admin UI and must be set in
settings.php. In general they are settings that should not be changed. The
current defaults are shown.

    // If TRUE run DELETE instead of TRUNCATE on all cache bins.
    $conf['cache_no_truncate'] = FALSE;

    // If FALSE do not prefetch the cache_bootstrap cache bin.
    $conf['cache_bootstrap_prefetch'] = TRUE;

    // If TRUE call apdqc_cache_clear_alter() & apdqc_cache_clear() on cc.
    $conf['apdqc_call_hook_on_clear'] = FALSE;

    // If TRUE use _apdqc_dblog_watchdog instead of dblog_watchdog.
    $conf['apdqc_dblog_watchdog'] = TRUE;


TROUBLESHOOTING
---------------

Fix all APDQC warnings and errors on the status report page
`admin/reports/status`. You might need to install the mysqlnd extension.

Disable prefetching on the `admin/config/development/performance/apdqc` page.

If you are having issues be sure to report it here:
`https://www.drupal.org/node/add/project-issue/apdqc`
