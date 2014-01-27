<?php


/**
 * @file
 * CCK Field for New Zealand phone numbers.
 */

function phone_nz_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid New Zealand phone number!<br>New Zealand phone numbers should contain only numbers, spaces, brackets and "-". They should look like 04 123 4567 or can optionally omit the leading 0 and have a prefix of "+64".',
  );
}

/**
 * Verification for New Zealand Phone Numbers.
 * As supplied by http://www.itu.int/itudoc/itu-t/number/n/nzl/76195_ww9.doc, April 2009
 *
 * @param string $phonenumber
 * @return boolean returns boolean FALSE if the phone number is not valid.
 */
function valid_nz_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // strip formatting chars
  $phonenumber = preg_replace('/[\-() ]/', '', $phonenumber);
  // strip optional '+64' or '0' prefixes
  $phonenumber = preg_replace('/^(\+64|0)/', '', $phonenumber);

  //$rules[] = array("Prefix","Minimum length","Maximum length");

  // special purpose service codes and numbers
  /*// Enable if required
  $rules[] = array('10', 3, 3);
  $rules[] = array('12', 6, 7); // NZ Direct Service
  $rules[] = array('60', 4, 4); // Directory Assistance (operator only) - Maybe shouldn't be in here
  $rules[] = array('83', 5, 8); // "Enhanced Voice Services"
  $rules[] = array('86', 8, 8); // "Enhanced Paging Services"
  $rules[] = array('87', 4, 8); // "PSTN access to data services"
  */

  // Mobile
  $rules[] = array('20', 9, 9); // mobile radio / Orcon mobile

  $rules[] = array('22', 8, 10); // NZ Communications (actual lengths subject to change)

  $rules[] = array('210', 8, 10); // Vodafone
  $rules[] = array('211', 8, 9);  // Vodafone
  $rules[] = array('212', 8, 9);  // Vodafone
  $rules[] = array('213', 8, 9);  // Vodafone
  $rules[] = array('214', 8, 9);  // Vodafone
  $rules[] = array('215', 8, 9);  // Vodafone
  $rules[] = array('216', 8, 9);  // Vodafone
  $rules[] = array('217', 8, 9);  // Vodafone
  $rules[] = array('218', 8, 9);  // Vodafone
  $rules[] = array('219', 8, 9);  // Vodafone

  $rules[] = array('24', 8, 8); // Scott Base
  //$rules[] = array('25', 8, 9); // Old Telecom 025, now unused
  $rules[] = array('26', 8, 9); // Telecom Paging
  $rules[] = array('27', 9, 9); // Telecom 027 mobile
  $rules[] = array('29', 8, 9); // TelstraClear mobile

  // South Island regional
  $rules[] = array('32', 8, 8);
  $rules[] = array('33', 8, 8);
  $rules[] = array('34', 8, 8);
  $rules[] = array('35', 8, 8);
  $rules[] = array('36', 8, 8);
  $rules[] = array('37', 8, 8);
  $rules[] = array('39', 8, 8);

  // Wellington regional
  $rules[] = array('42', 8, 8);
  $rules[] = array('43', 8, 8);
  $rules[] = array('44', 8, 8);
  $rules[] = array('45', 8, 8);
  $rules[] = array('46', 8, 8);
  $rules[] = array('48', 8, 8);
  $rules[] = array('49', 8, 8);

  // Manawatu, Taranaki, Hawkes Bay, Gisborne, Wairarapa, Otaki regional
  $rules[] = array('62', 8, 8);
  $rules[] = array('63', 8, 8);
  $rules[] = array('67', 8, 8);
  $rules[] = array('68', 8, 8);
  $rules[] = array('69', 8, 8);

  // Waikato, BOP, Taumarunui regional
  $rules[] = array('73', 8, 8);
  $rules[] = array('75', 8, 8);
  $rules[] = array('62', 8, 8);
  $rules[] = array('78', 8, 8);
  $rules[] = array('79', 8, 8);

  // Freecall
  $rules[] = array('80', 8, 10);

  // Pay-call
  $rules[] = array('90', 8, 10);

  // Auckland + Northland regional
  $rules[] = array('92', 8, 8);
  $rules[] = array('93', 8, 8);
  $rules[] = array('94', 8, 8);
  $rules[] = array('95', 8, 8);
  $rules[] = array('96', 8, 8);
  $rules[] = array('98', 8, 8);
  $rules[] = array('99', 8, 8);

  foreach ($rules as $rule) {
    if (preg_match('/^'.$rule[0].'/', $phonenumber) && strlen($phonenumber) >= $rule[1] && strlen($phonenumber) <= $rule[2]) {
      return true;
    }
  }
  return false;
}

