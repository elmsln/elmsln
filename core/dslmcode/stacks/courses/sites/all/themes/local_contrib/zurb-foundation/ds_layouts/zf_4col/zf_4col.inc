<?php
/**
 * @file
 * Definition of Zurb Foundation Four column Display Suite layout.
 */

function ds_zf_4col() {
  return array(
    'label' => t('Zurb Foundation Four column'),
    'regions' => array(
      'first' => t('First'),
      'second' => t('Second'),
      'third' => t('Third'),
      'fourth' => t('Fourth'),
    ),
    'image' => TRUE,
  );
}
