<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_three_25_50_25_panels_layouts() {
  $items['three_25_50_25'] = array(
    'title'    => t('AT Three column 25/50/25'),
    'category' => t('AT Responsive Panels - 3 column'),
    'icon'     => 'three_25_50_25.png',
    'theme'    => 'three_25_50_25',
    'admin css' => 'three_25_50_25.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_25_50_25_top'    => t('Top (conditional)'),
      'three_25_50_25_first'  => t('Left'),
      'three_25_50_25_second' => t('Center'),
      'three_25_50_25_third'  => t('Right'),
      'three_25_50_25_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'three',
    'options' => array(
      'three-25-50-25' => 'default',
      'three-25-50-25-stack-bottom' => 'stack bottom',
      'three-25-50-25-stack-top' => 'stack top',
      'three-25-50-25-stack' => 'stack',
    ),
    'styles' => array(
      'three-25-50-25' => array(
        'css' => array(
          '25' => array('.three-25-50-25 > .region' => 'width:25%'),
          '50' => array('.three-25-50-25 > div.region-three-25-50-25-second' => 'width:50%'),
        ),
      ),
      'three-25-50-25-stack-bottom' => array(
        'css' => array(
          '25' => array('.three-25-50-25 > div.region-three-25-50-25-first' => 'width:25%'),
          '75' => array('.three-25-50-25 > div.region-three-25-50-25-second' => 'width:75%'),
          'fdw' => array('.three-25-50-25 > .region-three-25-50-25-third' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-25-50-25-stack-top' => array(
        'css' => array(
          'fdw' => array('.three-25-50-25 > .region-three-25-50-25-first' => 'float:none;display:block;width:100%;clear:both'),
          '75' => array('.three-25-50-25 > div.region-three-25-50-25-second' => 'width:75%'),
          '25' => array('.three-25-50-25 > div.region-three-25-50-25-third' => 'width:25%'),
        ),
      ),
      'three-25-50-25-stack' => array(
        'css' => array(
          'fdw' => array('.three-25-50-25 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for three-25-50-25.tpl.php
 */
function template_preprocess_three_25_50_25(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
