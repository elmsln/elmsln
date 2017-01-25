<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['watermark_50'] = array (
  'name' => 'watermark_50',
  '#weight' => 4.1,
  'effects' => array (
    0 => array (
      'weight' => '0',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_file2canvas',
      'data' => array (
        'xpos' => 'right+20',
        'ypos' => 'bottom',
        'alpha' => '50',
        'path' => 'misc/druplicon.png',
      ),
    ),
  ),
);