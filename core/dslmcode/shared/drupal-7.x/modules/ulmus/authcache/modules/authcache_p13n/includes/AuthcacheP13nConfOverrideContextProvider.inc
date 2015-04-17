<?php

/**
 * @file
 * Defines context provider for overriding conf values.
 */

/**
 * Interface for context providers.
 */
class AuthcacheP13nConfOverrideContextProvider implements AuthcacheP13nContextProviderInterface {
  /**
   * ConfOverride phase required to serve this request.
   */
  protected $overrideConf;

  /**
   * Construct new instance.
   */
  public function __construct(array $override_conf = array()) {
    $this->overrideConf = $override_conf;
  }

  /**
   * {@inheritdoc}
   */
  public function get($input) {
    global $conf;

    $original = array_intersect_key($conf, $this->overrideConf);
    $conf = $this->overrideConf + $conf;

    return $original;
  }
}
