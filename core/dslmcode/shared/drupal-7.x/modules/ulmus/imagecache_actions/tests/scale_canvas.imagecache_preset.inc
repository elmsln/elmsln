<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['scale_canvas'] = array (
  'name' => 'scale_canvas',
  '#weight' => 2.1,

  'effects' => array (
    1 => array (
      'weight' => '1',
      'module' => 'image',
      'name' => 'image_scale',
      'data' => array (
        'width' => '100',
        'height' => '150',
        'upscale' => TRUE,
      ),
    ),
    2 => array (
      'weight' => '2',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_definecanvas',
      'data' => array (
        'RGB' => array (
          'HEX' => 'DDDDDD',
        ),
        'under' => 1,
        'exact' => array (
          'width' => '100',
          'height' => '150',
          'xpos' => 'center',
          'ypos' => 'center',
        ),
      ),
    ),
  ),
);