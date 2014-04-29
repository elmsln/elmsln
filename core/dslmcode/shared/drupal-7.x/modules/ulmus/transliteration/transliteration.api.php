<?php

/**
 * @file
 * Documents Transliteration's hooks for api reference.
 */

/**
 * Alters a file name before transliteration and sanitization.
 *
 * @param &$filename
 *   The file name before being parsed by transliteration.
 *
 * @param $source_langcode
 *   Optional ISO 639 language code that denotes the language of the input.
 *
 * @see transliteration_clean_filename()
 */
function hook_transliteration_clean_filename_prepare_alter(&$filename, $source_langcode) {
  $filename = drupal_strtolower($filename);
  $filename = str_ireplace(array('&amp; ', '& '), 'and ', $filename);
}
