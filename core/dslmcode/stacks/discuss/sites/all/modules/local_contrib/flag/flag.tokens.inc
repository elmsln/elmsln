<?php

/**
 * @file
 * Flag module tokens support.
 */

/**
 * Implements of hook_token_info().
 *
 * The tokens we provide on generic entities require token module.
 */
function flag_token_info() {
  $types = array();
  $tokens = array();

  // Flag tokens.
  $types['flag'] = array(
    'name' => t('Flags'),
    'description' => t('Tokens related to flag data.'),
    'needs-data' => 'flag',
  );
  $tokens['flag']['name'] = array(
    'name' => t('Flag name'),
    'description' => t('The flag machine-readable name.'),
  );
  $tokens['flag']['title'] = array(
    'name' => t('Flag title'),
    'description' => t('The human-readable flag title.'),
  );

  // Flagging tokens.
  //
  // Attached fields are exposed as tokens via some contrib module, but we
  // need to expose other fields ourselves. Currently, 'date' is the only such
  // field we expose.
  $types['flagging'] = array(
    'name' => t('Flaggings'),
    'description' => t('Tokens related to flaggings.'),
    'needs-data' => 'flagging',
  );
  $tokens['flagging']['date'] = array(
    'name' => t('Flagging date'),
    'description' => t('The date an item was flagged.'),
    'type' => 'date',
  );

  // Flag action tokens.
  $types['flag-action'] = array(
    'name' => t('Flag actions'),
    'description' => t('Tokens available in response to a flag action being executed by a user.'),
    'needs-data' => 'flag-action',
  );
  $tokens['flag-action']['action'] = array(
    'name' => t('Flag action'),
    'description' => t('The flagging action taking place, either "flag" or "unflag".'),
  );
  $tokens['flag-action']['entity-url'] = array(
    'name' => t('Flag entity URL'),
    'description' => t('The URL of the entity being flagged.'),
  );
  $tokens['flag-action']['entity-title'] = array(
    'name' => t('Flag entity title'),
    'description' => t('The title of the entity being flagged.'),
  );
  $tokens['flag-action']['entity-type'] = array(
    'name' => t('Flag entity type'),
    'description' => t('The type of entity being flagged, such as <em>node</em> or <em>comment</em>.'),
  );
  $tokens['flag-action']['entity-id'] = array(
    'name' => t('Flag entity ID'),
    'description' => t('The ID of entity being flagged, such as a nid or cid.'),
  );
  $tokens['flag-action']['count'] = array(
    'name' => t('Flag count'),
    'description' => t('The current count total for this flag.'),
  );

  // Add tokens for the flag count available at the entity level.
  // These require token module because we need its helper data and functions
  // to deal with token types that are not the same as the entity types they are
  // for (in particular, terms and vocabularies).
  if (module_exists('token')) {
    $entity_info = entity_get_info();
    foreach (flag_get_types() as $flag_type) {
      // The flag type is the entity type, but this is not necessarily the same
      // as the entity's token type.
      $token_type = $entity_info[$flag_type]['token type'];
      $flags = flag_get_flags($flag_type);
      foreach ($flags as $flag) {
        $tokens[$token_type]['flag-' . str_replace('_', '-', $flag->name) . '-count'] = array(
          'name' => t('@flag flag count', array('@flag' => $flag->get_title())),
          'description' => t('Total flag count for flag @flag', array('@flag' => $flag->get_title())),
          'flag-type' => $flag_type,
        );
        $tokens[$token_type]['flag-' . str_replace('_', '-', $flag->name) . '-link'] = array(
          'name' => t('@flag flag link', array('@flag' => $flag->get_title())),
          'description' => t('Flag/unflag link for @flag', array('@flag' => $flag->get_title())),
          'flag-type' => $flag_type,
        );
      }
    }
  }

  return array(
    'types' => $types,
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function flag_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);
  $langcode = isset($options['language']) ? $options['language']->language : NULL;

  if ($type == 'flag' && !empty($data['flag'])) {
    $flag = $data['flag'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'name':
          $replacements[$original] = $sanitize ? check_plain($flag->name) : $flag->name;
          break;

        case 'title':
          $replacements[$original] = $sanitize ? check_plain($flag->get_title()) : $flag->get_title();
          break;
      }
    }
  }
  elseif ($type == 'flagging' && !empty($data['flagging'])) {
    $flagging = $data['flagging'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'date':
          $replacements[$original] = format_date($flagging->timestamp, 'medium', '', NULL, $langcode);
          break;
      }
    }
    if ($date_tokens = token_find_with_prefix($tokens, 'date')) {
      $replacements += token_generate('date', $date_tokens, array('date' => $flagging->timestamp), $options);
    }
  }
  elseif ($type == 'flag-action' && !empty($data['flag-action'])) {
    $action = $data['flag-action'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'action':
          $replacements[$original] = $action->action;
          break;

        case 'entity-url':
          $replacements[$original] = $sanitize ? check_url($action->entity_url) : $action->entity_url;
          break;

        case 'entity-title':
          $replacements[$original] = $sanitize ? check_plain($action->entity_title) : $action->entity_title;
          break;

        case 'entity-type':
          $replacements[$original] = $action->entity_type;
          break;

        case 'entity-id':
          $replacements[$original] = $action->entity_id;
          break;

        case 'count':
          $replacements[$original] = $action->count;
          break;
      }
    }
  }

  // We only provide tokens on entity types if we have token module's helper
  // methods available.
  if (isset($data[$type]) && module_exists('token')) {
    $entity_type = token_get_entity_mapping('token', $type);
    if ($entity_type && in_array($entity_type, flag_get_types())) {
      $flags = flag_get_flags($entity_type);
      $object = $data[$type];
      foreach ($flags as $flag) {
        foreach ($tokens as $name => $original) {
          $flag_count_token = 'flag-' . str_replace('_', '-', $flag->name) . '-count';
          $flag_link_token = 'flag-' . str_replace('_', '-', $flag->name) . '-link';
          if ($name == $flag_count_token) {
            $replacements[$original] = $flag->get_count($flag->get_entity_id($object));
          }
          elseif ($name == $flag_link_token) {
            $replacements[$original] = flag_create_link($flag->name, $flag->get_entity_id($object));
          }
        }
      }
    }
  }
  return $replacements;
}

/**
 * Returns HTML for a tokens browser.
 *
 * @param $variables
 *   An associative array containing:
 *   - types: An array naming the types of tokens to show.
 *   - global_types: Whether to show global tokens.
 */
function theme_flag_tokens_browser($variables) {
  $types = $variables['types'];
  $global_types = $variables['global_types'];

  if (module_exists('token')) {
    return theme('token_tree', array('token_types' => $types, 'global_types' => $global_types));
  }
  else {
    return '<p><em>' . t("Note: You don't have the <a href='@token-url'>Token</a> module installed, so the list of available tokens isn't shown here. You don't have to install <a href='@token-url'>Token</a> to be able to use tokens, but if you have it installed, and enabled, you'll be able to enjoy an interactive tokens browser.", array('@token-url' => 'http://drupal.org/project/token')) . '</em></p>';
  }
}
