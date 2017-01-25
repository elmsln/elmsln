<?php
/**
 * @file
 *   Test imagecache preset.
 *
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['rounded_bl'] = array (
  'name' => 'rounded_bl',
  '#weight' => 3.1,
  'effects' => array (
    1 => array (
      'weight' => '0',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_roundedcorners',
      'data' => array (
        'radius' => '50',
        'independent_corners_set' => array (
          'independent_corners' => 1,
          'radii' => array (
            'tl' => '10',
            'tr' => '0',
            'bl' => '50',
            'br' => '10',
          ),
        ),
        'antialias' => true,
      ),
    ),
    2 => array (
      'weight' => '3',
      'module' => 'imagecache_coloractions',
      'name' => 'coloractions_convert',
      'data' =>array (
        'format' => 'image/png',
        'quality' => '95',
      ),
    ),
  ),
);
