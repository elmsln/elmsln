README.txt for Devel module
---------------------------

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Included Modules and Features
 * Recommended Modules
 * Installation
 * Compatibility Notes
 * Maintainers

INTRODUCTION
------------

A module containing helper functions for Drupal developers and inquisitive
admins. This module can print a log of all database queries for each page
request at the bottom of each page. The summary includes how many times each
query was executed on a page, and how long each query took.

 - For a full description of the module visit:
   https://www.drupal.org/project/devel

 - To submit bug reports and feature suggestions, or to track changes visit:
   https://www.drupal.org/project/issues/devel

It also offers
 - a block for running custom PHP on a page
 - a block for quickly accessing devel pages
 - a block for masquerading as other users (useful for testing)
 - reports memory usage at bottom of page
 - A mail-system class which redirects outbound email to files
 - more

This module is safe to use on a production site. Just be sure to only grant
'access development information' permission to developers.

Also a dpr() function is provided, which pretty prints arrays and strings.
Useful during development. Many other nice functions like dpm(), dvm().

AJAX developers in particular ought to install FirePHP Core from
http://www.firephp.org/ and put it in the devel directory. You may use the
devel-download drush command to download the library. If downloading by hand,
your path to fb.php should look like
devel/FirePHPCore/lib/FirePHPCore/fb.php. You can use svn checkout
http://firephp.googlecode.com/svn/trunk/trunk/Libraries/FirePHPCore.
Then you can log php variables to the Firebug console. Is quite useful.


REQUIREMENTS
------------

This module requires no modules outside of Drupal core.


INCLUDED MODULES AND FEATURES
-----------------------------

Included in this package is also:

 - Devel Node Access module - Prints out the node_access records for a given
   node. Also offers hook_node_access_explain for all node access modules to
   implement. Handy.
 - Devel Generate module - Bulk creates nodes, users, comment, terms for
   development.

Some nifty drush integration ships with Devel and Devel Generate. See drush help
for details.

DRUSH UNIT TEST - See develDrushTest.php for an example of unit testing of the
Drush integration. This uses Drush's own test framework, based on PHPUnit. To
run the tests, use
phpunit --bootstrap=/path/to/drush/tests/drush_testcase.inc. Note that we must
name a file under /tests there.


RECOMMENDED MODULE
------------------

Devel Generate Extensions - Devel Images Provider allows to configure external
providers for images.

 - http://drupal.org/project/devel_image_provider


INSTALLATION
------------

 - Install the Devel module as you would normally install a contributed Drupal
   module. Visit https://www.drupal.org/node/895232 for further information.


COMPATIBILITY NOTES
-------------------

- Modules that use AHAH may have incompatibility with the query log and other
  footer info. Consider setting $GLOBALS['devel_shutdown'] = FALSE if you run
  into any issues.


AUTHOR/MAINTAINER
-----------------

 - Moshe Weitzman (moshe weitzman) - https://www.drupal.org/u/moshe-weitzman
 - Hans Salvisberg (salvis) - https://www.drupal.org/u/salvis
