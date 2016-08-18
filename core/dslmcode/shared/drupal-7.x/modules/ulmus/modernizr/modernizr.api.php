<?php

/**
 * @file
 * Hooks provided by the Modernizr module
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Registers a Modernizr dependency.
 *
 * This hook will not alter the production output of the module whatsoever.
 * Its purpose is to tell the Drupal module which options are necessary if
 * another Modernizr custom build is downloaded using the admin UI.
 *
 * Currently, you must visit the admin page for Modernizr and click the button
 * in the admin UI to fetch the custom build. Future versions of the module will
 * integrate with the node.js builder, allowing drush to generate a properly
 * equipped Modernizr custom build.
 *
 * The module implements this function itself so feel free to look at
 * modernizr_modernizr_info() for another example.
 *
 * @return
 *   An array of options that specify Modernizr custom build requirements.
 */
function hook_modernizr_info() {
  $tests = array();

  //
  // The index of each entry MUST be the exact string needed in whatever
  // version of modernizr.js you're using. These strings are not arbitrary.
  // This Drupal module will always support the latest stable version of
  // Modernizr and nothing else.
  //

  // Specify feature tests.
  $tests[] = 'borderradius';

  return $tests;
}

/**
 * Registers a Modernizr.load() testObject.
 *
 * Modernizr.load() is actually a standalone library called yepnope.js
 * which is included in Modernizr custom builder. This hook aims to
 * offer 1:1 feature parity with yepnope.js - current version: 1.5
 *
 * Learn how all of these properties interact with Modernizr.load()
 * on the yepnope website: http://yepnopejs.com/#testObject
 *
 * @return
 *   An array to be output as yepnope testObjects.
 */
function hook_modernizr_load() {
  $load = array();

  // Unlike hook_modernizr_info(), no array index is needed.
  // You can add as many Modernizr.load() commands as you want
  $load[] = array(
    // The 'test' property determines which resources get downloaded.
    // Your test can be *any* truthy JavaScript expression; you are NOT
    // limited to Modernizr properties. You can combine tests like so:
    //
    // - Modernizr.borderradius && Modernizr.csstransforms3d
    //
    //   This test requires the user's browser to support both border-radius
    //   and CSS 3D transforms.
    //
    // - Modernizr.mq('only screen and (min-width: 400px)') || !!respond
    //
    //   This test requires the browser to support CSS3 media queries
    //   and have a window width of at least 400px or have access to
    //   the object provided by respond.js, a different JavaScript library
    //   which gives old browsers a minimal ability to eval min- and
    //   max-width media queries.
    //
    // Test the user's browser for border-radius support.
    'test' => 'Modernizr.borderradius',

    // If the test PASSES load these files. Example shows a hardcoded path.
    'yep'  => array('/css/radius.css'),

    // If the test FAILS load these files. Example shows a Drupal path (don't
    // forget opening slash, or it won't work except at your site root)
    'nope' => array('/' . drupal_get_path('module', 'modernizr') . '/fake/path/to/radius.css'),

    // These resources will always load regardless of the test results.
    // 'load' and 'both' offer the exact same functionality.
    'both' => array('/always/loaded.js'),
    'load' => array('/always/loaded.js'),

    // Each JavaScript callback should be enclosed inside an anonymous function.
    // Take care to format correctly. You can provide an array of functions that
    // should match the number of items in your yep or nope properties.
    'callback' => array('function(){console.log("If you can see this, a Modernizr.load() individual callback was fired.")}'),

    // The final 'complete' callback requires an anonymous JavaScript function.
    // Take care to format correctly. Despite being inside an array, you should
    // only add one function.
    'complete' => array('function(){console.log("If you can see this, the Modernizr.load() complete callback was fired.")}'),
  );

  return $load;
}

/**
 * @} End of "addtogroup hooks".
 */
