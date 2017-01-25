<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['scale_rotate'] = array (
  'name' => 'scale_rotate',
  '#weight' => 1.3,

  'effects' => array (
    1 => array (
      'weight' => '1',
      'module' => 'image',
      'name' => 'image_scale',
      'data' => array (
        'width' => '',
        'height' => '150',
        'upscale' => TRUE,
      ),
    ),
    2 => array (
      'weight' => '2',
      'module' => 'image',
      'name' => 'image_rotate',
      'data' => array (        
        'degrees' => '15',
        'random' => 0,
        'bgcolor' => '',
      ),
    ),
  ),
);