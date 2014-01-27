<?php

/**
 * @file
 * Command line utility support for Coder_sniffer module.
 */

/**
 * Implements hook_drush_command().
 */
function drupalcs_drush_command() {
  $items = array();

  $items['drupalcs'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'description' => dt('Executes PHP_CodeSniffer with Drupal Coding Standards on a particular directory.'),
    'arguments' => array(
      'path' => dt('The path that you wish to scan.'),
    ),
    'aliases' => array('dcs'),
    'options' => array(
      'extensions' => array(
        'description' => dt('Comma delimited list of file extensions to scan. The default is @default', array(
          '@default' => implode(',', _drupalcs_extensions()),
        )),
        'example-value' => dt('php,module'),
      ),
      'mode' => array(
        'description' => dt('Specify the name of the set of file extensions to scan if no extensions are specified. Options are: default, extended.'),
        'example-value' => dt('extended'),
      ),
      'report' => array(
        'description' => dt('Specify the report format. Options are: full, xml, checkstyle, csv, emacs, source, summary, svnblame, gitblame or hgblame.'),
        'example-value' => dt('xml'),
      ),
      'report-file' => array(
        'description' => dt('Write the report to the specified file path.'),
        'example-value' => dt('/var/log/snifflog.xml'),
      ),
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * @param string $section
 *   The help section.
 *
 * @return string
 *   The help text for the command.
 */
function drushrc_drush_help($section) {
  switch ($section) {
    case 'drush:drupalcs':{
      return dt('This command will execute PHP_CodeSniffer on a given path, using Drupal Coding Standard definitions.');
    }
  }
}

/**
 * Implements drush_hook_COMMAND_validate().
 */
function drush_drupalcs_validate($path = '') {
  if (!_drupalcs_is_compatible_phpcs_installed()) {
    $path_to_phpcs = _drupalcs_get_path();
    if ($path_to_phpcs) {
      return drush_set_error('NOT_INSTALLED', dt('PHP_CodeSniffer is not installed.'));
    }
    else {
      return drush_set_error('INCOMPATIBLE', dt('No compatible version of PHP_CodeSniffer was found; you must have 1.3.4 or higher.  Alternatively, you can symbolically link with the following command: sudo ln -sv @path $(pear config-get php_dir)/PHP/CodeSniffer/Standards/Drupal', array(
        '@path' => _drupalcs_get_standard($path_to_phpcs),
      )));
    }
  }
  if (!file_exists(drush_get_context('DRUSH_OLDCWD') . '/' . $path)) {
    return drush_set_error('NO_PATH', dt('Path not found; cannot scan.'));
  }
}

/**
 * Drush command callback; executes PHP_CodeSniffer with Drupal standards.
 */
function drush_drupalcs($path = '') {
  $phpcs_path = _drupalcs_get_path();

  // Start building the command; begin with the executable.
  $command = $phpcs_path;

  // Add the standard.
  $command .= ' --standard=' . _drupalcs_get_standard($phpcs_path);

  // Define the extensions; allow overriding.
  $extensions = drush_get_option('extensions');
  if (!$extensions) {
    $extensions = implode(',', _drupalcs_extensions(drush_get_option('mode')));
  }
  $command .= ' --extensions=' . $extensions;

  // Optionally define the report format.
  $report = drush_get_option('report');
  if ($report) {
    $command .= ' --report=' . $report;
  }

  // Optionally define the report file.
  $reportfile = drush_get_option('report-file');
  if ($reportfile) {
    $command .= ' --report-file=' . $reportfile;
  }

  // Path that you wish to scan.
  $command .= ' ' . drush_get_context('DRUSH_OLDCWD') . '/' . $path;

  // Execute the command.
  $result = drush_shell_exec($command);
  drush_print(implode("\n", drush_shell_exec_output()));

  // Report failure.
  if (!$result) {
    drush_set_error('PHPCS_FAIL', dt('PHP_CodeSniffer found at least one issue.'));
  }
  // There is a report file; no idea how many errors/warnings there were.
  elseif ($reportfile) {
    drush_log(dt('PHP_CodeSniffer executed.'), 'success');
  }
  // No problems found.
  else {
    drush_log(dt('PHP_CodeSniffer did not find any problems.'), 'success');
  }
}

/**
 * Defines the default file extensions scanned by PHP_CodeSniffer.
 *
 * @param string $mode
 *   (optional) A mode that can be set to 'extended'. Defaults to an empty
 *   string.
 *
 * @return array
 *   An array of file extensions that cover standard Drupal projects.
 */
function _drupalcs_extensions($mode = '') {
  $extensions = array(
    'php',
    'module',
    'inc',
    'install',
    'test',
    'profile',
    'theme',
  );
  if ('extended' == $mode) {
    $extensions[] = 'css';
    $extensions[] = 'js';
    $extensions[] = 'txt';
    $extensions[] = 'info';
  }
  return $extensions;
}

/**
 * Checks to see if a compatible version of PHP_CodeSniffer is installed.
 *
 * @return bool
 *   A Boolean indicating whether or not a compatible version of
 *   PHP_CodeSniffer is installed.
 */
function _drupalcs_is_compatible_phpcs_installed() {
  // Check to see if phpcs is installed.
  $version = _drupalcs_get_phpcs_version('phpcs');

  if ($version) {
    // Check if Drupal standard is installed.
    if (_drupalcs_is_drupal_standard_installed('phpcs')) {
      return TRUE;
    }
    // A fix was applied after version 1.3.3 that allowed external Sniff paths.
    // Version from git? Good luck.
    if ('@package_version@' == $version) {
      return TRUE;
    }
    // Version number comparison.
    if (version_compare($version, '1.3.4', '>')) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Gets the version of PHP_CodeSniffer.
 *
 * @param string $path_to_phpcs
 *   The path to PHP_CodeSniffer.
 *
 * @return string
 *   The version of PHP_CodeSniffer, or FALSE if it cannot be determined.
 */
function _drupalcs_get_phpcs_version($path_to_phpcs) {
  static $phpcs_version = NULL;

  if (is_null($phpcs_version)) {
    $result = drush_shell_exec($path_to_phpcs . ' --version');

    if ($result) {
      $phpcs_version_array = explode(' ', array_pop(drush_shell_exec_output()));
      $phpcs_version = $phpcs_version_array[2];
    }
    else {
      $phpcs_version = FALSE;
    }
  }

  return $phpcs_version;
}

/**
 * Checks to see if the Drupal standard profile has been installed.
 *
 * @param string $path_to_phpcs
 *   The path to PHP_CodeSniffer.
 *
 * @return bool
 *   TRUE if Drupal standard profile has been installed; otherwsie, FALSE.
 */
function _drupalcs_is_drupal_standard_installed($path_to_phpcs) {
  static $standard_installed = NULL;

  if (is_null($standard_installed)) {
    $standard_installed = FALSE;
    $result = drush_shell_exec($path_to_phpcs . ' -i');
    if ($result) {
      $phpcs_installed = array_pop(drush_shell_exec_output());
      if (strpos($phpcs_installed, 'Drupal')) {
        $standard_installed = TRUE;
      }
    }
  }

  return $standard_installed;
}

/**
 * Gets the path to PHP_CodeSniffer.
 *
 * @return string
 *   The path to PHP_CodeSniffer.
 */
function _drupalcs_get_path() {
  if (_drupalcs_is_compatible_phpcs_installed()) {
    return 'phpcs';
  }
  // This is a potential place to check for libraries.
  return '';
}

/**
 * Gets the full coding standard for PHP_CodeSniffer.
 *
 * @param string $path_to_phpcs
 *   The path to PHP_CodeSniffer.
 *
 * @return string
 *   The proper phpcs standard definition, full path or just the name.
 */
function _drupalcs_get_standard($path_to_phpcs) {
  $standard_name = 'Drupal';
  if (_drupalcs_is_drupal_standard_installed($path_to_phpcs)) {
    return $standard_name;
  }
  return dirname(__FILE__) . '/' . $standard_name;
}
