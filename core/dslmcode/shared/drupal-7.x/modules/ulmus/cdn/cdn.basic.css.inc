<?php

/**
 * @file
 * Overrides of Drupal's CSS aggregation system. Ensures that files referenced
 * by CSS files are also served from the CDN, according to the CDN module's
 * CSS aggregation rules.
 */


/**
 * Near-identical to @see drupal_aggregate_css().
 *
 * Changes: call _cdn_build_css_cache() instead of drupal_build_css_cache().
 */
function _cdn_aggregate_css(&$css_groups) {
  // Don't override Drupal core's aggregation if this page is not going to use
  // a CDN anyway.
  if (!cdn_check_protocol() && !cdn_check_drupal_path($_GET['q'])) {
    return;
  }

  $preprocess_css = (variable_get('preprocess_css', FALSE) && (!defined('MAINTENANCE_MODE') || MAINTENANCE_MODE != 'update'));

  // For each group that needs aggregation, aggregate its items.
  foreach ($css_groups as $key => $group) {
    switch ($group['type']) {
      // If a file group can be aggregated into a single file, do so, and set
      // the group's data property to the file path of the aggregate file.
      case 'file':
        if ($preprocess_css) {
          if ($group['preprocess']) {
            $css_groups[$key]['data'] = _cdn_build_css_cache($group['items']);
          }
          else {
            $suffix = '';
            if (count($group['items']) == 1) {
              $suffix .= '_' . basename($group['items'][0]['data']);
            }
            $css_groups[$key]['data'] = _cdn_build_css_cache($group['items'], $suffix);
          }
        }
        break;
      // Aggregate all inline CSS content into the group's data property.
      case 'inline':
        $css_groups[$key]['data'] = '';
        foreach ($group['items'] as $item) {
          $css_groups[$key]['data'] .= drupal_load_stylesheet_content($item['data'], $item['preprocess']);
        }
        break;
    }
  }
}

/**
 * Near-identical to @see drupal_build_css_cache().
 *
 * Changes:
 * - the inner loop is modified
 * - uses _cdn_build_css_path() instead of drupal_build_css_path().
 */
function _cdn_build_css_cache($css, $suffix = '') {
  // Create different CSS aggregation maps for HTTP and HTTPS.
  $https_mapping = variable_get(CDN_BASIC_MAPPING_HTTPS_VARIABLE, '');
  $css_cache_var = (!empty($https_mapping) && cdn_serve_from_https())
    ? 'cdn_css_cache_files_https'
    : 'cdn_css_cache_files_http';

  $data = '';
  $uri = '';
  $map = variable_get($css_cache_var, array());
  // Create a new array so that only the file names are used to create the hash.
  // This prevents new aggregates from being created unnecessarily.
  $css_data = array();
  foreach ($css as $css_file) {
    $css_data[] = $css_file['data'];
  }
  $key = hash('sha256', serialize($css_data));
  if (isset($map[$key])) {
    $uri = $map[$key];
  }

  if (empty($uri) || !file_exists($uri)) {
    // Build aggregate CSS file.
    foreach ($css as $stylesheet) {
      // Only 'file' stylesheets can be aggregated.
      if ($stylesheet['type'] == 'file') {
        $contents = drupal_load_stylesheet($stylesheet['data'], TRUE);

        // Get the parent directory of this file, relative to the Drupal root.
        $css_base_url = drupal_substr($stylesheet['data'], 0, strrpos($stylesheet['data'], '/'));
        _cdn_build_css_path(NULL, $css_base_url . '/');

        // Anchor all paths in the CSS with its base URL, ignoring external and absolute paths.
        $data .= preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_cdn_build_css_path', $contents);
      }
    }

    // Per the W3C specification at http://www.w3.org/TR/REC-CSS2/cascade.html#at-import,
    // @import rules must proceed any other style, so we move those to the top.
    $regexp = '/@import[^;]+;/i';
    preg_match_all($regexp, $data, $matches);
    $data = preg_replace($regexp, '', $data);
    $data = implode('', $matches[0]) . $data;

    // Prefix filename to prevent blocking by firewalls which reject files
    // starting with "ad*".
    $filename = 'css_' . drupal_hash_base64($data) . $suffix . '.css';
    // Create the css/ within the files folder.
    $csspath = ($css_cache_var == 'cdn_css_cache_files_https')
      ? 'public://cdn/css/https'
      : 'public://cdn/css/http';
    $uri = $csspath . '/' . $filename;
    // Create the CSS file.
    file_prepare_directory($csspath, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    if (!file_exists($uri) && !file_unmanaged_save_data($data, $uri, FILE_EXISTS_REPLACE)) {
      return FALSE;
    }
    // If CSS gzip compression is enabled, clean URLs are enabled (which means
    // that rewrite rules are working) and the zlib extension is available then
    // create a gzipped version of this file. This file is served conditionally
    // to browsers that accept gzip using .htaccess rules.
    if (variable_get('css_gzip_compression', TRUE) && variable_get('clean_url', 0) && extension_loaded('zlib')) {
      if (!file_exists($uri . '.gz') && !file_unmanaged_save_data(gzencode($data, 9, FORCE_GZIP), $uri . '.gz', FILE_EXISTS_REPLACE)) {
        return FALSE;
      }
    }
    // Save the updated map.
    $map[$key] = $uri;
    variable_set($css_cache_var, $map);
  }
  return $uri;
}

/**
 * Near-identical to @see drupal_build_css_path().
 *
 * Changes: apply file_create_url() to every file!
 */
function _cdn_build_css_path($matches, $base = NULL) {
  $_base = &drupal_static(__FUNCTION__);
  // Store base path for preg_replace_callback.
  if (isset($base)) {
    $_base = $base;
  }

  // Prefix with base and remove '../' segments where possible.
  $path = $_base . $matches[1];
  $last = '';
  while ($path != $last) {
    $last = $path;
    $path = preg_replace('`(^|/)(?!\.\./)([^/]+)/\.\./`', '$1', $path);
  }

  return 'url(' . file_create_url($path) . ')';
}
