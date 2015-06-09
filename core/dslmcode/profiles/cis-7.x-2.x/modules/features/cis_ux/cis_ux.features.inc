<?php
/**
 * @file
 * cis_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "flexslider" && $api == "flexslider_default_preset") {
    return array("version" => "1");
  }
  if ($module == "path_breadcrumbs" && $api == "path_breadcrumbs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "video_embed_field" && $api == "default_video_embed_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_menu_default_menu_links_alter().
 */
function cis_ux_menu_default_menu_links_alter(&$data) {
  if (isset($data['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops'])) {
    $data['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops']['customized'] = 1; /* WAS: 0 */
    $data['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops']['has_children'] = 1; /* WAS: 0 */
    $data['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops']['weight'] = -47; /* WAS: 0 */
    unset($data['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops']['options']['identifier']);
  }
  if (isset($data['menu-cis-toolkit_course-map:cis/courses/map'])) {
    unset($data['menu-cis-toolkit_course-map:cis/courses/map']);
  }
  if (isset($data['menu-cis-toolkit_course-map:cis/offerings/course-map'])) {
    unset($data['menu-cis-toolkit_course-map:cis/offerings/course-map']);
  }
  if (isset($data['menu-cis-toolkit_field-collection-admin:cis/admin/field-collections'])) {
    unset($data['menu-cis-toolkit_field-collection-admin:cis/admin/field-collections']);
  }
  if (isset($data['menu-cis-toolkit_offerings:cis/offerings'])) {
    unset($data['menu-cis-toolkit_offerings:cis/offerings']);
  }
  if (isset($data['menu-cis-toolkit_people:cis/admin/people'])) {
    unset($data['menu-cis-toolkit_people:cis/admin/people']);
  }
  if (isset($data['menu-cis-toolkit_resources:cis/resources'])) {
    unset($data['menu-cis-toolkit_resources:cis/resources']);
  }
  if (isset($data['menu-cis-toolkit_section-map:cis/offerings/section-map'])) {
    unset($data['menu-cis-toolkit_section-map:cis/offerings/section-map']);
  }
  if (isset($data['menu-cis-toolkit_semester-map:cis/offerings/semester-map'])) {
    unset($data['menu-cis-toolkit_semester-map:cis/offerings/semester-map']);
  }
  if (isset($data['menu-cis-toolkit_service-instances:cis/services/instances'])) {
    unset($data['menu-cis-toolkit_service-instances:cis/services/instances']);
  }
  if (isset($data['menu-cis-toolkit_service-map:cis/services/map'])) {
    unset($data['menu-cis-toolkit_service-map:cis/services/map']);
  }
  if (isset($data['menu-cis-toolkit_services:cis/services'])) {
    unset($data['menu-cis-toolkit_services:cis/services']);
  }
}
