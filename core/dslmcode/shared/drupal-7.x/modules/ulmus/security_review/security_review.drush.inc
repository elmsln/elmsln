<?php

/**
 * @file
 * Drush commands for Security Review module.
 */

// Include security_review.inc file for when invoked from outside the site.
include_once dirname(__FILE__) . '/security_review.inc';

/**
 * Implementation of hook_drush_command().
 */
function security_review_drush_command() {
  $items = array();

  $items['security-review'] = array(
    'callback' => 'security_review_drush',
    'aliases' => array('secrev'),
    'description' => "Run the Security Review checklist",
    'options' => array(
      'store' => 'Write results to the database',
      'log' => 'Log results of each check to watchdog, defaults to off',
      'lastrun' => 'Do not run the checklist, just print last results',
      'check' => 'Comma-separated list of specified checks to run. See README.txt for list of options',
      'skip' => 'Invert behavior of --check. Run all checks except specified checks',
      'short' => "Short result messages instead of full description (e.g. 'Text formats').",
      'results' => 'Show the incorrect settings for failed checks.',
    ),
    'examples' => array(
      'secrev' => 'Run the checklist and output the results',
      'secrev --store' => 'Run the checklist, store, and output the results',
      'secrev --lastrun' => 'Output the stored results from the last run of the checklist'
    ),
  );
  $items['password-check-setup'] = array(
    'callback' => 'security_review_drush_hash_setup',
    'aliases' => array('passset'),
    'description' => "Create and load a rainbow table for password checking",
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function security_review_drush_help($section) {
  switch ($section) {
    case 'drush:security-review':
      return dt("Run configuration security checks on your Drupal site.");
    case 'drush:password-check-setup':
      return dt("Creates a table and fills it with dictionary words for rainbow testing.");
  }
}

/**
 * Run checklist and display results command.
 */
function security_review_drush() {
  if (!function_exists('security_review_get_checklist')) {
    return drush_set_error('REQUIREMENTS_ERROR', 'File security_review.inc is required to run the checklist.');
  }
  // Retrieve the checklist.
  $checklist = security_review_get_checklist();

  $store = drush_get_option('store');
  $log = drush_get_option('log');
  $lastrun = drush_get_option('lastrun');
  if (!function_exists('security_review_menu')) {
    // Checklist is being executed when module is disabled . Deny these
    // features.
    $store = $log = $lastrun = FALSE;
  }
  $specific_checks = drush_get_option_list('check');
  $skip = drush_get_option('skip');
  $short_titles = drush_get_option('short');
  if (!empty($short_titles)) {
    $short_titles = TRUE;
  }
  else {
    $short_titles = FALSE;
  }
  // Show failed check results only if security_review.help.inc exists.
  $show_results = drush_get_option('results');
  if ($show_results && file_exists(__DIR__ . '/security_review.help.inc')) {
    include_once __DIR__ . '/security_review.help.inc';
  }
  else {
    $show_results = FALSE;
  }

  if (!$lastrun) {
    if (!empty($specific_checks)) {
      // Get specified checks.
      $specific_checklist = array();
      foreach ($specific_checks as $check_name) {
        if (empty($check_name)) {
          continue; // Can happen if user puts space after comma.
        }
        if (strpos($check_name, ':') !== FALSE) {
          list($module, $check_name) = explode(':', $check_name);
        }
        else {
          $module = 'security_review';
        }
        if (isset($checklist[$module][$check_name])) {
          $specific_checklist[$module][$check_name] = $checklist[$module][$check_name];
        }
      }
      if ($skip) {
        // Run all checks except specified checks.
        foreach ($specific_checklist as $module => $checks) {
          foreach (array_keys($checks) as $check_name) {
            unset($checklist[$module][$check_name]);
          }
        }
      }
      else {
        // Run only specified checks.
        $checklist = $specific_checklist;
      }
    }
    else {
      // Unset file_perms of security_review because drush is running as a
      // different user.
      unset($checklist['security_review']['file_perms']);
    }
    // Remove checks that are being skipped if storing.
    if ($store) {
      $skipped = security_review_skipped_checks();
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
    }
    if (empty($checklist)) {
      return drush_set_error('EMPTY_CHECKLIST', dt("No checks to run. Run 'drush help secrev' for option use or consult the drush section of README.txt for further help."));
    }
    // Run the checklist.
    $checklist_results = security_review_run($checklist, $log ? TRUE : NULL);
    if ($store) {
      security_review_store_results($checklist_results);
    }
    // Print results.
    foreach ($checklist_results as $module => $checks) {
      foreach ($checks as $check_name => $check) {
        _security_review_drush_print_result($check, $short_titles, $show_results);
      }
    }
  }
  elseif ($lastrun) {
    // Retrieve results from last run of the checklist.
    $results = security_review_get_stored_results();
    // Print results.
    if (!empty($results)) {
      foreach ($results as $result) {
        if (isset($checklist[$result['namespace']][$result['reviewcheck']])) {
          $check = array_merge($result, $checklist[$result['namespace']][$result['reviewcheck']]);
          _security_review_drush_print_result($check, $short_titles, $show_results);
        }
      }
    }
  }
}

/**
 * Helper function to print Security Review results using drush_log().
 *
 * @param array $check
 *   Check array with keys 'title', 'success', 'failure', 'result'
 * @param boolean $short_titles
 *   Whether to use short message (check title) or full check success or failure
 *   message.
 * @param boolean $show_results
 *   Whether to print failed check results.
 * @return NULL
 */
function _security_review_drush_print_result($check, $short_titles = FALSE, $show_results = FALSE) {
  if (is_null($check['result'])) {
    // Do nothing if result is NULL.
    return;
  }
  elseif ($check['result']) {
    $element = $short_titles ? 'title' : 'success';
    $message = $check[$element];
    $status = 'success';
  }
  else {
    $element = $short_titles ? 'title' : 'failure';
    $message = $check[$element];
    if ($show_results) {
      $results = _security_review_drush_findings_output($check);
      if (!empty($results)) {
        $message .= "\n";
        foreach ($results as $item) {
          $message .= "\t" . $item . "\n";
        }
      }
    }
    $status = 'error';
  }
  drush_log($message, $status);
}

function _security_review_drush_findings_output($check) {
  $findings = array();
  if (isset($check['help'])) {
    $findings[] = $check['help'];
  }
  elseif (isset($check['callback'])) {
    if (isset($check['file'])) {
      // Handle Security Review defining checks for other modules.
      if (isset($check['module'])) {
        $module = $check['module'];
      }
      module_load_include('inc', $module, $check['file']);
    }
    $function = $check['callback'] . '_help';
    if (function_exists($function)) {
      $element = $function($check);
      if (is_array($element['findings']['items'])) {
        foreach ($element['findings']['items'] as $item) {
          if (is_array($item) && isset($item['raw'])) {
            $findings[] = $item['raw'];
          }
        }
      }

    }
  }
  return $findings;
}

function security_review_drush_hash_setup() {
  $args = func_get_args();
  if (empty($args)) {
    drush_set_error('SECURITY_REVIEW_ERROR', dt('Dictionary filename required'));
    return FALSE;
  }
  if (file_exists($args[0])) {
    $ret = array();
    // Create the rainbow table.
    if (!db_table_exists('security_review_rainbow')) {
      $schema = array(
        'fields' => array(
          'hash_id' => array(
            'type' => 'serial',
          ),
          'hash_word' => array(
            'type' => 'varchar',
            'length' => 20,
          ),
          'hash_hash' => array(
            'type' => 'varchar',
            'length' => 32,
          ),
        ),
        'primary key' => array('hash_id'),
        'indexes' => array('hash_hash' => array('hash_hash')),
      );
      db_create_table($ret, 'security_review_rainbow', $schema);
    }
    // Put an index on users.pass.
    db_drop_index($ret, 'users', 'pass'); // Drop in case this has already run.
    db_add_index($ret, 'users', 'pass', array('pass'));

    $handle = fopen($args[0], 'r');
    if ($handle) {
      $count = 0;
      while (!feof($handle)) {
        $buffer = fgets($handle, 4096);
        $word = trim($buffer);
        $hash = md5($hash);
        $sql = "INSERT INTO {security_review_rainbow} (hash_word, hash_hash) VALUES ('%s', '%s')";
        db_query($sql, $word, $hash);
        $count++;
      }
      fclose($handle);
      drush_log(dt('!count records inserted into rainbow table', array('!count' => $count)), 'success');
    }
  }
  else {
    drush_die('File not found');
  }
}
