<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager node edit tasks.
 */
class AuthcachePageManagerNodeEditTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Adapted from page_manager node_edit.inc.
   *
   * @see page_manager_node_edit()
   */
  protected function taskContext(array $page_arguments = array()) {
    $node = array_shift($page_arguments);

    $contexts = ctools_context_handler_get_task_contexts($this->task, '', array($node));

    return array(
      'context' => $contexts,
      'arguments' => array(isset($node->nid) ? $node->nid : $node->type),
    );
  }
}
