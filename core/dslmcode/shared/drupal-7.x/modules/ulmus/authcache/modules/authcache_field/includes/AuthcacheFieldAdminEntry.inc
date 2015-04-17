<?php
/**
 * @file
 * Defines the block admin entry class.
 */

/**
 * Block admin entry class.
 */
class AuthcacheFieldAdminEntry {
  /**
   * Construct a new block admin entry.
   */
  public function __construct($entity_type, $field_name, $bundle_name, $config, $defaults) {
    // Copy over defaults.
    foreach ($defaults as $key => $value) {
      $this->{$key} = $value;
    }

    // Specify group.
    $this->group = t('Fields');

    // Add name, description, adminPath and clients properties.
    $instance = field_info_instance($entity_type, $field_name, $bundle_name);
    $entity_info = entity_get_info($entity_type);
    $entity_type_label = $entity_info['label'];
    $bundle_definitions = field_info_bundles();
    $bundle_label = $bundle_definitions[$entity_type][$bundle_name]['label'];

    $this->name = $instance['label'];
    $this->description = t('Field on bundle %bundle_label of type %entity_type_label', array(
      '%entity_type_label' => $entity_type_label,
      '%bundle_label' => $bundle_label,
    ));
    $this->clients = isset($config['clients']) ? $config['clients'] : array();

    if (module_exists('field_ui')) {
      $this->adminPath = _field_ui_bundle_admin_path($entity_type, $bundle_name) . '/fields/' . $field_name;
    }
  }
}
