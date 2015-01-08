<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_3col_panels_layouts() {
  $items['foundation_3col'] = array(
    'title' => t('Foundation: 3 column row'),
    'category' => t('Foundation: 3'),
    'icon' => 'foundation_3col.png',
    'theme' => 'foundation_3col',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right')
    ),
  );
  return $items;
}

