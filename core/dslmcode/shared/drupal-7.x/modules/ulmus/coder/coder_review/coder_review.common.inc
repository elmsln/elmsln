<?php

/**
 * @file
 * Common functions used by both the drush and form interfaces.
 */

/**
 * Specifies the Minor severity level.
 */
define('SEVERITY_MINOR', 1);

/**
 * Specifies the Normal severity level.
 */
define('SEVERITY_NORMAL', 5);

/**
 * Specifies the Critical severity level.
 */
define('SEVERITY_CRITICAL', 9);

/**
 * Creates a list of all modules that implement hook_reviews().
 *
 * @return array
 *   An array of return values of the from  hook_reviews() implementations.
 */
function _coder_review_reviews() {
  static $cache = array();
  if (!$cache) {
    // Always get the coder review.
    $cache = coder_review_reviews();

    // When Drupal is bootstrapped, also get all reviews.
    if (function_exists('module_invoke_all')) {
      $cache = array_merge($cache, module_invoke_all('reviews'));
    }
  }
  return $cache;
}

/**
 * Implements hook_reviews().
 *
 * This creates an array of all of the reviews that are implemented by the
 * coder_review module.
 *
 * @see hook_reviews()
 *
 * @todo Add an abbreviated explanation of what is coder_review.api.php.
 */
function coder_review_reviews() {
  static $cache = array();
  if (!$cache) {
    $path = _coder_review_file_path() . '/includes';
    foreach (scandir($path) as $file) {
      $pathinfo = pathinfo("$path/$file");
      if ($pathinfo['extension'] == 'inc') {
        require_once "$path/$file";
        $function = $pathinfo['filename'] . '_reviews';
        if (function_exists($function)) {
          $review = $function();
          if ($review) {
            foreach (array_keys($review) as $review_name) {
              $review[$review_name]['#file'] = "$path/$file";
            }
            $cache += $review;
          }
        }
      }
    }
  }
  return $cache;
}

/**
 * Returns a default list of reviews to perform a coder_review analysis upon.
 *
 * @return array
 *   An associative array with keys set to the names of the reviews to perform.
 *   The values are set to ???
 *
 * @see _coder_review_get_default_settings()
 */
function _coder_review_default_reviews() {
  // Do not use drupal_map_assoc() so that this will run without Drupal being
  // bootstraped.
  return array(
    'style' => 'style',
    'sql' => 'sql',
    'comment' => 'comment',
    'security' => 'security',
    'i18n' => 'i18n',
    'sniffer' => 'sniffer',
  );
}

/**
 * Creates a list of required filename extensions the included in default list.
 *
 * @param array $defaults
 *   An array of default filename extensions.
 * @param array $reviews
 *   An array of available coder reviews.
 *
 * @return array
 *   An array of file extensions, which are required to perform any of the
 *   reviews, but arenot part of the default filename extension list.
 *
 * @see coder_review_page_form()
 * @see coder_review_test_case.tinc::runTest()
 */
function _coder_review_get_reviews_extensions(array $defaults, array $reviews) {
  $extensions = array();
  foreach ($reviews as $key => $review) {
    foreach ($review['#rules'] as $rule) {
      if (isset($rule['#filename'])) {
        foreach ($rule['#filename'] as $ext) {
          if (!in_array($ext, $defaults) && !in_array($ext, $extensions)) {
            $extensions[] = $ext;
          }
        }
      }
    }
  }
  return $extensions;
}

/**
 * Determines most recent modification timestamp of key coder_review code files.
 *
 * @return int
 *   A Unix timestamp that represents the latest time that any of the key code
 *   files that are part of the coder_review module was modified.
 */
function _coder_review_modified() {
  static $cached_mtime = 0;
  if (!$cached_mtime) {
    // Create a list of all files whose timestamps are worth checking.
    $files[] = _coder_review_file_path() . '/coder_review.module';
    $files[] = _coder_review_file_path() . '/coder_review.common.inc';
    foreach (coder_review_reviews() as $review) {
      $files[] = $review['#file'];
    }

    // Find the newest filetime.
    foreach ($files as $file) {
      $mtime = filemtime($file);
      if ($mtime > $cached_mtime) {
        $cached_mtime = $mtime;
      }
    }
  }
  return $cached_mtime;
}

/**
 * Performs coder reviews for multiple code review definition files.
 *
 * @param array $coder_args
 *   An associative array of coder arguments. The valid arguments are:
 *   - #reviews => An array list of reviews to perform.  For more information,
 *     see _coder_review_reviews().
 *   - #severity => An integer magic number. See the constants SEVERITY_*, as
 *     defined at the top of coder_review.common.inc.
 *   - #filename => A string with the filename to check.
 *   - #patch => A string with the patch lines to perform a review on.
 *
 * @return array
 *   An associative array of results, in the form:
 *   - #stats => An array with error counts for all severities, in the form:
 *     - 'minor' => An integer count.
 *     - 'normal' => An integer count.
 *     - 'critical' => An integer count.
 *   - integer ID => An HTML error message string for display.
 *
 * @see _coder_review_reviews()
 */
function do_coder_reviews(array $coder_args) {
  // Load the cached results if they exist, but not for patches.
  if (empty($coder_args['#patch']) && empty($coder_args['#test']) && $coder_args['#cache']) {
    // @todo Replace md5() with with sha256().  See [#723802] for more info.
    $cache_key = 'coder:' . md5(implode(':', array_keys($coder_args['#reviews']))) . $coder_args['#severity'] . ':' . $coder_args['#filename'];
    if (_drush()) {
      if (drush_get_option('checkstyle')) {
        $cache_key .= ':drushcheckstyle';
      }
      elseif (drush_get_option('xml')) {
        $cache_key .= ':drushxml';
      }
    }
    $filepath = realpath($coder_args['#filename']);
    if (file_exists($filepath)) {
      $cache_mtime = filemtime($filepath);
      $cache_results = _cache_get($cache_key, 'cache_coder');
      if ($cache_results && $cache_results->data['mtime'] == $cache_mtime && _coder_review_modified() < $cache_results->created) {
        return $cache_results->data['results'];
      }
    }
  }

  $results['#stats'] = array('minor' => 0, 'normal' => 0, 'critical' => 0, 'ignored' => 0);

  // Skip PHP include files when the user requested severity is above minor.
  if (isset($coder_args['#php_minor']) && _substr($coder_args['#filename'], -4) == '.php') {
    if ($coder_args['#severity'] > 1) {
      return $results;
    }
  }

  // Read the file.
  if (_coder_review_read_and_parse_file($coder_args)) {
    // Do all of the code reviews.
    $errors = array();
    foreach ($coder_args['#reviews'] as $review_name => $review) {
      $review['#review_name'] = $review_name;
      $result = do_coder_review($coder_args, $review);
      if ($result) {
        // Keep track of severity and "ignored" statistics.
        foreach (array('critical', 'normal', 'minor', 'ignored') as $severity_level) {
          if (isset($result['#stats'][$severity_level])) {
            $results['#stats'][$severity_level] += $result['#stats'][$severity_level];
          }
        }
        $errors += $result;
      }
    }

    // Theme the error messages.
    foreach ($errors as $key => $error) {
      if (is_numeric($key)) {
        $error['warning'] = _coder_review_warning($error['rule']);
        $results[$key] = theme_coder_review_warning($error);
      }
    }

    // Sort the results.
    ksort($results, SORT_NUMERIC);
  }
  else {
    $results[] = theme('coder_review_warning', array('warning' => _t('Could not read the file'), 'severity_name' => 'critical'));
  }

  // Save the results in the cache if we're not reviewing a patch.
  if (empty($coder_args['#patch']) && empty($coder_args['#test']) && $coder_args['#cache'] && isset($cache_mtime)) {
    $cache_results = array(
      'mtime' => $cache_mtime,
      'results' => $results,
    );
    _cache_set($cache_key, $cache_results, 'cache_coder');
  }

  return $results;
}

