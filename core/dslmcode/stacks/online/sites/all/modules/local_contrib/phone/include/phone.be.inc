<?php

/**
 * @file
 * CCK Field for Belgian phone numbers.
 */

function phone_be_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Belgian phone number<br>Belgian phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_be_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+32|0)[1-9]\d{7,8}$/i";


  $phonenumber  = str_replace(array(' ','-','(',')'), '', $phonenumber);
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Belgian Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_be_phone_number($phonenumber, $field) {

  $phonenumber = trim($phonenumber);

   if ($field['phone_country_code']) {
      if ($matches[1] != "+32") {
  	$phonenumber = "+32" . " " . $phonenumber;
      }
   }
   
   return $phonenumber;
}
