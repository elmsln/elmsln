<?php
/**
 * @file
 * Defines a test case covering _authcache_enum_cartesian.
 */

namespace Drupal\authcache_enum\Tests;

/**
 * Unit tests for _authcache_enum_comb.
 */
class AuthcacheEnumKeysTestCase extends \DrupalWebTestCase {
  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Key enumeration',
      'description' => 'Tests for key enumeration',
      'group' => 'Authcache Enum',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp('authcache_enum');
  }

  /**
   * Test enumeration of anonymous and authenticated keys.
   */
  public function testKeyEnumKeys() {
    global $base_root;

    variable_set('authcache_roles', array());

    $expect = array(
      $base_root,
    );
    $result = authcache_enum_keys();
    $this->assertEqual($expect, $result);

    drupal_static_reset();

    // Test anonymous and authenticated roles.
    variable_set('authcache_roles', array(
      DRUPAL_ANONYMOUS_RID => DRUPAL_ANONYMOUS_RID,
      DRUPAL_AUTHENTICATED_RID => DRUPAL_AUTHENTICATED_RID,
    ));

    $result = authcache_enum_keys();
    $anonymous_key = array_pop($result);
    $this->assertEqual($base_root, $anonymous_key);

    // Expect 1 additional key for authenticated users.
    $this->assertEqual(1, count($result));

    drupal_static_reset();

    // Test additional roles.
    $rid1 = $this->drupalCreateRole(array());
    $rid2 = $this->drupalCreateRole(array());
    variable_set('authcache_roles', array(
      DRUPAL_ANONYMOUS_RID => DRUPAL_ANONYMOUS_RID,
      DRUPAL_AUTHENTICATED_RID => DRUPAL_AUTHENTICATED_RID,
      $rid1 => $rid1,
      $rid2 => $rid2,
    ));

    $result = authcache_enum_keys();
    $anonymous_key = array_pop($result);
    $this->assertEqual($base_root, $anonymous_key);

    // Expect 4 keys for authenticated users:
    // * Only authenticated rid
    // * Only rid1
    // * Only rid2
    // * rid1 and rid2
    $this->assertEqual(4, count($result));
  }
}
