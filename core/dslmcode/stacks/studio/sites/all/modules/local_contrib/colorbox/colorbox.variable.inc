<?php

/**
 * @file
 * Colorbox translatable variables.
 */

/**
 * Implements hook_variable_info().
 */
function colorbox_variable_info($options) {
  $variable['colorbox_text_start'] = array(
    'title' => t('Colorbox Start slideshow'),
    'description' => t('Text for the slideshow start button.'),
    'type' => 'string',
  );
  $variable['colorbox_text_stop'] = array(
    'title' => t('Colorbox Stop slideshow'),
    'description' => t('Text for the slideshow stop button.'),
    'type' => 'string',
  );
  $variable['colorbox_text_current'] = array(
    'title' => t('Colorbox current text'),
    'description' => t('Text for the content group / gallery count'),
    'type' => 'string',
  );
  $variable['colorbox_text_previous'] = array(
    'title' => t('Colorbox Previous'),
    'description' => t('Text for the previous button in a shared relation group.'),
    'type' => 'string',
  );
  $variable['colorbox_text_next'] = array(
    'title' => t('Colorbox Next'),
    'description' => t('Text for the next button in a shared relation group.'),
    'type' => 'string',
  );
  $variable['colorbox_text_close'] = array(
    'title' => t('Colorbox Close'),
    'description' => t('Text for the close button.'),
    'type' => 'string',
  );

  return $variable;
}
