<?php
/**
 * @file
 * Defines content encoder for HTML.
 */

/**
 * HTML content encoder.
 */
class AuthcacheP13nHTMLContent implements AuthcacheP13nContentEncoderInterface {
  /**
   * {@inheritdoc}
   */
  public function contentType() {
    return 'text/html; charset=UTF-8';
  }

  /**
   * {@inheritdoc}
   */
  public function encode($result) {
    return (string) $result;
  }
}
