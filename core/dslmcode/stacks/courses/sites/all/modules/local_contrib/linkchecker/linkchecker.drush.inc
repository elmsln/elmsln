<?php

/**
 * @file
 * Drush interface to linkchecker functionalities.
 */

/**
 * Implements hook_drush_command().
 */
function linkchecker_drush_command() {
  $commands = array();

  $commands['linkchecker-analyze'] = array(
    'description' => 'Reanalyzes content for links. Recommended after module has been upgraded.',
  );
  $commands['linkchecker-clear'] = array(
    'description' => 'Clears all link data and analyze content for links. WARNING: Custom link check settings are deleted.',
  );
  $commands['linkchecker-check'] = array(
    'description' => 'Check link status.',
    // 'options' => array(
    //   'links' => 'Number of links to check in one round. Default: 1000',
    // ),
  );

  return $commands;
}

/**
 * Callback for command linkchecker-analyze.
 */
function drush_linkchecker_analyze() {
  global $base_url;
  if ($base_url == 'http://default') {
    drush_die('You MUST configure the site $base_url or provide --uri parameter.');
  }

  module_load_include('admin.inc', 'linkchecker');

  // Fake $form_state to leverage _submit function.
  $form_state = array(
    'values' => array('op' => t('Analyze content for links')),
    'buttons' => array(),
  );

  $node_types = array_keys(array_filter(variable_get('linkchecker_scan_nodetypes', array())));
  if (!empty($node_types) || variable_get('linkchecker_scan_blocks', 0)) {
    linkchecker_analyze_links_submit(NULL, $form_state);
    drush_backend_batch_process();
  }
  else {
    drush_log('No content configured for link analysis.', 'status');
  }
}

/**
 * Callback for command linkchecker-analyze.
 */
function drush_linkchecker_clear() {
  global $base_url;
  if ($base_url == 'http://default') {
    drush_die('You MUST configure the site $base_url or provide --uri parameter.');
  }

  module_load_include('admin.inc', 'linkchecker');

  // Fake $form_state to leverage _submit function.
  $form_state = array(
    'values' => array('op' => t('Clear link data and analyze content for links')),
    'buttons' => array(),
  );

  $node_types = array_keys(array_filter(variable_get('linkchecker_scan_nodetypes', array())));
  if (!empty($node_types) || variable_get('linkchecker_scan_blocks', 0)) {
    linkchecker_clear_analyze_links_submit(NULL, $form_state);
    drush_backend_batch_process();
  }
  else {
    drush_log('No content configured for link analysis.', 'status');
  }
}

/**
 * Callback for command linkchecker-check.
 */
function drush_linkchecker_check() {
  drush_log('Starting link checking...', 'info');
  $run = _linkchecker_check_links();
  if (!$run) {
    drush_log('Attempted to re-run link checks while they are already running.', 'warning');
  }
  else {
    drush_log('Finished checking links.', 'completed');
  }
}
