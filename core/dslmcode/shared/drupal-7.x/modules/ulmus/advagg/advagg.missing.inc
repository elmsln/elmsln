<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * Functions used to generate a file given the filename.
 */

/**
 * Menu Callback; generates a missing CSS/JS file.
 */
function advagg_missing_aggregate($input = '') {
  // Do not stop processing this request.
  ignore_user_abort(TRUE);

  // Generate missing file.
  $msg = advagg_missing_generate($input);

  if (module_exists('jquery_update')) {
    $arg = arg();
    $filename = array_pop($arg);
    $filename = explode('?', $filename);
    $filename = array_shift($filename);
    if (strpos($filename, 'min.map') !== FALSE && strpos($filename, 'jquery') !== FALSE) {
      // Get filename from request.
      $wrong_pattern = t('Wrong pattern.');
      if ($msg === $wrong_pattern) {
        $version = variable_get('jquery_update_jquery_version', '1.10');
        $trueversion = '1.9.1';
        switch ($version) {
          case '1.9':
            $trueversion = '1.9.1';
            break;

          case '1.10':
            $trueversion = '1.10.2';
            break;

          case '1.11':
            $trueversion = '1.11.2';
            break;

          case '2.1':
            $trueversion = '2.1.4';
            break;
        }
        $url = "https://cdn.rawgit.com/jquery/jquery/$trueversion/jquery.min.map";
        drupal_goto($url, array('external' => TRUE), 301);
      }
    }
  }

  // If here send out fast 404.
  advagg_missing_fast404($msg);
}

/**
 * Generates a missing CSS/JS file and send it to client.
 *
 * @return string
 *   text if bundle couldn't be generated.
 */
function advagg_missing_generate($input = '') {
  // Make sure we are not in a redirect loop.
  $redirect_counter = isset($_GET['redirect_counter']) ? intval($_GET['redirect_counter']) : 0;
  if ($redirect_counter > 5) {
    watchdog('advagg', 'This request could not generate correctly. Loop detected. Request data: %info', array('%info' => $_GET['q']));
    return t('In a loop.');
  }

  // Get filename from request.
  $arg = arg();
  $filename = array_pop($arg);
  $filename = explode('?', $filename);
  $filename = array_shift($filename);

  // Quit ASAP if filename does not match the AdvAgg pattern.
  $data = advagg_get_hashes_from_filename($filename);
  if (is_string($data) || !is_array($data)) {
    // Try again with the function input.
    $filename = $input;
    $data1 = advagg_get_hashes_from_filename($filename);
    if (is_string($data) || !is_array($data)) {
      return "$data $data1";
    }
    else {
      $data = $data1;
    }
  }

  // Check to see if the file exists.
  list($css_path, $js_path) = advagg_get_root_files_dir();
  if ($data[0] === 'css') {
    $uri = $css_path[0] . '/' . $filename;
  }
  elseif ($data[0] === 'js') {
    $uri = $js_path[0] . '/' . $filename;
  }

  if (file_exists($uri) && filesize($uri) >= 0) {
    // File does exist and filesize is bigger than zero, 307 to it.
    $uri = advagg_generate_location_uri($filename, $data[0], $data[3]);
    ++$redirect_counter;
    $uri .= '?redirect_counter=' . $redirect_counter;
    header('Location: ' . $uri, TRUE, 307);
    exit();
  }

  // Get lock so only one process will do the work.
  $lock_name = 'advagg_' . $filename;
  $uri = $GLOBALS['base_path'] . $_GET['q'];
  $created = FALSE;
  $files_to_save = array();
  if (variable_get('advagg_no_locks', ADVAGG_NO_LOCKS)) {
    $return = advagg_missing_create_file($filename, FALSE, $data);
    if (!is_array($return)) {
      return $return;
    }
    else {
      list($files_to_save, $type) = $return;
      $created = TRUE;
    }
  }
  elseif (lock_acquire($lock_name, 10) || $redirect_counter > 4) {
    if ($redirect_counter > 4) {
      $return = advagg_missing_create_file($filename, TRUE, $data);
    }
    else {
      $return = advagg_missing_create_file($filename, FALSE, $data);
    }
    lock_release($lock_name);
    if (!is_array($return)) {
      return $return;
    }
    else {
      list($files_to_save, $type) = $return;
      $created = TRUE;
    }
  }
  else {
    // Wait for another request that is already doing this work.
    // We choose to block here since otherwise the router item may not
    // be available in menu_execute_active_handler() resulting in a 404.
    lock_wait($lock_name, 10);
    if (file_exists($uri) && filesize($uri) > 0) {
      $type = $data[0];
      $created = TRUE;
    }
  }

  // Redirect and try again on failure.
  if (empty($created)) {
    $uri = advagg_generate_location_uri($filename, $data[0], $data[3]);
    ++$redirect_counter;
    $uri .= '?redirect_counter=' . $redirect_counter;
    header('Location: ' . $uri, TRUE, 307);
    exit();
  }

  if ($redirect_counter > 4) {
    watchdog('advagg', 'One of the alter hooks failed when generating this file: %uri. Thus this file was created without any alter hooks.', array('%uri' => $uri), WATCHDOG_ERROR);
  }

  // Output file's contents if creating the file was successful.
  // This function will call exit.
  advagg_missing_send_saved_file($files_to_save, $uri, $created, $filename, $type, $redirect_counter, $data[3]);
}

/**
 * Given the filename, type, and settings, create absolute URL for 307 redirect.
 *
 * Due to url inbound alter we can not trust that the redirect will work if
 * using $GLOBALS['base_path'] . $_GET['q']. Generate the uri as if it was
 * going to be embedded in the html.
 *
 * @param string $filename
 *   Just the filename no path information.
 * @param string $type
 *   String: css or js.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return string
 *   String pointing to the URI of the file.
 */
function advagg_generate_location_uri($filename, $type, array $aggregate_settings = array()) {
  list($css_path, $js_path) = advagg_get_root_files_dir();
  if ($type === 'css') {
    $uri_307 = $css_path[0] . '/' . $filename;
  }
  elseif ($type === 'js') {
    $uri_307 = $js_path[0] . '/' . $filename;
  }

  if (empty($aggregate_settings)) {
    $aggregate_settings = advagg_current_hooks_hash_array();
  }

  // 307s need to be absolute. RFC 2616 14.30.
  $aggregate_settings['variables']['advagg_convert_absolute_to_relative_path'] = FALSE;
  $aggregate_settings['variables']['advagg_convert_absolute_to_protocol_relative_path'] = FALSE;

  // Make advagg_context_switch available.
  module_load_include('inc', 'advagg', 'advagg');
  advagg_context_switch($aggregate_settings, 0);
  $uri_307 = advagg_file_create_url($uri_307, $aggregate_settings);
  advagg_context_switch($aggregate_settings, 1);

  return $uri_307;
}

/**
 * Send the css/js file to the client.
 *
 * @param array $files_to_save
 *   Array of filenames and data.
 * @param string $uri
 *   Requested filename.
 * @param bool $created
 *   If file was created in a different thread.
 * @param string $filename
 *   Just the filename no path information.
 * @param string $type
 *   String: css or js.
 * @param array $aggregate_settings
 *   Array of settings. Used to generate the 307 redirect location.
 */
