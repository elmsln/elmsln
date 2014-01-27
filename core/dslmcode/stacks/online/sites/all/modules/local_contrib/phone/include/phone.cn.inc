<?php

/**
 * @file
 * CCK Field for China phone numbers.
 */

function phone_cn_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Chinese phone number!<br>Chinese phone numbers should ...',
  );
}

/**
 * Verifies that $phonenumber is a valid Chinese phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_cn_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // define regular expression
  $regex = '/^(\+86|86)?( |-)?([0-9]{11}|([0-9]{3,4}(\-|\.| )[0-9]{3,8})|[0-9]{2}( |\-)[0-9]{4}[ ][0-9]{4}|[0-9]{2}\.[0-9]{2}\.[0-9]{2}\.[0-9]{2}\.[0-9]{2})$/';

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Convert a valid Chinese phone number into standard ... format
 *
 * @param $phonenumber must be a valid number (with optional international prefix)
 *
 */
function format_cn_phone_number($phonenumber, $field) {

  return $phonenumber;
}
