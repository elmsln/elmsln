<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_three_inset_left_panels_layouts() {
  $items['three_inset_left'] = array(
    'title' => t('AT Inset left'),
    'category' => t('AT Responsive Panels - Inset'),
    'icon' => 'three_inset_left.png',
    'theme' => 'three_inset_left',
    'admin css' => 'three_inset_left.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_inset_left_sidebar' => t('Sidebar'),
      'three_inset_left_top'     => t('Top (conditional)'),
      'three_inset_left_middle'  => t('Middle'),
      'three_inset_left_inset'   => t('Inset'),
      'three_inset_left_bottom'  => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'inset',
    'options' => array(
      'three-inset-left' => 'default',
      'three-inset-left-wrap' => 'wrap',
      'three-inset-left-stack' => 'stack',
    ),
    'styles' => array(
      'three-inset-left' => array(
        'css' => array(
          'fr' => array('.three-inset-left > .region-three-inset-left-sidebar,.three-inset-left > .inset-wrapper,.three-inset-left > .inset-wrapper > .region-three-inset-left-middle' => 'float:right'),
          '25' => array('.three-inset-left > .region-three-inset-left-sidebar' => 'width:25%'),
          '75' => array('.three-inset-left > .inset-wrapper' => 'width:75%'),
          '33' => array('.three-inset-left > .inset-wrapper > div.region-three-inset-left-inset' => 'width:33.333333%'),
          '66' => array('.three-inset-left > .inset-wrapper > div.region-three-inset-left-middle' => 'width:66.666666%'),
          '100' => array('.three-inset-left > .inset-wrapper > .region' => 'width:100%'),
        ),
      ),
      'three-inset-left-wrap' => array(
        'css' => array(
          '25fr' => array('.three-inset-left > .region-three-inset-left-sidebar' => 'width:25%;float:right'),
          '75fr' => array('.three-inset-left > .inset-wrapper' => 'width:75%;float:right'),
          'fdw'  => array('.three-inset-left > .inset-wrapper > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-inset-left-stack' => array(
        'css' => array(
          'fdw' => array('.three-inset-left > .inset-wrapper,.three-inset-left > .inset-wrapper > .region,.three-inset-left > .region-three-inset-left-sidebar' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for three-inset-left.tpl.php
 */
function template_preprocess_three_inset_left(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
