<?php

/**
 * @file
 * Handle the 'file view' override task.
 *
 * This plugin overrides file/%file and reroutes it to the page manager, where
 * a list of tasks can be used to service this request based upon criteria
 * supplied by access plugins.
 */

/**
 * Specialized implementation of hook_page_manager_task_tasks().
 */
function file_entity_file_view_page_manager_tasks() {
  return array(
    // This is a 'page' task and will fall under the page admin UI
    'task type' => 'page',
    'title' => t('File template'),
    'admin title' => t('File template'),
    'admin description' => t('When enabled, this overrides the default Drupal behavior for displaying files at <em>file/%file</em>. If you add variants, you may use selection criteria such as file types or user access to provide different views of files. If no variant is selected, the default Drupal file view will be used. This page only affects files viewed as pages, it will not affect files viewed in lists or at other locations. Also please note that if you are using Pathauto, aliases may make a file to be available somewhere else, but as far as Drupal is concerned, they are still at file/%file.'),
    'admin path' => 'file/%file',

    // Menu hooks so that we can alter the file/%file menu entry to point to us.
    'hook menu' => 'file_entity_file_view_menu',
    'hook menu alter' => 'file_entity_file_view_menu_alter',

    // This is task uses 'context' handlers and must implement these to give the
    // handler data it needs.
    'handler type' => 'context',
    'get arguments' => 'file_entity_file_view_get_arguments',
    'get context placeholders' => 'file_entity_file_view_get_contexts',

    // Allow this to be enabled or disabled:
    'disabled' => variable_get('file_entity_file_view_disabled', TRUE),
    'enable callback' => 'file_entity_file_view_enable',
    'access callback' => 'file_entity_file_view_access_check',
  );
}

/**
 * Callback defined by page_manager_file_view_page_manager_tasks().
 *
 * Alter the file view input so that file view comes to us rather than the
 * normal file view process.
 */
function file_entity_file_view_menu_alter(&$items, $task) {
  if (variable_get('file_entity_file_view_disabled', TRUE)) {
    return;
  }

  // Override the node view handler for our purpose.
  $callback = $items['file/%file']['page callback'];
  if ($callback == 'file_entity_view_page' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['file/%file']['page callback'] = 'file_entity_file_view_page';
    $items['file/%file']['file path'] = $task['path'];
    $items['file/%file']['file'] = $task['file'];
  }
  else {
    // automatically disable this task if it cannot be enabled.
    variable_set('file_entity_file_view_disabled', TRUE);
    if (!empty($GLOBALS['page_manager_enabling_file_view'])) {
      drupal_set_message(t('Page manager module is unable to enable file/%file because some other module already has overridden with %callback.', array('%callback' => $callback)), 'error');
    }
  }
}

/**
 * Entry point for our overridden file view.
 *
 * This function asks its assigned handlers who, if anyone, would like
 * to run with it. If no one does, it passes through to File entity's
 * file view, which is file_entity_view_page().
 */
function file_entity_file_view_page($file) {
  // Load my task plugin:
  $task = page_manager_get_task('file_view');

  // Load the account into a context.
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($file));

  // We need to mimic Drupal's behavior of setting the file title here.
  drupal_set_title($file->filename);
  $uri = entity_uri('file', $file);
  // Set the file path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($file));

  $output = ctools_context_handler_render($task, '', $contexts, array($file->fid));
  if ($output != FALSE) {
    return $output;
  }

  $function = 'file_entity_view_page';
  foreach (module_implements('page_manager_override') as $module) {
    $call = $module . '_page_manager_override';
    if (($rc = $call('file_view')) && function_exists($rc)) {
      $function = $rc;
      break;
    }
  }

  // Otherwise, fall back.
  return $function($file);
}

/**
 * Callback to get arguments provided by this task handler.
 *
 * Since this is the file view and there is no UI on the arguments, we
 * create dummy arguments that contain the needed data.
 */
function file_entity_file_view_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'file',
      'identifier' => t('File being viewed'),
      'id' => 1,
      'name' => 'entity_id:file',
      'settings' => array(),
    ),
  );
}

/**
 * Callback to get context placeholders provided by this handler.
 */
function file_entity_file_view_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(page_manager_file_view_get_arguments($task, $subtask_id));
}

/**
 * Callback to enable/disable the page from the UI.
 */
function file_entity_file_view_enable($cache, $status) {
  variable_set('file_entity_file_view_disabled', $status);

  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['page_manager_enabling_file_view'] = TRUE;
  }
}

/**
 * Callback to determine if a page is accessible.
 *
 * @param $task
 *   The task plugin.
 * @param $subtask_id
 *   The subtask id
 * @param $contexts
 *   The contexts loaded for the task.
 * @return
 *   TRUE if the current user can access the page.
 */
function page_manager_file_view_access_check($task, $subtask_id, $contexts) {
  $context = reset($contexts);
  return file_entity_access('view');
}
