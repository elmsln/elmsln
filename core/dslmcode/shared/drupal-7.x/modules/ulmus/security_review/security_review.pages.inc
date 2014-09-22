<?php

/**
 * @file security_review.pages.inc
 */

/**
 * Page callback for run & review.
 */
function security_review_page() {
  $checks = array();
  $output = array();
  // Retrieve the checklist.
  module_load_include('inc', 'security_review');
  $checklist = security_review_get_checklist();
  // Retrieve results from last run of the checklist.
  $checks = security_review_get_stored_results();
  // Only users with the proper permission can run the checklist.
  if (user_access('run security checks')) {
    $output += drupal_get_form('security_review_run_form', $checks);
  }

  if (!empty($checks)) {
    // We have prior results, so display them.
    $output['results'] = security_review_reviewed($checklist, $checks);
  }
  else {
    // If they haven't configured the site, prompt them to do so.
    $variable = variable_get('security_review_log', FALSE);
    if (!$variable) {
      drupal_set_message(t('It appears this is your first time using the Security Review checklist. Before running the checklist please review the settings page at !link to set which roles are untrusted.', array('!link' => l('admin/reports/security-review/settings', 'admin/reports/security-review/settings'))));
    }
  }
  return $output;
}

function security_review_reviewed($checklist, $checks, $namespace = NULL) {
  $items = array();
  $last_run = variable_get('security_review_last_run', '');
  $date = !empty($last_run) ? format_date($last_run) : '';
  $header = t('Review results from last run !date', array('!date' => $date));
  $desc = t("Here you can review the results from the last run of the checklist. Checks are not always perfectly correct in their procedure and result. You can keep a check from running by clicking the 'Skip' link beside it. You can run the checklist again by expanding the fieldset above.");
  foreach ($checks as $check) {
    // Skip this iteration if the result has no matching item in the checklist.
    if (!isset($checklist[$check['namespace']][$check['reviewcheck']])) {
      continue;
    }
    $message = $check['result'] ? $checklist[$check['namespace']][$check['reviewcheck']]['success'] : $checklist[$check['namespace']][$check['reviewcheck']]['failure'];
    $title = $check['result'] ? t('OK') : t('Error');
    $class = $check['skip'] ? 'info' : ($check['result'] ? 'ok' : 'error');
    $toggle = $check['skip'] ? t('Enable') : t('Skip');
    $token = drupal_get_token($check['reviewcheck']);
    $link_options = array(
      'query' => array('token' => $token),
      //'attributes' => array('class' => 'use-ajax'),
    );
    $items[] = array(
      'title' => $title,
      'value' => $check['result'],
      'class' => $class,
      'message' => $message,
      'help_link' => l(t('Details'), 'admin/reports/security-review/help/' . $check['namespace'] . '/' . $check['reviewcheck']),
      'toggle_link' => l($toggle, 'admin/reports/security-review/toggle/nojs/' . $check['reviewcheck'], $link_options),
    );
  }
  $output = theme('security_review_reviewed', array('items' => $items, 'header' => $header, 'description' => $desc));
  // @todo #markup?
  return array('#markup' => $output);
}

function security_review_run_form($form, &$form_state, $checks = NULL) {
  $form['run_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Run'),
    '#description' => t('Click the button below to run the security checklist and review the results.'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($checks) ? FALSE : TRUE,
  );
  $form['run_form']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Run checklist'),
  );

  return $form;
}

function security_review_run_form_submit($form, &$form_state) {
  module_load_include('inc', 'security_review');
  $checklist = security_review_get_checklist();
  $skipped = security_review_skipped_checks();
  // Remove checks that are being skipped.
  if (!empty($skipped)) {
    foreach ($skipped as $module => $checks) {
      foreach ($checks as $check_name => $check) {
        unset($checklist[$module][$check_name]);
      }
      if (empty($checklist[$module])) {
        unset($checklist[$module]);
      }
    }
  }

  // Use Batch to process the checklist.
  $batch = array('operations' => array(),
    'title' => t('Performing Security Review'),
    'progress_message' => t('Progress @current out of @total.'),
    'error_message' => t('An error occurred. Rerun the process or consult the logs.'),
    'finished' => '_security_review_batch_finished',
  );
  $log = variable_get('security_review_log', TRUE);
  foreach ($checklist as $module => $checks) {
    foreach ($checks as $check_name => $check) {
      // Each check is its own operation. There could be a case where a single
      // check needs to run itself a batch operation, perhaps @todo?
      $batch['operations'][] = array('_security_review_batch_op', array($module, $check_name, $check, $log));
    }
  }
  batch_set($batch);
  return;
}

