<?php
/**
 * @file
 * Definition of Zurb Foundation Four column stacked Display Suite layout.
 */

function ds_zf_4col_stacked() {
  return array(
    'label' => t('Zurb Foundation Four column stacked'),
    'regions' => array(
      'header' => t('Header'),
      'first' => t('First'),
      'second' => t('Second'),
      'third' => t('Third'),
      'fourth' => t('Fourth'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
