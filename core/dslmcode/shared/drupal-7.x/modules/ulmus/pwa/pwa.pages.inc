<?php
/**
 * @file
 */

/**
 * Deliver the JS for the service worker.
 *
 * Adds a Service-Worker-Allowed header so that a file served from
 * '/pwa/X/serviceworker.js' can have a scope of '/'.
 */
function pwa_deliver_js_file($page_callback_result) {
  drupal_add_http_header('Content-Type', 'application/javascript');
  drupal_add_http_header('Service-Worker-Allowed', '/');
  print $page_callback_result;
}

/**
 * Returns the JS of the service worker.
 *
 * @return mixed
 */
function pwa_serviceworker_file_data($version = 1) {
  $data = cache_get('pwa:serviceworker', 'cache');
  if ($data) {
    $data = $data->data;
  }
  else {
    $data = pwa_serviceworker_file();
    cache_set('pwa:serviceworker', $data, 'cache');
  }

  return $data;
}

/**
 * Default page when for when the user has no connection.
 *
 * @todo template like maintenance page?
 *
 * @return string
 */
function pwa_offline_page() {
  return [
    '#theme' => 'html_tag',
    '#tag' => 'h1',
    '#value' => 'You are offline.',
    '#attributes' => [
      'data-drupal-pwa-offline' => TRUE,
    ],
  ];
}
