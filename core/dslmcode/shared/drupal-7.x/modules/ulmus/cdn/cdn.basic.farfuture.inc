<?php

/**
 * @file
 * Far Future expiration setting for basic mode.
 */


//----------------------------------------------------------------------------
// Menu system callbacks.

function cdn_basic_farfuture_download($token, $ufi, $path) {
  // Validate the token to make sure this request originated from CDN.
  $path_info = pathinfo($path);
  $sec_token = drupal_hmac_base64($ufi . $path_info['filename'], drupal_get_private_key() . drupal_get_hash_salt());
  if ($token != $sec_token) {
    header('HTTP/1.1 403 Forbidden');
    exit();
  }

  // Disallow downloading of files that are also not allowed to be downloaded
  // by Drupal's .htaccess file.
  if (preg_match("/\.(engine|inc|info|install|make|module|profile|test|po|sh|php([3-6])?|phtml|.*sql|theme|tpl(\.php)?|xtmpl)$|^(\..*|Entries.*|Repository|Root|Tag|Template)$/", $path)) {
    header('HTTP/1.1 403 Forbidden');
    exit();
  }

  if (!file_exists($path)) {
    watchdog(
      'cdn',
      'CDN Far Future 404: %file.',
      array('%file' => $path),
      WATCHDOG_ALERT
    );
    header('HTTP/1.1 404 Not Found');
    exit();
  }

  // Remove some useless/unwanted headers.
  $remove_headers = explode("\n", CDN_BASIC_FARFUTURE_REMOVE_HEADERS);
  $current_headers = array();
  foreach (headers_list() as $header) {
    $parts = explode(':', $header);
    $current_headers[] = $parts[0];
  }
  foreach ($remove_headers as $header) {
    if (in_array($header, $current_headers)) {
      // header_remove() only exists in PHP >=5.3
      if (function_exists('header_remove')) {
        header_remove($header);
      }
      else {
        // In PHP <5.3, we cannot remove headers. At least shorten them to save
        // every byte possible and to stop leaking information needlessly.
        header($header . ':');
      }
    }
  }

  // Remove all previously set Cache-Control headers, because we're going to
  // override it. Since multiple Cache-Control headers might have been set,
  // simply setting a new, overriding header isn't enough: that would only
  // override the *last* Cache-Control header. Yay for PHP!
  if (function_exists('header_remove')) {
    header_remove('Cache-Control');
  }
  else {
    header("Cache-Control:");
    header("Cache-Control:");
  }

  // Default caching rules: no caching/immediate expiration.
  header("Cache-Control: private, must-revalidate, proxy-revalidate");
  header("Expires: " . gmdate("D, d M Y H:i:s", time() - 86400) . "GMT");

  // Instead of being powered by PHP, tell the world this resource was powered
  // by the CDN module!
  header("X-Powered-By: Drupal CDN module");
  // Instruct intermediate HTTP caches to store both a compressed (gzipped)
  // and uncompressed version of the resource.
  header("Vary: Accept-Encoding");
  // Determine the content type.
  header("Content-Type: " . _cdn_basic_farfuture_get_mimetype(basename($path)));
  // Support partial content requests.
  header("Accept-Ranges: bytes");
  // Browsers that implement the W3C Access Control specification might refuse
  // to use certain resources such as fonts if those resources violate the
  // same-origin policy. Send a header to explicitly allow cross-domain use of
  // those resources. (This is called Cross-Origin Resource Sharing, or CORS.)
  header("Access-Control-Allow-Origin: *");

  // If the extension of the file that's being served is one of the far future
  // extensions (by default: images, fonts and flash content), then cache it
  // in the far future.
  $farfuture_extensions  = variable_get(CDN_BASIC_FARFUTURE_EXTENSIONS_VARIABLE, CDN_BASIC_FARFUTURE_EXTENSIONS_DEFAULT);
  $extension = drupal_strtolower(pathinfo($path, PATHINFO_EXTENSION));
  if (in_array($extension, explode("\n", $farfuture_extensions))) {
    // Remove all previously set Cache-Control headers, because we're going to
    // override it. Since multiple Cache-Control headers might have been set,
    // simply setting a new, overriding header isn't enough: that would only
    // override the *last* Cache-Control header. Yay for PHP!
    if (function_exists('header_remove')) {
      header_remove('Cache-Control');
    }
    else {
      header("Cache-Control:");
      header("Cache-Control:");
    }
    // Set a far future Cache-Control header (480 weeks), which prevents
    // intermediate caches from transforming the data and allows any
    // intermediate cache to cache it, since it's marked as a public resource.
    header("Cache-Control: max-age=290304000, no-transform, public");
    // Set a far future Expires header. The maximum UNIX timestamp is somewhere
    // in 2038. Set it to a date in 2037, just to be safe.
    header("Expires: Tue, 20 Jan 2037 04:20:42 GMT");
    // Pretend the file was last modified a long time ago in the past, this will
    // prevent browsers that don't support Cache-Control nor Expires headers to
    // still request a new version too soon (these browsers calculate a
    // heuristic to determine when to request a new version, based on the last
    // time the resource has been modified).
    // Also see http://code.google.com/speed/page-speed/docs/caching.html.
    header("Last-Modified: Wed, 20 Jan 1988 04:20:42 GMT");
  }

  // GET requests with an "Accept-Encoding" header that lists "gzip".
  if (isset($_SERVER['HTTP_ACCEPT_ENCODING']) && strpos($_SERVER['HTTP_ACCEPT_ENCODING'], 'gzip') !== FALSE) {
    // Only send gzipped files for some file extensions (it doesn't make sense
    // to gzip images, for example).
    if (in_array($extension, explode("\n", CDN_BASIC_FARFUTURE_GZIP_EXTENSIONS))) {
      // Ensure a gzipped version of the file is stored on disk, instead of
      // gzipping the file on every request.
      $gzip_path = drupal_realpath('public://') . '/' . CDN_BASIC_FARFUTURE_GZIP_DIRECTORY . "/$path.$ufi.gz";
      if (!file_exists($gzip_path)) {
        _cdn_basic_farfuture_create_directory_structure(dirname($gzip_path));
        file_put_contents($gzip_path, gzencode(file_get_contents($path), 9));
      }
      // Make sure zlib.output_compression does not gzip our gzipped output.
      ini_set('zlib.output_compression', '0');
      // Prepare for gzipped output.
      header("Content-Encoding: gzip");
      $path = $gzip_path;
    }
  }

  // Conditional GET requests (i.e. with If-Modified-Since header).
  if (isset($_SERVER['HTTP_IF_MODIFIED_SINCE'])) {
    // All files served by this function are designed to expire in the far
    // future. Hence we can simply always tell the client the requested file
    // was not modified.
    header("HTTP/1.1 304 Not Modified");
  }
  // "Normal" GET requests.
  else {
    _cdn_transfer_file($path);
  }

  exit();
}

