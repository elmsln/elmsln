<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_three_inset_right_panels_layouts() {
  $items['three_inset_right'] = array(
    'title'    => t('AT Inset right'),
    'category' => t('AT Responsive Panels - Inset'),
    'icon'     => 'three_inset_right.png',
    'theme'    => 'three_inset_right',
    'admin css' => 'three_inset_right.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_inset_right_sidebar' => t('Sidebar'),
      'three_inset_right_top'     => t('Top (conditional)'),
      'three_inset_right_middle'  => t('Middle'),
      'three_inset_right_inset'   => t('Inset'),
      'three_inset_right_bottom'  => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'inset',
    'options' => array(
      'three-inset-right' => 'default',
      'three-inset-right-wrap' => 'wrap',
      'three-inset-right-stack' => 'stack',
    ),
    'styles' => array(
      'three-inset-right' => array(
        'css' => array(
          '25' => array('.three-inset-right > .region-three-inset-right-sidebar' => 'width:25%'),
          '75fl' => array('.three-inset-right > .inset-wrapper' => 'width:75%;float:left'),
          '33' => array('.three-inset-right > .inset-wrapper > div.region-three-inset-right-inset' => 'width:33.333333%'),
          '66' => array('.three-inset-right > .inset-wrapper > div.region-three-inset-right-middle' => 'width:66.666666%'),
          '100' => array('.three-inset-right > .inset-wrapper > .region' => 'width:100%'),
        ),
      ),
      'three-inset-right-wrap' => array(
        'css' => array(
          '25'   => array('.three-inset-right > .region-three-inset-right-sidebar' => 'width:25%'),
          '75fl' => array('.three-inset-right > .inset-wrapper' => 'width:75%;float:left'),
          'fdw'  => array('.three-inset-right > .inset-wrapper > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-inset-right-stack' => array(
        'css' => array(
          'fdw' => array('.three-inset-right > .inset-wrapper,.three-inset-right > .inset-wrapper > .region,.three-inset-right > .region-three-inset-right-sidebar' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for three-inset-right.tpl.php
 */
function template_preprocess_three_inset_right(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
