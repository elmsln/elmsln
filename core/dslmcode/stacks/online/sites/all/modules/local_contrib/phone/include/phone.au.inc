<?php

/**
 * @file
 * CCK Field for Australian phone numbers.
 */

 function phone_au_metadata() {
   return array(
     'error' => '"%value" is not a valid Australian phone number<br>Australian phone numbers should contain only numbers with an optional prefix of "+61"',
   );
 }

/**
 * Verification for Australian Phone Numbers.
 * According to http://www.itu.int/itudoc/itu-t/number/a/aus/70772.html
 *    (Released 2005/10/03, retrieved 2008/04/14)
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_au_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // strip formatting chars
  $phonenumber = preg_replace('/[\-() ]/', '', $phonenumber);
  // strip optional '+61' or '0' prefixes
  $phonenumber = preg_replace('/^(\+61|0)/', '', $phonenumber);

  //$rules[] = array("Prefix","Minimum length","Maximum length");
  $rules[] = array("10", 5, 15);
  $rules[] = array("12", 5, 15);
  $rules[] = array("13", 6, 10);
  $rules[] = array("1451", 9, 9);
  $rules[] = array("1452", 9, 9);
  $rules[] = array("1453", 9, 9);
  $rules[] = array("1471", 9, 9);
  $rules[] = array("16", 5, 9);
  $rules[] = array("1800", 10, 10);
  $rules[] = array("1801", 8, 8);
  $rules[] = array("1900", 10, 10);
  $rules[] = array("1901", 10, 10);
  $rules[] = array("1902", 10, 10);
  $rules[] = array("1906", 10, 10);
  $rules[] = array("1983", 9, 9);
  $rules[] = array("2001", 4, 4);
  $rules[] = array("2002", 4, 4);
  $rules[] = array("2003", 4, 4);
  //$rules[] = array("2", 9, 9); // More specific rules follow
  $rules[] = array("240", 9, 9);
  $rules[] = array("242", 9, 9);
  $rules[] = array("243", 9, 9);
  $rules[] = array("244", 9, 9);
  $rules[] = array("245", 9, 9);
  $rules[] = array("246", 9, 9);
  $rules[] = array("247", 9, 9);
  $rules[] = array("248", 9, 9);
  $rules[] = array("249", 9, 9);
  $rules[] = array("260", 9, 9);
  $rules[] = array("261", 9, 9);
  $rules[] = array("262", 9, 9);
  $rules[] = array("263", 9, 9);
  $rules[] = array("264", 9, 9);
  $rules[] = array("265", 9, 9);
  $rules[] = array("266", 9, 9);
  $rules[] = array("267", 9, 9);
  $rules[] = array("268", 9, 9);
  $rules[] = array("269", 9, 9);
  $rules[] = array("28", 9, 9);
  $rules[] = array("29", 9, 9);
  //$rules[] = array("3", 9, 9); // More specific rules follow
  $rules[] = array("350", 9, 9);
  $rules[] = array("351", 9, 9);
  $rules[] = array("352", 9, 9);
  $rules[] = array("353", 9, 9);
  $rules[] = array("354", 9, 9);
  $rules[] = array("355", 9, 9);
  $rules[] = array("356", 9, 9);
  $rules[] = array("357", 9, 9);
  $rules[] = array("358", 9, 9);
  $rules[] = array("359", 9, 9);
  $rules[] = array("362", 9, 9);
  $rules[] = array("363", 9, 9);
  $rules[] = array("364", 9, 9);
  $rules[] = array("38", 9, 9);
  $rules[] = array("39", 9, 9);
// begin mobile phone numbers     
  $rules[] = array("400", 9, 9);
  $rules[] = array("401", 9, 9);
  $rules[] = array("402", 9, 9);
  $rules[] = array("403", 9, 9);
  $rules[] = array("404", 9, 9);
  $rules[] = array("405", 9, 9);
  $rules[] = array("406", 9, 9);
  $rules[] = array("407", 9, 9);
  $rules[] = array("408", 9, 9);
  $rules[] = array("409", 9, 9);
  $rules[] = array("410", 9, 9);
  $rules[] = array("411", 9, 9);
  $rules[] = array("412", 9, 9);
  $rules[] = array("413", 9, 9);
  $rules[] = array("414", 9, 9);
  $rules[] = array("415", 9, 9);
  $rules[] = array("416", 9, 9);
  $rules[] = array("417", 9, 9);
  $rules[] = array("418", 9, 9);
  $rules[] = array("419", 9, 9);
  $rules[] = array("420", 9, 9);
  $rules[] = array("4200", 9, 9);
  $rules[] = array("42010", 9, 9);
  $rules[] = array("421", 9, 9);
  $rules[] = array("422", 9, 9);
  $rules[] = array("423", 9, 9);
  $rules[] = array("424", 9, 9);
  $rules[] = array("425", 9, 9);
  $rules[] = array("4251", 9, 9);
  $rules[] = array("4252", 9, 9);
  $rules[] = array("4253", 9, 9);
  $rules[] = array("4256", 9, 9);
  $rules[] = array("4257", 9, 9);
  $rules[] = array("4258", 9, 9);
  $rules[] = array("427", 9, 9);
  $rules[] = array("428", 9, 9);
  $rules[] = array("429", 9, 9);
  $rules[] = array("430", 9, 9);
  $rules[] = array("4300", 9, 9);
  $rules[] = array("4301", 9, 9);
  $rules[] = array("4302", 9, 9);
  $rules[] = array("4303", 9, 9);
  $rules[] = array("4304", 9, 9);
  $rules[] = array("4305", 9, 9);
  $rules[] = array("431", 9, 9);
  $rules[] = array("432", 9, 9);
  $rules[] = array("433", 9, 9);
  $rules[] = array("434", 9, 9);
  $rules[] = array("435", 9, 9);
  $rules[] = array("4350", 9, 9);
  $rules[] = array("437", 9, 9);
  $rules[] = array("438", 9, 9);
  $rules[] = array("439", 9, 9);
  $rules[] = array("447", 9, 9);
  $rules[] = array("448", 9, 9);
  $rules[] = array("449", 9, 9);
  $rules[] = array("449", 9, 9);  
  $rules[] = array("450", 9, 9);
  $rules[] = array("451", 9, 9);
  $rules[] = array("457", 9, 9);
  $rules[] = array("458", 9, 9);
  $rules[] = array("4590", 9, 9);
  $rules[] = array("4591", 9, 9);
  $rules[] = array("4592", 9, 9);
  $rules[] = array("466", 9, 9);
  $rules[] = array("488", 9, 9);
// end mobile phone numbers   
  $rules[] = array("50", 9, 9);
  $rules[] = array("51", 9, 9);
  $rules[] = array("52", 9, 9);
  $rules[] = array("53", 9, 9);
  $rules[] = array("54", 9, 9);
  $rules[] = array("55", 9, 9);
  $rules[] = array("56", 9, 9);
  $rules[] = array("57", 9, 9);
  $rules[] = array("58", 9, 9);
  //$rules[] = array("59", 9, 9); //Not for use after 31 December 2005
  //$rules[] = array("7", 9, 9); // More specific rules follow
  $rules[] = array("73", 9, 9);
  $rules[] = array("740", 9, 9);
  $rules[] = array("741", 9, 9);
  $rules[] = array("745", 9, 9);
  $rules[] = array("746", 9, 9);
  $rules[] = array("747", 9, 9);
  $rules[] = array("749", 9, 9);
  $rules[] = array("754", 9, 9);
  $rules[] = array("755", 9, 9);
  $rules[] = array("756", 9, 9);
  //$rules[] = array("8", 9, 9); // More specific rules follow
  $rules[] = array("86", 9, 9);
  $rules[] = array("871", 9, 9);
  $rules[] = array("872", 9, 9);
  $rules[] = array("873", 9, 9);
  $rules[] = array("874", 9, 9);
  $rules[] = array("880", 9, 9);
  $rules[] = array("881", 9, 9);
  $rules[] = array("882", 9, 9);
  $rules[] = array("883", 9, 9);
  $rules[] = array("884", 9, 9);
  $rules[] = array("885", 9, 9);
  $rules[] = array("886", 9, 9);
  $rules[] = array("887", 9, 9);
  $rules[] = array("888", 9, 9);
  $rules[] = array("889", 9, 9);
  $rules[] = array("890", 9, 9);
  $rules[] = array("891", 9, 9);
  $rules[] = array("892", 9, 9);
  $rules[] = array("893", 9, 9);
  $rules[] = array("894", 9, 9);
  $rules[] = array("895", 9, 9);
  $rules[] = array("896", 9, 9);
  $rules[] = array("897", 9, 9);
  $rules[] = array("898", 9, 9);
  $rules[] = array("899", 9, 9);

  foreach ($rules as $rule) {
    if (preg_match('/^'.$rule[0].'/', $phonenumber) && strlen($phonenumber) >= $rule[1] && strlen($phonenumber) <= $rule[2]) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Formatting for Australian Phone Numbers. Based upon ITU-T E.123 (but let's not get too crazy)
 *
 * @param string $phonenumber
 * @return string Returns a string containing the phone number with some formatting.
 */
