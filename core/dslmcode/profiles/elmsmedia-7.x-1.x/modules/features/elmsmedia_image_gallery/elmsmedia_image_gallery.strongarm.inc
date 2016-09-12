<?php
/**
 * @file
 * elmsmedia_image_gallery.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_image_gallery_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_image_gallery';
  $strongarm->value = 1;
  $export['addanother_button_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_image_gallery';
  $strongarm->value = 0;
  $export['addanother_message_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_image_gallery';
  $strongarm->value = 0;
  $export['addanother_tab_edit_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_image_gallery';
  $strongarm->value = 0;
  $export['addanother_tab_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_image_gallery';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_image_gallery';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_image_gallery';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_image_gallery';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__image_gallery';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => FALSE,
      ),
      'image' => array(
        'custom_settings' => FALSE,
      ),
      'image__left' => array(
        'custom_settings' => FALSE,
      ),
      'image__left__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__left__circle' => array(
        'custom_settings' => FALSE,
      ),
      'image__left__circle__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__right' => array(
        'custom_settings' => FALSE,
      ),
      'image__right__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__right__circle' => array(
        'custom_settings' => FALSE,
      ),
      'image__right__circle__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__circle' => array(
        'custom_settings' => FALSE,
      ),
      'image__circle__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__card' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__left' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__left__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__right' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__right__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__left' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__left__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__right' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__right__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__parallax' => array(
        'custom_settings' => FALSE,
      ),
      'image__parallax__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail__right' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__poster' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__stretch' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__stretch__medium' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__stretch__small' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__left' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__left__medium' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__left__small' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__right' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__right__medium' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__right__small' => array(
        'custom_settings' => FALSE,
      ),
      'figurelabel' => array(
        'custom_settings' => FALSE,
      ),
      'h5p' => array(
        'custom_settings' => FALSE,
      ),
      'h5p__card' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__left__lightboxed__small' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__left__lightboxed__medium' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__left__lightboxed__large' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__right__lightboxed__small' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__right__lightboxed__medium' => array(
        'custom_settings' => FALSE,
      ),
      'image__card__right__lightboxed__large' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '8',
        ),
        'hidden_nodes' => array(
          'weight' => '6',
        ),
        'book' => array(
          'weight' => '7',
        ),
        'options' => array(
          'weight' => '4',
        ),
        'author' => array(
          'weight' => '3',
        ),
        'revision_information' => array(
          'weight' => '5',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_image_gallery';
  $strongarm->value = array();
  $export['menu_options_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_image_gallery';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_image_gallery';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_image_gallery';
  $strongarm->value = '0';
  $export['node_preview_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_image_gallery';
  $strongarm->value = 0;
  $export['node_submitted_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_image_gallery';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_image_gallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_template_default_image_gallery';
  $strongarm->value = '';
  $export['wysiwyg_template_default_image_gallery'] = $strongarm;

  return $export;
}
