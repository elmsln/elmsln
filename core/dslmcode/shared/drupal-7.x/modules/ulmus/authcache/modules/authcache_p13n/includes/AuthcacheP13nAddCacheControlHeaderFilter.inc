<?php

/**
 * @file
 * Defines request filter for adding HTTP cache-control headers.
 */

/**
 * Request filter for adding HTTP cache-control headers.
 *
 * This class provides a filter for adding appropriate HTTP Cache-Control
 * headers to a response.
 */
class AuthcacheP13nAddCacheControlHeaderFilter implements AuthcacheP13nFilterInterface {
  /**
   * @var AuthcacheP13nCoreService
   */
  protected $coreService;

  /**
   * Number of seconds the response should be cached in the users browser.
   */
  protected $cacheMaxage;

  /**
   * @var AuthcacheP13nCacheGranularity
   */
  protected $cacheGranularity;

  /**
   * Construct a new instance.
   */
  public function __construct(
    AuthcacheP13nCoreServiceInterface $core_service,
    $cache_maxage,
    AuthcacheP13nCacheGranularity $cache_granularity
  ) {
    $this->coreService = $core_service;
    $this->cacheMaxage = $cache_maxage;
    $this->cacheGranularity = $cache_granularity;
  }

  /**
   * {@inheritdoc}
   *
   * Add Cache-Control header.
   */
  public function filter($event, $input) {
    if ($this->cacheMaxage) {
      if ($this->cacheGranularity->is(AuthcacheP13nCacheGranularity::PER_USER)) {
        $this->coreService->drupalAddHttpHeader('Cache-Control', 'private, max-age=' . $this->cacheMaxage);
      }
      else {
        $this->coreService->drupalAddHttpHeader('Cache-Control', 'public, max-age=' . $this->cacheMaxage);
      }
    }
    else {
      $this->coreService->drupalAddHttpHeader('Cache-Control', 'no-cache, must-revalidate, post-check=0, pre-check=0');
    }

    return $input;
  }
}
