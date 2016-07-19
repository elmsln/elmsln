Node.js integration
===================

This module adds Node.js integration to Drupal.

Setup
=====

1. Install drupal-node.js packge with npm:

    npm install drupal-node.js

Make sure to do this outside of your Drupal modules directory, else Drupal may
try to process folders containing Node.js module information and fail. Follow
the install instructions in the drupal-node.js NPM package. You will need to
provide the hostname and port of your Drupal site to the Node.js process, and
ensure that the service token matches between Drupal and Node.js.

2. Point Drupal at the Node.js server process, either using the configuration
page or settings.php.

To use the configuration page, visit '/admin/config/nodejs/settings', and enter
the appropriate values.

To use your settings file, edit settings.php to add:

    $conf['nodejs_config'] = [
      // Configuration values here. See nodejs_get_config() function
      // for the values you can override.
    ];

3. Visit the reports page to validate that Drupal can communicate successfully
with the Node.js server process.