/**
 * Module settings form.
 */
function security_review_settings() {
  module_load_include('inc', 'security_review');
  $checklist = security_review_get_checklist();
  $roles = user_roles();
  foreach ($roles as $rid => $role) {
    $options[$rid] = check_plain($role);
  }
  $message = '';
  $defaults = _security_review_default_untrusted_roles();
  if (array_key_exists(DRUPAL_AUTHENTICATED_RID, $defaults)) {
    $message = 'You have allowed anonymous users to create accounts without approval so the authenticated role defaults to untrusted.';
  }

  $form['security_review_untrusted_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Untrusted roles'),
    '#description' => t('Mark which roles are not trusted. The anonymous role defaults to untrusted. @message Read more about the idea behind trusted and untrusted roles on <a href="!url">DrupalScout.com</a>. Most Security Review checks look for resources usable by untrusted roles.', array('@message' => $message, '!url' => url('http://drupalscout.com/knowledge-base/importance-user-roles-and-permissions-site-security'))),
    '#options' => $options,
    '#default_value' => variable_get('security_review_untrusted_roles', array_keys($defaults)),
  );

  $inactive_namespaces = array();
  // Report stored checks that aren't currently active.
  $checks = security_review_get_stored_results();
  foreach ($checks as $check) {
    if (!isset($checklist[$check['namespace']][$check['reviewcheck']])) {
      $inactive_namespaces[] = $check['namespace'];
    }
  }
  if (!empty($inactive_namespaces)) {
    $inactive_checks = implode(', ', $inactive_namespaces);
    $form['inactive_checks'] = array(
      '#prefix' => '<div class="messages warning">',
      '#suffix' => '</div>',
      '#markup' => t('Inactive checks are being stored under namespaces: %modules. Enabling associated modules may allow these checks to be run again. Inactive checks must be manually removed or uninstall and reinstall Security Review to clear all stored checks.', array('%modules' => $inactive_checks))
    );
  }

  $form['security_review_adv'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['security_review_adv']['security_review_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log checklist results and skips'),
    '#description' => t('The result of each check and skip can be logged to watchdog for tracking.'),
    '#default_value' => variable_get('security_review_log', TRUE),
  );
  $options = $values = array();

  $skipped = security_review_skipped_checks();
  foreach ($checklist as $module => $checks) {
    foreach ($checks as $check_name => $check) {
      // Determine if check is being skipped.
      if (!empty($skipped) && isset($skipped[$module]) && array_key_exists($check_name, $skipped[$module])) {
        $values[] = $check_name;
        $label = t('!name <em>skipped by UID !uid on !date</em>', array('!name' => $check['title'], '!uid' => $skipped[$module][$check_name]['skipuid'], '!date' => format_date($skipped[$module][$check_name]['skiptime'])));
      }
      else {
        $label = $check['title'];
      }
      $options[$check_name] = $label;
    }
  }
  $form['security_review_adv']['security_review_skip'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Checks to skip'),
    '#description' => t('Skip running certain checks. This can also be set on the <em>Run & review</em> page. It is recommended that you do not skip any checks unless you know the result is wrong or the process times out while running.'),
    '#options' => $options,
    '#default_value' => $values,
  );

  $form['security_review_adv']['check_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check-specific settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );

  $form['security_review_adv']['check_settings']['security_review_base_url_method'] = array(
    '#type' => 'radios',
    '#title' => t('Base URL check method'),
    '#description' => t('Detecting the $base_url in settings.php can be done via PHP tokenization (recommend) or including the file. Note that if you have custom functionality in your settings.php it will be executed if the file is included. Including the file can result in a more accurate $base_url check if you wrap the setting in conditional statements.'),
    '#options' => array(
      'token' => t('Tokenize settings.php (recommended)'),
      'include' => t('Include settings.php'),
    ),
    '#default_value' => variable_get('security_review_base_url_method', 'token'),
  );
  // Add a submit handler to set the skipped checks.
  $form['#submit'][] = '_security_review_settings_submit';

  return system_settings_form($form);
}

