<?php

/**
 * @file
 * Geofield contextual filter argument handler for Views.
 */

define('GEOFIELD_PROXIMITY_REGEXP_PATTERN', '/[,_ +]+/');
/**
 * The proximity argument may be appended to URL in the following format:
 *   /lat,lon_dist
 * where dist is a positive number representing a circular proximity in either
 * kilometers or miles, as configured through the contextual filter UI.
 */
class geofield_handler_argument_proximity extends views_handler_argument {

  function option_definition() {
    $options = parent::option_definition();
    $options['proximity']['operation'] = array('default' => 'lt');
    $options['proximity']['default_radius'] = array('default' => 100);
    $options['proximity']['radius_unit'] = array('default' => GEOFIELD_KILOMETERS);
    return $options;
  }

  /**
   * Add form elements to select options for this contextual filter.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['proximity'] = array(
      '#type' => 'fieldset',
      '#title' => t('Filter locations by proximity to a reference point'),
      '#description' => t('The reference point is normally apppend to the URL as lat,lon, or if you have the !geocoder module enabled, as a partial address, like "/New York"', array('!geocoder' => l('Geocoder', 'http://drupal.org/project/geocoder'))),
    );
    $form['proximity']['operation'] = array(
      '#type' => 'select',
      '#title' => t('Select locations'),
      '#options' => array(
        'lt' => t('Inside radius'),
        'gt' => t('Outside radius'),
      ),
      '#default_value' => $this->options['proximity']['operation'],
      '#description' => t("Reference point coordinates (<strong>lat,lon</strong>) and <strong>distance</strong> are typically appended to the URL. A fallback may be entered above under <em>Provide default value</em> as either a <em>Fixed value</em> or as <em>PHP Code</em>. <br/>In all cases use this format: <strong>lat,lon distance</strong>. You may omit either <strong>lat,lon</strong> or <strong>distance</strong>. Instead of spaces and comma's, you can use underscores."),
    );
    $form['proximity']['default_radius'] = array(
      '#type' => 'textfield',
      '#title' => t('Default radius'),
      '#size' => 8,
      '#default_value' => $this->options['proximity']['default_radius'],
      '#description' => t("Used if no distance is specified. If left blank <em>Fixed value</em> or <em>PHP Code</em> will be used instead."),
    );
    $form['proximity']['radius_unit'] = array(
      '#type' => 'select',
      '#title' => t('Unit of distance'),
      '#options' => geofield_radius_options(),
      '#default_value' => $this->options['proximity']['radius_unit'],
      '#description' => t('Select the unit of distance.'),
    );
  }

  /**
   * Set up the where clause for the contextual filter argument.
   */
  function query($group_by = FALSE) {
    $lat_lon_dist = array();
    foreach ($this->view->argument as $argument) {
      if ($argument->field == 'field_geofield_distance') {
        // Get and process args.
        $lat_lon_dist = $this->parseArg($argument);
        break;
      }
    }
    // At this point we expect $lat_lon_dist to contain 3 numeric values.
    if (count($lat_lon_dist) < 3) {
      return;
    }
    // Provide hook_geofield_handler_default_argument_alter(), so args may be
    // altered by other modules.
    drupal_alter('geofield_handler_argument_proximity', $this, $lat_lon_dist);

    $table = $this->ensure_my_table() ? $this->table_alias : $this->table;
    $haversine_args = array(
      'earth_radius' => $this->options['proximity']['radius_unit'],
      'origin_latitude'  => $lat_lon_dist['latitude'],
      'origin_longitude' => $lat_lon_dist['longitude'],
      'destination_latitude'  => $table . '.' . $this->definition['field_name'] . '_lat',
      'destination_longitude' => $table . '.' . $this->definition['field_name'] . '_lon',
    );
    $formula = geofield_haversine($haversine_args);
    $operator = ($this->options['proximity']['operation'] == 'gt') ? '>' : '<';
    $where = $formula . $operator . $lat_lon_dist['distance'];

    $this->query->add_where_expression(0, $where);
  }

