<?php
/**
 * JSONOutlineSchemaItem - a single item without an outline of items.
 */

class JSONOutlineSchemaItem {
  public $id;
  public $indent;
  public $location;
  public $order;
  public $parent;
  public $title;
  public $metadata;
  /**
   * Establish defaults for a new item
   */
  public function __construct() {
    $this->id = uniqid('item-');
    $this->indent = 0;
    $this->location = NULL;
    $this->order = 0;
    $this->parent = NULL;
    $this->title = 'New item';
    $this->metadata = new stdClass();
  }
  /**
   * Load data from the location specified
   */
  public function loadLocation() {
    if (file_exists($this->location)) {
      return file_get_contents($this->location);
    }
    return FALSE;
  }
}