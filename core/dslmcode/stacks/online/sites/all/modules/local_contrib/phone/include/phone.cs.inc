<?php

/**
 * @file
 * CCK Field for Czech phone numbers.
 */

function phone_cs_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Czech phone number!<br>Czech phone numbers should contain only numbers and spaces be like 999 999 999 with an optional prefix of "+420" or "00420".',
  );
}

/**
 * Verifies that $phonenumber is a valid nine-digit Czech phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_cs_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // define regular expression
  $regex = '/^((?:\+|00)420)? ?(\d{3}) ?(\d{3}) ?(\d{3})$/';

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Convert a valid Czech phone number into standard (+420) 999 999 999 format
 *
 * @param $phonenumber must be a valid nine-digit number (with optional international prefix)
 *
 */
function format_cs_phone_number($phonenumber, $field) {

  // define regular expression
  $regex = '/^((?:\+|00)420)? ?(\d{3}) ?(\d{3}) ?(\d{3})$/';

  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);

  if ($field['phone_country_code']) {
    	$phonenumber = '+420' . ' ' . $matches[2] .' '. $matches[3] .' '. $matches[4];
   }
  else {
  	$phonenumber = $matches[2] .' '. $matches[3] .' '. $matches[4];
  }

  return $phonenumber;
}
