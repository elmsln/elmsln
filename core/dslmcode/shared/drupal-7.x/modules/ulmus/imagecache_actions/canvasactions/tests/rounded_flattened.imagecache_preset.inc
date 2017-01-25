<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['rounded_flattened'] = array (
  'name' => 'rounded_flattened',
  '#weight' => 3.3,

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
            'tr' => '100',
            'br' => '0',
            'tl' => '0',
            'bl' => '0',
          ),
        ),
        'antialias' => true,
      ),
    ),
    2 => array (
      'weight' => '0',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_definecanvas',
      'data' => array (
        'RGB' => array (
          'HEX' => '333333',
        ),
        'under' => 1,
        'exact' => array (
          'width' => '',
          'height' => '',
          'xpos' => 'center',
          'ypos' => 'center',
        ),
        'relative' => array (
          'leftdiff' => '2',
          'rightdiff' => '2',
          'topdiff' => '2',
          'bottomdiff' => '2',
        ),
      ),
    ),
  ),
);