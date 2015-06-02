<?php

/**
 * @file typogrify.class.php
 * Defines a class for providing different typographical tweaks to HTML
 */
class Typogrify {
  /**
   * Enable custom styling of ampersands.
   *
   * Wraps apersands in html with '<span class="amp">', so they can be
   * styled with CSS. Ampersands are also normalized to '&amp;. Requires
   * ampersands to have whitespace or an '&nbsp;' on both sides.
   *
   * It won't mess up & that are already wrapped, in entities or URLs
   * @param string
   * @return string
   */
  public static function amp($text) {
    $amp_finder = "/(\s|&nbsp;)(&|&amp;|&\#38;|&#038;)(\s|&nbsp;)/";
    return preg_replace($amp_finder, '\\1<span class="amp">&amp;</span>\\3', $text);
  }

  /**
   * Puts a &thinsp; before and after an &ndash or &mdash;
   *
   * Dashes may have whitespace or an ``&nbsp;`` on both sides
   * @param string
   * @return string
   */
  public static function dash($text) {
      $dash_finder = "/(\s|&nbsp;|&thinsp;)*(&mdash;|&ndash;|&#x2013;|&#8211;|&#x2014;|&#8212;)(\s|&nbsp;|&thinsp;)*/";
      return preg_replace($dash_finder, '&thinsp;\\2&thinsp;', $text);
  }

  /**
   * Helper method for caps method - used for preg_replace_callback
   */
  public static function _cap_wrapper($matchobj) {
    if (!empty($matchobj[2])) {
      return sprintf('<span class="caps">%s</span>', $matchobj[2]);
    }
    else {
      $mthree = $matchobj[3];
      if (($mthree{strlen($mthree)-1}) == " ") {
        $caps = substr($mthree, 0, -1);
        $tail = ' ';
      }
      else {
        $caps = $mthree;
        $tail = $matchobj[4];
      }
      return sprintf('<span class="caps">%s</span>%s', $caps, $tail);
    }
  }

  /**
   * Stylable capitals
   *
   * Wraps multiple capital letters in ``<span class="caps">``
   * so they can be styled with CSS.
   *
   * Uses the smartypants tokenizer to not screw with HTML or with tags it shouldn't.
   */
  public static function caps($text) {
    // If _TokenizeHTML from Smartypants is not present, don't do anything.
    if (!function_exists('_TokenizeHTML')) {
      return $text;
    }

    $tokens = _TokenizeHTML($text);
    $result = array();
    $in_skipped_tag = false;

    $cap_finder = "/(
            (\b[[\p{Lu}=\d]*       # Group 2: Any amount of caps and digits
            [[\p{Lu}][[\p{Lu}\d]*  # A cap string much at least include two caps (but they can have digits between them)
            (?:&amp;)?             # allowing ampersand in caps.
            [[\p{Lu}'\d]*[[\p{Lu}\d]) # Any amount of caps and digits
            | (\b[[\p{Lu}]+\.\s?   # OR: Group 3: Some caps, followed by a '.' and an optional space
            (?:[[\p{Lu}]+\.\s?)+)  # Followed by the same thing at least once more
            (\s|\b|$|[)}\]>]))/xu";

    foreach ($tokens as $token) {
      if ( $token[0] == "tag" ) {
        // Don't mess with tags.
        $result[] = $token[1];
        $close_match = preg_match(SMARTYPANTS_TAGS_TO_SKIP, $token[1]);
        if ($close_match) {
          $in_skipped_tag = true;
        }
        else {
          $in_skipped_tag = false;
        }
      }
      else {
        if ($in_skipped_tag) {
          $result[] = $token[1];
        }
        else {
          $result[] = preg_replace_callback($cap_finder, array('Typogrify', '_cap_wrapper'), $token[1]);
        }
      }
    }
    return join("", $result);
  }

  /**
   * Helper method for initial_quotes method - used for preg_replace_callback
   */
  public static function _quote_wrapper($matchobj) {
    if (!empty($matchobj[7])) {
      $classname = "dquo";
      $quote = $matchobj[7];
    }
    else {
      $classname = "quo";
      $quote = $matchobj[8];
    }
    return sprintf('%s<span class="%s">%s</span>', $matchobj[1], $classname, $quote);
  }

  /**
   * initial_quotes
   *
   * Wraps initial quotes in ``class="dquo"`` for double quotes or
   * ``class="quo"`` for single quotes. Works in these block tags ``(h1-h6, p, li)``
   * and also accounts for potential opening inline elements ``a, em, strong, span, b, i``
   * Optionally choose to apply quote span tags to Gullemets as well.
   */
  public static function initial_quotes($text, $do_guillemets = false) {
    $quote_finder = "/((<(p|h[1-6]|li)[^>]*>|^)                     # start with an opening p, h1-6, li or the start of the string
                    \s*                                             # optional white space!
                    (<(a|em|span|strong|i|b)[^>]*>\s*)*)            # optional opening inline tags, with more optional white space for each.
                    ((\"|&ldquo;|&\#8220;)|('|&lsquo;|&\#8216;))    # Find me a quote! (only need to find the left quotes and the primes)
                                                                    # double quotes are in group 7, singles in group 8
                    /ix";

    if ($do_guillemets) {
    	$quote_finder = "/((<(p|h[1-6]|li)[^>]*>|^)                     					# start with an opening p, h1-6, li or the start of the string
	                    \s*                                             					# optional white space!
	                    (<(a|em|span|strong|i|b)[^>]*>\s*)*)            					# optional opening inline tags, with more optional white space for each.
	                    ((\"|&ldquo;|&\#8220;|\xAE|&\#171;|&laquo;)|('|&lsquo;|&\#8216;))    # Find me a quote! (only need to find the left quotes and the primes) - also look for guillemets (>> and << characters))
	                                                                    					# double quotes are in group 7, singles in group 8
	                    /ix";
    }
    return preg_replace_callback($quote_finder, array('Typogrify', '_quote_wrapper'), $text);
  }

  /**
   * widont
   *
   * Replaces the space between the last two words in a string with ``&nbsp;``
   * Works in these block tags ``(h1-h6, p, li)`` and also accounts for
   * potential closing inline elements ``a, em, strong, span, b, i``
   *
   * Empty HTMLs shouldn't error
   */
  public static function widont($text) {
    // This regex is a beast, tread lightly
    $widont_finder = "/([^<>\s]+|<\/span>)                    # ensure more than 1 word
                      (\s+)                                   # the space to replace
                      ([^<>\s]+                               # must be flollowed by non-tag non-space characters
                      \s*                                     # optional white space!
                      (<\/(a|em|span|strong|i|b)[^>]*>\s*)*   # optional closing inline tags with optional white space after each
                      ((<\/(p|h[1-6]|li|dt|dd)>)|$))          # end with a closing p, h1-6, li or the end of the string
                      /x";
    return preg_replace($widont_finder, '$1&nbsp;$3', $text);
  }

  /**
   * typogrify
   *
   * The super typography filter.
   * Applies the following filters: widont, smartypants, caps, amp, initial_quotes
   * Optionally choose to apply quote span tags to Gullemets as well.
   */
  public static function filter($text, $do_guillemets=FALSE) {
    $text = Typogrify::amp($text);
    $text = Typogrify::widont($text);
    $text = SmartyPants($text);
    $text = Typogrify::caps($text);
    $text = Typogrify::initial_quotes($text, $do_guillemets);
    $text = Typogrify::dash($text);
    return $text;
  }
}

