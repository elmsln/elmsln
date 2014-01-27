<?php

/**
 * @file
 * Coder format helper functions.
 */

/**
 * Recursively process .module and .inc files in directory with coder_format_file().
 *
 * @param $directory
 *   Path to a directory to process recursively.
 * @param $undo
 *   Boolean whether or not to undo batch replacements.
 */
function coder_format_recursive($directory, $undo = FALSE) {
  // Convert Windows paths (only cosmetical).
  $directory = str_replace('\\', '/', $directory);

  // Check if directory exists.
  if (!is_dir($directory)) {
    drupal_set_message(t('%directory not found.', array('%directory' => $directory)), 'error');
    return FALSE;
  }

  // Fetch files to process.
  $mask   = '\.php$|\.module$|\.inc$|\.install|\.profile$';
  $nomask = array('.', '..', 'CVS', '.svn', '.git');
  if (function_exists('drush_scan_directory')) {
    $files = drush_scan_directory($directory, '/' . $mask . '/', $nomask, 0, TRUE);
  }
  else {
    $files = file_scan_directory($directory, $mask, $nomask, 0, TRUE);
  }
  foreach ($files as $file) {
    coder_format_file($file->filename, $undo);
  }
}

/**
 * Reads, backups, processes and writes the source code from and to a file.
 *
 * @param $filename
 *   Path to a file to process or restore. Pass original filename to restore an
 *   already processed file.
 * @param $undo
 *   Whether to restore a processed file. Always restores the last backup.
 *
 * @return
 *   TRUE on success.
 */
function coder_format_file($filename, $undo = FALSE) {
  // Restore a processed file.
  if ($undo) {
    // Do nothing if no backup file exists at all.
    if (!file_exists($filename . '.coder.orig')) {
      return;
    }
    // Save original filename.
    $original = $filename;
    // Retrieve the file's basename.
    $basename = basename($filename);
    // Find all backups.
    $dirname = dirname($filename);
    $mask  = '^' . preg_quote($basename, '/') . '(\.coder\.orig)+$';
    $nomask = array('.', '..', 'CVS', '.svn', '.git');
    if (function_exists('drush_scan_directory')) {
      $backups = drush_scan_directory($dirname, '/' . $mask . '/', $nomask, 0, FALSE);
    }
    else {
      $backups = file_scan_directory($dirname, $mask, $nomask, 0, FALSE);
    }
    // Find the latest backup to restore.
    ksort($backups);
    $latest = array_pop($backups);
    // Restore latest backup.
    if (unlink($original) && rename($latest->filename, $original)) {
      drupal_set_message(t('%file restored.', array('%file' => $original)));
      return TRUE;
    }
    else {
      drupal_set_message(t('%file could not be restored.', array('%file' => $original)), 'error');
      return FALSE;
    }
  }

  // Backup original file.
  // file_copy() replaces source filepath with target filepath.
  $sourcefile = $filename;
  $targetfile = $filename . '.coder.orig';
  $status = file_exists($filename);
  $status = $status && copy($filename, $targetfile);
  $status = $status && file_exists($targetfile);
  if (!$status) {
    drupal_set_message(t('%file could not be backup.', array('%file' => $filename)), 'error');
    return FALSE;
  }

  // Read source code from source file.
  $fd = fopen($sourcefile, 'r');
  $code = fread($fd, filesize($sourcefile));
  fclose($fd);

  if ($code !== FALSE) {
    $code = coder_format_string_all($code);

    if ($code !== FALSE) {
      // Write formatted source code to target file.
      $fd = fopen($sourcefile, 'w');
      $status = fwrite($fd, $code);
      fclose($fd);

      drupal_set_message(t('%file processed.', array('%file' => $sourcefile)));
      return $status;
    }
    else {
      drupal_set_message(t('An error occurred while processing %file.', array('%file' => $sourcefile)), 'error');
      return FALSE;
    }
  }
  else {
    drupal_set_message(t('%file could not be opened.', array('%file' => $sourcefile)), 'error');
    return FALSE;
  }
}

/**
 * Formats source code according to Drupal conventions, also using
 * post and pre-processors.
 *
 * @param
 *   $code Code to process.
 */
function coder_format_string_all($code) {
  // Preprocess source code.
  $code = coder_exec_processors($code, 'coder_preprocessor');

  // Process source code.
  $code = coder_format_string($code);

  // Postprocess source code.
  $code = coder_exec_processors($code, 'coder_postprocessor');

  // Fix beginning and end of code.
  $code = coder_trim_php($code);

  return $code;
}