function advagg_missing_send_saved_file(array $files_to_save, $uri, $created, $filename, $type, $redirect_counter, array $aggregate_settings = array()) {
  // Send a 304 if this is a repeat request.
  if (!empty($_SERVER['HTTP_IF_MODIFIED_SINCE']) && strtotime($_SERVER['HTTP_IF_MODIFIED_SINCE']) >= REQUEST_TIME) {
    header("HTTP/1.1 304 Not Modified");
    exit();
  }

  $return_compressed_br = FALSE;
  $return_compressed_gz = FALSE;
  // Negotiate whether to use gzip compression.
  if (!empty($_SERVER['HTTP_ACCEPT_ENCODING'])) {
    if (strpos($_SERVER['HTTP_ACCEPT_ENCODING'], 'br') !== FALSE) {
      $return_compressed_br = TRUE;
    }
    if (strpos($_SERVER['HTTP_ACCEPT_ENCODING'], 'gzip') !== FALSE) {
      $return_compressed_gz = TRUE;
    }
  }
  header('Vary: Accept-Encoding', FALSE);

  if (!empty($created)) {
    if ($return_compressed_br && file_exists($uri . '.br') && filesize($uri . '.br') > 0) {
      $uri .= '.br';
    }
    elseif ($return_compressed_gz && file_exists($uri . '.gz') && filesize($uri . '.gz') > 0) {
      $uri .= '.gz';
    }
    if (!isset($files_to_save[$uri]) && file_exists($uri) && filesize($uri)) {
      // Do not use advagg_file_get_contents here.
      $files_to_save[$uri] = (string) @file_get_contents($uri);
    }
  }

  // Make sure zlib.output_compression does not compress the output.
  ini_set('zlib.output_compression', '0');
  header('Vary: Accept-Encoding', FALSE);
  // Clear the output buffer.
  if (ob_get_level()) {
    ob_end_clean();
  }
  // Set generic far future headers.
  if (variable_get('advagg_farfuture_php', ADVAGG_FARFUTURE_PHP)) {
    advagg_missing_set_farfuture_headers();
  }
  // Return compressed content if we can.
  if ($return_compressed_br || $return_compressed_gz) {
    foreach ($files_to_save as $uri => $data) {
      // See if this uri contains .br near the end of it.
      $pos = strripos($uri, '.br', 91 + strlen(ADVAGG_SPACE) * 3);
      if (!empty($pos)) {
        $len = strlen($uri);
        if ($pos == $len - 3) {
          // .br file exists, send it out.
          header('Content-Encoding: br');
          break;
        }
      }

      // See if this uri contains .gz near the end of it.
      $pos = strripos($uri, '.gz', 91 + strlen(ADVAGG_SPACE) * 3);
      if (!empty($pos)) {
        $len = strlen($uri);
        if ($pos == $len - 3) {
          // .gz file exists, send it out.
          header('Content-Encoding: gzip');
          break;
        }
      }
    }
  }
  else {
    $data = trim(reset($files_to_save));
  }

  // Output file and exit.
  if (!empty($data)) {
    $strlen = strlen($data);
    // Send a 304 if this is a repeat request.
    if (isset($_SERVER['HTTP_IF_NONE_MATCH'])) {
      $etags = explode(' ', $_SERVER['HTTP_IF_NONE_MATCH']);
      if ($etags[0] < REQUEST_TIME + 31 * 24 * 60 * 60
        && isset($etags[1])
        && $etags[1] == $strlen
      ) {
        header("HTTP/1.1 304 Not Modified");
        exit();
      }
    }

    // Send out a 200 OK status.
    $default = ADVAGG_HTTP_200_CODE;
    if (module_exists('httprl')
      && variable_get('advagg_use_httprl', ADVAGG_USE_HTTPRL)
      && (is_callable('httprl_is_background_callback_capable')
        && httprl_is_background_callback_capable()
        || !is_callable('httprl_is_background_callback_capable')
      )
    ) {
      // Use 203 instead of 200 if HTTPRL is being used.
      $default = 203;
    }
    $number = variable_get('advagg_http_200_code', $default);
    header("{$_SERVER['SERVER_PROTOCOL']} $number OK");

    // Insure the Last-Modified header is set so 304's work correctly.
    if (file_exists($uri) && $filemtime = @filemtime($uri)) {
      header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T', $filemtime));
      // Etags generation in php is broken due to millisecond precision for the
      // files mtime; apache has it, php does not.
    }
    else {
      header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T', REQUEST_TIME));
    }
    // Set the Expires date 1 month into the future.
    if (variable_get('advagg_farfuture_php', ADVAGG_FARFUTURE_PHP)) {
      header('Expires: ' . gmdate('D, d M Y H:i:s \G\M\T', REQUEST_TIME + 31 * 24 * 60 * 60));
    }
    // Also send an etag out.
    header('Etag: ' . REQUEST_TIME . ' ' . $strlen);

    if ($type === 'css') {
      header("Content-Type: text/css");
    }
    elseif ($type === 'js') {
      header("Content-Type: application/javascript; charset=UTF-8");
    }
    header('X-AdvAgg: Generated file at ' . REQUEST_TIME);

    print $data;
    exit();
  }
  else {
    // Redirect and try again on failure.
    $uri = advagg_generate_location_uri($filename, $type, $aggregate_settings);
    ++$redirect_counter;
    $uri .= '?redirect_counter=' . $redirect_counter;
    header('Location: ' . $uri, TRUE, 307);
    exit();
  }
}

/**
 * Set various headers so the browser will cache the file for a long time.
 */
function advagg_missing_set_farfuture_headers() {
  // Hat tip to the CDN module for the far future headers.
  //
  // Browsers that implement the W3C Access Control specification might refuse
  // to use certain resources such as fonts if those resources violate the
  // same-origin policy. Send a header to explicitly allow cross-domain use of
  // those resources. This is called Cross-Origin Resource Sharing, or CORS.
  header("Access-Control-Allow-Origin: *");
  // Remove all previously set Cache-Control headers, because we're going to
  // override it. Since multiple Cache-Control headers might have been set,
  // simply setting a new, overriding header isn't enough: that would only
  // override the *last* Cache-Control header. Yay for PHP!
  if (function_exists('header_remove')) {
    header_remove('Cache-Control');
    header_remove('ETag');
    header_remove('Set-Cookie');
  }
  else {
    header('Cache-Control:');
    header('Cache-Control:');
    header('ETag:');
    header('ETag:');
    header('Set-Cookie:');
    header('Set-Cookie:');
  }
  // Set a far future Cache-Control header (52 weeks), which prevents
  // intermediate caches from transforming the data and allows any
  // intermediate cache to cache it, since it's marked as a public resource.
  if (variable_get('advagg_resource_hints_use_immutable', ADVAGG_RESOURCE_HINTS_USE_IMMUTABLE)) {
    header('Cache-Control: max-age=31449600, no-transform, public, immutable');
  }
  else {
    header('Cache-Control: max-age=31449600, no-transform, public');
  }
}

/**
 * Given a filename create that file.
 *
 * @param string $filename
 *   Just the filename no path information.
 * @param bool $no_alters
 *   (optional) Set to TRUE to do the bare amount of processing on the file.
 * @param mixed $data
 *   (optional) Output from advagg_get_hashes_from_filename().
 *
 * @return mixed
 *   On failure a string saying why it failed.
 *   On success the $files_to_save array.
 */
