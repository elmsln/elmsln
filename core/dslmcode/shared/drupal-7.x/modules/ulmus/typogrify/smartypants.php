<?php

/**
 * @file
 * SmartyPants  -  Smart punctuation for web sites
 *
 * by John Gruber <http://daringfireball.net>
 *
 * PHP port by Michel Fortin
 * <http://www.michelf.com/>
 *
 * Copyright (c) 2003-2004 John Gruber
 * Copyright (c) 2004-2005 Michel Fortin
 * Copyright (c) 2012 Micha Glave - i18n-quote-style
 *
 * Re-released under GPLv2 for Drupal.
 */

// Fri 9 Dec 2005
define('SMARTYPANTS_PHP_VERSION', '1.5.1e');
// Fri 12 Mar 2004
define('SMARTYPANTS_SYNTAX_VERSION', '1.5.1');
// Regex-pattern for tags we don't mess with.
define('SMARTYPANTS_TAGS_TO_SKIP', '@<(/?)(?:pre|code|kbd|script|textarea|tt|math)[\s>]@');

// A global variable to keep track of our current SmartyPants
// configuration setting.
//
// Change this to configure.
// 1 =>  "--" for em-dashes; no en-dash support
// 2 =>  "---" for em-dashes; "--" for en-dashes
// 3 =>  "--" for em-dashes; "---" for en-dashes
// See docs for more configuration options.
$_typogrify_smartypants_attr = "1";

/* -- Smarty Modifier Interface ------------------------------------------*/

/**
 * Wrapper methode for SmartyPants.
 */
function smarty_modifier_smartypants($text, $attr = NULL) {
  return SmartyPants($text, $attr);
}

/**
 * returns a locale-specific array of quotes.
 */
function typogrify_i18n_quotes($langcode = NULL) {
  // Ignore all english-equivalents served by fallback.
  $quotes = array(
    'ar' => array('«', '»', '‹', '›'), // Arabic
    'be' => array('«', '»', '„', '“'), // Belarusian
    'bg' => array('„', '“', '‚', '‘'), // Bulgarian
    'da' => array('»', '«', '›', '‹'), // Danish
    'de' => array('„', '“', '‚', '‘'), // German
    'el' => array('«', '»', '‹', '›'), // Greek
    'en' => array('“', '”', '‘', '’'), // English
    'eo' => array('“', '”', '“', '”'), // Esperanto
    'es' => array('«', '»', '“', '“'), // Spanish
    'et' => array('„', '“', '„', '“'), // Estonian
    'fi' => array('”', '”', '’', '’'), // Finnish
    'fr' => array('«', '»', '‹', '›'), // French
    'gsw-berne' => array('„', '“', '‚', '‘'), // Swiss German
    'he' => array('“', '“', '«', '»'), // Hebrew
    'hr' => array('»', '«', '›', '‹'), // Croatian
    'hu' => array('„', '“', '„', '“'), // Hungarian
    'is' => array('„', '“', '‚', '‘'), // Icelandic
    'it' => array('«', '»', '‘', '’'), // Italian
    'lt' => array('„', '“', '‚', '‘'), // Lithuanian
    'lv' => array('„', '“', '„', '“'), // Latvian
    'nl' => array('„', '”', '‘', '’'), // Dutch
    'no' => array('„', '“', '„', '“'), // Norwegian
    'pl' => array('„', '”', '«', '»'), // Polish
    'pt' => array('“', '”', '‘', '’'), // Portuguese
    'ro' => array('„', '“', '«', '»'), // Romanian
    'ru' => array('«', '»', '„', '“'), // Russian
    'sk' => array('„', '“', '‚', '‘'), // Slovak
    'sl' => array('„', '“', '‚', '‘'), // Slovenian
    'sq' => array('«', '»', '‹', '›'), // Albanian
    'sr' => array('„', '“', '‚', '‘'), // Serbian
    'sv' => array('”', '”', '’', '’'), // Swedish
    'tr' => array('«', '»', '‹', '›'), // Turkish
    'uk' => array('«', '»', '„', '“'), // Ukrainian.
  );
  if ($langcode == 'all') {
    return $quotes;
  }
  if (isset($quotes[$langcode])) {
    return $quotes[$langcode];
  }
  return $quotes['en'];
}


