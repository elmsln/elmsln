<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager term view tasks.
 */
class AuthcachePageManagerTermViewTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Adapted from page_manager term_view.inc.
   *
   * @see page_manager_term_view_page()
   */
  protected function taskContext(array $page_arguments = array()) {
    $term = array_shift($page_arguments);
    $depth = array_shift($page_arguments);

    $contexts = ctools_context_handler_get_task_contexts($this->task, '', array($term, $depth));

    return array(
      'context' => $contexts,
      'arguments' => array($term->tid),
    );
  }
}
