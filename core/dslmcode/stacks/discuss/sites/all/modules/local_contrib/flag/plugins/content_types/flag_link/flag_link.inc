<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Flag link'),
  'description' => t('Add a flag link of a certain flag type for entities.'),
  'defaults' => array('flag_name' => ''),
  'content type' => 'flag_flag_link_content_type_info',
);

/**
 * Get the entity content type info.
 */
function flag_flag_link_content_type_info($entity_type) {
  $types = flag_flag_link_content_type_content_types();
  if (isset($types[$entity_type])) {
    return $types[$entity_type];
  }
}

/**
 * Implements hook_PLUGIN_content_type_content_types().
 */
function flag_flag_link_content_type_content_types() {
  $types = &drupal_static(__FUNCTION__);
  if (isset($types)) {
    return $types;
  }

  $types = array();
  $entities = entity_get_info();

  foreach ($entities as $entity_type => $info) {
    $types[$entity_type] = array(
      'title' => t('Flag for @entity_type', array('@entity_type' => $info['label'])),
      'category' => t('Entity'),
      'required context' => new ctools_context_required(t('Entity'), $entity_type),
    );
  }

  return $types;
}

/**
 * Render callback.
 */
function flag_flag_link_content_type_render($subtype, $conf, $args, $context) {
  $flag = flag_get_flag($conf['flag_name']);
  if (!$flag) {
    return;
  }

  if (empty($context->data)) {
    return;
  }

  // Get the ID of the entity.
  list($id,,) = entity_extract_ids($flag->entity_type, $context->data);
  $link = flag_create_link($flag->name, $id);

  if (!$link) {
    return;
  }

  $block = new stdClass();
  $block->module = 'flag';
  $block->title = t('Flag link');
  $block->delta = $flag->name;

  $block->content = $link;
  return $block;
}

/**
 * Form callback.
 */
function flag_flag_link_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $entity_type = $form_state['subtype_name'];
  $options = array();

  foreach (flag_get_flags($entity_type) as $flag) {
    $options[$flag->name] = $flag->title;
  }

  $form['flag_name'] = array(
    '#type' => 'select',
    '#title' => t('Flag name'),
    '#default_value' => $conf['flag_name'],
    '#options' => $options,
    '#description' => t('Select a flag.'),
    '#required' => TRUE,
    '#disabled' => !$options,
  );

  return $form;
}

/**
 * Form submit.
 */
function flag_flag_link_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a flag link.
 */
function flag_flag_link_content_type_admin_title($subtype, $conf) {
  if ($flag = flag_get_flag($conf['flag_name'])) {
    return t('Flag link of @flag', array('@flag' => $flag->title));
  }
}
