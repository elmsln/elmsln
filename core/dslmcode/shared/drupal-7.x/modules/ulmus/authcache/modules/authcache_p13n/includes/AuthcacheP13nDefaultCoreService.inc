<?php
/**
 * @file
 * Defines the default implementation for drupal core services.
 */

/**
 * Default implementation for drupal core services.
 */
class AuthcacheP13nDefaultCoreService implements AuthcacheP13nCoreServiceInterface {
  /**
   * {@inheritdoc}
   */
  public function drupalAddHttpHeader($name, $value, $append = FALSE) {
    drupal_add_http_header($name, $value, $append = FALSE);
  }

  /**
   * {@inheritdoc}
   */
  public function drupalBootstrap($phase = NULL, $new_phase = TRUE) {
    return drupal_bootstrap($phase, $new_phase);
  }
}
