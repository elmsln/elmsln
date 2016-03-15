<?php

/**
 * @file
 * colorbox.views.inc
 */

/**
 * Implementation of hook_views_data()
 */
function colorbox_views_data() {

  $data['colorbox']['table']['group'] = t('Colorbox');

  $data['colorbox']['table']['join'] = array(
    '#global' => array(),
  );

  $data['colorbox']['colorbox'] = array(
    'title' => t('Colorbox trigger'),
    'help' => t('Provide custom text or link.'),
    'field' => array(
      'handler' => 'colorbox_handler_field_colorbox',
    ),
  );

  return $data;
}
