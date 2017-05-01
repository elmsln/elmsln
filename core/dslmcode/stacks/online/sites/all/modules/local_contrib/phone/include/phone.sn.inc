<?php

/**
 * @file
 * CCK Field for Senegalese phone numbers.
 */

define('PHONE_SN_REGEX', '/((\+221|00221)?)((7[7608][0-9]{7}$)|(3[03][98][0-9]{6}$))/');


function phone_sn_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Senegalese phone number',
  );
}

/**
 * Verification for Senegalese Phone Numbers.
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_sn_phone_number($phonenumber) {

  $phonenumber  = str_replace(array(' ', '-', '(', ')') , '', $phonenumber);
  return (bool) preg_match(PHONE_SN_REGEX, $phonenumber);
}

/**
 * Formatting for Senegalese Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns the phone number as string.
 */
function format_sn_phone_number($phonenumber, $field = FALSE) {
  $phone  = str_replace(array(' ', '-', '(', ')'), '', $phonenumber);
  if (preg_match(PHONE_SN_REGEX, $phone, $matches) != 1) {
    return $phonenumber; // not a french phone number
  }
  //
  if (in_array($matches[0], array('+221', '00221'))) {
    return $matches[2];
  }
  else {
    return $matches[0];
  }
}

