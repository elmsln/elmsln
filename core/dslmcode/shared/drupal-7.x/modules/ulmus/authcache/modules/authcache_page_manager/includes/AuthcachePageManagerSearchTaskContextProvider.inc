<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager search tasks.
 */
class AuthcachePageManagerSearchTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Copied directly from page_manager search.inc.
   *
   * @see page_manager_search_page()
   */
  protected function taskContext(array $page_arguments = array()) {
    // We have to remove the $type.
    $type = array_shift($page_arguments);

    // And implode() it all back together.
    $keys = $page_arguments ? implode('/', $page_arguments) : '';

    // Allow other modules to alter the search keys.
    drupal_alter(array('search_keys', 'search_' . $type . '_keys'), $keys);

    // Load my task plugin.
    $subtask = page_manager_get_task_subtask($this->task, $type);
    $contexts = ctools_context_handler_get_task_contexts($this->task, $subtask, array($keys));

    return array(
      'context' => $contexts,
      'arguments' => array($keys),
    );
  }
}
