<?php

/**
 * @file
 * The Node export formats file.
 *
 * Implements the default node export format handlers.
 */

/**
 * Implements hook_node_export_format_handlers().
 */
function node_export_node_export_format_handlers() {
  return array(
    'json' => array(
      '#title' => t('JSON'),
      '#module' => 'node_export',
      '#file' => drupal_get_path('module', 'node_export') . '/formats/json.inc',
      '#description' => t(
        '<a href="!json">JavaScript Object Notation</a> code.',
        array(
          '!json' => 'http://en.wikipedia.org/wiki/JSON'
        )
      ),
      '#mime' => 'application/json',
      '#export_callback' => 'node_export_json_export',
      '#import_callback' => 'node_export_json_import',
    ),

    'drupal' => array(
      '#title' => t('Drupal var export'),
      '#module' => 'node_export',
      '#file' => drupal_get_path('module', 'node_export') . '/formats/drupal.inc',
      '#description' => t(
        '<a href="!drupal">Drupal var export</a> code.',
        array(
          '!drupal' => 'http://api.drupal.org/api/drupal/includes!utility.inc/function/drupal_var_export/7'
        )
      ),
      '#export_callback' => 'node_export_drupal_export',
      '#import_callback' => 'node_export_drupal_import',
    ),

    'serialize' => array(
      '#title' => t('Serialize'),
      '#module' => 'node_export',
      '#file' => drupal_get_path('module', 'node_export') . '/formats/serialize.inc',
      '#description' => t(
        'Very robust, though not human readable, representation through <a href="!wiki">Serialization</a> using the PHP <a href="!php">serialize</a> function.',
        array(
          '!wiki' => 'http://tools.ietf.org/html/rfc4180',
          '!php' => 'http://en.wikipedia.org/wiki/Comma-separated_values'
        )
      ),
      '#export_callback' => 'node_export_serialize_export',
      '#import_callback' => 'node_export_serialize_import',
    ),

    'xml' => array(
      '#title' => t('XML'),
      '#module' => 'node_export',
      '#file' => drupal_get_path('module', 'node_export') . '/formats/xml.inc',
      '#description' => t(
        '<a href="!xml">XML 1.0</a> representation which is good for machine-readability and human-readability.',
        array(
          '!xml' => 'http://en.wikipedia.org/wiki/XML',
        )
      ),
      '#mime' => 'application/xml',
      '#export_callback' => 'node_export_xml_export',
      '#import_callback' => 'node_export_xml_import',
    ),

    'dsv' => array(
      '#title' => t('DSV'),
      '#module' => 'node_export',
      '#file' => drupal_get_path('module', 'node_export') . '/formats/dsv.inc',
      '#description' => t(
        'Configurable <a href="!dsv">Delimiter-separated values</a> code. Export and import sites must be configured the same.',
        array(
          '!dsv' => 'http://en.wikipedia.org/wiki/Delimiter-separated_values'
        )
      ),
      '#settings_callback' => 'node_export_dsv_settings',
      '#export_callback' => 'node_export_dsv_export',
      '#import_callback' => 'node_export_dsv_import',
    ),

  );
}
