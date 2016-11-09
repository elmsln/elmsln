<?php

/**
 * @file
 *   Contains geofieldProximityPluginInterface and geofieldProximityBase.
 */

interface geofieldProximityPluginInterface {
  /**
   * All methods in geofieldProximityPluginInterface maps directly to a 
   * method in a views_handler class, expect for 'getSourceValue,' which
   * is primarily called in the 'query' method, but also in other instances.
   */
  public function option_definition(&$options, $views_plugin);
  public function options_form(&$form, &$form_state, $views_plugin);
  public function options_validate(&$form, &$form_state, $views_plugin);
  public function value_form(&$form, &$form_state, $views_plugin);
  public function value_validate(&$form, &$form_state, $views_plugin);
  public function getSourceValue($views_plugin);
}

class geofieldProximityBase implements geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin) {
    
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    
  }

  public function options_validate(&$form, &$form_state, $views_plugin) {

  }

  public function value_form(&$form, &$form_state, $views_plugin) {
  }

  public function value_validate(&$form, &$form_state, $views_plugin) {
    
  }

  public function getSourceValue($views_plugin) {
    return array(
      'latitude' => 0,
      'longitude' => 0,
    );
  }
}
