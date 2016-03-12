<?php

class NodeFeaturesBuilder extends EntityFeaturesBuilder {

  protected $type;

  public function __construct($name) {
    parent::__construct($name);
    $this->type = substr($this->name, 5);
  }

  public static function listFeatures() {
    $features = array();
    foreach (features_builder_get_exportables('node') as $name => $label) {
      $features["node_$name"] = $label;
    }
    return $features;
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Content';
  }

  protected function setComponents() {
    // Node-specific variables.
    $this->setNamedComponents('node', array($this->type));
    $this->setNamedComponents('variable', array('menu_options_' . $this->type));
    $this->setNamedComponents('variable', array('menu_parent_' . $this->type));
    $this->setNamedComponents('variable', array('node_options_' . $this->type));
    $this->setNamedComponents('variable', array('node_preview_' . $this->type));
    $this->setNamedComponents('variable', array('node_submitted_' . $this->type));


    // Add Fields and Field Groups assigned to the bundle.
    $bundle = substr($this->name, 5);
    $this->setFields('node', $bundle);
    $this->setAutoNodeTitle($bundle);
  }

  /**
   * Adds auto_nodetitle configuration for the entity bundle.
   *
   * @param string $type
   *   The bundle on the entity_type.
   */
  protected function setAutoNodeTitle($type) {
    $vars[] = "ant_$type";
    $vars[] = "ant_pattern_$type";
    $vars[] = "ant_php_$type";
    $this->setNamedComponents('variable', $vars);

    // If we added any auto_nodetitle variables, add it as a dependency.
    if (array_intersect($vars, $this->components['variable'])) {
      $this->setNamedComponents('dependencies', array('auto_nodetitle'));
    }
  }

}
