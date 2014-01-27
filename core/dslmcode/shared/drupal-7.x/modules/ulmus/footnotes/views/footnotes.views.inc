<?php
/**
 * @file
 * To do views declarations.
 */

/**
* Implements hook_views_data_alter()
*/
function footnotes_views_data_alter(&$views_data) {
  // allow for intergration with all entity types
  $types = entity_get_info();
  foreach ($types as $key => $type) {
    // only apply if fieldable
    if ($type['fieldable']) {
      // create a structured embed code field in the view
      $views_data['views_entity_' . $key]['footnotes_text'] = array(
        'field' => array(
          'title' => t('Footnotes from content'),
          'help' => t('Abstract the footnotes from a content field'),
          'handler' => 'views_handler_field_footnotes_text',
          'type' => $key,
          'real field' => 'entity object',
        ),
      );
    }
  }
}
