<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class ModuleImplements {

  /**
   * @var Cache
   */
  private $cache;

  /**
   * @var ModuleList
   */
  private $moduleList;

  /**
   * @var HookSystem
   */
  private $hookSystem;

  /**
   * @var array[]
   */
  private $drupalStaticFast;

  /**
   * Replacement for $implementations['#write_cache'].
   *
   * @var bool
   */
  private $writeCache = FALSE;

  /**
   * @var DrupalStatic
   */
  private $drupalStatic;

  /**
   * @param DrupalStatic $drupalStatic
   * @param Cache $cache
   * @param ModuleList $moduleList
   * @param HookSystem $hookSystem
   */
  function __construct(DrupalStatic $drupalStatic, Cache $cache, ModuleList $moduleList, HookSystem $hookSystem) {
    $this->drupalStatic = $drupalStatic;
    $this->cache = $cache;
    $this->moduleList = $moduleList;
    $this->hookSystem = $hookSystem;
  }

  /**
   * Replicates module_implements(*, *, TRUE)
   *
   * @see module_implements()
   *
   * @return null
   */
  function reset() {

    // Use the advanced drupal_static() pattern, since this is called very often.
    if (!isset($this->drupalStaticFast)) {
      $this->drupalStaticFast['implementations'] = &$this->drupalStatic->get('module_implements');
    }
    $implementations = &$this->drupalStaticFast['implementations'];

    $implementations = array();
    $this->cache->cacheSet('module_implements', array(), 'cache_bootstrap');
    $this->drupalStatic->resetKey('module_hook_info');
    $this->drupalStatic->resetKey('drupal_alter');
    $this->cache->cacheClearAll('hook_info', 'cache_bootstrap');
    return NULL;
  }

  /**
   * @see module_implements()
   *
   * @param string $hook
   * @param bool $sort
   *
   * @return array
   */
  function moduleImplements($hook, $sort = FALSE) {

    // Use the advanced drupal_static() pattern, since this is called very often.
    if (!isset($this->drupalStaticFast)) {
      $this->drupalStaticFast['implementations'] = &$this->drupalStatic->get('module_implements');
    }
    $implementations = &$this->drupalStaticFast['implementations'];

    // Fetch implementations from cache.
    if (empty($implementations)) {
      $cache = $this->cache->cacheGet('module_implements', 'cache_bootstrap');
      if (FALSE === $cache) {
        $implementations = array();
      }
      else {
        $implementations = $cache->data;
      }
    }

    if (!isset($implementations[$hook])) {
      $implementations[$hook] = $this->discoverImplementations($hook, $sort);
    }
    else {
      // @todo Change this when https://drupal.org/node/2263365 has landed in Drupal core.
      $this->filterImplementations($implementations[$hook], $hook);
    }

    return array_keys($implementations[$hook]);
  }

  /**
   * @param string $hook
   * @param bool $sort
   *
   * @return array
   */
  private function discoverImplementations($hook, $sort) {

    # StaticCallLog::addCall();

    // The hook is not cached, so ensure that whether or not it has
    // implementations, that the cache is updated at the end of the request.
    $this->writeCache = TRUE;
    $hook_info = $this->moduleHookInfo();
    $implementations = array();
    $list = $this->moduleList->moduleList(FALSE, FALSE, $sort);

    if ('modules_enabled' === $hook) {
      # HackyLog::logx($list);
    }

    foreach ($list as $module) {
      $include_file = isset($hook_info[$hook]['group'])
        && module_load_include('inc', $module, $module . '.' . $hook_info[$hook]['group']);
      // Since module_hook() may needlessly try to load the include file again,
      // function_exists() is used directly here.
      if (function_exists($module . '_' . $hook)) {
        $implementations[$module] = $include_file
          ? $hook_info[$hook]['group']
          : FALSE;
      }
    }

    // Allow modules to change the weight of specific implementations but avoid
    // an infinite loop.
    if ($hook != 'module_implements_alter') {
      $this->hookSystem->drupalAlter('module_implements', $implementations, $hook);
    }

    return $implementations;
  }

  /**
   * @param array &$implementations
   * @param string $hook
   */
  private function filterImplementations(&$implementations, $hook) {
    foreach ($implementations as $module => $group) {
      // If this hook implementation is stored in a lazy-loaded file, so include
      // that file first.
      if ($group) {
        module_load_include('inc', $module, "$module.$group");
      }
      // It is possible that a module removed a hook implementation without the
      // implementations cache being rebuilt yet, so we check whether the
      // function exists on each request to avoid undefined function errors.
      // Since module_hook() may needlessly try to load the include file again,
      // function_exists() is used directly here.
      if (!function_exists($module . '_' . $hook)) {
        // Clear out the stale implementation from the cache and force a cache
        // refresh to forget about no longer existing hook implementations.
        unset($implementations[$module]);
        $this->writeCache = TRUE;
      }
    }
  }


  /**
   * Replicates module_hook_info() for some known hooks.
   *
   * @return array
   *   An associative array whose keys are hook names and whose values are an
   *   associative array containing a group name. The structure of the array
   *   is the same as the return value of hook_hook_info().
   *
   * @see hook_hook_info()
   */
  private function moduleHookInfo() {
    // No core modules implement hook_hook_info().
    return array();
  }
} 