/**
 * Format the source code according to Drupal coding style guidelines.
 *
 * This function uses PHP's tokenizer functions.
 * @see http://www.php.net/manual/en/ref.tokenizer.php
 *
 * To achieve the desired coding style, we have to take some special cases
 * into account. These are:
 *
 * Indent-related:
 *   $_coder_indent int Indent level
 *      The number of indents for the next line. This is
 *      - increased after {, : (after case and default).
 *      - decreased after }, break, case and default (after a previous case).
 *   $in_case bool
 *      Is true after case and default. Is false after break and return, if
 *      $braces_in_case is not greater than 0.
 *   $switches int Switch level
 *      Nested switches need to have extra indents added to them.
 *   $braces_in_case array Count of braces
 *      The number of currently opened curly braces in a case. This is needed
 *      to support arbitrary function exits inside of a switch control strucure.
 *      This is an array to allow for nested switches.
 *   $parenthesis int Parenthesis level
 *      The number of currently opened parenthesis. This
 *      - prevents line feeds in brackets (f.e. in arguments of for()).
 *      - is the base for formatting of multiline arrays. Note: If the last
 *        ');' is not formatted to the correct indent level then there is no
 *        ',' (comma) behind the last array value.
 *   $in_brace bool
 *      Is true after left curly braces if they are in quotes, an object or
 *      after a dollar sign. Prevents line breaks around such variable
 *      statements.
 *   $in_heredoc bool
 *      Is true after heredoc output method and false after heredoc delimiter.
 *      Prevents line breaks in heredocs.
 *   $first_php_tag bool
 *      Is false after the first PHP tag. Allows inserting a line break after
 *      the first one.
 *   $in_do_while bool
 *      Is true after a do {} statement and set to false in the next while
 *      statement. Prevents a line break in the do {...} while() construct.
 *
 * Whitespace-related:
 *   $in_object bool
 *      Prevents whitespace after ->.
 *      Is true after ->. Is reset to false after the next string or variable.
 *   $in_at bool
 *      Prevents whitespace after @.
 *      Is true after @. Is reset to false after the next string or variable.
 *   $in_quote bool
 *      Prevents
 *      - removal of whitespace in double quotes.
 *      - injection of new line feeds after brackets in double quotes.
 *   $inline_if bool
 *      Controls formatting of ? and : for inline ifs until a ; (semicolon) is
 *      processed.
 *   $in_function_declaration
 *      Prevents whitespace after & for function declarations, e.g.
 *      function &foo(). Is true after function token but before first
 *      parenthesis.
 *   $in_array
 *      Array of parenthesis level to whether or not the structure
 *      is for an array.
 *   $in_multiline
 *      Array of parenthesis level to whether or not the structure
 *      is multiline.
 *
 * Context flags:
 *   These variables give information about what tokens have just been
 *   processed so that operations can change their behavior depending on
 *   the preceding context without having to scan backwards on the fully
 *   formed result. Most of these are ad hoc and have a very specific
 *   purpose in the program. It would probably be a good idea to generalize
 *   this facility.
 *
 *   $after_semicolon
 *      Is the token being processed on the same line as a semicolon? This
 *      allows for the semicolon processor to unconditionally add a newline
 *      while allowing things like inline comments on the same line to
 *      be bubbled up.
 *   $after_case
 *      Is the token being processed on the same line as a case? This
 *      is a specific override for comment movement behavior that places
 *      inline comments after a case before the case declaration.
 *   $after_comment
 *      Is the line being processed preceded by an inline comment?
 *      This is used to preserve newlines after comments.
 *   $after_initial_comment
 *      Is the line being processed preceded by the // $Id
 *      (ending dollar sign omitted) comment? This is a workaround to
 *      prevent the usual double-newline before docblocks for the very
 *      first docblock.
 *   $after_visibility_modifier
 *      Is the token being processed immediately preceded by a
 *      visibility modifier like public/protected/private? This prevents
 *      extra newlines added by T_FUNCTION.
 *   $after_return_in_case
 *      Whether or not the token is after a return statement in a case.
 *      This prevents the extra indent after case statements from being
 *      terminated prematurely for multiline return lines.
 *
 * @param $code
 *      The source code to format.
 *
 * @return
 *      The formatted code or false if it fails.
 */
