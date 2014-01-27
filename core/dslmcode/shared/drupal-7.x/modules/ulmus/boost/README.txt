
BOOST MODULE FOR DRUPAL 7.x
---------------------------

CONTENTS OF THIS README
-----------------------

   * Description
   * Requirements
   * Installation
   * Support
   * Credits

DESCRIPTION
-----------

This module provides static page caching for Drupal websites.

It provides a significant performance increase as well as
scalability for sites that receive mostly anonymous traffic.
Web pages load very fast from the cache instead of waiting on
PHP and Drupal to serve them from the database. If the page is
not found in the cache, then the request is passed to Drupal.

More information: http://drupal.org/project/boost

For information on supported features (as well as those deprecated
since 7.x-1.x), please read: https://drupal.org/node/1434362


REQUIREMENTS
------------

Drupal's clean URLs MUST be enabled and working properly.


INSTALLATION
------------

Handbook page: http://drupal.org/node/1459690

1. Goto: [Administer > Configuration > Search and metadata > Clean URLs]
   and ensure that Drupal's clean URLs are enabled and working correctly
   on your site.

2. Unzip and upload the module folder (as is) to the sites/all/modules
   folder in your Drupal installation directory.

3. Goto: [Administer > Configuration > Development > Performance] and disable
   the Drupal core cache for anonymous users. Boost will not be able to
   generate its cache if a page is already in the Drupal core cache.
   This is the only core setting you must disable, others can be left enabled.

4. Goto: [Administer > Configuration > System > Boost > Boost Settings]
   and review the default settings.

5. Goto: [Administer > Configuration > System > Boost > File System]
   Make sure that the cache directory is writeable by the web server:
   you may need to create the directory, and set the permissions.
   Ideally, the cache directory should be owned by your user and be in
   the group of your web server ("www-data" on Debian/Ubuntu), with a
   unix permission of 0775 (read/write/exec owner, read/write/exec group,
   read/exec others).

6. Review the other default Boost settings.

7. IMPORTANT - This step is easy and required for Boost to work!
   Backup the original .htaccess file from your Drupal installation
   directory for safe keeping.
   Copy the custom generated htaccess rule from [Administer > Configuration
     > System > Boost > .htaccess > .htaccess Generation] page and paste
   the rules into the Drupal htaccess file as shown below.

    # RewriteBase /
    -------paste the rules right here--------
    # Rewrite URLs of the form 'x' to the form 'index.php?q=x'.
    # Pass all requests not referring directly to files in the filesystem to
    # index.php. Clean URLs are handled in drupal_environment_initialize().
    RewriteCond %{REQUEST_FILENAME} !-f
    RewriteCond %{REQUEST_FILENAME} !-d
    RewriteCond %{REQUEST_URI} !=/favicon.ico
    RewriteRule ^ index.php [L]

Note: If you get "400 Bad Request" responses from Apache server, make sure you have configured the RewriteBase. For example when using VirtualHost configurations it is necessary to define as:

    RewriteBase /

For more information, please read the handbook page:
http://drupal.org/node/1459690


SUPPORT
-------

Project issue queue:
http://drupal.org/project/issues/boost

Please take the time to review other support issues before posting a new one.
It can be hard to debug boost support issues without access to the server.
Provide as much information as possible in order to reproduce the issue.

Feel free to post install tips in the installation handbook page:
https://drupal.org/node/1459690

Paid support is possible by contacting the module maintainers via their
user contact page (see below). We also accept donations, see:
https://drupal.org/node/1434362 (support section).


CREDITS
-------

4.7 Originally developed by Arto Bendiken.
5.x Port by Alexander I. Grafov, developed by Mike Carper.
6.x Port by Ben Lavender.
6.x Developed & Maintained by
  Mike Carper https://drupal.org/user/282446
  since 2012, minimal maintenance by Mathieu Lutfy
7.x Port by Mike Carper
7.x Developed & Maintained by
  Mike Carper (mikeytown2) https://drupal.org/user/282446
  Mathieu Lutfy (bgm) https://drupal.org/user/89461

