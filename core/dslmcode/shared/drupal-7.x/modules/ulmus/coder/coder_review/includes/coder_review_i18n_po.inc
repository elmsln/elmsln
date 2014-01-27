<?php

/**
 * @file
 * Provides coder_reviews for internationalization translation file issues.

 * This include file implements coder review functionality to check for
 * Internationalization issues in translation (.po) files.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_i18n_po_reviews() {
  $argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'\'|"")';

  $rules[] = array(
    '#type' => 'callback',
    '#filename' => array('po'),
    '#value' => '_coder_review_translation_callback',
  );

  $review = array(
    '#title' => 'Translation files',
    '#rules' => $rules,
    '#description' => 'Checks for .po translation issues, this is somewhat experimental',
    '#version' => 2,
    '#image' => 'images/po.png',
  );
  return array('i18n_po' => $review);
}

/**
 * Rule callback: Defines how to check for issues in translation files.
 */
function _coder_review_translation_callback(&$coder_args, $review, $rule, $lines, &$results) {
  $severity_name = _coder_review_severity_name($coder_args, $review, $rule);

  // Parse the translation file into msgid/msgstr pairs.
  $translations = array();
  foreach ($coder_args['#all_lines'] as $lineno => $line) {
    if (preg_match('/^(msgid|msgstr) "(.*)"$/', $line, $matches)) {
      if ($matches[1] == 'msgid') {
        $msgid = $matches[2];
      }
      elseif (!empty($msgid)) {
        $translations[$lineno] = array('msgid' => $msgid, 'msgstr' => $matches[2]);
        unset($msgid);
      }
    }
  }

  // Check each translation.
  foreach ($translations as $lineno => $translation) {
    $msgid = $translation['msgid'];
    $msgstr = $translation['msgstr'];

    // Check the translation first capitable letter.
    if (!empty($msgstr)) {
      $msgid0 = _substr($msgid, 0, 1);
      $msgstr0 = _substr($msgstr, 0, 1);
      if (($msgid0 == _strtoupper($msgid0) && $msgstr0 != _strtoupper($msgstr0)) || ($msgid0 == _strtolower($msgid0) && $msgstr0 != _strtolower($msgstr0))) {
        $tmprule = $rule;
        $tmprule['#warning'] = "The first letter in the translation text should have the same capitalization as it's original text.";
        _coder_review_error($results, $tmprule, $severity_name, $lineno, $msgstr);
      }

      // Check the translation trailing periods.
      if (_substr($msgid, -1, 1) == '.' && !_substr($msgstr, -1, 1) != '.') {
        $tmprule = $rule;
        $tmprule['#warning'] = 'The translation text should end in a period when the same original text also ends in a period.';
        _coder_review_error($results, $tmprule, $severity_name, $lineno, $msgstr);
      }

      // Check punctuation characters.
      if (preg_match_all('/[\.,:;?!]/', $msgid, $matches)) {
        foreach ($matches[0] as $html) {
          if (stripos($msgstr, $html) === FALSE) {
            $tmprule = $rule;
            $tmprule['#warning'] = 'Punctuation characters (.,:;?!) from the original text should exist in the translation.';
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $msgstr);
          }
        }
      }
      if (preg_match_all('/[\.,:;?!]/', $msgstr, $matches)) {
        foreach ($matches[0] as $html) {
          if (stripos($msgid, $html) === FALSE) {
            $tmprule = $rule;
            $tmprule['#warning'] = 'Punctuations characters (.,:;?!) in the translation should also exist in the original text.';
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $msgstr);
          }
        }
      }

      // Check HTML tags.
      if (preg_match_all('/<[^>]*>/', $msgid, $matches)) {
        foreach ($matches[0] as $html) {
          if (stripos($msgstr, $html) === FALSE) {
            $tmprule = $rule;
            $tmprule['#warning'] = 'HTML from the original text should also exist in the translation.';
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $msgstr);
          }
        }
      }

      // Check placeholders.
      if (preg_match_all('/[\!\@\%]\w+/', $msgid, $matches)) {
        foreach ($matches[0] as $placeholder) {
          if (stripos($msgstr, $placeholder) === FALSE) {
            $tmprule = $rule;
            $rule['#warning'] = 'If placeholders like !name, @name or %name exist in the original text, they must also exist in the translation.';
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $msgstr);
          }
        }
      }

      // @TODO: Check translations for opening/closing tags if they contain HTML.
      // @TODO: Quotation checks.
      // @TODO: Parenthesis (()[]{}) checks.
    }
  }
}