function advagg_missing_create_file($filename, $no_alters = FALSE, $data = array()) {
  // Option to still delever the file if fatal error.
  register_shutdown_function("advagg_missing_fatal_handler", $filename);

  if (empty($data)) {
    $data = advagg_get_hashes_from_filename($filename);
  }
  if (is_array($data)) {
    list($type, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings) = $data;
  }
  else {
    return $data;
  }

  if (empty($aggregate_settings)) {
    $aggregate_settings = advagg_current_hooks_hash_array();
  }

  // Set no alters if this is the last chance of generating the aggregate.
  if ($no_alters) {
    $aggregate_settings['settings']['no_alters'] = TRUE;
  }

  // Get a list of files.
  $files = advagg_get_files_from_hashes($type, $aggregate_filenames_hash, $aggregate_contents_hash);
  if (empty($files)) {
    return t('Hashes do not match database.');
  }

  // Save aggregate file.
  list($files_to_save, $errors) = advagg_save_aggregate($filename, $files, $type, $aggregate_settings);
  // Update atime.
  advagg_multi_update_atime(array(
    array(
      'aggregate_filenames_hash' => $aggregate_filenames_hash,
      'aggregate_contents_hash' => $aggregate_contents_hash,
    ),
  ));
  // Make sure .htaccess file exists in the advagg dir.
  if (variable_get('advagg_htaccess_check_generate', ADVAGG_HTACCESS_CHECK_GENERATE)) {
    advagg_htaccess_check_generate($files_to_save, $type);
  }

  // Return data.
  return array(
    $files_to_save,
    $type,
    $aggregate_filenames_hash,
    $aggregate_contents_hash,
    $aggregate_settings,
    $files,
    $errors,
  );
}

/**
 * Generate .htaccess rules and place them in advagg dir.
 *
 * @param array $files_to_save
 *   Array of files that where saved.
 * @param string $type
 *   String: css or js.
 * @param bool $force
 *   (Optional) force recreate the .htaccess file.
 *
 * @return array
 *   Empty array if not errors happened, list of errors if the write had any
 *   issues.
 */
function advagg_htaccess_check_generate(array $files_to_save, $type, $force = FALSE) {
  list($css_path, $js_path) = advagg_get_root_files_dir();

  $content_type = $type;
  if ($content_type === 'js') {
    $content_type = 'javascript';
    $advagg_dir = basename($js_path[1]);
  }
  elseif ($content_type === 'css') {
    $advagg_dir = basename($css_path[1]);
  }
  $type_upper = strtoupper($type);
  $data = "\n";

  // Some hosting companies do not allow "FollowSymLinks" but will support
  // "SymLinksIfOwnerMatch".
  if (variable_get('advagg_htaccess_symlinksifownermatch', ADVAGG_HTACCESS_SYMLINKSIFOWNERMATCH)) {
    $data .= "Options +SymLinksIfOwnerMatch\n";
  }
  else {
    $data .= "Options +FollowSymLinks\n";
  }
  if ($GLOBALS['base_path'] !== '/') {
    $data .= "ErrorDocument 404 {$GLOBALS['base_path']}index.php\n";
  }
  // See if RewriteBase is needed.
  $advagg_htaccess_rewritebase = trim(variable_get('advagg_htaccess_rewritebase', ADVAGG_HTACCESS_REWRITEBASE));
  if (!empty($advagg_htaccess_rewritebase) && !empty($advagg_dir)) {
    $rewrite_base_rule = str_replace('//', '/', $advagg_htaccess_rewritebase . '/' . $advagg_dir);
    $data .= "RewriteBase $rewrite_base_rule\n";
  }

  $data .= "\n";
  $data .= "<IfModule mod_rewrite.c>\n";
  $data .= "  RewriteEngine on\n";
  $data .= "  <IfModule mod_headers.c>\n";
  $data .= "    # Serve brotli compressed ${type_upper} files if they exist and the client accepts br.\n";
  $data .= "    RewriteCond %{HTTP:Accept-encoding} br\n";
  $data .= "    RewriteCond %{REQUEST_FILENAME}\.br -s\n";
  $data .= "    RewriteRule ^(.*)\.${type} " . '$1' . "\.${type}\.br [QSA]\n";
  if ($type === 'css') {
    $data .= "    RewriteRule \.${type}\.br$ - [T=text/${content_type},E=no-gzip:1]\n";
  }
  else {
    $data .= "    RewriteRule \.${type}\.br$ - [T=application/${content_type},E=no-gzip:1]\n";
  }
  $data .= "\n";
  $data .= "    <FilesMatch \"\.${type}\.br$\">\n";
  $data .= "      # Serve correct encoding type.\n";
  $data .= "      Header set Content-Encoding br\n";
  $data .= "      # Force proxies to cache gzipped & non-gzipped css/js files separately.\n";
  $data .= "      Header append Vary Accept-Encoding\n";
  $data .= "    </FilesMatch>\n";
  $data .= "\n";
  $data .= "    # Serve gzip compressed ${type_upper} files if they exist and the client accepts gzip.\n";
  $data .= "    RewriteCond %{HTTP:Accept-encoding} gzip\n";
  $data .= "    RewriteCond %{REQUEST_FILENAME}\.gz -s\n";
  $data .= "    RewriteRule ^(.*)\.${type} " . '$1' . "\.${type}\.gz [QSA]\n";
  if ($type === 'css') {
    $data .= "    RewriteRule \.${type}\.gz$ - [T=text/${content_type},E=no-gzip:1]\n";
  }
  else {
    $data .= "    RewriteRule \.${type}\.gz$ - [T=application/${content_type},E=no-gzip:1]\n";
  }
  $data .= "\n";
  $data .= "    <FilesMatch \"\.${type}\.gz$\">\n";
  $data .= "      # Serve correct encoding type.\n";
  $data .= "      Header set Content-Encoding gzip\n";
  $data .= "      # Force proxies to cache gzipped & non-gzipped css/js files separately.\n";
  $data .= "      Header append Vary Accept-Encoding\n";
  $data .= "    </FilesMatch>\n";
  $data .= "  </IfModule>\n";
  $data .= "</IfModule>\n";
  $data .= "\n";
  $data .= "<FilesMatch \"^${type}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}.${type}(\.gz|\.br)?\">\n";
  $data .= "  # No mod_headers. Apache module headers is not enabled.\n";
  $data .= "  <IfModule !mod_headers.c>\n";
  $data .= "    # No mod_expires. Apache module expires is not enabled.\n";
  $data .= "    <IfModule !mod_expires.c>\n";
  $data .= "      # Use ETags.\n";
  $data .= "      FileETag MTime Size\n";
  $data .= "    </IfModule>\n";
  $data .= "  </IfModule>\n";
  $data .= "\n";
  $data .= "  # Use Expires Directive if apache module expires is enabled.\n";
  $data .= "  <IfModule mod_expires.c>\n";
  $data .= "    # Do not use ETags.\n";
  $data .= "    FileETag None\n";
  $data .= "    # Enable expirations.\n";
  $data .= "    ExpiresActive On\n";
  $data .= "    # Cache all aggregated ${type} files for 52 weeks after access (A).\n";
  $data .= "    ExpiresDefault A31449600\n";
  $data .= "  </IfModule>\n";
  $data .= "\n";
  $data .= "  # Use Headers Directive if apache module headers is enabled.\n";
  $data .= "  <IfModule mod_headers.c>\n";
  $data .= "    # Do not use etags for cache validation.\n";
  $data .= "    Header unset ETag\n";
  $data .= "    # Serve correct content type.\n";
  if ($type === 'css') {
    $data .= "    Header set Content-Type text/${content_type}\n";
  }
  else {
    $data .= "    Header set Content-Type application/${content_type}\n";
  }
  $data .= "    <IfModule !mod_expires.c>\n";
  $data .= "      # Set a far future Cache-Control header to 52 weeks.\n";
  if (variable_get('advagg_resource_hints_use_immutable', ADVAGG_RESOURCE_HINTS_USE_IMMUTABLE)) {
    $data .= "      Header set Cache-Control \"max-age=31449600, no-transform, public, immutable\"\n";
  }
  else {
    $data .= "      Header set Cache-Control \"max-age=31449600, no-transform, public\"\n";
  }
  $data .= "    </IfModule>\n";
  $data .= "    <IfModule mod_expires.c>\n";
  if (variable_get('advagg_resource_hints_use_immutable', ADVAGG_RESOURCE_HINTS_USE_IMMUTABLE)) {
    $data .= "      Header append Cache-Control \"no-transform, public, immutable\"\n";
  }
  else {
    $data .= "      Header append Cache-Control \"no-transform, public\"\n";
  }
  $data .= "    </IfModule>\n";
  $data .= "  </IfModule>\n";
  if ($type === 'css') {
    $data .= "  ForceType text/${content_type}\n";
  }
  else {
    $data .= "  ForceType application/${content_type}\n";
  }
  $data .= "</FilesMatch>\n";

  $errors = array();
  foreach (array_keys($files_to_save) as $uri) {
    $dir = dirname($uri);
    $htaccess_file = $dir . '/.htaccess';
    if (!$force && file_exists($htaccess_file)) {
      continue;
    }

    $errors = advagg_save_data($htaccess_file, $data, $force);
  }
  return $errors;
}