function _security_review_settings_submit($form, &$form_state) {
  global $user;
  $log = $form_state['values']['security_review_log'];
  // Set checked.
  module_load_include('inc', 'security_review');
  $checklist = security_review_get_checklist();

  $stored = array();
  $results = db_query("SELECT namespace, reviewcheck, result, lastrun, skip, skiptime, skipuid FROM {security_review}");
  while($record = $results->fetchAssoc()) {
    $stored[$record['namespace']][$record['reviewcheck']] = $record;
  }

  foreach ($checklist as $module => $checks) {
    foreach ($checks as $check_name => $check) {
      $record = new stdClass();
      $update = array();
      // Toggle the skip.
      if (isset($stored[$module][$check_name]) && $stored[$module][$check_name]['skip'] == 1 && $form_state['values']['security_review_skip'][$check_name] === 0) {
        // We were skipping, so stop skipping and clear skip identifiers.
        $record->namespace = $module;
        $record->reviewcheck = $check_name;
        $record->skip = FALSE;
        $record->skiptime = 0;
        $record->skipuid = NULL;
        $result = drupal_write_record('security_review', $record, array('namespace', 'reviewcheck'));
        if ($log) {
          $variables = array('!name' => $check['title']);
          _security_review_log($module, $check_name, '!name check no longer skipped', $variables, WATCHDOG_INFO);
        }
      }
      elseif ($form_state['values']['security_review_skip'][$check_name] !== 0) {
        // Start skipping and record who made the decision and when.
        if (isset($stored[$module][$check_name])) {
          $update = array('namespace', 'reviewcheck');
        }
        $record->namespace = $module;
        $record->reviewcheck = $check_name;
        $record->skip = TRUE;
        $record->skiptime = REQUEST_TIME;
        $record->skipuid = $user->uid;
        $result = drupal_write_record('security_review', $record, $update);
        if ($log) {
          $variables = array('!name' => $check['title']);
          _security_review_log($module, $check_name, '!name check skipped', $variables, WATCHDOG_INFO);
        }
      }
    }
  }
  // Unset security_review_skip to keep it from being written to a variable.
  unset($form_state['values']['security_review_skip']);

  // Set check-specific settings.
  foreach ($form_state['values']['check_settings'] as $variable_name => $value) {
    variable_set($variable_name, $value);
  }
}

/**
 * Menu callback and Javascript callback for check skip toggling.
 */
function security_review_toggle_check($type = 'ajax', $check_name) {
  global $user;
  if (!isset($_GET['token']) || !drupal_valid_token($_GET['token'], $check_name)) {
    return drupal_access_denied();
  }
  $result = FALSE;
  // To be sure, compare the user-provided check with available checks.
  module_load_include('inc', 'security_review');
  $checklist = security_review_get_checklist();
  foreach ($checklist as $module => $checks) {
    if (in_array($check_name, array_keys($checks))) {
      $query = db_select('security_review', 'sr')
        ->fields('sr', array('namespace', 'reviewcheck', 'result', 'lastrun', 'skip', 'skiptime', 'skipuid'))
        ->condition('namespace', $module, '=')
        ->condition('reviewcheck', $check_name, '=');
      $record = $query->execute()->fetchObject();
      // Toggle the skip.
      if ($record->skip) {
        // We were skipping, so stop skipping and clear skip identifiers.
        $record->skip = FALSE;
        $record->skiptime = 0;
        $record->skipuid = NULL;
        $message = '!name check no longer skipped';
      }
      else {
        // Start skipping and record who made the decision and when.
        $record->skip = TRUE;
        $record->skiptime = REQUEST_TIME;
        $record->skipuid = $user->uid;
        $message = '!name check skipped';
      }
      $result = drupal_write_record('security_review', $record, array('namespace', 'reviewcheck'));
      // To log, or not to log?
      $log = variable_get('security_review_log', TRUE);
      if ($log) {
        $variables = array('!name' => $checks[$check_name]['title']);
        _security_review_log($module, $check_name, $message, $variables, WATCHDOG_INFO);
      }
      break;
    }
  }
  if ($type == 'ajax') {
    drupal_json_output($record);
    return;
  }
  else {
    // We weren't invoked via JS so set a message and return to the review page.
    drupal_set_message(t($message, array('!name' => $checks[$check_name]['title'])));
    drupal_goto('admin/reports/security-review');
  }
}

/**
 * Helper function creates message for reporting check skip information.
 */
function _security_review_check_skipped($last_check) {
  $account = array_pop(user_load_multiple(array($last_check['skipuid'])));
  $time = format_date($last_check['skiptime'], 'medium');
  $message = t('Check marked for skipping on !time by !user', array('!time' => $time, '!user' => theme('username', array('account' => $account))));
  return $message;
}

