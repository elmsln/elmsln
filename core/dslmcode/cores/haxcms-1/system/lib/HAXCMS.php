<?php
/**
 * HAXCMS - The worlds smallest, most nothing yet most empowering CMS.
 * Simply a tremendous CMS. The greatest.
 */

include_once 'HAXCMSSite.php';
include_once 'JSONOutlineSchema.php';
include_once 'JWT.php';

class HAXCMS {
  public $appStoreFile;
  public $salt;
  public $privateKey;
  public $superUser;
  public $user;
  public $sitesDirectory;
  public $sites;
  public $data;
  public $configDirectory;
  public $sitesJSON;
  public $basePath;
  public $safePost;
  public $safeGet;
  /**
   * Establish defaults for HAXCMS
   */
  public function __construct() {
    // stupid session less handling thing
    $_POST = (array)json_decode(file_get_contents('php://input'));
    // handle sanitization on request data, drop security things
    $this->safePost = filter_var_array($_POST, FILTER_SANITIZE_STRING);
    unset($this->safePost['jwt']);
    unset($this->safePost['token']);
    $this->safeGet = filter_var_array($_GET, FILTER_SANITIZE_STRING);
    $this->basePath = '/';
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
   * Generate appstore connection information. This has to happen at run time.
   * to get into account _config / environmental overrides
   */
  public function appStoreConnection() {
    $connection = new stdClass();
    $connection->url = $this->basePath . $this->appStoreFile;
    return $connection;
  }
  /**
   * Load a site off the file system with option to create
   */
  public function loadSite($name, $create = FALSE, $theme = 'default') {
    // check if this exists, load but fallback for creating on the fly
    if (is_dir(HAXCMS_ROOT . '/' . $this->sitesDirectory . '/' . $name)) {
      $site = new HAXCMSSite();
      $site->load(HAXCMS_ROOT . '/' . $this->sitesDirectory, $this->basePath . $this->sitesDirectory . '/', $name);
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
  public function validateRequestToken($token = NULL, $value = '') {
    // default token is POST
    if ($token == NULL && isset($_POST['token'])) {
      $token = $_POST['token'];
    }
    if ($token != NULL) {
      if ($token == $this->getRequestToken($value)) {
        return TRUE;
      }
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
  public function getRequestToken($value = '') {
    return $this->hmacBase64($value, $this->privateKey . $this->salt);
  }
  /**
   * Get user's JWT
   */
  public function getJWT() {
    $token = array();
    $token['id'] = $this->getRequestToken('user');
    $token['user'] = $_SERVER['PHP_AUTH_USER'];
    return JWT::encode($token, $this->privateKey . $this->salt);
  }
  /**
   * Validate a JTW during POST
   */
  public function validateJWT($endOnInvalid = TRUE) {
    if ($_POST['jwt'] != NULL) {
      $post = JWT::decode($_POST['jwt'], $this->privateKey);
      if ($post->id == $this->getRequestToken('user')) {
        return TRUE;
      }
    }
    // kick back the end if its invalid
    if ($endOnInvalid) {
      print 'Invalid token';
      header('Status: 403');
      exit;
    }
    return FALSE;
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