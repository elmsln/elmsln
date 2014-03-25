<?php

/**
 * @file
 * Builds placeholder replacement tokens for node scheduler data.
 */

/**
 * Implements hook_token_info().
 */
function scheduler_token_info() {
  $info['tokens']['node']['scheduler-publish'] = array(
    'name' => t('Publish on date'),
    'description' => t("The date the node will be published."),
    'type' => 'date',
  );
  $info['tokens']['node']['scheduler-unpublish'] = array(
    'name' => t('Unpublish on date'),
    'description' => t("The date the node will be unpublished."),
    'type' => 'date',
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function scheduler_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $language_code = isset($options['language']) ? $options['language']->language : NULL;
  $replacements = array();

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'scheduler-publish':
          if (isset($node->publish_on)) {
            $replacements[$original] = format_date($node->publish_on, 'medium', '', NULL, $language_code);
          }
          break;
        case 'scheduler-unpublish':
          if (isset($node->unpublish_on)) {
            $replacements[$original] = format_date($node->unpublish_on, 'medium', '', NULL, $language_code);
          }
          break;
      }
    }

    // Chained token replacement.
    if (isset($node->publish_on) && $publish_tokens = token_find_with_prefix($tokens, 'scheduler-publish')) {
      $replacements += token_generate('date', $publish_tokens, array('date' => $node->publish_on), $options);
    }
    if (isset($node->unpublish_on) && $unpublish_tokens = token_find_with_prefix($tokens, 'scheduler-unpublish')) {
      $replacements += token_generate('date', $unpublish_tokens, array('date' => $node->unpublish_on), $options);
    }
  }

  return $replacements;
}