/**
 * SmartyPants.
 *
 * @param string $text
 *   Text to be parsed.
 * @param string $attr
 *   Value of the smart_quotes="" attribute.
 * @param string $ctx
 *   MT context object (unused).
 */
function SmartyPants($text, $attr = NULL, $ctx = NULL) {
  if ($attr == NULL) {
    global $_typogrify_smartypants_attr;
    $attr = $_typogrify_smartypants_attr;
  }
  // Options to specify which transformations to make.
  $do_stupefy = FALSE;
  // Should we translate &quot; entities into normal quotes?
  $convert_quot = 0;

  // Parse attributes:
  // 0 : do nothing
  // 1 : set all
  // 2 : set all, using old school en- and em- dash shortcuts
  // 3 : set all, using inverted old school en and em- dash shortcuts
  //
  // q : quotes
  // b : backtick quotes (``double'' and ,,double`` only)
  // B : backtick quotes (``double'', ,,double``, ,single` and `single')
  // d : dashes
  // D : old school dashes
  // i : inverted old school dashes
  // e : ellipses
  // w : convert &quot; entities to " for Dreamweaver users.
  if ($attr == "0") {
    // Do nothing.
    return $text;
  }
  elseif ($attr == "1") {
    // Do everything, turn all options on.
    $do_quotes    = 2;
    $do_backticks = 1;
    $do_dashes    = 1;
    $do_ellipses  = 1;
  }
  elseif ($attr == "2") {
    // Do everything, turn all options on, use old school dash shorthand.
    $do_quotes    = 2;
    $do_backticks = 1;
    $do_dashes    = 2;
    $do_ellipses  = 1;
  }
  elseif ($attr == "3") {
    // Do everything, turn all options on,
    // use inverted old school dash shorthand.
    $do_quotes    = 2;
    $do_backticks = 1;
    $do_dashes    = 3;
    $do_ellipses  = 1;
  }
  elseif ($attr == "-1") {
    // Special "stupefy" mode.
    $do_stupefy   = 1;
  }
  else {
    $chars = preg_split('//', $attr);
    foreach ($chars as $c) {
      if ($c == "q") {
        $do_quotes    = 1;
      }
      elseif ($c == "Q") {
        $do_quotes    = 2;
      }
      elseif ($c == "b") {
        $do_backticks = 1;
      }
      elseif ($c == "B") {
        $do_backticks = 2;
      }
      elseif ($c == "d") {
        $do_dashes    = 1;
      }
      elseif ($c == "D") {
        $do_dashes    = 2;
      }
      elseif ($c == "i") {
        $do_dashes    = 3;
      }
      elseif ($c == "e") {
        $do_ellipses  = 1;
      }
      elseif ($c == "w") {
        $convert_quot = 1;
      }
    }
  }
  if ($do_quotes == 2) {
    $doc_lang = $ctx['langcode'];
  }
  else {
    $doc_lang = 'en';
  }

  $tokens = _TokenizeHTML($text);
  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;

  // This is a cheat, used to get some context
  // for one-character tokens that consist of
  // just a quote char. What we do is remember
  // the last character of the previous text
  // token, to use as context to curl single-
  // character quote tokens correctly.
  $prev_token_last_char = '';

  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == 'tag') {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
      else {
        // Reading language from span.
        if (preg_match('/<span .*(xml:)?lang="(..)"/', $cur_token[1], $matches)) {
          $span_lang = $matches[2];
        }
        elseif ($cur_token[1] == '</span>') {
          unset($span_lang);
        }
      }
    }
    else {
      $t = $cur_token[1];
      // Remember last char of this token before processing.
      $last_char = mb_substr($t, -1);
      if (!$in_pre) {
        $quotes = typogrify_i18n_quotes(isset($span_lang) ? $span_lang : $doc_lang);

        $t = ProcessEscapes($t);

        if ($convert_quot) {
          $t = preg_replace('/&quot;/', '"', $t);
        }

        if ($do_dashes) {
          if ($do_dashes == 1) {
            $t = EducateDashes($t);
          }
          elseif ($do_dashes == 2) {
            $t = EducateDashesOldSchool($t);
          }
          elseif ($do_dashes == 3) {
            $t = EducateDashesOldSchoolInverted($t);
          }
        }

        if ($do_ellipses) {
          $t = EducateEllipses($t);
        }

        // Note: backticks need to be processed before quotes.
        if ($do_backticks) {
          $t = EducateBackticks($t);
          if ($do_backticks == 2) {
            $t = EducateSingleBackticks($t);
          }
        }
        if ($do_quotes) {
          $t = EducateBackticks($t);
          if ($t == "'") {
            // Special case: single-character ' token.
            if (preg_match('/\S/', $prev_token_last_char)) {
              $t = $quotes[3];
            }
            else {
              $t = $quotes[2];
            }
          }
          elseif ($t == '"') {
            // Special case: single-character " token.
            if (preg_match('/\S/', $prev_token_last_char)) {
              $t = $quotes[1];
            }
            else {
              $t = $quotes[0];
            }
          }
          else {
            // Normal case:
            $t = EducateQuotes($t, $quotes);
          }
        }
        if ($do_stupefy) {
          $t = StupefyEntities($t);
        }
      }
      $prev_token_last_char = $last_char;
      $result .= $t;
    }
  }

  return $result;
}

