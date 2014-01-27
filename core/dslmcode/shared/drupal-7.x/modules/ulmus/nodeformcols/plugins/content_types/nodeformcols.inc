<?php

/**
 * @file
 * Renders the nodeformcols form in a panel pane. The entire panel is inside the
 * <form> tag. Most of the code is from the CTools form.inc content type.
 */

/**
 * Callback function to supply a list of content types.
 */
function nodeformcols_nodeformcols_ctools_content_types() {
  return array(
    // only provides a single content type
    'single' => TRUE,
    'render last' => TRUE,
    'title' => t('Nodeformcols form'),
    'icon' => 'icon_form.png',
    'description' => t('A complete nodeformcols node form.'),
    'required context' => new ctools_context_required(t('Form'), 'form'),
    'category' => t('Form'),
  );
}

/**
 * Output function for the 'nodeformcols' content type. Outputs a node form
 * as displayed by the nodeformcols module.
 */
function nodeformcols_nodeformcols_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = 'nodeformcols';

  $context->form['#theme'] = 'node_form';
  unset($context->form['#theme_used']);

  if (isset($context->form)) {
    $block->title = $context->form_title;
    if (!empty($context->form_id)) {
      // If this is a form, drupal_render it.
      $block->content = drupal_render($context->form);
    }
    else {
      // Otherwise just spit back what we were given. This is probably an
      // error message or something.
      $block->content = $context->form;
    }
    $block->delta = $context->form_id;
  }
  else {
    $block->title = t('Form');
    $block->content = t('Form goes here.');
    $block->delta   = 'unknown';
  }

  return $block;
}

/**
 * Callback to provide the administrative title of the custom content.
 */
function nodeformcols_nodeformcols_content_type_admin_title($subtype, $conf, $context) {
  return t('Nodeformcols node form');
}

/**
 * Callback to provide administrative info.
 */
function nodeformcols_nodeformcols_content_type_admin_info($subtype, $conf) {
  $block = new stdClass();
  $block->title = t('Affected forms');

  $types = node_type_get_types();
  $forms = array();
  foreach ($types as $type => $description) {
    if (variable_get('nodeformscols_field_placements_' . $type . '_default', FALSE)) {
      $forms[] = $description->name;
    }
  }

  if (!empty($forms)) {
    $block->content = theme('item_list', array('items' => $forms));
  }
  else {
    $block->content = '<p>' . t('No forms are using customized nodeformcols settings.') . '</p>';
  }
  return $block;
}

function nodeformcols_nodeformcols_content_type_edit_form(&$form, &$form_state) {
  // provide a blank form so we have a place to add settings widgets
}
