<?php

class HAXCMS {
  public $appStoreFile = "appstore/appstore.json";
  public $salt = "haxTheWeb";
  public $privateKey;
  public $appStoreConnection;
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