/**
 * SmartQuotes
 *
 * @param string $text
 *   Text to be parsed.
 * @param string $attr
 *   Value of the smart_quotes="" attribute.
 * @param string $ctx
 *   MT context object (unused).
 *
 * @return string
 *   $text with replacements.
 */
function SmartQuotes($text, $attr = NULL, $ctx = NULL) {
  if ($attr == NULL) {
    global $_typogrify_smartypants_attr;
    $attr = $_typogrify_smartypants_attr;
  }
  // Should we educate ``backticks'' -style quotes?
  $do_backticks;

  if ($attr == 0) {
    // Do nothing;
    return $text;
  }
  elseif ($attr == 2) {
    // Smarten ``backticks'' -style quotes.
    $do_backticks = 1;
  }
  else {
    $do_backticks = 0;
  }

  // Special case to handle quotes at the very end of $text when preceded by
  // an HTML tag. Add a space to give the quote education algorithm a bit of
  // context, so that it can guess correctly that it's a closing quote:
  $add_extra_space = 0;
  if (preg_match("/>['\"]\\z/", $text)) {
    // Remember, so we can trim the extra space later.
    $add_extra_space = 1;
    $text .= " ";
  }

  $tokens = _TokenizeHTML($text);
  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;

  // This is a cheat, used to get some context
  // for one-character tokens that consist of
  // just a quote char. What we do is remember
  // the last character of the previous text
  // token, to use as context to curl single-
  // character quote tokens correctly.
  $prev_token_last_char = "";

  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      // Remember last char of this token before processing.
      $last_char = mb_substr($t, -1);
      if (!$in_pre) {
        $t = ProcessEscapes($t);
        if ($do_backticks) {
          $t = EducateBackticks($t);
        }

        if ($t == "'") {
          // Special case: single-character ' token.
          if (preg_match('/\S/', $prev_token_last_char)) {
            $t = "&#8217;";
          }
          else {
            $t = "&#8216;";
          }
        }
        elseif ($t == '"') {
          // Special case: single-character " token.
          if (preg_match('/\S/', $prev_token_last_char)) {
            $t = "&#8221;";
          }
          else {
            $t = "&#8220;";
          }
        }
        else {
          // Normal case:
          $t = EducateQuotes($t);
        }

      }
      $prev_token_last_char = $last_char;
      $result .= $t;
    }
  }

  if ($add_extra_space) {
    // Trim trailing space if we added one earlier.
    preg_replace('/ \z/', '', $result);
  }
  return $result;
}

