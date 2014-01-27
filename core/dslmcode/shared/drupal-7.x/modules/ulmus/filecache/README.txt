-*- mode: org -*- in Emacs

* Introduction

This modules allows Drupal caches to be stored in files instead of
storing in database.

* Comparison with other caching modules

Built-in Drupal cache uses database backend.  There is one SQL query
for each accessed cache entry.  This is much slower than simple file
access as used by filecache module.  

memcache module is the closest caching module. File Cache can be
configured to use memory filesystem (e.g. /dev/shm in Debian) which is
very close to what memcache does. File Cache can use network
filesystems and this is another use case where memcache is
traditionally used.

apc module can be used for cache bins too. If it's used for that purpose,
it's usually only for some of the small cache bins like cache and
cache_bootstrap.

boost module generates caches of pages that are directly served by web
server. File Cache can plug in regular Drupal page caching and provide
very fast page caching but this still needs a bit of PHP to be
executed. Database access can be avoided altogether though. See
$conf['filecache_fast_pagecache'] below.

Drupal 7 allows using different caching module for different cache
bins, e.g. using apc module for cache and cache_bootstrap bins and
filecache for everything else.

* Feedback

Benchmark results in real scenarios are needed in comparison against
memcache, apc and boost. If you have such experience, please share
with File Cache maintainer 'ogi' (Ognyan Kulev). Numbers in
comparison with memcache against File Cache on memory filesystem are
especially important.

* Quick Installation when web server is Apache

Install and enable filecache module as usual, e.g. by placing unpacked
filecache directory in sites/all/modules and enabling the module in
admin/modules. Detailed information can be found in
http://drupal.org/documentation/install/modules-themes/modules-7

File Cache needs directory that is not accessible through web
server. When Apache is used, Drupal's .htaccess file protects all
files and directories that begin with ".ht" and File Cache can
automatically and safely create a File Cache directory. In this case,
adding the following lines to "settings.php" is enough for basic
operation.

$conf['cache_backends'] = array('sites/all/modules/filecache/filecache.inc');
$conf['cache_default_class'] = 'DrupalFileCache';

* Installation when web server is not Apache

If Apache is not used, File Cache directory must be provided in
"settings.php" by setting "filecache_directory" configuration
variable. This directory must be writable by Drupal and must not be
accessible through web server. If it doesn't exist, File Cache tries
to create it.

File Cache checks if provided directory is writable but doesn't check
if it's not accessible through web server. You must do this check
yourself.

Directory may be relative to Drupal root directory.

Here is a example of a simple configuration that works for multi-site
deployment. conf_path() always returns "sites/SITENAME" and this is
used to retrieve SITENAME. File Cache creates directory if it doesn't
exist and there should be no problem with permissions since it's in
/tmp.

$conf['cache_backends'] = array('sites/all/modules/filecache/filecache.inc');
$conf['cache_default_class'] = 'DrupalFileCache';
$conf['filecache_directory'] = '/tmp/filecache-' . substr(conf_path(), 6);

* NOT IMPLEMENTED YET: filecache_fast_pagecache

 #$conf['filecache_fast_pagecache'] = TRUE;

In the suggested lines for settings.php above, there's a commented
line for enabling pagecache support in filecache. To use it, just
remove the '#' character.

This mode of operation allows Drupal to serve cached pages without
accessing the database at all. The precise operation when
filecache_fast_pagecache is enabled is as follows:

1. Load cid 'variables' in bin 'cache' into $variables. If it doesn't
exist, no further action is taken.
2. Set the following $conf variables. Each variable is set only if
it's unset:
$conf['page_cache_without_database'] = TRUE;
$conf['page_cache_invoke_hooks'] = FALSE;
$conf['page_cache_maximum_age'] = $variables['page_cache_maximum_age'];
$conf['cache_lifetime'] = $variables['cache_lifetime'];
$conf['page_compression'] = $variables['page_compression'];

* Procedure for setting and getting cache entries

Each cache object is stored in a separate file. File name is
concatenated cache bin name, '-' character, and urlencode()-like
encoded cid. Written in code, it's "$cachebin-$urlencodedcid". File
content is serialized stdClass exactly as returned by cache_get(),
i.e. stdClass with properties cid, created, expire and data.

cache_set uses the following sequence of operations on file that
contains cache object:

1. take exclusive lock
2. truncate to zero size
3. write new file content
4. release exclusive lock

cache_get is designed to be as fast as possible. It just tries to read
serialized content. If content cannot be unserialized, then some other
page request is running cache_set. (From truncation of file to
completing write of new file content, the content of the file is
unserializable.) In this case, shared lock on file is taken before
reading serialized content. If this second time fails again, it's not
because cache_set is interfering and so broken file is removed.

* NOT IMPLEMENTED: Replacement for includes/session.inc

Using File Cache for storing sessions.

* Security Considerations

Usually filecache cleans its cache with credentials of web server.
When using Drush and the latter tries to clean cache, this operation
is run with user's credentials that are generally different than web
server's credentials.  For this reason, filecache creates all files
and directories with read/write permissions for all.
