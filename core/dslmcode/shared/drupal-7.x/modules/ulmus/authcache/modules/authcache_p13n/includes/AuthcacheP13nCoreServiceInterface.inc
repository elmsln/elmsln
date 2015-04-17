<?php
/**
 * @file
 * Defines interface for drupal core services.
 */

/**
 * Interface for core service.
 */
interface AuthcacheP13nCoreServiceInterface {
  /**
   * Sets an HTTP response header for the current page.
   *
   * @see drupal_add_http_header()
   */
  public function drupalAddHttpHeader($name, $value, $append = FALSE);

  /**
   * Ensures Drupal is bootstrapped to the specified phase.
   *
   * @see drupal_bootstrap()
   */
  public function drupalBootstrap($phase = NULL, $new_phase = TRUE);
}
