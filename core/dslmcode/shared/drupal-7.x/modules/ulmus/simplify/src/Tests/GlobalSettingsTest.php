<?php

/**
 * @file
 * Test case for testing the global simplify configuration page.
 *
 * Sponsored by: www.drupal-addict.com
 */

namespace Drupal\simplify\Tests;

use Drupal\simpletest\WebTestBase;

/**
 * Test Simplify module global settings.
 *
 * @group Simplify
 *
 * @ingroup simplify
 */
class GlobalSettingsTest extends WebTestBase {

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = array('simplify');

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Simplify global settings test.',
      'description' => 'Test the Simplify module global settings page.',
      'group' => 'Simplify',
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();
    $admin_user = $this->drupalCreateUser(array('administer simplify'));
    $this->drupalLogin($admin_user);
  }

  /**
   * Check that Simplify module global configuration files saves settings.
   */
  public function testSettingSaving() {

    // Open admin UI.
    $this->drupalGet('/admin/config/user-interface/simplify');

    /* -------------------------------------------------------.
     * 1/ Check only basic options are there but unchecked.
     */

    // Admin user option.
    $this->assertField('edit-simplify-admin', 'Admin user option is here.');
    $this->assertNoFieldChecked('edit-simplify-admin', 'Admin user option is unchecked.');
    // Node globals.
    $this->assertNoRaw('Nodes', 'Nodes options are not available.');
    $this->assertNoField('edit-simplify-nodes-global-author', 'Author option is not available.');
    // User globals.
    $this->assertRaw('Users', 'Users options are not available.');
    $this->assertNoFieldChecked('edit-simplify-users-global-format', 'Text selection option is not available.');
    // Taxonomy is not here.
    $this->assertNoRaw('Taxonomy', 'Taxonomy options are not available.');
    $this->assertNoField('edit-simplify-taxonomy-global-format', 'Text selection from taxonomy option is not available.');
    // Blocks is not here.
    $this->assertNoRaw('Block', 'Blocks options are now available.');
    $this->assertNoField('edit-simplify-blocks-global-format', 'Text format option is not available.');

    /* -------------------------------------------------------.
     * 2/ Check optionnal options are added if modules becomes available.
     */

    $this->container->get('module_installer')->install(array('node', 'book', 'taxonomy', 'block', 'comment', 'menu_ui', 'path'), TRUE);
    $this->drupalGet('/admin/config/user-interface/simplify');
    // Node globals.
    $this->assertRaw('Nodes', 'Nodes options are now available.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-author', 'Author option is unchecked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-format', 'Format option is unchecked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-options', 'Publishing option is unchecked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-revision-information', 'Revision option is unchecked.');
    // User globals.
    $this->assertRaw('Users', 'Users options are now available.');
    $this->assertNoFieldChecked('edit-simplify-users-global-format', 'Text selection option is unchecked.');
    $this->assertNoFieldChecked('edit-simplify-users-global-status', 'Status option is unchecked.');
    // Taxonomy is not here.
    $this->assertRaw('Taxonomy', 'Taxonomy options are now available.');
    $this->assertNoFieldChecked('edit-simplify-taxonomies-global-format', 'Taxonomy selection option is unchecked.');
    $this->assertNoFieldChecked('edit-simplify-taxonomies-global-relations', 'Taxonomy relation option is unchecked.');
    $this->assertNoFieldChecked('edit-simplify-taxonomies-global-path', 'Taxonomy url alias option is unchecked.');
    // Blocks is not here.
    $this->assertRaw('Block', 'Blocks options are now available.');
    $this->assertNoFieldChecked('edit-simplify-blocks-global-format', 'Text format option is unchecked.');

    /*  -------------------------------------------------------.
     * 3/ Check and validate some options.
     */

    $options = array(
      'simplify_admin' => TRUE,
      'simplify_nodes_global[author]' => 'author',
      'simplify_nodes_global[comment]' => 'comment',
      'simplify_nodes_global[options]' => 'options',
      'simplify_taxonomies_global[format]' => 'format',
      'simplify_taxonomies_global[path]' => 'path',
    );
    $this->drupalPostForm(NULL, $options, t('Save configuration'));
    // User1.
    $this->assertFieldChecked('edit-simplify-admin', 'Admin user option is checked.');
    // Nodes.
    $this->assertFieldChecked('edit-simplify-nodes-global-author', 'Node authoring information option is checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-format', 'Node text fomat selection option is not checked.');
    $this->assertFieldChecked('edit-simplify-nodes-global-options', 'Node promoting options option is checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-revision-information', 'Node revision information option is not checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-book', 'Node book outline option is not checked.');
    $this->assertFieldChecked('edit-simplify-nodes-global-comment', 'Node comment settings option is checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-menu', 'Node menu settings option is not checked.');
    $this->assertNoFieldChecked('edit-simplify-nodes-global-path-settings', 'Node URL path settings option is not checked.');
    // Vocabularies.
    $this->assertFieldChecked('edit-simplify-taxonomies-global-format', 'Taxonomy text fomat selection option is checked.');
    $this->assertNoFieldChecked('edit-simplify-taxonomies-global-relations', 'Taxonomy relation option is not checked.');
    $this->assertFieldChecked('edit-simplify-taxonomies-global-path', 'Taxonomy url alias option is checked.');
  }

}
