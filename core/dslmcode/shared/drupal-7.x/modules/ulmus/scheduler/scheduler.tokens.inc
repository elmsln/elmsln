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
    // Usually the tokens are generated on saved node data, where the scheduler
    // fields are numeric timestamps. However, if the tokens are required during
    // the process of saving a node before hook_node_presave() has been executed
    // then the fields will be date strings. Cater for both scenarios here.
    // @see https://www.drupal.org/node/2750467
    $node = $data['node'];
    foreach (array('publish_on', 'unpublish_on') as $field) {
      if (empty($node->$field)) {
        ${$field} = NULL;
      }
      elseif (is_numeric($node->$field)) {
        ${$field} = $node->$field;
      }
      else {
        ${$field} = _scheduler_strtotime($node->$field);
      }
    }

    // For the plain [node:scheduler-publish] and [node:scheduler-unpublish]
    // generate the replacements using the default date format of 'medium'.
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'scheduler-publish':
          if (!empty($publish_on)) {
            $replacements[$original] = format_date($publish_on, 'medium', '', NULL, $language_code);
          }
          break;
        case 'scheduler-unpublish':
          if (!empty($unpublish_on)) {
            $replacements[$original] = format_date($unpublish_on, 'medium', '', NULL, $language_code);
          }
          break;
        default:
      }
    }

    // Chained token replacement. This generates replacements for patterns with
    // a date format suffix, for example [node:scheduler-publish:long] or
    // [node:scheduler-unpublish:date_only].
    if (!empty($publish_on) && $publish_tokens = token_find_with_prefix($tokens, 'scheduler-publish')) {
      $replacements += token_generate('date', $publish_tokens, array('date' => $publish_on), $options);
    }
    if (!empty($unpublish_on) && $unpublish_tokens = token_find_with_prefix($tokens, 'scheduler-unpublish')) {
      $replacements += token_generate('date', $unpublish_tokens, array('date' => $unpublish_on), $options);
    }
  }
  return $replacements;
}
