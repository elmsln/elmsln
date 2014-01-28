<?php
/**
 * @file
 * Views integration for Replicate API.
 */

/**
 * Implements hook_views_data_alter().
 */
function replicate_ui_views_data_alter(&$views_data) {
  // allow for intergration with all entity types
  $types = entity_get_info();
  foreach ($types as $key => $type) {
    // create a structured link in the view to replicate entity
    $views_data['views_entity_' . $key]['replicate_ui_link'] = array(
      'field' => array(
        'title' => t('replicate link'),
        'help' => t('Provide a simple link to replicate the entity'),
        'handler' => 'views_handler_field_replicate_ui_link',
      ),
    );
  }
}
