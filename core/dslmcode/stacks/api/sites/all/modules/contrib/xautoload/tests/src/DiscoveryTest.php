<?php

namespace Drupal\xautoload\Tests;

use Drupal\xautoload\Discovery\WildcardFileFinder;

class DiscoveryTest extends \PHPUnit_Framework_TestCase {

  /**
   * Test hook_registry_files_alter() wildcard replacement.
   */
  public function testWildcardFileFinder() {

    $files_relative = array(
      'foo/bar.inc',
      'handlers/*.inc',
      'modules/*/**/*.inc',
      'tests/**/*.test',
      'misc/**',
    );

    $files = array();
    foreach ($files_relative as $file) {
      $file = dirname(__DIR__) . '/fixtures/WildcardFileFinder/' . $file;
      $files[$file] = array('module' => 'views', 'weight' => 0);
    }

    // The class file is loaded using the regular uncached xautoload autoload.
    $file_finder = new WildcardFileFinder();
    $file_finder->addDrupalPaths($files, TRUE);
    $files = $file_finder->getDrupalFiles();

    // The order of scandir() cannot be predicted, therefore only the sorted
    // list of files is being compared here.
    ksort($files);

    $expected = array (
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/foo/bar.inc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/handlers/bar.inc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/handlers/foo.inc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/misc/abc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/misc/foo.bar',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/misc/sub/xyz',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/modules/sub/foo.inc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/modules/sub/sub/foo.inc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/modules/sub/sub/sub/foo.inc',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/tests/foo.test',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/tests/sub/foo.test',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/tests/sub/sub/foo.test',
      dirname(__DIR__) . '/fixtures/WildcardFileFinder/tests/sub/sub/sub/foo.test',
    );

    $expected = array_fill_keys(
      $expected,
      array (
        'module' => 'views',
        'weight' => 0,
      ));

    $this->assertEquals($expected, $files);
  }

} 