/**
 * Returns HTML for a coder_review warning to be included in results.
 *
 * @param array $variables
 *   An associative array, which includes the following keys:
 *   - warning: Either summary warning description, or an array in format:
 *     - #warning: A summary warning description.
 *     - #description: A detailed warning description.
 *     - #link: A link to an explanatory document.
 *   - severity_name: The severity name as a string.
 *   - lineno: An integer line number on which error was detected.
 *   - line: A string with the contents of line.
 *   - review_name: A string with the review name.
 *   - rule_name: A string with the rule name.
 *
 * @ingroup themeable
 */
function theme_coder_review_warning($variables) {
  // Theme the output for the Drupal shell.
  if (_drush()) {
    return theme_drush_coder_review_warning($variables);
  }

  $warning = $variables['warning'];
  $severity_name = $variables['severity_name'];
  $review_name = $variables['review_name'];
  $rule_name = $variables['rule_name'];
  $lineno = $variables['lineno'];
  $line = $variables['line'];

  // Extract description from warning.
  if (is_array($warning)) {
    $description = isset($warning['#description']) ? _t($warning['#description']) : '';
    if (isset($warning['#warning'])) {
      $warning_msg = _t($warning['#warning']);
    }
    elseif (isset($warning['#text'])) {
      $warning += array('#args' => array());
      $warning_msg = _t($warning['#text'], $warning['#args']);
    }
    if (isset($warning['#link'])) {
      $warning_msg .= ' (' . l(_t('Drupal Docs'), $warning['#link']) . ')';
    }
    $warning = $warning_msg;
  }
  if ($lineno) {
    if ($lineno > 0) {
      $warning = _t('Line @number: !warning [@review_@rule]', array('@number' => $lineno, '!warning' => $warning, '@review' => $review_name, '@rule' => $rule_name));
    }
    else {
      $warning = _t('File: !warning [@review_@rule]', array('!warning' => $warning, '@review' => $review_name, '@rule' => $rule_name));
    }
    if ($line) {
      $warning .= '<pre>' . check_plain($line) . '</pre>';
    }
  }

  // Add informative images and classes to the output.
  $class = 'coder-warning';
  if ($severity_name) {
    $class .= " coder-$severity_name";
  }
  $path = _coder_review_path() . '/..';
  $title = _t('severity: @severity', array('@severity' => $severity_name));
  $img = theme('image', array(
    'path' => $path . "/images/$severity_name.png",
    'alt' => $title,
    'title' => $title,
    'attributes' => array('align' => 'right', 'class' => 'coder'),
    'getsize' => FALSE,
  ));
  $avail_reviews = _coder_review_reviews();
  if (isset($avail_reviews[$review_name]['#image'])) {
    $title = _t('review: @review_@rule', array('@review' => $review_name, '@rule' => $rule_name));
    $review_image = $avail_reviews[$review_name]['#image'];
    $img .= theme('image', array(
      'path' => (substr($review_image, 0, 7) == 'images/' ? "$path/" : '') . $review_image,
      'alt' => $title,
      'title' => $title,
      'attributes' => array('align' => 'right', 'class' => 'coder-review'),
      'getsize' => FALSE,
    ));
  }
  if (!empty($description)) {
    $img .= theme('image', array(
      'path' => $path . '/images/more.png',
      'alt' => t('click to read more'),
      'atributes' => array('align' => 'right', 'class' => 'coder-more'),
      'getsize' => FALSE,
    ));
    $warning .= '<div class="coder-description">' . t('Explanation: @description', array('@description' => $description)) . '</div>';
  }
  return '<div class="' . $class . '">' . $img . $warning . '</div>';
}

/**
 * Parses and reads source files into a format for easier review validation.
 *
 * For each source file, the following file lines of code (with trailing
 * newlines) will be added to the Coder arguments array:
 * - #all_array_lines:
 * - #all_lines:
 * - #allphp_array_lines:
 * - #comment_array_lines:
 * - #doublequote_array_lines:
 * - #html_array_lines:
 * - #php_array_lines:
 * - #quote_array_lines:
 *
 * The _array_ variants are multidimensional arrays, the first index for the
 * line number, and the second index for each occurance within the line.
 * #all_lines is a simple array, with each line from the source file as an
 * index.
 *
 * @param array $coder_args
 *   A Coder arguments array, passed by reference.
 *
 * @return int
 *   Integer 1 if success.
 */
