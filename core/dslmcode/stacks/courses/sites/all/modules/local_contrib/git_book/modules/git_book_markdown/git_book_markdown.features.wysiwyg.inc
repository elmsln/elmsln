<?php
/**
 * @file
 * git_book_markdown.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function git_book_markdown_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: git_book_markdown
  $profiles['git_book_markdown'] = array(
    'format' => 'git_book_markdown',
    'editor' => 'epiceditor',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 0,
      'add_to_summaries' => 0,
      'theme' => '',
      'language' => 'en',
      'css_setting' => 'theme',
      'css_path' => '',
      'advanced__active_tab' => 'edit-css',
    ),
  );

  return $profiles;
}
