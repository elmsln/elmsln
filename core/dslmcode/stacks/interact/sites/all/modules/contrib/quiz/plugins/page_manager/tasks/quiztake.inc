<?php

/**
 * Specialized implementation of hook_page_manager_task_tasks(). See api-task.html for
 * more information.
 */
function quiz_quiztake_page_manager_tasks() {

  return array(
    // This is a 'page' task and will fall under the page admin UI
    'task type' => 'page',

    'title' => t('Take quiz'),
    'admin title' => t('The take page for quiz.'),
    'admin description' => t('When enabled, this overrides the default view at node/%node/take'),
    'admin path' => 'node/%node/take',

    // Menu hooks so that we can alter the node/%node menu entry to point to us.
    'hook menu alter' => 'quiz_quiztake_menu_alter',

    // This is task uses 'context' handlers and must implement these to give the
    // handler data it needs.
    'handler type' => 'context',
    'get arguments' => 'quiz_quiztake_get_arguments',
    'get context placeholders' => 'quiz_quiztake_get_contexts',

    // Allow this to be enabled or disabled:
    'disabled' => variable_get('quiz_quiztake_disabled', TRUE),
    'enable callback' => 'quiz_quiztake_enable',
  );
}

/**
 * Callback defined by quiz_quiztake_page_manager_tasks().
 *
 * Alter menu item so that node/%node/take comes here.
 */
function quiz_quiztake_menu_alter(&$items, $task) {

  if (variable_get('quiz_quiztake_disabled', TRUE)) {
    return;
  }

  $callback = $items['node/%node/take']['page callback'];
  // Override the node edit handler for our purpose.
  if ($callback == 'quiz_take' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['node/%node/take']['page callback'] = 'quiz_quiztake';
    $items['node/%node/take']['file path'] = $task['path'];
    $items['node/%node/take']['file'] = $task['file'];
  }
  else {
    //variable_set('quiz_quiztake_disabled', TRUE);
    if (!empty($GLOBALS['page_manager_enabling_quiz'])) {
      drupal_set_message(t('Page manager module is unable to enable Qui take Node because some other module already has overridden with %callback.', array('%callback' => $callback)), 'warning');
    }
    return;
  }
}

/**
 * Entry point for our overridden quiz.
 *
 * This function asks its assigned handlers who, if anyone, would like
 * to run with it. If no one does, it passes through to the main node draft page.
 */
function quiz_quiztake($node) {
  // Load my task plugin
  $task = page_manager_get_task('quiztake');

  // Load the node into a context.
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($node));

  $output = ctools_context_handler_render($task, '', $contexts, array($node->nid));
  if ($output !== FALSE) {
    return $output;
  }

  module_load_include('inc', 'quiz', 'quiz.node');
  $function = 'quiz_take';
  foreach (module_implements('page_manager_override') as $module) {
    $call = $module . '_page_manager_override';
    if (($rc = $call('quiz')) && function_exists($rc)) {
      $function = $rc;
      break;
    }
  }

  // Otherwise, fall back.
  return $function($node);
}

/**
 * Callback to enable/disable the page from the UI.
 */
function quiz_quiztake_enable($cache, $status) {
  variable_set('quiz_quiztake_disabled', $status);
  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['page_manager_enabling_quiz'] = TRUE;
  }
}

/**
 * Callback to get arguments provided by this task handler.
 *
 * Since this is the node view and there is no UI on the arguments, we
 * create dummy arguments that contain the needed data.
 */
function quiz_quiztake_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'node',
      'identifier' => t('Node being taken'),
      'id' => 1,
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
  );
}

/**
 * Callback to get context placeholders provided by this handler.
 */
function quiz_quiztake_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(page_manager_node_view_get_arguments($task, $subtask_id));
}
