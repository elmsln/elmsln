<?php
/**
 * @file
 * cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops
  $menu_links['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/courses/bulk_ops',
    'router_path' => 'cis/courses/bulk_ops',
    'link_title' => 'Bulk Ops',
    'options' => array(
      'attributes' => array(
        'title' => 'Course Bulk Operations',
      ),
      'identifier' => 'menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_course-map:cis/courses/map
  $menu_links['menu-cis-toolkit_course-map:cis/courses/map'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/courses/map',
    'router_path' => 'cis/courses/map',
    'link_title' => 'Course Map',
    'options' => array(
      'attributes' => array(
        'title' => 'Visual list of courses',
      ),
      'identifier' => 'menu-cis-toolkit_course-map:cis/courses/map',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_course-map:cis/offerings/course-map
  $menu_links['menu-cis-toolkit_course-map:cis/offerings/course-map'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/offerings/course-map',
    'router_path' => 'cis/offerings/course-map',
    'link_title' => 'Course Map',
    'options' => array(
      'attributes' => array(
        'title' => 'Course Map',
      ),
      'identifier' => 'menu-cis-toolkit_course-map:cis/offerings/course-map',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'menu-cis-toolkit_offerings:cis/offerings',
  );
  // Exported menu link: menu-cis-toolkit_field-collection-admin:cis/admin/field-collections
  $menu_links['menu-cis-toolkit_field-collection-admin:cis/admin/field-collections'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/admin/field-collections',
    'router_path' => 'cis/admin/field-collections',
    'link_title' => 'Field Collection admin',
    'options' => array(
      'identifier' => 'menu-cis-toolkit_field-collection-admin:cis/admin/field-collections',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 30,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_offerings:cis/offerings
  $menu_links['menu-cis-toolkit_offerings:cis/offerings'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/offerings',
    'router_path' => 'cis/offerings',
    'link_title' => 'Offerings',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-toolkit_offerings:cis/offerings',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_people:cis/admin/people
  $menu_links['menu-cis-toolkit_people:cis/admin/people'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/admin/people',
    'router_path' => 'cis/admin/people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => 'view all people in the system',
      ),
      'identifier' => 'menu-cis-toolkit_people:cis/admin/people',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_resources:cis/resources
  $menu_links['menu-cis-toolkit_resources:cis/resources'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/resources',
    'router_path' => 'cis/resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all resources in the system',
      ),
      'identifier' => 'menu-cis-toolkit_resources:cis/resources',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_section-map:cis/offerings/section-map
  $menu_links['menu-cis-toolkit_section-map:cis/offerings/section-map'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/offerings/section-map',
    'router_path' => 'cis/offerings/section-map',
    'link_title' => 'Section Map',
    'options' => array(
      'attributes' => array(
        'title' => 'Section Map',
      ),
      'identifier' => 'menu-cis-toolkit_section-map:cis/offerings/section-map',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'menu-cis-toolkit_offerings:cis/offerings',
  );
  // Exported menu link: menu-cis-toolkit_semester-map:cis/offerings/semester-map
  $menu_links['menu-cis-toolkit_semester-map:cis/offerings/semester-map'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/offerings/semester-map',
    'router_path' => 'cis/offerings/semester-map',
    'link_title' => 'Semester Map',
    'options' => array(
      'attributes' => array(
        'title' => 'Semester Map',
      ),
      'identifier' => 'menu-cis-toolkit_semester-map:cis/offerings/semester-map',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'menu-cis-toolkit_offerings:cis/offerings',
  );
  // Exported menu link: menu-cis-toolkit_service-instances:cis/services/instances
  $menu_links['menu-cis-toolkit_service-instances:cis/services/instances'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/services/instances',
    'router_path' => 'cis/services/instances',
    'link_title' => 'Service Instances',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all services in the CIS',
      ),
      'identifier' => 'menu-cis-toolkit_service-instances:cis/services/instances',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 0,
    'parent_identifier' => 'menu-cis-toolkit_services:cis/services',
  );
  // Exported menu link: menu-cis-toolkit_service-map:cis/services/map
  $menu_links['menu-cis-toolkit_service-map:cis/services/map'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/services/map',
    'router_path' => 'cis/services/map',
    'link_title' => 'Service Map',
    'options' => array(
      'attributes' => array(
        'title' => 'Service map',
      ),
      'identifier' => 'menu-cis-toolkit_service-map:cis/services/map',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_services:cis/services
  $menu_links['menu-cis-toolkit_services:cis/services'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/services',
    'router_path' => 'cis/services',
    'link_title' => 'Services',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all services in the CIS',
      ),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-toolkit_services:cis/services',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 1,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Bulk Ops');
  t('Course Map');
  t('Field Collection admin');
  t('Offerings');
  t('People');
  t('Resources');
  t('Section Map');
  t('Semester Map');
  t('Service Instances');
  t('Service Map');
  t('Services');


  return $menu_links;
}