function coder_format_string($code = '') {
  global $_coder_indent;

  // Indent controls:
  $_coder_indent  = 0;
  $in_case        = FALSE;
  $switches       = 0;
  $parenthesis    = 0;
  $braces_in_case = array();
  $in_brace       = FALSE;
  $in_heredoc     = FALSE;
  $first_php_tag  = TRUE;
  $in_do_while    = FALSE;

  // Whitespace controls:
  $in_object    = FALSE;
  $in_at        = FALSE;
  $in_php       = FALSE;
  $in_quote     = FALSE;
  $inline_if    = FALSE;
  $in_array     = array();
  $in_multiline = array();

  // Context flags:
  $after_semicolon = FALSE;
  $after_case = FALSE;
  $after_comment = FALSE;
  $after_initial_comment = FALSE;
  $after_visibility_modifier = FALSE;
  $after_return_in_case = FALSE;
  $after_php = FALSE;

  // Whether or not a function token was encountered:
  $in_function_declaration = FALSE;

  // The position of the last character of the last non-whitespace
  // non-comment token, e.g. it would be:
  // function foo() { // bar
  //                ^ this character
  $position_last_significant_token = 0;

  $result    = '';
  $lasttoken = array(0);
  $tokens    = token_get_all($code);

  // Mask T_ML_COMMENT (PHP4) as T_COMMENT (PHP5).
  if (!defined('T_ML_COMMENT')) {
    define('T_ML_COMMENT', T_COMMENT);
  }
  // Mask T_DOC_COMMENT (PHP5) as T_ML_COMMENT (PHP4).
  elseif (!defined('T_DOC_COMMENT')) {
    define('T_DOC_COMMENT', T_ML_COMMENT);
  }

  foreach ($tokens as $token) {
    if (is_string($token)) {
      // Simple 1-character token.
      $text = trim($token);
      switch ($text) {
        case '{':
          // Add a space before and behind a curly brace, if we are in inline
          // PHP, e.g. <?php if ($foo) { print $foo }
          if ($after_php) {
            $text = " $text ";
          }
          // Write curly braces at the end of lines followed by a line break if
          // not in quotes (""), object ($foo->{$bar}) or in variables (${foo}).
          // (T_DOLLAR_OPEN_CURLY_BRACES exists but is never assigned.)
          $c = substr(rtrim($result), -1);
          if (!$after_php && !$in_quote && (!$in_variable && !$in_object && $c != '$' || $c == ')')) {
            if ($in_case) {
              ++$braces_in_case[$switches];
              $_coder_indent += $switches - 1;
            }
            ++$_coder_indent;
            $result = rtrim($result) . ' ' . $text;
            coder_br($result);
          }
          else {
            $in_brace = TRUE;
            $result .= $text;
          }
          break;

        case '}':
          if (!$in_quote && !$in_brace && !$in_heredoc) {
            if ($switches) {
              --$braces_in_case[$switches];
            }
            --$_coder_indent;
            if ($braces_in_case[$switches] < 0 && $in_case) {
              // Decrease indent if last case in a switch is not terminated.
              --$_coder_indent;
              $in_case = FALSE;
            }
            if ($braces_in_case[$switches] < 0) {
              $braces_in_case[$switches] = 0;
              $switches--;
            }
            if ($switches > 0) {
              $in_case = TRUE;
            }

            if (!$after_php) {
              $result = rtrim($result);
              if (substr($result, -1) != '{') {
                // Avoid line break in empty curly braces.
                coder_br($result);
              }
              $result .= $text;
              coder_br($result);
            }
            else {
              // Add a space before a curly brace, if we are in inline PHP, e.g.
              // <?php if ($foo) { print $foo }
              $result = rtrim($result, ' ');
              if (substr($result, -1) !== "\n") {
                $result .= ' ';
              }
              $result .= $text;
            }
          }
          else {
            $in_brace = FALSE;
            $result .= $text;
          }
          break;

        case ';':
          $result = rtrim($result) . $text;
          // Check if we had deferred reduction of indent because we were in
          // a case statement. Now we can decrease the indent.
          if ($after_return_in_case) {
            --$_coder_indent;
            $after_return_in_case = FALSE;
          }
          if (!$parenthesis && !$in_heredoc && !$after_php) {
            coder_br($result);
            $after_semicolon = TRUE;
          }
          else {
            $result .= ' ';
          }
          if ($inline_if) {
            $inline_if = FALSE;
          }
          break;

        case '?':
          $inline_if = TRUE;
          $result .= ' ' . $text . ' ';
          break;

        case ':':
          if ($inline_if) {
            $result .= ' ' . $text . ' ';
          }
          elseif ($after_php) {
            $result .= $text;
          }
          else {
            if ($in_case) {
              ++$_coder_indent;
            }
            $result = rtrim($result) . $text;
            coder_br($result);
          }
          break;

        case '(':
          $result .= $text;
          ++$parenthesis;
          // Not multiline until proven so by whitespace.
          $in_multiline[$parenthesis] = FALSE;
          // If the $in_array flag for this parenthesis level was not
          // set previously, set it to FALSE.
          if (!isset($in_array[$parenthesis])) {
            $in_array[$parenthesis] = FALSE;
          }
          // Terminate function declaration, as a parenthesis indicates
          // the beginning of the arguments. This will catch all other
          // instances of parentheses, but in this case it's not a problem.
          $in_function_declaration = FALSE;
          break;

        case ')':
          if ($in_array[$parenthesis] && $in_multiline[$parenthesis]) {
            // Check if a comma insertion is necessary:
            $c = $position_last_significant_token;
            if ($result[$c] !== ',') {
              // We need to add a comma at $c:
              $result = substr($result, 0, $c + 1) . ',' . substr($result, $c + 1);
            }
          }
          if (!$in_quote && !$in_heredoc && (substr(rtrim($result), -1) == ',' || $in_multiline[$parenthesis])) {
            // Fix indent of right parenthesis in multiline structures by
            // increasing indent for each parenthesis and decreasing one level.
            $result = rtrim($result);
            coder_br($result, $parenthesis - 1);
            $result .= $text;
          }
          else {
            $result .= $text;
          }
          if ($parenthesis) {
            // Current parenthesis level is not an array anymore.
            $in_array[$parenthesis] = FALSE;
            --$parenthesis;
          }
          break;

        case '@':
          $in_at = TRUE;
          $result .= $text;
          break;

        case ',':
          $result .= $text . ' ';
          break;

        case '.':
          // Starting from 7.x, string concatenations follow PEAR's standard.
          $result = rtrim($result) . ' ' . $text . ' ';
          break;

        case '=':
        case '<':
        case '>':
        case '+':
        case '*':
        case '/':
        case '|':
        case '^':
        case '%':
          $result = rtrim($result) . ' ' . $text . ' ';
          break;

        case '&':
          if (substr(rtrim($result), -1) == '=' || substr(rtrim($result), -1) == '(' || substr(rtrim($result), -1) == ',') {
            $result .= $text;
          }
          else {
            $result = rtrim($result) . ' ' . $text;
            // Ampersands used to declare reference return value for
            // functions should not have trailing space.
            if (!$in_function_declaration) {
              $result .= ' ';
            }
          }
          break;

        case '-':
          $result = rtrim($result);
          // Do not add a space before negative numbers or variables.
          $c = substr($result, -1);
          // Do not add a space between closing parenthesis and negative arithmetic operators.
          if ($c == '(') {
            $result .= ltrim($text);
          }
          // Add a space in front of the following chars, but not after them.
          elseif ($c == '>' || $c == '=' || $c == ',' || $c == ':' || $c == '?') {
            $result .= ' ' . $text;
          }
          // Default arithmetic operator behavior.
          else {
            $result .= ' ' . $text . ' ';
          }
          break;

        case '"':
          // Toggle quote if the char is not escaped.
          if (rtrim($result) != "\\") {
            $in_quote = $in_quote ? FALSE : TRUE;
          }
          $result .= $text;
          break;

        default:
          $result .= $text;
          break;
      }

      // All text possibilities are significant:
      $position_last_significant_token = strlen(rtrim($result)) - 1;

      // Because they are all significant, we cannot possibly be after
      // a comment now.
      $after_comment = FALSE;
      $after_initial_comment = FALSE;

      // TODO: Make resetting context flags easier to do.
    }
    else {
      // If we get here, then we have found not a single char, but a token.
      // See <http://www.php.net/manual/en/tokens.php> for a reference.

      // Fetch token array.
      list($id, $text) = $token;

      // Debugging:
      /*
      if ($lasttoken[0] == T_WHITESPACE) {
        $result .= token_name($id);
      }
      */


      switch ($id) {
        case T_ARRAY:
          // Write array in lowercase.
          $result .= strtolower(trim($text));
          // Mark the next parenthesis level (we haven't consumed that token
          // yet) as an array.
          $in_array[$parenthesis + 1] = TRUE;
          break;

        case T_OPEN_TAG:
        case T_OPEN_TAG_WITH_ECHO:
          $in_php = TRUE;
          // Add a line break between two PHP tags.
          if (substr(rtrim($result), -2) == '?>' && !$after_php) {
            coder_br($result);
          }
          $after_php = TRUE;
          $nl = substr_count($text, "\n");
          $result .= trim($text);
          if ($first_php_tag) {
            coder_br($result);
            $first_php_tag = FALSE;
          }
          else {
            if ($nl) {
              coder_br($result, $parenthesis);
            }
            else {
              $result .= ' ';
            }
          }
          break;

        case T_CLOSE_TAG:
          $in_php = FALSE;
          if ($after_php) {
            $result = rtrim($result, ' ') . ' ';
            $text = ltrim($text, ' ');
          }
          // Do not alter a closing PHP tag ($text includes trailing white-space)
          // at all. Should allow to apply coder_format on phptemplate files.
          $result .= $text;
          break;

        case T_OBJECT_OPERATOR:
          $in_object = TRUE;
          $result .= trim($text);
          break;

        case T_CONSTANT_ENCAPSED_STRING:
        case T_STRING:
        case T_VARIABLE:
          // Boolean constants (TRUE, FALSE, NULL) are T_STRINGs, but must be
          // written uppercase.
          $text = trim($text);
          if ($text == 'true' || $text == 'false' || $text == 'null') {
            $text = strtoupper($text);
          }
          // No space after object operator ($foo->bar) and error suppression (@function()).
          if ($in_object || $in_at) {
            $result    = rtrim($result) . $text;
            $in_object = FALSE;
            $in_at     = FALSE;
          }
          else {
            // Insert a space after right parenthesis, but not after type casts.
            if (!in_array($lasttoken[0], array(T_ARRAY_CAST, T_BOOL_CAST, T_DOUBLE_CAST, T_INT_CAST, T_OBJECT_CAST, T_STRING_CAST, T_UNSET_CAST))) {
              coder_add_space($result);
            }
            $result .= $text;
          }
          $in_variable = TRUE;
          break;

        case T_CONST:
          // Constants are written uppercase.
          $result = rtrim($result) . strtoupper(trim($text));
          break;

        case T_ENCAPSED_AND_WHITESPACE:
          $result .= $text;
          break;

        case T_WHITESPACE:
          // Avoid duplicate line feeds outside arrays.
          $c = ($parenthesis || $after_comment) ? 0 : 1;

          for ($c, $cc = substr_count($text, "\n"); $c < $cc; ++$c) {
            // Newlines were added; not after semicolon anymore
            coder_br($result, $parenthesis);
          }

          // If there were newlines present inside a parenthesis,
          // turn on multiline mode.
          if ($cc && $parenthesis) {
            $in_multiline[$parenthesis] = TRUE;
          }

          // If there were newlines present, move inline comments above.
          if ($cc) {
            $after_semicolon = FALSE;
            $after_case      = FALSE;
            $after_php       = FALSE;
          }

          $in_variable = FALSE;
          break;

        case T_SWITCH:
          ++$switches;
          // Purposely fall through.
        case T_FOR:
        case T_FOREACH:
        case T_GLOBAL:
        case T_STATIC:
        case T_ECHO:
        case T_PRINT:
        case T_NEW:
        case T_REQUIRE:
        case T_REQUIRE_ONCE:
        case T_INCLUDE:
        case T_INCLUDE_ONCE:
        case T_VAR:
          coder_add_space($result);
          // Append a space.
          $result .= trim($text) . ' ';
          break;

        case T_DO:
          $result .= trim($text);
          $in_do_while = TRUE;
          break;

        case T_WHILE:
          if ($in_do_while && substr(rtrim($result), -1) === '}') {
            // Write while after right parenthesis for do {...} while().
            $result = rtrim($result) . ' ';
            $in_do_while = FALSE;
          }
          // Append a space.
          $result .= trim($text) . ' ';
          break;

        case T_IF:
          // Use "elseif" instead of "else if".
          if (substr(rtrim($result), -4) == 'else') {
            $result = rtrim($result);
          }
          coder_add_space($result);
          // Append a space.
          $result .= trim($text) . ' ';
          break;

        case T_ELSE:
        case T_ELSEIF:
          // Write else and elseif to a new line.
          $result = rtrim($result);
          coder_br($result);
          $result .= trim($text) . ' ';
          break;

        case T_CASE:
        case T_DEFAULT:
          $braces_in_case[$switches] = 0;
          $result         = rtrim($result);
          $after_case     = TRUE;
          if (!$in_case) {
            $in_case = TRUE;
            // Add a line break between cases.
            if (substr($result, -1) != '{') {
              coder_br($result);
            }
          }
          else {
            // Decrease current indent to align multiple cases.
            --$_coder_indent;
          }
          coder_br($result);
          $result .= trim($text) . ' ';
          break;

        case T_BREAK:
          // Write break to a new line.
          $result = rtrim($result);
          coder_br($result);
          // Trailing space needed for 'break 3;'.
          $result .= trim($text) . ' ';
          if ($in_case && !$braces_in_case[$switches]) {
            --$_coder_indent;
            $in_case = FALSE;
          }
          break;

        case T_RETURN:
          if ($in_case && !$braces_in_case[$switches]) {
            // Defer reduction of indent for later.
            ++$_coder_indent;
            $after_return_in_case = TRUE;
          }
        case T_CONTINUE:
          coder_add_space($result);
          $result .= trim($text) . ' ';
          // Decrease indent only if we're not in a control structure inside a case.
          if ($in_case && !$braces_in_case[$switches]) {
            --$_coder_indent;
            $in_case = FALSE;
          }
          break;

        case T_ABSTRACT:
        case T_PRIVATE:
        case T_PUBLIC:
        case T_PROTECTED:
          // Class member function properties must be treated similar to
          // T_FUNCTION, but without line-break after the token. Because more
          // than one of these tokens can appear in front of a function token,
          // we need another white-space control variable.
          $result .= trim($text) . ' ';
          $after_visibility_modifier = TRUE;
          break;

        case T_FUNCTION:
          $in_function_declaration = TRUE;
          // Fall through.
        case T_CLASS:
          // Write function and class to new lines.
          $result = rtrim($result);
          if (substr($result, -1) == '}') {
            coder_br($result);
          }
          if (!$after_visibility_modifier) {
            coder_br($result);
          }
          else {
            // This code only applies to T_FUNCTION; do not add a newline
            // after public/protected/private/abstract.
            $after_visibility_modifier = FALSE;
            $result .= ' ';
          }
          $result .= trim($text) . ' ';
          break;

        case T_EXTENDS:
        case T_INSTANCEOF:
          // Add space before and after 'extends' and 'instanceof'.
          $result = rtrim($result);
          $result .= ' ' . trim($text) . ' ';
          break;

        case T_AND_EQUAL:
        case T_AS:
        case T_BOOLEAN_AND:
        case T_BOOLEAN_OR:
        case T_CONCAT_EQUAL:
        case T_DIV_EQUAL:
        case T_DOUBLE_ARROW:
        case T_IS_EQUAL:
        case T_IS_NOT_EQUAL:
        case T_IS_IDENTICAL:
        case T_IS_NOT_IDENTICAL:
        case T_IS_GREATER_OR_EQUAL:
        case T_IS_SMALLER_OR_EQUAL:
        case T_LOGICAL_AND:
        case T_LOGICAL_OR:
        case T_LOGICAL_XOR:
        case T_MINUS_EQUAL:
        case T_MOD_EQUAL:
        case T_MUL_EQUAL:
        case T_OR_EQUAL:
        case T_PLUS_EQUAL:
        case T_SL:
        case T_SL_EQUAL:
        case T_SR:
        case T_SR_EQUAL:
        case T_XOR_EQUAL:
          // Surround operators with spaces.
          if (substr($result, -1) != ' ') {
            // $result must not be trimmed to allow multi-line if-clauses.
            $result .= ' ';
          }
          $result .= trim($text) . ' ';
          break;

        case T_COMMENT:
        case T_ML_COMMENT:
        case T_DOC_COMMENT:
          if (substr($text, 0, 3) == '/**') {
            // Prepend a new line.
            $result = rtrim($result);
            if (!$after_initial_comment) {
              coder_br($result);
            }
            else {
              // This probably will get set below, but it's good to
              // explicitly turn it off after the initial comment has
              // influenced behavior and now is not necessary.
              $after_initial_comment = FALSE;
            }
            coder_br($result);

            // Remove carriage returns.
            $text = str_replace("\r", '', $text);

            $lines = explode("\n", $text);
            $params_fixed = FALSE;
            for ($l = 0; $l < count($lines); ++$l) {
              $lines[$l] = trim($lines[$l]);

              // Add a new line between function description and first parameter description.
              if (!$params_fixed && substr($lines[$l], 0, 8) == '* @param' && $lines[$l - 1] != '*') {
                $result .= ' *';
                coder_br($result);
                $params_fixed = TRUE;
              }
              elseif (!$params_fixed && substr($lines[$l], 0, 8) == '* @param') {
                // Do nothing if parameter description is properly formatted.
                $params_fixed = TRUE;
              }

              // Add a new line between function params and return.
              if (substr($lines[$l], 0, 9) == '* @return' && $lines[$l - 1] != '*') {
                $result .= ' *';
                coder_br($result);
              }

              // Add one space indent to get ' *[...]'.
              if ($l > 0) {
                $result .= ' ';
              }
              $result .= $lines[$l];
              if ($l < count($lines)) {
                coder_br($result);
              }
            }
          }
          else {
            // Move the comment above if it's embedded.
            $statement = FALSE;
            // Some PHP versions throw a warning about wrong parameter count for
            // substr_count().
            $cc = substr_count(substr($result, $position_last_significant_token), "\n");
            if ((!$cc || $after_semicolon) && !$after_case) {
              $nl_position     = strrpos(rtrim($result, " \n"), "\n");
              $statement       = substr($result, $nl_position);
              $result          = substr($result, 0, $nl_position);
              $after_semicolon = FALSE;
              coder_br($result, $parenthesis);
            }
            $result .= trim($text);
            coder_br($result, $parenthesis);
            if ($statement) {
              // Newlines are automatically added, so remove these.
              $result = rtrim($result, "\n ");
              $result .= rtrim($statement, "\n ");
              coder_br($result, $parenthesis);
              // Need to update this, as our comment trickery has just
              // reshuffled the index.
              $position_last_significant_token = strlen(rtrim($result, " \n")) - 1;
            }
            else {
              if (strpos($text, '$' . 'Id$') === FALSE) {
                $after_comment = TRUE;
              }
              else {
                // Is the number two so that our bottom code doesn't override
                // our flag immediately.
                $after_initial_comment = 2;
              }
            }
          }
          break;

        case T_INLINE_HTML:
          $result .= $text;
          break;

        case T_START_HEREDOC:
          $result .= trim($text);
          coder_br($result, FALSE, FALSE);
          $in_heredoc = TRUE;
          break;

        case T_END_HEREDOC:
          $result .= trim($text);
          coder_br($result, FALSE, FALSE);
          $in_heredoc = FALSE;
          break;

        default:
          $result .= trim($text);
          break;
      }

      // Store last token.
      $lasttoken = $token;

      // Excluding comments and whitespace, set the position of the
      // last significant token's last character to the length of the
      // string minus one.
      switch ($id) {
        case T_WHITESPACE:
        case T_COMMENT:
        case T_ML_COMMENT:
        case T_DOC_COMMENT:
          break;

        default:
          $position_last_significant_token = strlen(rtrim($result, " \n")) - 1;
          break;
      }

      if ($id !== T_COMMENT && $id !== T_ML_COMMENT) {
        $after_comment = FALSE;
      }
      if ($after_initial_comment && $id !== T_WHITESPACE) $after_initial_comment--;
    }
  }
  return $result;
}

