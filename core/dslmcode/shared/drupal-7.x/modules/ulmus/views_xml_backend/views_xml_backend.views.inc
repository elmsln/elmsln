<?php
/**
 * @file
 * Views hooks for views_xml_backend.
 */

/**
 * Implements hook_views_data().
 */
function views_xml_backend_views_data() {
  $data = array();
  $data['xml']['table']['group'] = t('XML');

  $data['xml']['table']['base'] = array(
    'title' => t('XML'),
    'help' => t('Queries an XML file.'),
    'query class' => 'views_xml_backend',
  );

  $data['xml']['passthru'] = array(
    'title' => t('Pass through'),
    'help' => t('This argument handler does not filter any values. It can be used to pass in values from an argument into token replacements.'),
    'argument' => array(
     'handler' => 'views_xml_backend_handler_argument_passthrough',
    ),
  );

  $data['xml']['text'] = array(
    'title' => t('Text'),
    'help' => t('Text in the XML file.'),
    'field' => array(
      'handler' => 'views_xml_backend_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_xml_backend_handler_filter',
    ),
    'sort' => array(
      'handler' => 'views_xml_backend_handler_sort',
    ),
    'argument' => array(
     'handler' => 'views_xml_backend_handler_argument',
    ),
  );

  $data['xml']['date'] = array(
    'title' => t('Date'),
    'help' => t('Date in the XML file.'),
    'field' => array(
      'handler' => 'views_xml_backend_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_xml_backend_handler_sort_date',
    ),
  );

  $data['xml']['numeric'] = array(
    'title' => t('Numeric'),
    'help' => t('A number in the XML file.'),
    //'field' => array(
    //  'handler' => 'views_xml_backend_handler_field',
    //),
    'filter' => array(
      'handler' => 'views_xml_backend_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_xml_backend_handler_sort_numeric',
    ),
    'argument' => array(
     'handler' => 'views_xml_backend_handler_argument_numeric',
    ),
  );

  $data['xml']['markup'] = array(
    'title' => t('Markup'),
    'help' => t('HTML markup in the XML file.'),
    'field' => array(
      'handler' => 'views_xml_backend_handler_field_markup',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function views_xml_backend_views_plugins() {
  return array(
    'query' => array(
      'views_xml_backend' => array(
        'title' => t('XML'),
        'help' => t('Reads from an XML file.'),
        'handler' => 'views_xml_backend_plugin_query_xml',
      ),
    ),
  );
}
