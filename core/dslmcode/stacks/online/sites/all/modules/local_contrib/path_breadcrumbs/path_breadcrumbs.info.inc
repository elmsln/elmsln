<?php

/**
 * @file
 * Contains Entity API hooks and callbacks.
 */

/**
 * Implements hook_entity_property_info_alter().
 */
function path_breadcrumbs_entity_property_info_alter(&$info) {
  $properties = &$info['taxonomy_term']['properties'];

  // Add tokens for automatic generation of taxonomy hierarchy.
  $properties['pb_join'] = array(
    'label' => t("Path Breadcrumbs join"),
    'description' => t("All parent terms (for Path Breadcrumbs)"),
    'getter callback' => 'path_breadcrumbs_entity_get_properties',
    'type' => 'struct',
    'property info' => array(
      'name' => array(
        'label' => t("Join parents names"),
        'description' => t("Join parents names"),
        'getter callback' => 'path_breadcrumbs_entity_get_properties',
        'type' => 'text',
      ),
      'url' => array(
        'label' => t("Join parents URLs"),
        'description' => t("Join parents URLs"),
        'getter callback' => 'path_breadcrumbs_entity_get_properties',
        'type' => 'text',
      ),
    ),
    'computed' => TRUE,
  );
}

/**
 * Entity API property 'pb_join' getter callback.
 *
 * Support for %term:pb-join:name and %term:pb-join:url tokens.
 */
function path_breadcrumbs_entity_get_properties($data, array $options, $name, $type, $info) {
  if ($name == 'pb_join') {
    $data->type = $type;
    $data->parents = array_reverse(taxonomy_get_parents_all($data->tid));
    return $data;
  }

  if ($data->type == 'taxonomy_term') {
    $result = array();
    foreach ($data->parents as $term) {
      if ($name == 'name') {
        $term_name = $term->name;
        if (function_exists('i18n_taxonomy_term_name')) {
          $term_name = i18n_taxonomy_term_name($term);
        }

        $result[] = $term_name;
      }
      elseif ($name == 'url') {
        $result[] = 'taxonomy/term/' . $term->tid;
      }
    }

    return implode("\n", $result);
  }

  return '';
}
