<?php

function phone_int_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Italian phone number<br>Italian phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is a valid international phone number as per ITU or,
 * if a default country code is specified, a valid subscriber number.
 *
 * @see http://www.itu.int/rec/T-REC-E.123/en
 *
 * @param $phonenumber
 *   International phone number to validate
 * @return
 *   TRUE if valid, FALSE if otherwise.
 */
function valid_int_phone_number($phonenumber) {
  $phonenumber = trim($phonenumber);
  if ($phonenumber === '') {
    return FALSE;
  }
  $phonenumber = _normalize_country_code($phonenumber);
  $base_phonenumber = str_replace(array('.', '(', ')', '[', ']', '-', '+', ' '), '', $phonenumber);
  if (!isset($field['phone_int_max_length'])) {
    $field['phone_int_max_length'] = 15;
  }
  if (strlen($base_phonenumber) > $field['phone_int_max_length']) {
    $error = t('Invalid international phone number: Phone number is too long; international phone numbers are limited to 15 digits.');
    return FALSE;
  }
  // Check if digits are used in the base_phonenumber
  if (!ctype_digit($base_phonenumber)) {  
    $error = t('Invalid international phone number: Phone number contains invalid characters; only allowed characters are numbers and punctuation.');
    return FALSE;
  }
  // Extract country code and see if it's correct:
  preg_match('/^\+(\d+)/', $phonenumber, $matches);
  $cc = $matches[1];
  if (strlen($cc) > 3) {
    $error = array(
      t('Invalid international phone number: Country code "+%cc" is too long; valid country codes are three digits or less.'),
      array('%cc' => $cc)
    );
    return FALSE;
  }
  
  //drupal_set_message('langue cc = ' . $cc, 'error');

  // TODO: Check if parentheses/brackets add up.
  // TODO: Validate the number against the country rules.
  // For now, validate only against a limited number of countries.

  $countrycode = phone_country_code_convert($cc);
  //drupal_set_message('langue countrycode = ' . $countrycode, 'error');
  if (!empty($countrycode)) {
      $valid_phone_function = 'valid_'. $countrycode . '_phone_number';
      module_load_include('inc', 'phone', 'phone.'. $countrycode);
      if (function_exists($valid_phone_function)) {
        return $valid_phone_function($phonenumber, $field);
      }
      else {
      	return TRUE; 
      }
  }
  
  return FALSE;
}

/**
 * Formats $phonenumber into the standard representation of international
 * numbers as per E.123.
 *
 * @param $phonenumber
 *   International phone number to format
 * @return
 *   Formatted international phone number
 */
function format_int_phone_number($phonenumber, $field = array()) {
  $phonenumber = trim($phonenumber);
  if ($phonenumber === '') {
    return '';
  }
  $phonenumber = _normalize_country_code($phonenumber, $field);
  $bits = preg_split('/[.()\[\]\- ]/', $phonenumber, -1, PREG_SPLIT_NO_EMPTY);
  // $bits[0] is the country code WITH a plus sign.
  if (isset($bits[1])) {
    // This is the first non-CC segment, so it could have the NDN.
    switch ($bits[1][0]) {
      case 0:
        $bits[1] = substr($bits[1], 1);
        break;
    }
    switch ($bits[1]) {
      case 0:
      case 7:
      case 8:
        array_splice($bits, 1, 1);
        break;
    }
  }
  return implode(' ', $bits);
}

/**
 * Adds a country code to a phone number if necessary.
 *
 * @param $phonenumber
 *   International or local phone number to format
 * @return
 *   International phone number with country code
 */
function _normalize_country_code($phonenumber, $field = array()) {
  if ($phonenumber[0] !== '+') {
    $cc = isset($field['phone_default_country_code']) ? $field['phone_default_country_code'] : '1';
    return "+$cc $phonenumber";
  }
  return $phonenumber;
}

/**
 * Returns the country code in the desired format.
 *
 * @todo Fill in the rest of the country code values.
 *
 * @param $code
 *   Country code to convert (either numeric or 2-letter abbreviation)
 * @param $input_type
 *   Type of country code to convert (either numeric or 2-letter abbreviation)
 * @return
 *   Converted country code
 */
