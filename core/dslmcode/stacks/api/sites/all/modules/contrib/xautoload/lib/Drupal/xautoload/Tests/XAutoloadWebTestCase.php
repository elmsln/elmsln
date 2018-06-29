<?php

namespace Drupal\xautoload\Tests;

class XAutoloadWebTestCase extends \DrupalWebTestCase {

  /**
   * {@inheritdoc}
   */
  static function getInfo() {
    return array(
      'name' => 'X Autoload web test',
      'description' => 'Test xautoload class loading for an example module.',
      'group' => 'X Autoload',
    );
  }

  /**
   * {@inheritdoc}
   */
  function setUp() {
    parent::setUp();
  }

  /**
   *
   */
  function testNoCache() {
    $this->xautoloadTestWithCacheTypes(array(), TRUE);
  }

  /**
   *
   */
  function testApcCache() {
    $cache_types = array(
      'apc' => 'apc',
      'xcache' => 'xcache',
      'wincache' => 'wincache',
    );
    $this->xautoloadTestWithCacheTypes($cache_types, TRUE);
  }

  /**
   * @param array $cache_types
   *   The autoloader modes that are enabled, e.g.
   *   array('apc' => 'apc', 'xcache' => 'xcache')
   * @param bool $cache_lazy
   *   Whether the "lazy" mode is enabled.
   */
  protected function xautoloadTestWithCacheTypes($cache_types, $cache_lazy) {

    variable_set(XAUTOLOAD_VARNAME_CACHE_TYPES, $cache_types);
    $this->pass("Set cache types: " . var_export($cache_types, TRUE));

    variable_set(XAUTOLOAD_VARNAME_CACHE_LAZY, $cache_lazy);
    $this->pass("Set cache lazy mode: " . var_export($cache_lazy, TRUE));

    // Enable xautoload.
    module_enable(array('xautoload'), FALSE);

    // At this time the xautoload_cache_mode setting is not in effect yet,
    // so we have to clear old cached values from APC cache.
    xautoload()->cacheManager->renewCachePrefix();

    module_enable(array(
      'xautoload_test_1',
      'xautoload_test_2',
      'xautoload_test_3',
      'xautoload_test_4',
      'xautoload_test_5',
    ), FALSE);
    menu_rebuild();

    foreach (array(
      'xautoload_test_1' => array('Drupal\xautoload_test_1\ExampleClass'),
      'xautoload_test_2' => array('xautoload_test_2_ExampleClass'),
      'xautoload_test_3' => array('Drupal\xautoload_test_3\ExampleClass'),
    ) as $module => $classes) {
      $classes_on_include = in_array($module, array('xautoload_test_2', 'xautoload_test_3'));
      $this->xautoloadModuleEnabled($module, $classes, $classes_on_include);
      $this->xautoloadModuleCheckJson($module, $cache_types, $cache_lazy, $classes);
    }
  }

  /**
   * @param string $module
   * @param string[] $classes
   * @param bool $classes_on_include
   */
  protected function xautoloadModuleEnabled($module, $classes, $classes_on_include) {

    EnvironmentSnapshotMaker::takeSnapshot($module, 'later', $classes);

    $all = EnvironmentSnapshotMaker::getSnapshots($module);

    foreach ($all as $phase => $observations) {
      $when = ($phase === 'early')
        ? 'on drupal_load() during module_enable()'
        : (($phase === 'later')
          ? 'after hook_modules_enabled()'
          : 'at an undefined time'
        );

      // Test the classes of the example module.
      foreach ($classes as $class) {
        // Test that the class was already found in $phase.
        $this->assertTrue(isset($observations['class_exists'][$class]), "Class $class was checked $when.");
        if ($classes_on_include || $phase !== 'early') {
          $this->assertTrue($observations['class_exists'][$class], "Class $class was found $when.");
        }
        else {
          $this->assertFalse($observations['class_exists'][$class], "Class $class cannot be found $when.");
        }
      }
    }
  }

