<?php

/**
 * @file
 * Hooks provided by the diff module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allow modules to provide a comparison about entity properties.
 *
 * @param object $old_entity
 *   The older entity revision.
 *
 * @param object $new_entity
 *   The newer entity revision.
 *
 * @param array $context
 *   An associative array containing:
 *   - entity_type: The entity type; e.g., 'node' or 'user'.
 *   - old_entity: The older entity.
 *   - new_entity: The newer entity.
 *   - view_mode: The view mode to use. Defaults to FALSE. If no view mode is
 *                given, the recommended fallback view mode is 'default'.
 *   - states: An array of view states. These could be one of:
 *     - raw: The raw value of the diff, the classic 7.x-2.x view.
 *     - rendered: The rendered HTML as determined by the view mode. Only
 *                 return markup for this state if the value is normally shown
 *                 by this view mode. The user will most likely be able to see
 *                 the raw or raw_plain state, so this is optional.
 *
 *                 The rendering state is a work in progress.
 *
 *     Conditionally, you can get these states, but setting these will override
 *     the user selectable markdown method.
 *
 *     - raw_plain: As raw, but text should be markdowned.
 *     - rendered_plain: As rendered, but text should be markdowned.
 *
 * @return array
 *   An associative array of values keyed by the entity property.
 *
 *   This is effectively an unnested Form API-like structure.
 *
 *   States are returned as follows:
 *
 *   $results['line'] = array(
 *     '#name' => t('Line'),
 *     '#states' => array(
 *       'raw' => array(
 *         '#old' => '<p class="line">This was the old line number [tag].</p>',
 *         '#new' => '<p class="line">This is the new line [tag].</p>',
 *       ),
 *       'rendered' => array(
 *         '#old' => '<p class="line">This was the old line number <span class="line-number">57</span>.</p>',
 *         '#new' => '<p class="line">This is the new line <span class="line-number">57</span>.</p>',
 *       ),
 *     ),
 *   );
 *
 *   For backwards compatibility, no changes are required to support states,
 *   but it is recommended to provide a better UI for end users.
 *
 *   For example, the following example is equivalent to returning the raw
 *   state from the example above.
 *
 *   $results['line'] = array(
 *     '#name' => t('Line'),
 *     '#old' => '<p class="line">This was the old line number [tag].</p>',
 *     '#new' => '<p class="line">This is the new line [tag].</p>',
 *   );
 */
function hook_entity_diff($old_entity, $new_entity, $context) {
  $results = array();

  if ($context['entity_type'] == 'node') {
    $type = node_type_get_type($new_entity);
    $results['title'] = array(
      '#name' => $type->title_label,
      '#old' => array($old_entity->title),
      '#new' => array($new_entity->title),
      '#weight' => -5,
      '#settings' => array(
        'show_header' => FALSE,
      ),
    );
  }

  return $results;
}

/**
 * Allow modules to alter a comparison about entities.
 *
 * @param array $entity_diffs
 *   An array of entity differences.
 * @param array $context
 *   An associative array containing:
 *   - entity_type: The entity type; e.g., 'node' or 'user'.
 *   - old_entity: The older entity.
 *   - new_entity: The newer entity.
 *   - view_mode: The view mode to use. Defaults to FALSE.
 *
 * @see hook_entity_diff()
 */
function hook_entity_diff_alter(&$entity_diffs, $context) {
  if ($context['entity_type'] == 'node') {
    $old_entity = $context['old_entity'];
    $new_entity = $context['new_entity'];
    $entity_diffs['custom_vid'] = array(
      '#name' => t('Second VID'),
      '#old' => array($old_entity->vid),
      '#new' => array($new_entity->vid),
      '#weight' => 5,
    );
    $entity_diffs['custom_log'] = array(
      '#name' => t('Second log'),
      '#old' => array($old_entity->log),
      '#new' => array($new_entity->log),
      '#weight' => 6,
    );
  }
}

