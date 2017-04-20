<?php

/**
 * @file
 * CCK Field for Brazilian phone numbers.
 * (based on CCK Field for French phone numbers.)
 */
define('PHONE_BR_REGEX', "/^(\+|0{2}|)?(55|0|)[\s.-]?((\(0?[1-9][0-9]\))|(0?[1-9][0-9]))[\s.-]?([1-9][0-9]{2,4})[\s.-]?([0-9]{4})$/");

function phone_br_metadata() {
  return array(
    'error' => '"%value" is not a valid Brazilian phone number<br>Brazilian phone numbers should contain only numbers and spaces and - and be like 099 9999-9999, 99 9999-9999 or 99 99999-9999 with an optional prefix of "+55".',
  );
}

/**
 * Verification for Brazilian Phone Numbers.
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_br_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);
/*
  $phonenumber  = str_replace(array(' ','-','(',')'), '', $phonenumber);
*/
  return (bool) preg_match(PHONE_BR_REGEX, $phonenumber);
}

/**
 * Formatting for Brazilian Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_br_phone_number($phonenumber, $field = FALSE) {
  $phone  = str_replace(array(' ','-','(',')'), '', $phonenumber);
  if (preg_match(PHONE_BR_REGEX, $phone, $matches) != 1) {
    return $phonenumber; // this is possible?
  }
  $formatedphone = '';
  if ($field && $field['phone_country_code']) {
    $formatedphone .= '+55 ';
  }
  $formatedphone .= '(' . $matches[3] . ')';
  $formatedphone .= ' ' . $matches[6] . '-';
  $formatedphone .= '' . $matches[7];

  return $formatedphone;
}
