<?php
//drived from au module and manipulated by Moshe Beeri, email: moshe.beeri (at-shetrudel) google mail

/**
* @file
* CCK Field for Isreali phone numbers.
*/

function phone_il_metadata() {
  return array(
    'error' => '"%value" is not a valid Israeli phone number',
  );
}

/**
* Verification for Israel Phone Numbers.
*
* @param string $phonenumber
* @return boolean Returns boolean FALSE if the phone number is not valid.
*/
function valid_il_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // strip formatting chars
  $phonenumber = preg_replace('/[\-() ]/', '', $phonenumber);
  // strip optional '+972' or '0' prefixes
  $phonenumber = preg_replace('/^(\+972)/', '', $phonenumber);

  //$rules[] = array("Prefix","Minimum length","Maximum length");

//http://he.wikipedia.org/wiki/%D7%A7%D7%99%D7%93%D7%95%D7%9E%D7%AA_%D7%98%D7%9C%D7%A4%D7%95%D7%9F

  $rules[] = array("02", 7, 10);
  $rules[] = array("03", 7, 10);
  $rules[] = array("04", 7, 10);
  $rules[] = array("08", 7, 10);
  $rules[] = array("09", 7, 10);
  $rules[] = array("072", 7, 10);
  $rules[] = array("073", 7, 10);
  $rules[] = array("074", 7, 10);
  $rules[] = array("076", 7, 10);
  $rules[] = array("077", 7, 10);
  $rules[] = array("078", 7, 10);
  $rules[] = array("050", 7, 10);
  $rules[] = array("052", 7, 10);
  $rules[] = array("054", 7, 10);
  $rules[] = array("057", 7, 10);
  $rules[] = array("1800", 6, 10);
  $rules[] = array("1801", 6, 10);
  $rules[] = array("1700", 6, 10);

  foreach ($rules as $rule) {
    if (preg_match('/^'.$rule[0].'/', $phonenumber) && strlen($phonenumber) >= $rule[1] && strlen($phonenumber) <= $rule[2]) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
* Formatting for Israeli Phone Numbers. Based upon ITU-T E.123 (but let's not get too crazy)
*
* @param string $phonenumber
* @return string Returns a string containing the phone number with some formatting.
*/
function format_il_phone_number($phonenumber) {
  $prefix = '';
  $extension = '';
  // strip old formatting chars
  $phonenumber = preg_replace('/[\-() ]/', '', $phonenumber);

  /*
  * strip and save the +9726 prefix if found
  */
  if (preg_match('/^\+972/', $phonenumber, $match)) {
    $prefix = '+972 ';
    $phonenumber = str_replace('+972', '', $phonenumber);
  }


  /*
  * 9 phones digit numbers
  * Eg. 03 9999 999
  */
  if (preg_match('/^([0-9]{2})([0-9]{4})([0-9]{3})$/', $phonenumber, $match)) {
    return $prefix . $match[1] . ' ' . $match[2] . ' ' . $match[3] . $extension;
  }

  /*
  * 10 digit numbers
  * Eg. 1800 999 999
  */
  if (preg_match('/^([0-9]{4})([0-9]{3})([0-9]{3})$/', $phonenumber, $match)) {
    return $prefix . $match[1] . ' ' . $match[2] . ' ' . $match[3] . $extension;
  }
  
  /*
  * cell phone
  * Eg. 054 9999 999
  */
  if (preg_match('/^([0-9]{3})([0-9]{4})([0-9]{3})$/', $phonenumber, $match)) {
    return $prefix . $match[1] . ' ' . $match[2] . ' ' . $match[3] . $extension;
  }   

  // default
  return $prefix . $phonenumber . $extension;
}
