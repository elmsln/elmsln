<?php
/**
 * @file
 * Defines the interface for mapping URLs to requests and vice versa.
 */

/**
 * Interface for mapping URLs to requests and vice versa.
 */
class AuthcacheP13nDefaultRequestRouter implements AuthcacheP13nRequestRouterInterface {
  /**
   * Key-value collection id for handlers.
   */
  const HANDLER_COLLECTION = 'route_handlers';

  /**
   * Key-value collection id for url generators.
   */
  const URL_GENERATOR_COLLECTION = 'route_generators';

  /**
   * {@inheritdoc}
   */
  public function getRoutes() {
    return $this->getHandlerStore()->getKeys();
  }

  /**
   * {@inheritdoc}
   */
  public function getHandler($route_id) {
    $handler = $this->getHandlerStore()->getOne($route_id);

    if (!$handler) {
      watchdog('AuthcacheP13nDefaultRequestRouter', 'Failed to find request handler for route %r', array('%r' => $route_id), WATCHDOG_ERROR);
    }

    return $handler;
  }

  /**
   * {@inheritdoc}
   */
  public function generateURL($route_id, $arg = NULL) {
    $generator = $this->getUrlGeneratorStore()->getOne($route_id);

    if ($generator) {
      return $generator->url($route_id, $arg);
    }
    else {
      watchdog('AuthcacheP13nDefaultRequestRouter', 'Failed to find url generator for route %r', array('%r' => $route_id), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function rebuild() {
    // Collect all request definitions.
    $resources = authcache_p13n_request_resources();
    $processors = authcache_p13n_resource_processors();

    $handler_store = $this->getHandlerStore();
    $url_generator_store = $this->getUrlGeneratorStore();

    $obsolete_handlers = drupal_map_assoc($handler_store->getKeys());
    $obsolete_url_generators = drupal_map_assoc($url_generator_store->getKeys());

    foreach ($resources as $route_id => $resource) {
      try {
        $factory = new AuthcacheP13nObjectFactory($resource, $processors);

        $handler = $factory->get('handler');
        $generator = $factory->get('url generator');

        $handler_store->set($route_id, $handler);
        $url_generator_store->set($route_id, $generator);

        unset($obsolete_handlers[$route_id]);
        unset($obsolete_url_generators[$route_id]);
      }
      catch (Exception $e) {
        watchdog_exception('AuthcacheP13nDefaultRequestRouter', $e);
      }
    }

    if (!empty($obsolete_handlers)) {
      $handler_store->delete($obsolete_handlers);
    }
    if (!empty($obsolete_url_generators)) {
      $handler_store->delete($obsolete_url_generators);
    }
  }

  /**
   * Map of short type name constants to key-value store.
   */
  protected $handlerStore;

  /**
   * Map of short type name constants to key-value store.
   */
  protected $urlGeneratorStore;

  /**
   * Return new key value store for pre-built request handlers.
   */
  protected function getHandlerStore() {
    if (!isset($this->handlerStore)) {
      $this->handlerStore = new AuthcacheP13nDatabaseKeyValueStore(static::HANDLER_COLLECTION);
    }
    return $this->handlerStore;
  }

  /**
   * Return new key value store for pre-built request handlers.
   */
  protected function getUrlGeneratorStore() {
    if (!isset($this->urlGeneratorStore)) {
      $this->urlGeneratorStore = new AuthcacheP13nDatabaseKeyValueStore(static::URL_GENERATOR_COLLECTION);
    }
    return $this->urlGeneratorStore;
  }
}
