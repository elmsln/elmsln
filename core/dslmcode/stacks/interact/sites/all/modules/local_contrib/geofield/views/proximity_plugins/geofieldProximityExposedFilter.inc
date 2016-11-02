<?php

/**
 * @file
 * Contains geofieldProximityExposedFilter.
 */

class geofieldProximityExposedFilter extends geofieldProximityBase implements geofieldProximityPluginInterface {
  public function getSourceValue($views_plugin) {
    $exposedFilter = $views_plugin->view->display_handler->get_handler('filter', 'field_geofield_distance');
    if ($exposedFilter) {
      $filterProximityPlugin = geofield_proximity_load_plugin($exposedFilter->options['source']);
      return $filterProximityPlugin->getSourceValue($exposedFilter);
    }
    return FALSE;
  }
}