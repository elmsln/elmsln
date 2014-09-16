<?php
/**
* This plugin array is more or less self documenting
*/
$plugin = array(
  // the title in the admin
  'title' => t('Quiz take pane'),
  'single' => TRUE,
  'render callback' => 'quiz_take_pane_content_type_render',
  'category' => array(t('Quiz'), -9),
//  'edit form' => 'quiz_take_pane_content_type_edit_form',
  'description' => t('Quiz take pane description.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);


/**
* Run-time rendering of the body of the block (content type)
* See ctools_plugin_examples for more advanced info
*/
function quiz_take_pane_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  if (!empty($context) && empty($context->data)) {
    return;
  }
  $node = isset($context->data) ? clone($context->data) : NULL;
  $block = new stdClass();

  if (empty($node)) {
    $block->delta   = 'placeholder';
    $block->title = t('Placeholder title.');
    $block->content = t('Placeholder content goes here.');
    return $block;
  }

  if (!quiz_take_access($node)) {
    return;
  }

  $block->module = 'node';
  $block->delta = $node->nid;

  //drupal_alter('quiz_take', $node);
  if (isset($node->rendered_content)) {
    $block->content = $node->rendered_content;
  } else {
    $block->content = quiz_take_quiz($node);
  }

  return $block;
}
