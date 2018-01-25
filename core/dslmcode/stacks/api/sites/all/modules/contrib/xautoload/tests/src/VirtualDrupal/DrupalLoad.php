<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class DrupalLoad {

  /**
   * @var array
   */
  private $files = array();

  /**
   * @var DrupalGetFilename
   */
  private $drupalGetFilename;

  /**
   * @param DrupalGetFilename $drupalGetFilename
   */
  function __construct(DrupalGetFilename $drupalGetFilename) {
    $this->drupalGetFilename = $drupalGetFilename;
  }

  /**
   * @see drupal_load()
   */
  function drupalLoad($type, $name) {

    if (isset($this->files[$type][$name])) {
      return TRUE;
    }

    $filename = $this->drupalGetFilename->drupalGetFilename($type, $name);

    if ($filename) {
      include_once $filename;
      $this->files[$type][$name] = TRUE;

      return TRUE;
    }

    return FALSE;
  }
} 
