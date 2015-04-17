<?php
/**
 * @file
 * Defines a test case covering _authcache_enum_cartesian.
 */

namespace Drupal\authcache_enum\Tests;

/**
 * Unit tests for _authcache_enum_comb.
 */
class AuthcacheEnumCartesianTestCase extends \DrupalUnitTestCase {
  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Cartesian product function',
      'description' => 'Unit test for the cartesian product implementation',
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
   * Test calculation of the cartesian product.
   */
  public function testCombineK() {
    $template = array(
      'x' => array(1, 2, 3),
      'y' => array('a', 'b'),
    );

    $expect = array(
      array('x' => 1, 'y' => 'a'),
      array('x' => 2, 'y' => 'a'),
      array('x' => 3, 'y' => 'a'),
      array('x' => 1, 'y' => 'b'),
      array('x' => 2, 'y' => 'b'),
      array('x' => 3, 'y' => 'b'),
    );
    $result = _authcache_enum_cartesian($template);
    $this->assertEqual($expect, $result);
  }
}
