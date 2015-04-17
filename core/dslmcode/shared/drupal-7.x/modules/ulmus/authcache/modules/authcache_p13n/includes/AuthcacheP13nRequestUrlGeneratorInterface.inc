<?php

/**
 * @file
 * Defines request filter.
 */

/**
 * Interface for request url generators.
 */
interface AuthcacheP13nRequestUrlGeneratorInterface {
  /**
   * Generate an url for the given request and parameter.
   *
   * @returns array
   *   An associative array consisting of the following key-value pairs:
   *   - path: A relative or absolute URL without query or fragment suitable for
   *     supplying to the $path parameter of the drupal url() function.
   *   - options: An associative array containing the options as accepted by the
   *     $options parameter of the drupal url() function.
   *
   * @see url()
   */
  public function url($route_id, $arg);
}
