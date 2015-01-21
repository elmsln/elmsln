<?php

/**
 * @file
 * Flag module tokens support.
 */

/**
 * Implements of hook_token_info().
 */
function typo_token_info() {
  $types = array();
  $tokens = array();

  // Flag tokens.
  $types['typo'] = array(
    'name' => t('Typo'),
    'description' => t('Tokens related to typo data.'),
    'needs-data' => 'typo',
  );

  $tokens['typo']['url'] = array(
    'name' => t('Typo URL'),
    'description' => t('The URL where the typo was found.'),
  );
  $tokens['typo']['text'] = array(
    'name' => t('typo text'),
    'description' => t('The text of the typo.'),
  );
  $tokens['typo']['comment'] = array(
    'name' => t('typo comment'),
    'description' => t('Comment for typo.'),
  );

  return array(
    'types' => $types,
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function typo_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  if ($type == 'typo' && !empty($data['typo'])) {
    $typo = $data['typo'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'url':
          $replacements[$original] = $sanitize ? check_plain($typo->url) : $typo->url;
          break;
        case 'text':
          $replacements[$original] = $sanitize ? check_plain($typo->text) : $typo->text;
          break;
        case 'comment':
          $replacements[$original] = $sanitize ? check_plain($typo->comment) : $typo->comment;
          break;
      }
    }
  }

  return $replacements;
}
