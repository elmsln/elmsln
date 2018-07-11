<?php
/**
 * JSONOutlineSchema - An object for interfacing with the JSON Outline schema
 * specification. @see https://github.com/LRNWebComponents/json-outline-schema
 * for more details. This provides a simple way of loading outlines, parsing
 * and working with the items in them while writing back to the specification
 * accurately.
 */

include_once 'JSONOutlineSchemaItem.php';

class JSONOutlineSchema {
  public $file;
  public $outline;
  public $items;
  public $data;
  /**
   * Establish defaults
   */
  public function __construct() {
    $this->file = NULL;
    $this->items = array();
    $this->outline = array();
    $this->data = new stdClass();
    $this->data->id = uniqid('outline-');
    $this->data->title = 'New outline';
    $this->data->author = 'Individual';
    $this->data->description = '';
    $this->data->license = 'by-sa';
    $this->data->metadata = new stdClass();
  }
  /**
   * Get a new item matching schema standards
   * @return new JSONOutlineSchemaItem Object
   */
  public function newItem() {
    $item = new JSONOutlineSchemaItem();
    return $item;
  }
  /**
   * Add an item to the outline
   * @var $item an array of values, keyed to match JSON Outline Schema
   * @return count of items in the array
   */
  public function addItem($item) {
    $item2 = new JSONOutlineSchemaItem();
    $ary = get_object_vars($item);
    foreach ($ary as $key => $value) {
      // a form of validation, only set what the spec allows
      // back into a new object just to be safe
      if (isset($item2->{$key})) {
        $item2->{$key} = $value;
      }
    }
    $count = array_push($this->items, $item);
    $this->updateHierarchy();
    return $count;
  }
  /**
   * Load a schema from a file
   */
  public function load($location) {
    if (file_exists($location)) {
      $this->file = $location;
      $fileData = json_decode(file_get_contents($location));
      $this->data = $fileData;
      $this->items = $this->data->items;
      unset($this->data->items);
      $this->updateHierarchy();
      return TRUE;
    }
    return FALSE;
  }
  /**
   * Save data back to the file system location
   */
  public function save() {
    $schema = get_object_vars($this->data);
    $schema['items'] = array();
    foreach ($this->items as $item) {
      $newItem = get_object_vars($item);
      array_push($newItem, $schema['items']);
    }
    return @file_put_contents($this->file, json_encode($schema));
  }
  /**
   * Update the outline variable to be a multidimensional
   * array, based on the items array (which is flat for simplicity)
   */
  private function updateHierarchy() {
    $outline = array();
    $this->outline = $outline;
    return TRUE;
  }
}