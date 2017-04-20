<?php

/**
 * @file
 * Plugin to provide an relationship handler for any entity property.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Entity property or field (via Entity Metadata Wrapper)'),
  'description' => t('Creates any kind of context for entity properties and fields.'),
  'context' => 'entity_entity_property_context',
  'required context' => new ctools_context_required(t('Entity'), 'entity'),
  'edit form' => 'entity_entity_property_edit_form',
  'edit form validate' => 'entity_entity_property_edit_form_validate',
  'defaults' => array(
    'selector' => '',
    'target_context' => 'entity',
    'concatenator' => ','
  ),
);

/**
 * Return a new context based on an existing context.
 */
function entity_entity_property_context($context, $conf) {
  $plugin = $conf['name'];

  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data)) {
    return ctools_context_create_empty(isset($conf['target_context']) ? $conf['target_context'] : 'entity', NULL);
  }

  list($part1, $entity_type) = explode(':', $context->plugin);

  if (isset($context->data) && $entity = $context->data) {
    // Apply the selector.
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    $parts = explode(':', $conf['selector']);

    try {
      foreach ($parts as $part) {
        if (!($wrapper instanceof EntityStructureWrapper || $wrapper instanceof EntityListWrapper)) {
          $wrapper = NULL;
          $value = NULL;
          continue;
        }
        $wrapper = $wrapper->get($part);
      }
    }
    catch (EntityMetadataWrapperException $e) {
      $wrapper = NULL;
      $value = NULL;
    }

    if (isset($wrapper)) {
      $value = $wrapper->value();
    }

    // Massage list values.
    if ($wrapper instanceof EntityListWrapper) {
      $value = $wrapper[0]->value();
      $argument = implode($conf['concatenator'], $wrapper->value(array('identifier' => TRUE)));
    }
    elseif ($wrapper instanceof EntityDrupalWrapper) {
      $argument = $wrapper->getIdentifier();
    }

    // Bail out if we were unable to retrieve the value.
    if (!isset($value)) {
      return ctools_context_create_empty(isset($conf['target_context']) ? $conf['target_context'] : 'entity', NULL);
    }

    $context = ctools_context_create($conf['target_context'], $value);
    // Provide a suiting argument if context is used as argument.
    if (isset($argument)) {
      $context->argument = $argument;
    }
    return $context;
  }
}

function entity_entity_property_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Data selector'),
    '#description' => t('Any valid data selector, e.g. "title" to select a node\'s title, or "field_tags:1" to select the second tag.'),
    '#default_value' =>  $conf['selector'],
    '#required' => TRUE,
  );
  $form['concatenator'] = array(
    '#title' => t('Concatenator (if multiple)'),
    '#type' => 'select',
    '#options' => array(',' => ', (AND)', '+' => '+ (OR)'),
    '#default_value' => $conf['concatenator'],
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
    '#description' => t("When the resulting value is multiple valued and the context is passed on to a view as argument, the value can be concatenated in the form of 1+2+3 (for OR) or 1,2,3 (for AND)."),
  );
  return $form;
}

function entity_entity_property_edit_form_validate($form, &$form_state) {
  $context_key = $form_state['values']['context'];
  $context = $form_state['contexts'][$context_key];
  $entity_type = $context->type[2];

  try {
    $all_properties = entity_get_all_property_info($entity_type);
    $wrapper = entity_metadata_wrapper($entity_type, NULL, array('property info' => $all_properties));
    $parts = explode(':', $form_state['values']['selector']);
    foreach ($parts as $part) {
      if (!($wrapper instanceof EntityStructureWrapper || $wrapper instanceof EntityListWrapper)) {
        form_set_error('selector', t('Unable to apply the data selector part %key.'. array('%key' => $part)));
        continue;
      }
      $wrapper = $wrapper->get($part);
    }
    $type = entity_entity_property_map_data_type($wrapper->type());
    $form_state['conf']['target_context'] = $type;
  }
  catch (EntityMetadataWrapperException $e) {
    form_set_error('selector', t('Unable to apply the data selector on entity type %type. @reason', array('@reason' => $e->getMessage(), '%type' => $entity_type)));
  }

  // Auto-generate a sane identifier.
  if ($form_state['values']['identifier'] == $form['identifier']['#default_value']) {
    $form_state['values']['identifier'] = 'Entity property ' . $entity_type . ':' . check_plain($form_state['values']['selector']);
  }
}

/**
 * Maps an entity-property data type to ctools types.
 */
function entity_entity_property_map_data_type($type) {
  // Remove list<> wrappers from types.
  while ($item_type = entity_property_list_extract_type($type)) {
    $type = $item_type;
  }
  // Massage data type of entites to c
  if (entity_get_info($type)) {
    $type = "entity:$type";
  }
  if ($type == 'text') {
    $type = 'string';
  }
  return $type;
}
