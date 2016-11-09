<?php
/**
 * @file
 * elmsmedia_static_content.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_static_content_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_static_content';
  $strongarm->value = 1;
  $export['addanother_button_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_static_content';
  $strongarm->value = 0;
  $export['addanother_message_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_static_content';
  $strongarm->value = 0;
  $export['addanother_tab_edit_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_static_content';
  $strongarm->value = 0;
  $export['addanother_tab_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_static_content';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bulk_photo_nodes_static_content';
  $strongarm->value = array(
    0 => 'image_field',
    1 => 'override_add_form',
  );
  $export['bulk_photo_nodes_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_static_content';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_static_content';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_static_content';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__static_content';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => TRUE,
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
      'image__card__left__lightboxed' => array(
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
      'image__card__right__lightboxed' => array(
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
      'image__parallax' => array(
        'custom_settings' => FALSE,
      ),
      'image__parallax__lightboxed' => array(
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
      'image_gallery__carousel' => array(
        'custom_settings' => FALSE,
      ),
      'image_gallery__carousel__slider' => array(
        'custom_settings' => FALSE,
      ),
      'image_gallery__comparison' => array(
        'custom_settings' => FALSE,
      ),
      'image_gallery__basic_gallery' => array(
        'custom_settings' => FALSE,
      ),
      'image_gallery__basic_gallery__circle' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '9',
        ),
        'hidden_nodes' => array(
          'weight' => '7',
        ),
        'book' => array(
          'weight' => '8',
        ),
        'options' => array(
          'weight' => '5',
        ),
        'author' => array(
          'weight' => '4',
        ),
        'revision_information' => array(
          'weight' => '6',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_static_content';
  $strongarm->value = array();
  $export['menu_options_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_static_content';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_static_content';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_static_content';
  $strongarm->value = '0';
  $export['node_preview_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_static_content';
  $strongarm->value = 0;
  $export['node_submitted_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_static_content';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__static_content';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 1,
    'image' => 0,
    'image__left' => 0,
    'image__left__lightboxed' => 0,
    'image__left__circle' => 0,
    'image__left__circle__lightboxed' => 0,
    'image__right' => 0,
    'image__right__lightboxed' => 0,
    'image__right__circle' => 0,
    'image__right__circle__lightboxed' => 0,
    'image__circle' => 0,
    'image__circle__lightboxed' => 0,
    'image__lightboxed' => 0,
    'image__card' => 0,
    'image__card__left__lightboxed' => 0,
    'image__card__left__lightboxed__small' => 0,
    'image__card__left__lightboxed__medium' => 0,
    'image__card__left__lightboxed__large' => 0,
    'image__card__right__lightboxed' => 0,
    'image__card__right__lightboxed__small' => 0,
    'image__card__right__lightboxed__medium' => 0,
    'image__card__right__lightboxed__large' => 0,
    'image__parallax' => 0,
    'image__parallax__lightboxed' => 0,
    'image__boxed' => 0,
    'image__boxed__left' => 0,
    'image__boxed__left__lightboxed' => 0,
    'image__boxed__right' => 0,
    'image__boxed__right__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediavideo__poster' => 0,
    'mediasvg' => 0,
    'mediasvg__stretch' => 0,
    'mediasvg__stretch__medium' => 0,
    'mediasvg__stretch__small' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'figurelabel' => 0,
    'h5p' => 0,
    'h5p__card' => 0,
    'image_gallery__carousel' => 0,
    'image_gallery__carousel__slider' => 0,
    'image_gallery__comparison' => 0,
    'image_gallery__basic_gallery' => 0,
    'image_gallery__basic_gallery__circle' => 0,
    'accessible_fallback' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__static_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_template_default_static_content';
  $strongarm->value = '';
  $export['wysiwyg_template_default_static_content'] = $strongarm;

  return $export;
}