  /**
   * @param string $module
   * @param array $cache_types
   *   The autoloader modes that are enabled, e.g.
   *   array('apc' => 'apc', 'xcache' => 'xcache')
   * @param bool $cache_lazy
   *   Whether the "lazy" mode is enabled.
   * @param string[] $classes
   */
  protected function xautoloadModuleCheckJson($module, $cache_types, $cache_lazy, $classes) {

    $path = "$module.json";
    $json = $this->drupalGet($path);
    $all = json_decode($json, TRUE);

    if (!is_array($all) || empty($all)) {
      $this->fail("$path must return a non-empty json array.");
      return;
    }

    foreach ($all as $phase => $observations) {

      $when = ($phase === 'early')
        ? 'on early bootstrap'
        : (($phase === 'boot')
          ? 'during hook_boot()'
          : 'at an undefined time'
        );

      $this->xautoloadCheckTestEnvironment($observations, $cache_types, $cache_lazy, $when);

      // Test the classes of the example module.
      foreach ($classes as $class) {
        // Test that the class was already found in $phase.
        $this->assertTrue($observations['class_exists'][$class], "Class $class was found $when.");
      }
    }
  }

  /**
   * @param array $observations
   * @param array $cache_types
   *   The autoloader modes that are enabled, e.g.
   *   array('apc' => 'apc', 'xcache' => 'xcache')
   * @param bool $lazy
   *   Whether the "lazy" mode is enabled.
   * @param $when
   */
  protected function xautoloadCheckTestEnvironment($observations, $cache_types, $lazy, $when) {

    // Check early-bootstrap variables.
    $label = "$when: xautoload_cache_types:";
    $this->assertEqualBlock($cache_types, $observations[XAUTOLOAD_VARNAME_CACHE_TYPES], $label);

    $label = "$when: xautoload_cache_lazy:";
    $this->assertEqualInline($lazy, $observations[XAUTOLOAD_VARNAME_CACHE_LAZY], $label);

    // Check registered class loaders.
    $expected = $this->expectedAutoloadStackOrder($cache_types);
    $actual = $observations['spl_autoload_functions'];
    $label = "$when: spl autoload stack:";
    $this->assertEqualBlock($expected, $actual, $label);
  }

  /**
   * @param string $cache_types
   *   The autoloader modes that are enabled, e.g.
   *   array('apc' => 'apc', 'xcache' => 'xcache')
   *
   * @return string[]
   *   Expected order of class loaders on the spl autoload stack for the given
   *   autoloader mode. Each represented by a string.
   */
  protected function expectedAutoloadStackOrder($cache_types) {

    if (!empty($cache_types['apc']) && extension_loaded('apc') && function_exists('apc_store')) {
      $loader = 'Drupal\xautoload\ClassLoader\ApcClassLoader->loadClass()';
    }
    elseif (!empty($cache_types['wincache']) && extension_loaded('wincache') && function_exists('wincache_ucache_get')) {
      $loader = 'Drupal\xautoload\ClassLoader\WinCacheClassLoader->loadClass()';
    }
    elseif (!empty($cache_types['xcache']) && extension_loaded('Xcache') && function_exists('xcache_get')) {
      $loader = 'Drupal\xautoload\ClassLoader\XCacheClassLoader->loadClass()';
    }
    else {
      $loader = 'Drupal\xautoload\ClassFinder\ClassFinder->loadClass()';
    }

    return array(
      'drupal_autoload_class',
      'drupal_autoload_interface',
      $loader,
    );
  }

  /**
   * Assert that a module is disabled.
   *
   * @param string $module
   */
  protected function assertModuleDisabled($module) {
    $this->assertFalse(module_exists($module), "Module $module is disabled.");
  }

  /**
   * Assert that a module is enabled.
   *
   * @param string $module
   */
  protected function assertModuleEnabled($module) {
    $this->assertTrue(module_exists($module), "Module $module is enabled.");
  }

  /**
   * Assert that a class is defined.
   *
   * @param string $class
   */
  protected function assertClassExists($class) {
    $this->assertTrue(class_exists($class), "Class '$class' must exist.");
  }

  /**
   * @param mixed $expected
   * @param mixed $actual
   * @param string $label
   */
  protected function assertEqualBlock($expected, $actual, $label) {
    $label .=
      'Expected: <pre>' . var_export($expected, TRUE) . '</pre>' .
      'Actual: <pre>' . var_export($actual, TRUE) . '</pre>';
    $this->assertEqual($expected, $actual, $label);
  }

  /**
   * @param mixed $expected
   * @param mixed $actual
   * @param string $label
   */
  protected function assertEqualInline($expected, $actual, $label) {
    $label .= '<br/>' .
      'Expected: <code>' . var_export($expected, TRUE) . '</code><br/>' .
      'Actual: <code>' . var_export($actual, TRUE) . '</code>';
    $this->assertEqual($expected, $actual, $label);
  }
}
