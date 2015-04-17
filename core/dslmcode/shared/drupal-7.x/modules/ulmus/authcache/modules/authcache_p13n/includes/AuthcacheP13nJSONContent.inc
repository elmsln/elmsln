<?php
/**
 * @file
 * Define content encoder for JSON.
 */

/**
 * JSON content encoder.
 */
class AuthcacheP13nJSONContent implements AuthcacheP13nContentEncoderInterface {
  /**
   * {@inheritdoc}
   */
  public function contentType() {
    return 'text/javascript';
  }

  /**
   * {@inheritdoc}
   */
  public function encode($result) {
    return json_encode($result);
  }
}
