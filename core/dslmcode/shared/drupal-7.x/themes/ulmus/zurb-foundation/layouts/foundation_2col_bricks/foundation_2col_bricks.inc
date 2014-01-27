<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_2col_bricks_panels_layouts() {
  $items['foundation_2col_bricks'] = array(
    'title' => t('Foundation: 2 column bricks'),
    'category' => t('Foundation: 2'),
    'icon' => 'foundation_2col_bricks.png',
    'theme' => 'foundation_2col_bricks',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'top' => t('Top'),
      'above_left' => t('Above Left'),
      'above_right' => t('Above Right'),
      'middle' => t('Middle'),
      'below_left' => t('Below Left'),
      'below_right' => t('Below Right'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

