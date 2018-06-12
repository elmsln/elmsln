<?php
/**
 * HAXCMS - The worlds smallest, most nothing yet most empowering CMS.
 * Simply a tremendous CMS. The greatest.
 */

include_once 'HAXCMSProject.php';

class HAXCMS {
  public $appStoreFile = "appstore/appstore.json";
  public $salt = "haxTheWeb";
  public $privateKey;
  public $appStoreConnection;
  public $projectDirectory;
  /**
   * Establish defaults for HAXCMS
   */
  public function __construct() {
    $this->appStoreConnection = new stdClass();
    $this->appStoreConnection->url = $this->appStoreFile;
    // ensure appstore file is there, then make salt size of this file
    if (file_exists(HAXCMS_ROOT . '/' . $this->appStoreFile)) {
      $this->salt = filesize(HAXCMS_ROOT . '/' . $this->appStoreFile);
    }
  }
  /**
   * Load a project off the file system with option to create
   */
  public function loadProject($name, $create = FALSE) {
    // check if this exists, load but fallback for creating on the fly
    if (is_dir($this->projectDirectory . '/' . $name)) {
      $project = new HAXCMSProject();
      $project->load($this->projectDirectory, $name);
      return $project;
    }
    else if ($create) {
      // attempt to create project
      return $this->createNewProject($name);
    }
    return FALSE;
  }
  /**
   * Attempt to create a new project on the file system
   * @return boolean true for success, false for failed
   */
  private function createNewProject($name) {
    // try and make the folder
    $project = new HAXCMSProject();
    if ($project->newProject($this->projectDirectory, $name)) {
      return $project;
    }
    return FALSE;
  }
  /**
   * Validate a security token
   */
  public function validateToken($token, $value = '') {
    if ($token == $this->getToken($value)) {
      return TRUE;
    }
    return FALSE;
  }
  /**
   * Get a secure key based on session and two private values
   */
  public function getToken($value = '') {
    return hmacBase64($value, session_id() . $this->privateKey . $this->salt);
  }
  /**
   * Generate a base 64 hash
   */
  private function hmacBase64($data, $key) {
    // generate the hash
    $hmac = base64_encode(hash_hmac('sha256', (string) $data, (string) $key, TRUE));
    // strip unsafe content post encoding
    return strtr($hmac, array(
      '+' => '-',
      '/' => '_',
      '=' => '',
    ));
  }
}