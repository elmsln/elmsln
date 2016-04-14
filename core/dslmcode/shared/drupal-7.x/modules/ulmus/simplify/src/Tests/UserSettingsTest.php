<?php

/**
 * @file
 * Test case for testing the user simplify configurations.
 *
 * Sponsored by: www.drupal-addict.com
 */

namespace Drupal\simplify\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\user\Entity\Role;

/**
 * Test simplify user settings.
 *
 * @group Simplify
 *
 * @ingroup simplify
 */
class UserSettingsTest extends WebTestBase {

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = array('contact', 'user', 'simplify');

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Simplify user settings test.',
      'description' => 'Test the Simplify module user settings.',
      'group' => 'Simplify',
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();
  }

  /**
   * Perform full user simplify scenario testing.
   */
  public function testSettingSaving() {

    // Create an admin user.
    $admin_user = $this->drupalCreateUser(array(), NULL, TRUE);
    $this->drupalLogin($admin_user);

    $user_edit_page = '/user/' . $admin_user->id() . '/edit';

    /* -------------------------------------------------------.
     * 0/ Check that everything is here in the user edit page.
     */
    // A- On user edit page.
    $this->drupalGet($user_edit_page);
    $this->assertRaw('Status', 'Status option is defined.');
    $this->assertRaw('Contact settings', 'Contact settings option is defined.');
    $this->assertRaw('Locale settings', 'Locale settings option is defined.');
    // B- On user register page.
    $this->drupalLogout();
    $this->drupalGet('/user/register');
    $this->assertRaw('Contact settings', 'Contact settings option is defined.');
    $this->assertRaw('Locale settings', 'Locale settings option is defined.');

    /* -------------------------------------------------------.
     * 1/ Check if everything is there but unchecked.
     */
    $this->drupalLogin($admin_user);
    // Globally activate some options.
    $this->drupalGet('admin/config/user-interface/simplify');
    $options = array(
      'simplify_admin' => TRUE,
      'simplify_users_global[status]' => 'status',
      'simplify_users_global[timezone]' => 'timezone',
      'simplify_users_global[contact]' => 'contact',
    );
    $this->drupalPostForm(NULL, $options, t('Save configuration'));
    // Admin users setting.
    $this->assertFieldChecked('edit-simplify-admin', "Admin users can't see hidden fields too.");

    /* -------------------------------------------------------.
     * 2/ Check the effect on user settings.
     */

    // @TODO Remove this when hook_form_user_register_alter() is taken in
    // in consideration in testing profile with no cache refresh.
    drupal_flush_all_caches();

    // A- On user edit page.
    $this->drupalGet($user_edit_page);
    $this->assertNoRaw('Status', 'Status option is not defined');
    $this->assertNoRaw('Contact settings', 'Contact settings option is not defined.');
    $this->assertNoRaw('Locale settings', 'Locale settings option is not defined.');
    // B- On user register page.
    $this->drupalLogout();
    $this->drupalGet('/user/register');
    $this->assertNoRaw('Contact settings', 'Contact settings option is not defined.');
    $this->assertNoRaw('Locale settings', 'Locale settings option is not defined.');
  }

}