function _coder_review_read_and_parse_file(array &$coder_args) {
  // Determine the file extension type.
  // Set all allowed PHP extensions to 'php'.
  $pathinfo = pathinfo($coder_args['#filename']);
  $allowed_extensions = array_merge(
    $coder_args['#php_extensions'],
    $coder_args['#include_extensions'],
    array('module', 'theme')
  );
  $ext = in_array($pathinfo['extension'], $allowed_extensions) ? 'php' : $pathinfo['extension'];

  /* The use of variables with 'php' in them ($in_php, $in_all_php, $php_lines,
   * etc.) is misleading. All references to such should be renamed 'code'
   * because we also are using this engine to read 'js' files.
   */

  // Get the path to the module file.
  $filepath = realpath($coder_args['#filename']);
  if (!empty($coder_args['#patch']) || !empty($coder_args['#test']) || file_exists($filepath)) {
    $in_php = ($ext == 'js') ? 1 : 0;
    $in_allphp = $in_php;
    $in_comment = 0;

    if (!empty($coder_args['#patch'])) {
      $content = $coder_args['#patch'];
      if (preg_match('/^\s*\*/', $content)) {
        $in_comment = '*';
      }
      else {
        $content = preg_replace('/^(function\s.*?(\r\n|\n)+)(\s*\*)/', '${1}/*', $content);
        $in_php = 1;
        $in_allphp = 1;
      }
    }
    elseif (!empty($coder_args['#test'])) {
      $content = $coder_args['#test'];
      $in_php = 1;
      $in_allphp = 1;
    }
    else {
      $content = file_get_contents($filepath);
    }
    $content .= "\n";
    $content_length = strlen($content);

    $in_comment = 0;
    $in_quote_html = 0;
    $in_backslash = 0;
    $in_quote = 0;
    $in_heredoc = 0;
    $in_heredoc_length = 0;
    $in_heredoc_html = '';
    $beginning_of_line = 0;
    $this_all_lines = '';
    $this_php_lines = '';
    $this_allphp_lines = '';
    $this_html_lines = '';
    $this_quote_lines = array('');
    $this_quote_index = -1;
    $this_quote_sep = FALSE;
    $this_doublequote_lines = array('');
    $this_doublequote_index = -1;
    $this_comment_lines = '';

    // Parse the file:
    // - Strip comments,
    // - Strip quote content,
    // - Strip stuff not in php,
    // - Break into lines.
    $lineno = 1;
    for ($pos = 0; $pos < $content_length; ++$pos) {
      // Get the current character.
      $char = $content[$pos];
      if ($char == "\n") {
        // End C++ style comments on newline.
        if ($in_comment === '/' || $in_comment === '#') {
          $in_comment = 0;
        }

        // Assume that html inside quotes doesn't span newlines.
        $in_quote_html = 0;

        // Remove coder's simpletests assertions as they validly contain bad
        // code, for testing the review rules.
        if (preg_match('/assertCoderReview(Fail|Pass)/', $this_all_lines)) {
          ++$lineno;
          $this_all_lines = '';
          $this_php_lines = '';
          $this_allphp_lines = '';
          $this_html_lines = '';
          $this_comment_lines = '';
          $this_quote_lines = array('');
          continue;
        }

        // Remove blank lines now, so we avoid processing them over-and-over.
        if ($this_all_lines != '') {
          if (trim($this_all_lines, "\r\n") != '') {
            $all_lines[$lineno] = array($this_all_lines);
            $full_lines[$lineno] = $this_all_lines;
          }
          if (trim($this_php_lines, "\r\n") != '') {
            $php_lines[$lineno] = array($this_php_lines);
          }
          if (trim($this_allphp_lines, "\r\n") != '') {
            $allphp_lines[$lineno] = array($this_allphp_lines);
          }
          if (trim($this_html_lines, "\r\n") != '') {
            $html_lines[$lineno] = array($this_html_lines);
          }
          $quotes = array();
          foreach ($this_quote_lines as $quote_line) {
            if (trim($quote_line, "\r\n") != '') {
              $quotes[] = $quote_line;
            }
          }
          if ($quotes) {
            $quote_lines[$lineno] = $quotes;
          }
          $quotes = array();
          foreach ($this_doublequote_lines as $quote_line) {
            if (trim($quote_line, "\r\n") != '') {
              $quotes[] = $quote_line;
            }
          }
          if ($quotes) {
            $doublequote_lines[$lineno] = $quotes;
          }
          if (trim($this_comment_lines, "\r\n") != '') {
            $comment_lines[$lineno] = array($this_comment_lines);
          }
        }

        // Save this line and start a new line.
        ++$lineno;
        $this_all_lines = '';
        $this_php_lines = '';
        $this_allphp_lines = '';
        $this_html_lines = '';
        $this_quote_lines = array('');
        $this_doublequote_lines = array('');
        $this_quote_index = -1;
        $this_quote_sep = FALSE;
        $this_doublequote_index = -1;
        $this_comment_lines = '';
        $beginning_of_line = 1;
        continue;
      }
      if ($this_all_lines != '') {
        $beginning_of_line = 0;
      }
      $this_all_lines .= $char;

      if ($in_php || $in_allphp) {
        // When in a quoted string, look for the trailing quote; strip the
        // characters in the string and replace with '' or "".
        if ($in_quote) {
          if ($in_backslash) {
            $in_backslash = 0;
          }
          elseif ($char == '\\') {
            $in_backslash = 1;
          }
          elseif ($char == $in_quote && !$in_backslash) {
            $in_quote = 0;
          }
          elseif ($char == '<') {
            $in_quote_html = '>';
          }
          if ($in_quote) {
            if ($this_quote_index == -1) {
              $this_quote_index = 0;
            }
            $this_quote_lines[$this_quote_index] .= $char;
            if ($in_quote == '"') {
              if ($this_doublequote_index == -1) {
                $this_doublequote_index = 0;
              }
              $this_doublequote_lines[$this_doublequote_index] .= $char;
            }
            if ($in_quote_html) {
              $this_html_lines .= $char;
            }
          }
          if ($char == $in_quote_html) {
            $in_quote_html = 0;
          }
          $this_allphp_lines .= $char;
          // @note: Trailing char output with starting one.
          unset($char);
        }

        elseif ($in_heredoc) {
          // @note: drupal_substr does not properly handle multi-byte characters in this string.
          // @todo: check other places where the drupal_ string functions fail.
          if ($beginning_of_line && $char == $in_heredoc[0] && substr($content, $pos, $in_heredoc_length) == $in_heredoc) {
            $this_all_lines .= _substr($content, $pos + 1, $in_heredoc_length - 1);
            $in_heredoc = 0;
            $pos += $in_heredoc_length;
          }
          elseif ($char == '<') {
            $in_heredoc_html = '>';
          }
          if ($in_heredoc && $in_heredoc_html) {
            $this_html_lines .= $char;
          }
          if ($in_heredoc_html && $char == $in_heredoc_html) {
            $in_heredoc_html = '';
          }
          unset($char);
        }

        // Look for the ending php tag.
        elseif ($ext == 'php' && $char == '?' && $content[$pos + 1] == '>' && $in_comment !== '*') {
          unset($char);
          $in_php = 0;
          $in_allphp = 0;
          $this_all_lines .= '>';
          ++$pos;
        }

        // When in a comment, look for the trailing comment.
        elseif ($in_comment) {
          $this_comment_lines .= $char;
          if ($in_comment == '*' && $char == '*' && $content[$pos + 1] == '/') {
            $in_comment = 0;
            $this_all_lines .= '/';
            $this_comment_lines .= '/';
            ++$pos;
          }
          // Do not add comments to php output.
          unset($char);
        }

        else {
          switch ($char) {
            case ',':
            case ')':
            case '(':
            // For 'foo' => 'bar' type syntax.
            case '>':
            case ':':
              // Look for separators which force a new quote string.
              if ($this_quote_index < 0 || !empty($this_quote_lines[$this_quote_index])) {
                $this_quote_sep = TRUE;
              }
              break;

            case '\'':
            case '"':
              if ($content[$pos - 1] != '\\') {
                $this_php_lines .= $char;
                $in_quote = $char;
                if ($this_quote_sep) {
                  $this_quote_lines[++$this_quote_index] = '';
                  if ($char == '"') {
                    $this_doublequote_lines[++$this_doublequote_index] = '';
                  }
                }
                $this_quote_sep = FALSE;
              }
              break;

            case '#':
              $this_comment_lines .= $char;
              $in_comment = $char;
              unset($char);
              break;

            case '/':
              $next_char = $content[$pos + 1];
              if ($next_char == '/' || $next_char == '*') {
                unset($char);
                $in_comment = $next_char;
                $this_all_lines .= $next_char;
                $this_comment_lines .= '/' . $next_char;
                ++$pos;
              }
              break;

            case '<':
              if ($content[$pos + 1] == '<' && $content[$pos + 2] == '<') {
                unset($char);
                $this_all_lines .= '<<';

                // Get the heredoc word.
                // Read until the end-of-line.
                $heredoc = '';
                for ($pos += 3; $pos < $content_length; ++$pos) {
                  $char = $content[$pos];
                  if ($char == "\n") {
                    $pos--;
                    if (preg_match('/^\s*(\w+)/', $heredoc, $match)) {
                      $in_heredoc = $match[1];
                      $in_heredoc_length = _strlen($in_heredoc);
                    }
                    break;
                  }
                  $this_all_lines .= $char;
                  $heredoc .= $char;
                }

                // Replace heredoc's with an empty string.
                $this_php_lines .= '\'\'';
                $this_allphp_lines .= '\'\'';
                unset($char);
              }
              break;
          }
        }
        if (isset($char)) {
          $this_php_lines .= $char;
          $this_allphp_lines .= $char;
        }
      }
      else {
        switch ($char) {
          case '<':
            if ($ext == 'php' && $content[$pos + 1] == '?') {
              if ($content[$pos + 2] == ' ') {
                $in_php = 1;
                $in_allphp = 1;
                $this_all_lines .= '? ';
                $pos += 2;
              }
              elseif (_substr($content, $pos + 2, 3) == 'php') {
                $in_php = 1;
                $in_allphp = 1;
                $this_all_lines .= '?php';
                $pos += 4;
              }
              break;
            }
            // Purposefully fall through.
          default:
            $this_html_lines .= $char;
            break;
        }
      }
    }

    // Add the files lines to the arguments.
    $coder_args['#all_array_lines'] = isset($all_lines) ? $all_lines : array();
    $coder_args['#php_array_lines'] = isset($php_lines) ? $php_lines : array();
    $coder_args['#allphp_array_lines'] = isset($allphp_lines) ? $allphp_lines : array();
    $coder_args['#html_array_lines'] = isset($html_lines) ? $html_lines : array();
    $coder_args['#quote_array_lines'] = isset($quote_lines) ? $quote_lines : array();
    $coder_args['#doublequote_array_lines'] = isset($doublequote_lines) ? $doublequote_lines : array();
    $coder_args['#comment_array_lines'] = isset($comment_lines) ? $comment_lines : array();
    $coder_args['#all_lines'] = isset($full_lines) ? $full_lines : array();
    $coder_args['#raw_contents'] = $content;
    $coder_args['#num_lines'] = isset($full_lines) ? key(array_slice($full_lines, -1, 1, TRUE)) : 0;

    // Given the sanitized PHP lines, determine the class and function for each
    // line.
    $stack = array();
    $class_stack = $class_stack_paren = array();
    $function_stack = $function_stack_paren = array();
    $paren_depth = 0;
    foreach ($coder_args['#php_array_lines'] as $lineno => $line_array) {
      foreach ($line_array as $line) {
        // Check if this line is the beginning of a function definition.
        if (preg_match('/function (\w+)\s*\(/', $line, $match) && !preg_match('/;/', $line)) {
          array_unshift($function_stack, $match[1]);
          array_unshift($function_stack_paren, $paren_depth);
        }

        // Check if this line is the beginning of a class definition.
        if (preg_match('/class (\w+)/', $line, $match) || preg_match('/interface (\w+)/', $line, $match)) {
          array_unshift($class_stack, $match[1]);
          array_unshift($class_stack_paren, $paren_depth);
        }

        // Check if this line changes the parenthesis depth.
        if (preg_match_all('/([{}])/', $line, $match)) {
          foreach ($match[0] as $paren_match) {
            $paren_depth += ($paren_match == '{') ? 1 : -1;
          }

          // If the depth is now less than then current function depth, pop the
          // function from the stack.
          if ($function_stack_paren && $paren_depth <= $function_stack_paren[0]) {
            array_shift($function_stack);
            array_shift($function_stack_paren);
          }

          // If the depth is now less than the current class depth, pop the
          // class from the stack.
          if ($class_stack_paren && $paren_depth <= $class_stack_paren[0]) {
            array_shift($class_stack);
            array_shift($class_stack_paren);
          }
        }

        // Cache the current function and class for each line of each file.
        $stack[$lineno] = array($class_stack ? $class_stack[0] : '', $function_stack ? $function_stack[0] : '');
      }
    }
    $coder_args['#stack'] = $stack;

    // Read the coder warning directives in the comments.
    foreach ($coder_args['#comment_array_lines'] as $lineno => $line_array) {
      foreach ($line_array as $line) {
        $pos = strpos($line, '@ignore ');
        if ($pos !== FALSE && preg_match_all('/([\w:]+)[\s,]*/', _substr($line, $pos + 8), $matches)) {
          foreach ($matches[1] as $ignore) {
            list($rule_name, $scope) = explode(':', "$ignore:1");

            if ($scope == 'file') {
              // Find the end of the file.
              $scope = $coder_args['#num_lines'] - $lineno;
            }
            elseif ($scope == 'class' || $scope == 'function') {
              // What scope are we looking for?
              // #stack is an array($class_name, $function_name).
              $stack_index = $scope == 'class' ? 0 : 1;

              // Find the current scope.
              $current_scope = NULL;
              foreach (array(0, 1) as $current_lineno) {
                if (!empty($stack[$lineno + $current_lineno][$stack_index])) {
                  $current_scope = $stack[$lineno + $current_lineno][$stack_index];
                  break;
                }
              }

              // Find the end of the class or function.
              if ($current_scope) {
                for ($scope = 1; !isset($stack[$lineno + $scope]) || $stack[$lineno + $scope][$stack_index] == $current_scope; ++$scope) {
                  if ($lineno + $scope > $coder_args['#num_lines']) {
                    break;
                  }
                }
              }
            }
            elseif ($scope == 'comment') {
              // Find the next line that is not a comment.
              for ($scope = 0; !empty($comment_lines[$lineno + $scope + 1]); ++$scope) {
              }
            }

            if (is_numeric($scope)) {
              for ($line_offset = 0; $line_offset <= $scope; ++$line_offset) {
                $ignores[$lineno + $line_offset][$rule_name] = $rule_name;
              }
            }
          }
        }
      }
    }
    $coder_args['#ignores'] = isset($ignores) && $coder_args['#settings_ignore'] ? $ignores : array();

    return 1;
  }
}

