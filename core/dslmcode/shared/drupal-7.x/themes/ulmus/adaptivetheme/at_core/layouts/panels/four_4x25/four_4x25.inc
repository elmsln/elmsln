<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_four_4x25_panels_layouts() {
  $items['four_4x25'] = array(
    'title'    => t('AT Four column 4x25'),
    'category' => t('AT Responsive Panels - 4,5,6 column'),
    'icon'     => 'four_4x25.png',
    'theme'    => 'four_4x25',
    'admin css' => 'four_4x25.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'four_first'  => t('Column 1'),
      'four_second' => t('Column 2'),
      'four_third'  => t('Column 3'),
      'four_fourth' => t('Column 4'),
    ),
    // AT Core
    'type' => 'four',
    'options' => array(
      'four-4x25' => 'default',
      'four-4x25-right-stack' => 'stack right',
      'four-4x25-2x2-grid' => '2x2 grid',
      'four-4x25-stack' => 'stack',
    ),
    'styles' => array(
      'four-4x25' => array(
        'css' => array(
          '50fl' => array('.four-4x25 > .panel-row > .region,.four-4x25 > .panel-row' => 'width:50%;float:left'),
        ),
      ),
      'four-4x25-right-stack' => array(
        'css' => array(
          '50fl' => array('.four-4x25 > .panel-row,.four-4x25 > .row-2 > .region' => 'width:50%;float:left'),
          'fdw' => array('.four-4x25 > .row-1 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'four-4x25-2x2-grid' => array(
        'css' => array(
          '50' => array('.four-4x25 > .panel-row > .region' => 'width:50%'),
          'fdw' => array('.four-4x25 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'four-4x25-stack' => array(
        'css' => array(
          'fdw' => array('.four-4x25 > .panel-row > .region,.four-4x25 > .panel-row' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for four-4x25.tpl.php
 */
function template_preprocess_four_4x25(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
