<?php

/**
 * @file
 * CCK Field for British phone numbers.
 */

function phone_gb_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid British (UK) phone number<br>British Phone numbers should .... ',
  );
}

/**
 * Verifies that $phonenumber is a valid eleven-digit United Kingdom phone number
 *
 * Regular expression adapted from Amos Hurd's regex at RegExLib.com
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */

function valid_gb_phone_number($phonenumber) {

  /*
    Accepts:
        +441970123456
        +44(0)1970123456
        +44 1970 123 456
        +44 (0)1970 123 456
        (01970) 123456 #0001
    Rejects:
        (+441970)123456
        +44(1970)123456
        +44 01970 123 456
        (0197) 0123456 #01
  */
  $regex = "/
    (
        (^\+44\s?(\(0\))?\d{4}|^\(?0\d{4}\)?){1}\s?\d{3}\s?\d{3}  # 4 digit area code with optional +44 internationalisation or not, optional spaces and brackets.
        |
        (^\+44\s?(\(0\))?\d{3}|^\(?0\d{3}\)?){1}\s?\d{3}\s?\d{4}  # 3 digit area code with optional +44 internationalisation or not, optional spaces and brackets.
        |
        (^\+44\s?(\(0\))?\d{2}|^\(?0\d{2}\)?){1}\s?\d{4}\s?\d{4}  # 2 digit area code with optional +44 internationalisation or not, optional spaces and brackets.
        |
        (^\+44\s?(\(0\))?\d{1}|^\(?0\d{1}\)?){1}\s?\d{5}\s?\d{5}  # 1 digit area code with optional +44 internationalisation or not, optional spaces and brackets.        
    )
    (\s?\#\d*)?   # optional extension number shown with a hash divider
  /x";

  if (!preg_match($regex, $phonenumber)) {
  	return FALSE;
  }
  else
  {
	return TRUE;
  }
}

/**
 * Convert a valid United Kingdom phone number into standard +44 (0)1970 123 456 #001 international format
 *
 * @param $phonenumber must be a valid eleven-digit number (with optional extension)
 *
 */
function format_gb_phone_number($phonenumber, $field = FALSE) {

    $area = $number = $extension = '';

    //If we already have the formatting we want just return
    if (preg_match(
    "/
        (
            \+44\s\(0\)\d{4}\s\d{3}\s\d{3}  # 4 digit area code
            |
            \+44\s\(0\)\d{3}\s\d{3}\s\d{4}  # 3 digit area code
            |
            \+44\s\(0\)\d{2}\s\d{4}\s\d{4}  # 2 digit area code
        )
        (\s\#\d*)?
    /",$phonenumber)) {
        return $phonenumber;
    }
    else {
        //Simplify to 10 digit number and clean up ready for international reformat.
        $phonenumber = preg_replace("/^(\+44)?\s?(\(?0\)?)?/","",$phonenumber);
        $phonenumber = preg_replace("/\(/","",$phonenumber);
        $phonenumber = preg_replace("/\(0/","",$phonenumber);
        $phonenumber = preg_replace("/\)/","",$phonenumber);

        //If there are some spaces in the number assume some level of preformatting
        if(preg_match("/ /",$phonenumber)) {
            $regex = "/
                # 4 digit area code.
                (
                    (\d{4}) # capture 4 digit area code
                    \s+     # ignore required separator to make a distinction with other area codes
                    (\d{3}) # capture first set of numbers in the local number
                    \s*     # ignore optional separator
                    (\d{3}) # capture second set of numbers in the local number
                |
                # 3 digit area code.
                    (\d{3}) # capture 3 digit area code
                    \s+     # ignore required seperator
                    (\d{3}) # capture first set of numbers in the local number
                    \s*     # ignore possible boundary
                    (\d{4}) # capture second set of numbers in the local number
                |
                # 2 digit area code.
                    (\d{2}) # capture 2 digit area code
                    \s+     # ignore required boundary to make a distinction with other area codes
                    (\d{4}) # capture first set of numbers in the local number
                    \s*     # ignore possible boundary
                    (\d{4}) # capture second set of numbers in the local number
                )
                # capture the optional extension number
                (\s*\#)?
                (\d{4}|\d{3})?
            /x";
            preg_match($regex, $phonenumber, $matches);
            $area = $matches[2].$matches[5].$matches[8];
            $number = $matches[3].$matches[6].$matches[9].' '.$matches[4].$matches[7].$matches[10];
            $extension = $matches[12];
        }
        //If there are no spaces in the number assume 4 digit area code.
        else {
            preg_match("/(\d{4})(\d{3})(\d{3})\#?(\d*)?/",$phonenumber, $matches);
            $area = $matches[1];
            $number = $matches[2].' '.$matches[3];
            $extension = $matches[4];
        }
	
      if ($field['phone_country_code']) {	
      	$phonenumber = '+44 (0)'.$area.' '.$number;
      }
      else {
      	$phonenumber = '0'.$area.' '.$number;
      }
      $phonenumber .= (empty($extension))?'':" #$extension";
  }
  return $phonenumber;
}
