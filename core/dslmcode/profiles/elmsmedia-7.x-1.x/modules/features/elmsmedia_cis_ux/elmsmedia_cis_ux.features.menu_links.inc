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

  // Exported menu link: menu-elmsln-add_audio:node/add/audio.
  $menu_links['menu-elmsln-add_audio:node/add/audio'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_audio:node/add/audio',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_document:node/add/document.
  $menu_links['menu-elmsln-add_document:node/add/document'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_document:node/add/document',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_external-video:node/add/external-video.
  $menu_links['menu-elmsln-add_external-video:node/add/external-video'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_external-video:node/add/external-video',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_figure-label:node/add/figurelabel.
  $menu_links['menu-elmsln-add_figure-label:node/add/figurelabel'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/figurelabel',
    'router_path' => 'node/add/figurelabel',
    'link_title' => 'Figure label',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_figure-label:node/add/figurelabel',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_h5p:node/add/h5p-content.
  $menu_links['menu-elmsln-add_h5p:node/add/h5p-content'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/h5p-content',
    'router_path' => 'node/add/h5p-content',
    'link_title' => 'H5P',
    'options' => array(
      'identifier' => 'menu-elmsln-add_h5p:node/add/h5p-content',
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_image-gallery:node/add/image-gallery.
  $menu_links['menu-elmsln-add_image-gallery:node/add/image-gallery'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/image-gallery',
    'router_path' => 'node/add/image-gallery',
    'link_title' => 'Image gallery',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_image-gallery:node/add/image-gallery',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_image:node/add/elmsmedia-image.
  $menu_links['menu-elmsln-add_image:node/add/elmsmedia-image'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_image:node/add/elmsmedia-image',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_static-content:node/add/static-content.
  $menu_links['menu-elmsln-add_static-content:node/add/static-content'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/static-content',
    'router_path' => 'node/add/static-content',
    'link_title' => 'Static content',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_static-content:node/add/static-content',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_svg:node/add/svg.
  $menu_links['menu-elmsln-add_svg:node/add/svg'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/svg',
    'router_path' => 'node/add/svg',
    'link_title' => 'SVG',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_svg:node/add/svg',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_video:node/add/video.
  $menu_links['menu-elmsln-add_video:node/add/video'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_video:node/add/video',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -41,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Audio');
  t('Document');
  t('External Video');
  t('Figure label');
  t('H5P');
  t('Image');
  t('Image gallery');
  t('SVG');
  t('Static content');
  t('Video');

  return $menu_links;
}
