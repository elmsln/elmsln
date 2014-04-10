<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_three_25_25_50_panels_layouts() {
  $items['three_25_25_50'] = array(
    'title'    => t('AT Three column 25/25/50'),
    'category' => t('AT Responsive Panels - 3 column'),
    'icon'     => 'three_25_25_50.png',
    'theme'    => 'three_25_25_50',
    'admin css' => 'three_25_25_50.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_25_25_50_top'    => t('Top (conditional)'),
      'three_25_25_50_first'  => t('Left'),
      'three_25_25_50_second' => t('Center'),
      'three_25_25_50_third'  => t('Right'),
      'three_25_25_50_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'three',
    'options' => array(
      'three-25-25-50' => 'default',
      'three-25-25-50-stack-bottom' => 'stack bottom',
      'three-25-25-50-stack-top' => 'stack top',
      'three-25-25-50-stack' => 'stack',
    ),
    'styles' => array(
      'three-25-25-50' => array(
        'css' => array(
          '25' => array('.three-25-25-50 > .region' => 'width:25%'),
          '50' => array('.three-25-25-50 > div.region-three-25-25-50-third' => 'width:50%'),
        ),
      ),
      'three-25-25-50-stack-bottom' => array(
        'css' => array(
          '50' => array('.three-25-25-50 > .region' => 'width:50%'),
          'fdw' => array('.three-25-25-50 > .region-three-25-25-50-third' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-25-25-50-stack-top' => array(
        'css' => array(
          'fdw' => array('.three-25-25-50 > .region-three-25-25-50-first' => 'float:none;display:block;width:100%;clear:both'),
          '25' => array('.three-25-25-50 > div.region-three-25-25-50-second' => 'width:25%'),
          '75' => array('.three-25-25-50 > div.region-three-25-25-50-third' => 'width:75%'),
        ),
      ),
      'three-25-25-50-stack' => array(
        'css' => array(
          'fdw' => array('.three-25-25-50 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for three-25-25-50.tpl.php
 */
function template_preprocess_three_25_25_50(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
