<?php
/**
 * @file
 * Defines the block admin entry class.
 */

/**
 * Block admin entry class.
 */
class AuthcachePageManagerAdminEntry {

  /**
   * Construct a new block admin entry.
   */
  public function __construct($task_id, $subtask_id, $handler_id, $clients, $defaults) {
    // Copy over defaults.
    foreach ($defaults as $key => $value) {
      $this->{$key} = $value;
    }

    // Add name, description, adminPath and clients properties.
    $task = page_manager_get_task($task_id);
    $handlers = page_manager_load_task_handlers($task, $subtask_id);
    $handler = $handlers[$handler_id];

    $task_name = $task['title'];
    $handler_name = $handler->conf['title'];

    $replacements = array(
      '%task_name' => $task_name,
      '%handler_name' => $handler_name,
    );

    if ($subtask_id) {
      $subtask = page_manager_get_task_subtask($task, $subtask_id);
      $replacements['%subtask_name'] = $subtask['admin title'];
      $this->description = t('Page manager variant %handler_name on task %task_name / subtask %subtask_name', $replacements);
    }
    else {
      $this->description = t('Page manager variant %handler_name on task %task_name', $replacements);
    }

    $this->clients = $clients;

    $this->adminPath = 'admin/structure/pages/nojs/operation/' . page_manager_make_task_name($task_id, $subtask_id) . '/handlers/' . $handler->name . '/content';
  }
}
