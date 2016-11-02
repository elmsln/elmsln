<?php
/**
 * Implements hook_services_resources().
 */
function geocoder_services_resources() {
  return array(
    'geocoder' => array(
      'retrieve' => array(
        'help' => 'Geocode data',
        'file' => array('type' => 'inc', 'module' => 'geocoder', 'name' => 'geocoder.services'),
        'callback' => 'geocoder_services_geocode',
        'access callback' => 'geocoder_services_access',
        'access arguments append' => TRUE,
        'args' => array(
          array(
            'name' => 'handler',
            'type' => 'string',
            'description' => 'The geocoder handler to use - google, gpx, kml etc.',
            'source' => array('path' => '0'),
            'optional' => FALSE,
          ),
          array(
            'name' => 'data',
            'type' => 'string',
            'description' => 'Value to geocode',
            'source' => array('param' => 'data'),
            'optional' => FALSE,
          ),
          array(
            'name' => 'output',
            'type' => 'string',
            'description' => 'Output Format (GPX, WKT, etc.)',
            'source' => array('param' => 'output'),
            'optional' => TRUE,
          ),
        ),
      ),
      'index' => array(
        'help' => 'List Geocoder Capabilities',
        'file' => array('type' => 'inc', 'module' => 'geocoder', 'name' => 'geocoder.services'),
        'callback' => 'geocoder_services_capabilities',
        'access callback' => 'geocoder_services_capabilities_ac', // Always returns TRUE
      ),
    ),
  );
}

function geocoder_services_capabilities_ac() {
  return TRUE;
}

function geocoder_services_access($handler, $data, $output) {
  if ($handler == 'default') {
    $handler == 'json';
  }
  return geocoder_service_check_perms($handler);
}

/**
 * Callback for geocoding service
 *
 * @param string $handler
 * @param string $data
 * @return object
 */
function geocoder_services_geocode($handler, $data, $format = 'default') {
  geophp_load();
  geocoder_service_check_request($handler, $format);

  $geom = geocoder($handler, $data);
  if (!$format || $format == 'default') {
    $result = $geom->out('json');
    return json_decode($result);
  }
  else {
    return $geom->out($format);
  }
}

function geocoder_services_capabilities() {
  geophp_load();

  $handlers = array();
  foreach (geocoder_handler_info() as $hid => $handler) {
    $handlers[$hid] = $handler['title'] . ' - ' . $handler['description'];
  }

  $object = new stdClass();
  $object->handlers = $handlers;
  $object->output = geoPHP::getAdapterMap();
  return $object;
}
