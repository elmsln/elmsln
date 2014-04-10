<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_six_6x16_panels_layouts() {
  $items['six_6x16'] = array(
    'title'    => t('AT Six column 6x16'),
    'category' => t('AT Responsive Panels - 4,5,6 column'),
    'icon'     => 'six_6x16.png',
    'theme'    => 'six_6x16',
    'admin css' => 'six_6x16.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'six_first'  => t('Column 1'),
      'six_second' => t('Column 2'),
      'six_third'  => t('Column 3'),
      'six_fourth' => t('Column 4'),
      'six_fifth'  => t('Column 5'),
      'six_sixth'  => t('Column 6'),
    ),
    // AT Core
    'type' => 'six',
    'options' => array(
      'six-6x16' => 'default',
      'six-6x16-3x2-grid' => '3x2 grid',
      'six-6x16-2x3-grid' => '2x3 grid',
      'six-6x16-stack' => 'stack',
    ),
    'styles' => array(
      'six-6x16' => array(
        'css' => array(
          '33fl' => array('.six-6x16 > .panel-row' => 'width:33.333333%;float:left'),
          '50' => array('.six-6x16 > .panel-row > .region' => 'width:50%'),
        ),
      ),
      'six-6x16-3x2-grid' => array(
        'css' => array(
          '33fl' => array('.six-6x16 > .panel-row' => 'width:33.333333%;float:left'),
          'fdw' => array('.six-6x16 > .panel-row > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'six-6x16-2x3-grid' => array(
        'css' => array(
          'fdw' => array('.six-6x16 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
          '50fl' => array('.six-6x16 > .panel-row > .region' => 'width:50%;float:left'),
        ),
      ),
      'six-6x16-stack' => array(
        'css' => array(
          'fdw' => array('.six-6x16 > .panel-row > .region,.six-6x16 > .panel-row ' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for six-6x16.tpl.php
 */
function template_preprocess_six_6x16(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
