<?php
/**
 * @file
 * Views include file with views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_data_export_views_plugins() {
  $path = drupal_get_path('module', 'views_data_export');

  $style_defaults = array(
    'path' => $path . '/plugins',
    'parent' => 'views_data_export',
    'theme' => 'views_data_export',
    'theme path' => $path . '/theme',
    'theme file' => 'views_data_export.theme.inc',
    'uses row plugin' => FALSE,
    'uses fields' => TRUE,
    'uses options' => TRUE,
    'type' => 'data_export',
  );

  return array(
    'display' => array (
      'views_data_export' => array(
        'title' => t('Data export'),
        'help' => t('Export the view results to a file. Can handle very large result sets.'),
        'path' => $path . '/plugins',
        'handler' => 'views_data_export_plugin_display_export',
        'parent' => 'feed',
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('Data export'),
        'help topic' => 'display-data-export',
      ),
    ),
    'style' => array(
      'views_data_export' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_data_export_plugin_style_export',
        'path' => $path . '/plugins',
        'theme path' => $path . '/theme',
        'theme file' => 'views_data_export.theme.inc',
        'type' => 'normal',
      ),
      'views_data_export_csv' => array(
        'title' => t('CSV file'),
        'help' => t('Display the view as a comma separated list.'),
        'handler' => 'views_data_export_plugin_style_export_csv',
        // Views Data Export element that will be used to set additional headers when serving the feed.
        'export headers' => array('Content-type' => 'text/csv; charset=utf-8'),
        // Views Data Export element mostly used for creating some additional classes and template names.
        'export feed type' => 'csv',
        'export feed text' => 'CSV',
        'export feed file' => '%view.csv',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/csv.png',
        'additional themes' => array(
          'views_data_export_csv_header' => 'style',
          'views_data_export_csv_body' => 'style',
          'views_data_export_csv_footer' => 'style',
        ),
        'additional themes base' => 'views_data_export_csv',
      ) + $style_defaults,
      'views_data_export_doc' => array(
        'title' => t('DOC file'),
        'help' => t('Display the view as a doc file.'),
        'handler' => 'views_data_export_plugin_style_export',
        'export headers' => array('Content-Type' => 'application/msword'),
        'export feed type' => 'doc',
        'export feed text' => 'Word Document',
        'export feed file' => '%view.doc',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/doc.png',
        'additional themes' => array(
          'views_data_export_doc_header' => 'style',
          'views_data_export_doc_body' => 'style',
          'views_data_export_doc_footer' => 'style',
        ),
        'additional themes base' => 'views_data_export_doc',
      ) + $style_defaults,
      'views_data_export_txt' => array(
        'title' => t('TXT file'),
        'help' => t('Display the view as a txt file.'),
        'handler' => 'views_data_export_plugin_style_export',
        'export headers' => array('Content-Type' => 'text/plain'),
        'export feed type' => 'txt',
        'export feed text' => 'Plain Text Document',
        'export feed file' => '%view.txt',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/txt.png',
        'additional themes' => array(
          'views_data_export_txt_header' => 'style',
          'views_data_export_txt_body' => 'style',
          'views_data_export_txt_footer' => 'style',
        ),
        'additional themes base' => 'views_data_export_txt',
      ) + $style_defaults,
      'views_data_export_xls' => array(
        'title' => t('XLS file'),
        'help' => t('Display the view as a xls file.'),
        'handler' => 'views_data_export_plugin_style_export',
        'export headers' => array('Content-Type' => 'application/vnd.ms-excel'),
        'export feed type' => 'xls',
        'export feed text' => 'XLS',
        'export feed file' => '%view.xls',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/xls.png',
        'additional themes' => array(
          'views_data_export_xls_header' => 'style',
          'views_data_export_xls_body' => 'style',
          'views_data_export_xls_footer' => 'style',
        ),
        'additional themes base' => 'views_data_export_xls',
      ) + $style_defaults,
      'views_data_export_xml' => array(
        'title' => t('XML file'),
        'help' => t('Display the view as a txt file.'),
        'handler' => 'views_data_export_plugin_style_export_xml',
        'export headers' => array('Content-Type' => 'text/xml'),
        'export feed type' => 'xml',
        'export feed text' => 'XML',
        'export feed file' => '%view.xml',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/xml.png',
        'additional themes' => array(
          'views_data_export_xml_header' => 'style',
          'views_data_export_xml_body' => 'style',
          'views_data_export_xml_footer' => 'style',
        ),
        'additional themes base' => 'views_data_export_xml',
      ) + $style_defaults,
    ),
  );
}
