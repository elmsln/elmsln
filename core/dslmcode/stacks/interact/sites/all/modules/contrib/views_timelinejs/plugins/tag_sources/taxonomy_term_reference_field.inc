<?php
/**
 * @file
 * Taxonomy term reference as tag source for TimelineJS.
 */

$plugin = array(
  'name' => t('Taxonomy Term Reference field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'taxonomy_term_reference',
  'callback' => 'views_timelinejs_taxonomy_term_reference_tag',
);

/**
 * Parses taxonomy term reference and returns name as tag.
 *
 * @param array $value
 *   Taxonomy term reference value.
 * @param array $options
 *   Optional configuration; not used.
 *
 * @return string|boolean
 *   String containing tag or boolean FALSE if not found.
 */
function views_timelinejs_taxonomy_term_reference_tag($value, $options = array()) {
  if (isset($value['tid']) && $value['tid'] != '') {
    $tid = $value['tid'];
    $term = taxonomy_term_load($tid);
    return $term->name;
  }
  else {
    return FALSE;
  }
}
