<?php

/**
 * @file
 * Test case for testing the per vocabulary simplify configurations.
 *
 * Sponsored by: www.drupal-addict.com
 */

namespace Drupal\simplify\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\Component\Utility\Unicode;

/**
 * Test simplify per vocabulary settings.
 *
 * @group Simplify
 *
 * @ingroup simplify
 */
class PerVocabularySettingsTest extends WebTestBase {

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = array('path', 'taxonomy', 'simplify');

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Simplify per taxonomy settings test.',
      'description' => 'Test the Simplify per taxonomy settings.',
      'group' => 'Simplify',
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    $admin_user = $this->drupalCreateUser(array('administer url aliases', 'administer taxonomy', 'administer simplify'));
    $this->drupalLogin($admin_user);

    // Create a vocabulary.
    $vocabulary = entity_create('taxonomy_vocabulary', array(
      'name' => $this->randomMachineName(),
      'description' => $this->randomMachineName(),
      'vid' => 'testing_vocabulary',
    ));
    $vocabulary->save();
  }

  /**
   * Check that Simplify module global configuration files saves settings.
   */
  public function testSettingSaving() {

    /* -------------------------------------------------------.
     * 0/ Check vocabulary edit term standard page.
     */

    $this->drupalGet("/admin/structure/taxonomy/manage/testing_vocabulary/add");

    $this->assertRaw('About text formats', 'Term edit text format option is defined.');
    $this->assertRaw('Relations', 'Term Relations option is defined.');
    $this->assertRaw('URL alias', 'Term URL alias option is defined.');

    /* -------------------------------------------------------.
     * 1/ Per vocabulary settings.
     */

    // Globally activate some options.
    $this->drupalGet('/admin/config/user-interface/simplify');
    $options = array(
      'simplify_admin' => TRUE,
      'simplify_taxonomies_global[format]' => 'format',
    );
    $this->drupalPostForm(NULL, $options, t('Save configuration'));

    // Open vocabulary admin UI.
    $this->drupalGet('/admin/structure/taxonomy/manage/testing_vocabulary');

    // Check if everything is there and global options are considered.
    $this->assertFieldChecked('edit-simplify-taxonomies-format', 'Vocabulary text fomat selection option is checked.');
    $this->assertNoFieldChecked('edit-simplify-taxonomies-relations', 'Vocabulary relations option is not checked.');
    $this->assertNoFieldChecked('edit-simplify-taxonomies-path', 'Vocabulary Path settings option is not checked.');

    // Check if everything is properly disabled if needed.
    $text_format = $this->xpath('//input[@name="simplify_taxonomies[format]" and @disabled="disabled"]');
    $this->assertTrue(count($text_format) === 1, 'Vocabulary text format option is disabled.');

    $text_format = $this->xpath('//input[@name="simplify_taxonomies[relations]" and @disabled="disabled"]');
    $this->assertTrue(count($text_format) === 0, 'Vocabulary relations option is not disabled.');

    $text_format = $this->xpath('//input[@name="simplify_taxonomies[path]" and @disabled="disabled"]');
    $this->assertTrue(count($text_format) === 0, 'Vocabulary URL alias option is not disabled.');

    // Save some custom options.
    $options = array(
      'simplify_taxonomies[relations]' => 'relations',
      'simplify_taxonomies[path]' => 'path',
    );
    $this->drupalPostForm(NULL, $options, t('Save'));

    // Check if options are saved.
    $this->drupalGet('/admin/structure/taxonomy/manage/testing_vocabulary');
    $this->assertFieldChecked('edit-simplify-taxonomies-relations', 'Vocabulary relations option is checked.');
    $this->assertFieldChecked('edit-simplify-taxonomies-path', 'Vocabulary URL alias option is checked.');

    /* -------------------------------------------------------.
     * 2/ Check settings effect on "term edit" page.
     */
    $this->drupalGet("/admin/structure/taxonomy/manage/testing_vocabulary/add");

    $this->assertNoRaw('About text formats', 'Term edit text format option is not defined.');
    $this->assertNoRaw('Relations', 'Term Relations option is not defined.');
    $this->assertNoRaw('URL alias', 'Term URL alias option is not defined.');
  }

}
