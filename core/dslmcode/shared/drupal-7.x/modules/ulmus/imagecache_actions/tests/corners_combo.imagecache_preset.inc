<?php
/**
 * @file
 *   Test imagecache preset.
 * 
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['corners_combo'] = array (
  'name' => 'corners_combo',
  '#weight' => 9,
  'effects' =>  array (
    0 => array (
      'weight' => '-10',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_definecanvas',
      'data' => array (
        'RGB' => array (
          'HEX' => 'e5e8a1',
        ),
        'under' => 1,
        'exact' => array (
          'width' => '',
          'height' => '',
          'xpos' => 'center',
          'ypos' => 'center',
        ),
        'relative' =>  array (
          'leftdiff' => '4',
          'rightdiff' => '4',
          'topdiff' => '4',
          'bottomdiff' => '4',
        ),
      ),
    ),
    1 => array (
      'weight' => '-9',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_definecanvas',
      'data' => array (
        'RGB' =>  array (
          'HEX' => '',
        ),
        'under' => 1,
        'exact' => array (
          'width' => '',
          'height' => '',
          'xpos' => 'center',
          'ypos' => 'center',
        ),
        'relative' => array (
          'leftdiff' => '4',
          'rightdiff' => '4',
          'topdiff' => '4',
          'bottomdiff' => '4',
        ),
      ),
    ),
    2 => array (
      'weight' => '-8',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_file2canvas',
      'data' => array (
        'xpos' => 'left',
        'ypos' => 'top',
        'alpha' => '100',
        'path' => "$filepath/corner-tl.png",
      ),
    ),
    3 => array (
      'weight' => '-7',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_file2canvas',
      'data' =>  array (
        'xpos' => 'right',
        'ypos' => 'top',
        'alpha' => '100',
        'path' => "$filepath/corner-tr.png",
      ),
    ),
    4 => 
    array (
      'weight' => '-6',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_file2canvas',
      'data' => array (
        'xpos' => 'left',
        'ypos' => 'bottom',
        'alpha' => '100',
        'path' => "$filepath/corner-bl.png",
      ),
    ),
    5 => array (
      'weight' => '-5',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_file2canvas',
      'data' => array (
        'xpos' => 'right',
        'ypos' => 'bottom',
        'alpha' => '100',
        'path' => "$filepath/corner-br.png",
      ),
    ),
    6 => array (
      'weight' => '-4',
      'module' => 'image',
      'name' => 'image_rotate',
      'data' => array (
        'degrees' => '7',
        'random' => 0,
        'bgcolor' => '',
      ),
    ),
    7 => array (
      'weight' => '-3',
      'module' => 'image',
      'name' => 'image_scale',
      'data' => array (
        'width' => '300',
        'height' => '',
        'upscale' => 0,
      ),
    ),
    8 => array (
      'weight' => '-2',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_canvas2file',
      'data' => array (
        'xpos' => '',
        'ypos' => '',
        'alpha' => '100',
        'path' => "$filepath/background-2.jpg",
        'dimensions' => 'original',
      ),
    ),
  ),
);