<?php

/**
 * This plugin array is more or less self documenting
 */

$plugin = array(
  // the title in the admin
  'title' => t('@quiz Pane: Take', array('@quiz' => QUIZ_NAME)),
  'single' => TRUE,
  'render callback' => 'quiz_quiztake_pane_content_type_render',
  'category' => array(t('Quiz'), -9),
  'description' => t('The quiz on the referenced node'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function quiz_quiztake_pane_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  if (!empty($context) && empty($context->data)) {
    return;
  }
  $node = isset($context->data) ? clone $context->data : NULL;
  $block = new stdClass();

  if (empty($node)) {
    $block->delta = 'placeholder';
    $block->title = t('Placeholder title.');
    $block->content = t('Placeholder content goes here.');
    return $block;
  }

  if (!quiz_take_access($node)) {
    return;
  }

  $block->module = 'node';
  $block->delta = $node->nid;

  if (isset($node->rendered_content)) {
    $block->content = $node->rendered_content;
  }
  else {
    quiz_take_quiz($node);
    $number = $_SESSION['quiz'][$node->nid]['current'];
    $block->content = quiz_take_question($node, $number);

  }
  return $block;
}
/**
 * Returns the administrative title for a type.
 */
function quiz_quiztake_pane_content_type_admin_title($subtype, $conf, $contexts) {
  $identifier = $contexts->identifier;
  return t('@quiz Pane: Take - ' . $identifier, array('@quiz' => QUIZ_NAME));
}
