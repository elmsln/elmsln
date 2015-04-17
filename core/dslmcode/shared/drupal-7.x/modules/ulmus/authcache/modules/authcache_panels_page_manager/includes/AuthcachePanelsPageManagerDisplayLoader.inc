<?php
/**
 * @file
 * Defines personalization fragment for panel pane.
 */

/**
 * Personalization fragment for panel pane.
 */
class AuthcachePanelsPageManagerDisplayLoader extends AuthcachePanelsAbstractDisplayLoader {
  protected $taskId;
  protected $subtaskId;
  protected $handlerId;

  /**
   * Construct new base task context provider.
   */
  public function __construct($pane_id, $task_id, $subtask_id, $handler_id) {
    parent::__construct($pane_id);

    $this->taskId = $task_id;
    $this->subtaskId = $subtask_id;
    $this->handlerId = $handler_id;
  }

  /**
   * Load the display object.
   */
  protected function loadDisplay() {
    $task = page_manager_get_task($this->taskId);
    $handlers = page_manager_load_task_handlers($task, $this->subtaskId);
    $handler = $handlers[$this->handlerId];
    page_manager_get_task_handler('panel_context');
    return panels_panel_context_get_display($handler);
  }
}
