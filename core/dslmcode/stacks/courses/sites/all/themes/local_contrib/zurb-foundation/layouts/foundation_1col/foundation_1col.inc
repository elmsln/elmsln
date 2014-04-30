<?php

/**
 * Implements hook_panels_layouts()
 */
function zurb_foundation_foundation_1col_panels_layouts() {
  $items['foundation_1col'] = array(
    'title' => t('Foundation: 1 column row'),
    'category' => t('Foundation: 1'),
    'icon' => 'foundation_1col.png',
    'theme' => 'foundation_1col',
    //'admin css' => '../foundation_panels_admin.css',
    'regions' => array('middle' => t('Main column')),
  );
  return $items;
}

