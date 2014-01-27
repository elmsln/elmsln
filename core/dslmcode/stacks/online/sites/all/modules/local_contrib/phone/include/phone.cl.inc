<?php

/**
 * @file
 * CCK Field for Chili phone numbers.
 */

function phone_cl_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Chilean mobile phone number<br>Chili phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_cl_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^((\(\d{3}\) ?)|(\d{3}-)|(\(\d{2}\) ?)|(\d{2}-)|(\(\d{1}\) ?)|(\d{1}-))?\d{3}-(\d{3}|\d{4})$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Chili Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_cl_phone_number($phonenumber, $field) {

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
