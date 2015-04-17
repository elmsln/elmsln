<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager user edit tasks.
 */
class AuthcachePageManagerUserEditTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Copied directly from page_manager user_edit.inc.
   *
   * @see page_manager_user_edit_page()
   */
  protected function taskContext(array $page_arguments = array()) {
    $account = array_shift($page_arguments);
    $category = array_shift($page_arguments);

    // Store the category on the user for later usage.
    $account->user_category = isset($category) ? $category : 'account';

    $contexts = ctools_context_handler_get_task_contexts($this->task, '', array($account));

    return array(
      'context' => $contexts,
      'arguments' => array($account->uid),
    );
  }
}
