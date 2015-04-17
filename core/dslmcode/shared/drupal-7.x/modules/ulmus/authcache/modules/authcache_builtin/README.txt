Authcache backend for drupal built-in cache system
==================================================

Installation
------------

1. Enable authcache and authcache_bultin module.

2. Setup a Drupal cache handler module (optional, but strongly recommended for
   vastly improved performance)

   Download and enable a cache handler module, such as:

   - Memcache API: http://drupal.org/project/memcache
   - Filecache: http://drupal.org/project/filecache
   - Redis: http://drupal.org/project/redis
   - Mongodb: http://drupal.org/project/mongodb

3. Open your settings.php file and configure the cache backends.

   Here are some examples:

   BUILTIN DATABASE CACHE:

     $conf['cache_backends'][] = 'sites/all/modules/authcache/authcache.cache.inc';
     $conf['cache_backends'][] = 'sites/all/modules/authcache/modules/authcache_builtin/authcache_builtin.cache.inc';

     // Optional: Force database cache if you have other cache classes in
     // place for other cache bins:
     $conf['cache_class_cache_page'] = 'DrupalDatabaseCache';

   MEMCACHE MODULE:

     $conf['memcache_servers']  = array('localhost:11211' => 'default');

     $conf['cache_backends'][] = 'sites/all/modules/memcache/memcache.inc';
     $conf['cache_backends'][] = 'sites/all/modules/authcache/authcache.cache.inc';
     $conf['cache_backends'][] = 'sites/all/modules/authcache/modules/authcache_builtin/authcache_builtin.cache.inc';
     $conf['cache_class_cache_page'] = 'MemCacheDrupal';


   FILECACHE MODULE:

     $conf['cache_backends'][] = 'sites/all/modules/filecache/filecache.inc';
     $conf['cache_backends'][] = 'sites/all/modules/authcache/authcache.cache.inc';
     $conf['cache_backends'][] = 'sites/all/modules/authcache/modules/authcache_builtin/authcache_builtin.cache.inc';
     $conf['cache_class_cache_page'] = 'DrupalFileCache';

   If no cache handler is setup or defined, Authcache will fall back to Drupal
   core database cache tables and "Authcache Debug" will say "Cache Class:
   DrupalDatabaseCache".

   If you are experimenting with multiple caching systems (db, apc, memcache),
   make sure to clear the cache each time you switch to remove stale data.

4. (Optional) If a third-party cache-class is in place it is possible to avoid
   hitting the database completely. Add the following line to settings.php:

   $conf['authcache_builtin_cache_without_database'] = TRUE;

   Please note that it is necessary to hard-code all the settings affecting
   delivery of cached pages in settings.php in that case.

5. (Optional) Install and setup the Cache Expiration module allowing finer
   grained control over which pages are should be purged from cache whenever
   new content is submitted. In order to work properly, the Authcache Enum
   module also needs to be activated.
   Cache Expiration Module: https://drupal.org/project/expire
