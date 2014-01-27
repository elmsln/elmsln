<?php

/**
 * @file
 * Command line utility support for Coder_review module.
 */

/**
 * Implements hook_drush_command().
 */
function coder_review_drush_command() {
  $items['coder-review'] = array(
    'description' => dt('Run code reviews'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'aliases' => array('coder', 'sniffer'),
    'options' => array(
      'severity' => 'Show warnings at the specified level, one of major, minor, or critical.',
      'major' => 'Show major and critical warnings.',
      'minor' => 'Show all warnings.',
      'critical' => 'Show only critical warnings.',
      'reviews' => 'Run the specified review(s), "all" runs all reviews, also accepts a comma separated list (no spaces).',
      'comment' => 'Run the comment review.',
      'style' => 'Run the style review (default).',
      'sniffer' => 'Run the CodeSniffer review.',
      'i18n' => 'Run the i18n review.',
      'security' => 'Run the security review.',
      'sql' => 'Run the SQL review.',
      'upgrade7x' => 'Run the 6.x -> 7.x upgrade review.',
      'upgrade8x' => 'Run the 7.x -> 8.x upgrade review.',
      'druplart' => 'Run the druplart review.',
      'release' => 'Run the production-ready review.',
      'sniffer' => 'Run the PHP CodeSniffer review.',
      'core' => 'Review all of core.',
      'contrib' => 'Review all of contrib.',
      'active' => 'Review all active modules and themes.',
      'all' => 'Review all modules and themes (default).',
      'default' => 'Review "default" modules and themes (as defined in coder settings).',
      'summary' => 'Display summary information only, no warning output.',
      'no-empty' => 'Hide results that are empty, opposite of --empty.',
      'empty' => 'Show or hide results that are empty, valid options are 0|no|off, on by default.',
      'ignore' => 'Enable or disable Ignore handling, valid options are 0|no|off, on by default.',
      'ignorename' => 'Enable display of ignore "rule names", helpful when adding ignores.',
      'xml' => 'Output results as xml.',
      'checkstyle' => 'Output results in Checkstyle xml format.',
      'git' => 'Install this coder command as a .git pre-commit hook',
    ),
    'arguments' => array(
      'name' => 'Review specified module or theme name, i.e. taxonomy.',
      'patch-url' => 'URL to patch file.',
      'file-path' => 'Path to file or multiple files, relative to Drupal installation.',
    ),
  );
  $items['install-php-code-sniffer'] = array(
    'description' => dt('Install PHP Code_Sniffer'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function coder_review_drush_help($section) {
  switch ($section) {
    case 'drush:coder-review':
      $help = dt('This comand will execute Coder reviews on a given path, using Drupal Coding Standard definitions.');
      // @todo What else should be added to the help message?  Popular options?
      return $help;
  }
}

/**
 * Determines which Coder modules are active for this run.
 *
 * @param array $settings
 *   An associative array of Coder modules, passed by reference.
 *
 * @todo Add function header comment. Still needed?
 */
function _coder_review_set_form_modules(array &$settings) {
  if (isset($settings['coder_modules'])) {
    foreach ($settings['coder_modules'] as $key => $value) {
      if ($value == 1) {
        $settings['coder_modules-' . $key] = 1;
      }
    }
    unset($settings['coder_modules']);
  }
}

/**
 * Install coder as a git pre-commit hook.
 */
function _drush_coder_review_git($uninstall = FALSE) {
  $gitpath = _drush_coder_git_path();

  $realroot = realpath(DRUPAL_ROOT) . '/';
  $realgit = realpath($gitpath . '/../');
  $gitrelative = substr($realgit, strlen($realroot));
  // @ignore sniffer_strings_unnecessarystringconcat_found
  $doxygen_file = '@' . 'file';

  // @ignore sniffer_squiz_whitespace_operatorspacing_nospaceafter
  $pre_commit_code =<<< __PRE_COMMIT__
#!/usr/bin/php
<?php
/**
 * $doxygen_file
 * Generic .git pre-commit hook runs all pre-commit hooks
 * following the naming convention of pre-commit_example.
 *
 * This script was created by drush coder-review --git.
 * Do not modify.
 */
\$GITPATH = "$gitpath";

/**
 * Return array of pre-commit_ files with their full relative paths.
 */
function find_pre_commit(\$dir = '.') {
  \$files = array();
  foreach (scandir(\$dir) as \$file) {
    if (substr(\$file, 0, 11) == 'pre-commit_' && is_executable("\$dir/\$file")) {
      \$files[] = "\$dir/\$file";
    }
    elseif (\$file != '.' && \$file != '..' && is_dir("\$dir/\$file")) {
      \$files = array_merge(\$files, find_pre_commit("\$dir/\$file"));
    }
  }
  return \$files;
}

// Run each pre-commit script.
foreach (find_pre_commit(\$GITPATH) as \$pre_commit) {
  system(\$pre_commit, \$ret);
  if (\$ret != 0) {
    // Exit as soon as one of the scripts returns an error.
    exit(\$ret);
  }
}
__PRE_COMMIT__;

  _drush_coder_write_file("$gitpath/hooks/pre-commit", $pre_commit_code, 0755, $uninstall);

  $args = $_SERVER['argv'];
  foreach ($args as $delta => $arg) {
    if ($delta == 0 || $delta == 1 || $arg == '--y' || $arg == '--git' || $arg == '-y') {
      unset($args[$delta]);
    }
  }
  $coder_args = implode(' ', $args);

  // @ignore sniffer_squiz_whitespace_operatorspacing_nospaceafter
  $coder_commit_code =<<< __CODER_COMMIT__
#!/usr/bin/php
<?php
/**
 * $doxygen_file
 * Coder pre-commit hook.
 *
 * This script was created by drush coder-review --git.
 * Do not modify.
 */
\$GITPATH = '$gitpath';
\$GITRELATIVE = '$gitrelative';
\$CODER_ARGS = '--empty=no $coder_args';

// Find the files that are ready to checkin.
// The magic revision is for an initial commit: diff against an empty tree object.
// See .git/pre-commit.sample.
exec('git rev-parse --verify HEAD 2> /dev/null 2>&1', \$dummy, \$ret);
\$against = (\$ret == 0) ? 'HEAD' : '4b825dc642cb6eb9a060e54bf8d69288fbee4904';
exec("git diff --cached --name-only \$against", \$files);

// Convert .git relative path to DRUPAL_ROOT relative.
foreach (\$files as &\$file) {
  \$file = "\$GITRELATIVE/\$file";
}

// Run coder against the .git files.
\$cmd = "drush \$CODER_ARGS";
print "Coder pre-commit: \$cmd\\n - " . implode("\\n - ", \$files) ."\\n\\n";
system(\$cmd . ' ' . implode(' ', \$files), \$ret);
if (\$ret) {
  exit(\$ret);
}
__CODER_COMMIT__;
  _drush_coder_write_file("$gitpath/hooks/pre-commit_coder", $coder_commit_code, 0755, $uninstall);
}

/**
 * Helper function to write a file with error checking.
 */
function _drush_coder_write_file($file, $contents, $perms = 0644, $uninstall = FALSE) {
  $contents .= "\n";
  $args = array('@file' => $file);
  if (file_exists($file)) {
    $existing = file_get_contents($file);
    if ($existing == $contents) {
      if ($uninstall) {
        drush_print(dt('removing @file', $args));
        return unlink($file);
      }
      if ($perms && (fileperms($file) & 0777) != $perms) {
        drush_print(dt('correcting permissions @file', $args));
        chmod($file, $perms);
      }
      else {
        drush_print(dt('ignore @file, already up to date.', $args));
      }
      return 1;
    }
    // Only print the question when not using --yes.
    if (!drush_get_context('DRUSH_AFFIRMATIVE')) {
      if (!drush_confirm(dt($uninstall ? 'remove @file possibly from another source' : 'overwrite @file with new contents', $args))) {
        return drush_error(dt('user aborted'));
      }
    }
    // Remove existing files.
    if ($uninstall) {
      drush_print(dt('removing @file', $args));
      return unlink($file);
    }
  }
  elseif ($uninstall) {
    return 1;
  }
  if (file_put_contents($file, $contents)) {
    if ($perms) {
      chmod($file, $perms);
    }
    drush_print(dt('writing @file', $args));
    return 1;
  }
  return drush_error(dt('error writing @file', $args));
}

/**
 * Get the git path.
 */
function _drush_coder_git_path() {
  static $gitpath;
  if (empty($gitpath)) {
    $path = drush_cwd();
    while (TRUE) {
      if (is_dir("$path/.git")) {
        $gitpath = "$path/.git";
        break;
      }
      if ($path == DRUPAL_ROOT) {
        break;
      }
      $path = realpath("$path/..");
    }
  }
  return $gitpath;
}

/**
 * Performs the actual review for drush.
 */
function drush_coder_review() {
  // Bootstrap Drupal if it is available.
  if (drush_conf_path(_drush_bootstrap_selected_uri()) && !function_exists('drupal_goto')) {
    drush_bootstrap_to_phase(DRUSH_BOOTSTRAP_DRUPAL_LOGIN);
  }

  // Bootstrap enough of coder review to run.
  require_once realpath(__DIR__) . '/coder_review.common.inc';

  // Check for the 'git' option.
  $git = drush_get_option('git');
  if (!empty($git)) {
    $uninstall = $git === 'no' || $git === 'off' || $git === 'remove' || $git === 'uninstall';
    return _drush_coder_review_git($uninstall);
  }

  // Get the command line options severity options.
  $severity = drush_get_option('severity');
  foreach (array('major', 'minor', 'critical') as $option) {
    if ($severity == $option || drush_get_option($option)) {
      $severity_name = $option;
    }
  }

  // Get the command line options module grouping options.
  foreach (array('active', 'core', 'contrib', 'all', 'default') as $option) {
    if (drush_get_option($option)) {
      $settings = _coder_review_get_default_settings($option);
      $settings['coder_includes'] = 1;
      break;
    }
  }
  if (!isset($settings)) {
    $settings = _coder_review_get_default_settings();
  }

  // Get the command line review options.
  $avail_reviews = _coder_review_reviews();
  $reviews = array();
  $reviews_option = drush_get_option('reviews');
  if ($reviews_option) {
    if ($reviews_option == 'all') {
      // @note: Don't use drupal_map_assoc because of bootstrap level.
      $avail_review_keys = array_keys($avail_reviews);
      $reviews += array_combine($avail_review_keys, $avail_review_keys);
    }
    else {
      foreach (explode(',', $reviews_option) as $option) {
        if (isset($avail_reviews[$option])) {
          $reviews[$option] = $option;
        }
      }
    }
  }
  foreach (array_keys($avail_reviews) as $option) {
    if (_coder_review_drush_get_option_no($option)) {
      unset($reviews[$option]);
    }
    elseif (drush_get_option($option)) {
      $reviews[$option] = $option;
    }
  }
  if (!$reviews) {
    $args = drush_parse_args();
    $review = $args[0] == 'sniffer' ? 'sniffer' : 'style';
    $reviews[$review] = $review;
  }

  // Process command line arguments.
  $args = func_get_args();
  $modules = array();
  $output = array();
  if (!empty($args)) {
    foreach ($args as $arg) {
      switch ($arg) {
        case 'summary':
        case 'no-empty':
        case 'xml':
        case 'checkstyle':
        case 'active':
        case 'core':
        case 'contrib':
        case 'all':
        case 'default':
          return drush_set_error(dt('use --@option.', array('@option' => $arg)));

        case 'major':
        case 'minor':
        case 'critical':
          return drush_set_error(dt('use --severity or --@option.', array('@option' => $arg)));

        default:
          if (isset($avail_reviews[$arg])) {
            return drush_set_error(dt('use --reviews or --@option.', array('@option' => $arg)));
          }
          elseif (function_exists('db_query') && (strpos($arg, '*') !== FALSE || strpos($arg, '%') !== FALSE)) {
            $result = db_query('SELECT name FROM {system} WHERE name LIKE :name', array(':name' => str_replace('*', '%', $arg)));
            foreach ($result as $system) {
              $settings['coder_modules-' . $system->name] = 1;
              $match = TRUE;
            }
            if (!isset($match)) {
              _coder_review_drush_print(dt('no matches found for @name', array('@name' => $arg)));
              return;
            }
            unset($settings['coder_active_modules']);
            unset($settings['coder_core']);
            unset($settings['coder_all']);
            unset($settings['coder_modules']);
            $settings['coder_includes'] = 1;
          }
          else {
            $root = dirname(__FILE__);
            if (_coder_review_drush_is_patch_arg($arg, $root)) {
              $settings['coder_patches'] = 1;
              $settings['coder_patch_link'] = $arg;
            }
            else {
              $path = realpath($arg);
              if (!file_exists($path)) {
                $path = preg_replace(",^$root/,", '', (function_exists('drush_getcwd') ? drush_getcwd() : getcwd()) . '/' . $arg);
                if (!file_exists($path)) {
                  $path = $root . '/' . $arg;
                  if (!file_exists($path)) {
                    $path = '';
                  }
                }
              }
              if ($path) {
                $settings['coder_files'] = 1;
                if (empty($settings['coder_file_list'])) {
                  $settings['coder_file_list'] = '';
                }
                if (is_dir($path)) {
                  $regex = '/\.(' . implode('|', _coder_review_php_ext()) . '$)/';
                  $settings['coder_file_list'] .= implode("\n", _file_list($path, $regex));
                  $settings['coder_includes'] = 1;
                }
                else {
                  if (empty($settings['coder_file_lsit'])) {
                    $settings['coder_includes'] = 0;
                  }
                  $settings['coder_file_list'] .= $path . "\n";
                }
              }
              else {
                $settings['coder_modules-' . $arg] = 1;
                $settings['coder_includes'] = 1;
              }
            }
            unset($settings['coder_active_modules']);
            unset($settings['coder_core']);
            unset($settings['coder_all']);
            unset($settings['coder_modules']);
          }
          break;
      }
    }
  }
  if (drush_get_option('checkstyle')) {
    _coder_review_drush_xml_output_header('checkstyle');
  }
  elseif (drush_get_option('xml')) {
    _coder_review_drush_xml_output_header('xml');
  }
  if (!empty($severity_name)) {
    if (drush_get_option('xml')) {
      _coder_review_drush_xml_output_severity($severity_name);
    }
    $output[] = dt('Severity @severity_name', array('@severity_name' => $severity_name));
    $settings['coder_severity'] = _coder_review_severity($severity_name);
  }
  if ($reviews) {
    if (drush_get_option('xml') && !drush_get_option('checkstyle')) {
      _coder_review_drush_xml_output_reviews($reviews, $avail_reviews);
    }
    else {
      foreach ($reviews as $review) {
        $output[] = $avail_reviews[$review]['#title'];
      }
    }
    $settings['coder_reviews'] = $reviews;
  }
  if (!empty($output) && !drush_get_option('summary') && !drush_get_option('xml') && !drush_get_option('checkstyle')) {
    _coder_review_drush_print(implode(', ', $output) . "\n");
  }
  if (_coder_review_drush_get_option_no('ignore')) {
    $settings['coder_ignore'] = 0;
  }
  _coder_review_set_form_modules($settings);
  $settings['op'] = 'drush';

  // Bootstrap the module.
  // @todo: separate this out better into an API, so we don't need the module.
  if (!function_exists('coder_review_page_form')) {
    require_once realpath(__DIR__) . '/coder_review.module';
  }

  $form_state['storage'] = $settings;
  coder_review_page_form(array(), $form_state);

  if (drush_get_option('checkstyle')) {
    _coder_review_drush_xml_output_footer('checkstyle');
  }
  elseif (drush_get_option('xml')) {
    _coder_review_drush_xml_output_footer('xml');
  }
}

/**
 * Drush command installs PHP Code_Sniffer.
 *
 * @todo: support Windows?
 */
function drush_coder_review_install_php_code_sniffer() {
  // Try loading CodeSniffer first, and if it already exists, exit.
  if (!@include_once 'PHP/CodeSniffer.php') {
    $missing = TRUE;
  }
  else {
    drush_print(dt('PHP_CodeSniffer already installed.'));
  }

  // Install PHP_CodeSniffer using pear.
  if (!empty($missing)) {
    if (!drush_shell_exec('pear update-channels') || !drush_shell_exec('pear install PHP_CodeSniffer')) {
      return drush_set_error('PHP_CODESNIFFER', dt('pear install failed: @output.', array('@output' => implode("; ", drush_shell_exec_output()))));
    }
  }

  // Get the pear install directory.
  if (drush_shell_exec('pear config-get php_dir')) {
    $output = drush_shell_exec_output();
    $php_dir = $output[0];

    // Check that the pear include path is include in the PHP path.
    if (strpos(ini_get('include_path'), $php_dir) === FALSE) {
      // @todo: Add the include path to php.ini.
      drush_print(dt('Please add @dir to include_path in php.ini', array('@dir' => $php_dir)));
    }

    // Symlink the Drupal Coder sniffs.
    $link = "$php_dir/PHP/CodeSniffer/Standards";
    $target = __DIR__ . "/../coder_sniffer/Drupal";
    if (!is_link($link) || readlink($link) != $target) {
      drush_shell_exec("ln -s $target $link");
    }
  }
}

/**
 * Determines if a specific option is explicitly disabled.
 *
 * Options can be disabled several ways in drush:
 *   --no-option
 *   --option=0
 *   --option=no
 *   --option=off
 *
 * @param string $option
 *   A drush command option as a string.
 *
 * @return bool
 *   TRUE if the specific option is disabled; otherwise, FALSE.
 */
function _coder_review_drush_get_option_no($option) {
  if (drush_get_option("no-$option")) {
    return TRUE;
  }
  $enabled = drush_get_option($option);
  return $enabled === '0' || $enabled === 'no' || $enabled === 'off';
}

/**
 * Handle patch reviews.
 *
 * @param ??? $arg
 *   ???, passed by reference.
 * @param ??? $root
 *   ???
 *
 * @return ???
 *   ???
 */
function _coder_review_drush_is_patch_arg(&$arg, $root) {
  if (_substr($arg, 0, 7) == 'http://') {
    return TRUE;
  }
  if (_drush() && preg_match('/\.(patch|diff|tmp)$/', $arg)) {
    $path = preg_replace(",^$root/,", '', drush_cwd() . '/' . $arg);
    if (is_file($path)) {
      $arg = $path;
      return TRUE;
    }
  }
}

/**
 * Save and return the exit error code.
 */
function _coder_review_exit($exitcode = -1) {
  static $ret = 1;
  if ($exitcode >= 0) {
    $ret = $exitcode;
  }
  return $ret;
}

/**
 * Implements hook_drush_exit().
 *
 * Force coder to exit with a shell exit code.
 * Drush does not support this natively.
 */
function coder_review_drush_exit() {
  $exitcode = _coder_review_exit();
  if ($exitcode != 1) {
    exit($exitcode);
  }
}

/**
 * Returns the results and filenames of a review in a format for drush use.
 *
 * @param array $variables
 *   An associative array with the following keys:
 *   - name:
 *   - filename:
 *   - results:
 *
 * @ingroup themeable
 */
function theme_drush_coder_review(array $variables) {
  $name = $variables['name'];
  $filename = $variables['filename'];
  $results = $variables['results'];
  $no_empty = _coder_review_drush_get_option_no('empty');
  if (!drush_get_option('summary') && !empty($results) && ((empty($results[0]) || $results[0] != _t('No Problems Found')) || !$no_empty)) {
    if (drush_get_option('checkstyle') || drush_get_option('xml')) {
      _coder_review_drush_xml_output_results($filename, $results);
    }
    else {
      _coder_review_drush_print($filename . ":\n " . implode("\n ", $results) . "\n");
    }
  }
}

/**
 * Returns warning message, including source snippet, in format for drush use.
 *
 * @param array $variables
 *   An associative array with the following keys:
 *   - lineno:
 *   - severity_name:
 *   - warning:
 *   - line:
 *   - rule_name:
 *   - review_name:
 *
 * @ingroup themeable
 */
function theme_drush_coder_review_warning(array $variables) {
  // Supply default theme variables.
  $variables += array(
    'lineno' => 0,
    'line' => '',
    'warning' => dt('Unknown warning (drush)'),
  );

  // Return warning as XML.
  if (drush_get_option('xml') || drush_get_option('checkstyle')) {
    $attr = array(
      'line' => $variables['lineno'],
      'column' => 0,
      'severity' => $variables['severity_name'],
      'message' => $variables['warning'],
      'source' => $variables['line'],
    );
    if (drush_get_option('checkstyle')) {
      $checkstyle_levels = array(
        'minor' => 'info',
        'normal' => 'warning',
        'critical' => 'error',
      );
      $attr['severity'] = $checkstyle_levels[$variables['severity_name']];
    }
    return '<error ' . drupal_attributes($attr) . ' />';
  }

  // Return warning as text output, formatted for the drush screen.
  $output  = $variables['lineno'] ? ($variables['lineno'] == -1 ? dt('File') : ('+' . $variables['lineno'])) . ': ' : '';
  if (drush_get_option('ignorename')) {
    $output .= '[' . $variables['review_name'] . '_' . $variables['rule_name'] . ', ' . $variables['severity_name'] . '] ';
  }
  else {
    $output .= '[' . $variables['severity_name'] . '] ';
  }
  if (is_string($variables['warning'])) {
    $output .= $variables['warning'];
  }
  elseif (isset($variables['warning']['#warning'])) {
    $output .= dt($variables['warning']['#warning']);
  }
  elseif (isset($variables['warning']['#text'])) {
    $variables['warning'] += array('#args' => array());
    $output .= call_user_func('dt', $variables['warning']['#text'], $variables['warning']['#args']);
  }
  return _coder_review_drush_output($output);
}

/**
 * Prints Coder review messages in a format for drush use.
 *
 * @param array $summary
 *   An array of summary statistics about warnings and errors.
 */
function coder_review_print_drush_messages(array $summary) {
  // Count the number of warnings/errors.
  $sum = array_sum($summary['sums']);
  _coder_review_exit($sum ? 0 : 1);

  // Display messages if there is something to display.
  $no_empty = _coder_review_drush_get_option_no('empty');
  if ($no_empty || $sum) {
    foreach (_message() as $type => $messages) {
      $output = _coder_review_drush_output(implode("\n ", $messages));

      if (!drush_get_option('checkstyle')) {
        if (drush_get_option('xml')) {
          _coder_review_drush_print('<status type="' . $type . '">' . $output . '</status>');
        }
        else {
          _coder_review_drush_print(dt(ucfirst($type) . ' Messages') . ":\n " . $output . "\n");
        }
      }
    }
  }
}

/**
 * Strips all HTML tags from drush output.
 *
 * @param string $output
 *   A string that may contain one or more HTML tags.
 *
 * @return string
 *   A modified string without any HTML tags.
 */
function _coder_review_drush_output($output) {
  return html_entity_decode(strip_tags($output));
}

/**
 * Switches between drush print and drush print pipe of output.
 *
 * @param string $message
 *   A message string to print for display in drush.
 */
function _coder_review_drush_print($message) {
  if (drush_get_context('DRUSH_PIPE')) {
    drush_print_pipe($message);
  }
  else {
    drush_print($message);
  }
}

/**
 * Formats output as an appropriate XML header tag.
 *
 * @param string $type
 *   (optional) The type of XML desired. Defaults to 'xml'.
 */
function _coder_review_drush_xml_output_header($type = 'xml') {
  // Put in an extra concatenation so syntax highlighting in vim doesn't break.
  _coder_review_drush_print('<?xml version="1.0" encoding="UTF-8"?' . '>');
  _coder_review_drush_print($type == 'checkstyle' ? '<checkstyle version="1.3.0RC1">' : '<coderreview version="1.1">');
}

/**
 * Formats output as an appropriate XML footer tag.
 *
 * @param string $type
 *   (optional) The type of XML desired. Defaults to 'xml'.
 *
 * @todo Where is the @ignore syntax and use documented in this module?
 */
// @ignore upgrade7x_74 sniffer_commenting_functioncomment_missing
function _coder_review_drush_xml_output_footer($type = 'xml') {
  _coder_review_drush_print($type == 'checkstyle' ? '</checkstyle>' : '</coderreview>');
}

/**
 * Formats XML output for a severity level.
 *
 * @param string $severity_name
 *   The severity level name as a string.
 */
function _coder_review_drush_xml_output_severity($severity_name) {
  _coder_review_drush_print('<severity>' . $severity_name . '</severity>');
}

/**
 * Formats XML output for a list of chosen Coder reviews.
 *
 * @param array $reviews
 *   An array of Reviews.
 * @param array $avail_reviews
 *   ???
 */
function _coder_review_drush_xml_output_reviews(array $reviews, array $avail_reviews) {
  _coder_review_drush_print('<reviews>');
  foreach ($reviews as $review) {
    _coder_review_drush_print('<review>' . $avail_reviews[$review]['#title'] . '</review>');
  }
  _coder_review_drush_print('</reviews>');
}

/**
 * Formats XML output for a filename and its results (if any).
 *
 * @param string $filename
 *   The filename as a string.
 * @param array $results
 *   A Results array from performing a Coder review.
 */
function _coder_review_drush_xml_output_results($filename, array $results) {
  if (empty($results) || (count($results) == 1 && isset($results[0]))) {
    _coder_review_drush_print('<file name = "' . $filename . '" />');
  }
  else {
    _coder_review_drush_print('<file name = "' . $filename . '">' . "\n" . implode("\n ", $results) . "\n" . '</file>');
  }
}
