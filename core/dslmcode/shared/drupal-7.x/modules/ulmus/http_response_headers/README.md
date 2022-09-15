CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Recommended Modules
 * Installation
 * Configuration
 * Known Issues/Problems
 * Maintainers


INTRODUCTION
------------

The HTTP Response Headers module allows to set HTTP response headers (both
standard and non-standard) on pages by various visibility rule settings.
Currently, the headers can be set by path, content type and user role.

 * For a full description of the module, visit the project page:
   https://www.drupal.org/project/http_response_headers

 * To submit bug reports and feature suggestions, or to track changes:
   https://www.drupal.org/project/issues/http_response_headers


REQUIREMENTS
------------

This module requires no modules outside of Drupal core.


RECOMMENDED MODULES
-------------------

To export/import header rules from an inc file:
 * Ctools - https://www.drupal.org/project/ctools


INSTALLATION
------------

 * Install the HTTP Response Headers module as you would normally install a
   contributed Drupal module. Visit https://www.drupal.org/node/895232 for
   further information.


CONFIGURATION
-------------

    1. Navigate to Administration > Extend and enable the module and the HTTP
       Response Headers UI module.
    2. Navigate to Administration > Configuration > System > HTTP response
       headers for configurations.
    3. Select the "Settings" tab to enable and exclude headers. Save
       configuration.
    4. Select "List" to add a HTTP header. Save.

Use cases:
 * Case 1: Set 'Cache-Control' or 'Expires' header to set/reset cache behavior
   of browser/cache servers.
 * Case 2: Set 'X-Frame-Options' to restrict your pages rendering on a frame.
 * Case 3: Set 'WWW-Authenticate' to set authentication to pages.


KNOWN ISSUES/PROBLEMS
---------------------

 * The calculation for certain headers (e.g. Expires) happens internally and end
   user may not aware of it. So entering 600 in the expires header value change
   to ISO date format of 5 minutes from current time.
 * Doesn't work well with Drupal page cache.

MAINTAINERS
-----------

 * Vijaya Chandran Mani (vijaycs85) - https://www.drupal.org/u/vijaycs85
 * Minnur Yunusov (minnur) - https://www.drupal.org/u/minnur
 * Drew Webber (mcdruid) - https://www.drupal.org/u/mcdruid
 * Malachy McConnell (mmcconnell) - https://www.drupal.org/u/mmcconnell

Supporting organization:

 * Eurostar - https://www.drupal.org/eurostar
