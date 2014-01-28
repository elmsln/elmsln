<?php
/**
 * @file
 * mooc_widgets.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_widgets_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_view_modes';
  $strongarm->value = array(
    'node' => array(
      'mooc_fieldset' => array(
        'label' => 'Fieldset',
        'custom settings' => 1,
      ),
      'mooc_tabs' => array(
        'label' => 'Tabs',
        'custom settings' => 1,
      ),
    ),
  );
  $export['entity_view_modes'] = $strongarm;

  return $export;
}
