<?php

/**
 * @file
 * Defines content encoder interface.
 */

/**
 * Interface for content encoders.
 */
interface AuthcacheP13nContentEncoderInterface {
  /**
   * Return an appropriate internet media type string.
   *
   * Return the internet media type string identifying the output produced by
   * the encoding function.
   */
  public function contentType();

  /**
   * Serialize a result produced by AuthcacheP13nContentBuilder::build().
   */
  public function encode($result);
}
