<?php

/**
 * @file
 * Entity tokens module integration.
 */

/**
 * Implements hook_custom_formatters_token_tree_types_alter() on behalf of
 * entity_tokens.module.
 *
 * @param $token_types
 * @param $field_type
 */
function entity_token_custom_formatters_token_tree_types_alter(&$token_types, $field_type) {
  $field = field_info_field_types($field_type);

  module_load_include('inc', 'entity_token', 'entity_token.tokens');
  $entity_token_types = entity_token_types_chained();
  if (is_array($entity_token_types)) {
    foreach ($entity_token_types as $token_type => $type) {
      foreach (entity_get_all_property_info($type) as $name => $property) {
        $property += array(
          'type'        => 'text',
          'description' => $property['label']
        );
        if ($property['type'] == $field['property_type'] || entity_property_list_extract_type($property['type']) == $field['property_type']) {
          $property_token_type = _entity_token_map_to_token_type($property);
          if (isset($entity_token_types[$property_token_type])) {
            $token_types[] = $property_token_type;
          }
          if (isset($property['property info'])) {
            foreach ($property['property info'] as $property_info) {
              $property_token_type = _entity_token_map_to_token_type($property_info);
              if (isset($entity_token_types[$property_token_type])) {
                $token_types[] = $property_token_type;
              }
            }
          }
        }
      }
    }
  }

  $token_types = array_unique($token_types);
}

/**
 * Implements hook_custom_formatters_token_data_alter() on behalf of
 * entity_token.module.
 *
 * @param $token_data
 * @param $text
 * @param $field
 * @param $delta
 *
 * @throws EntityMetadataWrapperException
 */
function entity_token_custom_formatters_token_data_alter(&$token_data, &$text, $field, $delta) {
  module_load_include('inc', 'entity_token', 'entity_token.tokens');
  $token_types = entity_token_types_chained();
  $field_name  = str_replace('_', '-', $field['field_name']);
  $info        = module_exists('token') ? token_get_info() : token_info();
  foreach (element_children($info['tokens']) as $type) {
    if (isset($token_data[$type]) && isset($info['tokens'][$type][$field_name])) {
      $wrapper = !isset($wrapper) ? _entity_token_wrap_data($type, $token_types[$type], $token_data[$type], array()) : $wrapper;
      if (isset($wrapper->{$field['field_name']})) {
        $field_wrapper = $wrapper->{$field['field_name']};
        if ($field_wrapper instanceof EntityListWrapper && isset($field_wrapper[$delta])) {
          $field_wrapper = $field_wrapper[$delta];
        }

        if ($field_wrapper instanceof EntityStructureWrapper) {
          $token_data['struct'] = $field_wrapper;
          foreach ($field_wrapper->getPropertyInfo() as $name => $property) {
            $property_token_type = _entity_token_map_to_token_type($property);
            if (isset($token_types[$property_token_type])) {
              $token_data[$property['type']] = $field_wrapper->get($name)
                ->value();
            }
          }
        }
        elseif (isset($token_types[$field_wrapper->type()])) {
          $token_data[$field_wrapper->type()] = $field_wrapper->value();
        }

        return;
      }
    }
  }
}