/**
 * Given a filename return the type and 2 hashes.
 *
 * @param string $filename
 *   Just the filename no path information.
 * @param bool $skip_hash_settings
 *   Allows for the skipping of db lookup for required file hooks.
 *
 * @return mixed
 *   On failure a string saying why it failed.
 *   On success array($ext, $aggregate_hash, $files_hash).
 */
function advagg_get_hashes_from_filename($filename, $skip_hash_settings = FALSE) {
  // Verify requested filename has the correct pattern.
  if (!advagg_match_file_pattern($filename)) {
    return t('Wrong pattern.');
  }

  // Get the extension.
  $ext = substr($filename, strpos($filename, '.', 131 + strlen(ADVAGG_SPACE) * 3) + 1);

  // Set extraction points.
  if ($ext === 'css') {
    $aggregate_filenames_start = 3 + strlen(ADVAGG_SPACE);
    $aggregate_contents_start = 46 + strlen(ADVAGG_SPACE) * 2;
    $hooks_hashes_start = 89 + strlen(ADVAGG_SPACE) * 3;
  }
  elseif ($ext === 'js') {
    $aggregate_filenames_start = 2 + strlen(ADVAGG_SPACE);
    $aggregate_contents_start = 45 + strlen(ADVAGG_SPACE) * 2;
    $hooks_hashes_start = 88 + strlen(ADVAGG_SPACE) * 3;
  }
  else {
    return t('Wrong file type.');
  }

  // Extract info from wanted filename.
  $aggregate_filenames_hash = substr($filename, $aggregate_filenames_start, 43);
  $aggregate_contents_hash = substr($filename, $aggregate_contents_start, 43);
  $hooks_hashes_value = substr($filename, $hooks_hashes_start, 43);

  $aggregate_settings = array();
  if (!$skip_hash_settings) {
    // Verify that the hooks hashes is valid.
    $aggregate_settings = advagg_get_hash_settings($hooks_hashes_value);
    if (empty($aggregate_settings)) {
      if (!variable_get('advagg_weak_file_verification', ADVAGG_WEAK_FILE_VERIFICATION)) {
        return t('Bad hooks hashes value.');
      }
      elseif (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
        watchdog('advagg-debug', 'File @filename has an empty aggregate_settings variable; the 3rd hash is incorrect.', array('@filename' => $filename), WATCHDOG_DEBUG);
      }
    }
  }

  return array(
    $ext,
    $aggregate_filenames_hash,
    $aggregate_contents_hash,
    $aggregate_settings,
  );
}

/**
 * Get the files that belong inside of this aggregate.
 *
 * @param string $type
 *   String: css or js.
 * @param string $aggregate_filenames_hash
 *   Hash of the groupings of files.
 * @param string $aggregate_contents_hash
 *   Hash of the files contents.
 *
 * @return array
 *   List of files in the order they should be included.
 */
