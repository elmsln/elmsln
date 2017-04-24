<?php

/**
 * @file
 * Advanced aggregation relocate module.
 */

/**
 * Implements hook_advagg_get_css_aggregate_contents_alter().
 */
function advagg_relocate_advagg_get_css_aggregate_contents_alter(&$data, $files, $aggregate_settings) {
  // Set variables if needed.
  if (!isset($aggregate_settings['variables']['advagg_relocate_css_inline_import'])) {
    $aggregate_settings['variables']['advagg_relocate_css_inline_import'] = variable_get('advagg_relocate_css_inline_import', ADVAGG_RELOCATE_CSS_INLINE_IMPORT);
  }

  // Do nothing if this is disabled.
  if (!$aggregate_settings['variables']['advagg_relocate_css_inline_import']) {
    return;
  }

  if (strpos($data, '@import') !== FALSE) {
    // Set values that will be used when preg_replace_callback is ran.
    _advagg_relocate_callback(array(), $files, $aggregate_settings);

    // Replace external import statements with the contents of them.
    $data = preg_replace_callback('%@import\s*+(?:url\(\s*+)?+[\'"]?+((?:http:\/\/|https:\/\/|\/\/)(?:[^\'"()\s]++))[\'"]?+\s*+\)?+\s*+;%i', '_advagg_relocate_callback', $data);
  }
}

/**
 * Verifies that the external CSS file is from a domain we allow for inlining.
 *
 * @param string $url
 *   The full URL of the css file.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return bool
 *   TRUE if the URL can be inlined.
 */
function advagg_relocate_check_domain_of_url($url, array $aggregate_settings) {
  // Bail if the host or path and query string are empty.
  $parse = @parse_url($url);
  if (empty($parse)
    || empty($parse['host'])
    || (empty($parse['path']) && empty($parse['query']))
  ) {
    return FALSE;
  }

  // Bail if the host doesn't match one of the listed domains.
  if (!isset($aggregate_settings['variables']['advagg_relocate_css_file_domains'])) {
    $aggregate_settings['variables']['advagg_relocate_css_file_domains'] = variable_get('advagg_relocate_css_file_domains', ADVAGG_RELOCATE_CSS_FILE_DOMAINS);
  }
  if (strpos($aggregate_settings['variables']['advagg_relocate_css_file_domains'], $parse['host']) === FALSE) {
    return FALSE;
  }
  return TRUE;
}

/**
 * Gets external CSS files and puts the contents of it in the aggregate.
 *
 * @param array $matches
 *   Array of matched items from preg_replace_callback().
 * @param array $files
 *   List of files with the media type.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return string
 *   Contents of the import statement.
 */
function _advagg_relocate_callback(array $matches = array(), array $files = array(), array $aggregate_settings = array()) {
  // Store values for preg_replace_callback callback.
  $_args = &drupal_static(__FUNCTION__, array());
  if (!empty($files)) {
    $_args['files'] = $files;
  }
  if (!empty($aggregate_settings)) {
    $_args['aggregate_settings'] = $aggregate_settings;
  }
  // Short circuit if no matches were passed in.
  if (empty($matches)) {
    return '';
  }

  // Bail if not matched.
  if (empty($matches[1])) {
    return $matches[0];
  }

  // Check URL.
  if (!advagg_relocate_check_domain_of_url($matches[1], $_args['aggregate_settings'])) {
    return $matches[0];
  }

  // Check per file settings.
  if (!isset($_args['aggregate_settings']['variables']['advagg_relocate_css_file_settings'])) {
    $_args['aggregate_settings']['variables']['advagg_relocate_css_file_settings'] = variable_get('advagg_relocate_css_file_settings', array());
  }
  foreach ($_args['files'] as $filename => $values) {
    $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $filename);
    if (isset($_args['aggregate_settings']['variables']['advagg_relocate_css_file_settings'][$form_api_filename])) {
      foreach ($_args['aggregate_settings']['variables']['advagg_relocate_css_file_settings'][$form_api_filename] as $key => $value) {
        if ($key !== $value && $key === $matches[1]) {
          // Do not replace.
          return $matches[0];
        }
      }
    }
  }

  $font_faces = advagg_relocate_get_remote_data($matches[1], $_args['aggregate_settings']);
  return advagg_relocate_font_face_parser($font_faces);

}

