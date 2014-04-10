<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_two_33_66_panels_layouts() {
  $items['two_33_66'] = array(
    'title' => t('AT Two column 33/66'),
    'category' => t('AT Responsive Panels - 2 column'),
    'icon' => 'two_33_66.png',
    'theme' => 'two_33_66',
    'admin css' => 'two_33_66.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'two_33_66_top'    => t('Top (conditional)'),
      'two_33_66_first'  => t('Left'),
      'two_33_66_second' => t('Right'),
      'two_33_66_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'two',
    'options' => array(
      'two-33-66' => 'default',
      'two-33-66-stack' => 'stack',
    ),
    'styles' => array(
      'two-33-66' => array(
        'css' => array(
          '33' => array('.two-33-66 > .region-two-33-66-first' => 'width:33.333333%'),
          '66' => array('.two-33-66 > .region-two-33-66-second' => 'width:66.666666%'),
        ),
      ),
      'two-33-66-stack' => array(
        'css' => array(
          'fdw' => array('.two-33-66 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for two-33-66.tpl.php
 */
function template_preprocess_two_33_66(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
