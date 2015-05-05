<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_2col_stacked_panels_layouts() {
  $items['foundation_2col_stacked'] = array(
    'title' => t('Foundation: stacked 2 column row'),
    'category' => t('Foundation: 2'),
    'icon' => 'foundation_2col_stacked.png',
    'theme' => 'foundation_2col_stacked',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'top' => t('Top'),
      'left' => t('Left'),
      'right' => t('Right'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

