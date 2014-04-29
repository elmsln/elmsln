<?php

/**
 * @file
 * Plugin to provide a relationship handler for a field collection field.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Field collection item'),
  'description' => t('Creates an entity context from a field collection field on a field.'),
  'context' => 'field_collection_field_collection_from_field_context',
  'edit form' => 'field_collection_field_collection_from_field_edit_form',
  'get child' => 'field_collection_field_collection_from_field_get_child',
  'get children' => 'field_collection_field_collection_from_field_get_children',
  'defaults' => array('delta' => 0),
);

/**
 * Get child callback.
 */
function field_collection_field_collection_from_field_get_child($plugin, $parent, $child) {
  $plugins = field_collection_field_collection_from_field_get_children($plugin, $parent);
  return $plugins[$parent . ':' . $child];
}

/**
 * Get children callback.
 */
function field_collection_field_collection_from_field_get_children($plugin, $parent) {

  $plugins = array();
  $instances_info = field_info_instances();
  if (isset($instances_info['field_collection_item'])) {
    $field_collection_items = $instances_info['field_collection_item'];

    foreach (field_read_instances() as $instance) {
      if (isset($field_collection_items[$instance['field_name']])) {
        $child_plugin_id = $parent . ':' . $instance['entity_type'] . ':' . $instance['bundle'] . ':' . $instance['field_name'];

        $child_plugin = $plugin;
        $child_plugin['context name'] = $instance['entity_type'] . ':' . $instance['bundle'] . ':' . $instance['field_name'];
        $child_plugin['title'] = t(
          '!label field collection (!field_name) from !entity_type (!bundle)',
          array(
          '!label' => $instance['label'],
          '!field_name' => $instance['field_name'],
          '!entity_type' => $instance['entity_type'],
          '!bundle' => $instance['bundle']
          )
        );
        $restrictions = array('type' => array($instance['bundle']));
        $child_plugin['required context'] = new ctools_context_required(ucfirst($instance['entity_type']), $instance['entity_type'], $restrictions);
        $child_plugin['parent'] = $parent;
        $child_plugin['keyword'] = 'Field collection';
        $child_plugin['entity_type'] = $instance['entity_type'];
        $child_plugin['field_name'] = $instance['field_name'];

        $child_plugin['name'] = $child_plugin_id;
        $plugins[$child_plugin_id] = $child_plugin;

      }
    }
  }

  return $plugins;
}

/**
 * Return a new field collection context based on an existing context.
 */
function field_collection_field_collection_from_field_context($context, $conf) {

  $plugin_info = ctools_get_relationship($conf['name']);
  $delta = (int) $conf['delta'];

  $entity = $context->data;
  if (isset($entity->{$plugin_info['field_name']})) {

    $items = field_get_items($plugin_info['entity_type'], $entity, $plugin_info['field_name']);
    if (isset($items[$delta]['value'])) {
      $field_collection_item = field_collection_item_load($items[$delta]['value']);
    }

    return ctools_context_create('entity:field_collection_item', $items[$delta]['value']);
  }

  return ctools_context_create_empty('entity:field_collection_item', NULL);
}

/**
 * Settings form.
 */
function field_collection_field_collection_from_field_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['delta'] = array(
    '#type' => 'textfield',
    '#title' => t('Delta'),
    '#size' => 3,
    '#description' => t('The relationship can only create one context, but multiple items can be related. Please type in the number you want. The first one will be 0.'),
    '#default_value' => empty($conf['delta']) ? 0 : $conf['delta'],
  );

  return $form;
}
