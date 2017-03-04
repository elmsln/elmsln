<?php

/**
 * @file
 * Drush integration for the schemaorg module.
 */

/**
 * Implements hook_drush_command().
 */
function schemaorg_drush_command() {
  $items['schemaorg-json'] = array(
    'description' => dt('Generates JSON from rdfs.schema.org.'),
    'options' => array(
      '--with-comments' => 'Includes comment in the JSON output',
    ),
  );
  return $items;
}

/**
 * JSON output command callback.
 */
function drush_schemaorg_json() {
  $data = json_decode(drupal_http_request('http://schema.rdfs.org/all.json')->data);

  $curated_terms = array();

  foreach ($data as $category => $terms) {
    foreach ($terms as $id => $term) {
      if (drush_get_option('with-comments')) {
        // The value and label keys are what the jQuery UI autocomplete excepts.
        $curated_terms[$category][$id]['value'] = $term->id;
        $curated_terms[$category][$id]['label'] = $term->id . ': ' . $term->comment_plain;
      }
      else {
        $curated_terms[$category][] = $term->id;
      }
    }
  }

  print json_encode($curated_terms);
}
