<?php

abstract class EntityFeaturesBuilder extends FeaturesBuilderBase {

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Entity';
  }

  /**
   * Analyzes fields on an entity bundle and adds appropriate components.
   *
   * @param string $entity_type
   *   The entity type to analyze.
   * @param string $bundle
   *   The bundle on the entity_type.
   */
  protected function setFields($entity_type, $bundle) {
    $this->setRegexComponents('field_instance', "/^{$entity_type}-{$bundle}-/");
    if (!empty($this->components['field_instance'])) {
      $this->setNamedComponents('dependencies', array($this->prefix . '_fields'));
    }
    $this->setNamedComponents('variable', array("field_bundle_settings_{$entity_type}__{$bundle}"));
    $info = field_info_instances($entity_type);
    $dependencies = array();
    foreach ($info[$bundle] as $bundleInfo) {
      $dependencies[] = $bundleInfo['widget']['module'];
      foreach ($bundleInfo['display'] as $display) {
        $dependencies[] = !empty($display['module']) ? $display['module'] : NULL;
      }
    }
    $this->setNamedComponents('dependencies', array_filter($dependencies));
    $this->setFieldGroups($entity_type, $bundle);
    $this->setAutoEntityLabel($entity_type, $bundle);
  }

  /**
   * Adds field_group components for the entity bundle.
   *
   * @param string $entity_type
   *   The entity type to analyze.
   * @param string $bundle
   *   The bundle on the entity_type.
   */
  protected function setFieldGroups($entity_type, $bundle) {
    $this->setRegexComponents('field_group', "/^group_[a-z0-9_]*\|$entity_type\|$bundle\|/");
    if (!empty($this->components['field_group'])) {
      $this->setNamedComponents('dependencies', array('field_group'));
    }
  }

  /**
   * Adds auto_entitylabel configuration for the entity bundle.
   *
   * @param string $entity_type
   *   The entity type to analyze.
   * @param string $bundle
   *   The bundle on the entity_type.
   */
  protected function setAutoEntityLabel($entity_type, $bundle) {
    $vars[] = "auto_entitylabel_{$entity_type}_$bundle";
    $vars[] = "auto_entitylabel_pattern_{$entity_type}_$bundle";
    $vars[] = "auto_entitylabel_php_{$entity_type}_$bundle";
    $this->setNamedComponents('variable', $vars);

    // If we added any auto_entitylabel variables, add it as a dependency.
    if (array_intersect($vars, $this->components['variable'])) {
      $this->setNamedComponents('dependencies', array('auto_entitylabel'));
    }

  }

}
