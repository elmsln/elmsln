<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_6row_combo_panels_layouts() {
  $items['foundation_6row_combo'] = array(
    'title' => t('Foundation: 6 row combo'),
    'category' => t('Foundation: 6'),
    'icon' => 'foundation_6row_combo.png',
    'theme' => 'foundation_6row_combo',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array(
      'top' => t('Top'),
      'top_first' => t('Top First'),
      'top_second' => t('Top Second'),
      'top_third' => t('Top Third'),
      'top_fourth' => t('Top Fourth'),
      'middle_small' => t('Middle Small'),
      'middle_large' => t('Middle Large'),
      'middle_first' => t('Middle First'),
      'middle_second' => t('Middle Second'),
      'bottom_first' => t('Bottom First'),
      'bottom_second' => t('Bottom Second'),
      'bottom_third' => t('Bottom Third'),
      'bottom_fourth' => t('Bottom Fourth'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

