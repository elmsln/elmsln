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
  public $id;
  public $title;
  public $author;
  public $description;
  public $license;
  public $metadata;
  public $items;
  /**
   * Establish defaults
   */
  public function __construct() {
    $this->file = NULL;
    $this->id = $this->generateUUID();
    $this->title = 'New site';
    $this->author = '';
    $this->description = '';
    $this->license = 'by-sa';
    $this->metadata = new stdClass();
    $this->items = array();
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
    return $count;
  }
  /**
   * Load a schema from a file
   */
  public function load($location) {
    if (file_exists($location)) {
      $this->file = $location;
      $fileData = json_decode(file_get_contents($location));
      $vars = get_object_vars($fileData);
      foreach ($vars as $key => $var) {
        if (isset($this->{$key}) && $key != 'items') {
          $this->{$key} = $var;
        }
      }
      // check for items and escalate to full JSONOutlineSchemaItem object
      // also ensures data matches only what is supported
      if (isset($vars['items'])) {
        foreach ($vars['items'] as $key => $item) {
          $newItem = new JSONOutlineSchemaItem();
          $newItem->id = $item->id;
          $newItem->indent = $item->indent;
          $newItem->location = $item->location;
          $newItem->order = $item->order;
          $newItem->parent = $item->parent;
          $newItem->title = $item->title;
          // metadata can be anything so whatever
          $newItem->metadata = $item->metadata;
          $this->items[$key] = $newItem;
        }
      }
      return TRUE;
    }
    return FALSE;
  }
  /**
   * Save data back to the file system location
   */
  public function save() {
    $schema = get_object_vars($this);
    unset($schema['file']);
    $schema['items'] = array();
    foreach ($this->items as $item) {
      $newItem = get_object_vars($item);
      array_push($schema['items'], $newItem);
    }
    return @file_put_contents($this->file, json_encode($schema, JSON_PRETTY_PRINT));
  }
  /**
   * Generate a UUID
   */
  private function generateUUID() {
    return sprintf( '%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
        // 32 bits for "time_low"
        mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff ),
        // 16 bits for "time_mid"
        mt_rand( 0, 0xffff ),
        // 16 bits for "time_hi_and_version",
        // four most significant bits holds version number 4
        mt_rand( 0, 0x0fff ) | 0x4000,
        // 16 bits, 8 bits for "clk_seq_hi_res",
        // 8 bits for "clk_seq_low",
        // two most significant bits holds zero and one for variant DCE1.1
        mt_rand( 0, 0x3fff ) | 0x8000,
        // 48 bits for "node"
        mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff )
    );
  }
}