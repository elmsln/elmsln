<?php
/**
 * @file
 * elmsmedia_list.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_list_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_elmsmedia_list';
  $strongarm->value = 0;
  $export['addanother_button_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_elmsmedia_list';
  $strongarm->value = 0;
  $export['addanother_message_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_elmsmedia_list';
  $strongarm->value = 0;
  $export['addanother_tab_edit_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_elmsmedia_list';
  $strongarm->value = 0;
  $export['addanother_tab_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_elmsmedia_list';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bulk_photo_nodes_elmsmedia_list';
  $strongarm->value = array(
    0 => 'image_field',
    1 => 'override_add_form',
  );
  $export['bulk_photo_nodes_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_elmsmedia_list';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_elmsmedia_list';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_elmsmedia_list';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__elmsmedia_list';
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
      'accessible_fallback' => array(
        'custom_settings' => FALSE,
      ),
      'document' => array(
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
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '5',
        ),
        'hidden_nodes' => array(
          'weight' => '6',
        ),
        'book' => array(
          'weight' => '7',
        ),
        'options' => array(
          'weight' => '8',
        ),
        'author' => array(
          'weight' => '9',
        ),
        'revision_information' => array(
          'weight' => '10',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_elmsmedia_list';
  $strongarm->value = array();
  $export['menu_options_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_elmsmedia_list';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_elmsmedia_list';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_elmsmedia_list';
  $strongarm->value = '0';
  $export['node_preview_elmsmedia_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_elmsmedia_list';
  $strongarm->value = 0;
  $export['node_submitted_elmsmedia_list'] = $strongarm;

  return $export;
}
