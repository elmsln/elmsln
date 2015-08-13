<?php
/**
 * @file
 * Admin forms and functionality for CSS Delivery Optimization.
 */

/**
 * Postback callback for AJAX calls to save the generated critical css.
 */
function css_delivery_postback() {

  if (!$_POST['css'] || !$_POST['op']) {
    $output = array(
      'status' => 'error',
      'message' => t('No data is sent.'),
    );
    drupal_json_output($output);
    drupal_exit();
  }

  $output = array();
  $critical_css = urldecode($_POST['css']);

  switch ($_POST['op']) {
    case 'save':
      variable_set('css_delivery_css', $critical_css);
      $output['status'] = 'ok';
      $output['message'] = t('Done. The resulting Critical CSS can be revised on the <a href="@url">settings page</a>.', array('@url' => url('admin/config/development/performance/css-delivery')));
      drupal_json_output($output);
      break;

    case 'download':
      $output['status'] = 'ok';
      $output['message'] = t('Done. The resulting Critical CSS has been sent for downloading.');
      drupal_add_http_header('Content-Description', 'File Transfer');
      drupal_add_http_header('Content-Type', 'application/octet-stream');
      drupal_add_http_header('Content-Disposition', 'attachment; filename=critical-' . format_date(time(), 'custom', 'Ymd-Hmi') . '.css');
      drupal_add_http_header('Expires', '0');
      drupal_add_http_header('Content-Length', strlen($critical_css));
      flush();
      print $critical_css;
      break;
  }

  drupal_exit();
}