/**
 * Page callback provides general help and check specific help documentation.
 */
function security_review_check_help($module = NULL, $check_name = NULL) {
  // Include checks and help files.
  module_load_include('inc', 'security_review');
  $checklist = security_review_get_checklist();
  module_load_include('inc', 'security_review', 'security_review.help');
  $output = '';
  $skipped_message = NULL;
  if (!is_null($module) && !is_null($check_name)) {
    $check = $checklist[$module][$check_name];
    if (isset($check['help'])) {
      $output = $check['help'];
    }
    elseif (isset($check['callback'])) {
      if (isset($check['file'])) {
        $check_module = $module;
        // Handle Security Review defining checks for other modules.
        if (isset($check['module'])) {
          $check_module = $check['module'];
        }
        module_load_include('inc', $check_module, $check['file']);
      }
      $function = $check['callback'] . '_help';
      if (function_exists($function)) {
        $last_check = security_review_get_last_check($module, $check_name);
        // Set skipped timestamp and user message.
        if ($last_check['skip'] == '1') {
          $skipped_message = _security_review_check_skipped($last_check);
        }
        // Add findings to check if it's failed.
        elseif ($last_check['result'] == '0') {
          $callback = $check['callback'];
          $check_return = $callback();
          $last_check = array_merge($last_check, $check_return);
        }
        $element = $function($last_check, $skipped_message);
        $output = theme('security_review_check_help', array('element' => $element));
      }
    }
  }
  else {
    $output = _security_review_help();
    // List all checks as links to specific help.
    $output .= '<h3>' . t('Check-specfic help') . '</h3>';
    $output .= '<p>' . t("Details and help on the security review checks. Checks are not always perfectly correct in their procedure and result. Refer to drupal.org handbook documentation if you are unsure how to make the recommended alterations to your configuration or consult the module's README.txt for support.") . '</p>';
    foreach ($checklist as $module => $checks) {
      foreach ($checks as $reviewcheck => $check) {
        $items[] = l($check['title'], 'admin/reports/security-review/help/' . $module . '/' . $reviewcheck);
      }
    }
    if ($items) {
      $output .= theme('item_list', array('items' => $items));
    }
  }
  if (empty($output)) {
    return drupal_not_found();
  }
  return array('#markup' => $output);
}

function theme_security_review_reviewed($variables) {
  // @todo
  //drupal_add_js(drupal_get_path('module', 'security_review') . '/security_review.js', array('scope' => 'footer'));
  $output = '<h3>' . $variables['header'] . '</h3>';
  $output .= '<p>' . $variables['description'] . '</p>';
  $output .= '<table class="system-status-report">';
  if (!empty($variables['items'])) {
    foreach ($variables['items'] as $item) {
      $output .= '<tr class="' . $item['class'] . '">';
      $output .= '<td class="status-icon"><div title="' . $item['title'] . '"><span class="element-invisible">' . $item['title'] . '</span></div></td>';
      $output .= '<td>' . $item['message'] . '</td>';
      $output .= '<td>' . $item['help_link'] . '</td>';
      $output .= '<td>' . $item['toggle_link'] . '</td>';
      $output .= '</tr>';
    }
  }
  $output .= '</table>';
  return $output;
}

/**
 * Theme function for help on a security check.
 *
 * Calling function should filter and sanitize.
 */
function theme_security_review_check_help($variables) {
  $element = $variables['element'];
  $output = '<h3>' . $element['title'] . '</h3>';
  foreach ($element['descriptions'] as $description) {
    $output .= '<p>' . $description . '</p>';
  }
  if (!empty($element['findings'])) {
    foreach ($element['findings']['descriptions'] as $description) {
      $output .= '<p>' . $description . '</p>';
    }
    if (!empty($element['findings']['items'])) {
      $items = $element['findings']['items'];
      $output .= "<ul>\n";
      // Loop through items outputting the best value HTML, safe, or raw if thats all there is.
      foreach ($items as $item) {
        if (is_array($item)) {
          if (isset($item['html'])) {
            $data = $item['html'];
          }
          elseif (isset($item['safe'])) {
            $data = $item['safe'];
          }
          else {
            $data = $item['raw'];
          }
        }
        else {
          $data = $item;
        }
        $output .= "<li>" . $data . "</li>\n";
      }
      $output .= "</ul>\n";
    }
    if (!empty($element['findings']['pager'])) {
      $output .= $element['findings']['pager'];
    }
  }
  return $output;
}