/**
 * Generate a line feed including current line indent.
 *
 * This function will also remove all line indentation from the
 * previous line if no text was added.
 *
 * @param &$result
 *   Result variable to append break and indent to, passed by reference.
 * @param $parenthesis
 *   Optional integer of parentheses level for extra indents.
 * @param $add_indent
 *   Whether to add current line indent after line feed.
 */
function coder_br(&$result, $parenthesis = FALSE, $add_indent = TRUE) {
  global $_coder_indent;

  // Scan result backwards for whitespace.
  for ($i = strlen($result) - 1; $i >= 0; $i--) {
    if ($result[$i] == ' ') {
      continue;
    }
    if ($result[$i] == "\n") {
      $result = rtrim($result, ' ');
      break;
    }
    // Non-whitespace was encountered, no changes necessary.
    break;
  }

  if ($parenthesis) {
    // Add extra indent for each parenthesis in multiline definitions (f.e. arrays).
    $_coder_indent = $_coder_indent + $parenthesis;
    $result = rtrim($result);
    // This recursive call will only be done once, as $parenthesis is
    // set to false.
    coder_br($result, FALSE, $add_indent);
    $_coder_indent = $_coder_indent - $parenthesis;
  }
  else {
    $output = "\n";
    if ($add_indent && $_coder_indent >= 0) {
      $output .= str_repeat('  ', $_coder_indent);
    }
    $result .= $output;
  }
}

