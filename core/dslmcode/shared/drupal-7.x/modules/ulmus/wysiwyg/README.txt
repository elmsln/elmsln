CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Configuration
 * Support requests
 * Maintainers


INTRODUCTION
------------

Wysiwyg API allows users of your site to use WYSIWYG/rich-text,
and other client-side editors for editing contents. This module
depends on third-party editor libraries, most often based on JavaScript.

For a full description of the module, visit the project page:
https://drupal.org/project/wysiwyg


INSTALLATION
------------

 * Install as usual, see
   https://drupal.org/documentation/install/modules-themes/modules-7

 * Go to Administration » Configuration » Content authoring » Wysiwyg,
   and follow the displayed installation instructions to download and install one
   of the supported editors.


CONFIGURATION
-------------

 * Go to Administration » Configuration » Content authoring » Text formats, and

   - either configure the Full HTML format, assign it to trusted roles, and
     disable "Limit allowed HTML tags", "Convert line breaks...", and
     (optionally) "Convert URLs into links".
     Note that disabling "Limit allowed HTML tags" will allow users to post
     anything, including potentially malicious content. For a more configurable
     alternative to "Limit allowed HTML tags" try
     https://drupal.org/project/wysiwyg_filter.

   - or add a new text format, assign it to trusted roles, and ensure that above
     mentioned input filters are configured as detailed.

 * Setup editor profiles in Administration » Configuration » Content authoring
   » Wysiwyg.


SUPPORT REQUESTS
----------------

Before posting a support request, carefully read the installation
instructions provided in module documentation page.

Before posting a support request, check Recent log entries at
admin/reports/dblog

Once you have done this, you can post a support request at module issue queue:
https://drupal.org/project/issues/wysiwyg

When posting a support request, please inform if you were able to see any errors
at admin/reports/dblog in Recent log entries.


MAINTAINERS
-----------

Current maintainers:
 * Daniel F. Kudwien (sun) - https://drupal.org/user/54136
 * Henrik Danielsson (TwoD) - https://drupal.org/user/244227

This project has been sponsored by:
 * UNLEASHED MIND
   Specialized in consulting and planning of Drupal powered sites, UNLEASHED
   MIND offers installation, development, theming, customization, and hosting
   to get you started. Visit http://www.unleashedmind.com for more information.
