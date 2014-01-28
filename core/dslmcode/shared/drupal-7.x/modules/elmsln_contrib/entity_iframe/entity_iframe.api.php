<?php

/**
 * Implements hook_entity_iframe_properties_alter().
 *
 * Modify the properties passed to the iframe for rendering.
 *
 * @param $properties
 *   array of iframe element properties
 * @param $context
 *   where iframe embed is being displayed, defaults to 'display'
 */
function hook_entity_iframe_properties_alter(&$properties, $context) {
  $properties['class'] = 'iframe';
  // when this is rendered in a view, render differently
  if ($context == 'view') {
    $properties['class'] = 'iframe_view';
    if (isset($properties['frameborder'])) {
      unset($properties['frameborder']);
    }
  }
}