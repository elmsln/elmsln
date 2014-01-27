<?php

/**
 * @file
 * CCK Field for Greek phone numbers.
 */

function phone_el_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Greek phone number<br>Greek phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid 
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_el_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+30)?[ ]?([0-9]{3,4}(\/|-| )?[0-9]{6,7})$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Greek Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_el_phone_number($phonenumber, $field) {

  //$phonenumber = trim($phonenumber);

   // do some formatting on the phone number
   $phonenumber = str_replace("[ -]", "", $phonenumber);

   if ($field['phone_country_code']) {
      if ($matches[1] != "+30") {
  	$phonenumber = "+30" . " " . $phonenumber;
      }
   }

   return $phonenumber;
}
