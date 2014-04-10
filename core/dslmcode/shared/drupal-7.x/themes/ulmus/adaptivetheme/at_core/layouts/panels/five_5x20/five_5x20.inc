<?php

/**
 * @file
 * Implimentation of an Adaptivetheme Panels Layout Plugin
 * A panels layout plugin on steroids and an implementation of
 * hook_panels_layouts().
 *
 * These plugins must use the function method - Panels can support two
 * methods, one that uses a function name and one that simply defines
 * a $plugins array. You MUST use the function method, which requires
 * correct naming of the function:
 * function [theme name]_[plugin name]_panels_layouts()
 *
 * Adaptivetheme needs more data to build the actual CSS since it does not use
 * Panels normal method of defining a static CSS file. In AT the CSS is built
 * programmatically for each selected option when the user saves the theme
 * settings. This is for two main reasons - first so we are optimizing the
 * CSS and not adding any duplicate CSS declarations, and secondly so we can
 * easily insert the CSS into the right media query in the generated stylsheet.
 *
 * Adding Selectors and CSS Declarations:
 * Each CSS declaration is an array, keyed by an "identifier". The array items
 * are selector/css pairs. For example:
 * '40' => array('.five-5x20 .row-1' => 'width:40%'),
 * Here '40' is the identifier, '.five-5x20 .row-1' is the selector and 'width:40%'
 * is the actual CSS style.
 *
 * Identifiers:
 * Each identifier represents a CSS style. It's basically shorthand notation for the
 * actual CSS. To ensure the CSS is optimized as much as possible you should use an
 * existing identifier if it exists, although you can use your own, just make sure
 * to re-use them as much as possible in order to get the smallest CSS files -
 * here is a full list of the existing identifiers used by AT Core Panels plugins:

 Basic Widths (all must be in percentages):

 ID       CSS

 '25'     'width:25%'
 '33'     'width:33.333333%'
 '40'     'width:40%'
 '50'     'width:50%'
 '60'     'width:60%'
 '66'     'width:66.666666%'
 '75'     'width:75%'
 '100'    'width:100%'

 Floats with widths:

 '25fl'   'width:25%;float:left'
 '25fr'   'width:25%;float:right'
 '33fl'   'width:33.333333%;float:left'
 '50fl'   'width:50%;float:left'
 '75fl'   'width:75%;float:left'
 '75fr'   'width:75%;float:right'

 Floats:

 'fl'     'float:left'
 'fr'     'float:right'
 'fn'     'float:none'

 Stacked Regions get a specail cased identifier:

 'fdw'    'float:none;display:block;width:100%;clear:both'

 */

function adaptivetheme_five_5x20_panels_layouts() {
  $items['five_5x20'] = array(
    'title'    => t('AT Five column 5x20'),
    'category' => t('AT Responsive Panels - 4,5,6 column'),
    'icon'     => 'five_5x20.png', // Used in Panels Admin only. AT Core uses a CSS sprite for the icons in theme settings.
    'theme'    => 'five_5x20',
    'admin css' => 'five_5x20.admin.css', // This holds a basic layout for Panels Admin and the CSS for theme settings sprite. Sprite icons must be 40px by 40px.
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'five_first'  => t('Column 1'),
      'five_second' => t('Column 2'),
      'five_third'  => t('Column 3'),
      'five_fourth' => t('Column 4'),
      'five_fifth'  => t('Column 5'),
    ),

    // The array items below are added by Adaptivetheme and are not normally present
    // in a Panels layout plugin. AT uses these to build the theme settings and generate
    // the CSS used when rendering the layout in the front end.
    'type' => 'five',            // - type: dictates what group it will fall into in theme settings.
    'options' => array(          // - options: the various layout options the user can choose in theme settings for each device group.
      'five-5x20' => 'default',  // - option key: the key used here MUST match the key used in the 'styles', the first one must be called 'default'.
      'five-5x20-2x3-grid' => '2/3 split grid',
      'five-5x20-1x2x2-grid' => 'stack',
      'five-5x20-stack-2' => 'Stack 50/50 bottom',
      'five-5x20-stack' => 'stack', // stack should always refer to "all regions stacked", and use the 'fdw' identifier in 'styles'.
    ),
    'styles' => array(          // - styles: these items are used to programatically build and optimize the CSS for each break-point.
      'five-5x20' => array(     // - styles keys: these key must match the 'options' keys, the first one must be the default.
        'css' => array(         // - css: holds the array of CSS identifiers
          '40' => array('.five-5x20 > .row-1' => 'width:40%'), // selectors as keys, CSS as values, values should align to the the "css" array key identifiers.
          '60' => array('.five-5x20 > .row-2' => 'width:60%'),
          'fl' => array('.five-5x20 > .panel-row' => 'float:left'),
          '50' => array('.five-5x20 > .row-1 > .region' => 'width:50%'),
          '33' => array('.five-5x20 > .row-2 > .region' => 'width:33.333333%'),
        ),
      ),
      'five-5x20-2x3-grid' => array(
        'css' => array(
          '33' => array('.five-5x20 > .panel-row > .region' => 'width:33.333333%'),
          '50' => array('.five-5x20 > .row-1 div.region-five-first,.five-5x20 .row-1 div.region-five-second' => 'width:50%'),
          'fdw' => array('.five-5x20 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'five-5x20-1x2x2-grid' => array(
        'css' => array(
          '50' => array('.five-5x20 > .panel-row > div.region' => 'width:50%'),
          'fdw' => array('.five-5x20 > div.panel-row,.five-5x20 > div.panel-row > div.region-five-fifth' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'five-5x20-stack-2' => array(
        'css' => array(
          '50' => array('.five-5x20 > .row-1 > div.region' => 'width:50%'),
          'fdw' => array('.five-5x20 > .panel-row,.five-5x20 > .row-2 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'five-5x20-stack' => array(
        'css' => array(
          'fdw' => array('.five-5x20 > .panel-row > .region,.five-5x20 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for five-5x20.tpl.php
 */
function template_preprocess_five_5x20(&$vars) {
 /**
  * We need to initialize these variables when Panels is displaying the template.
  * These are used primarily when the template is being rendered via Display suite
  * as a "node" so we can programatically wrap the layout in <article> elements
  * with appropriate classes and id.
  *
  * Note that in Display Suite layout plugin preprocess and process functions are
  * not fired, instead we need to use the functions for the template being
  * modified by DS, such as node, user or search. AT Core sets these prefix and
  * suffix vars for nodes in adaptivetheme_process_node().
  */
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
