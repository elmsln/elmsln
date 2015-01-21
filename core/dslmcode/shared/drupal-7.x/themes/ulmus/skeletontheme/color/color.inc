<?php

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'text' => t('Text color'),
    'link' => t('Links color'),
    'linkhover' => t('Links hover color'),
	'headings' => t('Headings color'),
    'sitename' => t('Site-name color'),
    'sitenamehover' => t('Site-name hover color'),
	'slogan' => t('Slogan color'),
	'bodyborder' => t('Body border top color'),
    'wrapborder' => t('Content border top color'),
	'footerborder' => t('Footer border top color'),
	'footerbackground' => t('Footer background color'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Default'),
      'colors' => array(
	    'text' => '#444444',
        'link' => '#2883DE',
		'linkhover' => '#000000',
    	'headings' => '#181818',
		'sitename' => '#262626',
        'sitenamehover' => '#3253ad',
		'slogan' => '#7d7d7d',
		'bodyborder' => '#375199',
    	'wrapborder' => '#4565be',
		'footerborder' => '#d6d6d6',
    	'footerbackground' => '#ffffff',
      ),
    ),
	'coronamusic' => array(
      'title' => t('Corona Music'),
      'colors' => array(
	    'text' => '#101010',
        'link' => '#e29300',
		'linkhover' => '#e29300',
    	'headings' => '#101010',
		'sitename' => '#194973',
        'sitenamehover' => '#263973',
		'slogan' => '#101010',
		'bodyborder' => '#194973',
    	'wrapborder' => '#e29300',
		'footerborder' => '#d6d6d6',
    	'footerbackground' => '#ffffff',
      ),
    ),
	'easycomeeasygo' => array(
      'title' => t('Easy Come Easy Go'),
      'colors' => array(
	    'text' => '#161616',
        'link' => '#b52c38',
		'linkhover' => '#b52c38',
    	'headings' => '#536682',
		'sitename' => '#536682',
        'sitenamehover' => '#536682',
		'slogan' => '#161616',
		'bodyborder' => '#de6846',
    	'wrapborder' => '#d9964b',
		'footerborder' => '#d6d6d6',
    	'footerbackground' => '#ffffff',
      ),
    ),
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'color/colors.css',
  ),
  
  // Files to copy.
  'copy' => array(
    'logo.png',
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
