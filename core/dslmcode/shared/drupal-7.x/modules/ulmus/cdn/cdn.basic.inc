<?php

/**
 * @file
 * Logic for basic mode ("Origin Pull mode" in the UI).
 */


//----------------------------------------------------------------------------
// Public functions.

/**
 * Gets the servers on which a file is available when basic mode is enabled.
 *
 * @param $path
 *   The path to get the servers for.
 */
function cdn_basic_get_servers($path) {
  static $mapping;
  $servers = array();

  // We only need to parse the textual CDN mapping once into a lookup table.
  if (!isset($mapping)) {
    $mapping = _cdn_basic_parse_raw_mapping(cdn_basic_get_mapping());
  }

  // Parse the file extension from the given path; convert it to lower case.
  $file_extension = drupal_strtolower(pathinfo($path, PATHINFO_EXTENSION));

  // Based on the file extension, determine which key should be used to find
  // the CDN URLs in the mapping lookup table, if any.
  if (array_key_exists($file_extension, $mapping)) {
    $key = $file_extension;
  }
  elseif (array_key_exists('*', $mapping)) {
    $key = '*';
  }
  else {
    $key = NULL;
  }

  // If there is a key to look up the CDN URLs in the mapping lookup table,
  // then build the list of servers.
  if (isset($key)) {
    $base_path = base_path();
    foreach ($mapping[$key] as $cdn_url) {
      $servers[] = array(
        'server' => $cdn_url,
        'url'    => $cdn_url . $base_path . $path,
      );
    }
  }

  return $servers;
}

/**
 * Returns the CDN mapping for HTTP or HTTPS.
 *
 * @return array
 */
function cdn_basic_get_mapping() {
  $https_mapping = variable_get(CDN_BASIC_MAPPING_HTTPS_VARIABLE, '');
  if (!empty($https_mapping) && cdn_serve_from_https()) {
    // if we have https mapping enabled and we are on a HTTPS page
    $mapping = $https_mapping;
  }
  else {
    // otherwise use the non-https mapping
    $mapping = variable_get(CDN_BASIC_MAPPING_VARIABLE, '');
  }

  return $mapping;
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
function _cdn_basic_parse_raw_mapping($mapping_raw) {
  $mapping = array();

  if (!empty($mapping_raw)) {
    $lines = preg_split("/[\n\r]+/", $mapping_raw, -1, PREG_SPLIT_NO_EMPTY);
    foreach ($lines as $line) {
      // Ignore empty lines.
      $line = trim($line);
      if (empty($line)) {
        continue;
      }

      // Parse this line. It may or may not limit the CDN URL to a list of
      // file extensions.
      if (strpos($line, '|') !== FALSE) {
        $parts = explode('|', $line);
        $cdn_urls = explode(' ', trim($parts[0]));
        $extensions = explode(' ', trim(str_replace('.', '', drupal_strtolower($parts[1])))); // Convert to lower case, remove periods, whitespace and split on ' '.
      }
      else {
        $cdn_urls   = explode(' ', trim($line));
        $extensions = array('*'); // Use the asterisk as a wildcard.
      }

      // Remove trailing slash from URLs.
      for ($i = 0; $i < count($cdn_urls); $i++) {
        $cdn_urls[$i] = rtrim($cdn_urls[$i], '/');
      }

      // Create the mapping lookup table.
      foreach ($extensions as $extension) {
        if (!isset($mapping[$extension])) {
          $mapping[$extension] = array();
        }
        $mapping[$extension] = array_merge($mapping[$extension], $cdn_urls);
      }
    }
  }

  return $mapping;
}
