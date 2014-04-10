<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_two_50_panels_layouts() {
  $items['two_50'] = array(
    'title'    => t('AT Two column 50/50'),
    'category' => t('AT Responsive Panels - 2 column'),
    'icon'     => 'two_50.png',
    'theme'    => 'two_50',
    'admin css' => 'two_50.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'two_50_top'    => t('Top (conditional)'),
      'two_50_first'  => t('Left'),
      'two_50_second' => t('Right'),
      'two_50_bottom' => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'two',
    'options' => array(
      'two-50' => 'default',
      'two-50-stack' => 'stack',
    ),
    'styles' => array(
      'two-50' => array(
        'css' => array(
          '50' => array('.two-50 > .region' => 'width:50%'),
        ),
      ),
      'two-50-stack' => array(
        'css' => array(
          'fdw' => array('.two-50 > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for two-50.tpl.php
 */
function template_preprocess_two_50(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