/**
 * Write a space in certain conditions.
 *
 * A conditional space is needed after a right parenthesis of an if statement
 * that is not followed by curly braces.
 *
 * @param $result
 *   Current result string that will be checked.
 *
 * @return
 *   Resulting string with or without an additional space.
 */
function coder_add_space(&$result) {
  if (substr($result, -1) == ')') {
    $result .= ' ';
  }
}

/**
 * Trim overall code.
 *
 * Strips whitespace at the beginning and end of code,
 * removes the closing PHP tag and appends two empty lines.
 */
function coder_trim_php($code) {
  // Remove surrounding whitespace.
  $code = trim($code);

  // Remove closing PHP tag.
  if (substr($code, -2) == '?>') {
    $code = rtrim($code, '?>');
  }

  // Append two empty lines.
  $code .= str_repeat(chr(10), 2);

  return $code;
}

/**
 * Execute special tasks on source code.
 *
 * This function works similar to the Drupal hook and forms system. It searches
 * for all defined functions with the given prefix and performs a preg_replace
 * on the source code for each of these functions.
 *
 * Processor functions are defined with a associative array containing the
 * following keys with the corresponding values:
 *   #title
 *      A human readable text describing what the processor actually does.
 *   #search
 *      The regular expression to search for.
 *   #replace
 *      The replacement text for each match.
 *
 * Optional definitions:
 *   #debug
 *      Set this to true to directly output the results of preg_match_all and
 *      exit script execution after this processor.
 *
 * @param string $code
 *      The source code to process.
 * @param string $prefix
 *      Prefix of the functions to execute.
 *
 * @return
 *      The processed source code.
 */
