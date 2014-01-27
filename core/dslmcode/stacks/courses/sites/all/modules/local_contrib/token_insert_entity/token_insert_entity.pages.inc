<?php
/**
 * @file
 * Page callback implementations for token_insert_entity module.
 */

/**
 * Form builder to insert a token.
 */
function token_insert_entity_form($form_state, $form_id) {
  $form = array();
  $form['entity'] = array(
    '#title' => t('Content title'),
    '#description' => t('Type the first words of the title of the content that you want to insert.'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'token_insert_entity/autocomplete',
  );

  return $form;
}

/**
 * Callback to return a form and associated metadata.
 */
function token_insert_entity_form_data() {
  // Loag the form to select an entity.
  $form = drupal_get_form('token_insert_entity_form');
  $markup = drupal_render($form);

  // Build an array of build modes per entity type.
  $view_modes = array();
  foreach (entity_get_info() as $entity_type => $entity_info) {
    $entity_view_modes = array();
    foreach($entity_info['view modes'] as $key => $view_mode) {
      $entity_view_modes[$key] = $view_mode['label'];
    }
    $view_modes[$entity_type] = $entity_view_modes;
  }

  return array(
    'markup' => $markup,
    'view_modes' => $view_modes,
  );
}

/**
 * Returns a list of entity suggestions.
 */
function _token_insert_entity_autocomplete($string) {
  $matches = array();
  // Define which property to search per entity type.
  $entities = _token_insert_entity_entity_type_titles();
  // Search over each entity type.
  foreach ($entities as $entity_type => $entity_property) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type)
      ->propertyCondition($entity_property, $string, 'CONTAINS');
    $result = $query->execute();
    $ids = !empty($result[$entity_type]) ? array_keys($result[$entity_type]) : array();
    if (count($ids)) {
      $entities = entity_load($entity_type, $ids);
      foreach ($entities as $id => $entity) {
        $bundle = !empty($entity->type) ? $entity->type : $entity_type;
        $matches[$entity_type . ':' . $id] = $bundle . ': ' . check_plain($entity->{$entity_property});
      }
    }
  }

  return drupal_json_output($matches);
}
