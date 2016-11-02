<?php

/**
 * Implements hook_rules_action_info().
 */
function geofield_rules_action_info() {
  return array(
    'geofield_create_values' => array(
      'base' => 'geofield_rules_create_values',
      'label' => t('Create geofield values from lat/lon'),
      'group' => t('Geofield'),
      'parameter' => array(
        'lat' => array('type' => 'decimal', 'label' => t('Latitude')),
        'lon' => array('type' => 'decimal', 'label' => t('Longitude')),
      ),
      'provides' => array(
        'geofield' => array(
          'label' => t('Geofield value'),
          'type' => 'geofield',
        ),
      ),
    ),
  );
}

/**
 * Rules action for creating geofield values from lat/lon.
 */
function geofield_rules_create_values($lat, $lon) {
  $geometry = new Point($lon, $lat);
  $value = geofield_get_values_from_geometry($geometry);
  return array(
    'geofield' => $value
  );
}
