<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_three_3x33_panels_layouts() {
  $items['three_3x33'] = array(
    'title'    => t('AT Three column 3x33'),
    'category' => t('AT Responsive Panels - 3 column'),
    'icon'     => 'three_3x33.png',
    'theme'    => 'three_3x33',
    'admin css' => 'three_3x33.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_33_top'    => t('Top (conditional)'),
      'three_33_first'  => t('Left'),
      'three_33_second' => t('Center'),
      'three_33_third'  => t('Right'),
      'three_33_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'three',
    'options' => array(
      'three-3x33' => 'default',
      'three-3x33-5050-stack-bottom' => 'even stack bottom', // new layout for 7.x-3.2
      'three-3x33-stack-bottom' => 'stack bottom',
      'three-3x33-stack-top' => 'stack top',
      'three-3x33-stack' => 'stack',
    ),
    'styles' => array(
      'three-3x33' => array(
        'css' => array(
          '33' => array('.three-3x33 > .region' => 'width:33.333333%'),
        ),
      ),
      'three-3x33-5050-stack-bottom' => array(
        'css' => array(
          '50' => array('.three-3x33 > .region' => 'width:50%'),
          'fdw' => array('.three-3x33 > .region-three-33-third' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-3x33-stack-bottom' => array(
        'css' => array(
          '66' => array('.three-3x33 > .region-three-33-first' => 'width:66.666666%'),
          '33' => array('.three-3x33 > .region-three-33-second' => 'width:33.333333%'),
          'fdw' => array('.three-3x33 > .region-three-33-third' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
       'three-3x33-stack-top' => array(
        'css' => array(
          '50' => array('.three-3x33 > .region' => 'width:50%'),
          'fdw' => array('.three-3x33 > div.region-three-33-first' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-3x33-stack' => array(
        'css' => array(
          'fdw' => array('.three-3x33 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for three-3x33.tpl.php
 */
function template_preprocess_three_3x33(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