function cdn_basic_farfuture_reverseproxy_test($token) {
  $reference_token = variable_get('cdn_reverse_proxy_test');
  if ($reference_token === FALSE || $token != $reference_token) {
    header('HTTP/1.1 403 Forbidden');
    exit();
  }

  print REQUEST_TIME . '-' . md5(rand());
  exit();
}


//----------------------------------------------------------------------------
// Public functions.

/**
 * Get the UFI method for the file at a path.
 *
 * @param $path
 *   The path to get UFI method for the file at the given path.
 * @param $mapping
 *   The UFI mapping to use.
 */

function cdn_basic_farfuture_get_ufi_method($path, $mapping) {
  // Determine which UFI method should be used. Note that we keep on trying to
  // find another method until the end: the order of rules matters!
  // However, specificity also matters. The directory pattern "foo/bar/*"
  // should *always* override the less specific pattern "foo/*".
  $ufi_method = FALSE;
  $current_specificity = 0;
  foreach (array_keys($mapping) as $directory) {
    if (drupal_match_path($path, $directory)) {
      // Parse the file extension from the given path; convert it to lower case.
      $file_extension = drupal_strtolower(pathinfo($path, PATHINFO_EXTENSION));

      // Based on the file extension, determine which key should be used to find
      // the CDN URLs in the mapping lookup table, if any.
      $extension = NULL;
      if (array_key_exists($file_extension, $mapping[$directory])) {
        $extension = $file_extension;
      }
      elseif (array_key_exists('*', $mapping[$directory])) {
        $extension = '*';
      }

      // If a matching extension was found, assign the corresponding UFI method.
      if (isset($extension)) {
        $specificity = $mapping[$directory][$extension]['specificity'];
        if ($specificity > $current_specificity) {
          $ufi_method = $mapping[$directory][$extension]['ufi method'];
          $current_specificity = $specificity;
        }
      }
    }
  }

  // Fall back to the default UFI method in case no UFI method is defined by
  // the user.
  if ($ufi_method === FALSE) {
    $ufi_method = CDN_BASIC_FARFUTURE_UNIQUE_IDENTIFIER_DEFAULT;
  }

  return $ufi_method;
}

/**
 * Get the UFI (Unique File Identifier) for the file at a path.
 *
 * @param $path
 *   The path to get a UFI for.
 */
