<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager comment reply tasks.
 */
class AuthcachePageManagerCommentReplyTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Adapted from page_manager comment_reply.inc.
   *
   * @see page_manager_comment_reply_page()
   */
  protected function taskContext(array $page_arguments = array()) {
    $node = array_shift($page_arguments);
    $pid = array_shift($page_arguments);

    $contexts = ctools_context_handler_get_task_contexts($this->task, '', array($node, $pid));

    return array(
      'context' => $contexts,
      'arguments' => array($node->nid, $pid),
    );
  }
}
