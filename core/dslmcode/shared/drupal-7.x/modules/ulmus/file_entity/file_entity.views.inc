<?php

/**
 * @file
 * Views integration for the file_entity module.
 */

/**
 * Implements hook_views_data().
 */
function file_entity_views_data() {
  // File type.
  $data['file_managed']['type'] = array(
    'title' => t('Type'),
    'help' => t('The type of the file (for example, "audio", "image", "video", etc).'),
    'field' => array(
      'handler' => 'views_handler_field_file_type',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_file_type',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_file_type',
    ),
  );

  // File schema type.
  $data['file_managed']['schema_type'] = array(
    'title' => t('Schema type'),
    'help' => t('Filter files by schema, such as public or private.'),
    'filter' => array(
      'handler' => 'views_handler_filter_schema_type',
    ),
  );

  // Rendered file.
  $data['file_managed']['rendered'] = array(
    'title' => t('Rendered'),
    'help' => t('Display the file in a specific view mode.'),
    'field' => array(
      'handler' => 'views_handler_field_file_rendered',
      'click sortable' => TRUE,
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
  );

  // View link.
  $data['file_managed']['link'] = array(
    'title' => t('Link'),
    'help' => t('Provide a simple link to the file entity.'),
    'field' => array(
      'handler' => 'views_handler_field_file_link',
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
  );

  // Edit link.
  $data['file_managed']['edit'] = array(
    'title' => t('Edit link'),
    'help' => t('Provide a simple link to edit the file entity.'),
    'field' => array(
      'handler' => 'views_handler_field_file_link_edit',
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
  );

  // Delete link.
  $data['file_managed']['delete'] = array(
    'title' => t('Delete link'),
    'help' => t('Provide a simple link to delete the file entity.'),
    'field' => array(
      'handler' => 'views_handler_field_file_link_delete',
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
  );

  // Download link.
  $data['file_managed']['download'] = array(
    'title' => t('Download link'),
    'help' => t('Provide a simple link to download the file entity.'),
    'field' => array(
      'handler' => 'views_handler_field_file_link_download',
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
  );

  // Usage link.
  $data['file_managed']['usage'] = array(
    'title' => t('Usage link'),
    'help' => t('Provide a simple link to view the usage of the file entity.'),
    'field' => array(
      'handler' => 'views_handler_field_file_link_usage',
      'click sortable' => TRUE,
      'real field' => 'fid',
      'additional fields' => array(
        'fid',
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function file_entity_views_data_alter(&$data) {
  // Add access tag for all queries against file_managed.
  $data['file_managed']['table']['base']['access query tag'] = 'file_access';
  // Override the filename field handler.
  $data['file_managed']['filename']['field']['handler'] = 'views_handler_field_file_filename';
}

/**
 * Implements hook_views_plugins().
 */
function file_entity_views_plugins() {
  return array(
    'module' => 'views', // This just tells our themes are elsewhere.
    'row' => array(
      'file' => array(
        'title' => t('File'),
        'help' => t('Display the file with standard file view.'),
        'handler' => 'views_plugin_row_file_view',
        'base' => array('file_managed'), // only works with 'file' as base.
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-file',
      ),
      'file_rss' => array(
        'title' => t('File'),
        'help' => t('Display the file with standard file view.'),
        'handler' => 'views_plugin_row_file_rss',
        'theme' => 'views_view_row_rss',
        'base' => array('file_managed'), // only works with 'file' as base.
        'uses options' => TRUE,
        'type' => 'feed',
        'help topic' => 'style-file-rss',
      ),
    ),
  );
}

/**
 * Implements hook_views_query_substitutions().
 */
function file_entity_views_query_substitutions() {
  return array(
    '***ADMINISTER_FILES***' => intval(user_access('administer files')),
    '***BYPASS_FILE_ACCESS***' =>  intval(user_access('bypass file access')),
  );
}
