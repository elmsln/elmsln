<?php

/**
 * @file
 * Documents Node export dependency's hooks for api reference.
 */

/**
 * Handle dependencies not already handled.
 *
 * Let other modules alter this - for example to only allow some users to
 * export specific nodes or types.
 *
 * @param &$handled
 *   Boolean indicating whether the dependency was handled, only set to TRUE,
 *   never explicitly set it to FALSE.  Only run code when it is already FALSE.
 * @param $node
 *   The node to handle the dependency for.
 * @param $dependency
 *   The dependency data.
 */
function hook_node_export_dependency_alter(&$handled, &$node, $dependency) {
  if (!$handled) {
    // Attempt to handle the dependency here.
    // If it's handled successfully set $handled to TRUE.
  }
}