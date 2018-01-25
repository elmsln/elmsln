<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;



class SystemList {

  /**
   * @var Cache
   */
  private $cache;

  /**
   * @var DrupalGetFilename
   */
  private $drupalGetFilename;

  /**
   * @var SystemListLoader
   */
  private $systemListLoader;

  /**
   * @var DrupalStatic
   */
  private $drupalStatic;

  /**
   * @param Cache $cache
   * @param SystemTable $systemTable
   * @param DrupalGetFilename $drupalGetFilename
   * @param DrupalStatic $drupalStatic
   */
  function __construct(Cache $cache, SystemTable $systemTable, DrupalGetFilename $drupalGetFilename, DrupalStatic $drupalStatic) {
    $this->cache = $cache;
    $this->drupalGetFilename = $drupalGetFilename;
    $this->systemListLoader = new SystemListLoader($systemTable);
    $this->drupalStatic = $drupalStatic;
  }

  /**
   * Replicates system_list('module_enabled').
   *
   * @return object[]
   */
  public function systemListModuleEnabled() {
    return $this->systemList('module_enabled');
  }

  /**
   * Replicates system_list($type), with $type !== 'bootstrap'.
   *
   * @see system_list()
   *
   * @param string $type
   *   Either 'module_enabled', 'theme' or 'filepaths'.
   *
   * @return object[]|array[]
   */
  private function systemList($type) {
    $lists = &$this->drupalStatic->get('system_list');

    if (isset($lists['module_enabled'])) {
      return $lists[$type];
    }

    // Otherwise build the list for enabled modules and themes.
    if ($cached = $this->cache->cacheGet('system_list', 'cache_bootstrap')) {
      $lists = $cached->data;
    }
    else {
      $lists = $this->systemListLoader->loadSystemLists();
      $this->cache->cacheSet('system_list', $lists, 'cache_bootstrap');
    }
    // To avoid a separate database lookup for the filepath, prime the
    // drupal_get_filename() static cache with all enabled modules and themes.
    foreach ($lists['filepaths'] as $item) {
      $this->drupalGetFilename->drupalSetFilename($item['type'], $item['name'], $item['filepath']);
    }

    return $lists[$type];
  }

  /**
   * Replicates system_list('bootstrap')
   *
   * @see system_list()
   *
   * @return array|null
   */
  function systemListBootstrap() {
    $lists = &$this->drupalStatic->get('system_list');

    // For bootstrap modules, attempt to fetch the list from cache if possible.
    // if not fetch only the required information to fire bootstrap hooks
    // in case we are going to serve the page from cache.
    if (isset($lists['bootstrap'])) {
      return $lists['bootstrap'];
    }

    if ($cached = $this->cache->cacheGet('bootstrap_modules', 'cache_bootstrap')) {
      $bootstrap_list = $cached->data;
    }
    else {
      $bootstrap_list = $this->systemListLoader->fetchBootstrapSystemList();
      $this->cache->cacheSet('bootstrap_modules', $bootstrap_list, 'cache_bootstrap');
    }

    // To avoid a separate database lookup for the filepath, prime the
    // drupal_get_filename() static cache for bootstrap modules only.
    // The rest is stored separately to keep the bootstrap module cache small.
    foreach ($bootstrap_list as $module) {
      $this->drupalGetFilename->drupalSetFilename('module', $module->name, $module->filename);
    }

    // We only return the module names here since module_list() doesn't need
    // the filename itself.
    return $lists['bootstrap'] = array_keys($bootstrap_list);
  }

} 
