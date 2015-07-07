<?php
/**
 * @file
 * elmsmedia_cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function elmsmedia_cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-add_audio:node/add/audio
  $menu_links['menu-cis-add_audio:node/add/audio'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/audio',
    'router_path' => 'node/add/audio',
    'link_title' => 'Audio',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_audio:node/add/audio',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_document:node/add/document
  $menu_links['menu-cis-add_document:node/add/document'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/document',
    'router_path' => 'node/add/document',
    'link_title' => 'Document',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_document:node/add/document',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_external-video:node/add/external-video
  $menu_links['menu-cis-add_external-video:node/add/external-video'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/external-video',
    'router_path' => 'node/add/external-video',
    'link_title' => 'External Video',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_external-video:node/add/external-video',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_image:node/add/elmsmedia-image
  $menu_links['menu-cis-add_image:node/add/elmsmedia-image'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/elmsmedia-image',
    'router_path' => 'node/add/elmsmedia-image',
    'link_title' => 'Image',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_image:node/add/elmsmedia-image',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_interactive-content:node/add/h5p-content
  $menu_links['menu-cis-add_interactive-content:node/add/h5p-content'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/h5p-content',
    'router_path' => 'node/add/h5p-content',
    'link_title' => 'Interactive content',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_interactive-content:node/add/h5p-content',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_video:node/add/video
  $menu_links['menu-cis-add_video:node/add/video'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/video',
    'router_path' => 'node/add/video',
    'link_title' => 'Video',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_video:node/add/video',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Audio');
  t('Document');
  t('External Video');
  t('Image');
  t('Interactive content');
  t('Video');


  return $menu_links;
}
