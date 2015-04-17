<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager user tasks.
 */
class AuthcachePageManagerUserTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Load user account as context.
   *
   * @see blog_page_user()
   */
  protected function taskContext(array $page_arguments = array()) {
    $account = array_shift($page_arguments);

    $contexts = ctools_context_handler_get_task_contexts($this->task, '', array($account));

    return array(
      'context' => $contexts,
      'arguments' => array($account->uid),
    );
  }
}
