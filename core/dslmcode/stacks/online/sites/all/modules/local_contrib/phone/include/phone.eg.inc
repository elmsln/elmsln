<?php

/* 2009/10/24, Ahmad Gharbeia: initial release

  General phone number format is +20 (#[#]) #######[#]
  currently (10/2009) only Greater Cairo (including all of Giza) has 8 digits:
Regional area codes:
??????? ??????		2
??????????			3
?????????			13
?????? ?? ?????	15
???????				4
???????				45
?????					46
????????				47
????????				48
????????				5
???????				55
?????					57
??????				62
???????????			64
???????				65
???????				66
??????				68
???? ?????			69
??? ????				82
??????				84
??????				86
?????					88
?????? ??????		92
?????					93
??????					95
???					96
?????					97
mobile network operators' area codes:
	Mobinil: 12, 16
	Vodafone: 10, 19
	Etisalat: 11, 18

  **/
define('AREA_CODE_REGEX', "
		(
			 1(3|5)
			|3
			|4(5|6|7|8|)
			|5(5|7|)
			|6(2|4|5|6|8|9)
			|8(2|4|6|8)
			|9(2|3|5|6|7)
		)
");

define('MOBILE_CODE_REGEX', "1(0|2|1|6|8|9)");		//area codes 10, 11, 12, 16, 18, or 19

define('TELEPHONE_REGEX', "
	(\+20)\s																					# optional countrycode optionally followed by a space
		(
				\(2\)\s(2|3)\d{3}\s\d{4}								# 8-digit numbers begining with 2 or 3 (Greater Cairo: Cairo and Giza, both having area code = 2)
			|
				\(" . AREA_CODE_REGEX . "\)\s\d{3}\s\d{4}		# all other areas' numbers have 7 digits. Checks for correct area codes
			|
				\(" . MOBILE_CODE_REGEX . "\)\s\d{3}\s\d{4}		# mobile operators' networks' area codes; followed by 7 digits
		)
		(\s\#\s\d+)?																# optional extension number shown with a hash divider
");

function phone_eg_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid phone number in Egypt. Telephone numbers in Egypt have the format +20 (#[#]) 1234567[8], where the digts between ( ) is the area or network code, without a leading zero; and digits between [ ] are optional',
  );

}#end function phone_eg_metadata;


function valid_eg_phone_number($phonenumber) {
/*
	accepts:
	properly formatted: [+20][ ][(]#[#][)][ ]1234[ ]567[#]
	common: [(][0#[#]][)][ ]123[ ]456[#]
	area code could be within paranthises and|or prefixed with 0
*/

  $regex = "/^						# the same as the model regex above, but with elements made optional
		(\+20)?\s?																					# country code, with following space being optional
   (
				(\(0?2\)|0?2)\s?(2|3)\d{3}\s?\d{4}				# Greater Cairo, with leading optional zeros and optional braces around the area code
			|
				(\(0?" . AREA_CODE_REGEX . "\)|0?" . AREA_CODE_REGEX . ")\s?\d{3}\s?\d{4}					# other areas, with optional leading zeros and braces
			|
				(\(0?" . MOBILE_CODE_REGEX . "\)|0?" . MOBILE_CODE_REGEX . ")\s?\d{3}\s?\d{4}		# mobiles, with optional leading zeros and braces
		)
		(\s?\#\s?\d+)?  									# extension
	$/x";

  return (bool) preg_match($regex, $phonenumber);

}#end function valid_eg_phone_number;


function format_eg_phone_number($phonenumber, $field) {
	if (preg_match("/^" . TELEPHONE_REGEX . "$/x", $phonenumber)) {		//already in proper format
		return $phonenumber;
	}
	else {	//remove country code, zeros, and braces
		$phonenumber = preg_replace("/(^(\+20)?\s?|\(0?|\)|^0?)/", '', $phonenumber);
	}

	//If there are some spaces in the number assume some level of preformatting
  if (preg_match("/ /", $phonenumber)) {
		$regex = "/^
   	(
				(\d{1,2})					# area code
				\s*  						   # ignore required separator
				(\d{3,4})					# 4 digits in case of Greater Cairo
				\s*
				(\d{4})
			)
			((\s*\#)?(\d*))?  									# extension
		$/x";
		preg_match($regex, $phonenumber, $matches);
		$area = $matches[2];
		$number = $matches[3] . ' ' . $matches[4];
		$extension = $matches[7];
  }
  else {					//no spaces?, then apply some guessing
		$regex = "/^  # order is important in this one
			(
					(\d)(\d{4})(\d{4})				# 2 area code, followed by 8 digits begining with 2 or 3: Greater Cairo
				|
					(\d{1,2})(\d{3})(\d{4})				# 1 or 2-digit area code followed by 7 digits: regional or mobile
			)
			((\s*\#)?(\d*))?
		$/x";
		preg_match($regex, $phonenumber, $matches);
		$area = $matches[2];
		$number = $matches[3] . ' ' . $matches[4];
		$extension = $matches[5];
  }

	return '+20 (' . $area . ') ' . $number . (empty($extension) ? '' : " #$extension");
}#end function format_eg_phone_number;

