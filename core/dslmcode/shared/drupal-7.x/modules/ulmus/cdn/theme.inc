<?php

/**
 * @file
 * Theme functions.
 */

/**
 * Render the CDN integration page statistics.
 *
 * @param $variables
 *   An associative array containing:
 *   - file_count: The number of files detected on this page.
 *   - cdn_file_count: The number of files on this page that are served from a
 *     CDN.
 *   - synced_files_per_server_count: The number of files synced to each
 *     server.
 *   - total_time: The total time it took to get all current CDN URLs.
 *   - synced_files: Array of synchronized files.
 *   - unsynced_files: Array of unsynchronized files.
 * @return
 *   The rendered HTML.
 */
function theme_cdn_page_stats($variables) {
  $file_count                    = $variables['file_count'];
  $cdn_file_count                = $variables['cdn_file_count'];
  $synced_files_per_server_count = $variables['synced_files_per_server_count'];
  $total_time                    = $variables['total_time'];
  $synced_files                  = $variables['synced_files'];
  $unsynced_files                = $variables['unsynced_files'];

  $output = '';
  $items = array();
  $mode = variable_get(CDN_MODE_VARIABLE, CDN_MODE_BASIC);

  $percentage = 100;
  if ($file_count > 0) {
    $percentage = number_format($cdn_file_count / $file_count * 100);
  }
  $avg_time = 0;
  if ($file_count > 0) {
    $avg_time = round($total_time * 1000 / $file_count, 3);
  }

  $output .= '<div id="cdn-integration-page-stats">';
  $items[] = t(
    'Total number of files on this page: <strong>!file-count</strong>.',
    array('!file-count' => $file_count)
  );
  $items[] = t(
    'Number of files served from CDNs: <strong>!cdn-file-count</strong>
    (!pct% coverage).',
    array('!cdn-file-count' => $cdn_file_count, '!pct' => $percentage)
  );
  $items[] = t(
    'Total time altering file URLs: !total ms, or !avg ms per file.',
    array(
      '!total' => round($total_time * 1000, 3),
      '!avg'   => $avg_time,
    )
  );

  // Nested list of unsynced files.
  if (count($unsynced_files)) {
    $unsynced_items = array();
    foreach ($unsynced_files as $file) {
      $unsynced_items[] = theme('cdn_page_stats_file_link', array(
        'file'          => $file,
        'absolute_path' => file_create_url($file),
        'synced'        => FALSE,
        'cdn_url'       => $file,
        'server'        => NULL,
      ));
    }
    $item = t('Files not served from the CDN:');
    $item .= theme('item_list', array(
      'items'      => $unsynced_items,
      'attributes' => array('class' => 'file-list'),
    ));
    $items[] = $item;
  }

  // Nested list of synced files.
  if (count($synced_files)) {
    $synced_items = array();
    foreach ($synced_files as $synced_file) {
      $file    = $synced_file['file'];
      $cdn_url = $synced_file['cdn_url'];
      $server  = $synced_file['server'];

      if (!isset($synced_items[$server])) {
        $synced_items[$server] = array();
      }
      $synced_items[$server][] = theme('cdn_page_stats_file_link', array(
        'file'          => $file,
        'absolute_path' => $synced_file['absolute path'],
        'synced'        => TRUE,
        'cdn_url'       => $cdn_url,
        'server'        => $server,
      ));
    }
    $synced_by_server = array();
    foreach (array_keys($synced_items) as $server) {
      $c = $synced_files_per_server_count[$server];
      $item = t(
        '<strong>!pct%</strong> of files served from %server (!count files):',
        array(
          '%server' => $server,
          '!count'  => $c,
          '!pct'    => number_format($c / $cdn_file_count * 100),
        )
      );
      $item .= theme('item_list', array(
        'items'      => $synced_items[$server],
        'attributes' => array('class' => 'file-list'),
      ));
      $synced_by_server[] = $item;
    }
    $item = t('Files served from the CDN:');
    $item .= theme('item_list', array('items' => $synced_by_server));
    $items[] =  $item;
  }

  $title = t('CDN integration statistics for %drupal_path', array(
    '%drupal_path' => $_GET['q']
  ));
  $output .= theme('item_list', array(
    'items' => $items,
    'title' => '<strong>' . $title . '</strong>',
  ));
  $output .= '</div>';
  return $output;
}

/**
 * Render a file link in the CDN integration page statistics.
 *
 * @param $variables
 *   An associative array containing:
 *   - file: A string containing the Drupal path (i.e. path relative to the
 *     Drupal root directory) of the file to generate the URL for.
 *   - absolute_path: The absolute path (on the filesystem) to the file.
 *   - synced: Whether this file has been synced to the CDN or not.
 *   - cdn_url: The CDN URL of the file, or the normal URL when the file is
 *     not on a CDN.
 *   - server: The server on which the file resides.
 * @return
 *   The rendered HTML.
 */
function theme_cdn_page_stats_file_link($variables) {
  $file          = $variables['file'];
  $absolute_path = $variables['absolute_path'];
  $synced        = $variables['synced'];
  $cdn_url       = $variables['cdn_url'];
  $server        = $variables['server'];

  $file_link = l(
    t('!file', array('!file' => $file)),
    $cdn_url,
    array(
      'external'   => TRUE,
      'attributes' => array('title' => $absolute_path),
    )
  );
  $touch_link = l(
    t('touch'),
    'admin/cdn/touch/' . $file,
    array('query' => drupal_get_destination())
  );

  $output = '';
  $output .= '<span class="file-link">' . $file_link;
  if ($synced) {
    $output .= '<span class="touch-link">';
    $output .=   '<span class="arrow">' . t('→') . '</span>';
    $output .=   $touch_link;
    $output .=   '<span class="touch-help">';
    $output .=   t('Touching this file will trigger a resync to the CDN.');
    $output .=   '</span>';
    $output .= '</span>';
  }
  $output .= '</span>';
  return $output;
}
