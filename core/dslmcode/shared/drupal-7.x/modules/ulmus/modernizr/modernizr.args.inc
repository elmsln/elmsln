<?php
/**
 * @file
 *   An up-to-date list of Modernizr custom build args
 *   and the way in which they affect Modernizr. This
 *   file is the glue that makes the drush command for
 *   custom builds possible.
 */
function _modernizr_args_return($name) {

  $modernizr_args = array(

    // Tests
    'applicationcache' => array(
      'type' => 'tests',
      'desc' => 'Browser cache layer that allows for offline usage of web applications.',
    ),
    'audio' => array(
      'type' => 'tests',
      'desc' => 'Built-in audio support using <code>&lt;audio></code>.',
    ),
    'borderradius' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows for rounded corners.',
    ),
    'boxshadow' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows for drop-shadows around an element.',
    ),
    'backgroundsize' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows a background image to resize based on its container.',
    ),
    'borderimage' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows for image-based borders around elements.',
    ),
    'canvas' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows for dynamic, scriptable rendering of 2D shapes and bitmap images.',
    ),
    'canvastext' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows for text effects within <code>&lt;canvas></code>.',
    ),
    'cssanimations' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows for keyframe-based animations.',
    ),
    'csscolumns' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows elements to be formatted in columns.',
    ),
    'cssgradients' => array(
      'type' => 'tests',
      'desc' => 'CSS property that creates vector-based background gradients.',
    ),
    'cssreflections' => array(
      'type' => 'tests',
      'desc' => 'CSS property that creates a "reflection" below the element.',
    ),
    'csstransforms' => array(
      'type' => 'tests',
      'desc' => 'CSS properties that allow elements to be moved or rotated in 2D space.',
    ),
    'csstransforms3d' => array(
      'type' => 'tests',
      'desc' => 'CSS properties that allow elements to be moved or rotated in 3D space.',
    ),
    'csstransitions' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allow other CSS properties to smoothly tween between two values.',
    ),
    'draganddrop' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows elements to be moved with the user\'s cursor.',
    ),
    'flexbox' => array(
      'type' => 'tests',
      'desc' => 'CSS properties that allow for advanced, content-independent layouts.',
    ),
    'flexboxlegacy' => array(
      'type' => 'tests',
      'desc' => 'An old version of the CSS properties that allow for advanced, content-independent layouts.',
    ),
    'fontface' => array(
      'type' => 'tests',
      'desc' => 'CSS properties that allow use of web fonts.',
    ),
    'generatedcontent' => array(
      'type' => 'tests',
      'desc' => 'CSS properties that allow CSS to generate presentational content.',
    ),
    'geolocation' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows the browser to determine its physical location.',
    ),
    'hashchange' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that provides an event listener for changes to <code>window.location.hash</code>.',
    ),
    'history' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows <code>window.location</code> to be updated dynamically.',
    ),
    'hsla' => array(
      'type' => 'tests',
      'desc' => 'CSS value that allows colors to be specified in terms of hue, saturation, lightness, and alpha.',
    ),
    'indexeddb' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows access to a local database which supports indexing.',
    ),
    'inlinesvg' => array(
      'type' => 'tests',
      'desc' => 'Browser support for inline SVG images.',
    ),
    'input' => array(
      'type' => 'tests',
      'desc' => 'Browser support for new <code>&lt;input></code> attributes such as placeholder, autocomplete, required...',
    ),
    'inputtypes' => array(
      'type' => 'tests',
      'desc' => 'Browser support for new <code>&lt;input></code> types such as color, date, number, tel...',
    ),
    'localstorage' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows access to a simple key/value store that persists across sessions.',
    ),
    'multiplebgs' => array(
      'type' => 'tests',
      'desc' => 'CSS value that allows multiple background images to be specified on a single element.',
    ),
    'opacity' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows for alpha transparency.',
    ),
    'pointerevents' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API for pointer events.',
    ),
    'postmessage' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API for cross-domain communication.',
    ),
    'rgba' => array(
      'type' => 'tests',
      'desc' => 'CSS value that allows colors to be specified in terms of red, green, blue, and alpha.',
    ),
    'sessionstorage' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows access to a simple key/value store. Cannot persist across sessions.',
    ),
    'smil' => array(
      'type' => 'tests',
      'desc' => 'Synchronized Multimedia Integration Language.',
    ),
    'svg' => array(
      'type' => 'tests',
      'desc' => 'Browser support for SVG images.',
    ),
    'svgclippaths' => array(
      'type' => 'tests',
      'desc' => 'Browser support for non-rectangular element shapes.',
    ),
    'textshadow' => array(
      'type' => 'tests',
      'desc' => 'CSS property that allows for drop-shadows behind text.',
    ),
    'touchevents' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API for touch events.',
    ),
    'video' => array(
      'type' => 'tests',
      'desc' => 'Built-in video support using <code>&lt;video></code>.',
    ),
    'webgl' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API for WebGL, the 3D graphics layer.',
    ),
    'websockets' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API for asynchronous browser communication.',
    ),
    'websqldatabase' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows access to a local database which supports a SQL-type language.',
    ),
    'webworkers' => array(
      'type' => 'tests',
      'desc' => 'JavaScript API that allows execution of background processes.',
    ),

    // Extensibility
    'addtest' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that allows the user to define their own feature tests.',
    ),
    'domprefixes' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that supplies DOM-style vendor prefixes.',
    ),
    'hasevent' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that detects support for a given event.',
    ),
    'prefixed' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that returns the prefixed or nonprefixed property name variant of its input.',
    ),
    'prefixes' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that supplies CSS-style vendor prefixes.',
    ),
    'teststyles' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that tests support for a specific CSS property.',
    ),
    'testprop' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function investigates whether a given style property is recognized.',
    ),
    'testallprops' => array(
      'type' => 'extensibility',
      'desc' => 'An internal Modernizr function that tests a list of DOM properties.',
    ),

    // Extras
    'load' => array(
      'type' => 'extras',
      'desc' => 'Provides yepnope.js, a conditional CSS/JS loader.',
    ),
    'setclasses' => array(
      'type' => 'extras',
      'desc' => 'Allows Modernizr to inject CSS classes into <code>&lt;html&gt;</code>.',
    ),
    'mq' => array(
      'type' => 'extras',
      'desc' => 'Allows Modernizr to evaluate CSS media queries.',
    ),
    'printshiv' => array(
      'type' => 'extras',
      'desc' => 'Provides html5shiv (for browsers that do not support HTML5 tags). Support for printing.',
    ),
    'shiv' => array(
      'type' => 'extras',
      'desc' => 'Provides html5shiv (for browsers that do not support HTML5 tags). No support for printing.',
    ),

    // CSS Prefix
    'cssclassprefix' => array(
      'type' => 'extras',
      'desc' => 'Allows the user to prefix injected Modernizr classes.',
    ),
  );

  if (isset($modernizr_args[$name])) {
    return $modernizr_args[$name];
  }

  return FALSE;
}
