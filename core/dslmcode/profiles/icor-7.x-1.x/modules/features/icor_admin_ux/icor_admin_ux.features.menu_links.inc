<?php
/**
 * @file
 * icor_admin_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function icor_admin_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-toolkit_add-content:node/add
  $menu_links['menu-cis-toolkit_add-content:node/add'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Add content',
    'options' => array(
      'attributes' => array(
        'title' => 'Add content to icor for usage in other systems',
      ),
      'identifier' => 'menu-cis-toolkit_add-content:node/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_file-upload:file/add
  $menu_links['menu-cis-toolkit_file-upload:file/add'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'file/add',
    'router_path' => 'file/add',
    'link_title' => 'File upload',
    'options' => array(
      'attributes' => array(
        'title' => 'upload a single file',
      ),
      'identifier' => 'menu-cis-toolkit_file-upload:file/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_add-content:node/add',
  );
  // Exported menu link: menu-cis-toolkit_html5-interaction:node/add/h5p-content
  $menu_links['menu-cis-toolkit_html5-interaction:node/add/h5p-content'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add/h5p-content',
    'router_path' => 'node/add/h5p-content',
    'link_title' => 'HTML5 interaction',
    'options' => array(
      'attributes' => array(
        'title' => 'H5P interactive content type',
      ),
      'identifier' => 'menu-cis-toolkit_html5-interaction:node/add/h5p-content',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_add-content:node/add',
  );
  // Exported menu link: menu-cis-toolkit_interactive-player:node/add/icor-interactive-player
  $menu_links['menu-cis-toolkit_interactive-player:node/add/icor-interactive-player'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add/icor-interactive-player',
    'router_path' => 'node/add/icor-interactive-player',
    'link_title' => 'Interactive player',
    'options' => array(
      'attributes' => array(
        'title' => 'Interactive players are a "playlist" of other items in the site like timelines, polls, and other content',
      ),
      'identifier' => 'menu-cis-toolkit_interactive-player:node/add/icor-interactive-player',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_add-content:node/add',
  );
  // Exported menu link: menu-cis-toolkit_poll:node/add/poll
  $menu_links['menu-cis-toolkit_poll:node/add/poll'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add/poll',
    'router_path' => 'node/add/poll',
    'link_title' => 'Poll',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a poll',
      ),
      'identifier' => 'menu-cis-toolkit_poll:node/add/poll',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_add-content:node/add',
  );
  // Exported menu link: menu-cis-toolkit_quiz:node/add/quiz
  $menu_links['menu-cis-toolkit_quiz:node/add/quiz'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add/quiz',
    'router_path' => 'node/add',
    'link_title' => 'Quiz',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a quiz object',
      ),
      'identifier' => 'menu-cis-toolkit_quiz:node/add/quiz',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_add-content:node/add',
  );
  // Exported menu link: menu-cis-toolkit_timeline-date:node/add/timeline-date
  $menu_links['menu-cis-toolkit_timeline-date:node/add/timeline-date'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add/timeline-date',
    'router_path' => 'node/add/timeline-date',
    'link_title' => 'Timeline date',
    'options' => array(
      'attributes' => array(
        'title' => 'Create an individual element to associate to a timeline',
      ),
      'identifier' => 'menu-cis-toolkit_timeline-date:node/add/timeline-date',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_timeline:node/add/timeline',
  );
  // Exported menu link: menu-cis-toolkit_timeline:node/add/timeline
  $menu_links['menu-cis-toolkit_timeline:node/add/timeline'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'node/add/timeline',
    'router_path' => 'node/add/timeline',
    'link_title' => 'Timeline',
    'options' => array(
      'attributes' => array(
        'title' => 'A timeline is an organization of dates to form a timeline',
      ),
      'identifier' => 'menu-cis-toolkit_timeline:node/add/timeline',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_add-content:node/add',
  );
  // Exported menu link: menu-cis-toolkit_zip-upload:file/add/upload/archive
  $menu_links['menu-cis-toolkit_zip-upload:file/add/upload/archive'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'file/add/upload/archive',
    'router_path' => 'file/add/upload/archive',
    'link_title' => 'Zip upload',
    'options' => array(
      'attributes' => array(
        'title' => 'Upload a zip file that you want to reference',
      ),
      'identifier' => 'menu-cis-toolkit_zip-upload:file/add/upload/archive',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_file-upload:file/add',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add content');
  t('File upload');
  t('HTML5 interaction');
  t('Interactive player');
  t('Poll');
  t('Quiz');
  t('Timeline');
  t('Timeline date');
  t('Zip upload');


  return $menu_links;
}