/**
 * Given an array of font data output a new CSS string.
 *
 * @param array $font_faces
 *   Array of font data.
 *
 * @return string
 *   String of CSS font data.
 */
function advagg_relocate_font_face_parser(array $font_faces) {
  $new_css = '';
  foreach ($font_faces as $values => $src) {
    $output = '';
    $output .= str_replace('; ', ";\n", $values);
    if (isset($src['eot'])) {
      $output .= "src: {$src['eot']};\n";
    }
    $output .= 'src:';
    foreach ($src as $key => $location) {
      if (is_numeric($key)) {
        $output .= "$location,";
      }
    }
    if (isset($src['eot'])) {
      $src['eot'] = str_replace('.eot', '.eot?#iefix', $src['eot']);
      $output .= "{$src['eot']} format('embedded-opentype'),";
    }
    if (isset($src['woff2'])) {
      $output .= "{$src['woff2']},";
    }
    if (isset($src['woff'])) {
      $output .= "{$src['woff']},";
    }
    if (isset($src['ttf'])) {
      $output .= "{$src['ttf']},";
    }
    if (isset($src['svg'])) {
      $output .= "{$src['svg']},";
    }
    $output = str_replace(array('),l', '),u'), array("),\nl", "),\nu"), trim($output, ',') . ';');
    $new_css .= "@font-face {\n$output\n}\n";
  }

  return $new_css;
}

/**
 * Gets external CSS files and puts the contents of it in the aggregate.
 *
 * @param string $url
 *   URL of the CSS file to import.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return array
 *   Array of font data.
 */
