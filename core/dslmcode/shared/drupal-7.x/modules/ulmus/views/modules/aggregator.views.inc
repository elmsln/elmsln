<?php

/**
 * @file
 * Provide views data and handlers for aggregator.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function aggregator_views_data() {
  // ----------------------------------------------------------------------
  // Main Aggregator Item base table.
  // Define the base group of this table. Fields that don't have a group
  // defined will go into this field by default.
  $data['aggregator_item']['table']['group']  = t('Aggregator');

  // Advertise this table as a possible base table.
  $data['aggregator_item']['table']['base'] = array(
    'field' => 'iid',
    'title' => t('Aggregator item'),
    'help' => t("Aggregator items are imported from external RSS and Atom news feeds."),
  );

  // ----------------------------------------------------------------
  // Fields
  // Item ID / 'iid'.
  $data['aggregator_item']['iid'] = array(
    // The item it appears as on the UI,
    'title' => t('Item ID'),
    // The help that appears on the UI,
    'help' => t('The unique ID of the aggregator item.'),
    // Information for displaying the iid.
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    // Information for accepting a iid as an argument.
    'argument' => array(
      'handler' => 'views_handler_argument_aggregator_iid',
      'name field' => 'title',
      // The field to display in the summary.
      'numeric' => TRUE,
    ),
    // Information for accepting a nid as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a nid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Title.
  $data['aggregator_item']['title'] = array(
    // The item it appears as on the UI,
    'title' => t('Title'),
    'help' => t('The title of the aggregator item.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_aggregator_title_link',
      'extra' => array('link'),
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Link.
  $data['aggregator_item']['link'] = array(
    // The item it appears as on the UI,
    'title' => t('Link'),
    'help' => t('The link to the original source URL of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Author.
  $data['aggregator_item']['author'] = array(
    // The item it appears as on the UI,
    'title' => t('Author'),
    'help' => t('The author of the original imported item.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_aggregator_xss',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // 'guid'.
  $data['aggregator_item']['guid'] = array(
    // The item it appears as on the UI,
    'title' => t('GUID'),
    'help' => t('The guid of the original imported item.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Feed body.
  $data['aggregator_item']['description'] = array(
    // The item it appears as on the UI,
    'title' => t('Body'),
    'help' => t('The actual content of the imported item.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_aggregator_xss',
      'click sortable' => FALSE,
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Item timestamp.
  $data['aggregator_item']['timestamp'] = array(
    // The item it appears as on the UI,
    'title' => t('Timestamp'),
    'help' => t('The date the original feed item was posted. (With some feeds, this will be the date it was imported.)'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // ----------------------------------------------------------------------
  // Aggregator feed table.
  $data['aggregator_feed']['table']['group']  = t('Aggregator feed');

  // Explain how this table joins to others.
  $data['aggregator_feed']['table']['join'] = array(
    'aggregator_item' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  // Feed ID / 'fid'.
  $data['aggregator_feed']['fid'] = array(
    // The item it appears as on the UI,
    'title' => t('Feed ID'),
    // The help that appears on the UI,
    'help' => t('The unique ID of the aggregator feed.'),
    // Information for displaying the fid.
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    // Information for accepting a fid as an argument.
    'argument' => array(
      'handler' => 'views_handler_argument_aggregator_fid',
      'name field' => 'title',
      // The field to display in the summary.
      'numeric' => TRUE,
    ),
    // Information for accepting a nid as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a fid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Title.
  $data['aggregator_feed']['title'] = array(
    // The item it appears as on the UI,
    'title' => t('Title'),
    // The help that appears on the UI,
    'help' => t('The title of the aggregator feed.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_aggregator_title_link',
      'extra' => array('link'),
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Link.
  $data['aggregator_feed']['link'] = array(
    // The item it appears as on the UI,
    'title' => t('Link'),
    'help' => t('The link to the source URL of the feed.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Feed last updated.
  $data['aggregator_feed']['checked'] = array(
    // The item it appears as on the UI,
    'title' => t('Last checked'),
    'help' => t('The date the feed was last checked for new content.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Feed description.
  $data['aggregator_feed']['description'] = array(
    // The item it appears as on the UI,
    'title' => t('Description'),
    'help' => t('The description of the aggregator feed.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Feed last updated.
  $data['aggregator_feed']['modified'] = array(
    // The item it appears as on the UI,
    'title' => t('Last modified'),
    'help' => t('The date of the most recent new content on the feed.'),
    // Information for displaying a title as a field.
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    // Information for accepting a title as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // ----------------------------------------------------------------------
  // Aggregator category feed table.
  $data['aggregator_category_feed']['table']['join'] = array(
    'aggregator_item' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  // ----------------------------------------------------------------------
  // Aggregator category table.
  $data['aggregator_category']['table']['group'] = t('Aggregator category');

  $data['aggregator_category']['table']['join'] = array(
    'aggregator_item' => array(
      'left_table' => 'aggregator_category_feed',
      'left_field' => 'cid',
      'field' => 'cid',
    ),
  );

  // Category ID / 'cid'.
  $data['aggregator_category']['cid'] = array(
    'title' => t('Category ID'),
    'help' => t('The unique ID of the aggregator category.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_aggregator_category_cid',
      'name field' => 'title',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_aggregator_category_cid',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Title.
  $data['aggregator_category']['title'] = array(
    'title' => t('Category'),
    'help' => t('The title of the aggregator category.'),
    'field' => array(
      'handler' => 'views_handler_field_aggregator_category',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function aggregator_views_plugins() {
  return array(
    'module' => 'views',
    // This just tells our themes are elsewhere.
    'row' => array(
      'aggregator_rss' => array(
        'title' => t('Aggregator item'),
        'help' => t('Display the aggregator item using the data from the original source.'),
        'handler' => 'views_plugin_row_aggregator_rss',
        'path' => drupal_get_path('module', 'views') . '/modules/node',
        // Not necessary for most modules.
        'theme' => 'views_view_row_rss',
        'base' => array('aggregator_item'),
        // Only works with 'node' as base.
        'uses options' => TRUE,
        'type' => 'feed',
        'help topic' => 'style-aggregator-rss',
      ),
    ),
  );
}