/**
 * Formatting for New Zealand Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containing the phone number with some formatting.
 */
function format_nz_phone_number($phonenumber, $field) {
  $prefix = '';
  $extension = '';
  // strip old formatting chars
  $phonenumber = preg_replace('/[\-() ]/', '', $phonenumber);

  /*
   * strip and save the +64 prefix if found
   */
  if (preg_match('/^\+64/', $phonenumber, $match)) {
    $prefix = '+64';
    $phonenumber = str_replace('+64', '', $phonenumber);
  }
  else {
    $prefix = '0';

    /*
     * Remove a leading 0, if present
     */
    if (preg_match('/^0/', $phonenumber, $match)) {
      $phonenumber = substr($phonenumber, 1);
    }
  }

  /*
   * strip and save the extension (x9999) postfix if found
   */
  if (preg_match('/(x[0-9]+)$/', $phonenumber, $match)) {
    $extension = ' '.$match[1];
    $phonenumber = preg_replace('/x[0-9]+$/', '', $phonenumber);
  }

  /*
   * geographic numbers
   * Eg. (04) 123 4578
   */
  if (preg_match('/^([34679])([0-9]{3})([0-9]{4})$/', $phonenumber, $match)) {
    return _format_nz_phone_number_prefix($prefix, $match[1]) . $match[2] . ' ' . $match[3] . $extension;
  }

  /*
   * 8 digit mobile numbers
   * Eg. 021 123 123
   */
  if (preg_match('/^(2[12679])([0-9]{3})([0-9]{3})$/', $phonenumber, $match)) {
    return _format_nz_phone_number_prefix($prefix, $match[1]) . $match[2] . ' ' . $match[3] . $extension;
  }

  /*
   * 9 digit mobile numbers
   * Eg. 021 123 4567
   */
  if (preg_match('/^(2[12679])([0-9]{3})([0-9]{4})$/', $phonenumber, $match)) {
    return _format_nz_phone_number_prefix($prefix, $match[1]) . $match[2] . ' ' . $match[3] . $extension;
  }

  /*
   * 10 digit mobile numbers
   * Eg. 021 1234 1234
   */
  if (preg_match('/^(2[12679])([0-9]{4})([0-9]{4})$/', $phonenumber, $match)) {
    return _format_nz_phone_number_prefix($prefix, $match[1]) . $match[2] . ' ' . $match[3] . $extension;
  }

  /**
   * 0800/0900 numbers (a bit random)
  */
  if (preg_match('/^(900|800)(\d+)$/', $phonenumber, $match)) {
    // How we format depends on the length
    $formatted = null;
    switch(strlen($match[2])) {
      case 5: $formatted = preg_replace('/^(\d{2})(\d{3})$/', '$1$2', $match[2]); break;
      case 6: $formatted = preg_replace('/^(\d{3})(\d{3})$/', '$1$2', $match[2]); break;
      case 7: $formatted = preg_replace('/^(\d{3})(\d{4})$/', '$1 $2', $match[2]); break;
    }
    return _format_nz_phone_number_prefix($prefix, $match[1]).$formatted;
  }

  // default (probably bad)
  return $prefix . $phonenumber . $extension;
}

/**
 * Formats the prefix as either +64 4 or (04), depending on the original prefix context
 *
 * @param string $prefix either '+64' or '0'
 * @param string  $area_code the area code, eg. 4, 21, 27 etc
 * @return string the formatted prefix
 */
function _format_nz_phone_number_prefix($prefix, $area_code) {
  $area_code = intval($area_code);
  if (in_array($area_code, array('800', '900'))) {
    return ($prefix == '0') ? $prefix.$area_code.' ' : $prefix.' '.$area_code.' ';
  }
  else {
    return ($prefix == '0') ? '('.$prefix.$area_code.') ' : $prefix.' '.$area_code.' ';
  }
}
