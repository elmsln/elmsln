<?php


namespace Drupal\xautoload\Tests;

use Drupal\xautoload\Adapter\ClassFinderAdapter;
use Drupal\xautoload\Adapter\LocalDirectoryAdapter;
use Drupal\xautoload\ClassFinder\ClassFinder;
use Drupal\xautoload\Discovery\ClassMapGenerator;

class ComposerJsonTest extends \PHPUnit_Framework_TestCase {

  function testComposerJson() {
    $finder = new ClassFinder();
    $masterAdapter = new ClassFinderAdapter($finder, new ClassMapGenerator());
    foreach (array(
      dirname(__DIR__) . '/fixtures/.libraries/ComposerTestLib' => array(
        'ComposerTestLib\Foo',
        'ComposerTestLib\Other\Foo',
      ),
      dirname(__DIR__) . '/fixtures/.libraries/ComposerTargetDirTestLib' => array(
        'Acme\ComposerTargetDirTestLib\Foo',
      ),
    ) as $dir => $classes) {
      $localDirectoryAdapter = new LocalDirectoryAdapter($masterAdapter, $dir);
      $localDirectoryAdapter->composerJson('composer.json');
      foreach ($classes as $class) {
        $this->assertFalse(class_exists($class, FALSE), "Class $class not defined yet.");
        $finder->loadClass($class);
        $this->assertTrue(class_exists($class, FALSE), "Class $class is defined.");
      }
    }
  }

} 
