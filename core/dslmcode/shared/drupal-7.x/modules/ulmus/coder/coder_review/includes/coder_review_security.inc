<?php

/**
 * @file
 * This include file implements coder functionality for Drupal Standards.
 *
 * @todo The rules for this review are not yet complete.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_security_reviews() {
  $argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'\'|"")';
  $allphp_argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'[^\']+\'|"[^"]+")';
  $sanitize_argex = '((t|st|\$t|check_plain|format_plural|check_markup|field_filter_xss|filter_xss|filter_xss_admin)\s*\([^\)]+?\))';
  $table = '\{[A-Za-z_]+\}'; // table-regex

  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]trigger_error\s*\(\s*[^\$]+.+\$',
    '#never' => '(^function\s|trigger_error\s*\(\s*(((st|t|\$t)\s*\()|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_trigger_error_filter_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]trigger_error\s*\(\s*(st|t|\$t)\s*\(\s*((.*?\$)|([\'"].*?!\w+.*?[\'"]\s*,)|(.*?array\(.*?!\w+.*?\)))',
    '#never' => '(^function\s|trigger_error\s*\(\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => 'Potential problem: !trigger_error() only accepts filtered text, be sure all !placeholders for $variables in !t() are fully sanitized using !check_plain(), !filter_xss() or similar.',
      '#args' => array(
        '!trigger_error' => _phpapi('trigger_error'),
        '!t' => _drupalapi('t'),
        '!check_plain' => _drupalapi('check_plain'),
        '!filter_xss' => _drupalapi('filter_xss'),
      ),
      '#link' => _drupalnode(28984),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_set_message\s*\(\s*[^\$)]+.+\$',
    '#never' => '(^function\s|drupal_set_message\s*\(\s*(((st|t|\$t)\s*\()|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_drupal_set_message_filter_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_set_message\s*\(\s*(st|t|\$t)\s*\(\s*((.*?\$)|([\'"].*?!\w+.*?[\'"]\s*,)|(.*?array\(.*?!\w+.*?\)))',
    '#never' => '(^function\s|drupal_set_message\s*\(\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_drupal_set_message_filter_t_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](form_set_error|form_error)\s*\(\s*' . $argex . '\s*,\s*[^\$)]+.+\$',
    '#never' => '(^function\s|(form_set_error|form_error)\s*\(\s*' . $argex . '\s*,\s*(((st|t|\$t)\s*\()|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_form_set_error_filter_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](form_set_error|form_error)\s*\(\s*' . $argex . '\s*,\s*(st|t|\$t)\s*\(\s*((.*?\$)|([\'"].*?!\w+.*?[\'"]\s*,)|(.*?array\(.*?!\w+.*?\)))',
    '#never' => '(^function\s|(form_set_error|form_error)\s*\(\s*' . $argex . '\s*,\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_form_set_error_filter_t_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]confirm_form\s*\(\s*' . $argex . '\s*,\s*[^\$\s]+.+\$[^,]+,\s*' . $argex . '\s*\)',
    '#never' => '(^function\s|confirm_form\s*\(\s*' . $argex . '\s*,\s*(((st|t|\$t)\s*\()|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_confirm_form_filter_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]confirm_form\s*\(\s*' . $argex . '\s*,\s*(st|t|\$t)\s*\(\s*((\$\w+[,\)])|("[^"]+?\$\w+.*?"\s*[,\)])|([\'"].*?[\'"]\s*\.\s*\$\w)|([\'"].*?!\w+.*?[\'"]\s*,)|(.*?array\(.*?!\w+.*?\)))',
    '#never' => '(^function\s|confirm_form\s*\(\s*' . $argex . '\s*,\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)',
    '#source' => 'allphp',
    '#warning' => _coder_review_security_confirm_form_filter_t_warning(),
  );
  // confirm_form 4th, 5th and 6th args
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]confirm_form\s*\(\s*((' . $allphp_argex . '|' . $sanitize_argex . ')\s*,\s*){3,5}([^\$\s]+.+\$[^,\)]+)(' . $allphp_argex . ')??\)\s*;',
    '#never' => '(^function\s|confirm_form\s*\(\s*((' . $allphp_argex . '|' . $sanitize_argex . ')\s*,\s*){3,5}((st|t|\$t|format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\([^\)\$]+\)).*?(' . $allphp_argex . ')??\)\s*;)',
    '#source' => 'allphp',
    '#warning' => '_coder_review_security_confirm_form_filter_warning',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]confirm_form\s*\(\s*((' . $allphp_argex . '|' . $sanitize_argex . ')\s*,\s*){3,5}(st|t|\$t)\s*\(\s*((\$\w+[,\)])|("[^"]+?\$\w+.*?"\s*[,\)])|([\'"].*?[\'"]\s*\.\s*\$\w)|([\'"].*?!\w+.*?[\'"]\s*,)|(.*?array\(.*?!\w+.*?\))).*?(' . $allphp_argex . ')??\)\s*;',
    '#never' => '(^function\s|confirm_form\s*\(\s*((' . $allphp_argex . '|' . $sanitize_argex . ')\s*,\s*){3,5}(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\([^\)\$]+\)).*?(' . $allphp_argex . ')??\)\s*;)',
    '#source' => 'allphp',
    '#warning' => _coder_review_security_confirm_form_filter_t_warning(),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#severity' => 'minor',
    '#value' => '[\s\(]l\(check_plain\(.*',
    '#never' => '[\'"]html[\'"]\s*=>\s*(TRUE|1)',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => '!l() already contains a !check_plain() call by default.',
      '#args' => array(
        '!l' => _drupalapi('l'),
        '!check_plain' => _drupalapi('check_plain'),
      ),
      '#link' => _drupalnode(28984),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '(?-i)\$REQUEST_URI',
    '#warning' => _coder_review_security_request_uri_warning(),
    '#function-not' => '^(request_uri|request_path|drupal_detect_baseurl)$',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '(?-i)\"REQUEST_URI\"|\'REQUEST_URI\'',
    '#warning' => _coder_review_security_request_uri_warning(),
    '#function-not' => '^(request_uri|request_path|drupal_detect_baseurl)$',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $table . '|insert\s+into\s+' . $table . '|update\s+' . $table . '\s+set|delete\s+from\s+' . $table . ')\s+.*\$[a-z0-9_]+',
    '#not' => '\$placeholder',
    '#source' => 'quote',
    '#warning' => array(
      '#text' => 'In SQL strings, Use !db_query() placeholders in place of variables.  This is a potential source of SQL injection attacks when the variable can come from user data.',
      '#args' => array(
        '!db_query' => _drupalapi('db_query'),
      ),
      '#link' => _drupalnode(62304),
      '#description' => 'Use %s and %d variable substitution.  When inserting an array of values use <code>$placeholders = implode(\',\', array_fill(0, count($args), "\'%s\'"));</code>',
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $table . '|insert\s+into\s+' . $table . '|update\s+' . $table . '\s+set|delete\s+from\s' . $table . ')\s+[^\']*?(\s+|\(|=|,)\%s',
    '#source' => 'quote',
    '#warning' => 'SQL query handling data in a potentially insecure way by using the %%s placeholder without wrapping it in single quotes.  This is a potential source of SQL injection attacks when the value can come from user data.',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp', // allow us to look inside the regex string
    '#value' => '\bpreg_replace\s*\(\s*(\'(.)([^\'\\\\]|\\\\.)*\\2([^\'\\\\]|\\\\.)*|"(.)([^"\\\\]|\\\\.)*\\5([^"\\\\]|\\\\.)*)e',
    '#warning' => "Use preg_replace_callback() instead of the 'e' modifier to preg_replace()",
    '#severity' => 'critical',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\'"]access callback.*=.*\(',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => "The value for the 'access callback' must always be a string which is the the name of the function - never a function call. It may also be assigned the value TRUE or FALSE if the callback is always (or never) accessible.",
      '#link' => _drupalnode(109157),
    ),
    '#function' => '_menu$',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#severity' => 'minor',
    '#value' => '\$_(POST)\[.+?\]',
    '#never' => '((((==|!=|>=|<=|>|<)\s*|[!\s\(](form_get_cache|form_set_cache|format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup|isset|empty|foreach|while|if|elseif)\s*\(\s*)\$_(POST)\[.+?\])|\$_(POST)\[.+?\]\s*(\.=|=|!=))',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => 'Potential problem: use the Form API to prevent against CSRF attacks. If you need to use $_POST variables, ensure they are fully sanitized if displayed by using !check_plain(), !filter_xss() or similar.',
      '#args' => array(
        '!check_plain' => _drupalapi('check_plain'),
        '!filter_xss' => _drupalapi('filter_xss'),
      ),
      '#link' => _drupalnode(178896),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'html',
    '#value' => '<form[\s\'"]',
    '#warning' => array(
      '#text' => 'Use the Form API to build forms to help prevent against CSRF attacks.',
      '#link' => _drupalnode(178896),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](drupal_)*?eval\s*\([^\)]*?\$',
    '#never' => '(^function\s)',
    '#source' => 'php',
    '#warning' => array(
      '#text' => "Using !eval() or !drupal_eval() in your module's code could have a security risk if the PHP input provided to the function contains malicious code.",
      '#args' => array(
        '!eval' => _phpapi('eval'),
        '!drupal_eval' => _drupalapi('drupal_eval'),
      ),
      '#link' => _drupalnode(715010),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\[][\'"]subject[\'"](\])*?\s*=(>)*?\s*\$',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => 'Potential problem: !hook_block() only accepts filtered text as the block title, be sure to use !check_plain(), !filter_xss() or similar to ensure your $variable is fully sanitized.',
      '#args' => array(
        '!hook_block' => _drupalapi('hook_block'),
        '!check_plain' => _drupalapi('check_plain'),
        '!filter_xss' => _drupalapi('filter_xss'),
      ),
      '#link' => _drupalnode(28984),
    ),
    '#function' => '_block$',
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_security_callback',
  );

  $review = array(
    '#title' => 'Drupal Security Checks',
    '#link' => _drupalnode(28984),
    '#rules' => $rules,
    '#severity' => 'critical',
    '#description' => 'Checks for security issues. This is a very basic security check. It errs on the side of caution so may give false positives.',
    '#version' => 2,
    '#image' => 'images/security.png',
  );
  return array('security' => $review);
}

/**
 * Define the rule callbacks.
 */

