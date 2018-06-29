<?php

namespace Drupal\xautoload\DrupalSystem;

interface DrupalSystemInterface {

  /**
   * Wrapper for variable_set()
   *
   * @param string $name
   * @param mixed $value
   */
  function variableSet($name, $value);

  /**
   * Replacement of variable_get().
   *
   * @param string $name
   * @param mixed $default
   *
   * @return mixed
   *
   * @see variable_get()
   */
  function variableGet($name, $default = NULL);

  /**
   * Replacement of drupal_get_filename(), but returning an absolute file path.
   *
   * @param string $type
   * @param string $name
   *
   * @return string
   *   The result of drupal_get_filename() with DRUPAL_ROOT . '/' prepended.
   *
   * @see drupal_get_filename()
   */
  function drupalGetFilename($type, $name);

  /**
   * Replacement of drupal_get_path(), but returning an absolute directory path.
   *
   * @param string $type
   * @param string $name
   *
   * @return string
   *
   * @see drupal_get_path()
   */
  function drupalGetPath($type, $name);

  /**
   * @param string[] $extension_names
   *   Extension names.
   *
   * @return string[]
   *   Extension types by extension name.
   */
  function getExtensionTypes($extension_names);

  /**
   * Gets active extensions directly from the system table.
   *
   * @return string[]
   *   Extension types by extension name.
   */
  function getActiveExtensions();

  /**
   * Wrapper for module_list()
   *
   * @return array
   */
  function moduleList();

  /**
   * Wrapper for module_implements()
   *
   * @param string $hook
   *
   * @return array[]
   */
  function moduleImplements($hook);

  /**
   * @see libraries_info()
   *
   * @return mixed
   */
  function getLibrariesInfo();

  /**
   * @see libraries_get_path()
   *
   * @param string $name
   *   Name of the library.
   *
   * @return string|false
   */
  function librariesGetPath($name);

  /**
   * Called from xautoload_install() to set the module weight.
   *
   * @param int $weight
   *   New module weight for xautoload.
   */
  public function installSetModuleWeight($weight);

  /**
   * @param string $cid
   * @param string $bin
   *
   * @return object|false
   *   The cache or FALSE on failure.
   *
   * @see cache_get()
   */
  public function cacheGet($cid, $bin = 'cache');

  /**
   * @param string $cid
   * @param mixed $data
   * @param string $bin
   *
   * @return mixed
   *
   * @see cache_set()
   */
  public function cacheSet($cid, $data, $bin = 'cache');

  /**
   * @param string|null $cid
   * @param string|null $bin
   *
   * @see cache_clear_all()
   */
  public function cacheClearAll($cid = NULL, $bin = NULL);

  /**
   * @param string $key
   */
  public function drupalStaticReset($key);

}
