<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_4col_panels_layouts() {
  $items['foundation_4col'] = array(
    'title' => t('Foundation: 4 column row'),
    'category' => t('Foundation: 4'),
    'icon' => 'foundation_4col.png',
    'theme' => 'foundation_4col',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'left' => t('Left'),
      'middle_left' => t('Left Middle'),
      'middle_right' => t('Right Middle'),
      'right' => t('Right')
    ),
  );
  return $items;
}

