<?php

/**
 * @file
 * Contains the FieldHierarchy class.
 */

class FieldHierarchy implements Countable {

  /**
   * @var array
   *  The flattened hierarchy data.
   */
  protected $data = array();

  const ROOT = 'root';

  public function __get($property) {
    return $this->{$property};
  }

  public function options($key = FieldHierarchy::ROOT, $parent = NULL, $depth = -1) {
    $options = array();

    $item = $this->data[$key];

    if (isset($item['label'])) {
      $options[$key] = str_repeat('-', $depth) . $item['label'];
    }

    if (isset($item['children'])) {
      foreach ($item['children'] as $child) {
        $options = array_merge($options, $this->options($child, $key, $depth + 1));
      }
    }

    return $options;
  }

  /**
   * Add an item of any type to the hierarchy.
   */
  public function add($item_key, $label = NULL, $parent = FieldHierarchy::ROOT) {
    if (!array_key_exists($item_key, $this->data)) {
      $this->data[$item_key]['label'] = isset($label) ? $label : $item_key;
    }

    if (!isset($this->data[$parent]['children'])) {
      $this->data[$parent]['children'] = array();
    }

    if (!in_array($item_key, $this->data[$parent]['children'])) {
      $this->data[$parent]['children'][] = $item_key;
    }
  }

  /**
   * Adds a single field plugin to the hierarchy.
   */
  public function addField(FieldInstance $field) {
    $bundle_key = "{$field->entityType}:{$field->bundle}";

    if ($field->isBundleable) {
      $this->add($field->entityType, $field->entityTypeLabel);
      $this->add($bundle_key, $field->bundleLabel, $field->entityType);
    }
    else {
      $this->add($bundle_key, $field->entityTypeLabel);
    }

    $field_key = "{$bundle_key}:{$field->name}";
    $this->add($field_key, $field->label, $bundle_key);
  }

  /**
   * Adds an entire field chain to the hierarchy.
   */
  public function addChain(FieldChain $chain) {
    $parents = array();

    foreach ($chain as $field) {
      if ($field->requireParent()) {
        $parent_key = implode('::', $parents);
        $field_key = "{$parent_key}::{$field}";

        $this->add($field_key, $field->label, $parent_key);
      }
      else {
        $this->addField($field);
      }

      $parents[] = $field->__toString();
    }
  }

  /**
   * @implements Countable::count().
   */  
  public function count() {
    return sizeof($this->data);
  }

}
