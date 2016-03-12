<?php

/**
 * Base class for a Features Builder.
 */
abstract class FeaturesBuilderBase implements FeaturesBuilderInterface {

  protected $name;
  protected $components;
  protected $dependencies;
  public $moduleName;
  public $moduleLabel;
  public $prefix;

  public function __construct($name) {
    $this->name = $name;
    $this->prefix = variable_get('features_builder_prefix_name');
    $this->moduleName = $this->prefix . '_' . $name;
    $features = $this->listFeatures();
    $this->moduleLabel = variable_get('features_builder_prefix_label') . ' ' . $features[$name];
  }

  /**
   * List components included for a named Features module.
   */
  abstract protected function setComponents();

  /**
   * Lists the components included in this build.
   */
  public function components() {
    if ($this->components === NULL) {
      $this->setComponents();
      if ($this->components === NULL) {
        $this->components = array();
      }
      drupal_alter('features_builder_components_' . $this->name, $this->components);
      ksort($this->components);
    }
    return $this->components;
  }

  /**
   * Set components as defined in $components parameter.
   * 
   * @param string $component
   *   Component type of the exportables to analyze.
   * @param array $components
   *   An array of exportable component names.
   */
  protected function setNamedComponents($component, $components) {
    if (empty($this->components[$component]) || !is_array($this->components[$component])) {
      $this->components[$component] = array();
    }
    $matches = array_intersect_key(features_builder_get_exportables($component), array_flip($components));
    if ($matches) {
      $this->components[$component] += $matches;
    }
  }

  /**
   * Set variable type components by matching a regex.
   * 
   * @param string $component
   *   Component type of the exportables to analyze.
   * @param string $regex
   *   A regex used to match variable names.
   */
  protected function setRegexComponents($component, $regex) {
    $components = features_builder_get_exportables($component);
    foreach ($components as $name => $value) {
      if (preg_match($regex, $name) > 0) {
        $this->components[$component][$name] = $value;
      }
    }
  }

  /**
   * Set all components of a specified type.
   * 
   * @param string $component
   *   Component type of the exportables to analyze.
   */
  protected function setAllComponents($component) {
    $this->components[$component] = features_builder_get_exportables($component);
  }

  /**
   * {@inheritdoc}
   */
  public function label() {
    return $this->moduleLabel;
  }

  /**
   * {@inheritdoc}
   */
  public function machineName() {
    return $this->moduleName;
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Features';
  }
}