function advagg_get_files_from_hashes($type, $aggregate_filenames_hash, $aggregate_contents_hash) {
  // Create main query for the advagg_aggregates_versions table.
  $query = db_select('advagg_aggregates_versions', 'aav')
    ->condition('aav.aggregate_filenames_hash', $aggregate_filenames_hash)
    ->condition('aav.aggregate_contents_hash', $aggregate_contents_hash);
  // Create join query for the advagg_aggregates table.
  $subquery_aggregates = $query->join('advagg_aggregates', 'aa', 'aa.aggregate_filenames_hash =
    aav.aggregate_filenames_hash AND aa.aggregate_filenames_hash = :aggregate_filenames_hash',
    array(':aggregate_filenames_hash' => $aggregate_filenames_hash));
  // Create join query for the advagg_files table.
  $query->join('advagg_files', 'af', 'af.filename_hash = aa.filename_hash AND
    af.filetype = :type AND af.filesize > 0', array(':type' => $type));
  // Select fields and ordering of the query; add in query comment as well.
  $query = $query->fields('af', array('filename'))
    ->fields($subquery_aggregates, array('settings'))
    ->orderBy('porder', 'ASC');
  $query->comment('Query called from ' . __FUNCTION__ . '()');
  $results = $query->execute();

  // Add in files that are included in this aggregate.
  $files = array();
  foreach ($results as $value) {
    $files[$value->filename] = unserialize($value->settings);
  }

  // Try again with weak file verification.
  if (empty($files) && variable_get('advagg_weak_file_verification', ADVAGG_WEAK_FILE_VERIFICATION)) {
    if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
      watchdog('advagg-debug', 'Filehash @filename of type @type has an aggregate_contents_hash variable; the 2rd hash is incorrect.', array(
        '@filename' => $aggregate_filenames_hash,
        '@type' => $type,
      ), WATCHDOG_DEBUG);
    }

    // Create main query for the advagg_aggregates_versions table.
    $query = db_select('advagg_aggregates_versions', 'aav')
      ->condition('aav.aggregate_filenames_hash', $aggregate_filenames_hash);
    // Create join query for the advagg_aggregates table.
    $subquery_aggregates = $query->join('advagg_aggregates', 'aa', 'aa.aggregate_filenames_hash =
      aav.aggregate_filenames_hash AND aa.aggregate_filenames_hash = :aggregate_filenames_hash',
      array(':aggregate_filenames_hash' => $aggregate_filenames_hash));
    // Create join query for the advagg_files table.
    $query->join('advagg_files', 'af', 'af.filename_hash = aa.filename_hash AND
      af.filetype = :type AND af.filesize > 0', array(':type' => $type));
    // Select fields and ordering of the query; add in query comment as well.
    $query = $query->fields('af', array('filename'))
      ->fields($subquery_aggregates, array('settings'))
      ->orderBy('porder', 'ASC');
    $query->comment('Query called from ' . __FUNCTION__ . '()');
    $results = $query->execute();

    // Add in files that are included in this aggregate.
    $files = array();
    foreach ($results as $value) {
      $files[$value->filename] = unserialize($value->settings);
    }
  }
  return $files;
}

/**
 * Given a list of files, grab their contents and glue it into one big string.
 *
 * @param array $files
 *   Array of filenames.
 * @param array $aggregate_settings
 *   Array of settings.
 * @param string $aggregate_filename
 *   Filename of the aggregeate.
 *
 * @return string
 *   String containing all the files.
 */
function advagg_get_css_aggregate_contents(array $files, array $aggregate_settings, $aggregate_filename = '') {
  $write_aggregate = TRUE;
  // Check if CSS compression is enabled.
  $optimize = TRUE;
  if (!empty($aggregate_settings['settings']['no_alters'])) {
    $optimize = FALSE;
  }
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $optimize = FALSE;
  }

  module_load_include('inc', 'advagg', 'advagg');
  $info_on_files = advagg_load_files_info_into_static_cache(array_keys($files));

  $data = '';
  if (!empty($files)) {
    $media_changes = FALSE;
    $last_media = NULL;
    foreach ($files as $settings) {
      if (!isset($settings['media'])) {
        continue;
      }
      if (is_null($last_media)) {
        $last_media = $settings['media'];
        continue;
      }
      if ($settings['media'] !== $last_media) {
        $media_changes = TRUE;
        break;
      }
    }
    if ($media_changes) {
      $global_file_media = 'all';
    }
    else {
      $global_file_media = $last_media;
    }

    // https://developer.mozilla.org/en-US/docs/Web/Guide/CSS/Media_queries
    $media_types = array(
      'all',
      'aural',
      'braille',
      'handheld',
      'print',
      'projection',
      'screen',
      'tty',
      'tv',
      'embossed',
    );

    $import_statements = array();
    module_load_include('inc', 'advagg', 'advagg');
    $original_settings = array($optimize, $aggregate_settings);
    foreach ($files as $file => $settings) {
      $media_changes = FALSE;
      if (!isset($settings['media'])) {
        $settings['media'] = '';
      }

      if ($settings['media'] !== $global_file_media) {
        $media_changes = TRUE;
      }

      list($optimize, $aggregate_settings) = $original_settings;
      // Allow other modules to modify aggregate_settings optimize.
      // Call hook_advagg_get_css_file_contents_pre_alter().
      if (empty($aggregate_settings['settings']['no_alters'])) {
        drupal_alter('advagg_get_css_file_contents_pre', $file, $optimize, $aggregate_settings);
      }
      if (is_readable($file)) {
        // Get the files contents.
        $file_contents = (string) @advagg_file_get_contents($file);
        // Get a hash of the file's contents.
        $file_contents_hash = drupal_hash_base64($file_contents);
        $cid = 'advagg:file:' . advagg_drupal_hash_base64($file);
        if (empty($info_on_files[$cid]['content_hash'])) {
          // If hash was not in the cache, get it from the DB.
          $results = db_select('advagg_files', 'af')
            ->fields('af', array('content_hash', 'filename_hash'))
            ->condition('filename', $file)
            ->execute();
          foreach ($results as $row) {
            $info_on_files['advagg:file:' . $row->filename_hash]['content_hash'] = $row->content_hash;
          }
        }
        if ($info_on_files[$cid]['content_hash'] !== $file_contents_hash) {
          // If the content hash doesn't match don't write the file.
          $write_aggregate = advagg_missing_file_not_readable($file, $aggregate_filename, FALSE);
        }
        $contents = advagg_load_css_stylesheet($file, $optimize, $aggregate_settings, $file_contents);
      }
      else {
        // File is not readable.
        $write_aggregate = advagg_missing_file_not_readable($file, $aggregate_filename, TRUE);
      }

      // Allow other modules to modify this files contents.
      // Call hook_advagg_get_css_file_contents_alter().
      if (empty($aggregate_settings['settings']['no_alters'])) {
        drupal_alter('advagg_get_css_file_contents', $contents, $file, $aggregate_settings);
      }

      if ($media_changes) {
        $media_blocks = advagg_parse_media_blocks($contents);
        $contents = '';

        $file_has_type = FALSE;
        if (!empty($settings['media'])) {
          foreach ($media_types as $media_type) {
            if (stripos($settings['media'], $media_type) !== FALSE) {
              $file_has_type = TRUE;
              break;
            }
          }
        }

        foreach ($media_blocks as $css_rules) {
          if (strpos($css_rules, '@media') !== FALSE) {
            // Get start and end of the rules for this media query block.
            $start = strpos($css_rules, '{');
            if ($start === FALSE) {
              continue;
            }
            $end = strrpos($css_rules, '}');
            if ($end === FALSE) {
              continue;
            }

            // Get current media queries for this media block.
            $media_rules = substr($css_rules, 6, $start - 6);
            // Get everything else besides top level media query.
            $css_selectors_rules = substr($css_rules, $start + 1, $end - ($start + 1));

            // Add in main media rule if needed.
            if (!empty($settings['media'])
              && strpos($media_rules, $settings['media']) === FALSE
              && $settings['media'] !== $global_file_media
            ) {
              $rule_has_type = FALSE;
              if ($file_has_type) {
                foreach ($media_types as $media_type) {
                  if (stripos($media_rules, $media_type) !== FALSE) {
                    $rule_has_type = TRUE;
                    break;
                  }
                }
              }
              if (!$rule_has_type) {
                $media_rules = $settings['media'] . ' and ' . $media_rules;
              }
            }
          }
          else {
            $media_rules = $settings['media'];
            $css_selectors_rules = $css_rules;
          }
          $media_rules = trim($media_rules);

          // Pul all @font-face defentions inside the @media declaration above.
          $font_face_string = '';
          $font_blocks = advagg_parse_media_blocks($css_selectors_rules, '@font-face');
          $css_selectors_rules = '';
          foreach ($font_blocks as $rules) {
            if (strpos($rules, '@font-face') !== FALSE) {
              $font_face_string .= "\n {$rules}";
            }
            else {
              $css_selectors_rules .= $rules;
            }
          }
          $css_selectors_rules = str_replace("\n", "\n  ", $css_selectors_rules);
          $font_face_string = str_replace("\n", "\n  ", $font_face_string);

          // Wrap css in dedicated media query if it differs from the global
          // media query and there actually are media rules.
          if (!empty($media_rules) && $media_rules !== $global_file_media) {
            $output = "{$font_face_string} \n@media {$media_rules} {\n {$css_selectors_rules} \n}";
          }
          else {
            $output = "{$font_face_string} \n {$css_selectors_rules}";
          }

          $contents .= trim($output);
        }

      }
      // Per the W3C specification at
      // http://www.w3.org/TR/REC-CSS2/cascade.html#at-import, @import rules
      // must proceed any other style, so we move those to the top.
      $regexp = '/@import[^;]+;/i';
      preg_match_all($regexp, $contents, $matches);
      $contents = preg_replace($regexp, '', $contents);
      // Add the import statements with the media query of the current file.
      $import_media = isset($settings['media']) ? $settings['media'] : '';
      $import_media = trim($import_media);
      $import_statements[] = array($import_media, $matches[0]);

      // Close any open comment blocks.
      $contents .= "\n/*})'\"*/\n";
      if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
        $contents .= "\n/* Above code came from $file */\n\n";
      }

      $data .= $contents;
    }

    // Add import statements to the top of the stylesheet.
    $import_string = '';
    foreach ($import_statements as $values) {
      if ($media_changes) {
        foreach ($values[1] as $statement) {
          $import_string .= str_replace(';', $values[0] . ';', $statement);
        }
      }
      else {
        $import_string .= implode('', $values[1]);
      }
    }
    $data = $import_string . $data;
  }

  // Allow other modules to modify this aggregates contents.
  // Call hook_advagg_get_css_aggregate_contents_alter().
  if (empty($aggregate_settings['settings']['no_alters'])) {
    drupal_alter('advagg_get_css_aggregate_contents', $data, $files, $aggregate_settings);
  }
  return array($data, $write_aggregate);
}

/**
 * Given a list of files, grab their contents and glue it into one big string.
 *
 * @param array $files
 *   Array of filenames.
 * @param array $aggregate_settings
 *   Array of settings.
 * @param string $aggregate_filename
 *   Filename of the aggregeate.
 *
 * @return string
 *   String containing all the files.
 */
