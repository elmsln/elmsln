<?php

namespace Drupal\xautoload\DrupalSystem;

class DrupalSystem implements DrupalSystemInterface {

  function __construct() {
    if (!function_exists('drupal_get_filename')) {
      throw new \Exception("This class works only within a working Drupal environment.");
    }
  }

  /**
   * {@inheritdoc}
   */
  function variableSet($name, $value) {
    variable_set($name, $value);
  }

  /**
   * {@inheritdoc}
   */
  function variableGet($name, $default = NULL) {
    return variable_get($name, $default);
  }

  /**
   * {@inheritdoc}
   */
  function drupalGetFilename($type, $name) {
    return DRUPAL_ROOT . '/' . drupal_get_filename($type, $name);
  }

  /**
   * {@inheritdoc}
   */
  function drupalGetPath($type, $name) {
    return DRUPAL_ROOT . '/' . drupal_get_path($type, $name);
  }

  /**
   * {@inheritdoc}
   */
  function getExtensionTypes($extension_names) {
    $q = db_select('system');
    $q->condition('name', $extension_names);
    $q->fields('system', array('name', 'type'));

    return $q->execute()->fetchAllKeyed();
  }

  /**
   * {@inheritdoc}
   */
  function getActiveExtensions() {
    try {
      // Doing this directly tends to be a lot faster than system_list().
      return db_query("SELECT name, type from {system} WHERE status = 1")
        ->fetchAllKeyed();
    }
    catch (\DatabaseConnectionNotDefinedException $e) {
      // During install, the database is not available.
      // At this time only the system module is "installed".
      /** See https://www.drupal.org/node/2393205 */
      return array('system' => 'module');
    }
    catch (\PDOException $e) {
      // Some time later during install, there is a database but not yet a system table.
      // At this time only the system module is "installed".
      // @todo Check if this is really a "Table 'system' doesn't exist'" exception.
      return array('system' => 'module');
    }
  }

  /**
   * {@inheritdoc}
   */
  function moduleImplements($hook) {
    return module_implements($hook);
  }

  /**
   * Wrapper for module_list()
   *
   * @return array
   */
  function moduleList() {
    return module_list();
  }

  /**
   * @see libraries_info()
   *
   * @throws \Exception
   * @return mixed
   */
  function getLibrariesInfo() {
    if (!function_exists('libraries_info')) {
      // Libraries is at a lower version, which does not have this function.
      return array();
    }
    # drupal_static_reset('libraries_info');
    return libraries_info();
  }

  /**
   * @see libraries_get_path()
   *
   * @param string $name
   *   Name of the library.
   *
   * @throws \Exception
   * @return string|false
   */
  function librariesGetPath($name) {
    if (!function_exists('libraries_get_path')) {
      throw new \Exception('Function libraries_get_path() does not exist.');
    }
    return libraries_get_path($name);
  }

  /**
   * Called from xautoload_install() to set the module weight.
   *
   * @param int $weight
   *   New module weight for xautoload.
   */
  public function installSetModuleWeight($weight) {
    db_update('system')
      ->fields(array('weight' => $weight))
      ->condition('name', 'xautoload')
      ->condition('type', 'module')
      ->execute();
    system_list_reset();
  }

  /**
   * @param string $cid
   * @param string $bin
   *
   * @return mixed
   *
   * @see cache_get()
   */
  public function cacheGet($cid, $bin = 'cache') {
    return cache_get($cid, $bin);
  }

  /**
   * @param string $cid
   * @param mixed $data
   * @param string $bin
   *
   * @return mixed
   *
   * @see cache_set()
   */
  public function cacheSet($cid, $data, $bin = 'cache') {
    cache_set($cid, $data, $bin);
  }

  /**
   * @param string|null $cid
   * @param string|null $bin
   *
   * @see cache_clear_all()
   */
  public function cacheClearAll($cid = NULL, $bin = NULL) {
    cache_clear_all($cid, $bin);
  }

  /**
   * @param string $key
   */
  public function drupalStaticReset($key) {
    \drupal_static_reset($key);
  }
}
