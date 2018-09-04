<?php
/**
 * HAXCMS - The worlds smallest, most nothing yet most empowering CMS.
 * Simply a tremendous CMS. The greatest.
 */
// service creation / HAX app store service abstraction
include_once 'HAXService.php';
// working with sites
include_once 'HAXCMSSite.php';
// working with files
include_once 'HAXCMSFile.php';
// working with JSON Outline Schema
include_once 'JSONOutlineSchema.php';
// working with json web tokens
include_once 'JWT.php';
// working with git operators
include_once 'Git.php';

class HAXCMS {
  public $appStoreFile;
  public $salt;
  public $privateKey;
  public $apiKeys;
  public $superUser;
  public $user;
  public $sitesDirectory;
  public $sites;
  public $data;
  public $configDirectory;
  public $sitesJSON;
  public $domain;
  public $protocol;
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
    // Get HTTP/HTTPS (the possible values for this vary from server to server)
    $this->protocol = (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] && !in_array(strtolower($_SERVER['HTTPS']),array('off','no'))) ? 'https' : 'http';
    $this->domain = $_SERVER['HTTP_HOST'];
    // auto generate base path
    $this->basePath = '/';
    $this->apiKeys = array();
    // set up user account stuff
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
      // add in the auto-generated app store file
      $this->appStoreFile = 'system/generateAppStore.php';
      // ensure appstore file is there, then make salt size of this file
      if (file_exists(HAXCMS_ROOT . '/SALT.txt')) {
        $this->salt = file_get_contents(HAXCMS_ROOT . '/SALT.txt');
      }
      if (file_exists($this->configDirectory . '/sites.json')) {
        $this->sitesJSON = '_config/sites.json?' . $this->getRequestToken(time());
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
   * Generate a valid HAX App store specification schema for connecting to this site via JSON.
   */
  public function siteConnectionJSON() {
    return '{
      "details": {
        "title": "Local files",
        "icon": "perm-media",
        "color": "light-blue",
        "author": "HAXCMS",
        "description": "HAXCMS integration for HAX",
        "tags": ["media", "hax"]
      },
      "connection": {
        "protocol": "' . $this->protocol . '",
        "url": "' . $this->domain . $this->basePath . '",
        "operations": {
          "browse": {
            "method": "GET",
            "endPoint": "system/loadFiles.php",
            "pagination": {
              "style": "link",
              "props": {
                "first": "page.first",
                "next": "page.next",
                "previous": "page.previous",
                "last": "page.last"
              }
            },
            "search": {
            },
            "data": {
            },
            "resultMap": {
              "defaultGizmoType": "image",
              "items": "list",
              "preview": {
                "title": "name",
                "details": "mime",
                "image": "url",
                "id": "uuid"
              },
              "gizmo": {
                "source": "url",
                "id": "uuid",
                "title": "name",
                "type": "type"
              }
            }
          },
          "add": {
            "method": "POST",
            "endPoint": "system/saveFile.php",
            "acceptsGizmoTypes": [
              "image",
              "video",
              "audio",
              "pdf",
              "svg",
              "document",
              "csv"
            ],
            "resultMap": {
              "item": "data.file",
              "defaultGizmoType": "image",
              "gizmo": {
                "source": "url",
                "id": "uuid"
              }
            }
          }
        }
      }
    }';
  }
  /**
   * Generate appstore connection information. This has to happen at run time.
   * to get into account _config / environmental overrides
   */
  public function appStoreConnection() {
    $connection = new stdClass();
    $connection->url = $this->basePath . $this->appStoreFile . '?app-store-token=' . $this->getRequestToken('appstore');
    return $connection;
  }
  /**
   * Load a site off the file system with option to create
   */
  public function loadSite($name, $create = FALSE, $domain = NULL) {
    $tmpname = urldecode($name);
    $tmpname = preg_replace('/[^A-Za-z0-9]/', '', $tmpname);
    $tmpname = strtolower($tmpname);
    // check if this exists, load but fallback for creating on the fly
    if (is_dir(HAXCMS_ROOT . '/' . $this->sitesDirectory . '/' . $tmpname)) {
      $site = new HAXCMSSite();
      $site->load(HAXCMS_ROOT . '/' . $this->sitesDirectory, $this->basePath . $this->sitesDirectory . '/', $tmpname);
      return $site;
    }
    else if ($create) {
      // attempt to create site
      return $this->createNewSite($name, $domain);
    }
    return FALSE;
  }
  /**
   * Attempt to create a new site on the file system
   * @return boolean true for success, false for failed
   */
  private function createNewSite($name, $domain = NULL) {
    // try and make the folder
    $site = new HAXCMSSite();
    if ($site->newSite(HAXCMS_ROOT . '/' . $this->sitesDirectory, $this->basePath . $this->sitesDirectory . '/', $name, $domain)) {
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
    if ($this->user->name === $_SERVER['PHP_AUTH_USER'] && $this->user->password === $_SERVER['PHP_AUTH_PW']) {
      return TRUE;
    }
    // if fallback is allowed, meaning the super admin then let them in
    // the default is to strictly test for the login in question
    // the fallback being allowable is useful for managed environments
    else if ($adminFallback && $this->superUser->name === $_SERVER['PHP_AUTH_USER'] && $this->superUser->password === $_SERVER['PHP_AUTH_PW']) {
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
    if (isset($_POST['jwt']) && $_POST['jwt'] != NULL) {
      $post = JWT::decode($_POST['jwt'], $this->privateKey);
      if ($post->id == $this->getRequestToken('user')) {
        return TRUE;
      }
    }
    // fallback is GET requests
    if (isset($_GET['jwt']) && $_GET['jwt'] != NULL) {
      $get = JWT::decode($_GET['jwt'], $this->privateKey);
      if ($get->id == $this->getRequestToken('user')) {
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