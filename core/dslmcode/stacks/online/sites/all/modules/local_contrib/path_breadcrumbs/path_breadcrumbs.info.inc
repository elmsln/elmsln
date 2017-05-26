<?php

/**
 * @file
 * Contains Entity API hooks and callbacks.
 */

/**
 * Implements hook_entity_property_info_alter().
 */
function path_breadcrumbs_entity_property_info_alter(&$info) {
  $taxonomy_properties = &$info['taxonomy_term']['properties'];
  $node_properties = &$info['node']['properties'];
  $site_properties = &$info['site']['properties'];

  // Add tokens for automatic generation of taxonomy hierarchy.
  $taxonomy_properties['pb_join'] = _path_breadcrumbs_pb_join_property_defaults();
  $taxonomy_properties['pb_join']['description'] = 'All parent terms (for Path Breadcrumbs)';

  // Add menu-link properties only for autocomplete in Path Breadcrumbs UI.
  $node_properties['menu_link'] = _path_breadcrumbs_menu_link_property_defaults();
  $site_properties['current_page']['property info']['menu_link'] = _path_breadcrumbs_menu_link_property_defaults();

  // Add path-menu-trail property only for autocomplete.
  $site_properties['current_page']['property info']['path_menu_trail'] = _path_breadcrumbs_menu_trail_property_defaults();
}

/**
 * Entity API property 'pb_join' getter callback.
 *
 * Support for %term:pb-join:name and %term:pb-join:url tokens.
 */
function path_breadcrumbs_entity_get_properties($data, array $options, $name, $type, $info) {
  if (empty($data)) {
    return;
  }

  if ($name == 'pb_join') {
    $data->parent_type = $type;
    return $data;
  }

  if (!empty($data->parent_type) && $data->parent_type == 'taxonomy_term') {
    $result = array();
    $parents = array_reverse(taxonomy_get_parents_all($data->tid));

    foreach ($parents as $term) {
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
      elseif ($name == 'none') {
        $result[] = '<none>';
      }
    }

    return implode("\n", $result);
  }

  return '';
}

/**
 * Return default 'pb-join' struct.
 */
function _path_breadcrumbs_pb_join_property_defaults() {
  return array(
    'label' => t("Path Breadcrumbs join"),
    'description' => t("Path Breadcrumbs join"),
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
      'none' => array(
        'label' => t("<none> equivalent for pb-join tokens"),
        'description' => t("<none> equivalent for pb-join tokens"),
        'getter callback' => 'path_breadcrumbs_entity_get_properties',
        'type' => 'text',
        'sanitized' => TRUE,
      ),
    ),
    'computed' => TRUE,
  );
}

/**
 * Return default 'menu-link' struct.
 */
function _path_breadcrumbs_menu_link_property_defaults() {
  return array(
    'label' => t("Menu link"),
    'description' => t("Menu link"),
    'getter callback' => 'path_breadcrumbs_entity_get_properties',
    'type' => 'struct',
    'property info' => array(
      'title' => array(
        'label' => t("Title"),
        'description' => t("The title of the menu link."),
        'type' => 'text',
      ),
      'mlid' => array(
        'label' => t("Link ID"),
        'description' => t("The unique ID of the menu link."),
        'type' => 'text',
      ),
      'parents' => array(
        'label' => t("Join parents names"),
        'description' => t("Join parents names"),
        'type' => 'text',
      ),
      'url' => array(
        'label' => t("Join parents URLs"),
        'description' => t("Join parents URLs"),
        'type' => 'text',
      ),
      'pb_join' => _path_breadcrumbs_pb_join_property_defaults(),
    ),
    'computed' => TRUE,
  );
}

/**
 * Return default 'path-menu-trail' structure.
 */
function _path_breadcrumbs_menu_trail_property_defaults() {
  return array(
    'label' => t('Path menu trail'),
    'description' => t('Expands menu trail by path'),
    'getter callback' => 'path_breadcrumbs_entity_get_properties',
    'type' => 'struct',
    'property info' => array(
      'pb_join' => _path_breadcrumbs_pb_join_property_defaults(),
    ),
    'computed' => TRUE,
  );
}
