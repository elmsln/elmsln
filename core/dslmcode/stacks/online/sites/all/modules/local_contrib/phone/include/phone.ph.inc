<?php

/**
 * @file
 * CCK Field for Philippine phone numbers.
 */

 function phone_ph_metadata() {
   // These strings are translated using t() on output.
   return array(
     'error' => '"%value" is not a valid Philippine phone number<br />Example of valid Philippine phone numbers: +63 (2) 123-4567 or +63 (2) 123-4567 loc. 123	or mobile +63 (919) 123-4567',
   );
 }

/**
 * Verifies that $phonenumber is a valid ten-digit Philippine phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */

function valid_ph_phone_number($phonenumber) {

  /*
    Accepts:
        +63197071234567
				+63197071234567
        +63(19707) 1234567
				+63(19707) 123-4567
        +63 19707 123 4567
        +63 19707 123-4567
        (19707) 1234567 loc. 1234
  */
  $regex = "/
    (
        (^\+63\s?\(?\d{5}\)?|^\(?\d{5}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}  # 5 digit area code with optional +63 internationalisation or not, optional spaces and brackets.
        |
        (^\+63\s?\(?\d{4}\)?|^\(?\d{4}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}  # 4 digit area code with optional +63 internationalisation or not, optional spaces and brackets.
        |
        (^\+63\s?\(?\d{3}\)?|^\(?\d{3}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}  # 3 digit area code with optional +63 internationalisation or not, optional spaces and brackets.
        |
        (^\+63\s?\(?\d{2}\)?|^\(?\d{2}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}  # 2 digit area code with optional +63 internationalisation or not, optional spaces and brackets.
        |
        (^\+63\s?\(?\d{1}\)?|^\(?\d{1}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}  # 1 digit area code with optional +63 internationalisation or not, optional spaces and brackets.
    )
    (\s?\#\d*)?   # optional extension number shown with a loc. divider
  /x";
  // return true if valid, false otherwise
  if (!preg_match($regex, $phonenumber)) {
  	return FALSE;
  }
  else
  {
		return TRUE;
  }
}

/**
 * Convert a valid Philippine phone number into standard +63 (2) 123-4567 or	+63 (2) 123-4567 loc. 123	or mobile +63 (919) 123-4567
 *
 * @param $phonenumber must be a valid ten-digit number (with optional extension)
 *
 */
function format_ph_phone_number($phonenumber, $field = FALSE) {

    $area = $number = $extension = $description = '';

        //Simplify to 10 digit number and clean up ready for international reformat.
        $phonenumber = preg_replace("/^\+63/","",$phonenumber);
        $phonenumber = preg_replace("/\(/","",$phonenumber);
        $phonenumber = preg_replace("/\)/","",$phonenumber);

        //If there are some spaces in the number assume some level of preformatting
            $regex = "/
                # 5 digit area code.
                (
                    (\d{5}) # capture 5 digit area code
                    (\s*)?     # ignore required separator to make a distinction with other area codes
                    (\d{3}) # capture first set of numbers in the local number
                    (\S?|\s*)?     # ignore optional separator
                    (\d{4}) # capture second set of numbers in the local number
                |
                # 4 digit area code.
                    (\d{4}) # capture 4 digit area code
                    (\s*)?    # ignore required seperator
                    (\d{3}) # capture first set of numbers in the local number
                    (\S?|\s*)?     # ignore possible boundary
                    (\d{4}) # capture second set of numbers in the local number
                |
                # 3 digit area code.
                    (\d{3}) # capture 3 digit area code
                    (\s*)?     # ignore required seperator
                    (\d{3}) # capture first set of numbers in the local number
                    (\S?|\s*)?     # ignore possible boundary
                    (\d{4}) # capture second set of numbers in the local number
                |
                # 2 digit area code.
                    (\d{2}) # capture 2 digit area code
                    (\s*)?     # ignore required seperator
                    (\d{3}) # capture first set of numbers in the local number
                    (\S?|\s*)?     # ignore possible boundary
                    (\d{4}) # capture second set of numbers in the local number
                |
                # 1 digit area code.
                    (\d{1}) # capture 1 digit area code
                    (\s*)?     # ignore required boundary to make a distinction with other area codes
                    (\d{3}) # capture first set of numbers in the local number
                    (\S?|\s*)?     # ignore possible boundary
                    (\d{4}) # capture second set of numbers in the local number
                )
                # capture the optional extension number
                (\s*loc\.\s*|\s*ext\.\s*)?
                (\d*)?
								([a-zA-Z0-9\-\. \/\,\']{0,})?
            /x";
            preg_match($regex, $phonenumber, $matches);
            $area = $matches[2] . $matches[7] . $matches[12] . $matches[17] . $matches[22];
            $number = $matches[4] . $matches[9] . $matches[14] . $matches[19] . $matches[24] . '-' . $matches[6] . $matches[11] . $matches[16] . $matches[21] . $matches[26];
            $extension = $matches[28];
						$description = $matches[29];

      $phonenumber = '+63 (' . $area . ') ' . $number;
      $phonenumber .= (empty($extension)) ? '' : " loc. $extension";
			$phonenumber .= (empty($description))? '' : " $description";

  return $phonenumber;
}
