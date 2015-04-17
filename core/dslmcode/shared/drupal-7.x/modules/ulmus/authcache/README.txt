
===========================================
Authenticated User Page Caching (Authcache)
===========================================

The Authcache module offers page caching for both anonymous users and logged-in
authenticated users. This allows Drupal/PHP to spend only 1-2 milliseconds
serving pages and greatly reduces server resources.

Please visit:

  http://drupal.org/project/authcache

For information, updates, configuration help, and support.

Please note that authcache requires at least Drupal 7.24.

============
Installation
============

1. Enable the authcache module along with one of the modules providing a cache
   backend. Currently those include:
   - authcache_builtin: Cache backend for the drupal core cache system. Also
     choose that one when using a third party cache like memcache.
   - authcache_varnish: Use varnish as the cache backend.
   - authcache_boost (experimental): Use boost as the cache backend.

   All of those cache backends need to be configured properly. Please read and
   follow the instructions given in the respective README.txt files.

2. Enable all authcache submodules providing support for enabled core and
   contrib modules like "Authcache Poll" if you are using the "Poll" module or
   "Authcache Forum" if the "Forum" module is active. Note: Some functionality
   is only enabled when the Personalization API is enabled.

3. Goto Configuration > Development > Performance and disable page caching for
   anonymous users.

4. Goto Configuration > System > Authcache and specify the cacheable user roles.

5. Modify your theme by tweaking user-customized elements (the final HTML
   must be the same for each user role). Use hook_preprocess to replace user
   specific content with <span>-tags which you can address using JavaScript.
   See the numerous examples in the modules and example directories.

=================
CACHE FLUSH NOTES
=================

Page cache is cleared when cron.php is executed. This is normal Drupal core
behavior. Using the Elysia Cron module it is possible to suppress overzealous
cache clearing by running system_cron on a slower pace than other cron jobs.

See:
  -- Elysia Cron @ http://drupal.org/project/elysia_cron

========================
Authcache Example Module
========================

Please review the examples in the modules and example directories for a
demonstration on how to alter the behavior of other modules such that their
output becomes cacheable for logged in users.

======
Author
======

Developed & maintained by Jonah Ellison.

Email: jonah [at] httpremix.com
Drupal: http://drupal.org/user/217669

Initial D7 port by Simon Gardner
Email: slgard@gmail.com
Drupal: http://drupal.org/user/620692

Version 7.x-2.x by Lorenz Schori
Drupal: http://drupal.org/user/63999

================
Credits / Thanks
================

- "Cache Router" module (Steve Rude) for the caching system/API
- "Boost" module (Arto Bendiken) for some minor code & techniques
