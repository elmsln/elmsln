<?php

/**
 * @file
 * CCK Field for Poland phone numbers.
 */

function phone_pl_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Polish mobile phone number<br>Polish phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_pl_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+48\s+)?\d{3}(\s*|\-)\d{3}(\s*|\-)\d{3}$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Polish Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_pl_phone_number($phonenumber, $field) {

  //$phonenumber = trim($phonenumber);

   // do some formatting on the phone number

/* ==> to be done ==> add the country code 
   if ($field['phone_country_code']) {
      if ($matches[1] != "+39") {
  	$phonenumber = "+39" . " " . $phonenumber;
      }
   }
*/ 
   return $phonenumber;
}