function phone_country_code_convert($code, $input_type = 'digits') {
   static $codes;
   if (!$codes) {
    $codes = array(    
      '1' => 'ca',
      '1' => 'us',
      '7' => 'ru',
      '20' => 'eg',
      '27' => 'za',
      '30' => 'gr',
      '31' => 'nl',
      '32' => 'be',
      '33' => 'fr',
      '34' => 'es',
      '36' => 'hu',
      '39' => 'it',
      '39' => 'va',
      '40' => 'ro',
      '41' => 'ch',
      '43' => 'at',
      '44' => 'gb',
      '45' => 'dk',
      '46' => 'se',
      '47' => 'no',
      '48' => 'pl',
      '49' => 'de', 
      '51' => 'pe',
      '52' => 'mx',
      '53' => 'cu',
      '54' => 'ar',
      '55' => 'br',
      '56' => 'cl',
      '57' => 'co',
      '58' => 've',    
      '60' => 'my',
      '61' => 'au',
      '61' => 'cc',
      '61' => 'cx',
      '62' => 'id',
      '63' => 'ph',
      '64' => 'nz',
      '65' => 'sg',
      '66' => 'th',
      '81' => 'jp',
      '82' => 'kr',
      '84' => 'vn',
      '86' => 'cn',
      '90' => 'tr',
      '91' => 'in',
      '92' => 'pk',
      '93' => 'af',
      '94' => 'lk',
      '95' => 'mm',
      '98' => 'ir', 
      '212' => 'ma',
      '213' => 'dz',
      '216' => 'tn',
      '218' => 'ly',
      '220' => 'gm',
      '221' => 'sn',
      '222' => 'mr',
      '223' => 'ml',
      '224' => 'gn',
      '225' => 'ci',
      '226' => 'bf',
      '227' => 'ne',
      '228' => 'tg',
      '229' => 'bj',
      '230' => 'mu',
      '231' => 'lr',
      '232' => 'sl',
      '233' => 'gh',
      '234' => 'ng',
      '235' => 'td',
      '236' => 'cf',
      '237' => 'cm',
      '238' => 'cv',
      '239' => 'st',
      '240' => 'gq',
      '241' => 'ga',
      '242' => 'cg',
      '243' => 'cd',
      '244' => 'ao',
      '245' => 'gw',
      '246' => 'io',
      '248' => 'sc',
      '249' => 'sd',
      '250' => 'rw',
      '251' => 'et',
      '252' => 'so',
      '253' => 'dj',
      '254' => 'ke',
      '255' => 'tz',
      '256' => 'ug',
      '257' => 'bi',
      '258' => 'mz',
      '260' => 'zm',
      '261' => 'mg',
      '263' => 'zw',
      '264' => 'na',
      '265' => 'mw',
      '266' => 'ls',
      '267' => 'bw',
      '268' => 'sz',
      '269' => 'km',
      '269' => 'yt',
      '290' => 'sh',
      '291' => 'er',
      '297' => 'aw',
      '298' => 'fo',
      '299' => 'gl',
      '350' => 'gi',
      '351' => 'pt',
      '352' => 'lu',
      '353' => 'ie',
      '354' => 'is',
      '355' => 'al',
      '356' => 'mt',
      '357' => 'cy',
      '358' => 'fi',
      '359' => 'bg',
      '370' => 'lt',
      '371' => 'lv',
      '372' => 'ee',
      '373' => 'md',
      '374' => 'am',
      '375' => 'by',
      '376' => 'ad',
      '377' => 'mc',
      '378' => 'sm',
      '380' => 'ua',
      '381' => 'rs',
      '382' => 'me',
      '385' => 'hr',
      '386' => 'si',
      '387' => 'ba',
      '389' => 'mk',   
      '420' => 'cz',
      '421' => 'sk',
      '423' => 'li',
      '500' => 'fk',
      '501' => 'bz',
      '502' => 'gt',
      '503' => 'sv',
      '504' => 'hn',
      '505' => 'ni',
      '506' => 'cr',
      '507' => 'pa',
      '508' => 'pm',
      '509' => 'ht',
      '590' => 'gp',
      '591' => 'bo',
      '592' => 'gy',
      '593' => 'ec',
      '594' => 'gf',
      '595' => 'py',
      '596' => 'mq',
      '597' => 'sr',
      '598' => 'uy',
      '599' => 'an',
      '670' => 'tp',
      '672' => 'nf',
      '673' => 'bn',
      '674' => 'nr',
      '675' => 'pg',
      '676' => 'to',
      '677' => 'sb',
      '678' => 'vu',
      '679' => 'fj',
      '680' => 'pw',
      '681' => 'wf',
      '682' => 'ck',
      '683' => 'nu',
      '686' => 'ki',
      '687' => 'nc',
      '688' => 'tv',
      '689' => 'pf',
      '690' => 'tk',
      '691' => 'fm',
      '692' => 'mh', 
      '850' => 'kp',
      '852' => 'hk',
      '853' => 'mo',
      '855' => 'kh',
      '856' => 'la',
      '880' => 'bd',
      '886' => 'tw', 
      '960' => 'mv',
      '961' => 'lb',
      '962' => 'jo',
      '963' => 'sy',
      '964' => 'iq',
      '965' => 'kw',
      '966' => 'sa',
      '967' => 'ye',
      '968' => 'om',
      '970' => 'ps',
      '971' => 'ae',
      '972' => 'il',
      '973' => 'bh',
      '974' => 'qa',
      '975' => 'bt',
      '976' => 'mn',
      '977' => 'np',
      '992' => 'tj',
      '993' => 'tm',
      '994' => 'az',
      '995' => 'ge',
      '996' => 'kg',
      '998' => 'uz',      
    );
   }

  if ($input_type == 'alpha') {
    $codes = array_flip($codes);
  }
  return isset($codes[$code]) ? $codes[$code] : FALSE;
}

