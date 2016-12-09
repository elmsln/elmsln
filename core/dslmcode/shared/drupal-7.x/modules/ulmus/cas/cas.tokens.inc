<?php

/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_token_info().
 */
function cas_token_info() {
  $types['cas'] = array(
    'name' => t('CAS user'),
    'description' => t('Tokens related to a CAS user.'),
    'needs-data' => 'cas',
  );

  $cas['name'] = array(
    'name' => t('Name'),
    'description' => t('The CAS username.'),
  );

  return array(
    'types' => $types,
    'tokens' => array('cas' => $cas),
  );
}

/**
 * Implements hook_token_info_alter().
 */
function cas_token_info_alter(&$data) {
  $data['tokens']['user']['cas'] = array(
    'name' => t('CAS'),
    'description' => t("The account's primary CAS username."),
    'type' => 'cas',
  );
}

/**
 * Implements hook_tokens().
 */
function cas_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  if ($type == 'cas' && !empty($data['cas'])) {
    $cas = $data['cas'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'name':
          $replacements[$original] = $sanitize ? check_plain($cas) : $cas;
          break;
      }
    }
  }

  if ($type == 'user' && !empty($data['user'])) {
    $account = $data['user'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'cas':
          // Provide [user:cas] token.
          if (!empty($account->cas_name)) {
            $replacements[$original] = $sanitize ? check_plain($account->cas_name) : $account->cas_name;
          }
          break;
      }
    }

    // Provide [user:cas:?] dynamic tokens.
    if ($cas_tokens = token_find_with_prefix($tokens, 'cas')) {
      $replacements += token_generate('cas', $cas_tokens, array('cas' => $account->cas_name), $options);
    }
  }

  return $replacements;
}
