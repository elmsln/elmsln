<?php
/**
 * @file
 * Defines authcache personalized fragment validator.
 */

/**
 * Interface for personalization fragment validators.
 */
interface AuthcacheP13nFragmentValidatorInterface {
  /**
   * Validate the given list of keys.
   *
   * Throw AuthcacheP13nRequestInvalidInput to abort a request.
   *
   * Note: At the time this method is called, the bootstrap phase is not
   * guaranteed to be greater than DRUPAL_BOOTSTRAP_SESSION. Therefore avoid
   * calling functions which will trigger hook invocations like e.g.
   * entity_load.
   *
   * @throws AuthcacheP13nRequestInvalidInput
   *
   * @param array $keys
   *   An associative array of key-value pairs (key=value) representing the
   *   keys of the fragment(s) to load.
   *
   * @return array
   *   An associative array of key-value pairs where keys correspond to the
   *   input keys and the values to subjects to be used in the renderer.
   */
  public function validate($keys);
}
