<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['relative_canvas'] = array (
  'name' => 'relative_canvas',
  '#weight' => 2.0,
  'effects' => array (
    0 => array (
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
          'leftdiff' => '10',
          'rightdiff' => '10',
          'topdiff' => '10',
          'bottomdiff' => '10',
        ),
      ),
    ),
  ),
);