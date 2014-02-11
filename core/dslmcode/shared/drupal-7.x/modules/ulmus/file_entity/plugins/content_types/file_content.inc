<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('File content'),
  'description' => t('Display a full file with a view mode.'),
  'required context' => new ctools_context_required(t('File'), 'entity:file'),
  'category' => t('File'),
  'defaults' => array(
    'link' => FALSE,
    'view_mode' => 'teaser',
  ),
);

/**
 * Render the node content.
 */
function file_entity_file_content_content_type_render($subtype, $conf, $panel_args, $context) {
  if (!empty($context) && empty($context->data)) {
    return;
  }

  $file = isset($context->data) ? clone($context->data) : NULL;
  $block = new stdClass();
  $block->module = 'file_entity';
  $block->delta  = $file->fid;

  if (empty($file)) {
    $block->delta   = 'placeholder';
    $block->title = t('File title.');
    $block->content = t('File content goes here.');
  }
  else {
    if (!empty($conf['identifier'])) {
      $node->ctools_template_identifier = $conf['identifier'];
    }

    $block->title = $file->filename;
    $block->content = file_build_content($file, $conf['view_mode']);
  }

  if (!empty($conf['link']) && $file) {
    $block->title_link = entity_uri('file', $file);
  }

  return $block;
}

/**
 * Returns an edit form for this plugin.
 */
function file_entity_file_content_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['link'] = array(
    '#title' => t('Link title to file'),
    '#type' => 'checkbox',
    '#default_value' => $conf['link'],
    '#description' => t('Check this to make the title link to the file.'),
  );

  $entity_info = entity_get_info('file');
  $build_mode_options = array();
  foreach ($entity_info['view modes'] as $mode => $option) {
    $build_mode_options[$mode] = $option['label'];
  }

  $form['view_mode'] = array(
    '#title' => t('View mode'),
    '#type' => 'select',
    '#description' => t('Select a view mode for this node.'),
    '#options' => $build_mode_options,
    '#default_value' => $conf['view_mode'],
  );

  return $form;
}

function file_entity_file_content_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

function file_entity_file_content_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" content', array('@s' => $context->identifier));
}