function coder_exec_processors($code, $prefix) {
  if (empty($prefix)) {
    return;
  }
  $tasks = get_defined_functions();
  $tasks = $tasks['user'];
  for ($c = 0, $cc = count($tasks); $c < $cc; ++$c) {
    // If the defined function starts with the specified prefix, invoke it.
    if (strpos($tasks[$c], $prefix) === 0) {
      // Store the results using the function name as key in $tasks.
      $tasks[$tasks[$c]] = call_user_func($tasks[$c]);
    }
    // Remove the (indexed) key for every checked function.
    unset($tasks[$c]);
  }
  uasort($tasks, 'coder_order_processors');
  foreach ($tasks as $func => $task) {
    if (!isset($task['#search']) || (!isset($task['#replace']) && !isset($task['#replace_callback']))) {
      continue;
    }
    if (isset($task['#debug'])) {
      // Output regular expression results if debugging is enabled.
      preg_match_all($task['#search'], $code, $matches, PREG_SET_ORDER);
      echo "<pre>";
      var_dump($matches);
      echo "</pre>\n";
      // Exit immediately in debugging mode.
      exit;
    }
    if (isset($task['#replace_callback'])) {
      $code = preg_replace_callback($task['#search'], $task['#replace_callback'], $code);
    }
    else {
      $code = preg_replace($task['#search'], $task['#replace'], $code);
    }
  }

  return $code;
}

