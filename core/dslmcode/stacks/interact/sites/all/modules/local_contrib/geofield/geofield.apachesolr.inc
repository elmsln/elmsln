<?php

/**
 * Implements hook_apachesolr_field_mappings().
 */
function geofield_apachesolr_field_mappings() {
  $mappings['geofield'] = array(
    'indexing_callback' => 'geofield_apachesolr_indexing_callback',
    'map callback' => 'geofield_apachesolr_map_callback',
    'index_type' => 'geohash',
    'facets' => TRUE,
    'query types' => array('term','geo'),
    'query type' => 'term',
  );
  return $mappings;
}

/**
 * Apachesolr indexing callback for geofield.
 *
 * It will index 2 fields on Solr:
 *
 * 1- Multi-valued field with all geometry(ies) points - as expected.
 * 2- The centroid of the geometry(ies), or the unique point.
 *
 * The single-value field is meant to be used for stats or as a performance
 * improvement in simple queries.
 *
 * The centroid can also be used in simple queries in favor of performance,
 * instead of using the full geometry when it is not necessary.
 *
 * @param object $entity
 * @param string $field_name
 * @param string $index_key
 * @param array $field_info
 * @return array $fields
 */
function geofield_apachesolr_indexing_callback($entity, $field_name, $index_key, $field_info) {
  $fields = array();
  if (!empty($entity->{$field_name})) {
    $values = $entity->{$field_name}[LANGUAGE_NONE];

    // If there is no geometry, just return
    if (empty($values[0]['geom'])) {
      return $fields;
    }

    // Store multiple geometries in a multi-valued Solr field.
    foreach ($values as $delta => $item) {
      $fields[] = array(
        'key' => $index_key,
        'value' => $item['lat'] . ',' . $item['lon'],
      );
    }

    // Store the centroid of multiple geometries or the unique point in a
    // singular Solr field.
    if ($field_info['multiple'] && !empty($values[0])) {

      // If there are multiple values, then get the centroid.
      if (count($values) > 1) {
        // Combine the geometries.
        $geoms = array();
        foreach ($values as $delta => $item) {
          $geoms[] = geoPHP::load($item['geom']);
        }
        $combined_geom = geoPHP::geometryReduce($geoms);
        // Get the centroid.
        $centroid = $combined_geom->getCentroid();
        // Format the value to be indexed.
        $formated_value = $centroid->y() . ',' . $centroid->x();
      }
      // There is no need for additional computation of a single item.
      else {
        $item = reset($values);
        $formated_value = $item['lat'] . ',' . $item['lon'];
      }

      // Get the field info and make it singular.
      $singular_field_info = $field_info;
      $singular_field_info['multiple'] = FALSE;

      $single_key = apachesolr_index_key($singular_field_info);
      $fields[] = array(
        'key' => $single_key,
        'value' => $formated_value,
      );
    }
  }
  return $fields;
}

/**
 * Map of the facet labels.
 *
 * @param array $values
 * @param array $options
 * @return type
 */
function geofield_apachesolr_map_callback(array $values, array $options) {
  $map = array();
  foreach ($values as $key) {
    $map[$key] = substr($key, 1) . 'km';
  }
  return $map;
}