function _coder_review_security_callback(&$coder_args, $review, $rule, $lines, &$results) {
  $argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'\'|"")';
  $allphp_argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'[^\']+\'|"[^"]+")';
  $sanitize_argex = '((t|st|\$t|check_plain|format_plural|check_markup|field_filter_xss|filter_xss|filter_xss_admin)\s*\([^\)]+?\))';

  $severity_name = _coder_review_severity_name($coder_args, $review, $rule);

  // Check for calls to trigger_error(), confirm_form(), drupal_set_title(),
  // drupal_set_message(), form_error() and form_set_error() on $vars without a
  // sanitizing function. If found, look back up within current function.
  //
  // @todo: what are we doing? why can't we use #function? needs better comment.
  $this_function = '';
  $function_paren = 0;
  $forward_matches = array();
  $function_name = '';
  foreach ($coder_args['#all_lines'] as $lineno => $line) {
    // Start of a function, store the line.
    if (preg_match('/function (\w+)\(/', $line, $match)) {
      $this_function = $line;
      $function_name = $match[1];
    }
    // Within a function.
    elseif ($function_paren > 0) {
      $this_function .= $line;
    }
    // Check to see if we're still in a function by counting number of {} chars.
    $tmp_line = preg_replace(array('/([^\\\])\'.+?[^\\\]\'/', '/([^\\\])".+?[^\\\]"/'), '$1', $line);
    if (preg_match('/([{}])/', $tmp_line, $match)) {
      $function_paren += ($match[0] == '{') ? 1 : -1;

      // If we've just exited a function, run forward match checks.
      if ($function_paren <= 0) {
        // FAPI #value
        if (isset($forward_matches['fapi_markup_value'])) {
          $find_match = '/[\s=]array\s*\(\s*([^\)]*?([\'"]#value[\'"]\s*=>\s*.*?\$' . $forward_matches['fapi_markup_value'] . '.*?))\);/';
          if (preg_match($find_match, $this_function, $sanitized_matches)) {
            if (!preg_match('/[\'"]#type[\'"]/', $sanitized_matches[1], $markup_matches) || preg_match('/[\'"]#type[\'"]\s*=>\s*[\'"]markup[\'"]/', $sanitized_matches[1], $markup_matches)) {
              $tmprule = $rule;
              $tmprule['#rule_name'] = 'fapi_markup';
              $tmprule['#warning'] = _coder_review_security_fapi_markup_value_warning();
              _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
            }
          }
        }
        $forward_matches = array();
        $function_name = '';
      }
    }
    // If we're not in a function, continue.
    if ($function_paren < 0 || $this_function == '') {
      continue;
    }

    // Run multi-line reviews.

    // trigger_error()
    $regex = '/[\s\(]trigger_error\s*\(\s*\$(\w+)\s*[,\)]/';
    $never_regex = '/(^function\s|trigger_error\s*\(\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)/';
    if (preg_match($regex, $line, $matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[1] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $tmprule = $rule;
          $tmprule['#rule_name'] = 'trigger_error';
          $tmprule['#warning'] = _coder_review_security_trigger_error_filter_warning();
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // drupal_set_message()
    $regex = '/[\s\(]drupal_set_message\s*\(\s*\$(\w+)\s*[,\)]/';
    $never_regex = '/(^function\s|drupal_set_message\s*\(\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)/';
    if (preg_match($regex, $line, $matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[1] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $tmprule = $rule;
          $tmprule['#rule_name'] = 'dsm';
          $tmprule['#warning'] = _coder_review_security_drupal_set_message_filter_warning();
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // form_set_error() and form_error()
    $regex = '/[\s\(](form_set_error|form_error)\s*\(\s*' . $argex . '\s*,\s*\$(\w+)\s*[,\)]/';
    $never_regex = '/(^function\s|(form_set_error|form_error)\s*\(\s*' . $argex . '\s*,\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)/';
    if (preg_match($regex, $line, $matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[8] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $tmprule = $rule;
          $tmprule['#rule_name'] = 'form_set_error';
          $tmprule['#warning'] = _coder_review_security_form_set_error_filter_warning();
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // confirm_form()
    $regex = '/[\s\(]confirm_form\s*\(\s*' . $argex . '\s*,\s*\$(\w+)\s*[,\)]/';
    $never_regex = '/(^function\s|confirm_form\s*\(\s*' . $argex . '\s*,\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)/';
    if (preg_match($regex, $line, $matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[7] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $tmprule = $rule;
          $tmprule['#rule_name'] = 'confirm_form';
          $tmprule['#warning'] = _coder_review_security_confirm_form_filter_warning();
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // confirm_form() - 4th, 5th and 6th args
    $regex = '/[\s\(]confirm_form\s*\(\s*((' . $allphp_argex . '|' . $sanitize_argex . ')\s*,\s*){3,5}\$(\w+)\s*[,\)]/';
    $never_regex = '/(^function\s|confirm_form\s*\(\s*((' . $allphp_argex . '|' . $sanitize_argex . ')\s*,\s*){3,5}(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*$)/';
    if (preg_match($regex, $line, $matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[11] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $tmprule = $rule;
          $tmprule['#rule_name'] = 'comfirm_form_456';
          $tmprule['#warning'] = _coder_review_security_confirm_form_filter_warning();
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // FAPI #title and #description
    $regex = '/[\'"]#(title|description)[\'"]\s*=>\s*.*?\$(\w+)\s*.*?[,\)]/';
    $never_regex = '/([\'"]#(title|description)[\'"]\s*=>\s*((((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*))/';
    if (preg_match($regex, $line, $matches) && preg_match('/_form(_alter)*$/', $function_name, $function_matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[1] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $tmprule = $rule;
          $tmprule['#rule_name'] = 'fapi_title';
          $tmprule['#warning'] = _coder_review_security_fapi_title_description_warning();
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // FAPI #value
    $regex = '/[\'"]#value[\'"]\s*=>\s*.*?\$(\w+)\s*.*?[,\)]/';
    $never_regex = '/([\'"]#value[\'"]\s*=>\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\().*)/';
    if (preg_match($regex, $line, $matches) && preg_match('/_form(_alter)*$/', $function_name, $function_matches)) {
      if (!preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
        $before_never_regex = '/[\s]\$' . $matches[1] . '\s*=\s*(((st|t|\$t)\s*\(((\s*[\'"][^!]+?[\'"]\s*,)|(.*?array\([^!]+\))))|(format_plural|field_filter_xss|filter_xss|filter_xss_admin|check_plain|check_markup)\s*\()/';
        if (!preg_match($before_never_regex, $this_function, $sanitized_matches)) {
          $forward_matches['fapi_markup_value'] = $matches[1];
        }
      }
    }
  }
}

/**
 * Warning callback: Defines the parameters for trigger_error_filter_warning.
 *
 * @return array
 *   An array of warning message parameters to be used in the construction of a
 *   warning display string.
 */
function _coder_review_security_trigger_error_filter_warning() {
  return array(
    '#text' => 'Potential problem: !trigger_error() only accepts filtered text, be sure to use !check_plain(), !filter_xss() or similar to ensure your $variable is fully sanitized.',
    '#args' => array(
      '!trigger_error' => _phpapi('trigger_error'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_drupal_set_message_filter_warning() {
  return array(
    '#text' => 'Potential problem: !drupal_set_message() only accepts filtered text, be sure to use !check_plain(), !filter_xss() or similar to ensure your $variable is fully sanitized.',
    '#args' => array(
      '!drupal_set_message' => _drupalapi('drupal_set_message'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_drupal_set_message_filter_t_warning() {
  return array(
    '#text' => 'Potential problem: !drupal_set_message() only accepts filtered text, be sure all !placeholders for $variables in !t() are fully sanitized using !check_plain(), !filter_xss() or similar.',
    '#args' => array(
      '!drupal_set_message' => _drupalapi('drupal_set_message'),
      '!t' => _drupalapi('t'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_form_set_error_filter_warning() {
  return array(
    '#text' => 'Potential problem: !form_set_error() and !form_error() only accept filtered text, be sure to use !check_plain(), !filter_xss() or similar to ensure your $variable is fully sanitized.',
    '#args' => array(
      '!form_set_error' => _drupalapi('form_set_error'),
      '!form_error' => _drupalapi('form_error'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_form_set_error_filter_t_warning() {
  return array(
    '#text' => 'Potential problem: !form_set_error() and !form_error() only accept filtered text, be sure all !placeholders for $variables in !t() are fully sanitized using !check_plain(), !filter_xss() or similar.',
    '#args' => array(
      '!form_set_error' => _drupalapi('form_set_error'),
      '!form_error' => _drupalapi('form_error'),
      '!t' => _drupalapi('t'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_confirm_form_filter_warning() {
  return array(
    '#text' => 'Potential problem: !confirm_form() only accepts filtered text, be sure to use !check_plain(), !filter_xss() or similar to ensure your $variable is fully sanitized.',
    '#args' => array(
      '!confirm_form' => _drupalapi('confirm_form'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_confirm_form_filter_t_warning() {
  return array(
    '#text' => 'Potential problem: !confirm_form() only accepts filtered text, be sure all !placeholders for $variables in !t() are fully sanitized using !check_plain(), !filter_xss() or similar.',
    '#args' => array(
      '!confirm_form' => _drupalapi('confirm_form'),
      '!t' => _drupalapi('t'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_request_uri_warning() {
  return array(
    '#text' => 'the use of REQUEST_URI is prone to XSS exploits and does not work on IIS; use !request_uri() instead',
    '#args' => array(
      '!request_uri' => _drupalapi('request_uri'),
    ),
  );
}

function _coder_review_security_fapi_title_description_warning() {
  return array(
    '#text' => "Potential problem: FAPI elements '#title' and '#description' only accept filtered text, be sure to use !check_plain(), !filter_xss() or similar to ensure your \$variable is fully sanitized.",
    '#args' => array(
      '!hook_form' => _drupalapi('hook_form'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}

function _coder_review_security_fapi_markup_value_warning() {
  return array(
    '#text' => "Potential problem: when FAPI element '#type' is set to 'markup' (default), '#value' only accepts filtered text, be sure to use !check_plain(), !filter_xss() or similar to ensure your \$variable is fully sanitized.",
    '#args' => array(
      '!hook_form' => _drupalapi('hook_form'),
      '!check_plain' => _drupalapi('check_plain'),
      '!filter_xss' => _drupalapi('filter_xss'),
    ),
    '#link' => _drupalnode(28984),
  );
}
