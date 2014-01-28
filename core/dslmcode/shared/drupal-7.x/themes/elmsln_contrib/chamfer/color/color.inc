<?php
// $Id: color.inc,v 1.7 2010/12/14 19:53:14 dries Exp $

// Put the logo path into JavaScript for the live preview.
drupal_add_js(array('color' => array('logo' => theme_get_setting('logo', 'chamfer'))), 'setting');

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'bg_top' => t('BG top'),
    'bg_bottom' => t('BG bottom'),
    'ext_link' => t('Exterior link'),
    'ext_text' => t('Exterior text'),
    'page_header' => t('Page headers'),
    'page_links' => t('Page links'),
    'section_header' => t('Section headers'),
    'section_links' => t('Section links'),
    'section_link_active' => t('Section a.active'),
    'menu_link' => t('Menu links'),
    'menu_link_active' => t('Menu a.active'),
    'menu_shadow' => t('Menu shadow'),
  ),  
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Default'),
      'colors' => array(
        'bg_top' => '#111111',
        'bg_bottom' => '#333333',
        'ext_link' => '#00ffff',
        'ext_text' => '#eeeeee',
        'page_header' => '#555555',
        'page_links' => '#000000',
        'section_header' => '#222222',
        'section_links' => '#6d6d6d',
        'section_link_active' => '#ee9999',
        'menu_link' => '#cccccc',
        'menu_link_active' => '#00f9f9',
        'menu_shadow' => '#111111',
      ),
    ),
    'drupal_org' => array(
      'title' => t('Drupal.org'),
      'colors' => array(
        'bg_top' => '#56b3e6',
        'bg_bottom' => '#EEEEEE',
        'ext_link' => '#FFFFFF',
        'ext_text' => '#EEEEEE',
        'page_header' => '#222222',
        'page_links' => '#0678BE',
        'section_header' => '#222222',
        'section_links' => '#0678BE',
        'section_link_active' => '#222222',
        'menu_link' => '#56b3e6',
        'menu_link_active' => '#EEEEEE',
        'menu_shadow' => '#222222',
      ),
    ),
    'space_opera' => array(
      'title' => t('Space opera'),
      'colors' => array(
        'bg_top' => '#000000',
        'bg_bottom' => '#111111',
        'ext_link' => '#00ccff',
        'ext_text' => '#00eeff',
        'page_header' => '#00b1ff',
        'page_links' => '#0099ff',
        'section_header' => '#00b1ff',
        'section_links' => '#0099ff',
        'section_link_active' => '#584efb',
        'menu_link' => '#cccccc',
        'menu_link_active' => '#fbf64e',
        'menu_shadow' => '#fbf64e',
      ),
    ),
    'silver' => array(
      'title' => t('Silver'),
      'colors' => array(
        'bg_top' => '#e4e4e4',
        'bg_bottom' => '#e7e7e7',
        'ext_link' => '#5d5d5d',
        'ext_text' => '#1d1d1d',
        'page_header' => '#222222',
        'page_links' => '#494949',
        'section_header' => '#222222',
        'section_links' => '#0e0e0e',
        'section_link_active' => '#acacac',
        'menu_link' => '#9f9f9f',
        'menu_link_active' => '#ffffff',
        'menu_shadow' => '#818181',
      ),
    ),
    'mud_brown' => array(
      'title' => t('Mud browns'),
      'colors' => array(
        'bg_top' => '#4d3a2b',
        'bg_bottom' => '#552714',
        'ext_link' => '#b57d52',
        'ext_text' => '#dfbd93',
        'page_header' => '#836c50',
        'page_links' => '#bb7e18',
        'section_header' => '#836c50',
        'section_links' => '#a76d18',
        'section_link_active' => '#df8d28',
        'menu_link' => '#d2bb91',
        'menu_link_active' => '#f9a900',
        'menu_shadow' => '#8c5900',
      ),
    ),
    'floral_green' => array(
      'title' => t('Floral green'),
      'colors' => array(
        'bg_top' => '#ffffde',
        'bg_bottom' => '#e1ffcf',
        'ext_link' => '#4a4933',
        'ext_text' => '#0e0e0e',
        'page_header' => '#535726',
        'page_links' => '#3c5400',
        'section_header' => '#64692e',
        'section_links' => '#486e00',
        'section_link_active' => '#90792f',
        'menu_link' => '#ebe490',
        'menu_link_active' => '#ffea4a',
        'menu_shadow' => '#b57400',
      ),
    ),
  ),
  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/colors.css',
  ),

  // Files to copy.
  'copy' => array(
  ),

  // Gradient definitions.
  'gradients' => array(
    array(
      // (x, y, width, height).
      'dimension' => array(0, 0, 0, 0),
      // Direction of gradient ('vertical' or 'horizontal').
      'direction' => 'vertical',
      // Keys of colors to use for the gradient.
      'colors' => array('top', 'bottom'),
    ),
  ),

  // Color areas to fill (x, y, width, height).
  'fill' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_css' => 'color/preview.css',
  'preview_js' => 'color/preview.js',
  'preview_html' => 'color/preview.html',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);
// allow modules to influence color schemes
drupal_alter('chamfer_color_schemes', $info);