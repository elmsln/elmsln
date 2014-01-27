<?php
/**
 * @file
 * This include file implements coder_review functionality for 4.7 -> 5.x upgrades.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_5x_reviews() {
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]user_mail\s*\(',
    '#warning' => array(
      '#text' => '!user_mail() is replaced by !drupal_mail()',
      '#args' => array(
        '!user_mail' => _drupalapi('user_mail', 4.7),
        '!drupal_mail' => _drupalapi('drupal_mail', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]user_mail_wrapper\s*\(',
    '#warning' => array(
      '#text' => '!user_mail_wrapper() changed to !drupal_mail_wrapper()',
      '#args' => array(
        '!user_mail_wrapper' => _drupalapi('user_mail_wrapper', 4.7),
        '!drupal_mail_wrapper' => _drupalapi('drupal_mail_wrapper', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]message_na\s*\(',
    '#warning' => array(
      '#text' => 'The function !message_na() was removed, remove it from your modules as well and replace it with !t(\'n/a\')',
      '#args' => array(
        '!message_na' => _drupalapi('message_na', 4.7),
        '!t' => _drupalapi('t', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]module_exist\s*\(',
    '#warning' => array(
      '#text' => '!module_exist() is now !module_exists()',
      '#args' => array(
        '!module_exist' => _drupalapi('module_exist', 4.7),
        '!module_exists' => _drupalapi('module_exists', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_call_js\s*\(',
    '#warning' => array(
      '#text' => 'Remove !drupal_call_js(), use "!drupal_add_js(\'myCustomFunction(your, parameters, here)\', \'inline\');" instead',
      '#args' => array(
        '!drupal_call_js' => _drupalapi('drupal_call_js', 4.7),
        '!drupal_add_js' => _drupalapi('drupal_add_js', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]system_listing\s*\(',
    '#warning' => array(
      '#text' => '!system_listing() is now !drupal_system_listing()',
      '#args' => array(
        '!system_listing' => _drupalapi('system_listing', 4.7),
        '!drupal_system_listing' => _drupalapi('drupal_system_listing', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_get_name\s*\(',
    '#warning' => array(
      '#text' => 'Replace !node_get_name($node) with !node_get_types(\'name\', $node)',
      '#args' => array(
        '!node_get_name' => _drupalapi('node_get_name', 4.7),
        '!node_get_types' => _drupalapi('node_get_types', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '\$_POST\s*\[\s*[\'"]?op[\'"]?\s*\]',
    '#warning' => '$_POST[\'op\'] deprecated in favor of $form_values[\'op\']',
    '#severity' => 'normal',
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_5x_callback',
    '#warning' => array(
      '#text' => 'modules Mow need to have a modulename.info file',
      '#link' => _drupalnode(101009),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'all',
    '#value' => '[\s\(]theme_add_style\s*\(',
    '#warning' => array(
      '#text' => 'Replace !theme_add_style() with !drupal_add_css()',
      '#args' => array(
        '!theme_add_style' => _drupalapi('theme_add_style', 4.7),
        '!drupal_add_css' => _drupalapi('drupal_add_css', 5),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'all',
    '#value' => '[\s\(]form_render\s*\(',
    '#warning' => array(
      '#text' => 'Replace !form_render() with !drupal_render()',
      '#args' => array(
        '!form_render' => _drupalapi('form_render', 4.7),
        '!drupal_render' => _drupalapi('drupal_render', 5),
      ),
    ),
  );

  $review = array(
    '#title' => 'Converting 4.7.x modules to 5.x',
    '#link' => _drupalnode(64279),
    '#rules' => $rules,
    '#severity' => 'critical',
    '#version' => 2,
    '#image' => 'images/5.png',
  );
  return array('upgrade5x' => $review);
}

/**
 * Define the rule callbacks for 5.x, see do_coder_review_review_callback().
 */
function _coder_review_5x_callback(&$coder_args, $review, $rule, $lines, &$results) {
  // Only perform this check on module's (not includes).
  $pathinfo = pathinfo(realpath($coder_args['#filename']));
  if ($pathinfo['extension'] == 'module') {
    // Make sure that a .info file exists.
    if (!file_exists($pathinfo['dirname'] . '/' . $pathinfo['filename'] . '.info')) {
      $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
      _coder_review_error($results, $rule, $severity_name);
    }
  }
}
