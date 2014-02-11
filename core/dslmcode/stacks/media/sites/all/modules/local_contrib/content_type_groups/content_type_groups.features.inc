<?php
/**
 * @file
 * Export functionality for the content type groups module.
 */

/**
 * Implementation of hook_features_export_options().
 *
 * This hook tells features what items of this component are available for export.
 *
 * @return array
 *   A keyed array of items, suitable for use with a FormAPI select or checkboxes element.
 */
function content_type_groups_features_export_options() {

  // Get all group names, keyed by machine name
  $options = ContentTypeGroup::fetch();
  return $options;
}

/**
 * Implementation of hook_features_export().
 *
 * When one of these components is selected on the features page, this hook
 * includes the item (plus any dependencies) in the export array.
 *
 * @param array $data
 *   The machine name for this component.
 * @param array &$export
 *   An array of components to be exported.
 * @param string $module_name
 *   The name of the feature module that will be created.
 *
 * @return array
 *   An array of functions for further processing (if desired).
 */
function content_type_groups_features_export($data, &$export, $module_name) {

  // These are the dependencies for this module to function properly
  $export['dependencies']['content_type_groups'] = 'content_type_groups';

  // This is a simple straight object export.
  foreach ($data as $component) {
    $export['features']['content_type_groups'][$component] = $component;
  }

  return array();
}

/**
 * Implementation of hook_features_export_render().
 *
 * This hook is called to export the component(s) selected via the features UI.
 *
 * @param string $module_name
 *   The name of the feature module to be exported.
 * @param array $data
 *   An array of machine name identifiers for the rendered objects.
 * @param array $export
 *   An array with the full export for the feature (only called during update or recreate).
 *
 * @return array
 *   The PHP code (an array) that will be rendered.
 */
function content_type_groups_features_export_render($module_name, $data, $export = NULL) {

  $code = array(
    ' $content_type_groups = array();',
    '',
  );

  foreach ($data as $machine_name) {

    // Retrieve the content_type_group
    $group = new ContentTypeGroup($machine_name);

    // Format it in prep for export.
    $group_data = _content_type_groups_format_group_data($group);

    // Add the content type group to the feature.
    $code[] = ' $content_type_groups[\'' . $machine_name . '\'] = ' . features_var_export($group_data, ' ' ) . ';';

  }

  $code[] = '';
  $code[] = ' return $content_type_groups;';
  $code = implode("\n", $code);

  return array('content_type_groups_features_default_settings' => $code);

}

/**
 * Implementation of hook_features_rebuild(). [component_hook]
 *
 * This is called whenever a new feature is enabled, or reverted.
 */
function content_type_groups_features_rebuild($module) {

  // Look for exported content type groups
  $groups = module_invoke($module, 'content_type_groups_features_default_settings');

  // Recreate groups that are in the feature
  $node_types = _content_type_groups_get_node_types();
  foreach ($groups as $machine_name => $data) {
    _content_type_groups_store_group_data($data, $node_types);
  }

}

/**
 * Implementation of hook_features_revert(). [component_hook]
 */
function content_type_groups_features_revert($module) {
  content_type_groups_features_rebuild($module);
}

/**
 * Formats a content type group loaded with the API
 * into a data structure for export
 */
function _content_type_groups_format_group_data($group) {
  $group_data = array(
    'type'          => $group->type,
    'name'          => $group->name,
    'content_types' => $group->content_types,
  );
  return $group_data;
}

/**
 * Stores exported content type group data in the database
 *
 * @param array $data
 *   Information about a single content type from feature export.
 * @param array $node_types
 *   Results from node_type_get_types(). Passed through to avoid calling this each time this function is called.
 */
function _content_type_groups_store_group_data($data, $node_types = NULL) {

  if (!$node_types) {
    $node_types = _content_type_groups_get_node_types();
  }

  // Create the group
  $group = new ContentTypeGroup($data['type']);

  // If the group already exists, clear out the existing content types
  if ($group->name) {
    $group->content_types = array();
  }

  // Fill in the stored name and content types
  $group->name = $data['name'];
  foreach ($data['content_types'] as $content_type => $type_data) {
    if (in_array($content_type, $node_types)) { // Only add existing node types
      $group->addContentType($content_type, $type_data['weight']);
    }
  }

  // Save the group
  $group->save();

}

/**
 * Returns the site's content types.
 *
 * @return array
 *    Machine names of all content types on the site.
 */
function _content_type_groups_get_node_types() {
  $types = array();
  foreach (node_type_get_types() as $type) {
    $types[] = $type->type;
  }
  return $types;
}