/**
 * Determines the integer severity magic number for a severity string.
 *
 * @param string $severity_name
 *   The name of severity string, e.g., 'minor', 'normal', or 'critical'.
 * @param int $default_value
 *   (optional) An integer magic number to use if severity string is not
 *   recognized. Defaults to SEVERITY_NORMAL.
 *
 * @return int
 *   An integer magic number, see SEVERITY_* constants.
 */
function _coder_review_severity($severity_name, $default_value = SEVERITY_NORMAL) {
  // @note: Implemented this way in hopes that it is faster than a PHP switch.
  static $severity_names = array();
  if (!$severity_names) {
    $severity_names = array(
      'minor' => SEVERITY_MINOR,
      'normal' => SEVERITY_NORMAL,
      'critical' => SEVERITY_CRITICAL,
    );
  }
  return isset($severity_names[$severity_name]) ? $severity_names[$severity_name] : $default_value;
}

/**
 * Return string severity for a given error.
 *
 * @param array $coder_args
 *   A Coder settings array. See do_coder_reviews() for format information.
 * @param array $review
 *   Review array that contains rule arrays. See hook_reviews() for details.
 * @param array $rule
 *   Rule array that was triggered. See individual entries from hook_reviews().
 *
 * @return string
 *   A string describing the severity of the error.
 *
 * @see do_coder_reviews()
 * @see hook_review()
 */
