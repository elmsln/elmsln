<?php
/**
 * @file
 * Definition of Zurb Foundation Three column stacked Display Suite layout.
 */

function ds_zf_3col_stacked() {
  return array(
    'label' => t('Zurb Foundation Three column stacked'),
    'regions' => array(
      'header' => t('Header'),
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
