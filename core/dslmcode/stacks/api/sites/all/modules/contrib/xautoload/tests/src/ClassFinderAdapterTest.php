<?php

namespace Drupal\xautoload\Tests;

use Drupal\xautoload\Tests\Filesystem\StreamWrapper;
use Drupal\xautoload\Tests\Filesystem\VirtualFilesystem;

class ClassFinderAdapterTest extends \PHPUnit_Framework_TestCase {

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

  /**
   * Test hook_registry_files_alter() wildcard replacement.
   */
  public function testWildcardClassmap() {
    $this->filesystem->addClass('test://lib/xy/z.php', 'Foo\Bar');

    $this->assertFalse(class_exists('Foo\Bar', FALSE), 'Class Foo\Bar must not exist yet.');
    xautoload()->adapter->addClassmapSources(array('test://lib/**/*.php'));
    $this->assertTrue(class_exists('Foo\Bar'), 'Class Foo\Bar must exist.');
  }
} 
