<?php
/**
 * @file
 * This include file implements coder_review functionality for Drupal Standards.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_style_reviews() {
  // @todo: add more specific #link's foreach #warning.
  $rules['no_tabs'] = array(
    '#type' => 'regex',
    '#value' => '\t',
    '#warning' => 'Use an indent of 2 spaces, with no tabs',
  );
  $rules['indent_spaces'] = array(
    '#type' => 'regex',
    '#never' => '<\?php',
    '#value' => '^ (  )*[^ \'".]',
    '#warning' => 'Use an indent of 2 spaces, with no tabs',
    '#severity' => 'minor',
  );
  $rules['control_spacing'] = array(
    '#type' => 'regex',
    '#value' => '\s(if|elseif|while|foreach|switch|case|return|for|catch)\(',
    '#warning' => 'Control statements should have one space between the control keyword and opening parenthesis',
  );
  $rules['function_spacing'] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](\w+)\s\(',
    '#not' => '^(if|elseif|while|foreach|switch|case|return|for|list|catch|function)$',
    '#warning' => 'Functions should be called with no spaces between the function name and opening parentheses',
  );
  $rules['paren_spacing'] = array(
    '#type' => 'regex',
    '#value' => '\){',
    '#warning' => 'use a space between the closing parenthesis and the open bracket',
  );
  $rules['array_spacing'] = array(
    '#type' => 'regex',
    '#value' => '(\S=>|=>\S)',
    '#source' => 'php',
    '#warning' => 'Arrays should be formatted with a space separating each element and assignment operator',
  );
  $rules['string_spacing'] = array(
    '#type' => 'regex',
    '#value' => '(\.(?:|\s{2,})[^\)\=\s0-9]|[^\(\s0-9](?:|\s{2,})\.)',
    '#warning' => 'String concatenation should be formatted with a space separating the operators (dot .) and the surrounding terms',
  );
  $rules['opening_php'] = array(
    '#type' => 'regex',
    '#value' => '<\?(\w+)',
    '#not' => '^(php|xml)$',
    '#warning' => 'Always use &lt;?php ?&gt; to delimit PHP code, not the &lt;? ?&gt; shorthand',
  );
  $rules['global_vars'] = array(
    '#type' => 'regex',
    '#value' => 'global\s+\$(\w+)(,\s\$(\w+))*',
    '#not' => '^_|^(' . _coder_review_style_core_global_regex() . ')$',
    '#warning' => 'global variables should start with a single underscore followed by the module and another underscore',
  );
  $rules['closing_php'] = array(
    '#type' => 'callback',
    '#source' => 'all',
    '#value' => '_coder_review_style_closing_php_callback',
    '#warning' => 'the final ?> should be omitted from all code files',
  );
  $rules['else_spacing'] = array(
    '#type' => 'regex',
    '#value' => '}\s*else',
    '#warning' => 'else statements should begin on a new line',
  );
  $rules['comma_spacing'] = array(
    '#type' => 'regex',
    '#value' => '[,][^ \n\r]',
    '#warning' => 'missing space after comma',
  );
  $rules['curly_braces'] = array(
    '#type' => 'regex',
    '#value' => '^\s*{',
    '#warning' => 'curly braces { should end a line, not start one',
  );
  $rules['camel_case'] = array(
    '#type' => 'regex',
    '#value' => '(?-i)(function\s+|\$)(([a-z]+_?[A-Z]+)|([A-Z]+_?[a-z]+))',
    '#warning' => 'do not use mixed case (camelCase), use lower case and _',
    '#class-not' => '.+',
    '#filename-not' => array('test'), // Add this line too for patch files, where we don't have have class context.
  );
  $rules['upper_functions'] = array(
    '#type' => 'regex',
    '#value' => '(?-i)(function\s+[A-Z]+\s*\()',
    '#warning' => array(
      '#text' => 'do not use UPPERCASE() function names',
      '#link' => _drupalnode(318, 'naming'),
    ),
  );
  $rules['stdclass'] = array(
    '#type' => 'regex',
    '#value' => '\s(stdclass)\s*\(',
    '#not' => '^(?-i)stdClass',
    '#warning' => "use stdClass caseCapitalization, it's the one exception to the mixed case style standard",
  );
  $rules['lowercase_html'] = array(
    '#type' => 'regex',
    '#source' => 'html',
    '#value' => '(?-i)<[A-Z]+',
    '#warning' => array(
      '#text' => 'use lowercase html tags to comply with <a href="@xhtml">XHTML</a>',
      '#args' => array(
        '@xhtml' => 'http://www.w3.org/TR/xhtml1/#h-4.2',
      ),
    ),
    '#severity' => 'minor',
  );
  $rules['control_newline'] = array(
    '#type' => 'regex',
    '#value' => '\s(if|elseif|while|foreach|switch|return|for|catch)\s*\(.*\) \s*{\s*[^\s]+',
    '#warning' => 'The control statement should be on a separate line from the control conditional',
  );
  $rules['template_controls'] = array(
    '#type' => 'regex',
    '#filename' => array('tpl.php'),
    '#value' => '\s(if|elseif)\s*\(.*\) \s*{\s*[^\s]+',
    '#warning' => 'The control statement should use ":" syntax instead of curly braces.',
  );
  $rules['trailing_spaces'] = array(
    '#type' => 'regex',
    '#source' => 'all',
    '#value' => '[ \t]+$',
    '#warning' => 'There should be no trailing spaces',
    '#severity' => 'minor',
  );
  // @todo Review if this rule throws too many false positives.
/*
  $rules['drupal_strings'] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](strlen|strtolower|strtoupper|substr|ucfirst)\s*\(',
    '#warning' => 'in most cases, replace the string function with the drupal_ equivalent string functions',
    '#severity' => 'minor',
  );
*/
  $rules['array_index'] = array(
    '#type' => 'regex',
    '#value' => '\[\s*[A-Za-z][A-Za-z0-9_]*\s*]',
    '#not' => '\[\s*[A-Z][A-Z0-9_]*\s*]',
    '#warning' => 'use quotes around a string literal array index, this is not only a style issue, but a known performance problem',
    '#case-sensitive' => TRUE,
  );
  $rules['uppercase_constants'] = array(
    '#type' => 'regex',
    '#value' => '[\s=>]+(true|false|null)[\)\s;,\n\r]+',
    '#case-sensitive' => TRUE,
    '#warning' => 'Use uppercase for PHP constants, e.g. NULL, TRUE, FALSE',
  );
  $rules['elseif'] = array(
    '#type' => 'regex',
    '#value' => '\s+else\s+if\s*\(',
    '#warning' => 'Use "elseif" in place of "else if"',
  );
  $rules['button_submit'] = array(
    '#type' => 'regex',
    '#value' => '\s*[\'"]#value[\'"]\s*=>\s*t\s*\(\s*[\'"]Submit[\'"]\s*\)',
    '#source' => 'allphp',
    '#warning' => 'When labelling buttons, make it clear what the button does, "Submit" is too generic.',
    '#severity' => 'minor',
  );
  $rules['class_names'] = array(
    '#type' => 'regex',
    '#value' => '(class|interface)\s+([a-z]|\w*_)',
    '#case-sensitive' => TRUE,
    '#warning' => 'Classes and interfaces should use UpperCamel naming.',
    '#severity' => 'minor',
  );
  $rules['method_names'] = array(
    '#type' => 'regex',
    '#value' => 'function\s+([A-Z]|\w*_)\s*\(',
    '#case-sensitive' => TRUE,
    '#warning' => 'Methods and class properties should use lowerCamel naming.',
    '#class' => '.+',
    '#not' => 'function\s+__(construct|destruct)\s*\(',
    '#severity' => 'minor',
  );

  $review = array(
    '#title' => 'Drupal Coding Standards',
    '#link' => _drupalnode(318),
    '#rules' => $rules,
    '#description' => 'Checks for Drupal coding standards. Every developer should use this.',
    '#version' => 2,
    '#image' => 'images/style.png',
  );
  return array('style' => $review);
}

