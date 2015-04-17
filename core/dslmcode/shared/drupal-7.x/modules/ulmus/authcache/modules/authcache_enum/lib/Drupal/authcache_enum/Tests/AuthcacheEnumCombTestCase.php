<?php
/**
 * @file
 * Defines a test case covering _authcache_enum_comb.
 */

namespace Drupal\authcache_enum\Tests;

/**
 * Unit tests for _authcache_enum_comb.
 */
class AuthcacheEnumCombTestCase extends \DrupalUnitTestCase {
  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Combine function',
      'description' => 'Unit test for the combine function',
      'group' => 'Authcache Enum',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();

    $module_dir = dirname(dirname(dirname(dirname(dirname(__FILE__)))));
    require_once $module_dir . '/authcache_enum.comb.inc';
  }

  /**
   * Test calculation of k-combinations.
   */
  public function testCombineK() {
    $set = array('a', 'b', 'c', 'd');

    $expect = array(
      array('a'),
      array('b'),
      array('c'),
      array('d'),
    );
    $result = _authcache_enum_comb_k($set, 1);
    $this->assertEqual($expect, $result);

    $expect = array(
      array('a', 'b'),
      array('a', 'c'),
      array('a', 'd'),
      array('b', 'c'),
      array('b', 'd'),
      array('c', 'd'),
    );
    $result = _authcache_enum_comb_k($set, 2);
    $this->assertEqual($expect, $result);

    $expect = array(
      array('a', 'b', 'c'),
      array('a', 'b', 'd'),
      array('a', 'c', 'd'),
      array('b', 'c', 'd'),
    );
    $result = _authcache_enum_comb_k($set, 3);
    $this->assertEqual($expect, $result);
  }

  /**
   * Test calculation of k-combinations where k is out of range.
   */
  public function testCombineKOffLimit() {
    $set = array('a', 'b', 'c', 'd');

    $expect = array(
      array('a'),
      array('b'),
      array('c'),
      array('d'),
    );
    $result = _authcache_enum_comb_k($set, 0);
    $this->assertEqual($expect, $result);

    $expect = array(
      array('a', 'b', 'c', 'd'),
    );
    $result = _authcache_enum_comb_k($set, 4);
    $this->assertEqual($expect, $result);
  }

  /**
   * Test calculation of combinations.
   */
  public function testCombine() {
    $set = array('a', 'b', 'c', 'd');

    $expect = array(
      array('a'),
      array('b'),
      array('c'),
      array('d'),
      array('a', 'b'),
      array('a', 'c'),
      array('a', 'd'),
      array('b', 'c'),
      array('b', 'd'),
      array('c', 'd'),
      array('a', 'b', 'c'),
      array('a', 'b', 'd'),
      array('a', 'c', 'd'),
      array('b', 'c', 'd'),
      array('a', 'b', 'c', 'd'),
    );
    $result = _authcache_enum_comb($set);
    $this->assertEqual($expect, $result);
  }
}
