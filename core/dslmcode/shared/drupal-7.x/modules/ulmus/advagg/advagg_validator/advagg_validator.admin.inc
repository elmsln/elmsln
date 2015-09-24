<?php

/**
 * @file
 * Admin page callbacks for the advagg validator module.
 */

/**
 * Form builder; CSS validator via w3.
 *
 * @return array
 *   form array.
 */
function advagg_validator_admin_css_w3_form() {
  drupal_set_title(t('AdvAgg: CSS Validator using w3.org'));

  $form = advagg_validator_admin_form_generator('css', FALSE);

  // Add notice that using this form will submit files to a remote server.
  $form['notice'] = array(
    '#markup' => '<div>' . t('Notice: The form below will submit files to the <a href="http://jigsaw.w3.org/css-validator/">http://jigsaw.w3.org/css-validator/</a> service if used.') . '</div>',
    '#weight' => -1,
  );

  return $form;
}

/**
 * Form builder; CSS validator via csslint.
 *
 * @return array
 *   form array.
 */
function advagg_validator_admin_css_lint_form() {
  drupal_set_title(t('AdvAgg: CSS Validator using CSSLINT'));

  $form = advagg_validator_admin_form_generator('css', TRUE);

  $form['#attached']['js'][] = array(
    // https://github.com/CSSLint/csslint.
    'data' => '//cdn.rawgit.com/stubbornella/csslint/master/release/csslint.js',
    'type' => 'external',
  );
  $form['#attached']['js'][] = array(
    'data' => drupal_get_path('module', 'advagg_validator') . '/advagg_validator.js',
    'type' => 'file',
  );

  // Comma separated code.
  // https://github.com/CSSLint/csslint/wiki/Command-line-interface#--ignore
  $ignore_list = variable_get('advagg_validator_csslint_ignore', ADVAGG_VALIDATOR_CSSLINT_IGNORE);
  if (is_array($ignore_list)) {
    $ignore_list = implode(',', $ignore_list);
  }
  $form['#attached']['js'][] = array(
    'data' => array('csslint' => array('ignore' => $ignore_list)),
    'type' => 'setting',
  );

  return $form;
}

/**
 * Form builder; CSS validator via jshint.
 *
 * @return array
 *   form array.
 */
function advagg_validator_admin_js_hint_form() {
  drupal_set_title(t('AdvAgg: JavaScript Validator using JSHINT'));

  $form = advagg_validator_admin_form_generator('js', TRUE);

  $form['#attached']['js'][] = array(
    // https://github.com/jshint/jshint.
    'data' => '//cdn.rawgit.com/jshint/jshint/master/dist/jshint.js',
    'type' => 'external',
  );
  $form['#attached']['js'][] = array(
    'data' => drupal_get_path('module', 'advagg_validator') . '/advagg_validator.js',
    'type' => 'file',
  );
  // Define JSHINT options from https://drupal.org/node/1955232
  $settings = array(
    'browser' => TRUE,
    'curly' => TRUE,
    'eqeqeq' => TRUE,
    'forin' => TRUE,
    'latedef' => TRUE,
    'newcap' => TRUE,
    'noarg' => TRUE,
    'strict' => TRUE,
    'trailing' => TRUE,
    'undef' => TRUE,
    'unused' => TRUE,
    'predef' => array(
      'Drupal' => FALSE,
      'drupalSettings' => FALSE,
      'domready' => FALSE,
      'jQuery' => FALSE,
      '_' => FALSE,
      'matchMedia' => FALSE,
      'Backbone' => FALSE,
      'Modernizr' => FALSE,
      'VIE' => FALSE,
      'CKEDITOR' => FALSE,
    ),
  );

  // Comma separated code.
  // https://jslinterrors.com/
  $ignore_list = variable_get('advagg_validator_jshint_ignore', ADVAGG_VALIDATOR_JSHINT_IGNORE);
  if (is_array($ignore_list)) {
    $ignore_list = implode(',', $ignore_list);
  }
  $settings['ignore'] = $ignore_list;

  $form['#attached']['js'][] = array(
    'data' => array('jshint' => $settings),
    'type' => 'setting',
  );

  return $form;
}

/**
 * Scan the file system and build a form tree from it.
 *
 * @param string $type
 *   String: css or js.
 * @param bool $run_client_side
 *   Set to TRUE to run the checking code client side.
 *
 * @return array
 *   form array.
 */
