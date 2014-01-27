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
function advagg_missing_aggregate() {
  // Do not stop processing this request.
  ignore_user_abort(TRUE);

  // Generate missing file
  $msg = advagg_missing_generate();

  // If here send out fast 404.
  advagg_missing_fast404($msg);
}

/**
 * Generates a missing CSS/JS file and send it to client.
 *
 * @return
 *   text if bundle couldn't be generated.
 */
function advagg_missing_generate() {
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

  $lock_name = 'advagg_' . $filename;
  $uri = $GLOBALS['base_path'] . $_GET['q'];
  $created = FALSE;
  $files_to_save = array();
  if (lock_acquire($lock_name, 10) || $redirect_counter > 4) {
    if ($redirect_counter > 4) {
      $return = advagg_missing_create_file($filename, TRUE);
    }
    else {
      $return = advagg_missing_create_file($filename);
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
      $data = advagg_get_hashes_from_filename($filename);
      if (is_array($data)) {
        $type = $data[0];
        $created = TRUE;
      }
    }
  }

  // Redirect and try again on failure.
  if (empty($created)) {
    $redirect_counter++;
    $uri .= '?redirect_counter=' . $redirect_counter;
    header('Location: ' . $uri, TRUE, 307);
    exit();
  }

  if ($redirect_counter > 4) {
    watchdog('advagg', 'One of the alter hooks failed when generating this file: %uri. Thus this file was created without any alter hooks.', array('%uri' => $uri), WATCHDOG_CRITICAL);
  }

  // Output file's contents if creating the file was successful.
  // This function will call exit.
  advagg_missing_send_saved_file($files_to_save, $uri, $created, $type, $redirect_counter);
}

/**
 * Send the css/js file to the client.
 *
 * @param $files_to_save
 *   Array of filenames and data.
 * @param $uri
 *   Requested filename.
 * @param $created
 *   If file was created in a different thread.
 * @param $type
 *   css or js
 */
