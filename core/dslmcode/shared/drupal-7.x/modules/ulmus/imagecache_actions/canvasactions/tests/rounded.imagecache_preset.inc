<?php
/**
 * @file
 *   Test imagecache preset.
 *
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['rounded'] = array (
  'name' => 'rounded',
  '#weight' => 3.0,
  'effects' => array (
    1 => array (
      'weight' => '0',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_roundedcorners',
      'data' => array (
        'radius' => '25',
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
