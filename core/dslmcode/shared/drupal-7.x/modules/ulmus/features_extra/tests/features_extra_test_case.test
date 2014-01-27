<?php

/**
 * @file
 * Base class for Features Extra tests.
 */

class FeaturesExtraTestCase extends DrupalWebTestCase {
  // The installation profile that will be used to run the tests.
  protected $profile = 'testing';

  public function setUp() {
    // Enable the test feature in addition to given modules.
    $modules = func_get_args();
    $modules = !empty($modules[0]) ? $modules[0] : array();
    $modules[] = 'features_extra_test';
    parent::setUp($modules);

    $admin_user = $this->drupalCreateUser(array('administer features'));
    $this->drupalLogin($admin_user);
  }

  /**
   * Test if components can be reverted and that overrides are detected.
   */
  protected function revertComponents($components = array()) {
    module_load_include('inc', 'features', 'features.export');

    foreach ($components as $component) {
      // Ensure that the component is in its default state initially.
      $states = features_get_component_states(array('features_extra_test'), FALSE, TRUE);
      $this->assertTrue($states['features_extra_test'][$component] === FEATURES_DEFAULT, t('@component state: Default.', array('@component' => $component)));

      // Override component and test that Features detects the override.
      $callback = "override_{$component}";
      $this->$callback();
      $states = features_get_component_states(array('features_extra_test'), FALSE, TRUE);
      $this->assertTrue($states['features_extra_test'][$component] === FEATURES_OVERRIDDEN, t('@component state: Overridden.', array('@component' => $component)));
    }

    // Revert component and ensure that component has reverted.
    features_revert(array('features_extra_test' => $components));
    foreach ($components as $component) {
      $states = features_get_component_states(array('features_extra_test'), FALSE, TRUE);
      $this->assertTrue($states['features_extra_test'][$component] === FEATURES_DEFAULT, t('@component reverted successfully.', array('@component' => $component)));
    }
  }
}
