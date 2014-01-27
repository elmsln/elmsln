<?php

/**
 * @file
 * CCK Field for Dutch phone numbers.
 */

function phone_nl_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Dutch phone number!<br>Dutch phone numbers should contain only numbers and spaces and - and be like 099-9999999 with an optional prefix of "+31".',
  );
}

 /**
 * Verifies that $phonenumber is a valid ten-digit Dutch phone number with spaces and -
 *
 * Regular expression adapted from Nico Lubbers's regex at RegExLib.com
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_nl_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  /*
    Accepts:
    	06-12345678
    	06 123 456 78
    	010-1234567
    	020 123 4567
    	0221-123456
    	0221 123 456
    Rejects:
    	05-12345678
    	123-4567890
    	123 456 7890
  */

  // define regular expression
  $regex = '/
  ([0]{1}[6]{1}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){7})				# Mobile phonenumber
  |
  ([0]{1}[1-9]{1}[0-9]{2}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){5})		# Phonenumber with 4 digit area code
  |
  ([0]{1}[1-9]{1}[0-9]{1}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){6})		# Phonenumber with 3 digit area code
  /x';

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Dutch Phone Numbers into standard area-phonenumber or with extra country code +31 international format
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_nl_phone_number($phonenumber, $field) {

  $areacode = $localnumber = '';
  // Mobile number
  if (preg_match('/([0]{1}[6]{1}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){7})/', $phonenumber)) {
        preg_match('/([0]{1}[6]{1})[-\s]+([1-9]{1}[\s]*([0-9]{1}[\s]*){7})/', $phonenumber, $matches);
    }
  // Phonenumber with 4 digit area code
  if (preg_match('/([0]{1}[1-9]{1}[0-9]{2}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){5})/', $phonenumber)) {
      preg_match('/([0]{1}[1-9]{1}[0-9]{2})[-\s]+([1-9]{1}[\s]*([0-9]{1}[\s]*){5})/', $phonenumber, $matches);
  }
  // Phonenumber with 3 digit area code
  if (preg_match('/([0]{1}[1-9]{1}[0-9]{1}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){6})/', $phonenumber)) {
      preg_match('/([0]{1}[1-9]{1}[0-9]{1})[-\s]+([1-9]{1}[\s]*([0-9]{1}[\s]*){6})/', $phonenumber, $matches);
  }

  $areacode = $matches[1];
  $localnumber = preg_replace('/ /', '', $matches[2]);
  $phonenumber = $areacode. '-'. $localnumber;

  // Add Country code if needed
  if ($field['phone_country_code']) {
      $areacode = preg_replace('/^0/', '', $areacode);
      $phonenumber = '+31-'. $areacode. '-'. $localnumber;
  }

  return $phonenumber;
}
