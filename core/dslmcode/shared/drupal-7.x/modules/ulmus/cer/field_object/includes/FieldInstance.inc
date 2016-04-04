<?php

class FieldInstance {

  /**
   * @var string
   * The instance's entity type.
   */
  public $entityType;

  /**
   * @var string
   * The instance bundle.
   */
  public $bundle;

  /**
   * @var string
   * The field's machine name.
   */
  public $name;

  /**
   * @var boolean
   * Whether or not this instance's entity type supports bundles.
   */
  public $isBundleable;

  /**
   * @var string
   * The human-readable label of the instance's entity type.
   */
  public $entityTypeLabel;

  /**
   * @var string
   * The human-readable label of the instance's bundle.
   */
  public $bundleLabel;

  /**
   * @var integer
   * The cardinality (maximum values) the field supports, or
   * FIELD_CARDINALITY_UNLIMITED.
   */
  public $cardinality;

  /**
   * @var string
   * The instance's label.
   */
  public $label;

  /**
   * @var FieldInstance
   * The parent of this instance, if any.
   */
  protected $parent;

  /**
   * @var FieldInstance
   * The child of this instance, if any.
   */
  protected $child;

  public function __construct($entity_type, $bundle, $field_name) {
    $this->entityType = $entity_type;
    $this->bundle = $bundle;
    $this->name = $field_name;

    // Get info about the entity type and bundle hosting this field instance.
    $info = entity_get_info($entity_type);
    $this->isBundleable = (boolean) $info['entity keys']['bundle'];
    $this->entityTypeLabel = $info['label'];
    $this->bundleLabel = $info['bundles'][$bundle]['label'];

    // Get global info about the field.
    $info = field_info_field($field_name);
    $this->cardinality = $info['cardinality'];

    // Finally, get info about the field instance.
    $instance = field_info_instance($entity_type, $field_name, $bundle);
    $this->label = $instance['label'];
  }

  public function __toString() {
    return "{$this->entityType}:{$this->bundle}:{$this->name}";
  }

  /**
   * Get or set the parent of this field instance.
   */
  public function parent(FieldInstance $parent = NULL) {
    if ($parent) {
      $this->parent = $parent;
    }
    return $this->parent;
  }

  /**
   * Get or set the child of this field instance.
   */
  public function child(FieldInstance $child = NULL) {
    if ($child) {
      $this->child = $child;
    }
    return $this->child;
  }

  /**
   * Determine if this field requires a parent. An example of this would be
   * a field that is instantiated on a field collection (which is itself
   * a field).
   */
  public function requireParent() {
    return FALSE;
  }

  /**
   * Return the parents of this field instance as an array of FieldInstance
   * objects. If there are no parents, return an empty array.
   */
  public function getParents() {
    return array();
  }

}
