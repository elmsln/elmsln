<?php

/**
 * @file
 *   Admin include for Modernizr module.
 */

/**
 * Implements hook_admin().
 *
 * Modernizr administration settings
 */
function modernizr_admin() {
  $form = array();

  // Fieldset for drupal_add_js() options.
  $form['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('Placement and Performance'),
  );

  // Option to set the scope of Modernizr.
  $form['js']['modernizr_scope'] = array(
    '#type' => 'select',
    '#title' => t('Where should Modernizr be loaded?'),
    '#options' => array(
      'header' => t('header'),
      'footer' => t('footer'),
    ),
    '#default_value' => variable_get('modernizr_scope', MODERNIZR_SCOPE_DEFAULT),
    '#description' => t('When possible, it is recommended to print all JavaScript in the footer unless you are using a specific set of features which require blocking execution in the &lt;head&gt;. <a href="@url">Read more on GitHub</a>. <strong>Important:</strong> you should not move Modernizr to the bottom of the page unless ALL dependent scripts are also after Modernizr (higher weight in <code>drupal_add_js()</code> settings).', array('@url' => 'https://github.com/Modernizr/Modernizr/issues/878#issuecomment-41448059')),
  );

  // Options to determine how Modernizr is included. Although these options are
  // presented as one group, they control two settings within drupal_add_js()
  // because an inline file cannot be deferred. If inline is set, it precludes
  // us from setting `defer` to TRUE. Conversely if `defer` is chosen, we must
  // set the type to `file` when invoking drupal_add_js().
  $form['js']['modernizr_type'] = array(
    '#type' => 'select',
    '#title' => t('How should Modernizr be loaded?'),
    '#options' => array(
      'defer' => t('Defer'),
      'inline' => t('Inline'),
      'sync' => t('Synchronous'),
    ),
    '#default_value' => variable_get('modernizr_type', MODERNIZR_TYPE_DEFAULT),
    '#description' => t('When possible, it is recommended to <code>defer</code> this JavaScript unless you are using a specific set of features which require blocking execution in the &lt;head&gt;. <strong>Important:</strong> you should not defer Modernizr unless any dependent scripts are also deferred.<br><br>In some cases, it might be beneficial to inline this JavaScript file. Make sure that you can confirm that this works better for your site by measuring performance! <a href="@url">Read more on GitHub</a>.', array('@url' => 'https://github.com/Modernizr/Modernizr/issues/878#issuecomment-41448059')),
  );

  // Fieldset for custom build options.
  $form['build_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Build Options'),
  );

  // Custom builds no longer require printshiv by default.
  $form['build_options']['modernizr_cb_printshiv'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require <code>printshiv</code> when custom builds are created.'),
    '#default_value' => variable_get('modernizr_cb_printshiv', FALSE),
  );

  // Modernizr v3 deprecated direct inclusion of Modernizr.load(). In order to
  // continue using Modernizr.load(), we have to include yepnope.js ourselves.
  $form['build_options']['modernizr_cb_load'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include <code>Modernizr.load()</code> functionality. Modernizr v3 no longer includes this script itself. <a href="@url">Read more on GitHub</a>.', array('@url' => 'https://github.com/Modernizr/Modernizr/issues/1182')),
    '#default_value' => variable_get('modernizr_cb_load', MODERNIZR_YEPNOPE_DEFAULT),
  );

  // Fieldset for reporting options.
  $form['reporting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Error reporting'),
  );

  // Reduce severity of requirements errors. Admin can use this option to avoid
  // seeing the red boxes when Modernizr requirements are not met.
  $form['reporting']['modernizr_quiet'] = array(
    '#type' => 'checkbox',
    '#title' => t('Decrease severity of Modernizr Test API errors.'),
    '#description' => t('Check this box if you\'d rather not see the red warning about missing Modernizr tests (or lack of a custom build). Enabling this option will not make Modernizr function properly if things are missing, but it will suppress the error message.'),
    '#default_value' => variable_get('modernizr_quiet', MODERNIZR_QUIET_DEFAULT),
  );

  return system_settings_form($form);
}


/**
 * Generates new Modernizr URL for admin interface
 * Callback for 'admin/config/development/modernizr'.
 */