function advagg_missing_send_saved_file($files_to_save, $uri, $created, $type, $redirect_counter) {
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
      $pos = strripos($uri, '.gz', 91 + strlen(ADVAGG_SPACE)*3);
      if (!empty($pos)) {
        $len = strlen($uri);
        if ($pos == $len-3) {
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
    if (file_exists($uri) && $filemtime = @filemtime($uri)) {
      header('Last-Modified: ' . gmdate('D, d M Y H:i:s \G\M\T', $filemtime));
    }

    if ($type == 'css') {
      header("Content-Type: text/css");
    }
    elseif ($type == 'js') {
      header("Content-Type: text/javascript; charset=UTF-8");
    }
    header('X-AdvAgg: Generated file at ' . REQUEST_TIME);

    print $data;
    exit();
  }
  else {
    // Redirect and try again on failure.
    $redirect_counter++;
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
  // Set a far future Cache-Control header (480 weeks), which prevents
  // intermediate caches from transforming the data and allows any
  // intermediate cache to cache it, since it's marked as a public resource.
  header('Cache-Control: max-age=290304000, no-transform, public');
  // Set a far future Expires header. The maximum UNIX timestamp is somewhere
  // in 2038. Set it to a date in 2037, just to be safe.
  header("Expires: Tue, 20 Jan 2037 04:08:15 GMT");
}

/**
 * Given a filename create that file.
 *
 * @param $filename
 *   Just the filename no path information.
 * @param $no_alters
 *   Set to TRUE to do the bare amount of processing on the file.
 *
 * @return
 *   On failure a string saying why it failed.
 *   On success the $files_to_save array.
 */
function advagg_missing_create_file($filename, $no_alters = FALSE) {
  $data = advagg_get_hashes_from_filename($filename);
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
  advagg_update_atime($aggregate_filenames_hash, $aggregate_contents_hash);
  // Make sure .htaccess file exists in the advagg dir.
  if (variable_get('advagg_htaccess_check_generate', ADVAGG_HTACCESS_CHECK_GENERATE)) {
    advagg_htaccess_check_generate($files_to_save, $type);
  }

  // Return data.
  return array($files_to_save, $type, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings, $files);
}

/**
 * Generate .htaccess rules and place them in advagg dir
 *
 * @param $files_to_save
 *   array of files that where saved..
 * @param $force
 *   force recreate the .htaccess file.
 */
function advagg_htaccess_check_generate($files_to_save, $type, $force = FALSE) {
  $content_type = $type;
  if ($content_type == 'js') {
    $content_type = 'javascript';
  }

  $data  = "\n";
  $data .= "<FilesMatch \"^${type}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}" . ADVAGG_SPACE . "[A-Za-z0-9-_]{43}.${type}(\.gz)?\">\n";
  $data .= "  # No mod_headers\n";
  $data .= "  <IfModule !mod_headers.c>\n";
  $data .= "    # No mod_expires\n";
  $data .= "    <IfModule !mod_expires.c>\n";
  $data .= "      # Use ETags.\n";
  $data .= "      FileETag MTime Size\n";
  $data .= "    </IfModule>\n";
  $data .= "\n";
  $data .= "    # Use Expires Directive.\n";
  $data .= "    <IfModule mod_expires.c>\n";
  $data .= "      # Do not use ETags.\n";
  $data .= "      FileETag None\n";
  $data .= "      # Enable expirations.\n";
  $data .= "      ExpiresActive On\n";
  $data .= "      # Cache all aggregated ${type} files for 480 weeks after access (A).\n";
  $data .= "      ExpiresDefault A290304000\n";
  $data .= "    </IfModule>\n";
  $data .= "  </IfModule>\n";
  $data .= "\n";
  $data .= "  <IfModule mod_headers.c>\n";
  $data .= "    # Serve correct content type.\n";
  $data .= "    Header set Content-Type text/${content_type}\n";
  $data .= "    # Set a far future Cache-Control header to 480 weeks.\n";
  $data .= "    Header set Cache-Control \"max-age=290304000, no-transform, public\"\n";
  $data .= "    # Set a far future Expires header.\n";
  $data .= "    Header set Expires \"Tue, 20 Jan 2037 04:20:42 GMT\"\n";
  $data .= "    # Do not use etags for cache validation.\n";
  $data .= "    Header unset ETag\n";
  $data .= "  </IfModule>\n";
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
 * @param $filename
 *   Just the filename no path information.
 *
 * @return
 *   On failure a string saying why it failed.
 *   On success array($ext, $aggregate_hash, $files_hash).
 */
function advagg_get_hashes_from_filename($filename) {
  // Verify requested filename has the correct pattern.
  if (!preg_match('/^(j|cs)s' . ADVAGG_SPACE . '[A-Za-z0-9-_]{43}' . ADVAGG_SPACE . '[A-Za-z0-9-_]{43}' . ADVAGG_SPACE . '[A-Za-z0-9-_]{43}\.(j|cs)s$/', $filename)) {
    return t('Wrong pattern.');
  }

  // Get the extension.
  $ext = substr($filename, strpos($filename, '.', 131 + strlen(ADVAGG_SPACE)*3) + 1);

  // Set extraction points.
  if ($ext == 'css') {
    $aggregate_filenames_start = 3 + strlen(ADVAGG_SPACE);
    $aggregate_contents_start = 46 + strlen(ADVAGG_SPACE)*2;
    $hooks_hashes_start = 89 + strlen(ADVAGG_SPACE)*3;
  }
  elseif ($ext == 'js') {
    $aggregate_filenames_start = 2 + strlen(ADVAGG_SPACE);
    $aggregate_contents_start = 45 + strlen(ADVAGG_SPACE)*2;
    $hooks_hashes_start = 88 + strlen(ADVAGG_SPACE)*3;
  }
  else {
    return t('Wrong file type.');
  }

  // Extract info from wanted filename.
  $aggregate_filenames_hash = substr($filename, $aggregate_filenames_start, 43);
  $aggregate_contents_hash = substr($filename, $aggregate_contents_start, 43);
  $hooks_hashes_value = substr($filename, $hooks_hashes_start, 43);

  // Verify that the hooks hashes is valid.
  $aggregate_settings = advagg_get_hash_settings($hooks_hashes_value);
  if (empty($aggregate_settings)) {
    return t('Bad hooks hashes value.');
  }

  return array($ext, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings);
}

/**
 * Get the files that belong inside of this aggregate.
 *
 * @param $filetype
 *   css or js.
 * @param $aggregate_filenames_hash
 *   Hash of the groupings of files.
 * @param $aggregate_contents_hash
 *   Hash of the files contents.
 *
 * @return array
 *   List of files in the order they should be included.
 */
function advagg_get_files_from_hashes($type, $aggregate_filenames_hash, $aggregate_contents_hash) {
  // Create join query for the advagg_files table.
  $subquery_files = db_select('advagg_files', 'af')
    ->fields('af')
    ->condition('af.filetype', $type);
  // Create join query for the advagg_aggregates table.
  $subquery_aggregates = db_select('advagg_aggregates', 'aa')
    ->fields('aa');

  // Create main query for the advagg_aggregates_versions table.
  $query = db_select('advagg_aggregates_versions', 'aav')
    ->condition('aav.aggregate_filenames_hash', $aggregate_filenames_hash)
    ->condition('aav.aggregate_contents_hash', $aggregate_contents_hash);
  $query->join($subquery_aggregates, 'aa', 'aa.aggregate_filenames_hash=aav.aggregate_filenames_hash');
  $query->join($subquery_files, 'af', 'af.filename_hash=aa.filename_hash');
  $query->comment('Query called from ' . __FUNCTION__ . '()');
  $query = $query->fields('af', array('filename'))
    ->fields('aa', array('settings'))
    ->orderBy('porder', 'ASC')
    ->execute();

  // Add in files that are included in this aggregate.
  $files = array();
  foreach ($query as $value) {
    $files[$value->filename] = unserialize($value->settings);
  }
  return $files;
}

// Read CSS/JS files.
/**
 * Given a list of files, grab their contents and glue it into one big string.
 *
 * @param $files
 *   array of filenames.
 * @param $aggregate_settings
 *   array of settings.
 * @return
 *   string containing all the files.
 */
function advagg_get_css_aggregate_contents($files, $aggregate_settings) {
  // Check if CSS compression is enabled.
  $optimize = TRUE;
  if (!empty($aggregate_settings['settings']['no_alters'])) {
    $optimize = FALSE;
  }

  $data = '';
  if (!empty($files)) {
    $media_changes = FALSE;
    $last_media = NULL;
    foreach ($files as $file => $settings) {
      if (!isset($settings['media'])) {
        continue;
      }
      if (is_null($last_media)) {
        $last_media = $settings['media'];
        continue;
      }
      if ($settings['media'] != $last_media) {
        $media_changes = TRUE;
        break;
      }
    }
    $last_media = NULL;
    $import_statements = array();
    module_load_include('inc', 'advagg', 'advagg');
    foreach ($files as $file => $settings) {
      $contents = advagg_load_css_stylesheet($file, $optimize, $aggregate_settings);

      // Allow other modules to modify this files contents.
      // Call hook_advagg_get_css_file_contents_alter().
      if (empty($aggregate_settings['settings']['no_alters'])) {
        drupal_alter('advagg_get_css_file_contents', $contents, $file, $aggregate_settings);
      }

      if ($media_changes) {
        $media_blocks = advagg_parse_media_blocks($contents);
        $contents = '';

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
            $media_rules = substr($css_rules, 6, $start-6);
            // Get everything else besides top level media query.
            $css_selectors_rules = substr($css_rules, $start+1, $end-($start+1));

            // Add in main media rule if needed.
            if (strpos($media_rules, $settings['media']) === FALSE) {
              $media_rules = $settings['media'] . ' ' . $media_rules;
            }
          }
          else {
            $media_rules = $settings['media'];
            $css_selectors_rules = $css_rules;
          }
          // Remove the all rule.
          $media_rules = str_replace('all', '', $media_rules);
          $media_rules = trim($media_rules);
          $css_selectors_rules = trim($css_selectors_rules);

          // Start of stylesheet.
          if (is_null($last_media)) {
            if (!empty($media_rules)) {
              $output = '@media ' . $media_rules . ' {' . $css_selectors_rules;
            }
            else {
              $output = $css_selectors_rules;
            }
          }
          elseif ($media_rules != $last_media) {
            if (!empty($media_rules)) {
              if (!empty($last_media)) {
                $output = "} \n@media " . $media_rules . ' {' . $css_selectors_rules;
              }
              else {
                $output = "\n@media " . $media_rules . ' {' . $css_selectors_rules;
              }
            }
            else {
              $output = "} \n " . $css_selectors_rules;
            }
          }
          else {
            $output = ' ' . $css_selectors_rules;
          }

          $last_media = $media_rules;
          $contents .= $output;
        }

      }
      // Per the W3C specification at
      // http://www.w3.org/TR/REC-CSS2/cascade.html#at-import, @import rules
      // must proceed any other style, so we move those to the top.
      $regexp = '/@import[^;]+;/i';
      preg_match_all($regexp, $contents, $matches);
      $contents = preg_replace($regexp, '', $contents);
      $import_statements[] = array($last_media, $matches[0]);

      // Close any open comment blocks.
      $contents .= '/**/';

      $data .= $contents;
    }

    // Close the final media bracket.
    if ($media_changes && !empty($last_media)) {
      $data .= '}';
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
 * @param $files
 *   array of filenames.
 * @param $aggregate_settings
 *   array of settings.
 * @return
 *   string containing all the files.
 */
function advagg_get_js_aggregate_contents($files, $aggregate_settings) {
  $data = '';

  if (!empty($files)) {
    // Build aggregate JS file.
    foreach ($files as $filename => $settings) {
      $contents = '';
      // Append a ';' and a newline after each JS file to prevent them from
      // running together. Also close any comment blocks.
      if (file_exists($filename)) {
        $contents .= file_get_contents($filename) . ";/**/\n";
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
 * @param $filename
 *   Just the filename no path information.
 * @param $files
 *   array of filenames.
 * @param $type
 *   css or js
 * @param $aggregate_settings
 *   array of settings.
 *
 * @return array
 *   $files_to_save array.
 */
function advagg_save_aggregate($filename, $files, $type, $aggregate_settings) {
  list($css_path, $js_path) = advagg_get_root_files_dir();

  // Build the aggregates contents.
  $contents = '';
  if ($type == 'css') {
    $contents = advagg_get_css_aggregate_contents($files, $aggregate_settings);
    $uri = $css_path[0] . '/' . $filename;
  }
  elseif ($type == 'js') {
    $contents = advagg_get_js_aggregate_contents($files, $aggregate_settings);
    $uri = $js_path[0] . '/' . $filename;
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
      watchdog('advagg', 'Write to file system failed. %uri', array('%uri' => $uri), WATCHDOG_EMERGENCY);
    }
  }
  return $files_to_save;
}

/**
 * Save data to a file.
 *
 * This will use the rename operation ensuring atomic file operations.
 *
 * @param $uri
 *   A string containing the destination location. This must be a stream wrapper
 *   URI.
 * @param $data
 *   A string containing the contents of the file.
 * @param $overwrite
 *   Bool, set to TRUE to overwrite a file.
 */
function advagg_save_data($uri, $data, $overwrite = FALSE) {
  // File already exists.
  if (!$overwrite && file_exists($uri) && filesize($uri) > 0) {
    return;
  }

  // Perform the replace operation. Since there could be multiple processes
  // writing to the same file, the best option is to create a temporary file in
  // the same directory and then rename it to the destination. A temporary file
  // is needed if the directory is mounted on a separate machine; thus ensuring
  // the rename command stays local.

  // Get a temporary filename in the destination directory.
  $temporary_file = drupal_tempnam(drupal_dirname($uri), 'file');
  // Save to temporary filename in the destination directory.
  $filepath = file_unmanaged_save_data($data, $temporary_file, FILE_EXISTS_REPLACE);

  // Perform the rename operation.
  $result = @rename($temporary_file, $uri);
  if (!$result) {
    // Unlink and try again for windows. Rename on windows does not replace
    // the file if it already exists.
    @unlink($uri);
    $result = @rename($temporary_file, $uri);
    // Remove temporary_file if rename failed.
    if (!$result) {
      @unlink($temporary_file);
    }
  }
}

// Helper functions.
/**
 * Send out a fast 404 and exit.
 *
 * @param $msg
 *   Small message reporting why the file didn't get created.
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
 * @param $aggregate_filenames_hash
 *   Hash of the groupings of files.
 * @param $aggregate_contents_hash
 *   Hash of the files contents.
 * @param $uri
 *   URI pointing to the aggregate file.
 *
 * @return
 *   drupal_write_record().
 */
function advagg_get_atime($aggregate_filenames_hash, $aggregate_contents_hash, $uri) {
  // Try to use the cache to avoid hitting the database with a select query.
  $cache_id = 'advagg:db:' . $aggregate_filenames_hash . ADVAGG_SPACE . $aggregate_contents_hash;
  if ($cache = cache_get($cache_id, 'cache_advagg_info')) {
    // If the atime in the cache is less than 12 hours old, use that.
    if (!empty($cache->data['atime']) && $cache->data['atime'] > REQUEST_TIME - (12*60*60)) {
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
 * @see http://stackoverflow.com/questions/14145620/regular-expression-for-media-queries-in-css
 *
 * @param string $css
 *   String of CSS.
 * @return
 *   array of css with only media queries.
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
    $i++;

    // Find the closing bracket for the @media statement.
    while (!empty($s)) {
      // If the character is an opening bracket, push it onto the stack,
      // otherwise pop the stack.
      if ($css[$i] == "{") {
        array_push($s, "{");
      }
      elseif ($css[$i] == "}") {
        array_pop($s);
      }
      $i++;
    }

    // Get CSS before @media and store it.
    if ($last_start != $start) {
      $insert = trim(substr($css, $last_start, $start-$last_start));
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

