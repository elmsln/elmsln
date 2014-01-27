<?php

/**
 * @file
 * CCK Field for Costa Rican phone numbers.
 */

 function phone_cr_metadata() {
   // These strings are translated using t() on output.
   return array(
     'error' => '"%value" is not a valid Costa Rican phone number!<br>Costa Rican phone numbers should contain only numbers and spaces be like 99 99 99 99 with an optional prefix of "+506" or "00506".',
   );
 }

/**
 * Verifies that $phonenumber is a valid eight-digit Costa Rican phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_cr_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // define regular expression
    $regex = "/(00)?[\s|-]?((\+)?[\s|-]?[0-9]{3})?[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?/";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Convert a valid Costa Rican phone number into standard (+506) 5555 55 55 format
 *
 * @param $phonenumber must be a valid eight-digit number (with optional international prefix)
 *
 */

  /*
    Accepts:
        +506 88798857
 		+506 88-79-88-57
        00506 88798857
        00506 88-79-88-57
    Rejects:
        +506 8 8798857
 		+506 8 8-79-88-57
        00506 8 8798857
        00506 8 8-79-88-57  */

function format_cr_phone_number($phonenumber, $field = FALSE) {

  // define regular expression
    $regex = "/(00)?[\s|-]?((\+)?[\s|-]?[0-9]{3})?[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?/";

  // get digits of phone number
  //dprint_r($matches);
  preg_match($regex, $phonenumber, $matches);

  // construct eight-digit phone number

  //dprint_r($matches);
  $phonenumber = $matches[4] . '-' . $matches[5] . '-' . $matches[6] . '-' . $matches[7];

  if($matches[2]){
  	if($matches[1])
  		$phonenumber =  "+" . $matches[2] . " " . $phonenumber;
  	else
  		$phonenumber =  $matches[2] . " " . $phonenumber;
  }

  return $phonenumber;
}
