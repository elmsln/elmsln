<?php
/**
 * @file
 * cle_submission.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function cle_submission_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: student_work
  $profiles['student_work'] = array(
    'format' => 'student_work',
    'editor' => 'ckeditor',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 0,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'Source' => 1,
        ),
      ),
      'toolbar_align' => 'left',
      'path_loc' => 'none',
      'default_toolbar_grouping' => 0,
      'verify_html' => 1,
      'preformatted' => 0,
      'convert_fonts_to_spans' => 1,
      'remove_linebreaks' => 0,
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'css_setting' => 'theme',
      'css_path' => '',
      'advanced__active_tab' => 'edit-output',
      'simple_source_formatting' => 1,
      'resize_enabled' => 0,
      'toolbarLocation' => 'top',
      'forcePasteAsPlainText' => 1,
      'stylesSet' => '',
    ),
  );

  return $profiles;
}
