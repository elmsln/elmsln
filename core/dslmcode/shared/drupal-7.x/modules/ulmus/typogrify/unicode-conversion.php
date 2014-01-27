<?php

/**
 * @file
 * Return the unicode conversion maps.
 */


/**
 * Provides Unicode-mapping.
 *
 * @param string $type
 *   The map type we're looking for, one of 'ligature', 'punctuation',
 *   'arrow' 'nested' or 'all'.
 *
 * @return array
 *   Array of conversions, keyed by the original string.
 */
function unicode_conversion_map($type = 'all') {
  $map = array(
    // See http://www.unicode.org/charts/PDF/UFB00.pdf .
    'ligature' => array(
      'ffi' => '&#xfb03;',
      'ffl' => '&#xfb04;',
      'ff'  => '&#xfb00;',
      'fi'  => '&#xfb01;',
      'fl'  => '&#xfb02;',
      'ij'  => '&#x0133;',
      'IJ'  => '&#x0132;',
      'st'  => '&#xfb06;',
      'ss'  => '&szlig;',
    ),
    // See http:#www.unicode.org/charts/PDF/U2000.pdf .
    'punctuation' => array(
      '...'   => '&#x2026;',
      '..'    => '&#x2025;',
      '. . .' => '&#x2026;',
      '---'   => '&mdash;',
      '--'    => '&ndash;',
    ),
    'fraction' => array(
      '1/4'   => '&frac14;',
      '1/2'   => '&frac12;',
      '3/4'   => '&frac34;',
      '1/3'   => '&#8531;',
      '2/3'   => '&#8532;',
      '1/5'   => '&#8533;',
      '2/5'   => '&#8534;',
      '3/5'   => '&#8535;',
      '4/5'   => '&#8536;',
      '1/6'   => '&#8537;',
      '5/6'   => '&#8538;',
      '1/8'   => '&#8539;',
      '3/8'   => '&#8540;',
      '5/8'   => '&#8541;',
      '7/8'   => '&#8542;',
    ),
    'quotes' => array(
      ',,'       => '&bdquo;',
      '\'\''     => '&rdquo;',
      '&lt;&lt;' => '&laquo;',
      '&gt;&gt;' => '&raquo;',
    ),
    // See http:#www.unicode.org/charts/PDF/U2190.pdf .
    'arrow' => array(
      '-&gt;&gt;' => '&#x21a0;',
      '&lt;&lt;-' => '&#x219e;',
      '-&gt;|'    => '&#x21e5;',
      '|&lt;-'    => '&#x21e4;',
      '&lt;-&gt;' => '&#x2194;',
      '-&gt;'     => '&#x2192;',
      '&lt;-'     => '&#x2190;',
      '&lt;=&gt;' => '&#x21d4;',
      '=&gt;'     => '&#x21d2;',
      '&lt;='     => '&#x21d0;',
    ),
  );

  if ($type == 'all') {
    return array_merge($map['ligature'], $map['arrow'], $map['punctuation'], $map['quotes'], $map['fraction']);
  }
  elseif ($type == 'nested') {
    return $map;
  }
  else {
    return $map[$type];
  }
}

/**
 * Perform character conversion.
 *
 * @param string $text
 *   Text to be parsed.
 * @param array $characters_to_convert
 *   Array of ASCII characters to convert.
 *
 * @return string
 *   The result of the conversion.
 */
function convert_characters($text, $characters_to_convert) {
  if (($characters_to_convert == NULL) || (count($characters_to_convert) < 1)) {
    // Do nothing.
    return $text;
  }

  // Get ascii to unicode mappings.
  $unicode_map = unicode_conversion_map();

  foreach ($characters_to_convert as $ascii_string) {
    $unicode_strings[] = $unicode_map[$ascii_string];
  }

  $tokens = _TokenizeHTML($text);
  $result = '';
  // Keep track of when we're inside <pre> or <code> tags.
  $in_pre = 0;
  foreach ($tokens as $cur_token) {
    if ($cur_token[0] == "tag") {
      // Don't mess with text inside tags, <pre> blocks, or <code> blocks.
      $result .= $cur_token[1];
      // Get the tags to skip regex from SmartyPants.
      if (preg_match(SMARTYPANTS_TAGS_TO_SKIP, $cur_token[1], $matches)) {
        $in_pre = isset($matches[1]) && $matches[1] == '/' ? 0 : 1;
      }
    }
    else {
      $t = $cur_token[1];
      if ($in_pre == 0) {
        $t = ProcessEscapes($t);
        $t = str_replace($characters_to_convert, $unicode_strings, $t);
      }
      $result .= $t;
    }
  }
  return $result;
}


// _TokenizeHTML is shared between PHP SmartyPants and PHP Markdown.
// We're borrowing it for Typogrify.module, too
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
