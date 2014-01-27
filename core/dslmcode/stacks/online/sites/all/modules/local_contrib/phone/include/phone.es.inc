<?php

/**
 * @file
 * CCK Field for Spanish phone numbers.
 */

function phone_es_metadata() {
   // These strings are translated using t() on output.
   return array(
     'error' => '"%value" is not a valid Spanish phone number<br>Spanish phone numbers should only contains numbers and spaces and be like 999 999 999',
   );
 }


/**
 * Verifies that $phonenumber is a valid nine-digit Spanish phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_es_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // define regular expression
  //$regex = "/
  //  \D*           # optional separator
  //  [69]\d{2}     # first group of numbers
  //  \D*           # optional separator
  //  \d{3}         # second group
  //  \D*           # optional separator
  //  \d{3}         # third group
  //  \D*           # ignore trailing non-digits
  //  $/x";
    
    $regex = '/^[0-9]{2,3}-? ?[0-9]{6,7}$/';

    
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Convert a valid Spanish phone number into standard (+34) 916 555 777 format
 *
 * @param $phonenumber must be a valid nine-digit number (with optional international prefix)
 *
 */
function format_es_phone_number($phonenumber, $field = FALSE) {

  // define regular expression
  //$regex = "/
  //  \D*           # optional separator
  //  ([69]\d{2})   # first group of numbers
  //  \D*           # optional separator
  //  (\d{3})       # second group
  //  \D*           # optional separator
  //  (\d{3})       # third group
  //  \D*           # ignore trailing non-digits
  //  $/x";

  $regex = '/^[0-9]{2,3}-? ?[0-9]{6,7}$/';
  
  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);

  // construct ten-digit phone number
  $phonenumber = $matches[1] . ' ' . $matches[2] . ' ' . $matches[3];

  return $phonenumber;
}

