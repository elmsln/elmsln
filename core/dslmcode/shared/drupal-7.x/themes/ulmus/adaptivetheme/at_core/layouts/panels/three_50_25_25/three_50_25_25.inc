<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_three_50_25_25_panels_layouts() {
  $items['three_50_25_25'] = array(
    'title'    => t('AT Three column 50/25/25'),
    'category' => t('AT Responsive Panels - 3 column'),
    'icon'     => 'three_50_25_25.png',
    'theme'    => 'three_50_25_25',
    'admin css' => 'three_50_25_25.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_50_25_25_top'    => t('Top (conditional)'),
      'three_50_25_25_first'  => t('Left'),
      'three_50_25_25_second' => t('Center'),
      'three_50_25_25_third'  => t('Right'),
      'three_50_25_25_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'three',
    'options' => array(
      'three-50-25-25' => 'default',
      'three-50-25-25-stack-bottom' => 'stack bottom',
      'three-50-25-25-stack-top' => 'stack top',
      'three-50-25-25-stack' => 'stack',
    ),
    'styles' => array(
      'three-50-25-25' => array(
        'css' => array(
          '25' => array('.three-50-25-25 > .region' => 'width:25%'),
          '50' => array('.three-50-25-25 > div.region-three-50-25-25-first' => 'width:50%'),
        ),
      ),
      'three-50-25-25-stack-bottom' => array(
        'css' => array(
          '75' => array('.three-50-25-25 > div.region-three-50-25-25-first' => 'width:75%'),
          '25' => array('.three-50-25-25 > div.region-three-50-25-25-second' => 'width:25%'),
          'fdw' => array('.three-50-25-25 > .region-three-50-25-25-third' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-50-25-25-stack-top' => array(
        'css' => array(
          '50' => array('.three-50-25-25 > .region-three-50-25-25-second,.three-50-25-25 .region-three-50-25-25-third' => 'width:50%'),
          'fdw' => array('.three-50-25-25 > .region-three-50-25-25-first' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-50-25-25-stack' => array(
        'css' => array(
          'fdw' => array('.three-50-25-25 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for three-50-25-25.tpl.php
 */
function template_preprocess_three_50_25_25(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