function advagg_get_js_aggregate_contents(array $files, array $aggregate_settings, $aggregate_filename = '') {
  $write_aggregate = TRUE;
  $data = '';

  module_load_include('inc', 'advagg', 'advagg');
  $info_on_files = advagg_load_files_info_into_static_cache(array_keys($files));

  if (!empty($files)) {
    // Build aggregate JS file.
    foreach ($files as $filename => $settings) {
      $contents = '';
      // Append a ';' and a newline after each JS file to prevent them from
      // running together. Also close any comment blocks.
      if (is_readable($filename)) {
        $file_contents = (string) @advagg_file_get_contents($filename);
        $file_contents_hash = drupal_hash_base64($file_contents);
        $cid = 'advagg:file:' . advagg_drupal_hash_base64($filename);
        if (empty($info_on_files[$cid]['content_hash'])) {
          $results = db_select('advagg_files', 'af')
            ->fields('af', array('content_hash', 'filename_hash'))
            ->condition('filename', $filename)
            ->execute();
          foreach ($results as $row) {
            $info_on_files['advagg:file:' . $row->filename_hash]['content_hash'] = $row->content_hash;
          }
        }
        if (isset($info_on_files[$cid]['content_hash']) && $info_on_files[$cid]['content_hash'] !== $file_contents_hash) {
          // If the content hash doesn't match don't write the file.
          $write_aggregate = advagg_missing_file_not_readable($filename, $aggregate_filename, FALSE);
        }

        // Make sure that the file is ended properly.
        $file_contents .= "\n;/*})'\"*/\n";
        if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
          $file_contents .= "/* Above code came from $filename */\n\n";
        }
        $contents .= $file_contents;
      }
      else {
        // File is not readable.
        $write_aggregate = advagg_missing_file_not_readable($filename, $aggregate_filename, TRUE);
      }
      // Allow other modules to modify this files contents.
      // Call hook_advagg_get_js_file_contents_alter().
      if (empty($aggregate_settings['settings']['no_alters'])) {
        drupal_alter('advagg_get_js_file_contents', $contents, $filename, $aggregate_settings);
      }
      // Make sure that the file is ended properly.
      if (!empty($contents)) {
        $contents .= ";/*})'\"*/\n";
      }
      $data .= $contents;
    }
  }

  // Allow other modules to modify this aggregates contents.
  // Call hook_advagg_get_js_aggregate_contents_alter().
  if (empty($aggregate_settings['settings']['no_alters'])) {
    drupal_alter('advagg_get_js_aggregate_contents', $data, $files, $aggregate_settings);
  }
  return array($data, $write_aggregate);
}

/**
 * Let other modules know that this file couldn't be found.
 *
 * @param string $filename
 *   Filename of the missing file.
 * @param string $aggregate_filename
 *   Filename of the aggregate that is trying to be generated.
 * @param bool $fs_read_failure
 *   Set to TRUE if the file system couldn't be read.
 */
function advagg_missing_file_not_readable($filename, $aggregate_filename = '', $fs_read_failure = FALSE) {
  $write_aggregate = FALSE;
  $config_path = advagg_admin_config_root_path();
  list($css_path, $js_path) = advagg_get_root_files_dir();

  // Get cache of this report.
  $cid = 'advagg:file_issue:' . drupal_hash_base64($filename);
  $cache = cache_get($cid, 'cache_advagg_info');

  // Let other modules know about this missing file.
  // Call hook_advagg_missing_root_file().
  module_invoke_all('advagg_missing_root_file', $aggregate_filename, $filename, $cache);

  // Report to watchdog if this is not cached and it does not start in the
  // public dir and the advagg dirs.
  if (empty($cache)
    && strpos($filename, 'public://') !== 0
    && strpos($filename, $css_path[1]) !== 0
    && strpos($filename, $js_path[1]) !== 0
  ) {
    if ($fs_read_failure) {
      watchdog('advagg', 'Reading from the file system failed. This can sometimes happen during a deployment and/or a clear cache operation. Filename: %file Aggregate Filename: %aggregate. If this continues to happen go to the <a href="@operations">Operations page</a> and under Drastic Measures - Reset the AdvAgg Files table click the Truncate advagg_files button.', array(
        '%file' => $filename,
        '%aggregate' => $aggregate_filename,
        '@operations' => url('admin/config/development/performance/advagg/operations', array('fragment' => 'edit-reset-advagg-files')),
      ), WATCHDOG_WARNING);
    }
    else {
      watchdog('advagg', 'The content hash for %file does not match the stored content hash from the database. Please <a href="@url">flush the advagg cache</a> under Smart Cache Flush. This can sometimes happen during a deployment. Filename: %file Aggregate Filename: %aggregate', array(
        '%file' => $filename,
        '%aggregate' => $aggregate_filename,
        '@url' => url($config_path . '/advagg/operations', array(
          'fragment' => 'edit-smart-flush',
        )),
      ), WATCHDOG_WARNING);
    }
    cache_set($cid, TRUE, 'cache_advagg_info', CACHE_TEMPORARY);
  }
  elseif (!empty($cache) && $cache->created < (REQUEST_TIME - variable_get('advagg_file_read_failure_timeout', ADVAGG_FILE_READ_FAILURE_TIMEOUT))) {
    // Write the aggregate if it's been in a failure state for over 30 minutes.
    $write_aggregate = TRUE;
  }
  return $write_aggregate;
}

/**
 * Save an aggregate given a filename, the files included in it, and the type.
 *
 * @param string $filename
 *   Just the filename no path information.
 * @param array $files
 *   Array of filenames.
 * @param string $type
 *   String: css or js.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return array
 *   array($files_to_save, $errors).
 */
function advagg_save_aggregate($filename, array $files, $type, array $aggregate_settings = array()) {
  list($css_path, $js_path) = advagg_get_root_files_dir();
  $uri = '';
  if ($type === 'css') {
    $uri = $css_path[0] . '/' . $filename;
  }
  elseif ($type === 'js') {
    $uri = $js_path[0] . '/' . $filename;
  }

  if (empty($aggregate_settings)) {
    $aggregate_settings = advagg_current_hooks_hash_array();
  }

  // Allow other modules to alter the location, files included, and settings.
  if (empty($aggregate_settings['settings']['no_alters'])) {
    // Call hook_advagg_save_aggregate_pre_alter().
    drupal_alter('advagg_save_aggregate_pre', $uri, $files, $aggregate_settings);
  }

  // Build the aggregates contents.
  $contents = '';
  if ($type === 'css') {
    list($contents, $write_aggregate) = advagg_get_css_aggregate_contents($files, $aggregate_settings, $filename);
  }
  elseif ($type === 'js') {
    list($contents, $write_aggregate) = advagg_get_js_aggregate_contents($files, $aggregate_settings, $filename);
  }
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $contents = "/* This aggregate contains the following files:\n" . implode(",\n", array_keys($files)) . ". */\n\n" . $contents;
  }

  // List of files to save.
  $files_to_save = array(
    $uri => $contents,
  );

  // Allow other modules to alter the contents and add new files to save.
  // Call hook_advagg_save_aggregate_alter().
  $other_parameters = array($files, $type);
  if (empty($aggregate_settings['settings']['no_alters'])) {
    drupal_alter('advagg_save_aggregate', $files_to_save, $aggregate_settings, $other_parameters);
  }

  $errors = array();
  if ($write_aggregate) {
    foreach ($files_to_save as $uri => $data) {
      $errors = advagg_save_data($uri, $data);
      if (!file_exists($uri) || filesize($uri) == 0) {
        if ($type === 'css') {
          $full_dir = DRUPAL_ROOT . '/' . $css_path[1];
        }
        elseif ($type === 'js') {
          $full_dir = DRUPAL_ROOT . '/' . $js_path[1];
        }
        $free_space = @disk_free_space($full_dir);
        if ($free_space !== FALSE && strlen($data) > $free_space) {
          watchdog('advagg', 'Write to file system failed. Disk is full. %uri. !errors. %full_dir.', array(
            '%uri' => $uri,
            '!errors' => print_r($errors, TRUE),
            '%full_dir' => $full_dir,
          ), WATCHDOG_ALERT);
        }
        elseif (!is_writable($full_dir)) {
          watchdog('advagg', 'Write to file system failed. Check directory permissions. %uri. !errors. %full_dir.', array(
            '%uri' => $uri,
            '!errors' => print_r($errors, TRUE),
            '%full_dir' => $full_dir,
          ), WATCHDOG_ERROR);
        }
        else {
          watchdog('advagg', 'Write to file system failed. %uri. !errors. %full_dir.', array(
            '%uri' => $uri,
            '!errors' => print_r($errors, TRUE),
            '%full_dir' => $full_dir,
          ), WATCHDOG_ERROR);
        }
        // If the file is empty, remove it. Serving via drupal is better than an
        // empty aggregate being served.
        if (file_exists($uri) && filesize($uri) == 0) {
          @unlink($uri);
        }
      }
    }
  }
  return array($files_to_save, $errors);
}

