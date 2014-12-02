<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_2col_panels_layouts() {
  $items['foundation_2col'] = array(
    'title' => t('Foundation: 2 column row'),
    'category' => t('Foundation: 2'),
    'icon' => 'foundation_2col.png',
    'theme' => 'foundation_2col',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right')
    ),
  );
  return $items;
}

