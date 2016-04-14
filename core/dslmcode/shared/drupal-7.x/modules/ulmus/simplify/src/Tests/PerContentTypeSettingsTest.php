<?php

/**
 * @file
 * Test case for testing the per content-type simplify configurations.
 *
 * Sponsored by: www.drupal-addict.com
 */

namespace Drupal\simplify\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\user\Entity\Role;

/**
 * Test simplify per content-type settings.
 *
 * @group Simplify
 *
 * @ingroup simplify
 */
class PerContentTypeSettingsTest extends WebTestBase {

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = array('path', 'menu_ui', 'comment', 'node', 'user', 'simplify');

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Simplify per content-type settings test.',
      'description' => 'Test the Simplify per content-type settings.',
      'group' => 'Simplify',
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    // Create an admin user.
    $admin_user = $this->drupalCreateUser(array(), NULL, TRUE);
    $this->drupalLogin($admin_user);

    // Create a content type.
    $this->drupalCreateContentType(['type' => 'testing_type', 'name' => 'Testing type']);

    // Create another content type.
    $this->drupalCreateContentType(['type' => 'another_type', 'name' => 'Another type']);
  }

  /**
   * Perform full "per content-type" simplify scenario testing.
   */
  public function testSettingSaving() {

    /* -------------------------------------------------------.
     * 0/ Check that everything is here in the content type.
     */
    $this->drupalGet('node/add/testing_type');

    $this->assertRaw('About text formats', 'Text format option is defined.');
    $this->assertRaw('Menu settings', 'Menu settings option is defined.');
    $this->assertRaw('URL path settings', 'URL path settings option is defined.');
    $this->assertRaw('Authoring information', 'Authoring information option is defined.');
    $this->assertRaw('Promotion options', 'Promotion options option is defined.');

    /* -------------------------------------------------------.
     * 1/ Check if everything is there but unchecked.
     */

    // Globally activate some options.
    $this->drupalGet('admin/config/user-interface/simplify');
    $options = array(
      'simplify_admin' => TRUE,
      'simplify_nodes_global[author]' => 'author',
      'simplify_nodes_global[comment]' => 'comment',
      'simplify_nodes_global[options]' => 'options',
    );
    $this->drupalPostForm(NULL, $options, t('Save configuration'));
    // Admin users setting.
    $this->assertFieldChecked('edit-simplify-admin', "Admin users can't see hidden fields too.");

    /* -------------------------------------------------------.
     * 2/ Check the effect on content-type settingss.
     */

    // Open admin UI.
    $this->drupalGet('/admin/structure/types/manage/testing_type');

    // Nodes.
    $this->assertFieldChecked('edit-simplify-nodes-author', 'Node authoring information option is checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-format', 'Node text fomat selection option is not checked.');
    $this->assertFieldChecked('edit-simplify-nodes-options', 'Node promoting options option is checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-revision-information', 'Node revision information option is not checked.');
    $this->assertFieldChecked('edit-simplify-nodes-comment', 'Node comment settings option is checked.');

    /* -------------------------------------------------------.
     * 2-bis/ Check if everything is properly disabled if needed.
     */

    // Nodes.
    $author_info = $this->xpath('//input[@name="simplify_nodes[author]" and @disabled="disabled"]');
    $this->assertTrue(count($author_info) === 1, 'Node authoring information option is disabled.');

    $text_format = $this->xpath('//input[@name="simplify_nodes[format]" and @disabled="disabled"]');
    $this->assertTrue(count($text_format) === 0, 'Node text format option is not disabled.');

    $publishing_option = $this->xpath('//input[@name="simplify_nodes[options]" and @disabled="disabled"]');
    $this->assertTrue(count($publishing_option) === 1, 'Node promoting options option is disabled.');

    $revision_option = $this->xpath('//input[@name="simplify_nodes[revision-information]" and @disabled="disabled"]');
    $this->assertTrue(count($revision_option) === 0, 'Node revision information option is not disabled.');

    $comment_option = $this->xpath('//input[@name="simplify_nodes[comment]" and @disabled="disabled"]');
    $this->assertTrue(count($comment_option) === 1, 'Node comment settings option is disabled.');

    /* -------------------------------------------------------.
     * 3/ Save some "per content-type" options.
     */

    // Nodes.
    $options = array(
      'simplify_nodes[format]' => 'format',
    );
    $this->drupalPostForm(NULL, $options, t('Save content type'));

    /* -------------------------------------------------------.
     * 3-bis/ Check if options are saved.
     */
    $this->drupalGet('admin/structure/types/manage/testing_type');
    $this->assertFieldChecked('edit-simplify-nodes-format', 'Node text fomat selection option is checked.');

    /* -------------------------------------------------------.
     * 4/ Check The effect of all this on node form.
     */
    $this->drupalGet('node/add/testing_type');

    $this->assertNoRaw('About text formats', 'Text format option is not defined.');
    $this->assertRaw('Menu settings', 'Menu settings option is defined.');
    $this->assertRaw('URL path settings', 'URL path settings option is defined.');
    $this->assertNoRaw('Authoring information', 'Authoring information option is not defined.');
    $this->assertNoRaw('Promotion options', 'Promotion options option is not defined.');
  }

}
