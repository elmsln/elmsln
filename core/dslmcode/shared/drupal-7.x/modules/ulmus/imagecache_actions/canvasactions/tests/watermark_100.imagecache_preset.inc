<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['watermark_100'] = array (
  'name' => 'watermark_100',
  '#weight' => 4.0,
  'effects' => array (
    0 => array (
      'weight' => '0',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_file2canvas',
      'data' => array (
        'xpos' => '10',
        'ypos' => '5',
        'alpha' => '100',
        'path' => 'misc/druplicon.png',
      ),
    ),
  ),
);