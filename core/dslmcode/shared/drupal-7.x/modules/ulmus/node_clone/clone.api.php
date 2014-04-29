<?php

/**
 * @file
 * API documentation for the Node clone module.
 */

/**
 * Alter the node before saving a clone.
 *
 * @param $node
 *   Reference to the fully loaded node object being saved (the clone) that
 *   can be altered as needed.
 * @param array $context
 *   An array of context describing the clone operation. The keys are:
 *   - 'method' : Can be either 'prepopulate' or 'save-edit'.
 *   - 'original_node' : The original fully loaded node object being cloned.
 *
 * @see clone_node_save()
 * @see drupal_alter()
 */
function hook_clone_node_alter(&$node, $context) {
  if ($context['original_node']->type == 'special') {
    $node->special = special_something();
  }
}

/**
 * Alter the access to the ability to clone a given node.
 *
 * @param bool $access
 *   Reference to the boolean determining if cloning should be allowed on a
 *   given node.
 * @param $node
 *   The fully loaded node object being considered for cloning.
 *
 * @see clone_access_cloning()
 * @see drupal_alter()
 */
function hook_clone_access_alter(&$access, $node) {
  global $user;
  // Only allow cloning of nodes posted to groups you belong to.
  // This function doesn't really exist, but you get the idea...
  if (!og_user_is_member_of_group_the_node_is_in($user, $node)) {
    $access = FALSE;
  }
}
