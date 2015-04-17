<?php
/**
 * @file
 * Defines authcache personalized fragment renderer.
 */

/**
 * Interface for personalization fragment renderers.
 */
interface AuthcacheP13nFragmentInterface {
  /**
   * Render and return fragment.
   *
   * @param string $key
   *   The key for the fragment to be rendered.
   *
   * @param var $subject
   *   The result of the loader function for the given key. If no
   *   AuthcacheP13nFragmentLoader is associated with this fragment, subject is
   *   equal to key.
   *
   * @param array $context
   *   Additional run-time per-request context (key-value pairs).
   *
   * @return string
   *   Return a string representing the HTML fragment
   */
  public function render($key, $subject, $context);
}
