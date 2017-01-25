<?php
/**
 * @file
 *   Test imagecache preset.
 *
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['rotate_alpha_gif'] = array (
  'name' => 'rotate_alpha_gif',
  '#weight' => 1.5,

  'effects' => array (
    1 => array (
      'weight' => '1',
      'module' => 'image',
      'name' => 'image_rotate',
      'data' => array (
        'degrees' => '15',
        'random' => 0,
        'bgcolor' => '',
      ),
    ),
    3 => array (
      'weight' => '3',
      'module' => 'imagecache_coloractions',
      'name' => 'coloractions_convert',
      'data' => array (
        'format' => 'image/gif',
        'quality' => '75',
      ),
    ),
  ),
);
