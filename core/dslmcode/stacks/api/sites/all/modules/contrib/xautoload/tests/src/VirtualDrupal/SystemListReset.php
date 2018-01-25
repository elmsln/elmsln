<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class SystemListReset {

  /**
   * @var DrupalStatic
   */
  private $drupalStatic;

  /**
   * @var Cache
   */
  private $cache;

  /**
   * @param Cache $cache
   * @param DrupalStatic $drupalStatic
   */
  function __construct(Cache $cache, DrupalStatic $drupalStatic) {
    $this->cache = $cache;
    $this->drupalStatic = $drupalStatic;
  }

  /**
   * @see system_list_reset()
   */
  function systemListReset() {
    $this->drupalStatic->resetKey('system_list');
    $this->drupalStatic->resetKey('system_rebuild_module_data');
    $this->drupalStatic->resetKey('list_themes');
    $this->cache->cacheClearAll('bootstrap_modules', 'cache_bootstrap');
    $this->cache->cacheClearAll('system_list', 'cache_bootstrap');

  }
} 
