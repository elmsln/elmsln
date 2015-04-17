<?php

/**
 * @file
 * Defines context provider for drupal bootstrap mechanism.
 */

/**
 * Interface for context providers.
 */
class AuthcacheP13nBootstrapContextProvider implements AuthcacheP13nContextProviderInterface {
  /**
   * @var AuthcacheP13nCoreService
   */
  protected $coreService;

  /**
   * Bootstrap phase required to serve this request.
   */
  protected $bootstrapPhase;

  /**
   * Construct new instance.
   */
  public function __construct(AuthcacheP13nCoreServiceInterface $core_service, $bootstrap_phase = NULL) {
    $this->coreService = $core_service;
    $this->bootstrapPhase = $bootstrap_phase;
  }

  /**
   * {@inheritdoc}
   */
  public function get($input) {
    return $this->coreService->drupalBootstrap($this->bootstrapPhase);
  }
}
