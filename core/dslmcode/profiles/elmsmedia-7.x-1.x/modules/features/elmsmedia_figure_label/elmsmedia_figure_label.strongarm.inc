<?php
/**
 * @file
 * elmsmedia_figure_label.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_figure_label_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_figurelabel';
  $strongarm->value = 1;
  $export['addanother_button_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_figurelabel';
  $strongarm->value = 1;
  $export['addanother_message_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_figurelabel';
  $strongarm->value = 1;
  $export['addanother_tab_edit_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_figurelabel';
  $strongarm->value = 1;
  $export['addanother_tab_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_figurelabel';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_figurelabel';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_figurelabel';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_figurelabel';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__figurelabel';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'teaser' => array(
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
        'custom_settings' => TRUE,
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
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '100',
        ),
        'hidden_nodes' => array(
          'weight' => '100',
        ),
        'book' => array(
          'weight' => '100',
        ),
        'options' => array(
          'weight' => '100',
        ),
        'author' => array(
          'weight' => '100',
        ),
        'revision_information' => array(
          'weight' => '100',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_figurelabel';
  $strongarm->value = array();
  $export['menu_options_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_figurelabel';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_figurelabel';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_figurelabel';
  $strongarm->value = '0';
  $export['node_preview_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_figurelabel';
  $strongarm->value = 0;
  $export['node_submitted_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_template_default_figurelabel';
  $strongarm->value = '';
  $export['wysiwyg_template_default_figurelabel'] = $strongarm;

  return $export;
}
