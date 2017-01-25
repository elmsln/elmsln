<?php
/**
 * @file
 *   Test imagecache preset.
 *
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['positioned_underlay'] = array (
  'name' => 'positioned_underlay',
  '#weight' => 4.4,
  'effects' => array (
    0 => array (
      'module' => 'image',
      'name' => 'image_scale',
      'weight' => '0',
      'data' => array (
        'width' => '200',
        'height' => '',
        'upscale' => 0,
      ),
    ),
    1 => array (
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_canvas2file',
      'weight' => '1',
      'data' => array (
        'xpos' => '50',
        'ypos' => 'bottom+50',
        'alpha' => '100',
        'path' => "$filepath/shiny-bg.png",
        'dimensions' => 'background',
      ),
    ),
    4 => array (
      'weight' => '10',
      'module' => 'imagecache_coloractions',
      'name' => 'coloractions_convert',
      'data' => array (
        'format' => 'image/png',
        'quality' => '95',
      ),
    ),
  ),
);
