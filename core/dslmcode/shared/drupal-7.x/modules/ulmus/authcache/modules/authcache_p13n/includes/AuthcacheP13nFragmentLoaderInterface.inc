<?php
/**
 * @file
 * Defines authcache personalized fragment object loader.
 */

/**
 * Interface for personalization fragment object loaders.
 */
interface AuthcacheP13nFragmentLoaderInterface {
  /**
   * Load the objects designated by the given list of keys.
   *
   * @throws AuthcacheP13nRequestNotFound
   *
   * @param array $keys
   *   A list of strings representing the keys of the fragment(s) to load.
   *
   * @param array $context
   *   Additional run-time per-request context (key-value pairs).
   *
   * @return array
   *   An associative array of key-value pairs where keys correspond to the
   *   input keys and the values to the objects loaded from the database.
   */
  public function load($keys, $context);
}
