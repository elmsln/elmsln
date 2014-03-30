<?php

/**
 * @file
 * Atjs export UI plugin.
 */

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'atjs_listener',
  'access' => 'administer atjs',
  // Define the menu item.
  'menu' => array(
    'menu item' => 'atjs',
    'menu title' => 'At.js Listeners',
    'menu description' => 'Administer atjs listeners.',
  ),
  // Define user interface texts.
  'title singular' => t('listener'),
  'title plural' => t('listeners'),
  'title singular proper' => t('atjs listener'),
  'title plural proper' => t('atjs listeners'),
);
