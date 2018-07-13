<?php
/**
 * HAXCMS - The worlds smallest, most nothing yet most empowering CMS.
 * Simply a tremendous CMS. The greatest.
 */

include_once 'HAXCMSSite.php';
include_once 'JSONOutlineSchema.php';

class HAXCMS {
  public $appStoreFile;
  public $salt;
  public $privateKey;
  public $appStoreConnection;
  public $superUser;
  public $user;
  public $sitesDirectory;
  public $sites;
  public $data;
  public $configDirectory;
  public $sitesJSON;
  public $basePath;
  /**
   * Establish defaults for HAXCMS
   */
  public function __construct() {
    $this->basePath = '/';
    $this->appStoreConnection = new stdClass();
    $this->superUser = new stdClass();
    $this->superUser->name = NULL;
    $this->superUser->password = NULL;
    $this->user = new stdClass();
    $this->user->name = NULL;
    $this->user->password = NULL;
    // set default sites directory to look in if there
    if (is_dir(HAXCMS_ROOT . '/_sites')) {
      $this->sitesDirectory = '_sites';
    }
    // set default config directory to look in if there
    if (is_dir(HAXCMS_ROOT . '/_config')) {
      $this->configDirectory = HAXCMS_ROOT . '/_config';
      // ensure appstore file is there, then make salt size of this file
      if (file_exists(HAXCMS_ROOT . '/_config/appstore.json')) {
        $this->appStoreFile = '_config/appstore.json';
        $this->appStoreConnection->url = $this->appStoreFile;
      }
      // ensure appstore file is there, then make salt size of this file
      if (file_exists(HAXCMS_ROOT . '/SALT.txt')) {
        $this->salt = file_get_contents(HAXCMS_ROOT . '/SALT.txt');
      }
      if (file_exists($this->configDirectory . '/sites.json')) {
        $this->sitesJSON = '_config/sites.json';
        $this->outlineSchema = new JSONOutlineSchema();
        if ($this->outlineSchema->load($this->configDirectory . '/sites.json')) {
          // @todo
        }
        else {
          print 'no _config/sites.json';
        }
      }
    }
  }
  /**
   * Load a site off the file system with option to create
   */
  public function loadSite($name, $create = FALSE, $theme = 'default') {
    // check if this exists, load but fallback for creating on the fly
    if (is_dir(HAXCMS_ROOT . '/' . $this->sitesDirectory . '/' . $name)) {
      $site = new HAXCMSSite();
      $site->load(HAXCMS_ROOT . '/' . $this->sitesDirectory, $name);
      return $site;
    }
    else if ($create) {
      // attempt to create site
      return $this->createNewSite($name, $theme);
    }
    return FALSE;
  }
  /**
   * Attempt to create a new site on the file system
   * @return boolean true for success, false for failed
   */
  private function createNewSite($name, $theme = 'default') {
    // try and make the folder
    $site = new HAXCMSSite();
    if ($site->newSite(HAXCMS_ROOT . '/' . $this->sitesDirectory, $this->basePath . $this->sitesDirectory . '/', $name, $theme)) {
      return $site;
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
   * test the active user login based on session.
   */
  public function testLogin($adminFallback = FALSE) {
    if ($this->user->name == $_SERVER['PHP_AUTH_USER'] && $this->user->password == $_SERVER['PHP_AUTH_PW']) {
      return TRUE;
    }
    // if fallback is allowed, meaning the super admin then let them in
    // the default is to strictly test for the login in question
    // the fallback being allowable is useful for managed environments
    else if ($adminFallback && $this->superUser->name == $_SERVER['PHP_AUTH_USER'] && $this->superUser->password == $_SERVER['PHP_AUTH_PW']) {
      return TRUE;
    }
    return FALSE;
  }
  /**
   * Get a secure key based on session and two private values
   */
  public function getToken($value = '') {
    return $this->hmacBase64($value, session_id() . $this->privateKey . $this->salt);
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