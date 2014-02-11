<?php

/**
 * @file
 * Display Suite revision callback.
 */

/**
 * Menu callback: show an individual revision node using the revision view mode.
 */
function ds_revision_node_show($node, $message = NULL) {

  drupal_set_title(t('Revision of %title from %date', array('%title' => $node->title, '%date' => format_date($node->revision_timestamp))), PASS_THROUGH);

  // Update the history table, stating that this user viewed this node.
  node_tag_new($node);

  // Determine view mode.
  $layout = ds_get_layout('node', $node->type, 'revision', FALSE);
  $view_mode = ($layout) ? 'revision' : 'full';
  drupal_static('ds_view_mode', $view_mode);

  // For markup consistency with other pages, use node_view_multiple() rather than node_view().
  return node_view_multiple(array($node->nid => $node), $view_mode);
}
