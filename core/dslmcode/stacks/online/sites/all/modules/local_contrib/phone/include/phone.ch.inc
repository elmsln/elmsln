<?php

/**
 * @file
 * CCK Field for Switzerland phone numbers.
 */

define('PHONE_CH_REGEX', "%(\+41|0|0041)([2-9]\d{8})$%");

function phone_ch_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Swiss phone number<br>Swiss phone numbers should only contain numbers and spaces and be like 099 999 99 99',
  );
}

/**
 * Verification for private/standr switzerland Phone Numbers (E.164/2002).
 * According to http://en.wikipedia.org/wiki/Telephone_numbers_in_Switzerland#After_2002
 *    (Released 2002)
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_ch_phone_number($phonenumber) {
  $phonenumber = str_replace(array(' ','-','.','/','(',')'), '', $phonenumber);
  $match =array();
  $result = (bool) preg_match(PHONE_CH_REGEX, $phonenumber, $match);
  return $result;
}

/**
 * Formatting for Switzerland Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_ch_phone_number($phonenumber, $field = FALSE) {
  $phone  = str_replace(array(' ','-','.','/','(',')'), '', $phonenumber);
  $matches =array();
  if (preg_match(PHONE_CH_REGEX, $phone, $matches) != 1) {
    return $phonenumber; // not a switzerland phone number
  }

  $value =($field && $field['phone_country_code'] ? '+41 (0)' : '0') .
  					substr($matches[2],0,2).
  				  ' '.substr($matches[2],2,3).
  					' '.substr($matches[2],5,2).
  					' '.substr($matches[2],7);
  return $value;
}
