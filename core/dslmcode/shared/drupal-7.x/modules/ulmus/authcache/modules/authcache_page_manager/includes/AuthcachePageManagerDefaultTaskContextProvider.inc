<?php
/**
 * @file
 * Defines basic context provider for page manager tasks.
 */

/**
 * Base class for page manager task context providers.
 */
class AuthcachePageManagerDefaultTaskContextProvider implements AuthcacheP13nContextProviderInterface {
  protected $taskId;
  protected $subtaskId;
  protected $handlerId;
  protected $task;

  /**
   * Construct new base task context provider.
   */
  public function __construct($task_id, $subtask_id, $handler_id) {
    $this->taskId = $task_id;
    $this->subtaskId = $subtask_id;
    $this->handlerId = $handler_id;
  }

  /**
   * {@inheritdoc}
   */
  public function get($params) {
    ctools_include('context');
    ctools_include('context-task-handler');

    // Load task.
    $this->task = page_manager_get_task($this->taskId);

    // Load base context and arguments.
    $router_item = menu_get_item();
    $env = $this->taskContext($router_item['page_arguments']);

    // Augment base context with handler context.
    $handlers = page_manager_load_task_handlers($this->task, $this->subtaskId);
    $env['context'] = ctools_context_handler_get_handler_contexts($env['context'], $handlers[$this->handlerId]);

    return $env;
  }

  /**
   * Return task context and arguments.
   *
   * @param array $page_arguments
   *   Arguments retrieved from the current router item.
   *
   * @return array
   *   Associative array containing the following keys and values:
   *   - context: An array of page manager contexts
   *   - arguments: An array of page manager arguments
   */
  protected function taskContext(array $page_arguments = array()) {
    return array(
      'context' => array(),
      'arguments' => array(),
    );
  }
}