function format_au_phone_number($phonenumber, $field = FALSE) {
  $prefix = '';
  $extension = '';
  // strip old formatting chars
  $phonenumber = preg_replace('/[\-() ]/', '', $phonenumber);

  /*
   * strip and save the +61 prefix if found
   */
  if (preg_match('/^\+61/', $phonenumber, $match)) {
    $prefix = '+61 ';
    $phonenumber = str_replace('+61', '', $phonenumber);
  }

  /*
   * strip and save the extension (x9999) postfix if found
   */
  if (preg_match('/(x[0-9]+)$/', $phonenumber, $match)) {
    $extension = ' ('.$match[1].')';
    $phonenumber = preg_replace('/x[0-9]+$/', '', $phonenumber);
  }

  /*
   * geographic numbers and UPT
   * Eg. (02) 9999 9999 or +61 (2) 9999 9999
   */
  if (preg_match('/^(0{0,1}[23578])([0-9]{4})([0-9]{4})$/', $phonenumber, $match)) {
    return $prefix . '(' . $match[1] . ') ' . $match[2] . ' ' . $match[3] . $extension;
  }

  /*
   * mobile numbers
   * Eg. 0423 999 999 or +61 423 999 999
   */
  if (preg_match('/^(0{0,1}4[0-9]{2})([0-9]{3})([0-9]{3})$/', $phonenumber, $match)) {
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
   * 9 digit satellite or dialup data numbers
   * Eg. 1471 99999
   */
  if (preg_match('/^(14[0-9]{2}|1983)([0-9]{5})$/', $phonenumber, $match)) {
    return $prefix . $match[1] . ' ' . $match[2] . $extension;
  }

  /*
   * 6 digit numbers
   * Eg. 13 99 99
   */
  if (preg_match('/^([0-9]{2})([0-9]{2})([0-9]{2})$/', $phonenumber, $match)) {
    return $prefix . $match[1] . ' ' . $match[2] . ' ' . $match[3] . $extension;
  }

  // default
  return $prefix . $phonenumber . $extension;
}

