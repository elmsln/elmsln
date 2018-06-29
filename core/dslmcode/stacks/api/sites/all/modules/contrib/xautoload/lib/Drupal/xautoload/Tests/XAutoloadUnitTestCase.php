<?php

namespace Drupal\xautoload\Tests;

use Drupal\xautoload\ClassFinder\ClassFinder;
use Drupal\xautoload\ClassFinder\InjectedApi\CollectFilesInjectedApi;
use Drupal\xautoload\ClassLoader\ClassLoaderInterface;
use Drupal\xautoload\Util;

class XAutoloadUnitTestCase extends \DrupalUnitTestCase {

  static function getInfo() {
    return array(
      'name' => 'X Autoload unit test',
      'description' => 'Test the xautoload class finder.',
      'group' => 'X Autoload',
    );
  }

  function setUp() {

    // drupal_load('module', 'xautoload') would register namespaces for all
    // enabled modules, which is not intended for this unit test.
    // Instead, we just include xautoload.early.inc.
    require_once __DIR__ . '/../../../../xautoload.early.inc';

    // Make sure we use the regular loader, not the APC one.
    // Also make sure to prepend this one. Otherwise, the core class loader will
    // try to load xautoload-related stuff, e.g. xautoload_Mock_* stuff, and
    // will fail due to the database.
    foreach (spl_autoload_functions() as $callback) {
      if (is_array($callback)
        && ($loader = $callback[0])
        && $loader instanceof ClassLoaderInterface
      ) {
        $loader->unregister();
      }
    }
    xautoload()->finder->register(TRUE);

    // Do the regular setUp().
    parent::setUp();
  }

  function testAutoloadStackOrder() {
    $expected = array(
      'Drupal\\xautoload\\ClassFinder\\ClassFinder->loadClass()',
      /* @see _drupal_bootstrap_database() */
      'drupal_autoload_class',
      'drupal_autoload_interface',
      /* @see simpletest_classloader_register() */
      '_simpletest_autoload_psr4_psr0',
    );

    $actual = array();
    foreach (spl_autoload_functions() as $callback) {
      $actual[] = Util::callbackToString($callback);
    }

    $this->assertEqualBlock($expected, $actual, "SPL autoload stack:");
  }

  function testNamespaces() {

    // Prepare the class finder.
    $finder = new ClassFinder();
    $finder->add('Drupal\\ex_ample', 'sites/all/modules/contrib/ex_ample/lib-psr0');
    $finder->addPsr4('Drupal\\ex_ample', 'sites/all/modules/contrib/ex_ample/lib-psr4');

    // Test class finding for 'Drupal\\ex_ample\\Abc_Def'.
    $this->assertFinderSuggestions($finder, 'Drupal\\ex_ample\\Abc_Def', array(
      // Class finder is expected to suggest these files, in the exact order,
      // until one of them is accepted.
      array('suggestFile', 'sites/all/modules/contrib/ex_ample/lib-psr0/Drupal/ex_ample/Abc/Def.php'),
      array('suggestFile', 'sites/all/modules/contrib/ex_ample/lib-psr4/Abc_Def.php'),
    ));
  }

  function testPrefixes() {

    // Prepare the class finder.
    $finder = new ClassFinder();
    $finder->registerPrefixDeep('ex_ample', 'sites/all/modules/contrib/ex_ample/lib');
    $finder->registerPrefixRoot('ex_ample', 'sites/all/modules/contrib/ex_ample/vendor');

    // Test class finding for 'ex_ample_Abc_Def'.
    $this->assertFinderSuggestions($finder, 'ex_ample_Abc_Def', array(
      // Class finder is expected to suggest these files, in the exact order,
      // until one of them is accepted.
      array('suggestFile', 'sites/all/modules/contrib/ex_ample/lib/Abc/Def.php'),
      array('suggestFile', 'sites/all/modules/contrib/ex_ample/vendor/ex/ample/Abc/Def.php'),
    ));
  }

  /**
   * @param ClassFinder $finder
   * @param string $class
   * @param array $expectedSuggestions
   *
   * @return bool
   *   Result of the assertion
   */
  protected function assertFinderSuggestions($finder, $class, array $expectedSuggestions) {
    $success = TRUE;
    for ($iAccept = 0; $iAccept < count($expectedSuggestions); ++$iAccept) {
      list($method_name, $file) = $expectedSuggestions[$iAccept];
      $api = new CollectFilesInjectedApi($class, $method_name, $file);
      $finder->apiFindFile($api, $class);
      $suggestions = $api->getSuggestions();
      $expected = array_slice($expectedSuggestions, 0, $iAccept + 1);
      $success = $success && $this->assertEqualBlock($expected, $suggestions, "Finder suggestions for class <code>$class</code>:");
    }
    return $success;
  }

  /**
   * @param mixed $expected
   * @param mixed $actual
   * @param string $label
   *
   * @return bool
   *   Result of the assertion
   */
  protected function assertEqualBlock($expected, $actual, $label) {
    $label .= '<br/>' .
      'Expected: <pre>' . var_export($expected, TRUE) . '</pre>' .
      'Actual: <pre>' . var_export($actual, TRUE) . '</pre>';
    return $this->assertEqual($expected, $actual, $label);
  }
}
