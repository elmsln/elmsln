<?php
/**
 * @file
 * elmsmedia_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_audio';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_elmsmedia_image';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_video';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_bundle_accessibility_test';
  $strongarm->value = array(
    'accessibility_test' => 'accessibility_test',
  );
  $export['entity_iframe_bundle_accessibility_test'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_bundle_node';
  $strongarm->value = array(
    'audio' => 'audio',
    'document' => 'document',
    'external_video' => 'external_video',
    'elmsmedia_image' => 'elmsmedia_image',
    'h5p_content' => 'h5p_content',
    'video' => 'video',
    'cis_course' => 0,
    'section' => 0,
  );
  $export['entity_iframe_bundle_node'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_bundle_og_membership';
  $strongarm->value = array(
    'og_membership_type_default' => 'og_membership_type_default',
  );
  $export['entity_iframe_bundle_og_membership'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_bundle_og_membership_type';
  $strongarm->value = array(
    'og_membership_type' => 'og_membership_type',
  );
  $export['entity_iframe_bundle_og_membership_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_bundle_user';
  $strongarm->value = array(
    'user' => 'user',
  );
  $export['entity_iframe_bundle_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_height';
  $strongarm->value = '400';
  $export['entity_iframe_height'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_types';
  $strongarm->value = array(
    'node' => 'node',
    'accessibility_test' => 0,
    'og_membership_type' => 0,
    'og_membership' => 0,
    'taxonomy_term' => 0,
    'user' => 0,
  );
  $export['entity_iframe_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_width';
  $strongarm->value = '100%';
  $export['entity_iframe_width'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__audio';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => TRUE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__document';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__elmsmedia_image';
  $strongarm->value = array(
    'view_modes' => array(
      'iframe' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'image' => array(
        'custom_settings' => TRUE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'image__left' => array(
        'custom_settings' => FALSE,
      ),
      'image__right' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__left__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__right__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__poster' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail__right' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg' => array(
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
      'mediasvg__stretch' => array(
        'custom_settings' => FALSE,
      ),
      'figurelabel' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__external_video';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => TRUE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo' => array(
        'custom_settings' => TRUE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'image' => array(
        'custom_settings' => FALSE,
      ),
      'image__left' => array(
        'custom_settings' => FALSE,
      ),
      'image__right' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__left__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__right__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__poster' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail__right' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg' => array(
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
      'mediasvg__stretch' => array(
        'custom_settings' => FALSE,
      ),
      'figurelabel' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '3',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__figurelabel';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__svg';
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
      'image__right' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__left__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__right__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'image__boxed__lightboxed' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__poster' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail' => array(
        'custom_settings' => FALSE,
      ),
      'mediavideo__thumbnail__right' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg' => array(
        'custom_settings' => TRUE,
      ),
      'mediasvg__left' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__right' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__stretch' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__left__medium' => array(
        'custom_settings' => FALSE,
      ),
      'mediasvg__left__small' => array(
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
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__video';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => TRUE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '1',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fitvids_customselectors';
  $strongarm->value = '';
  $export['fitvids_customselectors'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fitvids_selectors';
  $strongarm->value = '.nowhere';
  $export['fitvids_selectors'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fitvids_simplifymarkup';
  $strongarm->value = 1;
  $export['fitvids_simplifymarkup'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_audio';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_document';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_elmsmedia_image';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_external_video';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_figurelabel';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_svg';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_video';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_audio';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_document';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_elmsmedia_image';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_external_video';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_figurelabel';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_svg';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_video';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_audio';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_document';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_elmsmedia_image';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_external_video';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_figurelabel';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_svg';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_video';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_audio';
  $strongarm->value = '0';
  $export['node_preview_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_document';
  $strongarm->value = '0';
  $export['node_preview_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_elmsmedia_image';
  $strongarm->value = '0';
  $export['node_preview_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_external_video';
  $strongarm->value = '0';
  $export['node_preview_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_figurelabel';
  $strongarm->value = '1';
  $export['node_preview_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_svg';
  $strongarm->value = '1';
  $export['node_preview_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_video';
  $strongarm->value = '1';
  $export['node_preview_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_audio';
  $strongarm->value = 0;
  $export['node_submitted_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_document';
  $strongarm->value = 0;
  $export['node_submitted_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_elmsmedia_image';
  $strongarm->value = 0;
  $export['node_submitted_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_external_video';
  $strongarm->value = 0;
  $export['node_submitted_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_figurelabel';
  $strongarm->value = 1;
  $export['node_submitted_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_svg';
  $strongarm->value = 1;
  $export['node_submitted_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_video';
  $strongarm->value = 0;
  $export['node_submitted_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_enable_by_default';
  $strongarm->value = 0;
  $export['view_mode_enable_by_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__audio__figurelabel_audio';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__audio__figurelabel_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__document__figurelabel_document';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__document__figurelabel_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 1,
    'image__left' => 1,
    'image__right' => 1,
    'image__boxed' => 1,
    'image__lightboxed' => 1,
    'image__left__lightboxed' => 1,
    'image__right__lightboxed' => 1,
    'image__boxed__lightboxed' => 1,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__diff_standard_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__diff_standard_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__figurelabel_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__figurelabel_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__full_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__full_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__iframe_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__iframe_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__boxed__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__left_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__left__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__left__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__right_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__image__right__lightboxed_elmsmedia_image';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__elmsmedia_image__image__right__lightboxed_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__left_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__left_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__left__medium_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__left__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__left__small_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__left__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__right__medium_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__right__medium_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__right__small_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__right__small_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediasvg__stretch_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediasvg__stretch_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__poster_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__poster_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail__right_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__mediavideo__thumbnail__right_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__revision_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__revision_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__rss_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__rss_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__teaser_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__teaser_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__elmsmedia_image__token_elmsmedia_image';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__elmsmedia_image__token_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__figurelabel_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__figurelabel_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__left_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__left_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__left__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__left__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__left__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__left__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__right_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__right__medium_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__right__medium_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__right__small_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__right__small_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediasvg__stretch_external_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__external_video__mediasvg__stretch_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__poster_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__poster_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__thumbnail_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__thumbnail_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__external_video__mediavideo__thumbnail__right_external_video';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__external_video__mediavideo__thumbnail__right_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 0,
    'mediasvg__left' => 0,
    'mediasvg__left__medium' => 0,
    'mediasvg__left__small' => 0,
    'mediasvg__right' => 0,
    'mediasvg__right__medium' => 0,
    'mediasvg__right__small' => 0,
    'mediasvg__stretch' => 0,
    'figurelabel' => 1,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__diff_standard_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__diff_standard_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__figurelabel_figurelabel';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__figurelabel__figurelabel_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__full_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__full_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__iframe_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__iframe_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__boxed__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__boxed__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__left__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__left__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__image__right__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__image__right__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__left__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__left__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__left__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__left__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__right__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__right__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__right__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__right__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediasvg__stretch_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediasvg__stretch_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__poster_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__poster_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__thumbnail_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__thumbnail_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__mediavideo__thumbnail__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__mediavideo__thumbnail__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__revision_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__revision_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__rss_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__rss_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__teaser_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__teaser_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figurelabel__token_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__figurelabel__token_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__figure_label';
  $strongarm->value = array(
    'full' => 1,
    'teaser' => 1,
    'rss' => 1,
    'diff_standard' => 1,
    'iframe' => 1,
    'image' => 1,
    'image__left' => 1,
    'image__right' => 1,
    'image__boxed' => 1,
    'image__lightboxed' => 1,
    'image__left__lightboxed' => 1,
    'image__right__lightboxed' => 1,
    'image__boxed__lightboxed' => 1,
    'mediavideo' => 1,
    'mediavideo__poster' => 1,
    'mediavideo__thumbnail' => 1,
    'mediavideo__thumbnail__right' => 1,
    'mediasvg' => 1,
    'mediasvg__left' => 1,
    'mediasvg__left__medium' => 1,
    'mediasvg__left__small' => 1,
    'mediasvg__right' => 1,
    'mediasvg__right__medium' => 1,
    'mediasvg__right__small' => 1,
    'mediasvg__stretch' => 1,
    'token' => 1,
    'revision' => 1,
  );
  $export['view_mode_tab_settings__figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__h5p_content__figurelabel_h5p_content';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__h5p_content__figurelabel_h5p_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'image' => 0,
    'image__left' => 0,
    'image__right' => 0,
    'image__boxed' => 0,
    'image__lightboxed' => 0,
    'image__left__lightboxed' => 0,
    'image__right__lightboxed' => 0,
    'image__boxed__lightboxed' => 0,
    'mediavideo' => 0,
    'mediavideo__poster' => 0,
    'mediavideo__thumbnail' => 0,
    'mediavideo__thumbnail__right' => 0,
    'mediasvg' => 1,
    'mediasvg__left' => 1,
    'mediasvg__left__medium' => 1,
    'mediasvg__left__small' => 1,
    'mediasvg__right' => 1,
    'mediasvg__right__medium' => 1,
    'mediasvg__right__small' => 1,
    'mediasvg__stretch' => 1,
    'figurelabel' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__figurelabel_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__figurelabel_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__left_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__left_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__left__medium_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__left__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__left__small_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__left__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__right_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__right__medium_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__right__medium_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__right__small_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__right__small_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediasvg__stretch_svg';
  $strongarm->value = 1;
  $export['view_mode_tab_settings__svg__mediasvg__stretch_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo__poster_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo__poster_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo__thumbnail_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo__thumbnail_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__svg__mediavideo__thumbnail__right_svg';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__svg__mediavideo__thumbnail__right_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__video__figurelabel_video';
  $strongarm->value = 0;
  $export['view_mode_tab_settings__video__figurelabel_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____diff_standard_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____diff_standard_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____diff_standard_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____diff_standard_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____full_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____full_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____full_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____full_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____iframe_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____iframe_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____iframe_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____iframe_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__boxed__lightboxed_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__boxed__lightboxed_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__left_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__left_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__left__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__left__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__left__lightboxed_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__left__lightboxed_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__lightboxed_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__lightboxed_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__right_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__right_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__right__lightboxed_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__right__lightboxed_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____image__right__lightboxed_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____image__right__lightboxed_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left__medium_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left__medium_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__left__small_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__left__small_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right__medium_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right__medium_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right__medium_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right__medium_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right__small_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right__small_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__right__small_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__right__small_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__stretch_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__stretch_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediasvg__stretch_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediasvg__stretch_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__poster_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__poster_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__poster_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__poster_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__thumbnail_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__thumbnail_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__thumbnail_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__thumbnail_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__thumbnail__right_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__thumbnail__right_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____mediavideo__thumbnail__right_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____mediavideo__thumbnail__right_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____revision_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____revision_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____revision_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____revision_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____rss_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____rss_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____rss_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____rss_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____teaser_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____teaser_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____teaser_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____teaser_figure_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____token_figurelabel';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____token_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings____token_figure_label';
  $strongarm->value = 0;
  $export['view_mode_tab_settings____token_figure_label'] = $strongarm;

  return $export;
}
