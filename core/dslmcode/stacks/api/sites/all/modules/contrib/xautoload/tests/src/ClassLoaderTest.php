<?php

namespace Drupal\xautoload\Tests;

use Drupal\xautoload\ClassFinder\ClassFinder;
use Drupal\xautoload\DirectoryBehavior\Psr0DirectoryBehavior;
use Drupal\xautoload\Tests\Filesystem\StreamWrapper;
use Drupal\xautoload\Tests\Filesystem\VirtualFilesystem;

class ClassLoaderTest extends \PHPUnit_Framework_TestCase {

  /**
   * @var VirtualFilesystem
   */
  protected $filesystem;

  function setUp() {
    parent::setUp();
    $this->filesystem = StreamWrapper::register('test');
  }

  function tearDown() {
    stream_wrapper_unregister('test');
    parent::tearDown();
  }

  //                                                                Test methods
  // ---------------------------------------------------------------------------

  /**
   * Test PSR-4-like namespaces.
   */
  function testPsr4() {

    // Prepare the class finder.
    $finder = new ClassFinder();

    $finder->addPsr4('Drupal\ex_ample\\', 'test://base/lib/');

    $this->assertCandidateOrder(
      $finder,
      'Drupal\ex_ample\Psr4_%\Foo_Bar',
      array('test://base/lib/Psr4_%/Foo_Bar.php'));
  }

  /**
   * Test PSR-0-like namespaces.
   */
  function testNamespaces() {

    // Prepare the class finder.
    $finder = new ClassFinder();
    $psr0 = new Psr0DirectoryBehavior();

    $finder->registerNamespaceDeep('Drupal\\ex_ample', 'test://base/lib', $psr0);
    $finder->registerNamespaceRoot('Drupal\\ex_ample', 'test://base/vendor', $psr0);

    $this->assertCandidateOrder(
      $finder,
      'Drupal\ex_ample\Sub_%\Foo_Bar',
      array(
        'test://base/lib/Sub_%/Foo/Bar.php',
        'test://base/vendor/Drupal/ex_ample/Sub_%/Foo/Bar.php',
      ));
  }

  /**
   * Test PEAR-like prefixes.
   */
  function testPrefixes() {

    // Prepare the class finder.
    $finder = new ClassFinder();

    $finder->registerPrefixDeep('ex_ample', 'test://base/lib');
    $finder->registerPrefixRoot('ex_ample', 'test://base/vendor');

    $this->assertCandidateOrder(
      $finder,
      'ex_ample_Sub%_Foo',
      array(
        'test://base/lib/Sub%/Foo.php',
        'test://base/vendor/ex/ample/Sub%/Foo.php',
      ));
  }

  /**
   * Tests PEAR-like class names beginning with underscore, or with a double
   * underscore in between.
   */
  function testSpecialUnderscores() {

    // Prepare the class finder.
    $finder = new ClassFinder();

    $finder->registerPrefixDeep('_ex_ample', 'test://lib');
    $finder->registerPrefixRoot('_ex_ample', 'test://vendor');

    // Verify that underscores are not a problem..
    $this->assertCandidateOrder(
      $finder,
      '_ex_ample_Abc%_Def', array(
        'test://lib/Abc%/Def.php',
        'test://vendor/_ex/ample/Abc%/Def.php',
      ));
    $this->assertCandidateOrder($finder, '_abc_Foo%', array());
    $this->assertCandidateOrder($finder, 'abc__Foo%', array());
  }

  //                                                           Assertion helpers
  // ---------------------------------------------------------------------------

  /**
   * @param \Drupal\xautoload\ClassLoader\ClassLoaderInterface $loader
   * @param string $class
   * @param string $file
   */
  protected function assertLoadClass($loader, $class, $file) {

    // Register the class file in the virtual filesystem.
    $this->filesystem->addClass($file, $class);

    // Check that the class is not already defined.
    $this->assertFalse(class_exists($class, FALSE));

    // Trigger the class loader.
    $loader->loadClass($class);

    // Check that the class is defined after the class loader has done its job.
    $this->assertTrue(class_exists($class, FALSE));
  }

  /**
   * @param \Drupal\xautoload\ClassLoader\ClassLoaderInterface $loader
   * @param string $classTemplate
   * @param string[] $expectedCandidateTemplates
   */
  protected function assertCandidateOrder($loader, $classTemplate, array $expectedCandidateTemplates) {
    for ($i = 0; $i < count($expectedCandidateTemplates); ++$i) {
      $class = $this->replaceWildcard($classTemplate, "n$i");
      // If str_replace() is called with an array as 3rd parameter, it will do
      // the replacement on all array elements.
      $expectedCandidates = $this->replaceWildcardMultiple(array_slice($expectedCandidateTemplates, 0, $i + 1), "n$i");
      $this->assertFileInclusions($loader, $class, $expectedCandidates);
    }
  }

  /**
   * Assert that inclusions are done in the expected order.
   *
   * @param \Drupal\xautoload\ClassLoader\ClassLoaderInterface $loader
   * @param string $class
   * @param string[] $expectedCandidates
   */
  protected function assertFileInclusions($loader, $class, array $expectedCandidates) {

    // Register the class file in the virtual filesystem.
    $this->filesystem->addClass(end($expectedCandidates), $class);

    $this->filesystem->resetReportedOperations();

    // Check that the class is not already defined.
    $this->assertFalse(class_exists($class, FALSE), "Class '$class' is not defined before loadClass().");

    // Trigger the class loader.
    $loader->loadClass($class);

    $expectedOperations = array();
    foreach ($expectedCandidates as $file) {
      $expectedOperations[] = $file . ' - stat';
    }
    $expectedOperations[] = end($expectedCandidates) . ' - include';
    $this->assertSame($expectedOperations, $this->filesystem->getReportedOperations());

    // Check that the class is defined after the class loader has done its job.
    $this->assertTrue(class_exists($class, FALSE), "Class is defined after loadClass().");
  }

  /**
   * @param string[] $strings
   * @param string $replacement
   *
   * @return string[]
   */
  protected function replaceWildcardMultiple(array $strings, $replacement) {
    foreach ($strings as &$str) {
      $str = $this->replaceWildcard($str, $replacement);
    }
    return $strings;
  }

  /**
   * @param string $str
   * @param string $replacement
   *
   * @return string
   *
   * @throws \Exception
   */
  protected function replaceWildcard($str, $replacement) {
    $fragments = explode('%', $str);
    if (count($fragments) < 2) {
      throw new \Exception("String '$str' does not contain a '%' wildcard.");
    }
    if (count($fragments) > 2) {
      throw new \Exception("String '$str' has more than one '%' wildcard.");
    }
    return str_replace('%', $replacement, $str);
  }
}