function advagg_relocate_get_remote_data($url, array $aggregate_settings) {
  // Set settings if needed.
  if (!isset($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers'])) {
    $defaults = array(
      'woff2' => 'woff2',
      'woff' => 'woff',
      'ttf' => 'ttf',
    );
    $aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers'] = variable_get('advagg_relocate_css_inline_import_browsers', $defaults);
  }

  // Set arguments for drupal_http_request().
  $options = array(
    'headers' => array(
      'Accept-Encoding' => 'gzip, deflate',
      'Connection' => 'close',
      'Referer' => $GLOBALS['base_root'] . request_uri(),
    ),
    'timeout' => 8,
    'version' => '1.0',
  );
  if (function_exists('brotli_uncompress')) {
    $options['headers']['Accept-Encoding'] .= ', br';
  }

  // Build CID.
  $aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers'] = array_filter($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']);
  $fonts = implode(',', $aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']);
  $cid = "advagg_relocate_css_inline_import:$fonts:$url";

  // Try local cache.
  $cached_data = cache_get($cid, 'cache_advagg_info');
  if (!empty($cached_data->data[0])) {
    if ($cached_data->expire >= REQUEST_TIME) {
      return $cached_data->data[0];
    }
    else {
      // Set header for 304 response.
      // $options['headers']['If-None-Match'] = $response->headers['etag'];.
      $options['headers']['If-Modified-Since'] = gmdate('D, d M Y H:i:s T', $cached_data->created);
    }
  }

  // Get external data.
  $responses = array();
  if (module_exists('httprl')) {
    // Get ttf.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['ttf'])) {
      $options['#font-type'] = 'ttf';
      httprl_request($url . '#ttf', $options);
    }

    // Get eot.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['eot'])) {
      $options['#font-type'] = 'eot';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (Windows; U; MSIE 7.0; Windows NT 6.0; en-US)';
      httprl_request($url . '#eot', $options);
    }

    // Get svg.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['svg'])) {
      $options['#font-type'] = 'svg';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (iPad; U; CPU OS 3_2_2 like Mac OS X; nl-nl) AppleWebKit/531.21.10 (KHTML, like Gecko) Version/4.0.4 Mobile/7B500 Safari/531.21.10';
      httprl_request($url . '#svg', $options);
    }

    // Get woff.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['woff'])) {
      $options['#font-type'] = 'woff';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (Windows; U; MSIE 9.0; Windows NT 9.0; en-US)';
      httprl_request($url . '#woff', $options);
    }

    // Get woff2.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['woff2'])) {
      $options['#font-type'] = 'woff2';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';
      httprl_request($url . '#woff2', $options);
    }

    $responses = httprl_send_request();
  }
  else {
    // Get ttf.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['ttf'])) {
      $options['#font-type'] = 'ttf';
      $responses['ttf'] = drupal_http_request($url . '#ttf', $options);
    }

    // Get eot.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['eot'])) {
      $options['#font-type'] = 'eot';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (Windows; U; MSIE 7.0; Windows NT 6.0; en-US)';
      $responses['eot'] = drupal_http_request($url . '#eot', $options);
    }

    // Get svg.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['svg'])) {
      $options['#font-type'] = 'svg';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (iPad; U; CPU OS 3_2_2 like Mac OS X; nl-nl) AppleWebKit/531.21.10 (KHTML, like Gecko) Version/4.0.4 Mobile/7B500 Safari/531.21.10';
      $responses['svg'] = drupal_http_request($url . '#svg', $options);
    }

    // Get woff.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['woff'])) {
      $options['#font-type'] = 'woff';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (Windows; U; MSIE 9.0; Windows NT 9.0; en-US)';
      $responses['woff'] = drupal_http_request($url . '#woff', $options);
    }

    // Get woff2.
    if (!empty($aggregate_settings['variables']['advagg_relocate_css_inline_import_browsers']['woff2'])) {
      $options['#font-type'] = 'woff2';
      $options['headers']['User-Agent'] = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';
      $responses['woff2'] = drupal_http_request($url . '#woff2', $options);
    }
  }

  // Parse data.
  $font_faces = array();
  $ttl = 0;
  $now = REQUEST_TIME;
  foreach ($responses as $key => $response) {
    if ($response->code == 304 && !empty($cached_data->data[0])) {
      // This might need to be better handled in the future.
      return $cached_data->data[0];
    }

    // Set the font type if not set.
    if (empty($response->options['#font-type'])) {
      if (!is_numeric($key)) {
        $response->options['#font-type'] = $key;
      }
      else {
        continue;
      }
    }

    if ($response->code != 200
      && $response->code != 201
      && $response->code != 202
      && $response->code != 206
    ) {
      return FALSE;
    }
    if (empty($response->data)) {
      return FALSE;
    }

    // Uncompress.
    if (!empty($response->headers['content-encoding'])
      && !empty($response->data)
      && !isset($response->chunk_size)
      && ($response->headers['content-encoding'] === 'gzip'
        || $response->headers['content-encoding'] === 'deflate'
        || $response->headers['content-encoding'] === 'br'
    )) {
      // Do the first level of decoding if not already done.
      if ($response->headers['content-encoding'] === 'gzip') {
        $response->data = @gzinflate(substr($response->data, 10));
      }
      elseif ($response->headers['content-encoding'] === 'deflate') {
        $response->data = @gzinflate($response->data);
      }
      elseif ($response->headers['content-encoding'] === 'br' && is_callable('brotli_uncompress')) {
        $response->data = @brotli_uncompress($response->data);
      }
    }

    // Get ttl.
    if (isset($response->headers['expires'])) {
      $expires = strtotime($response->headers['expires']);
      if (isset($response->headers['date'])) {
        $now = max($now, strtotime($response->headers['date']));
      }
      $ttl = max($ttl, $expires - $now);
    }
    if (isset($response->headers['cache-control'])) {
      $cache_control_array = advagg_relocate_parse_cache_control($response->headers['cache-control']);
      if (isset($cache_control_array['max-age']) && is_numeric($cache_control_array['max-age'])) {
        $ttl = max($ttl, $cache_control_array['max-age']);
      }
      if (isset($cache_control_array['s-maxage']) && is_numeric($cache_control_array['s-maxage'])) {
        $ttl = max($ttl, $cache_control_array['s-maxage']);
      }
    }

    // Parse the CSS.
    $font_face = advagg_relocate_parse_css_font_face(
      $response->data,
      array('font-family', 'font-style', 'font-weight', 'src'),
      $response->options['#font-type']
    );

    // Format into a better data structure and combine.
    foreach ($font_face as $k => $values) {
      if (!isset($font_faces[$k])) {
        $font_faces[$k] = $font_face[$k];
        continue;
      }

      foreach ($values as $index => $value) {
        if (!in_array($value, $font_faces[$k])) {
          if ($index === $response->options['#font-type']) {
            $font_faces[$k][$index] = $values[$index];
          }
          else {
            $font_faces[$k][] = $values[$index];
          }
        }
      }
    }
  }

  // Save data to the cache.
  if (!empty($font_faces)) {
    cache_set($cid, array($font_faces, $responses), 'cache_advagg_info', REQUEST_TIME + $ttl);
  }
  return $font_faces;
}

