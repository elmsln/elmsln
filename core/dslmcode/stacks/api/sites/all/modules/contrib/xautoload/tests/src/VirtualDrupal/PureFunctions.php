<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class PureFunctions {

  /**
   * @see module_invoke()
   *
   * @param string $module
   * @param string $hook
   *
   * @return mixed|null
   *
   * @todo Do this in a injectable object instead?
   * @see HookSystem::moduleInvoke()
   */
  static function moduleInvoke($module, $hook) {
    $args = func_get_args();
    assert($module === array_shift($args));
    assert($hook === array_shift($args));
    $function = $module . '_' . $hook;
    if (function_exists($function)) {
      return call_user_func_array($function, $args);
    }
    return NULL;
  }

  /**
   * @see bootstrap_hooks()
   *
   * @return string[]
   */
  static function bootstrapHooks() {
    return array('boot', 'exit', 'watchdog', 'language_init');
  }
}
