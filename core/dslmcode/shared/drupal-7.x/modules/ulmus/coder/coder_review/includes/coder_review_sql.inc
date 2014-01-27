<?php

/**
 * @file
 * This include file implements coder functionality for SQL strings
 */

/**
 * Implements hook_reviews().
 */
function coder_review_sql_reviews() {
  $table = '\{[A-Za-z_]+\}'; // table-regex
  $bad = '[A-Za-z_]+';

  // NOTE: This doesn't catch all non-upper case keywords, but is a good start.
  $rules['upper'] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $table . '|insert\s+into\s+' . $table . '|update\s+' . $table . '\s+set|delete\s+from\s+' . $table . ')',
    '#source' => 'quote',
    '#warning' => 'SQL keywords should be upper case',
    '#case-sensitive' => TRUE,
    '#severity' => 'minor',
    '#never' => '[\s=\(](t|st|dt)\s*\(',
  );
  $rules['curly'] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $bad . '|insert\s+into\s+' . $bad . '|update\s+' . $bad . '\s+set|delete\s+from\s' . $bad . ')',
    '#source' => 'quote',
    '#warning' => 'table names should be enclosed in {curly_brackets}',
    '#severity' => 'critical',
    '#never' => '[\s=\(](t|st|dt)\s*\(',
  );
  $rules['limit'] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $table . '|insert\s+into\s+' . $table . ')\s+.*[Ll][Ii][Mm][Ii][Tt]\s[0-9]+',
    '#source' => 'quote',
    '#warning' => array(
      '#text' => 'Use !db_query_range() instead of the SQL LIMIT clause',
      '#args' => array(
        '!db_query_range' => _drupalapi('db_query_range'),
      ),
      '#link' => _drupalnode(1395),
    ),
    '#never' => '[\s=\(](t|st|dt)\s*\(',
  );
  $rules['noteq'] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $table . '|update\s+' . $table . '\s+set|delete\s+from\s' . $table . ')\s+.*!=',
    '#source' => 'quote',
    '#warning' => 'Use ANSI standard &lt;&gt; instead of !=',
    '#never' => '[\s=\(](t|st|dt)\s*\(',
  );
  $rules['backtick'] = array(
    '#type' => 'regex',
    '#value' => '^(select\s+.*\s+from\s+' . $table . '\s+.+?=\s*`|insert\s+into\s+' . $table . '\s+.*?VALUES\s*(\(\s*`|\(.*?,\s*`)|update\s+' . $table . '\s+set\s+.*?=\s*`|delete\s+from\s' . $table . '\s+.*?=\s*`)',
    '#source' => 'quote',
    '#warning' => "Don't use back ticks to quote values as it is not compliant with ANSI SQL",
    '#never' => '[\s=\(](t|st|dt)\s*\(',
  );
  $rules['count'] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => 'db_query\s*\(\s*[\'"]select\s+count\s*\(\s*\*\s*\)\s+from\s+',
    '#warning' => array(
      '#text' => 'You may not want to use SELECT COUNT(*), if all you want to do is check for the existance of any rows, rather than the actual number of rows.',
      '#link' => _drupalnode(224333, 'select_count'),
    ),
    '#severity' => 'minor',
  );

  $review = array(
    '#title' => 'Drupal SQL Standards',
    '#rules' => $rules,
    '#description' => 'Checks for SQL strings inside db_query, since the change to DBTNG, this is less useful.',
    '#version' => 2,
    '#image' => 'images/sql.png',
  );
  return array('sql' => $review);
}
