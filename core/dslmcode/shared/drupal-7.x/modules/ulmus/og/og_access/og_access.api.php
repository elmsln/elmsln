<?php


/**
 * @file
 * Hooks provided by the Organic groups access module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allow modules to mark group privacy change.
 *
 * @param array $context
 *   Array with the following keys:
 *   'entity': the group entity.
 *   'entity_type':  The group type.
 *
 * @return bool
 *   TRUE if group privacy has been changed.
 */
function hook_og_access_invoke_node_access_acquire_grants($context) {
  $wrapper = entity_metadata_wrapper($context['entity_type'], $context['entity']);
  if (!isset($wrapper->OG_ACCESS_FIELD)) {
    // Group doesn't have OG access field attached to it.
    return;
  }

  $original_wrapper = entity_metadata_wrapper($context['entity_type'], $context['entity']->original);

  $og_access = $wrapper->{OG_ACCESS_FIELD}->value();
  $original_og_access = $original_wrapper->{OG_ACCESS_FIELD}->value();
  return $og_access !== $original_og_access;
}

/**
 * Allow modules to mark group privacy change.
 *
 * @param $result
 *   Array of results of the hooks called before.
 * @param array $context
 *   Array with the following keys:
 *   'entity': the group entity.
 *   'entity_type':  The group type.
 */
function hook_og_access_invoke_node_access_acquire_grants_alter(&$result, $context) {
  $wrapper = entity_metadata_wrapper($context['entity_type'], $context['entity']);
  if (!isset($wrapper->OG_ACCESS_FIELD)) {
    // Group doesn't have OG access field attached to it.
    return;
  }

  $original_wrapper = entity_metadata_wrapper($context['entity_type'], $context['entity']->original);

  $og_access = $wrapper->{OG_ACCESS_FIELD}->value();
  $original_og_access = $original_wrapper->{OG_ACCESS_FIELD}->value();
  if ($og_access !== $original_og_access) {
    $result['my_module'] = TRUE;
  }
}

/**
 * @} End of "addtogroup hooks".
 */
