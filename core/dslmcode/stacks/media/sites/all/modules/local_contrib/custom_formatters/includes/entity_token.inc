<?php
/**
 * @file
 * Entity tokens module integration.
 */

/**
 * Implements hook_custom_formatters_token_tree_types_alter() on behalf of
 * entity_tokens.module.
 */
function entity_token_custom_formatters_token_tree_types_alter(&$token_types, $field_type) {
  module_load_include('inc', 'entity_token', 'entity_token.tokens');
  $fields = array();
  foreach (field_info_fields() as $name => $field) {
    if ($field['type'] == $field_type) {
      $fields[] = str_replace('_', '-', $name);
    }
  }
  $info = module_exists('token') ? token_get_info() : token_info();
  foreach ($fields as $field) {
    foreach (element_children($info['tokens']) as $type) {
      if (isset($info['tokens'][$type][$field])) {
        $token_info = $info['tokens'][$type][$field];
        if (!empty($token_info['entity-token']) && isset($token_info['type']) && entity_token_types_chained($token_info['type'])) {
         $token_types[] = $token_info['type'];
         return;
        }
      }
    }
  }
}

/**
 * Implements hook_custom_formatters_token_data_alter() on behalf of
 * entity_token.module.
 */
function entity_token_custom_formatters_token_data_alter(&$token_data, &$text, $field) {
  module_load_include('inc', 'entity_token', 'entity_token.tokens');
  $field_name = str_replace('_', '-', $field['field_name']);
  $info = module_exists('token') ? token_get_info() : token_info();
  foreach (element_children($info['tokens']) as $type) {
    if (isset($info['tokens'][$type][$field_name])) {
      $token_info = $info['tokens'][$type][$field_name];
      if (!empty($token_info['entity-token']) && isset($token_info['type']) && entity_token_types_chained($token_info['type'])) {
        $token_types = entity_token_types_chained();
        $item_token_type = entity_property_list_extract_type($token_info['type']);

        // List tokens.
        if (isset($token_types[$item_token_type])) {
          $entity_info = entity_get_info($token_types[$item_token_type]);
          $entity = entity_load($token_types[$item_token_type], array($token_data['item'][$entity_info['entity keys']['id']]));
          $token_data[$token_info['type']] = array($entity[$token_data['item'][$entity_info['entity keys']['id']]]);
          $text = str_replace('[list:', "[{$token_info['type']}:", $text);
        }

        // Structural tokens.
        elseif ('struct' == $token_info['type']) {
          $entity_info = entity_get_info($field['type']);
          if (isset($entity_info['entity keys'])) {
            $entity = entity_load($field['type'], array($token_data['item'][$entity_info['entity keys']['id']]));
            $token_data['struct'] = entity_metadata_wrapper($field['type'], $entity[$token_data['item'][$entity_info['entity keys']['id']]]);
          }
        }
        return;
      }
    }
  }
}
