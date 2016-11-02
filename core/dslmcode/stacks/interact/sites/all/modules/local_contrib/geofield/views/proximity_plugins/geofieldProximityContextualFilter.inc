<?php

/**
 * @file
 * Contains geofieldProximityContextualFilter.
 */

class geofieldProximityContextualFilter extends geofieldProximityBase implements geofieldProximityPluginInterface {

  public function getSourceValue($views_plugin) {
    $contextualFilter = $views_plugin->view->display_handler->get_handler('argument', 'field_geofield_distance');
    if (isset($contextualFilter->view->argument['field_geofield_distance'])) {
      $argument = $contextualFilter->view->argument['field_geofield_distance'];
      return $contextualFilter->parseArg($argument);
    }
    return FALSE;
  }
}