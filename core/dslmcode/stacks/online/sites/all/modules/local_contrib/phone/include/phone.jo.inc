<?php

/**
 * This plugin is contributed by Untitled Web http://untitledstudios.com
 * @author Rashad Majali <rashad.612@gmail.com> http://drupal.org/user/319686
 * @file
 * CCK Field for Jordanian phone numbers.
 */

function phone_jo_metadata(){
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Jordanian phone number, Please check the spaces and dashes in your number.',
  );
}

/**
 * Verification for Jordanian Phone Numbers.
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_jo_phone_number($phonenumber){

  /**
  Accepts:

    Mobile numbers: (X refers to network code, it might be 7,8,9).

      +9627X1234567
      +962-7X1234567
      +962 7X1234567
      009627X1234567
      00962-7X1234567
      00962 7X1234567

      962... accepted as well

      07X1234567

    Local area numbers: (X refers to region code, i.e. Amman[6], north [2], middle [5], south[3]).
      +962X1234567
      +962-X-1234567
      +962X-1234567
      +962 X 1234567
      +962X 1234567
      +962 X1234567

      00962X1234567
      00962-X-1234567
      00962X-1234567
      00962 X 1234567
      00962X 1234567
      00962 X1234567

      962... accepted as well

      0X1234567
      0X-1234567
      0X 1234567

  Rejects:

    Generally rejects any number without leading code.
    starts with X instead of 0X

    Mobile:
      7X1234567
      7 X1234567 and similar formats
      +962 7 X1234567 and similar formats

    Local:
      X1234567
      X-1234567
      X 1234567 and similar formats

  */
  $regex = "/(^(\+962|00962|962|0)[-\s]{0,1}[7]{1}[7-9]{1}[0-9]{7}$) | (^(\+962|00962|962|0)[-\s]{0,1}[2-6][-\s]{0,1}[0-9]{7}$)/x";

  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Jordanian Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_jo_phone_number($phonenumber, $field = FALSE){


  $phonenumber = trim($phonenumber);
  $regex = "/(^(\+962|00962|962|0)[-\s]{0,1}[7]{1}[7-9]{1}[0-9]{7}$) | (^(\+962|00962|962|0)[-\s]{0,1}[2-6][-\s]{0,1}[0-9]{7}$)/x";
  preg_match($regex, $phonenumber, $matches);

  $phonenumber = preg_replace('/^(\+962|00962|962|0)|[-\s]/', '', $matches[0]);


  return '+962'.$phonenumber;

}
