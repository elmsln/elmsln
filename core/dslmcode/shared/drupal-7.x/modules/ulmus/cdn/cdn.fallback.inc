<?php

/**
 * @file
 * Fallback when hook_file_url_alter() is not available (i.e. when the core
 * patch is not installed or when not using Pressflow): use the Parallel
 * module's logic (with some adaptations to be able to use the CDN module's
 * logic (in particular: cdn_file_url_alter()) to alter file URLs via the
 * theme layer.
 * Some of the functions are also used when altering rendered nodes so that
 * their images are served from the CDN.
 */


/**
 * Alter image file URLs in a piece of HTML.
 */
function cdn_html_alter_image_urls(&$html) {
  $url_prefix_regex = _cdn_generate_url_prefix_regex();

  // TRICKY: order matters!

  // Image file URLs of <a> tags that wrap <img> tags.
  $pattern = "#((<a\s+|<a\s+[^>]*\s+)href\s*=\s*[\"|'])($url_prefix_regex)([^\"|^'|^\?]*)()(\?[^\"|^']*)?";
  $pattern .= "("; // Capture everything after the path.
  $pattern .= "([\"|'][^>]*)>"; // End of opening <a> tag.
  $pattern .= "((<img\s+|<img\s+[^>]*\s+)src\s*=\s*[\"|'])([^\"|^'|^\?]*)()(\?[^\"|^']*)?([\"|'])"; // Wrapped <img> tag.
  $pattern .= ")#i";
  _cdn_html_alter_file_url($html, $pattern, 0, 4, 6, 1, 7, 11);

  // Image file URLs in <img> tags.
  $pattern = "#((<img\s+|<img\s+[^>]*\s+)src\s*=\s*[\"|'])($url_prefix_regex)([^\"|^'|^\?]*)()(\?[^\"|^']*)?([\"|'])#i";
  _cdn_html_alter_file_url($html, $pattern, 0, 4, 6, 1, 7);
}

/**
 * Generate the URL prefix regular expression, that supports all possible
 * types of file URLs: root-relative, protocol-relative and absolute URLs.
 */
function _cdn_generate_url_prefix_regex() {
  global $base_url;
  static $url_prefix_regex;

  if (!isset($url_prefix_regex)) {
    $url_prefixes = array(
      preg_quote(base_path()) . '(?!/)',                      // Root-relative URL.
      // Note:  root-relative URL that isn't a protocol-relative URL. The
      // negative lookahead for a trailing slash is relaly only necessary
      // when this site is installed in the document root (i.e. when the base
      // path equals "/"), because this would otherwise match *all* protocol-
      // relative URLs, also those that already point to the CDN.
      preg_quote('//' . $_SERVER['HTTP_HOST'] . base_path()), // Protocol-relative URL.
      preg_quote($base_url . '/'),                            // Absolute URL.
    );

    $regexes = array();
    $farfuture = preg_quote('cdn/farfuture/');
    foreach ($url_prefixes as $url_prefix) {
      $regexes[] = $url_prefix . '(?!' . $farfuture . ')';
    }

    // The URL prefix regex that will match all URLs to the current site,
    // except for those that already point to Far Future expiration URLs.
    $url_prefix_regex = implode('|', $regexes);
  }

  return $url_prefix_regex;
}

/**
 * Alter the file URLs in a piece of HTML given a regexp pattern and some
 * additional parameters.
 *
 * @param &$html
 *   The HTML in which file URLs will be altered.
 * @param $pattern
 *   A regular expression pattern to apply to the subject.
 * @param $search_index
 *   The index of the search string in the array of regexp matches.
 * @param $path_index
 *   The index of the file path in the array of regexp matches.
 * @param $querystring_index
 *   The index of (an optional) query string in the array of regexp matches.
 * @param $prefix
 *   $search_index will be replaced by $prefix, plus the altered file URL,
 *   plus the @suffix. If numeric, then it is assumed to be the index of the
 *   prefix in the array of regexp matches.
 * @param $suffix
 *   See $prefix.
 * @param $comparison_index
 *   The index of a comparison path whose file extension should match the file
 *   extension of the path located at $path_index.
 */
function _cdn_html_alter_file_url(&$html, $pattern, $search_index, $path_index, $querystring_index, $prefix, $suffix, $comparison_index = FALSE) {
  // Find a match against the given pattern.
  preg_match_all($pattern, $html, $matches);

  // Generate replacements to alter file URLs.
  $searches = array();
  $replacements = array();
  for ($i = 0; $i < count($matches[0]); $i++) {
    $search = $matches[$search_index][$i];
    $path = $matches[$path_index][$i];

    $prefix_string = (is_numeric($prefix)) ? $matches[$prefix][$i] : $prefix;
    $suffix_string = (is_numeric($suffix)) ? $matches[$suffix][$i] : $suffix;

    // Compare the filename in the path with that of another index. The file
    // URL only is rewritten if it matches.
    if ($comparison_index) {
      $comparison = $matches[$comparison_index][$i];

      // Calculate length of extension.
      $path_ext_pos = strrpos($path, '.');
      $ext_length = -1 * (strlen($path) - $path_ext_pos);

      if (substr($path, $ext_length) !== substr($comparison, $ext_length)) {
        continue;
      }
    }

    // Store the current path as the old path, then let cdn_file_url_alter()
    // do its magic by invoking all file_url_alter hooks. When the path hasn't
    // changed and is not already root-relative or protocol-relative, then
    // generate a file URL as Drupal core would: prepend the base path.
    $old_path = $path;
    drupal_alter('file_url', $path);
    if ($path == $old_path && drupal_substr($path, 0, 1) != '/' && drupal_substr($path, 0, 2) != '//') {
      $path = base_path() . $path;
    }

    $searches[]     = $search;
    $replacements[] = $prefix_string . $path . $matches[$querystring_index][$i] . $suffix_string;
  }

  // Apply the generated replacements ton the subject.
  $html = str_replace($searches, $replacements, $html);
}
