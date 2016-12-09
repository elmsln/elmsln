<?php

/**
 * @file
 * EPUB Version Views integration.
 *
 * @ingroup print
 */

/**
 * Implements hook_views_data().
 */
function print_epub_views_data() {
  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['print_epub_node_conf']['table']['group'] = t('Printer-friendly version');
  $data['print_epub_page_counter']['table']['group'] = t('Printer-friendly version');

  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
  $data['print_epub_node_conf']['table']['join']['node'] = array(
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'left_field' => 'nid',
    'field' => 'nid',
  );
  $data['print_epub_page_counter']['table']['join']['node'] = array(
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'left_field' => 'nid',
    'field' => 'path',
    'handler' => 'print_join_page_counter',
  );

  // print_epub_node_conf fields.
  $data['print_epub_node_conf']['link'] = array(
    'title' => t('EPUB: Show link'),
    'help' => t('Whether to show the EPUB version link.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['print_epub_node_conf']['comments'] = array(
    'title' => t('EPUB: Show link in individual comments'),
    'help' => t('Whether to show the EPUB version link in individual comments.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['print_epub_node_conf']['url_list'] = array(
    'title' => t('EPUB: Show Printer-friendly URLs list'),
    'help' => t('Whether to show the URL list.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // print_epub_page_counter fields.
  $data['print_epub_page_counter']['totalcount'] = array(
    'title' => t('EPUB: Number of page accesses'),
    'help' => t('Counter of accesses to the EPUB version for this node.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['print_epub_page_counter']['timestamp'] = array(
    'title' => t('EPUB: Last access'),
    'help' => t("The date of the last access to the node's EPUB version."),
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
  );

  return $data;
}
