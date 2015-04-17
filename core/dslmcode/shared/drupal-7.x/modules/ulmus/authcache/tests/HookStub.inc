<?php
/**
 * @file
 * Defines some helper classes for stubbing and recording hook invocations.
 */

/**
 * Helper class representing a stub-module.
 */
class ModuleStub {
  protected $name;

  /**
   * Construct a new module stub-helper.
   *
   * @param string $name
   *   The name of an existing stub-module, e.g., mymodule_test
   */
  public function __construct($name) {
    $this->name = $name;
  }

  /**
   * Install a stub for a hook-implementation.
   *
   * @param string $hookname
   *   The name of the hook (without the module prefix). E.g. form_alter, if
   *   the stub-module has an implementation of hook_form_alter.
   *
   * @param any $return
   *   The result which should be returned when the hook is invoked.
   *
   * @return HookStubProxy
   *   A proxy object representing the stubbed hook.
   */
  public function hook($hookname, $return = NULL) {
    return HookStub::on($this->name . '_' . $hookname, $return);
  }
}

/**
 * (Internal) helper class representing a stub-hook.
 */
class HookStubProxy {
  protected $hookname;

  /**
   * Construct new stubbed hook.
   *
   * Note: Do not instantiate hook proxies directly but use StubModule::hook().
   *
   * @param string $hookname
   *   The fully qualified function name (including module prefix).
   */
  public function __construct($hookname) {
    $this->hookname = $hookname;
  }

  /**
   * Enable recording of invocations.
   *
   * @param any $return
   *   The result which should be returned when the hook is invoked.
   *
   * @return HookStubProxy
   *   A proxy object representing the stubbed hook.
   */
  public function on($return = NULL) {
    return HookStub::on($this->hookname, $return);
  }

  /**
   * Disable recording of invocations.
   *
   * @return HookStubProxy
   *   A proxy object representing the stubbed hook.
   */
  public function off() {
    return HookStub::off($this->hookname);
  }

  /**
   * Record one invocation.
   *
   * @return any
   *   A value specified by HookStubProxy::on().
   */
  public function record($args) {
    return HookStub::record($this->hookname, $args);
  }

  /**
   * Verify invocations.
   *
   * @param callable $checkfunc
   *   Use this function to test invocation expectations.
   * @param string $message
   *   A reference to a string for the validation message.
   *
   * @return bool
   *   Return TRUE when expectations are met, FALSE otherwise.
   */
  public function verify($checkfunc, &$message) {
    return HookStub::verify($this->hookname, $checkfunc, $message);
  }

  /**
   * Return the name of the stubbed function.
   *
   * @return string
   *   Fully qualified function this object represents.
   */
  public function hookname() {
    return $this->hookname;
  }

  /**
   * Return the recorded invocations.
   *
   * @return array
   *   An array of arrays. Each inner array representing the parameter list
   *   passed to one invocation.
   */
  public function invocations() {
    return HookStub::invocations($this->hookname);
  }
}

/**
 * Static methods for keeping track of enabled hooks and invocations.
 */
class HookStub {
  protected $hookname;
  protected $invocations;
  protected $return;

  /**
   * Construct new stub recorderd.
   */
  public function __construct($hookname, $return = NULL) {
    $this->hookname = $hookname;
    $this->invocations = array();
    $this->return = $return;
  }

  /**
   * Enable a stubbed-function.
   *
   * @param string $hookname
   *   The fully qualified name of a function in a stub-module.
   *
   * @param any $return
   *   The result which should be returned when the hook is invoked.
   *
   * @return HookStubProxy
   *   A proxy object representing the stubbed hook.
   */
  public static function on($hookname, $return = NULL) {
    variable_set('hookstub_' . $hookname, new HookStub($hookname, $return));
    return new HookStubProxy($hookname);
  }

  /**
   * Disable recording of invocations.
   *
   * @param string $hookname
   *   The fully qualified name of a function in a stub-module.
   *
   * @return HookStubProxy
   *   A proxy object representing the stubbed hook.
   */
  public static function off($hookname) {
    variable_del('hookstub_' . $hookname);
  }

  /**
   * Record one invocation.
   *
   * @param string $hookname
   *   The fully qualified name of a function in a stub-module.
   *
   * @return any
   *   A value specified by HookStub::on().
   */
  public static function record($hookname, $args) {
    if (($stub = variable_get('hookstub_' . $hookname))) {
      $stub->invocations[] = $args;
      variable_set('hookstub_' . $hookname, $stub);
      return $stub->return;
    }
  }

  /**
   * Return the recorded invocations.
   *
   * @param string $hookname
   *   The fully qualified name of a function in a stub-module.
   *
   * @return array
   *   An array of arrays. Each inner array representing the parameter list
   *   passed to one invocation.
   */
  public static function invocations($hookname) {
    if (($stub = variable_get('hookstub_' . $hookname))) {
      return $stub->invocations;
    }
  }

  /**
   * Verify invocations.
   *
   * @param string $hookname
   *   The fully qualified name of a function in a stub-module.
   *
   * @param callable $checkfunc
   *   Use this function to test invocation expectations.
   *
   * @param string $message
   *   A reference to a string for the validation message.
   *
   * @return bool
   *   Return TRUE when expectations are met, FALSE otherwise.
   */
  public static function verify($hookname, $checkfunc, &$message) {
    if (($stub = variable_get('hookstub_' . $hookname))) {
      if (!isset($checkfunc)) {
        $checkfunc = HookStub::once();
      }
      return $checkfunc($stub->invocations, $message);
    }
    $message .= ' ' . t('No information available.');
  }

  /**
   * Returns a verifyier which succeeds when a hook was invoked at least once.
   */
  public static function any() {
    // Necessary until #1272900 lands
    // @ignore style_function_spacing
    return function($invocations, &$message) {
      $message = format_string('Expecting any number of invocations, got @actual.', array(
        '@actual' => count($invocations),
      ));
      return count($invocations) > 0;
    };
  }

  /**
   * Returns a verifyier which succeeds when a hook never was invoked.
   */
  public static function never() {
    return static::times(0);
  }

  /**
   * Returns a verifyier which succeeds when a hook was invoked exactly once.
   */
  public static function once() {
    return static::times(1);
  }

  /**
   * Returns a verifyier which succeeds when a hook was invoked exactly n times.
   *
   * @param int $times
   *   Number of times this hook is expected to be invoked.
   */
  public static function times($times) {
    // Necessary until #1272900 lands
    // @ignore style_function_spacing
    return function($invocations, &$message) use ($times) {
      $message = format_plural($times, 'Expecting one invocation, got @actual.', 'Expecting @expected invocations, got @actual.', array(
        '@expected' => $times,
        '@actual' => count($invocations),
      ));
      return count($invocations) === $times;
    };
  }

  /**
   * Returns a verifyier which succeeds when arguments match.
   *
   * @param array $args
   *   A list of expected arguments
   * @param int $invoc
   *   The invocation (starting from 0 for the first).
   */
  public static function args($args, $invoc = 0) {
    // Necessary until #1272900 lands
    // @ignore style_function_spacing
    return function($invocations, &$message) use ($args, $invoc) {
      $message = t('On invocation number @invoc, expected @this and got @that.', array(
        '@invoc' => $invoc,
        '@this' => var_export($args, TRUE),
        '@that' => var_export($invocations[$invoc], TRUE),
      ));
      return $invocations[$invoc] === $args;
    };
  }
}
