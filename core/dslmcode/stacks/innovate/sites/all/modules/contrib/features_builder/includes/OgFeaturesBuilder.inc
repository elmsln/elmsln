<?php
/**
 * @file
 * Contains \OgFeaturesBuilder class.
 */

class OgFeaturesBuilder extends EntityFeaturesBuilder {

  static public $og_components = array(
    'og_features_permission',
    'og_membership_type'
  );

  // Stores og entity and component info per feature.
  static protected $info = array();

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'OG';
  }

  /**
   * {@inheritdoc}
   */
  protected function setComponents() {
    // Retrieve the feature of entity and component info.
    $name = substr($this->moduleName, strlen($this->prefix)+1);
    $info = OgFeaturesBuilder::$info[$name];

    switch ($info['entity_type']) {
      case 'og_membership_type':
        // Enable all og_membership_type bundle components.
        $this->setRegexComponents('og_membership_type', "/^{$info['bundle']}/");
        // Set bundle fields.
        $this->setFields('og_membership', $info['bundle']);
        break;

      default:
        // Sets roles and permissions per group entity type.
        $this->setRegexComponents('og_features_permission', "/{$info['entity_type']}:{$info['bundle']}/");
        $this->setRegexComponents('og_features_role', "/{$info['entity_type']}:{$info['bundle']}/");
        break;

    }
  }

  /**
   * {@inheritdoc}
   */
  public static function listFeatures() {
    $features = array();
    foreach (OgFeaturesBuilder::$og_components as $og_component) {
      // Retrieve feature exportables for each og component.
      $exportables = features_builder_get_exportables($og_component);
      // Set feature name to component:entity_type:bundle:label for each og
      // entity.
      switch ($og_component) {
        case 'og_features_permission':
          // Create feature module for group type roles and permissions.
          foreach ($exportables as $key => $value) {
            list($entity_type, $bundle) = explode(':', $key);
            $name = "{$og_component}_{$entity_type}_$bundle";
            if (!array_key_exists($name, $features)) {
              OgFeaturesBuilder::$info[$name] = array(
                'component' => $og_component,
                'entity_type' => $entity_type,
                'bundle' => $bundle,
              );
              $features[$name] = "$entity_type $bundle " . str_replace('_', ' ', $og_component);
            }
          }
          break;

        case 'og_membership_type':
          // Create feature module per og_membership_type bundle.
          $entity_type = 'og_membership_type';
          foreach ($exportables as $bundle => $value) {
            $name = "{$og_component}_{$entity_type}_$bundle";
            OgFeaturesBuilder::$info[$name] = array(
              'component' => $og_component,
              'entity_type' => $entity_type,
              'bundle' => $bundle,
            );
            $features[$name] = $value . ' ' . str_replace('_', ' ', $og_component);
          }
          break;

      }
    }

    return $features;
  }
}
