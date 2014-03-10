<?php
/**
 * @file
 * cis_nodequeue.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_nodequeue_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cis_nodequeue_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_fe_nodequeue_export_fields().
 */
function cis_nodequeue_fe_nodequeue_export_fields() {
  $nodequeues = array();

  // Exported nodequeues: accolades
  $nodequeues['accolades'] = array(
    'name' => 'accolades',
    'title' => 'Accolades',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'news',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_faculty
  $nodequeues['cis_faculty'] = array(
    'name' => 'cis_faculty',
    'title' => 'Featured faculty',
    'subqueue_title' => '',
    'size' => 3,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'person',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_featured_courses
  $nodequeues['cis_featured_courses'] = array(
    'name' => 'cis_featured_courses',
    'title' => 'Featured courses',
    'subqueue_title' => '',
    'size' => 4,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'course',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_featured_services
  $nodequeues['cis_featured_services'] = array(
    'name' => 'cis_featured_services',
    'title' => 'Featured services',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'college_services',
      1 => 'service',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_homepage_featured
  $nodequeues['cis_homepage_featured'] = array(
    'name' => 'cis_homepage_featured',
    'title' => 'CIS homepage featured',
    'subqueue_title' => '',
    'size' => 6,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_programs
  $nodequeues['cis_programs'] = array(
    'name' => 'cis_programs',
    'title' => 'Featured programs',
    'subqueue_title' => '',
    'size' => 3,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'program',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: our_people
  $nodequeues['our_people'] = array(
    'name' => 'our_people',
    'title' => 'Our people',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'person',
    ),
    'roles' => array(),
    'count' => 0,
  );

  return $nodequeues;
}