/**
 * Save data to a file.
 *
 * This will use the rename operation ensuring atomic file operations.
 *
 * @param string $uri
 *   A string containing the destination location. This must be a stream wrapper
 *   URI.
 * @param string $data
 *   A string containing the contents of the file.
 * @param bool $overwrite
 *   (optional) Bool, set to TRUE to overwrite a file.
 *
 * @return array
 *   Empty array if not errors happened, list of errors if the write had any
 *   issues.
 */
function advagg_save_data($uri, $data, $overwrite = FALSE) {
  $t = get_t();
  $errors = array();
  // Clear the stat cache.
  module_load_include('inc', 'advagg', 'advagg');
  advagg_clearstatcache($uri);

  // Prepare dir if needed.
  $dir = dirname($uri);
  $dir_good = file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
  if (!$dir_good) {
    $errors[1] = $t('The directory for @file can not be created or is not writable.', array('@file' => $uri));
    return $errors;
  }

  // File already exists.
  if (!$overwrite && file_exists($uri) && filesize($uri) > 0) {
    if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
      watchdog('advagg-debug', 'File @uri exists and overwrite is false.', array('@uri' => $uri), WATCHDOG_DEBUG);
    }
    $errors[2] = $t('File (@file) already exits.', array('@file' => $uri));
    return $errors;
  }

  // If data is empty, write a space.
  if (empty($data)) {
    $data = ' ';
  }

  // Perform the replace operation. Since there could be multiple processes
  // writing to the same file, the best option is to create a temporary file in
  // the same directory and then rename it to the destination. A temporary file
  // is needed if the directory is mounted on a separate machine; thus ensuring
  // the rename command stays local and atomic.
  //
  // Get a temporary filename in the destination directory.
  $dir = $uri_dir = drupal_dirname($uri) . '/';

  // Corect the bug with drupal_tempnam where it doesn't pass subdirs to
  // tempnam() if the dir is a stream wrapper.
  $scheme = file_uri_scheme($uri_dir);
  if ($scheme && file_stream_wrapper_valid_scheme($scheme)) {
    $wrapper = file_stream_wrapper_get_instance_by_scheme($scheme);
    if ($wrapper && method_exists($wrapper, 'getDirectoryPath')) {
      $wrapper_dir_path = $wrapper->getDirectoryPath();
      if (!empty($wrapper_dir_path)) {
        $dir = $wrapper_dir_path . '/' . substr($uri_dir, strlen($scheme . '://'));
        $uri = $dir . substr($uri, strlen($uri_dir));
      }
    }
  }

  // Get the extension of the original filename and append it to the temp file
  // name. Preserves the mime type in different stream wrapper implementations.
  $parts = pathinfo($uri);
  if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
    watchdog('advagg-debug', 'Creating URI @uri', array('@uri' => $uri), WATCHDOG_DEBUG);
    watchdog('advagg-debug', 'File Parts <pre>@parts</pre>', array('@parts' => print_r($parts, TRUE)), WATCHDOG_DEBUG);
  }
  $extension = '.' . $parts['extension'];
  if ($extension === '.gz' || $extension === '.br') {
    $parts = pathinfo($parts['filename']);
    $extension = '.' . $parts['extension'] . $extension;
  }

  // Create temp filename.
  $temporary_file = $dir . 'advagg_file_' . drupal_hash_base64(microtime(TRUE) . mt_rand()) . $extension;

  // Save to temporary filename in the destination directory.
  $filepath = file_unmanaged_save_data($data, $temporary_file, FILE_EXISTS_REPLACE);

  if ($filepath) {
    // Perform the rename operation.
    if (!advagg_rename($filepath, $uri)) {
      // Unlink and try again for windows. Rename on windows does not replace
      // the file if it already exists.
      if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
        watchdog('advagg-debug', 'Rename failed. @to', array('@to' => $uri), WATCHDOG_WARNING);
      }
      @unlink($uri);
      // Remove temporary_file if rename failed.
      if (!advagg_rename($filepath, $uri)) {
        $errors[20] = $t('Renaming the filename (@incorrect) to (@correct) failed.', array('@incorrect' => $filepath, '@correct' => $uri));

        @unlink($filepath);
        if (file_exists($filepath)) {
          $errors[22] = $t('unlinking @file failed.', array('@file' => $filepath));
        }
        watchdog('advagg', 'Rename 4 failed. Current: %current Target: %target', array(
          '%current' => $filepath,
          '%target' => $uri,
        ), WATCHDOG_ERROR);
      }
    }

    // Check the filesize.
    $file_size = @filesize($uri);
    $expected_size = _advagg_string_size_in_bytes($data);
    if ($file_size === 0) {
      // Zero byte file.
      $errors[26] = $t('Write successful, but the file is empty. @file', array('@file' => $filepath));
      watchdog('advagg', 'Write successful, but the file is empty. Target: target.  The empty file has been removed.  If this error continues, performance will be greatly degraded.', array(
        '%target' => $uri,
      ), WATCHDOG_ERROR);
      // Better to serve straight from Drupal than have a broken file.
      @unlink($uri);
    }
    elseif ($file_size > 0 && $file_size != $expected_size) {
      // Data written to disk doesn't match.
      $errors[28] = $t('Write successful, but the file is the wrong size. @file Expected size is @expected_size, actual size is @file_size', array(
        '@file' => $uri,
        '@expected_size' => $expected_size,
        '@file_size' => $file_size,
      ));
      watchdog('advagg', 'Write successful, but the file is the wrong size. %file Expected size is %expected_size, actual size is %file_size. The broken file has been removed.  If this error continues, performance will be greatly degraded.', array(
        '%file' => $uri,
        '%expected_size' => $expected_size,
        '%file_size' => $file_size,
      ), WATCHDOG_ERROR);
      // Better to serve straight from Drupal than have a broken file.
      @unlink($uri);
    }
  }
  else {
    $errors[24] = $t('Write failed. @file', array('@file' => $temporary_file));
    watchdog('advagg', 'Write failed. Target: %target', array(
      '%target' => $temporary_file,
    ), WATCHDOG_ERROR);
  }
  // Cleanup leftover files.
  if (file_exists($temporary_file)) {
    @unlink($temporary_file);
  }
  if (file_exists($filepath)) {
    @unlink($filepath);
  }
  return $errors;
}

