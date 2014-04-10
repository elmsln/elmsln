<?php

/**
 * @file
 * Implementation of hook_panels_layouts
 */
function adaptivetheme_two_brick_panels_layouts() {
  $items['two_brick'] = array(
    'title'    => t('AT Two column brick'),
    'category' => t('AT Responsive Panels - 2 column'),
    'icon'     => 'two_brick.png',
    'theme'    => 'two_brick',
    'admin css' => 'two_brick.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'two_brick_top'         => t('Top (conditional)'),
      'two_brick_left_above'  => t('Left above'),
      'two_brick_right_above' => t('Right above'),
      'two_brick_middle'      => t('Middle (conditional)'),
      'two_brick_left_below'  => t('Left below'),
      'two_brick_right_below' => t('Right below'),
      'two_brick_bottom'      => t('Bottom (conditional)'),
    ),
    // AT Core
    'type' => 'two',
    'options' => array(
      'two-brick' => 'default',
      'two-brick-stack' => 'stack',
    ),
    'styles' => array(
      'two-brick' => array(
        'css' => array(
          'fn' => array('.two-brick > .panel-row' => 'float:none'),
          '50' => array('.two-brick > .panel-row > .region' => 'width:50%'),
        ),
      ),
      'two-brick-stack' => array(
        'css' => array(
          'fdw' => array('.two-brick > .panel-row > .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Preprocess variables for two-brick.tpl.php
 */
function template_preprocess_two_brick(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