/**
 * Orders preprocessors by weight.
 *
 * @see coder_exec_processors()
 */
function coder_order_processors($a, $b) {
  if (isset($a['#weight']) && isset($b['#weight'])) {
    return $a['#weight'] - $b['#weight'];
  }
  else {
    return isset($a['#weight']) ? FALSE : TRUE;
  }
}

/**
 * @defgroup coder_preprocessor Preprocessors.
 * @{
 */
function coder_preprocessor_line_breaks_win() {
  return array(
    '#title' => 'Convert Windows line breaks to Unix format.',
    '#weight' => 1,
    '#search' => "@\r\n@",
    '#replace' => "\n",
  );
}

function coder_preprocessor_line_breaks_mac() {
  return array(
    '#title' => 'Convert Macintosh line breaks to Unix format.',
    '#weight' => 2,
    '#search' => "@\r@",
    '#replace' => "\n",
  );
}

function coder_preprocessor_php() {
  return array(
    '#title' => 'Always use &lt;?php ?&gt; to delimit PHP code, not the &lt;? ?&gt; shorthands.',
    '#search' => '@<\?(\s)@',
    '#replace' => "<?php$1",
  );
}

function coder_preprocessor_switch_duplicate_exit() {
  return array(
    '#title' => 'Either exit a switch case with return *or* break.',
    '#search' => '@
      (return   # match a return
        \s+     # - followed by some white-space
        .+      # - followed by any characters
        ;       # - followed by a semicolon
      )
      \s+       # match white-space (required)
      break;    # match a directly following "break;"
      @mx',
    '#replace' => '$1',
  );
}