function cdn_basic_farfuture_get_identifier($path) {
  static $ufi_info;
  static $mapping;

  // Gather all unique file identifier info.
  if (!isset($ufi_info)) {
    $ufi_info = module_invoke_all('cdn_unique_file_identifier_info');
  }

  // We only need to parse the textual CDN mapping once into a lookup table.
  if (!isset($mapping)) {
    $mapping = _cdn_basic_farfuture_parse_raw_mapping(variable_get(CDN_BASIC_FARFUTURE_UNIQUE_IDENTIFIER_MAPPING_VARIABLE, CDN_BASIC_FARFUTURE_UNIQUE_IDENTIFIER_MAPPING_DEFAULT));
  }

  $ufi_method = cdn_basic_farfuture_get_ufi_method($path, $mapping);

  $prefix = $ufi_info[$ufi_method]['prefix'];
  if (isset($ufi_info[$ufi_method]['value'])) {
    $value = $ufi_info[$ufi_method]['value'];
  }
  else {
    $callback = $ufi_info[$ufi_method]['callback'];
    $value = call_user_func_array($callback, array($path));
  }

  return "$prefix:$value";
}


//----------------------------------------------------------------------------
// Private functions.

/**
 * Parse the raw (textual) mapping into a lookup table, where the key is the
 * file extension and the value is a list of CDN URLs that serve the file.
 *
 * @param $mapping_raw
 *   A raw (textual) mapping.
 * @return
 *   The corresponding mapping lookup table.
 */
function _cdn_basic_farfuture_parse_raw_mapping($mapping_raw) {
  $mapping = array();

  if (!empty($mapping_raw)) {
    $lines = preg_split("/[\n\r]+/", $mapping_raw, -1, PREG_SPLIT_NO_EMPTY);
    foreach ($lines as $line) {
      // Parse this line. It may or may not limit the CDN URL to a list of
      // file extensions.
      $parts = explode('|', $line);
      $directories = explode(':', $parts[0]);
      $specificity = 0;

      // There may be 2 or 3 parts:
      // - part 1: directories
      // - part 2: file extensions (optional)
      // - part 3: unique file identifier method
      if (count($parts) == 2) {
        $extensions = array('*'); // Use the asterisk as a wildcard.
        $ufi_method = drupal_strtolower(trim($parts[1]));
      }
      elseif (count($parts) == 3) {
        // Convert to lower case, remove periods, whitespace and split on ' '.
        $extensions = explode(' ', trim(str_replace('.', '', drupal_strtolower($parts[1]))));
        $ufi_method = drupal_strtolower(trim($parts[2]));
      }

      // Create the mapping lookup table.
      foreach ($directories as $directory) {
        $directory_specificity = 10 * count(explode('/', $directory));
        foreach ($extensions as $extension) {
          $extension_specificity = ($extension == '*') ? 0 : 1;

          $mapping[$directory][$extension] = array(
            'ufi method'  => $ufi_method,
            'specificity' => $directory_specificity + $extension_specificity,
          );
        }
      }
    }
  }

  return $mapping;
}

/**
 * Variant of Drupal's file_transfer(), based on
 *  http://www.thomthom.net/blog/2007/09/php-resumable-download-server/
 * to support ranged requests as well.
 *
 * Note: ranged requests that request multiple ranges are not supported. They
 * are responded to with a 416. See
 * http://www.w3.org/Protocols/rfc2616/rfc2616-sec19.html
 */
function _cdn_transfer_file($path) {
  $fp = @fopen($path, 'rb');

  $size   = filesize($path); // File size
  $length = $size;           // Content length
  $start  = 0;               // Start byte
  $end    = $size - 1;       // End byte

  // In case of a range request, seek within the file to the correct location.
  if (isset($_SERVER['HTTP_RANGE'])) {
    $c_start = $start;
    $c_end   = $end;

    // Extract the string containing the requested range.
    list(, $range) = explode('=', $_SERVER['HTTP_RANGE'], 2);

    // If the client requested multiple ranges, repond with a 416.
    if (strpos($range, ',') !== FALSE) {
      header('HTTP/1.1 416 Requested Range Not Satisfiable');
      header("Content-Range: bytes $start-$end/$size");
      exit();
    }

    // Case "Range: -n": final n bytes are requested.
    if ($range[0] == '-') {
      $c_start = $size - substr($range, 1);
    }
    // Case "Range: m-n": bytes m through n are requested. When n is empty or
    // non-numeric, n is the last byte.
    else {
      $range  = explode('-', $range);
      $c_start = intval($range[0]);
      $c_end   = (isset($range[1]) && is_numeric($range[1])) ? intval($range[1]) : $size;
    }
    // Minor normalization: end bytes can not be larger than $end.
    $c_end = ($c_end > $end) ? $end : $c_end;

    // If the requested range is not valid, respond with a 416.
    if ($c_start > $c_end || $c_start > $end || $c_end > $end) {
      header('HTTP/1.1 416 Requested Range Not Satisfiable');
      header("Content-Range: bytes $start-$end/$size");
      exit();
    }

    $start  = $c_start;
    $end    = $c_end;
    $length = $end - $start + 1;
    fseek($fp, $start);

    // The ranged request is valid and will be performed, respond with a 206.
    header('HTTP/1.1 206 Partial Content');
    header("Content-Range: bytes $start-$end/$size");
  }
  header("Content-Length: $length");

  // Start buffered download. Prevent reading too far for a ranged request.
  $buffer = 1024 * 8;
  while (!feof($fp) && ($p = ftell($fp)) <= $end) {
    if ($p + $buffer > $end) {
      $buffer = $end - $p + 1;
    }
    set_time_limit(0); // Reset time limit for big files.
    echo fread($fp, $buffer);
    flush(); // Free up memory, to prevent triggering PHP's memory limit.
  }
  fclose($fp);
}

