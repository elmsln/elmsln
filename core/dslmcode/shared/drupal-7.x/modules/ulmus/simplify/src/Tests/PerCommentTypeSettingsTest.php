<?php

/**
 * @file
 * Test case for testing the per comment-type simplify configurations.
 *
 * Sponsored by: www.drupal-addict.com
 */

namespace Drupal\simplify\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\comment\Tests\CommentTestTrait;

/**
 * Test simplify per comment-type settings.
 *
 * @group Simplify
 *
 * @ingroup simplify
 */
class PerCommentTypeSettingsTest extends WebTestBase {
  use CommentTestTrait;

  /**
   * An administrative user with permission to configure comment settings.
   *
   * @var \Drupal\user\UserInterface
   */
  protected $adminUser;

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = array('node', 'comment', 'field_ui', 'simplify');

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => 'Simplify per comment-type settings test.',
      'description' => 'Test the Simplify per comment-type settings.',
      'group' => 'Simplify',
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    // Create two test users.
    $this->adminUser = $this->drupalCreateUser(array(
      'administer content types',
      'administer comments',
      'administer comment types',
      'administer comment fields',
      'administer comment display',
      'administer simplify',
      'skip comment approval',
      'post comments',
      'access comments',
      'access content',
    ));
    $this->drupalLogin($this->adminUser);

    // Create a content type.
    $content_type = $this->drupalCreateContentType(['type' => 'content_type', 'name' => 'Testing content type']);

    // Create comment field on $content_type bundle.
    $this->addDefaultCommentField('node', 'content_type');
  }

  /**
   * Check that Simplify module global configuration files saves settings.
   */
  public function testSettingSaving() {

    /* -------------------------------------------------------.
     * 0/ Check the comment form by default.
     */

    // Create a test node authored by the user.
    $node = $this->drupalCreateNode(array('type' => 'content_type', 'promote' => 1, 'uid' => $this->adminUser->id()));

    // Check if options are there.
    $this->drupalGet("/node/" . $node->id());
    $this->assertRaw('About text formats', 'Comment text format option is defined.');

    /* -------------------------------------------------------.
     * 1/ Activate some global options and check "per comment-type" accordingly.
     */

    // Globally activate some options.
    $this->drupalGet('/admin/config/user-interface/simplify');
    $options = array(
      'simplify_admin' => TRUE,
      'simplify_comments_global[format]' => 'format',
    );
    $this->drupalPostForm(NULL, $options, t('Save configuration'));

    // Open admin UI.
    $this->drupalGet('/admin/structure/comment/manage/comment');

    // Check if global options are forwarded.
    $this->assertFieldChecked('edit-simplify-comments-format', 'Comment text fomat selection option is checked.');

    // Check if everything is properly disabled if needed.
    $text_format = $this->xpath('//input[@name="simplify_comments[format]" and @disabled="disabled"]');
    $this->assertTrue(count($text_format) === 1, 'Comment text format option is disabled.');

    /* -------------------------------------------------------.
     * 2/ Remove global options.
     */

    $this->drupalGet('/admin/config/user-interface/simplify');
    $options = array(
      'simplify_admin' => TRUE,
      'simplify_comments_global[format]' => FALSE,
    );
    $this->drupalPostForm(NULL, $options, t('Save configuration'));

    // Open admin UI.
    $this->drupalGet('/admin/structure/comment/manage/comment');

    // Check if global options are forwarded.
    $this->assertNoFieldChecked('edit-simplify-comments-format', 'Comment text fomat selection option is not checked.');

    /* -------------------------------------------------------.
     * 3/ Save some custom options.
     */

    // Nodes.
    $options = array(
      'simplify_comments[format]' => 'format',
    );
    $this->drupalPostForm(NULL, $options, t('Save'));

    /* -------------------------------------------------------.
     * 4/ Check if options are saved.
     */
    $this->drupalGet('/admin/structure/comment/manage/comment');
    $this->assertFieldChecked('edit-simplify-comments-format', 'Comment text fomat selection option is checked.');

    /*
     * 5/ Check if comment form is now simplified.
     */
    $this->drupalGet("/node/" . $node->id());
    $this->assertNoRaw('About text formats', 'Comment text format option is not defined.');


  }

}
