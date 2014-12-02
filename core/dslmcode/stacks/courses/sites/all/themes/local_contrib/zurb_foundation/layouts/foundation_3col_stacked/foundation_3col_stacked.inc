<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_3col_stacked_panels_layouts() {
  $items['foundation_3col_stacked'] = array(
    'title' => t('Foundation: stacked 3 column row'),
    'category' => t('Foundation: 3'),
    'icon' => 'foundation_3col_stacked.png',
    'theme' => 'foundation_3col_stacked',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'top' => t('Top'),
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

