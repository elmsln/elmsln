<?php

namespace Drupal\xautoload\DIC;

/**
 * @see ServiceFactory
 */
class ServiceContainer implements ServiceContainerInterface {

  /**
   * @var ServiceFactory
   */
  protected $factory;

  /**
   * @var object[]
   */
  protected $services = array();

  /**
   * @param string $key
   *
   * @return mixed
   */
  function get($key) {
    return isset($this->services[$key])
      ? $this->services[$key]
      : $this->services[$key] = $this->factory->$key($this) ? : FALSE;
  }

  /**
   * Unset the service for a specific key.
   *
   * @param string $key
   */
  function reset($key) {
    $this->services[$key] = NULL;
  }

  /**
   * Register a new service under the given key.
   *
   * @param string $key
   * @param mixed $service
   */
  function set($key, $service) {
    $this->services[$key] = $service;
  }

  /**
   * Magic getter for a service.
   *
   * @param string $key
   *
   * @return mixed
   *
   * @throws \Exception
   */
  function __get($key) {
    if (isset($this->services[$key])) {
      return $this->services[$key];
    }
    if (!method_exists($this->factory, $key)) {
      throw new \Exception("Unsupported key '$key' for service factory.");
    }

    return $this->services[$key] = $this->factory->$key($this) ? : FALSE;
  }

  /**
   * @param ServiceFactory $factory
   */
  function __construct($factory) {
    $this->factory = $factory;
  }
}