function modernizr_generate_url() {
  // Reset our lists of needed Modernizr tests in drupal_static.
  drupal_static_reset('modernizr_api_list');

  // Get latest tests from modules and themes
  $tests = modernizr_api_list();

  // Begin assembling link to re-download Modernizr
  $link = 'https://modernizr.com/download/#-';

  // Pull tests that are currently set.
  $current_tests = _modernizr_current_build();

  if (is_null($current_tests)) {
    // We can't find a custom build of modernizr.
    // Decide how severe this warning is based on admin settings.
    $modernizr_severity = (variable_get('modernizr_quiet', MODERNIZR_QUIET_DEFAULT)) ? 'warning' : 'error';

    // Set error/warning message.
    drupal_set_message(t("You don't seem to have a custom build of Modernizr installed yet, or we are detecting the wrong version. Remove any existing modernizr-latest.js or modernizr custom builds from !path and replace it with a new copy. This page will help generate one for you.", array(
      '!path' => module_exists('libraries') ? libraries_get_path('modernizr') : 'sites/all/libraries/modernizr'
    )), $modernizr_severity);
  }
  else {
    // Generate the list of tests that are being requested by the Test API, but
    // are NOT in the Modernizr JS file.
    $missing_tests = array_diff_key($tests, array_flip($current_tests));

    foreach ($current_tests as $current_test) {
      // Adds all current tests to the array of tests.
      if (!isset($tests[$current_test])) {
        $tests[$current_test] = array(
          'name' => $current_test,
          'source' => array(modernizr_get_filename()),
          'desc' => _modernizr_get_desc($current_test),
          'docs' => '',
          'caniuse' => '',
        );
      }
    }
  }

  // Create indexes for first download link/desc to place them
  // above everything. They will be populated later.
  $elements['download_modernizr1']['link'] = array();
  $elements['download_modernizr1']['description'] = array();

  // Create the tests heading render element.
  $elements['tests']['heading-tests'] = array(
    '#theme' => 'html_tag',
    '#value' => t('Current Modernizr Tests'),
    '#tag' => 'h2',
  );

  // Create the tests description render element.
  $elements['tests']['description'] = array(
    '#theme' => 'html_tag',
    '#value' => t('Currently enabled Drupal modules and themes have requested the following Modernizr tests:'),
    '#tag' => 'p',
  );

  // Create a container to indent everything
  $elements['tests']['list'] = array(
    '#prefix' => '<div class="modernizr-tests">',
    '#suffix' => '</div>',
  );

  // Check to see if there are any registered tests.
  if (!empty($tests)) {
    // Loop through each registered test.
    foreach ($tests as $key => $test) {
      // API was changed between 7.x-3.0 and 7.x-3.1. We originally specified
      // `module` but since themes can also specify tests the attribute was
      // changed to `source`.
      $source = (isset($test['source'])) ? $test['source'] : $test['module'];

      // Check to see if this test has been set. If not, add it.
      if (!isset($elements['tests']['list'][$key])) {
        // Check if this test is missing, and apply a special class only when it
        // is missing from the current build of Modernizr JS file.
        $not_included = (isset($missing_tests[$key])) ? 'not-included' : '';

        // Build the element for this Modernizr test.
        $elements['tests']['list'][$key]['name'] = array(
          '#theme' => 'html_tag',
          '#value' => $key,
          '#tag' => 'h3',
          '#attributes' => array('class' => $not_included),
        );
      }

      // Create the description for this test.
      $elements['tests']['list'][$key]['tests'][] = array(
        'description' => array(
          '#markup' => _modernizr_get_desc($key),
          '#prefix' => '<p class="desc">',
          '#suffix' => '</p>',
        ),
      );

      // @TODO: Check to see if this test has already been added by another module.
      $link .= $key . '-';
    }
  }
  else {
    $elements['tests']['list']['#markup'] = '<p>There are no Modernizr tests registered</p>';
  }

  // Create the download link render element.
  $download_link = array(
    '#prefix' => '<div class="download-modernizr">',
    '#theme' => 'link',
    '#text' => t('Download your Modernizr production build'),
    '#path' => substr($link, 0, -1), // Truncate the last hyphen.
    '#options' => array(
      'attributes' => array(
        'class' => array(
          'button',
        ),
        'target' => '_blank',
      ),
      'html' => FALSE,
    ),
    '#suffix' => '</div>',
  );

  // Create the download description render element.
  $download_desc = array(
    '#theme' => 'html_tag',
    '#value' => t('The button links to a custom Modernizr build based on the tests listed above. <br/> Once you download the script, place it inside <b>!path</b> and !cc.', array(
      '!path' => module_exists('libraries') ? libraries_get_path('modernizr') : 'sites/all/libraries/modernizr',
      '!cc' => l(t('clear your cache'), 'admin/config/development/performance'),
    )),
    '#tag' => 'p',
  );

  // Print the Download link above and below the tests.
  $elements['download_modernizr1']['link'] = $download_link;
  $elements['download_modernizr2']['link'] = $download_link;

  // Print the Download description above and below the tests.
  $elements['download_modernizr1']['description'] = $download_desc;
  $elements['download_modernizr2']['description'] = $download_desc;

  // Load admin CSS
  drupal_add_css(drupal_get_path('module', 'modernizr') . '/css/modernizr.admin.css');

  return $elements;
}
