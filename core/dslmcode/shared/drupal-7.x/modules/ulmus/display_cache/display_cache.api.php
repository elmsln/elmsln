<?php
/**
 * @file
 * Hooks provided by the Display Cache module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alters the keys to build a cid.
 *
 * Use this alteration to edit the context of cached entities.
 *
 * @param array $keys
 *   Array of keys. Used to build the cache id.
 *
 * @see drupal_render_cid_create()
 * @see drupal_render_cid_parts()
 */
function hook_display_cache_cache_keys_alter(&$keys) {
  // Add a 'foo' context to all nodes.
  if ($keys['entity_type'] === 'node') {
    $keys['my_new_context'] = 'foo';
  }
}

/**
 * @} End of "addtogroup hooks".
 */
