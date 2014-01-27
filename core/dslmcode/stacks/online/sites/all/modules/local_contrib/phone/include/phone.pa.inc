<?php

/**
 * @file
 * CCK field for Panamanian phone numbers
 */
/*
 * ((00|\+)?[0-9]{3}[\s])?  #First group    00507 or +507 (plus space)
 * ([0-9]{3,4})       #Second group three or four numbers (four for cellphones)
 * [\s|-]? space or dash
 * ([0-9]{4})  #Third group
 *
 * Accepted:
 *  00507 2603133
 *  +507 260-4343
 *  260 3133
 *  260-3133
 *
 *  Cellphones
 *  +507 6545-4345
 *  6545-4345
 *  6545 4345
 *  65454345
 */
define('PHONE_PA_REGEX', '/((00|\+)?[0-9]{3}[\s])?([0-9]{3,4})[\s|-]?([0-9]{4})/');

function phone_pa_metadata() {
   // These strings are translated using t() on output.
   return array(
     'error' => '"%value" is not a valid Panamanian phone number!<br>Panamanian phone numbers should contain only numbers, spaces and dashes be like 9999-999, 9999 999 or 9999999 with an optional prefix of "+507" or "00507".',
   );
 }

/**
 * Verifies that $phonenumber is a valid nine-digit Panamanian phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_pa_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // define regular expression
  // return true if valid, false otherwise
  return (bool) preg_match(PHONE_PA_REGEX, $phonenumber);
}

/**
 * Convert a valid Panamenian phone number into standard (+507) 260-4324 format
 *
 * @param $phonenumber must be a valid nine-digit number (with optional international prefix)
 *
 */
function format_pa_phone_number($phonenumber, $field = FALSE) {
  // get digits of phone number
  preg_match(PHONE_PA_REGEX, $phonenumber, $matches);
  if (preg_match(PHONE_PA_REGEX, $phonenumber, $matches) != 1) {
    return $phonenumber; // not a Panamanian phone number
  }
  $phonenumber = $matches[3] . '-' . $matches[4];
  if (trim($matches[1]) != '') {
    $phonenumber = '+' . substr($matches[1], -4) . $phonenumber;
  }
  elseif ($field && isset($field['phone_country_code'])) {
    $phonenumber = '+507 ' . $phonenumber;
  }

  return $phonenumber;
}