function coder_preprocessor_inline_comment() {
  return array(
    '#title' => 'Move inline comments above remarked line.',
    '#weight' => 2,
    '#search' => '@
      ^([\040\t]*)  # match spaces or tabs only.
      (?!case)      # do not match case statements.
      (\S.+?        # do not match lines containing only a comment.
        [;,{]       # match the TRICKY lines only.
      )
      [\040\t]*     # match spaces or tabs only.
      (?!:)         # do not match URL protocols.
      //\s*         # match inline comment token.
      ([^;\$]+?)$   # fetch comment, but do not match CVS keyword Id, nested comments, and comment tokens in quotes (f.e. "W3C//DTD").
      @mx',
    '#replace' => "$1// $3\n$1$2",
  );
}

/**
 * @} End of "defgroup coder_preprocessor".
 */

/**
 * @defgroup coder_postprocessor Postprocessors.
 * @{
 */
function coder_postprocessor_cvs_id() {
  return array(
    '#title' => 'If the CVS keyword Id already exists, append a new line after it.',
    '#search' => '@
      ^(          # match start of a line
        //.*      # match an inline comment followed by any characters
        \$Id.*\$  # match a CVS Id tag
      )$          # match end of a line
      @mx',
    '#replace' => "$1\n",
  );
}

// @todo Disabled, since actually unwanted. Remove entirely?
function _coder_postprocessor_multiple_vars() {
  return array(
    '#title' => 'Align equal signs of multiple variable assignments in the same column.',
    '#search' => '@
      ^(          # match start of a line
        \n?\ *    # match white-space, but only one new line
        \$.+?     # match a variable name
        \ =\      # match a variable assignment
        .+?$      # match a variable value
      ){3,}       # require the pattern to match at least 3 times
      @mx',
    '#replace_callback' => 'coder_replace_multiple_vars',
  );
}

function _coder_replace_multiple_vars($matches) {
  // Retrieve all variable name = variable value pairs.
  $regex = '@
    ^           # match start of a line
    (\s*)       # match a single optional white-space char
    (\$.+?)     # match a variable name
    \ (.?)=\    # match a variable assignment
    (.+?$)      # match a variable value including end of line
    @mx';
  preg_match_all($regex, $matches[0], $vars, PREG_SET_ORDER);

  // Determine the longest variable name.
  $maxlength = 0;
  foreach ($vars as $var) {
    if (strlen($var[2]) > $maxlength) {
      $maxlength = strlen($var[2] . $var[3]);
    }
  }

  // Realign variable values at the longest variable names.
  $return = '';
  $extra_spaces = 0;
  for ($c = 0, $cc = count($vars); $c < $cc; ++$c) {
    if ($maxlength <= 20) {
      $extra_spaces = $maxlength - strlen($vars[$c][2] . $vars[$c][3]);
    }
    $return .= $vars[$c][1] . $vars[$c][2];
    $return .= str_repeat(' ', $extra_spaces) . ' ' . $vars[$c][3] . '= ';
    $return .= $vars[$c][4];
    if ($c < $cc - 1) {
      // Append a line break, but not to the last variable assignment.
      $return .= "\n";
    }
  }

  return $return;
}

// @todo Disabled, since buggy.
function _coder_postprocessor_indent_multiline_array() {
  // Still buggy, disabled for now.
  return array(
    '#title' => 'Align equal signs of multiline array assignments in the same column.',
    '#search' => '@
      ^                   # match start of a line
      (?:\s*              # require initial white-space
        (?:
          (?:
            ([\'"]).+?\1  # capture a string key
            |.+?          # or any other key without white-space
          )
          \s*=>\s*        # require associative array arrow syntax
          .+?             # match an array value
          |\),\s?         # or a closing brace followed by a comma and a single optional white-space char
        )$                # require end of a line
      ){3,}               # require the pattern to match at least 3 times
      @mix',
    //'#replace_callback' => 'coder_replace_indent_multiline_array',
  );
}

function _coder_replace_indent_multiline_array($matches) {
  // Separate out important components of the multiline array:
  // (\s*) matches existing indent as \1
  // (([\'"]).+?\2|\$.+?|[+\-]?(?:0x)?[0-9A-F]+) matches key as \2
  //    ([\'"]).+?\3 matches a quoted key, quote used is \3
  //    \.+? matches anything else
  // \),\s*? matches a closing parenthesis in a nested array
  // \s*=>\s* matches existing indentation and arrow to be discarded
  // (.+?) matches value as \4
  // {3,} requires three or more of these lines
  // mi enables multiline and caseless mode
  preg_match_all('/^(\s*)(?:(([\'"]).+?\3|\.+?)\s*=>\s*(.+?),?|\),)\s*?$/mi', $matches[0], $vars, PREG_SET_ORDER);
  // Determine max key length for varying indentations.
  $maxlengths = array();
  foreach ($vars as $var) {
    list(, $indent, $key) = $var;
    if (!isset($maxlengths[$indent])) {
      $maxlengths[$indent] = 0;
    }
    if (($t = strlen($key)) > $maxlengths[$indent]) {
      $maxlengths[$indent] = $t;
    }
  }
  // Reconstruct variable array declaration.
  $return = '';
  foreach ($vars as $var) {
    list(, $indent, $key, , $value) = $var;
    if ($key === NULL) {
      $return .= "$indent),\n";
      continue;
    }
    $spaces = str_repeat(' ', $maxlengths[$indent] - strlen($key));
    if ($value !== 'array(') {
      $comma = ',';
    }
    else {
      $comma = '';
    }
    $return .= "$indent$key$spaces => $value$comma\n";
  }
  $return = rtrim($return, "\n");
  return $return;
}

// @todo Disabled, since not yet working properly 25/03/2007 sun.
// @see common.inc, comment.module
function _coder_postprocessor_array_rearrange() {
  return array(
    '#title' => 'Break array elements into separate lines, indented one level.',
    // ([\040\t]*) matches blanks and tabs.
    // (.*?array\() matches anything and 'array('.
    // ((.+ => .+, ){3,}) matches all array items, except the last one.
    // (.+ => ([^\(\)]+)) matches the last array item, excluding.
    //   arrays or functions (starting with a left parenthesis) (not supported yet).
    //'#search' => '/^([\040\t]*)(.*?array\()((.+ => .+, ){3,})(.+ => ([^\(\)]+))\)/m',
    '#replace_callback' => 'coder_replace_array_rearrange',
  );
}

function _coder_replace_array_rearrange($matches) {
  // Retrieve all array items, except the last one.
  preg_match_all('/(.+? => .+?,) /', $matches[3], $items);

  // The original line including array(.
  $return = $matches[1] . $matches[2] . "\n";
  foreach ($items[1] as $item) {
    // All array items, except the last one, with extra indent.
    $return .= $matches[1] . '  ' . $item . "\n";
  }
  // Last array item, with extra indent and comma.
  $return .= $matches[1] . '  ' . $matches[5] . ",\n";
  // Closing parenthesis (on a new line).
  $return .= $matches[1] . ')';

  return $return;
}

function coder_postprocessor_if_curly_braces() {
  // This post-processor relies on the fact that coder_format already
  // re-formatted if statements without curly braces to be on one line.
  return array(
    '#title' => 'Use curly braces even in situations where they are technically optional.',
    '#search' => '@
      (\s*)                    # match leading white-space, including newline
      ((?:else)?if\ \(.+\)\ )  # match if/elseif statement
      ([^\{].+;)               # match conditional executed code not starting with a curly brace, delimited by a semicolon.
      @x',
    '#replace' => '$1$2{$1  $3$1}',
  );
}

/**
 * @} End of "defgroup coder_postprocessor".
 */

