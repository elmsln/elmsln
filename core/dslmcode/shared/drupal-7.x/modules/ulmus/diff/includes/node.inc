<?php

/**
 * @file
 * Provide diff functions for the node module.
 */

/**
 * Private callback function to render the title field.
 */
function _node_entity_diff_additional_options_title($old_node, $new_node, $context) {
  $type = node_type_get_type($new_node);
  $row = array(
    '#name' => $type->title_label,
    '#states' => array(),
    '#weight' => -5,
    '#settings' => array(
      'show_header' => variable_get('diff_show_header_node', 1),
    ),
  );
  foreach ($context['states'] as $state) {
    switch ($state) {
      case 'rendered':
        $row['#states'][$state] = array(
          '#old' => l($old_node->title, 'node/' . $old_node->title),
          '#new' => l($new_node->title, 'node/' . $new_node->title),
        );
        break;

      // We specify a default so that the title is allows compared.
      case 'raw':
      default:
        $row['#states'][$state] = array(
          '#old' => array($old_node->title),
          '#new' => array($new_node->title),
        );
        break;
    }
  }
  return $row;
}

/**
 * Private callback function to render the type field.
 */
function _node_entity_diff_additional_options_type($old_node, $new_node, $context) {
  $row = array(
    '#name' => t('Content type'),
    '#states' => array(),
    '#weight' => -4,
    '#settings' => array(),
  );
  $old_type = node_type_get_type($old_node);
  $new_type = node_type_get_type($new_node);

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array($old_type ? $old_type->name : t('Deleted type !type', array('!type' => $old_node->type))),
      '#new' => array($new_type ? $new_type->name : t('Deleted type !type', array('!type' => $new_node->type))),
    );
  }
  return $row;
}

/**
 * Private callback function to render the author field.
 */
function _node_entity_diff_additional_options_author($old_node, $new_node, $context) {
  $old_author = user_load($old_node->uid);
  $new_author = user_load($new_node->uid);
  return _node_entity_diff_additional_options_account(t('Author'), $old_author, $new_author, $context, -4);
}

/**
 * Private callback function to render the revision_author field.
 */
function _node_entity_diff_additional_options_revision_author($old_node, $new_node, $context) {
  $old_author = user_load($old_node->revision_uid);
  $new_author = user_load($new_node->revision_uid);
  return _node_entity_diff_additional_options_account(t('Revision author'), $old_author, $new_author, $context, -3.9);
}

/**
 * Private callback function to render the author field.
 */
function _node_entity_diff_additional_options_account($label, $old_author, $new_author, $context, $weight = 0) {
  $row = array(
    '#name' => $label,
    '#states' => array(),
    '#weight' => $weight,
    '#settings' => array(),
  );
  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array($old_author ? format_username($old_author) : t('Deleted user')),
      '#new' => array($new_author ? format_username($new_author) : t('Deleted user')),
    );
  }
  return $row;
}

/**
 * Private callback function to render the status, sticky and published field.
 */
function _node_entity_diff_additional_options_publishing_flags($old_node, $new_node, $context) {
  $row = array(
    '#name' => t('Publishing options'),
    '#states' => array(),
    '#weight' => -3,
    '#settings' => array(),
  );
  $old_options = array($old_node->status ? t('Published') : t('Unpublished'));
  if ($old_node->promote) {
    $old_options[] = t('Promoted to front page');
  }
  if ($old_node->sticky) {
    $old_options[] = t('Sticky at top of lists');
  }

  $new_options = array($new_node->status ? t('Published') : t('Unpublished'));
  if ($new_node->promote) {
    $new_options[] = t('Promoted to front page');
  }
  if ($new_node->sticky) {
    $new_options[] = t('Sticky at top of lists');
  }

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => $old_options,
      '#new' => $new_options,
    );
  }
  return $row;
}

/**
 * Private callback function to render the created field.
 */
function _node_entity_diff_additional_options_created($old_node, $new_node, $context) {
  return _node_entity_diff_additional_options_date_field(t('Created timestamp'), $old_node->created, $new_node->created, $context, -1);
}

/**
 * Private callback function to render the changed field.
 */
function _node_entity_diff_additional_options_changed($old_node, $new_node, $context) {
  return _node_entity_diff_additional_options_date_field(t('Changed timestamp'), $old_node->changed, $new_node->changed, $context, -1);
}

/**
 * Private callback function to render the revision_timestamp field.
 */
function _node_entity_diff_additional_options_revision_timestamp($old_node, $new_node, $context) {
  return _node_entity_diff_additional_options_date_field(t('Revision timestamp'), $old_node->revision_timestamp, $new_node->revision_timestamp, $context, -1);
}

/**
 * Helper function to render the date flags.
 */
function _node_entity_diff_additional_options_date_field($label, $old_date, $new_date, $context, $weight = 0) {
  $row = array(
    '#name' => $label,
    '#states' => array(),
    '#weight' => $weight,
    '#settings' => array(),
  );

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array(format_date($old_date)),
      '#new' => array(format_date($new_date)),
    );
  }
  return $row;
}

/**
 * Private callback function to render the comment field.
 */
function _node_entity_diff_additional_options_comment($old_node, $new_node, $context) {
  if (!module_exists('comment')) {
    return array();
  }
  $row = array(
    '#name' => t('Comment setting'),
    '#states' => array(),
    '#weight' => -1,
    '#settings' => array(),
  );
  $options = array(
    COMMENT_NODE_OPEN => t('Open'),
    COMMENT_NODE_CLOSED => t('Closed'),
    COMMENT_NODE_HIDDEN => t('Hidden'),
  );

  foreach ($context['states'] as $state) {
    $row['#states'][$state] = array(
      '#old' => array($options[$old_node->comment]),
      '#new' => array($options[$new_node->comment]),
    );
  }
  return $row;
}
