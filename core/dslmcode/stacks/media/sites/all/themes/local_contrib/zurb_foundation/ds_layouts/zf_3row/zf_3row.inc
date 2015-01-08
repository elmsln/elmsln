<?php
/**
 * @file
 * Definition of Zurb Foundation Three row Display Suite layout.
 */

function ds_zf_3row() {
  return array(
    'label' => t('Zurb Foundation Three row'),
    'regions' => array(
      'header' => t('Header'),
      'ds_content' => t('Content'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
