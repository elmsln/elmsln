Introduction
============

Central Authentication Services (CAS) is a commonly used Single Sign-On
protocol used by many universities and large organizations. For a brief
introduction, please see the Jasig website: http://www.jasig.org/cas/about

The Drupal CAS project has two modules:

 * CAS:
     Drupal acts as a CAS client, allowing users to authenticate with a
     separate single sign-on CAS server.

 * CAS Server:
     Drupal acts as a CAS server.

Do NOT enable both modules at the same time, as it may lead to unpredictable
results.

The following README.txt covers the CAS module only. If you are interested in
the CAS Server module, please see README_SERVER.txt

Requirements
============
PHP 5 with the following extensions:
  curl, openssl, dom, zlib, and xml
phpCAS version 1.0.0 or later.

Installation
============

* Place the cas folder in your Drupal modules directory.

* Download phpCAS from https://wiki.jasig.org/display/CASC/phpCAS. You will
  need version 1.3.2 or later (1.3.3 for CAS 3.0 support). The most recent
  release is available at http://downloads.jasig.org/cas-clients/php/current.tgz

* There are several locations you can install the phpCAS library.

  1. Module directory installation. This means installing the library folder
     under the modules directory, so that the file
     sites/<site>/modules/cas/CAS/CAS.php exists.

  2. System wide installation. See the phpCAS installation guide, currently at
     https://wiki.jasig.org/display/CASC/phpCAS+installation+guide

  3. Libraries API installation. Install and enable the Libraries API module,
     available at http://drupal.org/project/libraries. Then extract phpCAS so
     that sites/<site>/libraries/CAS/CAS.php exists. For example:
       $ cd sites/all/libraries
       $ curl http://downloads.jasig.org/cas-clients/php/current.tgz | tar xz
       $ mv CAS-* CAS

* Go to Administer > Modules and enable this module.

* Go to Administer > Configuration > People > CAS to configure the CAS module.
  Depending on where and how you installed the phpCAS library, you may need
  to configure the path to CAS.php. The current library version will be
  displayed if the library is found.

Configuration & Workflow
========================

For the purposes of this example, assume the following configuration:
 * https://auth.example.com/cas - Your organization's CAS server
 * http://site.example.com/ - This Drupal site using the CAS module

Configure the CAS module:
 * Log in to the Drupal site and navigate to Admin > Configuration > People >
   Central Authentication Services.
 * Point the CAS module at the CAS server:
     - Hostname: auth.example.com
     - Port: 443
     - URI: /cas
 * Configure user accounts:
     - Decide if you want to automatically create Drupal user accounts for each
       CAS-authenticated user. If you leave this option deselected, you will
       have to manually add a paired Drupal account for every one of your users
       in advance.
     - Hide the Drupal password field if your users will never know (or need to
       know) their Drupal password.
 * Configure the login form(s):
     - There are four ways that a user can start the CAS authentication
       process:
         1. Visit http://site.example.com/cas
              This option is always available and is good for embedding a text
              "Login" link in your theme. (See the note to themers below).

         2. Click on a CAS Login menu link.
              The menu item is disabled by default, but may be enabled in
              Admin > Structure > Menus. You should find the link in the
              "Navigation" menu.

         3. Select the CAS login option on the Drupal login form.
              The CAS login option needs to be added to the login form in the
              CAS settings.

         4. Use the CAS login block.
              The CAS login block may be enabled in Admin > Structure > Blocks.

Note to Themers
===============

You may want to include a text CAS "Login" link in your theme. If you simply
link to "/cas", you will find that your users are redirected to the site
frontpage after they are authenticated. To redirect your users to the page
they were previously on, instead use:

  <?php
    print l(t('Login'), 'cas', array('query' => drupal_get_destination()));
  ?>

Upgrading from 6.x-2.x / Associating CAS usernames with Drupal users
=====================================================================

The following options have been depreciated:
* "Is Drupal also the CAS user repository?"
* "If Drupal is not the user repository, should CAS hijack users with the same name?"

The CAS module uses a lookup table (cas_user) to associate CAS usernames with
their corresponding Drupal user ids. The depreciated options bypassed this
lookup table and let users log in if their CAS username matched their Drupal
name. The update.php script has automatically inserted entries into the lookup
table so that your users will continue to be able to log in as before.

You can see the results of the update script and manage CAS usernames on the
"Administration >> People" (admin/people) page. A new column displays CAS
usernames, and the bulk operations drop-down includes options for rapidly
creating and removing CAS usernames. The "Create CAS username" option will
assign a CAS username to each selected account that matches their Drupal name.
The "Remove CAS usernames" option will remove all CAS usernames from the
selected accounts.

API Changes Since 6.x-2.x
=========================
The hooks hook_auth_name() and hook_auth_filter() were combined and renamed
to hook_cas_user_alter(). See cas.api.php.

Testing
=======
The CAS module comes with built-in test routines. To enable testing on a
development site, enable the 'Testing' module. Then navigate to Admin >
Configuration > Development > Testing. The CAS test routines are available
under "Central Authentication Service".

Note, the CAS test routines will automatically download phpCAS from the JASIG
website, to ensure a version compatible with the test routines, and so that
the tests may run successfully on qa.drupal.org.
