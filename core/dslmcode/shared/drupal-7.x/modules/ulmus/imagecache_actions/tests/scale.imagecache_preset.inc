<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['scale'] = array (
  'name' => 'scale',
  '#weight' => 1.1,
  'effects' => array (
    0 => array (
      'weight' => '-1',
      'module' => 'image',
      'name' => 'image_scale',
      'data' => array (
        'width' => '100',
        'height' => '',
        'upscale' => 0,
      ),
    ),
  )
);