function advagg_validator_admin_form_generator($type, $run_client_side) {
  $form = array();
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  $files = advagg_validator_scan_all_dirs($type);
  rsort($files);
  foreach ($files as $file) {
    $dir = dirname($file);

    // Build the direcotry structure.
    $levels = explode('/', $dir === '.' ? '{ROOT}' : $dir);
    $point = &$form;
    $built = array();
    foreach ($levels as $key => $value) {
      // Build direcotry structure,
      $built[] = $value;
      $point = &$point[$value];
      if (!is_array($point)) {
        $form_api_dirname = str_replace(array('/', '.'), array('__', '--'), $dir);
        $wrapper = 'advagg-validator-' . $type . '-validator-ajax' . $form_api_dirname;

        $point = array(
          '#type' => 'fieldset',
          '#title' => check_plain($value),
          '#description' => '<strong>' . t('Directory:') . ' </strong>' . check_plain(implode('/', $built)),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#weight' => 100,
        );
        if (!isset($point['check_all_levels']) && $value !== '{ROOT}') {
          $point['check_all_levels'] = array(
            '#type' => 'submit',
            '#value' => t('Check this Directory and all Subdirectories: @dirname', array('@dirname' => implode('/', $built))),
          );
          if (!$run_client_side) {
            $point['check_all_levels'] += array(
              '#submit' => array('advagg_validator_admin_test_advagg_' . $type . '_subdirectory_submit'),
              '#ajax' => array(
                'callback' => 'advagg_validator_admin_test_advagg_' . $type . '_subdirectory_callback',
                'wrapper' => $wrapper,
              ),
            );
          }
          else {
            $point['check_all_levels'] += array(
              '#attributes' => array(
                'class' => array('advagg_validator_recursive_' . $type),
              ),
            );
          }
        }
        $point['break'] = array(
          '#markup' => '<div></div>',
        );

        $point['wrapper'] = array(
          '#markup' => "<div id='" . $wrapper . "' class='results'></div>",
          '#weight' => 90,
        );
      }

      // Drop in button and info if we reached the point where a file lives.
      if (count($levels) == $key + 1) {
        $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $file);

        if (!isset($point['check_this_level'])) {
          $point['check_this_level'] = array(
            '#type' => 'submit',
            '#value' => t('Check this Directory: @dirname', array('@dirname' => $dir)),
          );
          if (!$run_client_side) {
            $point['check_this_level'] += array(
              '#submit' => array('advagg_validator_admin_test_advagg_' . $type . '_directory_submit'),
              '#ajax' => array(
                'callback' => 'advagg_validator_admin_test_advagg_' . $type . '_directory_callback',
                'wrapper' => $wrapper,
              ),
            );
          }
          else {
            $point['check_this_level'] += array(
              '#attributes' => array(
                'class' => array('advagg_validator_' . $type),
              ),
            );
          }
        }
        if (!isset($point['start'])) {
          $point['start'] = array(
            '#markup' => '<br /><strong>' . t('File:') . ' </strong><div class="filenames">',
          );
        }
        else {
          $point['start'] = array(
            '#markup' => '<br /><strong>' . t('Files:') . ' </strong><div class="filenames">',
          );
        }
        $point[$form_api_filename] = array(
          '#markup' => check_plain($file) . " </br>\n",
        );
        if (!isset($point['end'])) {
          $point['end'] = array(
            '#markup' => '</div>',
          );
        }

        $point['hidden_' . $form_api_filename] = array(
          '#type' => 'hidden',
          '#value' => $file,
          '#attributes' => array(
            'class' => array('filenames'),
          ),
        );

      }
    }
  }
  return $form;
}


// Submit callbacks.
/**
 * Display file info in a drupal message.
 */
function advagg_validator_admin_test_advagg_css_submit($form, &$form_state) {
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  // @codingStandardsIgnoreLine
  if (!empty($form_state['input']['ajax_page_state'])) {
    return;
  }
  $info = advagg_validator_test_advagg_css();
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . check_plain(print_r($info, TRUE)) . '</pre>';
  }
  // @ignore security_dsm
  drupal_set_message($output);
}

/**
 * Display file info via ajax callback.
 */
function advagg_validator_admin_test_advagg_css_callback($form, &$form_state) {
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  if (!empty($form_state['values']['error'])) {
    return '<div id="advagg-file-info-ajax"></div>';
  }
  $info = advagg_validator_test_advagg_css();
  if (empty($info)) {
    return '<div id="advagg-file-info-ajax"></div>';
  }
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . print_r($info, TRUE) . '</pre>';
  }
  return '<div id="advagg-validator-css-validator-ajax">' . $output . '</div>';
}

/**
 * Display file info in a drupal message.
 */
function advagg_validator_admin_test_advagg_css_directory_submit($form, &$form_state) {
  // @codingStandardsIgnoreLine
  if (!empty($form_state['input']['ajax_page_state']) || empty($form_state['values']['op']) || strpos($form_state['values']['op'], t('Check this Directory:')) !== 0) {
    return;
  }
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  $dir = trim(substr($form_state['values']['op'], strpos($form_state['values']['op'], ':') + 1));
  $slash_count = substr_count('/' . $dir, '/');

  // Get list of files.
  $files = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'hidden') === FALSE || strpos($value, $dir) === FALSE || substr_count($value, '/') > $slash_count || ($dir === '.' && substr_count($value, '/') > 0)) {
      continue;
    }
    $files[] = $value;
  }

  // Check list.
  $info = advagg_validator_test_css_files($files);
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . check_plain(print_r($info, TRUE)) . '</pre>';
  }
  // @ignore security_dsm
  drupal_set_message($output);
}

