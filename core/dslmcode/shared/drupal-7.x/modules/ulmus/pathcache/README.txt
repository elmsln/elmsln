The Path Cache module stores paths in a cache so that Drupal does not have
to look them up from the database.

If you want to use this module, use memcached or another memory-based caching
backend. It will still work if your caching backend is not memcached (Drupal's 
default caching backend is MySQL) but it will actually make things slower.

STEP ONE: Make sure memcached (the Unix daemons) are working. See, for example:

http://www.lullabot.com/articles/how_install_memcache_debian_etch
http://www.lullabot.com/articles/setup-memcached-mamp-sandbox-environment

STEP TWO: Make sure the Memcache API and Integration stuff is set up. See

http://drupal.org/project/memcache

STEP THREE: Create two memcached bins named pathdst and pathsrc. A sample 
configuration for settings.php is shown below. Note this configuration
contains some other bins too.

$conf = array(
  // Enable memcache caching backend.
  'cache_inc' => './sites/all/modules/memcache/memcache.inc',
  // Enable memcached-based sessions.
  'session_inc' => './sites/all/modules/memcache/memcache-session.inc',
  'memcache_servers' => array(
    'localhost:11211' => 'default',
    'localhost:11212' => 'filter',
    'localhost:11213' => 'menu',
    'localhost:11214' => 'page',
    'localhost:11215' => 'session',
    'localhost:11216' => 'users',
    'localhost:11217' => 'pathdst',
    'localhost:11218' => 'pathsrc',
  ),
  'memcache_bins' => array(
    'cache' => 'default',
    'cache_filter' => 'filter',
    'cache_menu' => 'menu',
    'cache_page' => 'page',
    'session' => 'session',
    'users' => 'users',
    'cache_pathdst' => 'pathdst',
    'cache_pathsrc' => 'pathsrc',
  ),
);

STEP FOUR: Make sure memcached daemons are actually running on the ports
you assigned. At the command line:

ps aux | grep memc

STEP FIVE: Switch path_inc to use the one provided by this module:

$conf['path_inc'] = './sites/all/modules/contrib/pathcache/path.inc';

STEP SIX: Enable pathcache.module. All the module does is make sure that
the path caches get cleared when someone clicks the Clear cached data button
on the Administer -> Site configuration -> Performance page.

PERFORMANCE

The sites with the most to gain from path caching in memcache are sites that
have many path aliases, and a very busy database. Every cache hit in memcache
is one query that the database does not have to handle. Obviously every site
is different and you'll need to test to make sure that this module actually
improves things instead of making them worse.
