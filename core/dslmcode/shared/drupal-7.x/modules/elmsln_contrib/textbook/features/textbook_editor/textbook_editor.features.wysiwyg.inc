<?php
/**
 * @file
 * textbook_editor.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function textbook_editor_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: textbook_editor
  $profiles['textbook_editor'] = array(
    'format' => 'textbook_editor',
    'editor' => 'ckeditor',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 0,
      'add_to_summaries' => 1,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'Image' => 1,
          'BGColor' => 1,
          'Source' => 1,
          'HorizontalRule' => 1,
          'ShowBlocks' => 1,
          'RemoveFormat' => 1,
          'Format' => 1,
          'Styles' => 1,
          'Table' => 1,
          'CreateDiv' => 1,
          'Iframe' => 1,
        ),
        'drupal_accessibility' => array(
          'drupal_accessibility' => 1,
        ),
        'imce' => array(
          'imce' => 1,
        ),
        'video_filter' => array(
          'video_filter' => 1,
        ),
        'templates' => array(
          'Templates' => 1,
        ),
        'drupal_path' => array(
          'Link' => 1,
        ),
      ),
      'toolbarLocation' => 'top',
      'resize_enabled' => 1,
      'default_toolbar_grouping' => 0,
      'simple_source_formatting' => 0,
      'acf_mode' => 0,
      'acf_allowed_content' => '',
      'css_setting' => 'theme',
      'css_path' => '',
      'stylesSet' => '',
      'block_formats' => 'p,h2,h3,h4,h5,h6,div,blockquote',
      'advanced__active_tab' => 'edit-css',
      'forcePasteAsPlainText' => 0,
    ),
  );

  return $profiles;
}
