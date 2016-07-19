<?php

/**
 * @file
 * API documentation for the Scheduler module.
 */

/**
 * Allows to prevent publication of a scheduled node.
 *
 * @param object $node
 *   The scheduled node that is about to be published.
 *
 * @return bool
 *   FALSE if the node should not be published. TRUE otherwise.
 */
function hook_scheduler_allow_publishing($node) {
  $allowed = TRUE;

  // Prevent publication of nodes that do not have the 'Approved for publication
  // by the CEO' checkbox ticked.
  if ($items = field_get_items('node', $node, 'field_approved')) {
    $allowed = !empty($items[0]['value']);

    // If publication is denied then inform the user why.
    if (!$allowed) {
      drupal_set_message(t('The content will only be published after approval by the CEO.'), 'status', FALSE);
    }
  }

  return $allowed;
}

/**
 * Allows to prevent unpublication of a scheduled node.
 *
 * @param object $node
 *   The scheduled node that is about to be unpublished.
 *
 * @return bool
 *   FALSE if the node should not be unpublished. TRUE otherwise.
 */
function hook_scheduler_allow_unpublishing($node) {
  $allowed = TRUE;

  // Prevent unpublication of competition entries if not all prizes have been
  // claimed.
  if ($node->type == 'competition' && $items = field_get_items('node', $node, 'field_competition_prizes')) {
    $allowed = (bool) count($items);

    // If unpublication is denied then inform the user why.
    if (!$allowed) {
      drupal_set_message(t('The competition will only be unpublished after all prizes have been claimed by the winners.'));
    }
  }

  return $allowed;
}
