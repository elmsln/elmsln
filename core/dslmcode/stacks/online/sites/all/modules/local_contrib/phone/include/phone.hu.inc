<?php

/**
 * @file
 * CCK Field for Hungarian phone numbers.
 */

define('PHONE_HU_REGEX', "/^(\+36|06|)[\s.-]?([0-9]{1,2})[\s.-]?([0-9]{2,3})[\s.-]?([0-9]{2,4})$/");

function phone_hu_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Hungarian phone number!<br>Hungarian phone numbers should contain only numbers and spaces be like 70 999 9999 with an optional prefix of "+36" or "06".',
  );
}

/**
 * Verifies that $phonenumber is a valid nine-digit Hungarian phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_hu_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // return true if valid, false otherwise
  return (bool) preg_match(PHONE_HU_REGEX, $phonenumber);
}

/**
 * Convert a valid Hungarian phone number into standard (+36) ..... format
 *
 * @param $phonenumber must be a valid nine-digit number (with optional international prefix)
 *
 */
function format_hu_phone_number($phonenumber, $field = FALSE) {
  $phonenumber = trim($phonenumber);
  // get digits of phone number
  preg_match(PHONE_HU_REGEX, $phonenumber, $matches);

  $formatedphone = '';
  if ($field && $field['phone_country_code']) {
    $formatedphone .= '+36 ';
  }

  // construct ten-digit phone number
  $formatedphone .=  $matches[2] . ' ' . $matches[3] . ' ' . $matches[4];

  return $formatedphone;
}

