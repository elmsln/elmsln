<?php
/**
 * @file
 * Defines setting handler for profile data of currently logged in user.
 */

/**
 * Setting handler for profile data of currently logged in user.
 */
class AuthcacheUserSetting implements AuthcacheP13nSettingInterface {
  protected $properties;

  /**
   * Construct new personalized user setting handler.
   */
  public function __construct(array $properties) {
    $this->properties = drupal_map_assoc($properties);
  }

  /**
   * Return profile data of currently logged in user.
   */
  public function get($params, $context) {
    $data = $this->getUserData();
    return $this->escapeUserData($data);
  }

  /**
   * Load and prepare an array of properties of the currently logged in user.
   */
  protected function getUserData() {
    global $user;

    $data = (array) $user;
    unset($data['pass']);

    return array_intersect_key($data, $this->properties);
  }

  /**
   * Escape user data such that it can be savely displayed by the browser.
   */
  protected function escapeUserData(array $data) {
    array_walk_recursive($data, function (&$value) {
      $value = check_plain($value);
    });

    return $data;
  }
}
