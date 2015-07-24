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
    $data = advagg_get_hashes_from_filename($filename);
    if (is_string($data) || !is_array($data)) {
      return $data;
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
  if (lock_acquire($lock_name, 10) || $redirect_counter > 4) {
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
  // Negotiate whether to use gzip compression.
  $return_compressed = isset($_SERVER['HTTP_ACCEPT_ENCODING']) && strpos($_SERVER['HTTP_ACCEPT_ENCODING'], 'gzip') !== FALSE;
  header('Vary: Accept-Encoding', FALSE);

  if (!empty($created)) {
    if ($return_compressed && file_exists($uri . '.gz') && filesize($uri . '.gz') > 0) {
      $uri .= '.gz';
    }
    if (!isset($files_to_save[$uri]) && file_exists($uri) && filesize($uri)) {
      $files_to_save[$uri] = file_get_contents($uri);
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
  advagg_missing_set_farfuture_headers();
  // Return compressed content if we can.
  if ($return_compressed) {
    foreach ($files_to_save as $uri => $data) {
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
    // Send out a 200 OK status.
    header($_SERVER['SERVER_PROTOCOL'] . " 200 OK");

    // Insure the Last-Modified header is set so 304's work correctly.
    // @ignore druplart_andor_assignment
    if (file_exists($uri) && $filemtime = @filemtime($uri)) {
      header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T', $filemtime));
      // Etags generation in php is broken due to millisecond precision for the
      // files mtime; apache has it, php does not.
    }

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
  // those resources. (This is called Cross-Origin Resource Sharing, or CORS.)
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
  header('Cache-Control: max-age=31449600, no-transform, public');
}

/**
 * Given a filename create that file.
 *
 * @param string $filename
 *   Just the filename no path information.
 * @param bool $no_alters
 *   (optional) Set to TRUE to do the bare amount of processing on the file.
 * @param array $data
 *   (optional) Output from advagg_get_hashes_from_filename().
 *
 * @return mixed
 *   On failure a string saying why it failed.
 *   On success the $files_to_save array.
 */
function advagg_missing_create_file($filename, $no_alters = FALSE, $data = array()) {
  if (empty($data)) {
    $data = advagg_get_hashes_from_filename($filename);
  }
  if (is_array($data)) {
    list($type, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings) = $data;
  }
  else {
    return $data;
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
  $files_to_save = advagg_save_aggregate($filename, $files, $type, $aggregate_settings);
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
 */
function advagg_htaccess_check_generate(array $files_to_save, $type, $force = FALSE) {
  $content_type = $type;
  if ($content_type === 'js') {
    $content_type = 'javascript';
  }

  // @ignore style_lowercase_html:45
  $data  = "\n";
  $data .= "<FilesMatch \"^${type}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}.${type}(\.gz)?\">\n";
  $data .= "  # No mod_headers\n";
  $data .= "  <IfModule !mod_headers.c>\n";
  $data .= "    # No mod_expires\n";
  $data .= "    <IfModule !mod_expires.c>\n";
  $data .= "      # Use ETags.\n";
  $data .= "      FileETag MTime Size\n";
  $data .= "    </IfModule>\n";
  $data .= "  </IfModule>\n";
  $data .= "\n";
  $data .= "  # Use Expires Directive.\n";
  $data .= "  <IfModule mod_expires.c>\n";
  $data .= "    # Do not use ETags.\n";
  $data .= "    FileETag None\n";
  $data .= "    # Enable expirations.\n";
  $data .= "    ExpiresActive On\n";
  $data .= "    # Cache all aggregated ${type} files for 52 weeks after access (A).\n";
  $data .= "    ExpiresDefault A31449600\n";
  $data .= "  </IfModule>\n";
  $data .= "\n";
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
  $data .= "      Header set Cache-Control \"max-age=31449600, no-transform, public\"\n";
  $data .= "    </IfModule>\n";
  $data .= "    <IfModule mod_expires.c>\n";
  $data .= "      Header append Cache-Control \"no-transform, public\"\n";
  $data .= "    </IfModule>\n";
  $data .= "  </IfModule>\n";
  if ($type === 'css') {
    $data .= "  ForceType text/${content_type}\n";
  }
  else {
    $data .= "  ForceType application/${content_type}\n";
  }
  $data .= "</FilesMatch>\n";

  foreach (array_keys($files_to_save) as $uri) {
    $dir = dirname($uri);
    $htaccess_file = $dir . '/.htaccess';
    if (!$force && file_exists($htaccess_file)) {
      continue;
    }

    advagg_save_data($htaccess_file, $data, $force);
  }
}

// Lookup functions.
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
      return t('Bad hooks hashes value.');
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
    af.filetype = :type', array(':type' => $type));
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
  return $files;
}

// Read CSS/JS files.
/**
 * Given a list of files, grab their contents and glue it into one big string.
 *
 * @param array $files
 *   Array of filenames.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return string
 *   String containing all the files.
 */
function advagg_get_css_aggregate_contents(array $files, array $aggregate_settings) {
  // Check if CSS compression is enabled.
  $optimize = TRUE;
  if (!empty($aggregate_settings['settings']['no_alters'])) {
    $optimize = FALSE;
  }
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $optimize = FALSE;
  }

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
      $contents = advagg_load_css_stylesheet($file, $optimize, $aggregate_settings);

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
            if ( !empty($settings['media'])
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
          $css_selectors_rules = trim($css_selectors_rules);

          // Wrap css in dedicated media query if it differs from the global
          // media query and there actually are media rules.
          if (!empty($media_rules) && $media_rules !== $global_file_media) {
            $output = "\n@media " . $media_rules . " {\n  " . str_replace("\n", "\n  ", $css_selectors_rules) . "\n}";
          }
          else {
            $output = "\n" . $css_selectors_rules;
          }

          $contents .= $output;
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
      $contents .= '/**/';
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
  return $data;
}

/**
 * Given a list of files, grab their contents and glue it into one big string.
 *
 * @param array $files
 *   Array of filenames.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return string
 *   String containing all the files.
 */
function advagg_get_js_aggregate_contents(array $files, array $aggregate_settings) {
  $data = '';

  if (!empty($files)) {
    // Build aggregate JS file.
    foreach ($files as $filename => $settings) {
      $contents = '';
      // Append a ';' and a newline after each JS file to prevent them from
      // running together. Also close any comment blocks.
      if (file_exists($filename)) {
        $contents .= file_get_contents($filename) . ";/**/\n";
        if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
          $contents .= "/* Above code came from $filename */\n\n";
        }
      }
      // Allow other modules to modify this files contents.
      // Call hook_advagg_get_js_file_contents_alter().
      if (empty($aggregate_settings['settings']['no_alters'])) {
        drupal_alter('advagg_get_js_file_contents', $contents, $filename, $aggregate_settings);
      }
      $data .= $contents;
    }
  }

  // Allow other modules to modify this aggregates contents.
  // Call hook_advagg_get_js_aggregate_contents_alter().
  if (empty($aggregate_settings['settings']['no_alters'])) {
    drupal_alter('advagg_get_js_aggregate_contents', $data, $files, $aggregate_settings);
  }
  return $data;
}

// File save functions.
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
 *   $files_to_save array.
 */
function advagg_save_aggregate($filename, array $files, $type, array $aggregate_settings) {
  list($css_path, $js_path) = advagg_get_root_files_dir();
  $uri = '';
  if ($type === 'css') {
    $uri = $css_path[0] . '/' . $filename;
  }
  elseif ($type === 'js') {
    $uri = $js_path[0] . '/' . $filename;
  }

  // Allow other modules to alter the location, files included, and settings.
  if (empty($aggregate_settings['settings']['no_alters'])) {
    // Call hook_advagg_save_aggregate_pre_alter().
    drupal_alter('advagg_save_aggregate_pre', $uri, $files, $aggregate_settings);
  }

  // Build the aggregates contents.
  $contents = '';
  if ($type === 'css') {
    $contents = advagg_get_css_aggregate_contents($files, $aggregate_settings);
  }
  elseif ($type === 'js') {
    $contents = advagg_get_js_aggregate_contents($files, $aggregate_settings);
  }
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $contents = "/* This aggregate contains the following files:\n" . implode(",\n", array_keys($files)) . ". */\n\n" . $contents;
  }

  // List of files to save.
  $files_to_save = array(
    $uri => $contents,
  );

  // Allow other modules to alter the contents and add new files to save (.gz).
  // Call hook_advagg_save_aggregate_alter().
  $other_parameters = array($files, $type);
  if (empty($aggregate_settings['settings']['no_alters'])) {
    drupal_alter('advagg_save_aggregate', $files_to_save, $aggregate_settings, $other_parameters);
  }

  foreach ($files_to_save as $uri => $data) {
    advagg_save_data($uri, $data);
    if (!file_exists($uri) || filesize($uri) == 0) {
      if ($type === 'css') {
        $full_dir = DRUPAL_ROOT . '/' . $css_path[1];
      }
      elseif ($type === 'js') {
        $full_dir = DRUPAL_ROOT . '/' . $js_path[1];
      }
      $free_space = @disk_free_space($full_dir);
      if ($free_space !== FALSE && strlen($data) > $free_space) {
        watchdog('advagg', 'Write to file system failed. Disk is full. %uri', array('%uri' => $uri), WATCHDOG_ALERT);
      }
      elseif (!is_writable($full_dir)) {
        watchdog('advagg', 'Write to file system failed. Check directory permissions. %uri', array('%uri' => $uri), WATCHDOG_ERROR);
      }
      else {
        watchdog('advagg', 'Write to file system failed. %uri', array('%uri' => $uri), WATCHDOG_ERROR);
      }
      // If the file is empty, remove it. Serving via drupal is better than an
      // empty aggregate being served.
      if (file_exists($uri) && filesize($uri) == 0) {
        @unlink($uri);
      }
    }
  }
  return $files_to_save;
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
 */
function advagg_save_data($uri, $data, $overwrite = FALSE) {
  // Clear the stat cache.
  module_load_include('inc', 'advagg', 'advagg');
  advagg_clearstatcache($uri);
  // File already exists.
  if (!$overwrite && file_exists($uri) && filesize($uri) > 0) {
    return;
  }

  // If data is empty, write a space.
  if (empty($data)) {
    $data = ' ';
  }

  // Perform the replace operation. Since there could be multiple processes
  // writing to the same file, the best option is to create a temporary file in
  // the same directory and then rename it to the destination. A temporary file
  // is needed if the directory is mounted on a separate machine; thus ensuring
  // the rename command stays local.
  //
  // Get a temporary filename in the destination directory.
  $dir = drupal_dirname($uri) . '/';
  $temporary_file = @drupal_tempnam($dir, 'file_advagg_');
  if ($temporary_file === FALSE) {
    $temporary_file = $dir . 'file_advagg_' . md5(getmypid() . microtime(TRUE) . mt_rand());
  }
  $temporary_file_copy = $temporary_file;

  // Get the extension of the original filename and append it to the temp file
  // name. Preserves the mime type in different stream wrapper implementations.
  $parts = pathinfo($uri);
  $extension = '.' . $parts['extension'];
  if ($extension === '.gz') {
    $parts = pathinfo($parts['filename']);
    $extension = '.' . $parts['extension'] . $extension;
  }
  // Move temp file into the dest dir, if not in there.
  // Add the extension on as well.
  $temporary_file = str_replace(substr($temporary_file, 0, strpos($temporary_file, 'file_advagg_')), $dir, $temporary_file) . $extension;

  // Preform the rename, adding the extension to the temp file.
  if (!@rename($temporary_file_copy, $temporary_file)) {
    // Remove if rename failed.
    @unlink($temporary_file_copy);
  }

  // Save to temporary filename in the destination directory.
  $filepath = file_unmanaged_save_data($data, $temporary_file, FILE_EXISTS_REPLACE);

  if ($filepath) {
    // Perform the rename operation.
    $result = @rename($filepath, $uri);
    if (!$result) {
      // Unlink and try again for windows. Rename on windows does not replace
      // the file if it already exists.
      @unlink($uri);
      $result = @rename($filepath, $uri);
      // Remove temporary_file if rename failed.
      if (!$result) {
        @unlink($filepath);
      }
    }
  }
}

// Helper functions.
/**
 * Send out a fast 404 and exit.
 *
 * @param string $msg
 *   (optional) Small message reporting why the file didn't get created.
 */
function advagg_missing_fast404($msg = '') {
  // Strip new lines and limit header message to 512 characters.
  $msg = substr(str_replace(array("\n", "\r"), '', $msg), 0, 512);

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
 *
 * @return array
 *   array of css with only media queries.
 *
 * @see http://stackoverflow.com/questions/14145620/regular-expression-for-media-queries-in-css
 */
function advagg_parse_media_blocks($css) {
  $media_blocks = array();
  $start = 0;
  $last_start = 0;

  // Using the string as an array throughout this function.
  // http://php.net/types.string#language.types.string.substr
  while (($start = strpos($css, "@media", $start)) !== FALSE) {
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
