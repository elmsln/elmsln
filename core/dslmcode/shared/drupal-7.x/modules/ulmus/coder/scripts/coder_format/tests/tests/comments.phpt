<?php
TEST: Comment movement

--INPUT--
$foo = foo(); // Move up.
if ($foo) {
  bar($foo); // Move up.
}

--EXPECT--
// Move up.
$foo = foo();
if ($foo) {
  // Move up.
  bar($foo);
}

--INPUT--
$string = '//';
$foo    = 'http://google.com';
$string = array(
  'foo', '//',
);

--INPUT--
// Comment // comment.

--INPUT--
/**
 * This does stuff with FOO//BOO.
 */
function foo() {
  return 'boo';
}

--INPUT--
function _batch_progress_page_nojs() {
  // This is one of the later requests: do some processing first.

  // Error handling: if PHP dies due to a fatal error (e.g. non-existant
  // function), it will output whatever is in the output buffer,
  // followed by the error message.
}

--INPUT--
function drupal_page_cache_header($cache) {
  if ($if_modified_since && $if_none_match
      && $if_none_match == $etag // etag must match
      && $if_modified_since == $last_modified) {  // if-modified-since must match
    exit();
  }
}

--EXPECT--
function drupal_page_cache_header($cache) {
  if ($if_modified_since && $if_none_match
    // etag must match
    && $if_none_match == $etag
    // if-modified-since must match
    && $if_modified_since == $last_modified
  ) {
    exit();
  }
}

-- INPUT --
$a = 2; // ,

-- EXPECT --
// ,
$a = 2;

--INPUT--
function parse_size($size) {
  $suffixes = array(
    '' => 1,
    'k' => 1024,
    'm' => 1048576, // 1024 * 1024
    'g' => 1073741824, // 1024 * 1024 * 1024
  );
}

--EXPECT--
function parse_size($size) {
  $suffixes = array(
    '' => 1,
    'k' => 1024,
    // 1024 * 1024
    'm' => 1048576,
    // 1024 * 1024 * 1024
    'g' => 1073741824,
  );
}

--INPUT--
function drupal_to_js($var) {
  switch ($foo) {
    case 'boolean':
      return $var ? 'true' : 'false'; // Lowercase necessary!
  }
}

--EXPECT--
function drupal_to_js($var) {
  switch ($foo) {
    case 'boolean':
      // Lowercase necessary!
      return $var ? 'true' : 'false';
  }
}

--INPUT--
switch ($foo) {
  case 'bar': // Things
    break;

  default: // Other things
    break;
}

--EXPECT--
switch ($foo) {
  case 'bar':
    // Things
    break;

  default:
    // Other things
    break;
}

--INPUT--
function _db_query_callback($match, $init = FALSE) {
  switch ($match[1]) {
    case '%d': // We must use type casting to int to convert FALSE/NULL/(TRUE?)
      return (int)array_shift($args); // We don't need db_escape_string as numbers are db-safe

    case '%b': // binary data
      return db_encode_blob(array_shift($args));
  }
}

--EXPECT--
function _db_query_callback($match, $init = FALSE) {
  switch ($match[1]) {
    case '%d':
      // We must use type casting to int to convert FALSE/NULL/(TRUE?)
      // We don't need db_escape_string as numbers are db-safe
      return (int)array_shift($args);

    case '%b':
      // binary data
      return db_encode_blob(array_shift($args));
  }
}

--INPUT--
function _locale_import_read_po($op, $file, $mode = NULL, $lang = NULL, $group = 'default') {
  $context = "COMMENT"; // Parser context: COMMENT, MSGID, MSGID_PLURAL, MSGSTR and MSGSTR_ARR
  $lineno = 0;          // Current line

  while (!feof($fd)) {
    $line = fgets($fd, 1024); // A line should not be this long
    if (!strncmp("#", $line, 1)) { // A comment
      if ($context == "COMMENT") { // Already in comment context: add
        $current["#"][] = substr($line, 1);
      }
      elseif (($context == "MSGSTR") || ($context == "MSGSTR_ARR")) { // End current entry, start a new one
        _locale_import_one_string($op, $current, $mode, $lang, $file, $group);
      }
      else { // Parse error
        return FALSE;
      }
    }
  }
}

--EXPECT--
function _locale_import_read_po($op, $file, $mode = NULL, $lang = NULL, $group = 'default') {
  // Parser context: COMMENT, MSGID, MSGID_PLURAL, MSGSTR and MSGSTR_ARR
  $context = "COMMENT";
  // Current line
  $lineno = 0;

  while (!feof($fd)) {
    // A line should not be this long
    $line = fgets($fd, 1024);
    // A comment
    if (!strncmp("#", $line, 1)) {
      // Already in comment context: add
      if ($context == "COMMENT") {
        $current["#"][] = substr($line, 1);
      }
      // End current entry, start a new one
      elseif (($context == "MSGSTR") || ($context == "MSGSTR_ARR")) {
        _locale_import_one_string($op, $current, $mode, $lang, $file, $group);
      }
      // Parse error
      else {
        return FALSE;
      }
    }
  }
}

