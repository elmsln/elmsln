<?php

/**
* Implements hook_views_data_alter()
*/
function entity_iframe_views_data_alter(&$views_data) {
  // allow for intergration with all entity types
  $types = entity_get_info();
  foreach ($types as $key => $type) {
    // only apply if fieldable to match iframe criteria
    if ($type['fieldable']) {
      // create a structured embed code field in the view
      $views_data['views_entity_' . $key]['entity_iframe_embed'] = array(
        'field' => array(
          'title' => t('embed code'),
          'help' => t('Provide the embed code of an iframe for this entity'),
          'handler' => 'views_handler_field_entity_iframe_embed',
          'type' => $key,
          'real field' => 'entity object',
        ),
      );
      // create a structured iframe link in the view
      $views_data['views_entity_' . $key]['entity_iframe_link'] = array(
        'field' => array(
          'title' => t('iframe link'),
          'help' => t('Provide a simple link to the entity in iframe mode'),
          'handler' => 'views_handler_field_entity_iframe_link',
        ),
      );
    }
  }
}
