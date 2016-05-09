<?php
/**
 * @file
 * cis_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cis_types_node_info() {
  $items = array(
    'academic_unit' => array(
      'name' => t('Academic Unit'),
      'base' => 'node_content',
      'description' => t('Academic home, unit, department, or school that courses can then be associated to.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'course' => array(
      'name' => t('Course'),
      'base' => 'node_content',
      'description' => t('A course that we have on the books to help with management'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'program' => array(
      'name' => t('Program'),
      'base' => 'node_content',
      'description' => t('Program of courses'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'resource' => array(
      'name' => t('Course Resource'),
      'base' => 'node_content',
      'description' => t('A resource that can be utilized across courses and sections.  This is standard language for describing how to use different services and technologies used in a course.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'service' => array(
      'name' => t('Web Service'),
      'base' => 'node_content',
      'description' => t('Registration of a new learning service'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'service_instance' => array(
      'name' => t('Service instance'),
      'base' => 'node_content',
      'description' => t('The instance of a course on a service.  This relationship helps CIS know what other sites exist where as well as store information specifically related to this service implementation.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
