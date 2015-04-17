<?php
/**
 * @file
 * Defines the cache granularity class.
 */

/**
 * Cache granularity class.
 *
 * @see AuthcacheP13nAddCacheControlHeaderFilter
 * @see AuthcacheP13nDefaultRequestUrlGenerator
 */
class AuthcacheP13nCacheGranularity {
  const PER_USER = 0x02;
  const PER_PAGE = 0x04;

  protected $granularity;

  /**
   * Construct new cache granularity instance.
   */
  public function __construct($granularity) {
    $this->granularity = $granularity;
  }

  /**
   * Test whether a given granularity is set.
   */
  public function is($flag) {
    return $this->granularity & $flag;
  }
}
