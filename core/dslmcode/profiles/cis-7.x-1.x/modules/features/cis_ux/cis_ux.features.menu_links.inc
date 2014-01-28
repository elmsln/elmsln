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

  // Exported menu link: management:admin/config/system/cis
  $menu_links['management:admin/config/system/cis'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/cis',
    'router_path' => 'admin/config/system/cis',
    'link_title' => 'CIS',
    'options' => array(
      'attributes' => array(
        'title' => 'Course information system configuration',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/config/system',
  );
  // Exported menu link: management:cis
  $menu_links['management:cis'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis',
    'router_path' => 'cis',
    'link_title' => 'CIS',
    'options' => array(
      'attributes' => array(
        'title' => 'CIS list of courses',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
  );
  // Exported menu link: management:cis/admin
  $menu_links['management:cis/admin'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/admin',
    'router_path' => 'cis',
    'link_title' => 'Admin',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -42,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/admin/field-collections
  $menu_links['management:cis/admin/field-collections'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/admin/field-collections',
    'router_path' => 'cis/admin/field-collections',
    'link_title' => 'Field Collection admin',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'parent_path' => 'cis/admin',
  );
  // Exported menu link: management:cis/admin/people
  $menu_links['management:cis/admin/people'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/admin/people',
    'router_path' => 'cis/admin/people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => 'view all people in the system',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/courses
  $menu_links['management:cis/courses'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/courses',
    'router_path' => 'cis/courses',
    'link_title' => 'Courses',
    'options' => array(
      'attributes' => array(
        'title' => 'List of courses',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/courses/bulk_ops
  $menu_links['management:cis/courses/bulk_ops'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/courses/bulk_ops',
    'router_path' => 'cis/courses/bulk_ops',
    'link_title' => 'Bulk ops',
    'options' => array(
      'attributes' => array(
        'title' => 'Course bulk operations',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/courses',
  );
  // Exported menu link: management:cis/courses/map
  $menu_links['management:cis/courses/map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/courses/map',
    'router_path' => 'cis/courses/map',
    'link_title' => 'Course map',
    'options' => array(
      'attributes' => array(
        'title' => 'Visual list of courses',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/courses',
  );
  // Exported menu link: management:cis/historical_college_data
  $menu_links['management:cis/historical_college_data'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data',
    'router_path' => 'cis/historical_college_data',
    'link_title' => 'College data',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -43,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/historical_college_data/campus
  $menu_links['management:cis/historical_college_data/campus'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data/campus',
    'router_path' => 'cis/historical_college_data/campus',
    'link_title' => 'Campus',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/historical_college_data',
  );
  // Exported menu link: management:cis/historical_college_data/program
  $menu_links['management:cis/historical_college_data/program'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data/program',
    'router_path' => 'cis/historical_college_data/program',
    'link_title' => 'Program',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 1,
    'parent_path' => 'cis/historical_college_data',
  );
  // Exported menu link: management:cis/historical_college_data/program/enrollments
  $menu_links['management:cis/historical_college_data/program/enrollments'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data/program/enrollments',
    'router_path' => 'cis/historical_college_data/program/enrollments',
    'link_title' => 'Enrollments',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'parent_path' => 'cis/historical_college_data/program',
  );
  // Exported menu link: management:cis/historical_college_data/unit
  $menu_links['management:cis/historical_college_data/unit'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data/unit',
    'router_path' => 'cis/historical_college_data/unit',
    'link_title' => 'Unit',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 1,
    'parent_path' => 'cis/historical_college_data',
  );
  // Exported menu link: management:cis/historical_college_data/unit/enrollments
  $menu_links['management:cis/historical_college_data/unit/enrollments'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data/unit/enrollments',
    'router_path' => 'cis/historical_college_data/unit/enrollments',
    'link_title' => 'Enrollments',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'parent_path' => 'cis/historical_college_data/unit',
  );
  // Exported menu link: management:cis/historical_college_data/year
  $menu_links['management:cis/historical_college_data/year'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/historical_college_data/year',
    'router_path' => 'cis/historical_college_data/year',
    'link_title' => 'Year',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -1,
    'parent_path' => 'cis/historical_college_data',
  );
  // Exported menu link: management:cis/offerings
  $menu_links['management:cis/offerings'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings',
    'router_path' => 'cis/offerings',
    'link_title' => 'Offerings',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/offerings/course-map
  $menu_links['management:cis/offerings/course-map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings/course-map',
    'router_path' => 'cis/offerings/course-map',
    'link_title' => 'Course map',
    'options' => array(
      'attributes' => array(
        'title' => 'Course map',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'parent_path' => 'cis/offerings',
  );
  // Exported menu link: management:cis/offerings/manage-semester
  $menu_links['management:cis/offerings/manage-semester'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings/manage-semester',
    'router_path' => 'cis/offerings',
    'link_title' => 'Manage semester',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'parent_path' => 'cis/offerings',
  );
  // Exported menu link: management:cis/offerings/planning
  $menu_links['management:cis/offerings/planning'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings/planning',
    'router_path' => 'cis/offerings/planning',
    'link_title' => 'Planning',
    'options' => array(
      'attributes' => array(
        'title' => 'Plan what courses are going to be offered in the future',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'parent_path' => 'cis/offerings',
  );
  // Exported menu link: management:cis/offerings/section-map
  $menu_links['management:cis/offerings/section-map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings/section-map',
    'router_path' => 'cis/offerings/section-map',
    'link_title' => 'Section map',
    'options' => array(
      'attributes' => array(
        'title' => 'Section map',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'parent_path' => 'cis/offerings',
  );
  // Exported menu link: management:cis/offerings/semester-map
  $menu_links['management:cis/offerings/semester-map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings/semester-map',
    'router_path' => 'cis/offerings/semester-map',
    'link_title' => 'Semester map',
    'options' => array(
      'attributes' => array(
        'title' => 'Semester map',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'parent_path' => 'cis/offerings',
  );
  // Exported menu link: management:cis/programs
  $menu_links['management:cis/programs'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/programs',
    'router_path' => 'cis/programs',
    'link_title' => 'Programs',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/programs/map
  $menu_links['management:cis/programs/map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/programs/map',
    'router_path' => 'cis/programs/map',
    'link_title' => 'Program map',
    'options' => array(
      'attributes' => array(
        'title' => 'Program mapping',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/programs',
  );
  // Exported menu link: management:cis/resources
  $menu_links['management:cis/resources'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/resources',
    'router_path' => 'cis/resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all resources in the system',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/services
  $menu_links['management:cis/services'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/services',
    'router_path' => 'cis/services',
    'link_title' => 'Services',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all services in the CIS',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -44,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/services/instances
  $menu_links['management:cis/services/instances'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/services/instances',
    'router_path' => 'cis/services/instances',
    'link_title' => 'Service instances',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all services in the CIS',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'parent_path' => 'cis/services',
  );
  // Exported menu link: management:cis/services/map
  $menu_links['management:cis/services/map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/services/map',
    'router_path' => 'cis/services/map',
    'link_title' => 'Service map',
    'options' => array(
      'attributes' => array(
        'title' => 'Service map',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/services',
  );
  // Exported menu link: management:cis/units
  $menu_links['management:cis/units'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/units',
    'router_path' => 'cis/units',
    'link_title' => 'Units',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'parent_path' => 'cis',
  );
  // Exported menu link: management:cis/units/map
  $menu_links['management:cis/units/map'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/units/map',
    'router_path' => 'cis/units/map',
    'link_title' => 'Unit map',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/units',
  );
  // Exported menu link: management:node/add/academic-unit
  $menu_links['management:node/add/academic-unit'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/academic-unit',
    'router_path' => 'node/add/academic-unit',
    'link_title' => 'Add unit',
    'options' => array(
      'attributes' => array(
        'title' => 'Add an academic unit',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 27,
    'parent_path' => 'cis/units',
  );
  // Exported menu link: management:node/add/course
  $menu_links['management:node/add/course'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/course',
    'router_path' => 'node/add/course',
    'link_title' => 'Add course',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a course to CIS',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 27,
    'parent_path' => 'cis/courses',
  );
  // Exported menu link: management:node/add/program
  $menu_links['management:node/add/program'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/program',
    'router_path' => 'node/add/program',
    'link_title' => 'Add program',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a program of study',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 29,
    'parent_path' => 'cis/programs',
  );
  // Exported menu link: management:node/add/resource
  $menu_links['management:node/add/resource'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/resource',
    'router_path' => 'node/add/resource',
    'link_title' => 'Add resource',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new resource for use in courses',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'cis/resources',
  );
  // Exported menu link: management:node/add/service
  $menu_links['management:node/add/service'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/service',
    'router_path' => 'node/add/service',
    'link_title' => 'Add service',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a service for courses to use',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 30,
    'parent_path' => 'cis/services',
  );
  // Exported menu link: user-menu:cis-quick-setup
  $menu_links['user-menu:cis-quick-setup'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'cis-quick-setup',
    'router_path' => 'cis-quick-setup',
    'link_title' => 'Build service instance',
    'options' => array(
      'attributes' => array(
        'title' => 'Use this to build a course, associate an offering and section to it, and then go and request the setup of webservices that will be used by the course.',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'user',
  );
  // Exported menu link: user-menu:login
  $menu_links['user-menu:login'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'login',
    'router_path' => 'login',
    'link_title' => 'Login',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: user-menu:user
  $menu_links['user-menu:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
  );
  // Exported menu link: user-menu:user/logout
  $menu_links['user-menu:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add course');
  t('Add program');
  t('Add resource');
  t('Add service');
  t('Add unit');
  t('Admin');
  t('Build service instance');
  t('Bulk ops');
  t('CIS');
  t('Campus');
  t('College data');
  t('Course map');
  t('Courses');
  t('Enrollments');
  t('Field collection admin');
  t('Log out');
  t('Login');
  t('Manage semester');
  t('Offerings');
  t('People');
  t('Planning');
  t('Program');
  t('Program map');
  t('Programs');
  t('Resources');
  t('Section map');
  t('Semester map');
  t('Service instances');
  t('Service map');
  t('Services');
  t('Unit');
  t('Unit map');
  t('Units');
  t('User account');
  t('Year');


  return $menu_links;
}