function _coder_review_severity_name(array $coder_args, array $review, array $rule) {
  // NOTE: Warnings in php includes are suspicious because
  // PHP includes are frequently 3rd party products.
  if (isset($coder_args['#php_minor']) && _substr($coder_args['#filename'], -4) == '.php') {
    return 'minor';
  }

  // Get the severity as defined by the rule.
  if (isset($rule['#severity'])) {
    return $rule['#severity'];
  }

  // If it's not defined in the rule, then it can be defined by the review.
  if (isset($review['#severity'])) {
    return $review['#severity'];
  }

  // Use the default.
  return 'normal';
}

/**
 * Performs a code review for a review array.
 *
 * @param array $coder_args
 *   An array of coder_review settings, which must have been prepared with
 *   _coder_review_read_and_parse_file().  See do_coder_reviews() for more
 *   information on the array format.
 * @param array $review
 *   A review array. See hook_review() for format details.
 *
 * @return array
 *   An array of coder_review results. See do_coder_reviews() return value for
 *   more information on the format.
 *
 * @see do_coder_reviews()
 * @see hook_review()
 * @see _coder_review_read_and_parse_file()
 */
function do_coder_review(array $coder_args, array $review) {
  $results = array('#stats' => array('minor' => 0, 'normal' => 0, 'critical' => 0, 'ignored' => 0));
  $allowed_extensions = array_merge(
    $coder_args['#php_extensions'],
    $coder_args['#include_extensions'],
    array('module', 'theme')
  );
  if (!empty($review['#js'])) {
    $allowed_extensions[] = 'js';
  }
  if ($review['#rules']) {
    // Get the review's severity, used when the rule severity is not defined.
    $default_severity = isset($review['#severity']) ? _coder_review_severity($review['#severity']) : SEVERITY_NORMAL;

    // Get filename of current file.
    $filename = empty($coder_args['#patch']) ? $coder_args['#filename'] : 'coder_review.patch';
    $is_patch = 0;
    // Handle special case filename for patch files, if available.
    if (!empty($coder_args['#patch']) && preg_match('/(.+?):/', $coder_args['#filename'], $matches)) {
      $filename = empty($matches) ? 'coder_review.patch' : $matches[1];
      $is_patch = 1;
    }

    foreach ($review['#rules'] as $rule_name => $rule) {
      $rule += array(
        '#rule_name' => $rule_name,
        '#review_name' => $review['#review_name'],
      );

      // Ignore rules that don't match the file extension.
      $filename_includes = isset($rule['#filename']) ? $rule['#filename'] : (isset($rule['#filename-not']) ? $allowed_extensions : NULL);
      if ($filename_includes) {
        $regex = '/(' . implode('|', $filename_includes) . ')$/i';
        if (!preg_match($regex, $filename, $matches)) {
          continue;
        }
      }

      // Ignore rules that do match the file extension, javascript files are
      // excluded by default.
      $not = isset($rule['#filename-not']) ? $rule['#filename-not'] : (isset($rule['#filename']) ? NULL : $coder_args['#include_extensions']);
      if ($not) {
        $regex = '/(' . implode('|', $not) . ')$/i';
        // Check filename. If a patch, also check the .patch extension.
        if (preg_match($regex, $filename, $matches) || ($is_patch && preg_match($regex, 'coder_review.patch', $matches))) {
          continue;
        }
      }

      // If it's a patch, it can contain any sort of file, so ensure the file
      // being processed is either PHP or one of the supported extensions.
      if ($is_patch) {
        $regex = '/(' . implode('|', $allowed_extensions) . ')$/i';
        if (!preg_match($regex, $filename, $matches)) {
          continue;
        }
      }

      // Perform the review if above the user requested severity.
      $severity = _coder_review_severity(isset($rule['#severity']) ? $rule['#severity'] : '', $default_severity);
      if ($severity >= $coder_args['#severity']) {
        // #source can be an array, a string, or empty.
        $rule_sources = isset($rule['#source']) ? (is_array($rule['#source']) ? $rule['#source'] : array($rule['#source'])) : array('php');
        foreach ($rule_sources as $source) {
          // Permissible values for #source: all, html, comment, allphp or php.
          $source_lines = '#' . $source . '_array_lines';
          $lines = isset($coder_args[$source_lines]) ? $coder_args[$source_lines] : array();
          switch ($rule['#type']) {
            case 'regex':
              do_coder_review_regex($coder_args, $review, $rule, $lines, $results);
              break;

            case 'grep':
              do_coder_review_grep($coder_args, $review, $rule, $lines, $results);
              break;

            case 'grep_invert':
              do_coder_review_grep_invert($coder_args, $review, $rule, $lines, $results);
              break;

            case 'callback':
              do_coder_review_callback($coder_args, $review, $rule, $lines, $results);
              break;

            default:
              _message(_t('Invalid rule type @type', array('@type' => $rule['#type'])), 'error');
              break;
          }
        }
      }
    }
  }
  return $results;
}

