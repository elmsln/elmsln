<?php
/**
 * @file
 * Definition of Zurb Foundation Three column Display Suite layout.
 */

function ds_zf_3col() {
  return array(
    'label' => t('Zurb Foundation Three column'),
    'regions' => array(
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right'),
    ),
    'image' => TRUE,
  );
}