/**
 * Parse the cache-control string into a key value array.
 *
 * @param string $cache_control
 *   The cache-control string.
 *
 * @return array
 *   Returns a key value array.
 */
function advagg_relocate_parse_cache_control($cache_control) {
  $cache_control_array = explode(',', $cache_control);
  $cache_control_array = array_map('trim', $cache_control_array);
  $cache_control_parsed = array();
  foreach ($cache_control_array as $value) {
    if (strpos($value, '=') !== FALSE) {
      $temp = array();
      parse_str($value, $temp);
      $cache_control_parsed += $temp;
    }
    else {
      $cache_control_parsed[$value] = TRUE;
    }
  }
  return $cache_control_parsed;
}

/**
 * Parse the font family string into a structured array.
 *
 * @param string $css_string
 *   The raw css string.
 * @param array $properties
 *   The css properties to get.
 * @param string $type
 *   The type of font file.
 *
 * @return array
 *   Returns a key value array.
 */
function advagg_relocate_parse_css_font_face($css_string, array $properties, $type) {
  // Get the CSS that contains a font-family rule.
  $length = strlen($css_string);
  $property_position = 0;
  $lower = strtolower($css_string);

  $attributes = array();
  foreach ($properties as $property) {
    while (($property_position = strpos($lower, $property, $property_position)) !== FALSE) {
      // Find the start of the values for the property.
      $start_of_values = strpos($css_string, ':', $property_position);
      // Get the property at this location of the css.
      $property_in_loop = trim(substr($css_string, $property_position, ($start_of_values - $property_position)));

      // Make sure this property is one of the ones we're looking for.
      if ($property_in_loop !== $property) {
        $property_position += strlen($property);
        continue;
      }

      // Get position of last closing bracket plus 1 (start of this section).
      $start = strrpos($css_string, '}', -($length - $property_position));
      if ($start === FALSE) {
        // Property is in the first selector and a declaration block (full rule
        // set).
        $start = 0;
      }
      else {
        // Add one to start after the }.
        $start++;
      }

      // Get closing bracket (end of this section).
      $end = strpos($css_string, '}', $property_position);
      if ($end === FALSE) {
        // The end is the end of this file.
        $end = $length;
      }

      // Get closing ; in order to get end of the declaration of the property.
      $declaration_end_a = strpos($css_string, ';', $property_position);
      $declaration_end_b = strpos($css_string, '}', $property_position);
      if ($declaration_end_a === FALSE) {
        $declaration_end = $declaration_end_b;
      }
      else {
        $declaration_end = min($declaration_end_a, $declaration_end_b);
      }
      if ($declaration_end > $end) {
        $declaration_end = $end;
      }
      // Add one in order to capture the } when we ge the full rule set.
      $end++;
      // Advance position for the next run of the while loop.
      $property_position = $end;

      // Get values assigned to this property.
      $values_string = substr($css_string, $start_of_values + 1, $declaration_end - ($start_of_values + 1));
      // Parse values string into an array of values.
      $values_array = explode(',', $values_string);
      $values_array = array_map('trim', $values_array);

      foreach ($values_array as $key => $value) {
        if (stripos($value, "'$type'") !== FALSE
          || stripos($value, ".$type") !== FALSE
        ) {
          unset($values_array[$key]);
          $values_array[$type] = $value;
        }
      }
      $attributes[$property][] = $values_array;
    }
  }

  // Make sure src is the last one.
  $temp = $attributes['src'];
  unset($attributes['src']);
  $attributes['src'] = $temp;

  // Parse attributes into an output array.
  $temp = array();
  $output = array();
  foreach ($attributes as $property => $values) {
    foreach ($values as $key => $value) {
      if ($property !== 'src') {

        $value = implode(',', $value);
        if (!isset($temp[$key])) {
          $temp[$key] = '';
        }
        $temp[$key] .= "$property: $value; ";
      }
      else {
        $output[$temp[$key]] = $value;
      }
    }
  }

  return $output;
}
