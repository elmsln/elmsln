<?php

function joyride_preprocess_joyride_start_link(&$vars) {
  if(empty($vars['options'])) $vars['options'] = array();

  if(!isset($vars['options']['attributes']['class'])) $vars['options']['attributes']['class'] = array();
  $vars['options']['attributes']['class'][] = 'joyride-start-link';

  $vars['options']['external'] = TRUE;

  if(empty($vars['link_title'])) $vars['link_title'] = t('Start the tour!');

  drupal_add_js(drupal_get_path('module', 'joyride') . '/inc/js/joyride_start_link.js');
}