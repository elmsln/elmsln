<?php
/**
 * @file
 * Defines authcache personalized setting validator.
 */

/**
 * Interface for personalization setting validators.
 */
interface AuthcacheP13nSettingValidatorInterface {
  /**
   * Validate the given parameters.
   *
   * Throw AuthcacheP13nRequestInvalidInput to abort a request.
   *
   * Note: At the time this method is called, the bootstrap phase is not
   * guaranteed to be greater than DRUPAL_BOOTSTRAP_SESSION. Therefore avoid
   * calling functions which will trigger hook invocations like e.g.
   * entity_load.
   *
   * @param var $params
   *   Params set by the client.
   *
   * @return array
   *   Params to be used in subsequent processing.
   */
  public function validate($params);
}
