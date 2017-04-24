<?php

/**
 * @file
 * CCK Field for South African phone numbers.
 */

function phone_za_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid South African phone number!<br>South African phone numbers should only contain numbers with an optional prefix of "+27".',
  );
}

/**
 * Verifies that $phonenumber is a valid South African phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_za_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // define regular expression
  $regex = '/^((?:\+27|27)|0)[ ]*((\d{2})(-| )?(\d{3})(-| )?(\d{4})|(\d{2})( |-)(\d{7}))$/';
  
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Convert a valid South African phone number into standard ... format
 *
 * @param $phonenumber must be a valid  ... digit number (with optional international prefix)
 *
 */
function format_za_phone_number($phonenumber, $field) {

  // define regular expression
  $regex = '/^((?:\+27|27)|0)[ ]*((\d{2})(-| )?(\d{3})(-| )?(\d{4})|(\d{2})( |-)(\d{7}))$/';

  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);
  
/*
  drupal_set_message('$matches[1] = ' . $matches[1], 'error');
  drupal_set_message('$matches[2] = ' . $matches[2], 'error');
  drupal_set_message('$matches[3] = ' . $matches[3], 'error');
  drupal_set_message('$matches[4] = ' . $matches[4], 'error');
  drupal_set_message('$matches[5] = ' . $matches[5], 'error');
  drupal_set_message('$matches[6] = ' . $matches[6], 'error');
  drupal_set_message('$matches[7] = ' . $matches[7], 'error');
  drupal_set_message('$matches[8] = ' . $matches[8], 'error');
*/

  if ($field['phone_country_code']) {
    	$phonenumber = '+27' . ' ' . $matches[3] .'-'. $matches[5] .'-'. $matches[7];
  }
  else {
  	$phonenumber = '0' . $matches[3] .'-'. $matches[5] .'-'. $matches[7];
  }

  return $phonenumber;
}
