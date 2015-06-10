<?php
/**
 * @file
 * cis_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_types_ctools_plugin_api($module = NULL, $api = NULL) {
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
    'college_services' => array(
      'name' => t('College Services'),
      'base' => 'node_content',
      'description' => t('Services provided by the college, this is more so used for the marketing and front facing side of the CIS'),
      'has_title' => '1',
      'title_label' => t('Title'),
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
    'instructional_model' => array(
      'name' => t('Instructional Model'),
      'base' => 'node_content',
      'description' => t('Store reusable instructional models for helping to develop instructional best practices for your college to follow.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'news' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('News item, either stand alone or related to something on the site you want to highlight on the home page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('A basic information page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('Someone that has a page about themselves in the system.  This is intended for faculty and staff.'),
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