/**
 * SmartDashes.
 *
 * @param string $text
 *   Text to be parsed.
 * @param string $attr
 *   Value of the smart_quotes="" attribute.
 * @param string $ctx
 *   MT context object (unused).
 *
 * @return string
 *   $text with replacements.
 */
function SmartDashes($text, $attr = NULL, $ctx = NULL) {
  if ($attr == NULL) {
    global $_typogrify_smartypants_attr;
    $attr = $_typogrify_smartypants_attr;
  }

  // Reference to the subroutine to use for dash education,
  // default to EducateDashes:
  $dash_sub_ref = 'EducateDashes';

  if ($attr == 0) {
    // Do nothing;
    return $text;
  }
  elseif ($attr == 2) {
    // Use old smart dash shortcuts, "--" for en, "---" for em.
    $dash_sub_ref = 'EducateDashesOldSchool';
  }
  elseif ($attr == 3) {
    // Inverse of 2, "--" for em, "---" for en.
    $dash_sub_ref = 'EducateDashesOldSchoolInverted';
  }

  $tokens;
  $tokens = _TokenizeHTML($text);

  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $t = ProcessEscapes($t);
        $t = $dash_sub_ref($t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * SmartEllipses.
 *
 * @param string $text
 *   Text to be parsed.
 * @param string $attr
 *   Value of the smart_quotes="" attribute.
 * @param string $ctx
 *   MT context object (unused).
 *
 * @return string
 *   $text with replacements.
 */
function SmartEllipses($text, $attr = NULL, $ctx = NULL) {
  if ($attr == NULL) {
    global $_typogrify_smartypants_attr;
    $attr = $_typogrify_smartypants_attr;
  }

  if ($attr == 0) {
    // Do nothing;
    return $text;
  }

  $tokens;
  $tokens = _TokenizeHTML($text);

  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $t = ProcessEscapes($t);
        $t = EducateEllipses($t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * Replaces = with '&shy;' for easier manual hyphenating.
 *
 * @param string $text
 *   work on.
 */
function typogrify_hyphenate($text) {
  $tokens;
  $tokens = _TokenizeHTML($text);

  $equal_finder = '/(\p{L})=(\p{L})/u';
  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $t = preg_replace($equal_finder, '\1&shy;\2', $t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * Adding space in numbers for easier reading aka digit grouping.
 *
 * @param string $text
 *   to work on.
 * @param int   $attr
 *   kind of space to use.
 * @param array $ctx
 *   not used.
 */
function typogrify_smart_numbers($text, $attr = 0, $ctx = NULL) {
  $tokens;
  $tokens = _TokenizeHTML($text);

  if ($attr == 0) {
    return $text;
  }
  elseif ($attr == 1) {
    $method = '_typogrify_number_narrownbsp';
  }
  elseif ($attr == 2) {
    $method = '_typogrify_number_thinsp';
  }
  elseif ($attr == 3) {
    $method = '_typogrify_number_span';
  }
  elseif ($attr == 4) {
    $method = '_typogrify_number_just_span';
  }

  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  $span_stop = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
      elseif (preg_match('/<span .*class="[^"]*\b(number|phone|ignore)\b[^"]*"/', $cur_token[1], $matches)) {
          $span_stop = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
      elseif ($cur_token[1] == '</span>') {
          $span_stop = 0;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre && !$span_stop) {
        $number_finder = '@(?:(&#\d{2,4};|&(#x[0-9a-fA-F]{2,4}|frac\d\d);)|' .
          '(\d{4}-\d\d-\d\d)|(\d\d\.\d\d\.\d{4})|' .
          '(0[ \d-/]+)|([+-]?\d+)([.,]\d+|))@';
        $t = preg_replace_callback($number_finder, $method, $t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * Internal: wraps and inserts space in numbers.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 * @param string $thbl
 *   kind of whitespace to add.
 */
function _typogrify_number_replacer($hit, $thbl) {
  if ($hit[1] != '') {
    // Html-entity number: don't touch.
    return $hit[1];
  }
  elseif ($hit[2] != '') {
    // Html-entity number: don't touch.
    return $hit[2];
  }
  elseif ($hit[3] != '') {
    // Don't format german phone-numbers.
    return $hit[3];
  }
  elseif ($hit[4] != '') {
    // Date -`iso don't touch.
    return $hit[4];
  }
  elseif ($hit[5] != '') {
    // Date -`dd.mm.yyyy don't touch.
    return $hit[5];
  }
  if (preg_match('/[+-]?\d{5,}/', $hit[6]) == 1) {
    $dec = preg_replace('/[+-]?\d{1,3}(?=(\d{3})+(?!\d))/', '\0' . $thbl, $hit[6]);
  } else {
    $dec = $hit[6];
  }
  $frac = preg_replace('/\d{3}/', '\0' . $thbl, $hit[7]);
  return '<span class="number">' . $dec . $frac . '</span>';
}

/**
 * Wrapping numbers and adding whitespace '&narrownbsp;'.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_number_narrownbsp($hit) {
  return _typogrify_number_replacer($hit, '&#8239;');
}

/**
 * Wrapping numbers and adding whitespace '&thinsp;'.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_number_thinsp($hit) {
  return _typogrify_number_replacer($hit, '&#8201;');
}

/**
 * Wrapping numbers and adding whitespace by setting margin-left in a span.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_number_span($hit) {
  $thbl = '<span style="margin-left:0.167em"></span>';
  return _typogrify_number_replacer($hit, $thbl);
}

/**
 * Wrapping numbers and adding whitespace by setting margin-left in a span.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_number_just_span($hit) {
  return _typogrify_number_replacer($hit, '');
}

/**
 * Wrapping abbreviations and adding half space between digit grouping.
 *
 * @param string $text
 *   to work on.
 * @param int $attr
 *   kind of space to use.
 * @param array $ctx
 *   not used.
 */
function typogrify_smart_abbreviation($text, $attr = 0, $ctx = NULL) {
  $tokens;
  $tokens = _TokenizeHTML($text);

  $replace_method = '_typogrify_abbr_asis';
  if ($attr == 1) {
    $replace_method = '_typogrify_abbr_narrownbsp';
  }
  elseif ($attr == 2) {
    $replace_method = '_typogrify_abbr_thinsp';
  }
  elseif ($attr == 3) {
    $replace_method = '_typogrify_abbr_span';
  }
  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $abbr_finder = '/(?<=\s|)(\p{L}+\.)(\p{L}+\.)+(?=\s|)/u';
        $t = preg_replace_callback($abbr_finder, $replace_method, $t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * Wrapping abbreviations without adding whitespace.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_abbr_asis($hit) {
  return '<span class="abbr">' . $hit[0] . '</span>';
}

/**
 * Wrapping abbreviations adding whitespace '&thinsp;'.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_abbr_thinsp($hit) {
  $res = preg_replace('/\.(\p{L})/u', '.&#8201;\1', $hit[0]);
  return '<span class="abbr">' . $res . '</span>';
}

/**
 * Wrapping abbreviations adding whitespace '&narrownbsp;'.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_abbr_narrownbsp($hit) {
  $res = preg_replace('/\.(\p{L})/u', '.&#8239;\1', $hit[0]);
  return '<span class="abbr">' . $res . '</span>';
}

/**
 * Wrapping abbreviations adding whitespace by setting margin-left in a span.
 *
 * @param array $hit
 *   matcher-array from preg_replace_callback.
 */
function _typogrify_abbr_span($hit) {
  $thbl = '.<span style="margin-left:0.167em"><span style="display:none">&nbsp;</span></span>';
  $res = preg_replace('/\.(\p{L})/u', $thbl . '\1', $hit[0]);
  return '<span class="abbr">' . $res . '</span>';
}

/**
 * Wrapping ampersands.
 *
 * @param string $text
 *   text to work on.
 */
function SmartAmpersand($text) {
  $tokens;
  $tokens = _TokenizeHTML($text);

  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $t = Typogrify::amp($t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * EducatedQuotes.
 * Example input:  "Isn't this fun?"
 * Example output: [0]Isn&#8217;t this fun?[1];
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with "educated" curly quote HTML entities.
 */
function EducateQuotes($_, $quotes) {
  // Make our own "punctuation" character class, because the POSIX-style
  // [:PUNCT:] is only available in Perl 5.6 or later:
  $punct_class = "[!\"#\\$\\%'()*+,-.\\/:;<=>?\\@\\[\\\\\]\\^_`{|}~]";

  // Special case if the very first character is a quote
  // followed by punctuation at a non-word-break.
  // Close the quotes by brute force:
  $_ = preg_replace(
    array("/^'(?=$punct_class\\B)/", "/^\"(?=$punct_class\\B)/"),
    array($quotes[3], $quotes[1]), $_);


  // Special case for double sets of quotes, e.g.:
  // <p>He said, "'Quoted' words in a larger quote."</p>.
  $spacer = '&#8201;';
  $_ = preg_replace(
    array(
      "/\"'(?=\p{L})/u",
      "/'\"(?=\p{L})/u",
      "/(\p{L})\"'/u",
      "/(\p{L})'\"/u",
    ),
    array(
      $quotes[0] . $spacer . $quotes[2],
      $quotes[2] . $spacer . $quotes[0],
      '\1' . $quotes[1] . $spacer . $quotes[3],
      '\1' . $quotes[3] . $spacer . $quotes[1],
    ), $_);

  // Special case for decade abbreviations (the '80s):
  $_ = preg_replace("/'(?=\\d{2}s)/", '&#8217;', $_);

  // Special case for apostroph.
  $_ = preg_replace("/(\\p{L})(')(?=\\p{L}|$)/u", '\1&#8217;', $_);

  $close_class = '[^\ \t\r\n\[\{\(\-]';
  $dec_dashes = '&\#8211;|&\#8212;';

  // Get most opening single quotes:
  $_ = preg_replace("{
    (
      \\s         |   # a whitespace char, or
      &nbsp;      |   # a non-breaking space entity, or
      --          |   # dashes, or
      &[mn]dash;  |   # named dash entities
      $dec_dashes |   # or decimal entities
      &\\#x201[34];   # or hex
    )
    '                 # the quote
    (?=\\p{L})           # followed by a word character
    }x", '\1' . $quotes[2], $_);
  // Single closing quotes:
  $_ = preg_replace("{
    ($close_class)?
    '
    (?(1)|            # If $1 captured, then do nothing;
      (?=\\s | s\\b)  # otherwise, positive lookahead for a whitespace
    )                 # char or an 's' at a word ending position. This
                      # is a special case to handle something like:
                      # \"<i>Custer</i>'s Last Stand.\"
    }xi", '\1' . $quotes[3], $_);

  // Any remaining single quotes should be opening ones:
  $_ = str_replace("'", $quotes[2], $_);


  // Get most opening double quotes:
  $_ = preg_replace("{
    (
      \\s         |   # a whitespace char, or
      &nbsp;      |   # a non-breaking space entity, or
      --          |   # dashes, or
      &[mn]dash;  |   # named dash entities
      $dec_dashes |   # or decimal entities
      &\\#x201[34];   # or hex
    )
    \"                # the quote
    (?=\\p{L})           # followed by a word character
    }x", '\1' . $quotes[0], $_);

  // Double closing quotes:
  $_ = preg_replace("{
    ($close_class)?
    \"
    (?(1)|(?=\\s))   # If $1 captured, then do nothing;
                     # if not, then make sure the next char is whitespace.
    }x", '\1' . $quotes[1], $_);

  // Any remaining quotes should be opening ones.
  $_ = str_replace('"', $quotes[0], $_);

  return $_;
}


/**
 * Example input:  ``Isn't this fun?''
 * Example output: &#8220;Isn't this fun?&#8221;.
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with ``backticks'' -style double quotes
 *   translated into HTML curly quote entities.
 */
function EducateBackticks($_) {
  $_ = str_replace(array("``", "''", ",,"),
                   array('&#8220;', '&#8221;', '&#8222;'), $_);
  return $_;
}


/**
 * Example input:  `Isn't this fun?'
 * Example output: &#8216;Isn&#8217;t this fun?&#8217;
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with `backticks' -style single quotes
 *   translated into HTML curly quote entities.
 */
function EducateSingleBackticks($_) {
  $_ = str_replace(array("`", "'"), array('&#8216;', '&#8217;'), $_);
  return $_;
}

/**
 * Example input:  `Isn't this fun?'
 * Example output: &#8216;Isn&#8217;t this fun?&#8217;
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with each instance of "--" translated to
 *   an em-dash HTML entity.
 */
function EducateDashes($_) {
  $_ = str_replace('--', '&#8212;', $_);
  return $_;
}

/**
 * EducateDashesOldSchool.
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with each instance of "--" translated to
 *   an en-dash HTML entity, and each "---" translated to
 *   an em-dash HTML entity.
 */
function EducateDashesOldSchool($_) {
  $_ = str_replace(array("---", "--"), array('&#8212;', '&#8211;'), $_);
  return $_;
}


/**
 * EducateDashesOldSchoolInverted.
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with each instance of "--" translated to an em-dash HTML
 *   entity, and each "---" translated to an en-dash HTML entity. Two
 *   reasons why: First, unlike the en- and em-dash syntax supported by
 *   EducateDashesOldSchool(), it's compatible with existing entries written
 *   before SmartyPants 1.1, back when "--" was only used for em-dashes.
 *   Second, em-dashes are more common than en-dashes, and so it sort of makes
 *   sense that the shortcut should be shorter to type. (Thanks to Aaron Swartz
 *   for the idea.)
 */
function EducateDashesOldSchoolInverted($_) {
  // Dashes               en         em.
  $_ = str_replace(array("---", "--"), array('&#8211;', '&#8212;'), $_);
  return $_;
}


/**
 * EducateEllipses.
 * Example input:  Huh...?
 * Example output: Huh&#8230;?
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with each instance of "..." translated to
 *   an ellipsis HTML entity. Also converts the case where
 *   there are spaces between the dots.
 */
function EducateEllipses($_) {
  $_ = str_replace(array("...", ". . ."), '&#8230;', $_);
  return $_;
}


/**
 * StupefyEntities.
 * Example input:  &#8220;Hello &#8212; world.&#8221;
 * Example output: "Hello -- world."
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with each SmartyPants HTML entity translated to
 *   it's ASCII counterpart.
 */
function StupefyEntities($_) {
  // Dashes               en-dash    em-dash.
  $_ = str_replace(array('&#8211;', '&#8212;'), array('-', '--'), $_);

  // Single quote         open       close.
  $_ = str_replace(array('&#8216;', '&#8217;', '&#8218;'), "'", $_);

  // Double quote         open       close.
  $_ = str_replace(array('&#8220;', '&#8221;', '&#8222;'), '"', $_);

  // Ellipsis.
  $_ = str_replace('&#8230;', '...', $_);

  return $_;
}


/**
 * EducateDashesOldSchool.
 *
 *               Escape  Value
 *               ------  -----
 *               \\      &#92;
 *               \"      &#34;
 *               \'      &#39;
 *               \.      &#46;
 *               \-      &#45;
 *               \`      &#96;
 *               \,      &#x2c;
 *
 * @param string $_
 *   Input text.
 *
 * @return string
 *   The string, with after processing the following backslash
 *   escape sequences. This is useful if you want to force a "dumb"
 *   quote or other character to appear.
 */
function ProcessEscapes($_) {

  $_ = str_replace(
    array('\\\\',  '\"',    "\'",      '\.',    '\-',    '\`',    '\,',     '<',    '>'   , '&quot;', '&#039;'),
    array('&#92;', '&#34;', '&#8217;', '&#46;', '&#45;', '&#96;', '&#x2c;', '&lt;', '&gt;', '"',      '\''    ),
    $_
  );

  return $_;
}

/**
 * space_to_nbsp
 *
 * Replaces the space before a "double punctuation mark" (!?:;) with
 * ``&nbsp;``
 * Especially useful in french.
 */
function typogrify_space_to_nbsp($text) {
  $tokens;
  $tokens = _TokenizeHTML($text);

  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $t = preg_replace("/\s([\!\?\:;])/", '&nbsp;$1', $t);
      }
      $result .= $t;
    }
  }
  return $result;
}

/**
 * space_hyphens
 *
 * Replaces a normal dash with em-dash between whitespaces.
 */
function typogrify_space_hyphens($text) {
  $tokens;
  $tokens = _TokenizeHTML($text);

  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with quotes inside tags.
      $result .= $cur_token[1];
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if (!$in_pre) {
        $t = preg_replace("/\s(-{1,3})\s/", '&#8239;—&thinsp;', $t);
      }
      $result .= $t;
    }
  }
  return $result;
}


// _TokenizeHTML is shared between PHP SmartyPants and PHP Markdown.
// We only define it if it is not already defined.
if (!function_exists('_TokenizeHTML')) :
/**
 * Fallback Tokenizer if Markdown not present.
 *
 * @param string $str
 *   String containing HTML markup.
 *
 * @returns array
 *   An array of the tokens comprising the input string. Each token is either
 *   a tag (possibly with nested, tags contained therein, such as
 *   <a href="<MTFoo>" />, or a run of text between tags. Each element of the
 *   array is a two-element array; the first is either 'tag' or 'text'; the
 *   second is the actual value.
 *
 * Regular expression derived from the _tokenize() subroutine in
 * Brad Choate's MTRegex plugin.
 * <http://www.bradchoate.com/past/mtregex.php>
 */
function _TokenizeHTML($str) {

  $index = 0;
  $tokens = array();

  // Comment
  // Processing instruction
  // Regular tags.
  $match = '(?s:<!(?:--.*?--\s*)+>)|' .
    '(?s:<\?.*?\?>)|' .
    '(?:<[/!$]?[-a-zA-Z0-9:]+\b(?>[^"\'>]+|"[^"]*"|\'[^\']*\')*>)';

  $parts = preg_split("{($match)}", $str, -1, PREG_SPLIT_DELIM_CAPTURE);

  foreach ($parts as $part) {
    if (++$index % 2 && $part != '') {
      $tokens[] = array('text', $part);
    }
    else {
      $tokens[] = array('tag', $part);
    }
  }
  return $tokens;
}
endif;

/*
Copyright and License
---------------------

Copyright (c) 2003 John Gruber
<http://daringfireball.net/>
All rights reserved.

Copyright (c) 2004-2005 Michel Fortin
<http://www.michelf.com>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

*  Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

*  Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

*  Neither the name "SmartyPants" nor the names of its contributors may
   be used to endorse or promote products derived from this software
   without specific prior written permission.

This software is provided by the copyright holders and contributors "as is"
and any express or implied warranties, including, but not limited to, the
implied warranties of merchantability and fitness for a particular purpose
are disclaimed. In no event shall the copyright owner or contributors be
liable for any direct, indirect, incidental, special, exemplary, or
consequential damages (including, but not limited to, procurement of
substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in
contract, strict liability, or tort (including negligence or otherwise)
arising in any way out of the use of this software, even if advised of the
possibility of such damage.
*/
