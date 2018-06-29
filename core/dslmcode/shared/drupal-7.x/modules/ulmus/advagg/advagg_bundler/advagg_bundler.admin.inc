<?php

/**
 * @file
 * Admin page callbacks for the advagg bundler module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_bundler_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Bundler'));
  advagg_display_message_if_requirements_not_met();

  $form = array();
  $options = array(
    0 => t('Use HTTP 1.1 settings'),
    2 => t('Use HTTP 2.0 settings'),
    4 => t('Use customized settings'),
  );
  $form['advagg_bundler_admin_mode'] = array(
    '#type' => 'radios',
    '#title' => t('AdvAgg Settings'),
    '#default_value' => variable_get('advagg_bundler_admin_mode', ADVAGG_BUNDLER_ADMIN_MODE),
    '#options' => $options,
    '#description' => t("Default settings will mirror core as closely as possible. <br>Recommended settings are optimized for speed."),
  );

  // Test http2.
  $http2_support = 0;
  $url = 'https://tools.keycdn.com/http2-query.php?url=' . url('', array('absolute' => TRUE));
  if (filter_var($_SERVER['HTTP_HOST'], FILTER_VALIDATE_IP) === FALSE && $_SERVER['HTTP_HOST'] !== 'localhost') {
    $response = drupal_http_request($url, array(
      'timeout' => 3,
    ));
  }
  else {
    $response = new stdClass();
    $response->code = 0;
  }
  if ($response->code == 200 && !empty($response->data)) {
    $http2_support = 1;
    if (stripos($response->data, 'success') !== FALSE) {
      $http2_support = 2;
    }
  }
  if (stripos($_SERVER['SERVER_SOFTWARE'], 'apache') !== FALSE && is_callable('apache_get_modules')) {
    $modules = apache_get_modules();
    $key_a = array_search('mod_http2', $modules);
    $key_b = array_search('mod_h2', $modules);
    if ($key_a !== FALSE || $key_b !== FALSE) {
      $http2_support += 4;
    }
  }
  // Display http2 info.
  if ($http2_support & 2) {
    $description = t('This server supports HTTP 2.0; the test from @url came back ok.', array('@url' => $url));
  }
  else {
    if ($http2_support == 0) {
      $description = t('AdvAgg can not detect if this server supports HTTP 2.0. You can <a href="@url">go here to learn how to enable it</a>.', array('@url' => 'https://httpd.apache.org/docs/2.4/mod/mod_http2.html'));
    }
    elseif ($http2_support & 4) {
      $description = t('It appears that this server could support HTTP 2.0 (apache <a href="@url">mod_http2</a> found)', array(
        '@url' => 'https://httpd.apache.org/docs/2.4/mod/mod_http2.html',
      ));
      if ($http2_support & 1) {
        $description .= t(', but it may not be configured to do so. The test from <a href="@test">here</a> was inconclusive.', array(
          '@test' => $url,
        ));
      }
      else {
        if (count($response) == 1) {
          $description .= t(', but the test from <a href="@test">here</a> was not actually done due to the URL being an IP address or localhost.', array(
            '@test' => $url,
          ));
        }
        else {
          $description .= t(', but the test from <a href="@test">here</a> was inconclusive.', array(
            '@test' => $url,
          ));
        }
      }
    }
    else {
      $description = t('This server does not support HTTP 2.0.');
    }
    $description .= ' ' . t('<a href="@url">This guide</a> can help you get http2 enabled on your site.', array('@url' => 'https://geekflare.com/http2-implementation-apache-nginx/'));
  }
  if (!empty($description)) {
    $form['advagg_http2'] = array(
      '#markup' => "<p>{$description}</p>",
    );
  }

  $form['global_container'] = array(
    '#type' => 'container',
    '#hidden' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="advagg_bundler_admin_mode"]' => array('value' => '4'),
      ),
    ),
  );

  $form['global_container']['advagg_bundler_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bundler is Active (recommended)'),
    '#default_value' => variable_get('advagg_bundler_active', ADVAGG_BUNDLER_ACTIVE),
    '#description' => t('If not checked, the bundler will passively monitor your site, but it will not split up aggregates.'),
  );

  $options = array(
    0 => 0,
    1 => 1,
    2 => 2,
    3 => 3,
    4 => 4,
    5 => 5,
    6 => 6,
    7 => 7,
    8 => 8,
    9 => 9,
    10 => 10,
    11 => 11,
    12 => 12,
    13 => 13,
    14 => 14,
    15 => 15,
    16 => 16,
    17 => 17,
    18 => 18,
    19 => 19,
    20 => 20,
    21 => 21,
    22 => 22,
    23 => 23,
    24 => 24,
    25 => 25,
  );
  $form['global_container']['advagg_bundler_max_css'] = array(
    '#type' => 'select',
    '#title' => t('Target Number Of CSS Bundles Per Page'),
    '#default_value' => variable_get('advagg_bundler_max_css', ADVAGG_BUNDLER_MAX_CSS),
    '#options' => $options,
    '#description' => t('If 0 is selected then the bundler is disabled. 2 is recommended for HTTP 1.1 and 25 for HTTP 2.0.'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-bundler-active' => array('checked' => FALSE),
      ),
    ),
    '#recommended_value' => 25,
  );
  $form['global_container']['advagg_bundler_max_js'] = array(
    '#type' => 'select',
    '#title' => t('Target Number Of JS Bundles Per Page'),
    '#default_value' => variable_get('advagg_bundler_max_js', ADVAGG_BUNDLER_MAX_JS),
    '#options' => $options,
    '#description' => t('If 0 is selected then the bundler is disabled. 5 is recommended for HTTP 1.1 and 25 for HTTP 2.0.'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-bundler-active' => array('checked' => FALSE),
      ),
    ),
    '#recommended_value' => 25,
  );

  $form['global_container']['advagg_bundler_grouping_logic'] = array(
    '#type' => 'radios',
    '#title' => t('Grouping logic'),
    '#default_value' => variable_get('advagg_bundler_grouping_logic', ADVAGG_BUNDLER_GROUPING_LOGIC),
    '#options' => array(
      0 => t('File count'),
      1 => t('File size'),
    ),
    '#description' => t('If file count is selected then each bundle will try to have a similar number of original files aggregated inside of it. If file size is selected then each bundle will try to have a similar file size.'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-bundler-active' => array('checked' => FALSE),
      ),
    ),
    '#recommended_value' => 0,
  );

  $form['global_container']['info'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Raw Grouping Info'),
  );
  module_load_include('inc', 'advagg', 'advagg.admin');
  $analysis = advagg_bundler_analysis('', TRUE);

  $rawtext = print_r($analysis, TRUE);
  $form['global_container']['info']['advagg_bundler_info'] = array(
    '#type' => 'textarea',
    '#title' => t('%count different groupings', array('%count' => count($analysis))),
    '#default_value' => $rawtext,
    '#rows' => 30,
  );

  // Clear the cache bins on submit. Also remove advagg_bundler_info so it
  // doesn't get added to the variable table.
  $form['#submit'][] = 'advagg_bundler_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Submit callback, clear out the advagg cache bin.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_bundler_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();

  // Unset advagg_bundler_info.
  if (isset($form_state['values']['advagg_bundler_info'])) {
    unset($form_state['values']['advagg_bundler_info']);
  }

  // Reset this form to defaults or recommended values; also show what changed.
  advagg_set_admin_form_defaults_recommended($form_state, 'advagg_bundler_admin_mode');
}