/**
 * Display file info via ajax callback.
 */
function advagg_validator_admin_test_advagg_css_directory_callback($form, &$form_state) {
  if (empty($form_state['values']['op']) || strpos($form_state['values']['op'], t('Check this Directory:')) !== 0) {
    return '<div></div>';
  }
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  $dir = trim(substr($form_state['values']['op'], strpos($form_state['values']['op'], ':') + 1));
  $slash_count = substr_count('/' . $dir, '/');

  // Get list of files.
  $files = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'hidden') === FALSE || strpos($value, $dir) === FALSE || substr_count($value, '/') > $slash_count || ($dir === '.' && substr_count($value, '/') > 0)) {
      continue;
    }
    $files[] = $value;
  }

  // Check list.
  $info = advagg_validator_test_css_files($files);
  $wrapper = '';
  if (empty($info)) {
    return '<div id="' . $wrapper . '" class="results"></div>';
  }
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . print_r($info, TRUE) . '</pre>';
  }

  $form_api_dirname = str_replace(array('/', '.'), array('__', '--'), $dir);
  $wrapper = 'advagg-validator-css-validator-ajax' . $form_api_dirname;
  return '<div id="' . $wrapper . '" class="results">' . $output . '</div>';
}

/**
 * Display file info in a drupal message.
 */
function advagg_validator_admin_test_advagg_css_subdirectory_submit($form, &$form_state) {
  // @codingStandardsIgnoreLine
  if (!empty($form_state['input']['ajax_page_state']) || empty($form_state['values']['op']) || strpos($form_state['values']['op'], t('Check this Directory and all Subdirectories:')) !== 0) {
    return;
  }
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  $dir = trim(substr($form_state['values']['op'], strpos($form_state['values']['op'], ':') + 1));

  // Get list of files.
  $files = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'hidden') === FALSE || strpos($value, $dir) === FALSE || ($dir === '.' && substr_count($value, '/') > 0)) {
      continue;
    }
    $files[] = $value;
  }

  // Check list.
  $info = advagg_validator_test_css_files($files);
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . check_plain(print_r($info, TRUE)) . '</pre>';
  }
  // @ignore security_dsm
  drupal_set_message($output);
}

/**
 * Display file info via ajax callback.
 */
function advagg_validator_admin_test_advagg_css_subdirectory_callback($form, &$form_state) {
  if (empty($form_state['values']['op']) || strpos($form_state['values']['op'], t('Check this Directory and all Subdirectories:')) !== 0) {
    return '<div></div>';
  }
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  $dir = trim(substr($form_state['values']['op'], strpos($form_state['values']['op'], ':') + 1));

  // Get list of files.
  $files = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'hidden') === FALSE || strpos($value, $dir) === FALSE || ($dir === '.' && substr_count($value, '/') > 0)) {
      continue;
    }
    $files[] = $value;
  }

  // Check list.
  $info = advagg_validator_test_css_files($files);
  $wrapper = '';
  if (empty($info)) {
    return '<div id="' . $wrapper . '" class="results"></div>';
  }
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . print_r($info, TRUE) . '</pre>';
  }

  $form_api_dirname = str_replace(array('/', '.'), array('__', '--'), $dir);
  $wrapper = 'advagg-validator-css-validator-ajax' . $form_api_dirname;
  return '<div id="' . $wrapper . '" class="results">' . $output . '</div>';
}

/**
 * Display file info in a drupal message.
 */
function advagg_validator_admin_test_all_css_submit($form, &$form_state) {
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  // @codingStandardsIgnoreLine
  if (!empty($form_state['input']['ajax_page_state'])) {
    return;
  }
  $info = advagg_validator_test_all_css();
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . check_plain(print_r($info, TRUE)) . '</pre>';
  }
  // @ignore security_dsm
  drupal_set_message($output);
}

/**
 * Display file info via ajax callback.
 */
function advagg_validator_admin_test_all_css_callback($form, &$form_state) {
  module_load_include('inc', 'advagg_validator', 'advagg_validator');

  if (!empty($form_state['values']['error'])) {
    return '<div id="advagg-file-info-ajax"></div>';
  }
  $info = advagg_validator_test_all_css();
  if (empty($info)) {
    return '<div id="advagg-file-info-ajax"></div>';
  }
  $info = advagg_validator_admin_hide_good_files($info);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . print_r($info, TRUE) . '</pre>';
  }
  return '<div id="advagg-validator-css-validator-ajax">' . $output . '</div>';
}

/**
 * Do not display info on a file if it is valid.
 *
 * @param array $info
 *   Array containing info about validators and if the file is valid.
 *
 * @return array
 *   $info array minus data if that file is valid.
 */
function advagg_validator_admin_hide_good_files(array $info) {
  $output = array();
  foreach ($info as $filename => $validators) {
    foreach ($validators as $v_name => $v_data) {
      if (!empty($v_data['validity'])) {
        $output[$filename][$v_name] = 'valid';
        continue;
      }
      $output[$filename][$v_name] = $v_data;
    }
  }
  return $output;
}