  function parseArg($argument) {
    // Get and process args. Expect and parse this format: "lat,lon dist".
    if (!empty($this->view->args) && $lat_lon_dist = $this->parseLatLonDistArg($this->view->args[$argument->position])) {
      // Found lat, lon and dist. Can proceed with haversine formula.
      return $lat_lon_dist;
    }
    // The filter argument cannot be parsed as a lat,lon_dist string.
    // Reinterpret this and all trailing arguments as an address of sorts.
    // Examples:
    // "/Sydney/Opera House" or "/sydney opera house"
    // "/Portland" (defaults to "/Portland, Oregon")
    // "/Indiana/Portland" or "/IN/Portland"  or "/Portland IN"

    // Ignore all args up to the one that belongs to this contextual filter.
    $args = array_slice(arg(), $argument->position + 1);

    return $this->parseAddress($args); // may return FALSE
  }

  /**
   * Extract lat,lon and distance from arg and return as array.
   *
   * @param type $arg_string
   * @return array(lat, lon, dist) or FALSE if string could not be parsed.
   */
  function parseLatLonDistArg($arg_string) {
    $args = array_filter(preg_split(GEOFIELD_PROXIMITY_REGEXP_PATTERN, $arg_string));

    foreach ($args as $value) {
      if (!is_numeric($value)) {
        return FALSE;
      }
    }
    if (count($args) == 3) { // Got lat + lon + dist: we're good to go
       // Use next() on $args as after array_filter() we cannot be sure what
       // the element indices are.
        return array(
          'latitude' => reset($args),
          'longitude' => next($args),
          'distance' => next($args));
    }
    // Either distance or lat,lon where omitted. See if we can get these
    // from the defaults.
    $lat = reset($args);
    $lon = next($args);

    if ($lat !== FALSE && $lon !== FALSE) {
      // 2 args received, interpret as lat,lon and take distrance from default
      if ($dist = $this->getDefaultDist()) {
        return array(
          'latitude' => $lat,
          'longitude' => $lon,
          'distance' => $dist);
      }
      return FALSE;
    }
    if ($lat !== FALSE && $lon === FALSE) {
      // 1 arg received, interpret as distance and take lat,lon from default
      $dist = $lat;
      $defaults = $this->getDefaultLatLonDist();
      if (count($defaults) < 2) {
        return FALSE;
      }
      return array(
        'latitude' => reset($defaults),
        'longitude' => next($defaults),
        'distance' => $dist);
    }
    // If we get here, we're dealing with rubbish
    return FALSE;
  }

  /**
   * Interpret URL args as an address with optional distance attached.
   *
   * Return latitude, longitude and distance as an array.
   *
   * @param array of arguments, e.g. result of arg()
   * @return array(lat, lon, dist) or FALSE if arguments could not be parsed.
   */
  private function parseAddress($args) {
    if (empty($args)) {
      return FALSE;
    }
    // Interpret the last arg as a distance, if it is numeric.
    $dist = is_numeric(end($args)) ? array_pop($args) : $this->getDefaultDist();

    $address = implode(', ', $args);

    if (!empty($address) && module_exists('geocoder')) {
      $all_geocoder_engines = array_keys(geocoder_handler_info('text'));
      // Pick Google if defined, otherwise the first in the list.
      $geocoder_engine = in_array('google', $all_geocoder_engines) ? 'google' : reset($all_geocoder_engines);
      if ($geocoded_data = geocoder($geocoder_engine, $address)) {
        return array(
          'latitude' => $geocoded_data->getY(),
          'longitude' => $geocoded_data->getX(),
          'distance' => $dist);
      }
    }
    return FALSE;
  }

  private function getDefaultLatLonDist() {
    $default_arg = $this->get_default_argument();
    return $default_arg
      ? array_filter(preg_split(GEOFIELD_PROXIMITY_REGEXP_PATTERN, $default_arg))
      : array();
  }

  public function getDefaultDist() {
    if (!empty($this->options['proximity']['default_radius'])) {
      return $this->options['proximity']['default_radius'];
    }
    $defaults = $this->getDefaultLatLonDist();
    if (empty($defaults) || count($defaults) == 2) { // expecting either 1 or 3 numbers
      return 100; // last resort default, same as geofield_handler_filter.inc
    }
    return isset($defaults[2]) ? $defaults[2] : reset($defaults);
  }
}