/**
 * Callback to the module that defined the field to prepare items comparison.
 *
 * This allows the module to alter all items prior to rendering the comparative
 * values. It is mainly used to bulk load entities to reduce overheads
 * associated with loading entities individually.
 *
 * @param array $old_items
 *   An array of field items from the older revision.
 * @param array $new_items
 *   An array of field items from the newer revision.
 * @param array $context
 *   An associative array containing:
 *   - entity_type: The entity type; e.g., 'node' or 'user'.
 *   - bundle: The bundle name.
 *   - field: The field that the items belong to.
 *   - instance: The instance that the items belong to.
 *   - language: The language associated with $items.
 *   - old_entity: The older entity.
 *   - new_entity: The newer entity.
 *
 * @see MODULE_field_diff_view()
 */
function MODULE_field_diff_view_prepare(&$old_items, &$new_items, $context) {
  $fids = array();
  foreach (array_merge_recursive($old_items, $new_items) as $info) {
    $fids[$info['fid']] = $info['fid'];
  }
  // A single load is much faster than individual loads.
  $files = file_load_multiple($fids);

  // For ease of processing, store a reference of the entity on the item array.
  foreach ($old_items as $delta => $info) {
    $old_items[$delta]['file'] = isset($files[$info['fid']]) ? $files[$info['fid']] : NULL;
  }
  foreach ($new_items as $delta => $info) {
    $new_items[$delta]['file'] = isset($files[$info['fid']]) ? $files[$info['fid']] : NULL;
  }
}

/**
 * Callback to the module that defined the field to generate items comparisons.
 *
 * @param array $items
 *   An array of field items from the entity.
 * @param array $context
 *   An associative array containing:
 *   - entity: The entity being compared.
 *   - entity_type: The entity type; e.g., 'node' or 'user'.
 *   - bundle: The bundle name.
 *   - field: The field that the items belong to.
 *   - instance: The instance that the items belong to.
 *   - language: The language associated with $items.
 *   - old_entity: The older entity.
 *   - new_entity: The newer entity.
 *
 * @see MODULE_field_diff_view_prepare()
 */
function MODULE_field_diff_view($items, $context) {
  $diff_items = array();
  foreach ($items as $delta => $item) {
    if (isset($item['file'])) {
      $diff_items[$delta] = $item['file']->filename . ' [fid: ' . $item['fid'] . ']';
    }
  }

  return $diff_items;
}

/**
 * Allow other modules to interact with MODULE_field_diff_view_prepare().
 *
 * @param array $old_items
 *   An array of field items from the older revision.
 * @param array $new_items
 *   An array of field items from the newer revision.
 * @param array $context
 *   An associative array containing:
 *   - entity_type: The entity type; e.g., 'node' or 'user'.
 *   - bundle: The bundle name.
 *   - field: The field that the items belong to.
 *   - instance: The instance that the items belong to.
 *   - language: The language associated with $items.
 *   - old_entity: The older entity.
 *   - new_entity: The newer entity.
 *
 * @see MODULE_field_diff_view_prepare()
 */
function hook_field_diff_view_prepare_alter($old_items, $new_items, $context) {

}

/**
 * Allow other modules to interact with MODULE_field_diff_view().
 *
 * @param array $values
 *   An array of field items from the entity ready for comparison.
 * @param array $items
 *   An array of field items from the entity.
 * @param array $context
 *   An associative array containing:
 *   - entity: The entity being compared.
 *   - entity_type: The entity type; e.g., 'node' or 'user'.
 *   - bundle: The bundle name.
 *   - field: The field that the items belong to.
 *   - instance: The instance that the items belong to.
 *   - language: The language associated with $items.
 *   - old_entity: The older entity.
 *   - new_entity: The newer entity.
 *
 * @see MODULE_field_diff_view()
 */
function hook_field_diff_view_alter($values, $items, $context) {

}

/**
 * @} End of "addtogroup hooks".
 */