/**
 * Given a string, what is the size that it should be as a file?
 *
 * @param string $string
 *   Input data to be sized in bytes.
 *
 * @link http://stackoverflow.com/a/3511239/231914
 *
 * @return int
 *   Number of bytes this string uses.
 */
function _advagg_string_size_in_bytes($string) {
  if (function_exists('mb_strlen')) {
    return mb_strlen($string, '8bit');
  }
  else {
    return strlen($string);
  }
}

/**
 * Rename; fallback to copy delete if this fails.
 *
 * @param string $source
 *   A string containing the source location.
 * @param string $destination
 *   A string containing the destination location.
 *
 * @return mixed
 *   Destination string on success, FALSE on failure.
 */
function advagg_rename($source, $destination) {
  $real_source = drupal_realpath($source);
  $real_source = $real_source ? $real_source : $source;
  $real_destination = drupal_realpath($destination);
  $real_destination = $real_destination ? $real_destination : $destination;

  if (!@rename($real_source, $real_destination)) {
    if (!file_unmanaged_move($source, $destination)) {
      return FALSE;
    }
  }

  return $destination;
}

/**
 * Send out a fast 404 and exit.
 *
 * @param string $msg
 *   (optional) Small message reporting why the file didn't get created.
 */
function advagg_missing_fast404($msg = '') {
  drupal_page_is_cacheable(FALSE);

  // Strip new lines & separators and limit header message to 512 characters.
  $msg = substr(preg_replace("/[^\w\. ]+/", "", $msg), 0, 512);

  // Add in headers if possible.
  if (!headers_sent()) {
    header($_SERVER['SERVER_PROTOCOL'] . ' 404 Not Found');
    header('X-AdvAgg: Failed validation. ' . $msg);
  }

  // Output fast 404 message and exit.
  print '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">' . "\n";
  print '<html xmlns="http://www.w3.org/1999/xhtml">';
  print '<head><title>404 Not Found</title><meta http-equiv="Content-Type" content="text/html; charset=UTF-8" /></head>';
  print '<body><h1>Not Found</h1>';
  print '<p>The requested URL was not found on this server.</p>';
  print '<p><a href="' . $GLOBALS['base_path'] . '">Home</a></p>';
  print '<!-- advagg_missing_fast404 -->';
  print '</body></html>';
  exit();
}

/**
 * Read the atime value for the given aggregate.
 *
 * @param string $aggregate_filenames_hash
 *   Hash of the groupings of files.
 * @param string $aggregate_contents_hash
 *   Hash of the files contents.
 * @param string $uri
 *   URI pointing to the aggregate file.
 *
 * @return mixed
 *   File atime or FALSE if not found.
 */
function advagg_get_atime($aggregate_filenames_hash, $aggregate_contents_hash, $uri) {
  // Try to use the cache to avoid hitting the database with a select query.
  $cache_id = 'advagg:db:' . $aggregate_filenames_hash . ADVAGG_SPACE . $aggregate_contents_hash;
  $cache = cache_get($cache_id, 'cache_advagg_info');
  if ($cache) {
    // If the atime in the cache is less than 12 hours old, use that.
    if (!empty($cache->data['atime']) && $cache->data['atime'] > REQUEST_TIME - (12 * 60 * 60)) {
      return $cache->data['atime'];
    }
  }

  // Try to get the atime from the DB.
  $atime = db_select('advagg_aggregates_versions', 'aav')
    ->fields('aav', array('atime'))
    ->condition('aav.aggregate_filenames_hash', $aggregate_filenames_hash)
    ->condition('aav.aggregate_contents_hash', $aggregate_contents_hash)
    ->execute()
    ->fetchField();
  if (!empty($atime)) {
    return $atime;
  }

  // Return the atime from disk as a last resort.
  if (file_exists($uri)) {
    return fileatime($uri);
  }
  // No atime was found, return FALSE.
  return FALSE;
}

/**
 * Split up as CSS string by @media queries.
 *
 * @param string $css
 *   String of CSS.
 * @param string $starting_string
 *   What to look for when starting to parse the string.
 *
 * @return array
 *   array of css with only media queries.
 *
 * @see http://stackoverflow.com/a/14145856/125684
 */
function advagg_parse_media_blocks($css, $starting_string = '@media') {
  $media_blocks = array();
  $start = 0;
  $last_start = 0;

  // Using the string as an array throughout this function.
  // http://php.net/types.string#language.types.string.substr
  while (($start = strpos($css, $starting_string, $start)) !== FALSE) {
    // Stack to manage brackets.
    $s = array();

    // Get the first opening bracket.
    $i = strpos($css, "{", $start);

    // If $i is false, then there is probably a css syntax error.
    if ($i === FALSE) {
      continue;
    }

    // Push bracket onto stack.
    array_push($s, $css[$i]);
    // Move past first bracket.
    ++$i;

    // Find the closing bracket for the @media statement. But ensure we don't
    // overflow if there's an error.
    while (!empty($s) && isset($css[$i])) {
      // If the character is an opening bracket, push it onto the stack,
      // otherwise pop the stack.
      if ($css[$i] === "{") {
        array_push($s, "{");
      }
      elseif ($css[$i] === "}") {
        array_pop($s);
      }
      ++$i;
    }

    // Get CSS before @media and store it.
    if ($last_start != $start) {
      $insert = trim(substr($css, $last_start, $start - $last_start));
      if (!empty($insert)) {
        $media_blocks[] = $insert;
      }
    }
    // Cut @media block out of the css and store.
    $media_blocks[] = trim(substr($css, $start, $i - $start));
    // Set the new $start to the end of the block.
    $start = $i;
    $last_start = $start;
  }

  // Add in any remaining css rules after the last @media statement.
  if (strlen($css) > $last_start) {
    $insert = trim(substr($css, $last_start));
    if (!empty($insert)) {
      $media_blocks[] = $insert;
    }
  }

  return $media_blocks;
}

/**
 * Given a filename create that file; usually works if PHP goes fatal.
 *
 * @param string $filename
 *   Just the filename no path information.
 *
 * @return mixed
 *   On failure a string saying why it failed.
 *   On success the $files_to_save array.
 */
function advagg_missing_fatal_handler($filename) {
  static $counter = 0;
  // Bail out if there is no error.
  $error = error_get_last();
  if ($error === NULL) {
    return;
  }

  $counter++;
  // Bail out if this is still in a loop.
  if ($counter > 2) {
    return;
  }

  // Bail out if the file already exists.
  $data = advagg_get_hashes_from_filename($filename);
  $type = $data[0];
  list($css_path, $js_path) = advagg_get_root_files_dir();
  $uri = '';
  if ($type === 'css') {
    $uri = $css_path[0] . '/' . $filename;
  }
  elseif ($type === 'js') {
    $uri = $js_path[0] . '/' . $filename;
  }
  if (file_exists($uri)) {
    return;
  }

  // Generate the file with no alters.
  set_time_limit(0);
  $return = advagg_missing_create_file($filename, TRUE);
  if (is_array($return) && !headers_sent()) {
    $redirect_counter = isset($_GET['redirect_counter']) ? intval($_GET['redirect_counter']) : 0;
    // 307 if headers have not been sent yet.
    $uri = advagg_generate_location_uri($filename, $data[0], $data[3]);
    ++$redirect_counter;
    $uri .= '?redirect_counter=' . $redirect_counter;
    header('Location: ' . $uri, TRUE, 307);
    exit();
  }
}
