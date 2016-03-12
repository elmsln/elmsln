<?php

class EckFeaturesBuilder extends EntityFeaturesBuilder {

  /**
   * {@inheritdoc}
   */
  public static function listFeatures() {
    $features = array();

    // Provides a Feature module for each Entity Type.
    foreach (features_builder_get_exportables('eck_entity_type') as $type => $label) {
      $features['eck_' . $type] = $label;
    }

    return $features;
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Entity';
  }

  /**
   * {@inheritdoc}
   */
  protected function setComponents() {
    $entity_type = entity_type_load(substr($this->name, 4));
    $bundles = Bundle::loadByEntityType($entity_type);

    // Add the entity type.
    $this->setNamedComponents('eck_entity_type', array($entity_type->name));

    // Add each bundle and its fields.
    foreach ($bundles as $bundle) {
      $this->setNamedComponents('eck_bundle', array($bundle->machine_name));
      $this->setFields($entity_type->name, $bundle->name);
    }

    // Last but not least, add the dependency to eck.
    $this->setNamedComponents('dependencies', array('eck'));
  }

}
