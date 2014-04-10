<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_two_66_33_panels_layouts() {
  $items['two_66_33'] = array(
    'title' => t('AT Two column 66/33'),
    'category' => t('AT Responsive Panels - 2 column'),
    'icon' => 'two_66_33.png',
    'theme' => 'two_66_33',
    'admin css' => 'two_66_33.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'two_66_33_top'    => t('Top (conditional)'),
      'two_66_33_first'  => t('Left'),
      'two_66_33_second' => t('Right'),
      'two_66_33_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'two',
    'options' => array(
      'two-66-33' => 'default',
      'two-66-33-stack' => 'stack',
    ),
    'styles' => array(
      'two-66-33' => array(
        'css' => array(
          '66' => array('.two-66-33 > .region-two-66-33-first' => 'width:66.666666%'),
          '33' => array('.two-66-33 > .region-two-66-33-second' => 'width:33.333333%'),
        ),
      ),
      'two-66-33-stack' => array(
        'css' => array(
          'fdw' => array('.two-66-33 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for two-66-33.php
 */
function template_preprocess_two_66_33(&$vars, $hook) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