/**
 * Determine an Internet Media Type, or MIME type from a filename.
 * Borrowed from Drupal 7.
 *
 * @param $path
 *   A string containing the file path.
 * @return
 *   The internet media type registered for the extension or
 *   application/octet-stream for unknown extensions.
 */
function _cdn_basic_farfuture_get_mimetype($path) {
  static $mapping;
  if (!isset($mapping)) {
    // The default file map, defined in file.mimetypes.inc is quite big.
    // We only load it when necessary.
    include_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';
    $mapping = file_mimetype_mapping();
  }

  $extension = '';
  $file_parts = explode('.', basename($path));

  // Remove the first part: a full filename should not match an extension.
  array_shift($file_parts);

  // Iterate over the file parts, trying to find a match.
  // For my.awesome.image.jpeg, we try:
  //   - jpeg
  //   - image.jpeg, and
  //   - awesome.image.jpeg
  while ($additional_part = array_pop($file_parts)) {
    $extension = drupal_strtolower($additional_part . ($extension ? '.' . $extension : ''));
    if (isset($mapping['extensions'][$extension])) {
      return $mapping['mimetypes'][$mapping['extensions'][$extension]];
    }
  }

  return 'application/octet-stream';
}

/**
 * Perform a nested HTTP request to generate a file.
 *
 * @param $path
 *   A path relative to the Drupal root (not urlencoded!) to the file that
 *   should be generated.
 * @return
 *   Whether the file was generated or not.
 */
function _cdn_basic_farfuture_generate_file($path) {
  // Check if there's a file to generate in the first place!
  if (!menu_get_item($path)) {
    return FALSE;
  }

  // While it should already be impossible to enter recursion because of the
  // above menu system check, we still want to detect this just to be safe.
  // This really can only happen if a file is missing and we try to generate
  // it and the request to generate the file itself triggers a 404, which
  // again references the file that is missing, and would thus again trigger a
  // 404, etc.
  // @see http://drupal.org/node/1417616#comment-5694960
  if (request_uri() == base_path() . $path) {
    watchdog('cdn', 'Recursion detected for %file!', array('%file' => $path), WATCHDOG_ALERT);
    header('HTTP/1.1 404 Not Found');
    exit();
  }

  $url = $GLOBALS['base_url'] . '/' . drupal_encode_path($path);

  $headers = array(
    // Make sure we hit the server and do not end up with a stale
    // cached version.
    'Cache-Control' => 'no-cache',
    'Pragma'        => 'no-cache',
  );
  drupal_http_request($url, array('headers' => $headers));

  $exists = file_exists($path);
  watchdog(
    'cdn',
    'Nested HTTP request to generate %file: %result (URL: %url, time: !time).',
    array(
      '!time'   => (int) $_SERVER['REQUEST_TIME'],
      '%file'   => $path,
      '%url'    => $url,
      '%result' => $exists ? 'success' : 'failure',
    ),
    $exists ? WATCHDOG_NOTICE : WATCHDOG_CRITICAL
  );
  return $exists;
}

/**
 * file_check_directory() doesn't support creating directory trees.
 */
function _cdn_basic_farfuture_create_directory_structure($path) {
  // Create the directory structure in which the file will be stored. Because
  // it's nested, file_check_directory() can't do this in one run.
  $parts = explode('/', $path);
  for ($i = 0; $i < count($parts); $i++) {
    $directory = implode('/', array_slice($parts, 0, $i + 1));
    if (!file_exists($directory)) {
      file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    }
  }
}