/**
 * Performs a 'regex' type of coder_review.
 *
 * This type of do_coder_review_* attempts to locate occurances based on a
 * regular expression string.
 *
 * @param array $coder_args
 *   A Coder settings array, passed by reference. See do_coder_review() for format.
 * @param array $review
 *   Review array the current rule belongs to, used by _coder_review_severity_name().
 * @param array $rule
 *   Rule array being checked.
 * @param array $lines
 *   Pertinent source file lines according to rule's '#source' value.
 * @param array $results
 *   Results array variable to save errors to, passed by reference.
 *
 * @see do_coder_review()
 * @see _coder_review_severity_name()
 */
function do_coder_review_regex(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  if (isset($rule['#value']) && !empty($lines)) {
    $regexflags = isset($rule['#case-sensitive']) ? '' : 'i';
    $regex = '/' . $rule['#value'] . '/' . $regexflags;
    $class_regex = isset($rule['#class']) ? '/' . $rule['#class'] . '/' : '';
    $class_not_regex = isset($rule['#class-not']) ? '/' . $rule['#class-not'] . '/' : '';
    $function_regex = isset($rule['#function']) ? '/' . $rule['#function'] . '/' : '';
    $function_not_regex = isset($rule['#function-not']) ? '/' . $rule['#function-not'] . '/' : '';
    $not_regex = isset($rule['#not']) ? '/' . $rule['#not'] . '/' . $regexflags : '';
    $never_regex = isset($rule['#never']) ? '/' . $rule['#never'] . '/' . $regexflags : '';
    $review_name = $review['#review_name'];

    foreach ($lines as $lineno => $line_array) {
      foreach ($line_array as $line) {
        if (preg_match($regex, $line, $matches)) {
          // Some rules apply only within certain functions and classes.
          list($class_current, $function_current) = isset($coder_args['#stack'][$lineno]) ? $coder_args['#stack'][$lineno] : array('', '');
          if (   ($function_regex && (!$function_current || !preg_match($function_regex, $function_current)))
              || ($function_not_regex && $function_current && preg_match($function_not_regex, $function_current))
              || ($class_regex && (!$class_current || !preg_match($class_regex, $class_current[0])))
              || ($class_not_regex && $class_current && preg_match($class_not_regex, $class_current[0]))
            ) {
            continue;
          }

          // Don't match some regex's.
          if ($not_regex) {
            foreach ($matches as $match) {
              if (preg_match($not_regex, $match)) {
                continue 2;
              }
            }
          }
          if ($never_regex) {
            if (preg_match($never_regex, $coder_args['#all_lines'][$lineno])) {
              continue;
            }
          }

          $line = $coder_args['#all_lines'][$lineno];
          $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
          _coder_review_error($results, $rule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }
  }
}

/**
 * Builds an error message based on the rule that failed and other information.
 *
 * @param array $results
 *   A Results array variable to save errors to, passed by reference.
 * @param array $rule
 *   A Rule array that triggered the error.
 * @param string $severity_name
 *   A severity of error string as detected by _coder_review_severity_name().
 * @param int $lineno
 *   (optional) The line number on which the error was detected. Defaults to
 *   negative one.
 * @param string $line
 *   (optional) The content of the line that triggered the error. Defaults to an
 *   empty string.
 * @param array $ignores
 *   (optional) Any warnings to ignore. Defaults to an empty array.
 *
 * @see _coder_review_severity_name()
 */
function _coder_review_error(array &$results, array $rule, $severity_name, $lineno = -1, $line = '', $ignores = array()) {
  // Note: The use of the $key allows multiple errors on one line. This assumes
  // that no line of source has more than 10000 lines of code and that we have
  // fewer than 10000 errors.
  global $_coder_errno;

  // Skip warnings we've been told to ignore.
  if (_coder_review_ignore($rule, $lineno, $ignores)) {
    ++$results['#stats']['ignored'];
  }
  else {
    $key = ($lineno + 1) * 10000 + ($_coder_errno++);
    $results[$key] = array(
      'rule' => $rule,
      'severity_name' => $severity_name,
      'review_name' => $rule['#review_name'],
      'rule_name' => $rule['#rule_name'],
      'lineno' => $lineno,
      'line' => $line,
    );
    ++$results['#stats'][$severity_name];
  }
}

/**
 * Determines whether a rule should be ignored.
 *
 * @param array $rule
 *   A Rule array that triggered the error.
 * @param int $lineno
 *   The line number on which the error was detected.
 * @param array $ignores
 *   Any warnings to ignore.
 *
 * @return bool
 *   TRUE if the ruleshould be ignored; otherwise, FALSE.
 */
function _coder_review_ignore(array $rule, $lineno, array $ignores) {
  $name = $rule['#review_name'] . '_' . $rule['#rule_name'];
  return isset($ignores[$lineno][$name]);
}

/**
 * Performs a 'grep' type of coder_review.
 *
 * This type of do_coder_review_* searches for the occurance of a string.
 *
 * @param array $coder_args
 *   A Coder settings array, passed by reference. See do_coder_review() for format.
 * @param array $review
 *   Review array the current rule belongs to, used by _coder_review_severity_name().
 * @param array $rule
 *   Rule array being checked.
 * @param array $lines
 *   Pertinent source file lines according to rule's '#source' value.
 * @param array $results
 *   Results array variable to save errors to, passed by reference.
 *
 * @see do_coder_review()
 * @see _coder_review_severity_name()
 */
function do_coder_review_grep(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  if (isset($rule['#value'])) {
    foreach ($lines as $lineno => $line_array) {
      foreach ($line_array as $line) {
        if (_coder_review_search_string($line, $rule)) {
          $line = $coder_args['#all_lines'][$lineno];
          $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
          _coder_review_error($results, $rule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }
  }
}

/**
 * Performs a 'grep_invert' type of coder_review.
 *
 * This type of do_coder_review_* searches for the absence of the occurance of a
 * string.
 *
 * @param array $coder_args
 *   A Coder settings array, passed by reference. See do_coder_review() for format.
 * @param array $review
 *   Review array the current rule belongs to, used by _coder_review_severity_name().
 * @param array $rule
 *   Rule array being checked.
 * @param array $lines
 *   Pertinent source file lines according to rule's '#source' value.
 * @param array $results
 *   Results array variable to save errors to, passed by reference.
 *
 * @see do_coder_review()
 * @see _coder_review_severity_name()
 */
function do_coder_review_grep_invert(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  if (isset($rule['#value'])) {
    foreach ($lines as $lineno => $line_array) {
      foreach ($line_array as $line) {
        if (_coder_review_search_string($line, $rule)) {
          return;
        }
      }
    }
    $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
    _coder_review_error($results, $rule, $severity_name);
  }
}

/**
 * Performs a 'callback' type of coder_review.
 *
 * This type of do_coder_review_* allows for an arbitrary callback function to
 * perform a review.
 *
 * @param array $coder_args
 *   A Coder settings array, passed by reference. See do_coder_review() for format.
 * @param array $review
 *   Review array the current rule belongs to, used by _coder_review_severity_name().
 * @param array $rule
 *   Rule array being checked.
 * @param array $lines
 *   Pertinent source file lines according to rule's '#source' value.
 * @param array $results
 *   Results array variable to save errors to, passed by reference.
 *
 * @see do_coder_review()
 * @see _coder_review_severity_name()
 */
function do_coder_review_callback(array &$coder_args, array $review, array $rule, array $lines, array &$results) {
  $function = $rule['#value'];
  if ($function) {
    if (function_exists($function)) {
      call_user_func_array($function, array(&$coder_args, $review, $rule, $lines, &$results));
    }
    else {
      static $bad;
      if (!isset($bad[$function])) {
        $bad[$function] = 1;
        _message(_t('Invalid rule callback @function', array('@function' => $function)), 'error');
      }
    }
  }
}

/**
 * Searches for the occurance of a string in a line of text.
 *
 * This function uses the fastest available PHP function for searching.
 *
 * @param string $line
 *   Haystack.
 * @param array $rule
 *   A Rule array to process.
 *
 * @return
 *   TRUE if needle is in haystack; otherwise, FALSE.
 */
function _coder_review_search_string($line, $rule) {
  // Case-sensitive search with strpos() (supported everywhere).
  if (isset($rule['#case-sensitive'])) {
    return strpos($line, $rule['#value']) !== FALSE;
  }

  // Case-insensitive search with stripos().
  if (!isset($rule['#case-sensitive'])) {
    return stripos($line, $rule['#value']) !== FALSE;
  }

  // Case-insensitive search.
  $regex = '/' . preg_quote($rule['#value']) . '/i';
  return preg_match($regex, $line);
}

/**
 * Returns an active settings array for coder_review.
 *
 * The name is a misnomer, but is a largely correct characterization
 * for most of Coder's settings as the variables usually do not exist.
 *
 * @param string $args
 *   (optional) A string settings argument, can be 'settings', 'active', 'core',
 *   'all' and 'default'. Defaults to 'default'.
 *
 * @return
 *   Associative array of settings in the form of setting name => setting value.
 */
function _coder_review_get_default_settings($arg = 'default') {
  $settings = array(
    'coder_includes' => 0,
    'coder_includes_exclusions' => '',
    'coder_active_modules' => 0,
    'coder_core' => 0,
    'coder_all' => 0,
    'coder_contrib' => 0,
    'coder_files' => 0,
    'coder_file_list' => '',
    'coder_patches' => 0,
    'coder_modules' => array(),
    'coder_themes' => array(),
    'coder_ignore' => 1,
  );
  $settings['coder_reviews'] = _variable_get('coder_reviews', _coder_review_default_reviews());
  $settings['coder_severity'] = _variable_get('coder_severity', SEVERITY_NORMAL);

  // Determine any options based on the passed in URL.
  switch ($arg) {
    case 'settings':
      $settings['coder_includes'] = 1;
      break;

    case 'active':
      $settings['coder_active_modules'] = 1;
      break;

    case 'core':
      $settings['coder_core'] = 1;
      $settings['coder_includes'] = 1;
      break;

    case 'all':
      $settings['coder_core'] = 1;
      $settings['coder_includes'] = 1;
      $settings['coder_all'] = 1;
      break;

    case 'contrib':
      $settings['coder_includes'] = 1;
      $settings['coder_contrib'] = 1;
      break;

    case 'files':
      $settings['coder_files'] = 1;
      break;

    case 'patches':
      $settings['coder_patches'] = 1;
      break;

    case 'default':
      $settings['coder_active_modules'] = _variable_get('coder_active_modules', 1);
      $settings['coder_core'] = _variable_get('coder_core', 0);
      $settings['coder_includes'] = _variable_get('coder_includes', 0);
      $settings['coder_includes_exclusions'] = _variable_get('coder_includes_exclusions', '');
      $settings['coder_modules'] = _variable_get('coder_modules', array());
      $settings['coder_themes'] = _variable_get('coder_themes', array());
      break;

    default:
      $settings['coder_includes'] = 1;
      $settings['coder_includes_exclusions'] = _variable_get('coder_includes_exclusions', '');
      // TODO: Does this need to go into coder_review_themes sometimes?
      $settings['coder_modules'] = array($arg => $arg);
      break;
  }
  return $settings;
}

/**
 * Determines if a module is part of Drupal's core group.
 *
 * @param object $system
 *   ???
 *
 * @return bool
 *   TRUE if a module is part of Drupal's core group; otherwise, FALSE.
 */
function _coder_review_is_drupal_core($system) {
  $info_file = dirname(realpath($system->filename)) . '/' . $system->name . '.info';
  $info = drupal_parse_info_file($info_file);
  return !empty($info['package']) && strtolower($info['package']) == 'core';
}

/**
 * Creates a formatted warning message from a Rule array definition.
 *
 * @param array $rule
 *   A Rule definition array.
 *
 * @return string
 *   A formatted warning message.
 *   @todo Is this an HTML string? Is it sanitized? Needs better explanation.
 */
function _coder_review_warning(array $rule) {
  /* @todo: add version check so we handle tranlations right for older rules definitions.
   * ... or should we just ignore them?
   * This will require passing the review to this function.
   */

  // Call warning callbacks.
  if (isset($rule['#warning_callback'])) {
    // This rule definition is deprecated.
    if (is_callable($rule['#warning_callback']) || function_exists($rule['#warning_callback'])) {
      return $rule['#warning_callback']();
    }
  }
  elseif (isset($rule['#warning'])) {
    // Return array warnings as-is.
    // They get translated in theme_coder_review_warning().
    if (is_array($rule['#warning'])) {
      return $rule['#warning'];
    }

    // Warnings callback functions can now be stored as the #warning element.
    if (is_callable($rule['#warning']) || function_exists($rule['#warning'])) {
      return $rule['#warning']();
    }

    // Translate the warning message and return it.
    return _t($rule['#warning']);
  }

  // No valid warning definition: return a warning about the warning.
  return _t('Unknown warning');
}

/**
 * Define a wrapper t() function that works in Drush cli.
 *
 * @param string $string
 * @param array $args
 * @param array $options
 *
 * @return string
 *
 * @see t()
 */
function _t($string, $args = array(), $options = array()) {
  return _drush() ? dt($string, $args) : t($string, $args, $options);
}

/**
 * Define a wrapper l() function that works in Drush cli.
 *
 * @param string $text
 * @param string $path
 * @param array $options
 *
 * @return string
 *
 * @see l()
 */
function _l($text, $path, $options = array()) {
  return _drush() ? "$text $path" : l($text, $path, $options);
}

/**
 * Define a wrapper variable_get() function that works in Drush cli.
 *
 * @param string $variable
 *   The name of the variable.
 * @param mixed $default
 *   The default value for the variable.
 *
 * @return mixed
 *   The value of the variable.
 *
 * @see variable_get()
 */
function _variable_get($variable, $default = NULL) {
  return function_exists('variable_get') ? variable_get($variable, $default) : $default;
}

/**
 * Return the valid PHP extensions.
 */
function _coder_review_php_ext() {
  return _variable_get('coder_review_php_ext', array('inc', 'php', 'install', 'test'));
}

/**
 * Determines if currently running with the Drush client.
 *
 * @return bool
 *   TRUE if currently running with the Drush client; otherwise, FALSE.
 */
function _drush() {
  return function_exists('drush_verify_cli') && drush_verify_cli();
}

/**
 * Creates a link to the Drupal node.
 *
 * @param int $nid
 *   The Drupal Node ID to link to.
 * @param string $anchor
 *   (optional) An anchor tag. Defaults to an empty string.
 *
 * @return string
 *   An HTML link to the drupal.org node.
 *   Except when called from Drush, then it is a plain text link.
 */
function _drupalnode($nid, $anchor = '') {
  $link = "http://drupal.org/node/$nid";
  if ($anchor) {
    $link .= "#$anchor";
  }
  return $link;
}

/**
 * Creates a link to the Drupal API docs.
 *
 * @param string $function
 *   The name of a function to link to.
 * @param string $version
 *   (optional) The Drupal version to link to.
 *
 * @return string
 *   An HTML link to the Drupal API documents for the function and version.
 *   Except when called from Drush, then it is a plain text link.
 */
function _drupalapi($function, $version = '') {
  return _l($function, "http://api.drupal.org/api/function/$function/$version");
}

/**
 * Creates a link to the PHP API docs.
 *
 * @param string $function
 *   The PHP function documentation to link to.
 *
 * @return string
 *   An HTML link to the PHP documents for the function.
 *   Except when called from Drush, then it is a plain text link.
 */
function _phpapi($function) {
  return _l($function, "http://php.net/$function");
}

/**
 * Returns the file system path to the coder_review module.
 *
 * @return string
 *   The file system path to the coder_review module.
 */
function _coder_review_file_path() {
  return dirname(__FILE__);
}

/**
 * Returns the URL path to the coder_review module.
 *
 * @return string
 *   The URL path to the coder_review module.
 */
function _coder_review_path() {
  return drupal_get_path('module', 'coder_review');
}

/**
 * Retrieves data from the cache.
 *
 * @param string $cid
 *   ???
 * @param string $bin
 *   (optional) The name of the bin in which to store the cached data.
 *
 * @return ???
 *   ???
 *
 * @see cache_get()
 */
function _cache_get($cid, $bin = 'default') {
  return function_exists('cache_get') ? cache_get($cid, $bin) : array();
}

/**
 * Stores data in the cache.
 *
 * @param string $cid
 *   ???
 * @param mixed $data
 *   ???
 * @param string $bin
 *   (optional) The name of the bin in which to store the cached data.
 *
 * @return ???
 *   ???
 *
 * @see cache_set()
 */
function _cache_set($cid, $data, $bin = 'default') {
  return function_exists('cache_set') ? cache_set($cid, $data, $bin) : array();
}

/**
 * Returns a sub string.
 *
 * @param string $text
 *   ???
 * @param int $start
 *   ???
 * @param int $length
 *   ???
 *
 * @return ???
 *   ???
 *
 * @see drupal_substr()
 */
function _substr($text, $start, $length = NULL) {
  return function_exists('drupal_substr') ? drupal_substr($text, $start, $length) : substr($text, $start, $length);
}

/**
 * Returns the length of a string.
 *
 * @param string $text
 *   ???
 *
 * @return int
 *   ???
 *
 * @see drupal_strlen()
 */
function _strlen($text) {
  return function_exists('drupal_strlen') ? drupal_strlen($text) : strlen($text);
}

/**
 * Returns a string converted to all UPPERCASE letters.
 *
 * @param string $text
 *   ???
 *
 * @return string
 *   ???
 *
 * @see drupal_strtoupper()
 */
function _strtoupper($text) {
  return function_exists('drupal_strtoupper') ? drupal_strtoupper($text) : strtoupper($text);
}

/**
 * Returns a string converted to all lowercase letters.
 *
 * @param string $text
 *   ???
 *
 * @return string
 *   ???
 *
 * @see drupal_strtolower()
 */
function _strtolower($text) {
  return function_exists('drupal_strtolower') ? drupal_strtolower($text) : strtolower($text);
}

/**
 * Returns all available file paths matching the regular expression.
 *
 * @param ??? $path
 *   ???
 * @param ??? $regex
 *   ???
 * @param bool $recurse
 *   (optional) ??? Defaults to TRUE.
 *
 * @return array
 *   ???
 */
function _file_list($path, $regex, $recurse = TRUE) {
  $files = array();
  foreach (scandir($path) as $file) {
    if ($file != '.' && $file != '..' && is_dir("$path/$file")) {
      if ($recurse) {
        $files += _file_list("$path/$file", $regex);
      }
    }
    elseif (preg_match($regex, $file)) {
      $files["$path/$file"] = "$path/$file";
    }
  }
  return $files;
}

/**
 * Displays and retrieves messages.
 *
 * @param ??? $message
 *   (optional) ??? Defaults to NULL.
 * @param string $type
 *   (optional) ??? Defaults to 'status'.
 *
 * @return array
 *   ???
 */
function _message($message = NULL, $type = 'status') {
  if (function_exists('drupal_set_message')) {
    // @ignore security_dsm
    drupal_set_message($message);
  }

  static $messages = array();
  if ($message) {
    $messages[$type][] = $message;
  }
  return $messages;
}
