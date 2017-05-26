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
    parent::setUp('authcache_enum', 'authcache_enum_test');

    // HookStub.
    $this->stubmod = new \ModuleStub('authcache_enum_test');
  }

  /**
   * Test whether the given stub passes the invocation verifier.
   */
  protected function assertStub(\HookStubProxy $stub, $verifier, $message = NULL) {
    $result = $stub->verify($verifier, $error);

    if (!$message) {
      $message = t('Verify invocation of hook @hook.', array('@hook' => $stub->hookname()));
    }
    if (!$result && is_string($error)) {
      $message .= ' ' . $error;
    }

    $this->assertTRUE($result, $message);
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

  /**
   * Test anonymous key customization.
   */
  public function testCustomAnonymousKeys() {
    global $base_root;

    $keys = array(
      $this->randomName(6),
      $this->randomName(7),
      $this->randomName(8),
    );

    $delete_key = $keys[1];
    $insert_key = $this->randomName(9);

    $alter_keys = array(
      'delete' => array($base_root, $delete_key),
      'insert' => array($insert_key),
    );

    $expected_keys = array(
      $keys[0],
      $keys[2],
      $insert_key,
    );

    $keystub = $this->stubmod->hook('authcache_enum_anonymous_keys', $keys);
    $alterstub = $this->stubmod->hook('authcache_enum_anonymous_keys_alter', $alter_keys);
    $result = authcache_enum_keys();
    $this->assertStub($keystub, \HookStub::once());
    $this->assertStub($alterstub, \HookStub::once());

    $this->assertEqual($expected_keys, $result);
  }

  /**
   * Test authenticated key customization.
   */
  public function testCustomAuthenticatedKeys() {
    global $base_root;

    $rid1 = (int) $this->drupalCreateRole(array());
    $rid2 = (int) $this->drupalCreateRole(array());
    variable_set('authcache_roles', array(
      DRUPAL_ANONYMOUS_RID => DRUPAL_ANONYMOUS_RID,
      DRUPAL_AUTHENTICATED_RID => DRUPAL_AUTHENTICATED_RID,
      $rid1 => $rid1,
      $rid2 => $rid2,
    ));

    // Data for hook_authcache_enum_key_property_info().
    $custom_property_info = array(
      'js' => array(
        'name' => t('Browser supports JavaScript'),
        'choices' => array(TRUE, FALSE),
      ),
    );

    // Data for hook_authcache_enum_key_property_info_alter().
    // Remove roles and customize choices on base_root property.
    $base_roots = array(
      'http://www.' . $this->randomName(6) . '.com',
      'http://www.' . $this->randomName(7) . '.com',
    );
    $property_info_alter = array(
      'delete' => array(
        'roles' => TRUE,
      ),
      'insert' => array(
        'base_root' => array(
          'name' => t('The root URL of the host, excluding the path'),
          'choices' => $base_roots,
        ),
      ),
    );

    $expect_properties = array(
      array(
        'base_root' => $base_roots[0],
        'js' => FALSE,
      ),
      array(
        'base_root' => $base_roots[0],
        'js' => TRUE,
      ),
      array(
        'base_root' => $base_roots[1],
        'js' => FALSE,
      ),
      array(
        'base_root' => $base_roots[1],
        'js' => TRUE,
      ),
    );

    $user_keys = array_map('authcache_user_key', $expect_properties);
    $expect_alter = array_combine($user_keys, $expect_properties);
    ksort($expect_alter);

    $expect_keys = $user_keys;
    $expect_keys[] = $base_root;

    $infostub = $this->stubmod->hook('authcache_enum_key_property_info', $custom_property_info);
    $infoalterstub = $this->stubmod->hook('authcache_enum_key_property_info_alter', $property_info_alter);
    $keyalterstub = $this->stubmod->hook('authcache_enum_key_properties_alter');

    $result = authcache_enum_keys();

    $this->assertStub($infostub, \HookStub::once());

    $default_property_info = authcache_enum_authcache_enum_key_property_info();
    $this->assertStub($infoalterstub, \HookStub::once());
    $this->assertStub($infoalterstub, \HookStub::args(array(
      $default_property_info + $custom_property_info,
      NULL,
      NULL,
      NULL,
    ), 0, FALSE));

    $this->assertStub($keyalterstub, \HookStub::once());
    $this->assertStub($keyalterstub, \HookStub::args(array(
      $expect_alter,
      NULL,
      NULL,
      NULL,
    ), 0, FALSE));

    sort($result);
    sort($expect_keys);
    $this->assertEqual($expect_keys, $result);
  }

  /**
   * Test deprecated authenticated key customization.
   */
  public function testDeprecatedCustomAuthenticatedKeys() {
    global $base_root;

    $rid1 = (int) $this->drupalCreateRole(array());
    $rid2 = (int) $this->drupalCreateRole(array());
    variable_set('authcache_roles', array(
      DRUPAL_ANONYMOUS_RID => DRUPAL_ANONYMOUS_RID,
      DRUPAL_AUTHENTICATED_RID => DRUPAL_AUTHENTICATED_RID,
      $rid1 => $rid1,
      $rid2 => $rid2,
    ));

    $property_info = array(
      'js' => array(
        'name' => t('Browser supports JavaScript'),
        'choices' => array(TRUE, FALSE),
      ),
    );

    $expect_properties = array(
      array(
        'base_root' => $base_root,
        'roles' => array(DRUPAL_AUTHENTICATED_RID),
        'js' => FALSE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array(DRUPAL_AUTHENTICATED_RID),
        'js' => TRUE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array($rid1),
        'js' => FALSE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array($rid1),
        'js' => TRUE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array($rid2),
        'js' => FALSE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array($rid2),
        'js' => TRUE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array($rid1, $rid2),
        'js' => FALSE,
      ),
      array(
        'base_root' => $base_root,
        'roles' => array($rid1, $rid2),
        'js' => TRUE,
      ),
    );

    $user_keys = array_map('authcache_user_key', $expect_properties);
    $expect_alter = array_combine($user_keys, $expect_properties);
    ksort($expect_alter);

    $expect_keys = $user_keys;
    $expect_keys[] = $base_root;

    $keystub = $this->stubmod->hook('authcache_enum_key_properties', $property_info);
    $alterstub = $this->stubmod->hook('authcache_enum_key_properties_alter');
    $result = authcache_enum_keys();
    $this->assertStub($keystub, \HookStub::once());
    $this->assertStub($alterstub, \HookStub::once());
    $this->assertStub($alterstub, \HookStub::args(array(
      $expect_alter,
      NULL,
      NULL,
      NULL,
    ), 0, FALSE));

    sort($result);
    sort($expect_keys);
    $this->assertEqual($expect_keys, $result);
  }

}
