<?php
/**
 * @file
 * Defines context provider collecting page manager context from path.
 */

/**
 * Collect arguments and contexts from current menu router item path.
 *
 * Use this context provider when rendering page manager page tasks.
 */
class AuthcachePageManagerPageTaskContextProvider extends AuthcachePageManagerDefaultTaskContextProvider {
  /**
   * {@inheritdoc}
   *
   * Copied directly from page_manager page.inc.
   *
   * @see page_manager_page_execute()
   */
  protected function taskContext(array $page_arguments = array()) {
    $page = page_manager_page_load($this->subtaskId);

    // Turn the contexts into a properly keyed array.
    $contexts = array();
    $args = array();
    foreach ($page_arguments as $count => $arg) {
      if (is_object($arg) && get_class($arg) === 'ctools_context') {
        $contexts[$arg->id] = $arg;
        $args[] = $arg->original_argument;
      }
      elseif ($count) {
        $args[] = $arg;
      }
    }

    $count = 0;
    $names = page_manager_page_get_named_arguments($page->path);
    $bits = explode('/', $page->path);

    if ($page->arguments) {
      foreach ($page->arguments as $name => $argument) {
        // Optional arguments must be converted to contexts too, if they exist.
        if ($bits[$names[$name]][0] === '!') {
          ctools_include('context');
          $argument['keyword'] = $name;
          if (isset($args[$count])) {
            // Hack: use a special argument config variable to learn if we need
            // to use menu_tail style behavior:
            if (empty($argument['settings']['use_tail'])) {
              $value = $args[$count];
            }
            else {
              $value = implode('/', array_slice($args, $count));
            }

            $context = ctools_context_get_context_from_argument($argument, $value);
          }
          else {
            // Make sure there is a placeholder context for missing optional
            // contexts.
            $context = ctools_context_get_context_from_argument($argument, NULL, TRUE);
            // Force the title to blank for replacements.
          }
          if ($context) {
            $contexts[$context->id] = $context;
          }
        }
        $count++;
      }
    }

    return array(
      'context' => $contexts,
      'arguments' => $args,
    );
  }
}
