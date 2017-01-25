<?php
/**
 * @file
 *   Test imagecache preset.
 *
 * Created on Dec 29, 2009
 *
 * @author 'dman' Dan Morrison http://coders.co.nz/
 */

$presets['cheap_dropshadow'] = array (
  'name' => 'cheap_dropshadow',
  '#weight' => '3.3',
  'effects' =>
  array (
    -1 => array (
      'weight' => '-1',
      'module' => 'imagecache_coloractions',
      'name' => 'coloractions_convert',
      'data' => array (
        'format' => 'image/png',
        'quality' => '95',
      ),
    ),
    0 =>
    array (
      'weight' => '0',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_definecanvas',
      'data' =>
      array (
        'RGB' =>
        array (
          'HEX' => '999999',
        ),
        'under' => 0,
        'exact' =>
        array (
          'width' => '',
          'height' => '',
          'xpos' => 'center',
          'ypos' => 'center',
        ),
        'relative' =>
        array (
          'leftdiff' => '0',
          'rightdiff' => '0',
          'topdiff' => '0',
          'bottomdiff' => '0',
        ),
      ),
    ),
    1 =>
    array (
      'weight' => '1',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_definecanvas',
      'data' =>
      array (
        'RGB' =>
        array (
          'HEX' => '',
        ),
        'under' => 1,
        'exact' =>
        array (
          'width' => '',
          'height' => '',
          'xpos' => 'center',
          'ypos' => 'center',
        ),
        'relative' =>
        array (
          'leftdiff' => '20',
          'rightdiff' => '0',
          'topdiff' => '20',
          'bottomdiff' => '0',
        ),
      ),
    ),
    2 =>
    array (
      'weight' => '2',
      'module' => 'imagecache_canvasactions',
      'name' => 'canvasactions_source2canvas',
      'data' =>
      array (
        'xpos' => 0,
        'ypos' => 0,
        'alpha' => '100',
      ),
    ),
    3 =>
    array (
      'weight' => '3',
      'module' => 'image',
      'name' => 'image_scale',
      'data' =>
      array (
        'width' => '200',
        'height' => '100%',
        'upscale' => 0,
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
