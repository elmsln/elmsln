<?php
/**
 * @file
 * cle_cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cle_cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-add_create-assignment:node/add/cle-assignment
  $menu_links['menu-cis-add_create-assignment:node/add/cle-assignment'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/cle-assignment',
    'router_path' => 'node/add/cle-assignment',
    'link_title' => 'Create Assignment',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_create-assignment:node/add/cle-assignment',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_create-submission:node/add/cle-submission
  $menu_links['menu-cis-add_create-submission:node/add/cle-submission'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/cle-submission',
    'router_path' => 'node/add/cle-submission',
    'link_title' => 'Create Submission',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_create-submission:node/add/cle-submission',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cle-navigation_assignments-list:cle/assignments
  $menu_links['menu-cle-navigation_assignments-list:cle/assignments'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/assignments',
    'router_path' => 'cle/assignments',
    'link_title' => 'Assignments list',
    'options' => array(
      'attributes' => array(
        'title' => 'Listing of assignments for this section',
      ),
      'identifier' => 'menu-cle-navigation_assignments-list:cle/assignments',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 0,
  );
  // Exported menu link: menu-cle-navigation_files:cle/my-gallery/files
  $menu_links['menu-cle-navigation_files:cle/my-gallery/files'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery/files',
    'router_path' => 'cle/my-gallery/files',
    'link_title' => 'Files',
    'options' => array(
      'attributes' => array(
        'title' => 'All my files as a gallery',
      ),
      'identifier' => 'menu-cle-navigation_files:cle/my-gallery/files',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 0,
    'parent_identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
  );
  // Exported menu link: menu-cle-navigation_images:cle/my-gallery/images
  $menu_links['menu-cle-navigation_images:cle/my-gallery/images'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery/images',
    'router_path' => 'cle/my-gallery/images',
    'link_title' => 'Images',
    'options' => array(
      'attributes' => array(
        'title' => 'All my submissions as a gallery',
      ),
      'identifier' => 'menu-cle-navigation_images:cle/my-gallery/images',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 0,
    'parent_identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
  );
  // Exported menu link: menu-cle-navigation_links:cle/my-gallery/links
  $menu_links['menu-cle-navigation_links:cle/my-gallery/links'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery/links',
    'router_path' => 'cle/my-gallery/links',
    'link_title' => 'Links',
    'options' => array(
      'attributes' => array(
        'title' => 'All my links as a gallery',
      ),
      'identifier' => 'menu-cle-navigation_links:cle/my-gallery/links',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 4,
    'customized' => 0,
    'parent_identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
  );
  // Exported menu link: menu-cle-navigation_my-gallery:cle/my-gallery
  $menu_links['menu-cle-navigation_my-gallery:cle/my-gallery'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery',
    'router_path' => 'cle/my-gallery',
    'link_title' => 'My Gallery',
    'options' => array(
      'attributes' => array(
        'title' => 'All of my submissions for this course',
      ),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 9,
    'customized' => 1,
  );
  // Exported menu link: menu-cle-navigation_overview:cle/my-gallery/overview
  $menu_links['menu-cle-navigation_overview:cle/my-gallery/overview'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery/overview',
    'router_path' => 'cle/my-gallery/overview',
    'link_title' => 'Overview',
    'options' => array(
      'attributes' => array(
        'title' => 'Overview of your submissions',
      ),
      'identifier' => 'menu-cle-navigation_overview:cle/my-gallery/overview',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -1,
    'customized' => 0,
    'parent_identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
  );
  // Exported menu link: menu-cle-navigation_video:cle/my-gallery/video
  $menu_links['menu-cle-navigation_video:cle/my-gallery/video'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery/video',
    'router_path' => 'cle/my-gallery/video',
    'link_title' => 'Video',
    'options' => array(
      'attributes' => array(
        'title' => 'All my videos as a gallery',
      ),
      'identifier' => 'menu-cle-navigation_video:cle/my-gallery/video',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 0,
    'parent_identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Assignments list');
  t('Create Assignment');
  t('Create Submission');
  t('Files');
  t('Images');
  t('Links');
  t('My Gallery');
  t('Overview');
  t('Video');


  return $menu_links;
}
