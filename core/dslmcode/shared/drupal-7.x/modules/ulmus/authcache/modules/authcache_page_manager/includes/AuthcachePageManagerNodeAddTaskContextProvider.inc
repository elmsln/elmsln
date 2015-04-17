<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager node add tasks.
 */
class AuthcachePageManagerNodeAddTaskContextProvider extends AuthcachePageManagerNodeEditTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Adapted from page_manager node_edit.inc.
   *
   * @see page_manager_node_add()
   */
  protected function taskContext(array $page_arguments = array()) {
    global $user;

    $type = array_shift($page_arguments);

    // Initialize settings:
    $node = (object) array(
      'uid' => $user->uid,
      'name' => (isset($user->name) ? $user->name : ''),
      'type' => $type,
      'language' => LANGUAGE_NONE,
    );

    return parent::taskContext($node);
  }
}
