<?php
/**
 * @file
 * Defines AuthcacheP13nSettingBuilder.
 */

/**
 * Content builder for personalized Drupal.settings.
 */
class AuthcacheP13nSettingBuilder implements AuthcacheP13nContentBuilderInterface, AuthcacheP13nRequestValidatorInterface {
  /**
   * A list of settings keyed by parameter name.
   */
  protected $settings;

  /**
   * Construct new instance.
   *
   * @param array $settings
   *   List of key-value pairs where the key is a setting-id and the value a
   *   record with the following entries:
   *   - renderer: A AuthcacheP13nSetting instance
   *   - target: A string specifying the target Drupal.setting key.
   *   - validator: (optional) an AuthcacheP13nSettingValidator instance
   *   - access: (optional) an AuthcacheP13nSettingAccess instance
   */
  public function __construct($settings) {
    $this->settings = $settings;
  }

  /**
   * {@inheritdoc}
   */
  public function validate($req) {
    // Run setting request validators.
    if (!empty($req['a']) && is_array($req['a'])) {
      foreach ($req['a'] as $paramname => $params) {
        if (!empty($this->settings[$paramname]['validator'])) {
          $req['a'][$paramname] = $this->settings[$paramname]['validator']->validate($params);
        }
      }
    }

    return $req;
  }

  /**
   * {@inheritdoc}
   */
  public function build($req, $context) {
    global $user;

    $data = array();
    foreach ($this->settings as $paramname => $setting) {
      $params = isset($req['a'][$paramname]) ? $req['a'][$paramname] : NULL;

      // Run access check.
      if (!empty($setting['access']) && !$setting['access']->check($user, $params, $context)) {
        throw new AuthcacheP13nRequestAccessDenied();
      }

      // Render result.
      $data[] = array(
        $setting['target'] => $setting['renderer']->get($params, $context),
      );
    }

    // Merge and return result of all settings.
    return drupal_array_merge_deep_array($data);
  }
}
