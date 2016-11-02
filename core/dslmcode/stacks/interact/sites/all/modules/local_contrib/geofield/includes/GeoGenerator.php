<?php

/**
 * @file
 * Helper class for generating random WKT/Geospatial data.
 */

class GeoGenerator {

  /**
   * Helper to generate DD coordinates
   */
  function dd_generate($min, $max, $int = FALSE) {
    $func = 'rand';
    if (function_exists('mt_rand')) {
      $func = 'mt_rand';
    }
    $number = $func($min, $max);
    if ($int || $number === $min || $number === $max) {
      return $number;
    }
    $decimals = $func(1, pow(10, 5)) / pow(10, 5);
    return round($number + $decimals, 5);
  }

  /**
   * Helper to generate a random WKT string
   *
   * Try to keeps values sane, no shape is more than 100km across
   */
  function wkt_generate() {
    $types = array(
      'point',
      'linestring',
      'polygon',
      'multipoint',
      'multilinestring',
      'multipolygon',
    );
    // don't always generate the same type
    shuffle($types);
    $type = $types[0];
    $func = 'wkt_generate_' . $type;
    if (method_exists($this, $func)) {
      $wkt = $this->$func();
      return drupal_strtoupper($type) . ' (' . $wkt . ')';
    }
    return 'POINT (0 0)';
  }

  function random_point() {
    $lon = $this->dd_generate(-180, 180);
    $lat = $this->dd_generate(-84, 84);
    return array($lon, $lat);
  }

  function wkt_generate_point($point = FALSE) {
    $point = $point ? $point : $this->random_point();
    return implode(' ', $point);
  }

  function wkt_generate_multipoint() {
    $num = $this->dd_generate(1, 5, TRUE);
    $start = $this->random_point();
    $points[] = $this->wkt_generate_point($start);
    for ($i = 0; $i < $num; $i += 1) {
      $diff = $this->random_point();
      $start[0] += $diff[0] / 100;
      $start[1] += $diff[1] / 100;
      $points[] = $this->wkt_generate_point($start);
    }
    return implode(', ', $points);
  }

  // make a line that looks like a line
  function wkt_generate_linestring($start = FALSE, $segments = FALSE) {
    $start = $start ? $start : $this->random_point();
    $segments = $segments ? $segments : $this->dd_generate(1, 5, TRUE);
    $points[] = $start[0] . ' ' . $start[1];
    // Points are at most 1km away from each other
    for ($i = 0; $i < $segments; $i += 1) {
      $diff = $this->random_point();
      $start[0] += $diff[0] / 100;
      $start[1] += $diff[1] / 100;
      $points[] = $start[0] . ' ' . $start[1];
    }
    return implode(", ", $points);
  }

  // make a line that looks like a line
  function wkt_generate_multilinestring() {
    $start = $this->random_point();
    $num = $this->dd_generate(1, 3, TRUE);
    $lines[] = $this->wkt_generate_linestring($start);
    for ($i = 0; $i < $num; $i += 1) {
      $diff = $this->random_point();
      $start[0] += $diff[0] / 100;
      $start[1] += $diff[1] / 100;
      $lines[] = $this->wkt_generate_linestring($start);
    }
    return '(' . implode('), (', $lines) . ')';
  }

  function wkt_generate_polygon($start = FALSE, $segments = FALSE) {
    $start = $start ? $start : $this->random_point();
    $segments = $segments ? $segments : $this->dd_generate(2, 4, TRUE);
    $poly = $this->wkt_generate_linestring($start, $segments);
    // close the polygon
    return '(' . $poly . ' , ' . $start[0] . ' ' . $start[1] . ')';
  }

  function wkt_generate_multipolygon() {
    $start = $this->random_point();
    $num = $this->dd_generate(1, 5, TRUE);
    $segments = $this->dd_generate(2, 3, TRUE);
    $poly[] = $this->wkt_generate_polygon($start, $segments);
    for ($i = 0; $i < $num; $i += 1) {
      $diff = $this->random_point();
      $start[0] += $diff[0] / 100;
      $start[1] += $diff[1] / 100;
      $poly[] = $this->wkt_generate_polygon($start, $segments);
    }
    return '(' . implode(', ', $poly) . ')';
  }
}
