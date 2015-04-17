<?php
/**
 * @file
 * API documentation for the Authcache Page Manager module.
 */

/**
 * Declare context providers for page manager tasks.
 *
 * Return an associative array with page manager task names as keys and a
 * context provider class as value.
 */
function hook_authcache_page_manager_task_context_provider() {
  return array(
    'my_task' => 'MyModuleMyTaskContextProvider',
  );
}

/**
 * Modify context providers declared by other modules.
 */
function hook_authcache_page_manager_task_context_provider_alter(&$task_context_providers) {
}