/**
 * Rule callback: Defines the rule callbacks for style.
 *
 * @see do_coder_review_callback()
 */
function _coder_review_style_closing_php_callback(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  for ($lineno = -1; $last = array_slice($lines, $lineno); $lineno --) {
    $lastline = $last[0][0];
    if (preg_match('/\S/', $lastline)) {
      break;
    }
  }
  if ($last && $lastline && preg_match('/\?>\s*$/i', $lastline)) {
    $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
    _coder_review_error($results, $rule, $severity_name, count($lines));
  }
}

/**
 * Returns regex of all global core variables.
 */
function _coder_review_style_core_global_regex() {
  static $coreglobalregex;
  if (!isset($coreglobalregex)) {
    $coreglobalvars = array(
      'base_insecure_url',
      'base_path',
      'base_root',
      'base_secure_url',
      'base_theme_info',
      'base_url',
      'channel',
      'conf',
      'cookie_domain',
      'databases',
      'db_prefix',
      'db_url',
      'drupal_hash_salt',
      'drupal_test_info',
      'element',
      'forum_topic_list_header',
      'image',
      'install_state',
      'installed_profile',
      'is_https',
      'is_https_mock',
      'item',
      'items',
      'language',
      'language_content',
      'language_url',
      'locks',
      'menu_admin',
      'multibyte',
      'pager_limits',
      'pager_page_array',
      'pager_total',
      'pager_total_items',
      'tag',
      'theme',
      'theme_engine',
      'theme_info',
      'theme_key',
      'theme_path',
      'timers',
      'update_free_access',
      'update_rewrite_settings',
      'user',
    );
    $coreglobalregex = implode('|', $coreglobalvars);
  }
  return $coreglobalregex;
}
