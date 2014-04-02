<?php
/**
 * @file
 * Variable Realm controller class definition.
 */


/**
 * Realm controller for environment realms.
 */
class EnvironmentVariableRealmController extends VariableRealmDefaultController {
  /**
   * Implementation of VariableRealmControllerInterface::getAvailableVariables().
   */
  public function getAvailableVariables() {
    $variables = array();
    foreach (variable_get_info() as $name => $variable) {
      $variables[] = $name;
    }
    return $variables;
  }
  /**
   * Implementation of VariableRealmControllerInterface::getDefaultKey().
   */
  public function getDefaultKey() {
    $env = environment_indicator_default_environment_indicator_environment();
    $env = reset($env);
    return $env->machine;
  }
  /**
   * Implementation of VariableRealmControllerInterface::getRequestKey().
   */
  public function getRequestKey() {
    $env = environment_indicator_get_active();
    return $env['machine'];
  }
  /**
   * Implementation of VariableRealmControllerInterface::getAllKeys().
   */
  public function getAllKeys() {
    $environment_list = array();
    foreach (environment_indicator_get_all() as $machine => $environment) {
      $environment_list[$machine] = $environment->name;
    }
    return $environment_list;
  }
}
