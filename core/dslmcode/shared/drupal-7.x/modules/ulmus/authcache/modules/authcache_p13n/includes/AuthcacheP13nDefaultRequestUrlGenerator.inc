<?php

/**
 * @file
 * Defines request URL generator.
 */

/**
 * Interface for request url generators.
 */
class AuthcacheP13nDefaultRequestUrlGenerator implements AuthcacheP13nRequestUrlGeneratorInterface {
  /**
   * Personalization fragment frontcontroller relative to DRUPAL_ROOT.
   */
  protected $frontControllerURL;

  /**
   * @var AuthcacheP13nCacheGranularity
   */
  protected $cacheGranularity;

  /**
   * Construct new request URL generator.
   *
   * @param String $front_controller
   *   Path to the personalization fragment frontcontroller relative to
   *   DRUPAL_ROOT.
   * @param int $cache_granularity
   *   Cache granularity.
   */
  public function __construct(
    $front_controller,
    AuthcacheP13nCacheGranularity $cache_granularity
  ) {
    // If the frontcontroller is given as a relative path, prepend it with the
    // base path.
    $parts = parse_url($front_controller);
    if (empty($parts['host'])) {
      $this->frontControllerURL = base_path() . $front_controller;
    }
    else {
      $this->frontControllerURL = $front_controller;
    }

    $this->cacheGranularity = $cache_granularity;
  }

  /**
   * {@inheritdoc}
   */
  public function url($route_id, $arg) {
    $query = array(
      'a' => $arg,
      'r' => $route_id,
    );

    // Add path for per-page caching.
    url('', array('prefix' => &$prefix));
    if ($this->cacheGranularity->is(AuthcacheP13nCacheGranularity::PER_PAGE)) {
      $query['o'] = $_GET;
    }
    else {
      $query['o'] = array(
        'q' => empty($prefix) ? '' : $prefix,
      );
    }

    return array(
      'path' => $this->frontControllerURL,
      'options' => array(
        'external' => TRUE,
        'query' => $query,
      ),
    );
  }
}
