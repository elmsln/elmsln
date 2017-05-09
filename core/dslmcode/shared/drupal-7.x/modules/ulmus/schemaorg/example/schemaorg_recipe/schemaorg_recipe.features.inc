<?php
/**
 * @file
 * schemaorg_recipe.features.inc
 */

/**
 * Implements hook_rdf_default_mappings().
 */
function schemaorg_recipe_rdf_default_mappings() {
  $schemaorg = array();

  // Exported RDF mapping: recipe
  $schemaorg['node']['recipe'] = array(
    'rdftype' => array(
      0 => 'schema:Recipe',
      1 => 'v:Recipe',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'schema:name',
      ),
    ),
    'recipe_instructions' => array(
      'predicates' => array(
        0 => 'v:instructions',
      ),
    ),
    'recipe_description' => array(
      'predicates' => array(
        0 => 'v:summary',
      ),
    ),
    'recipe_preptime' => array(
      'predicates' => array(
        0 => 'v:prepTime',
      ),
    ),
    'recipe_cooktime' => array(
      'predicates' => array(
        0 => 'v:cookTime',
      ),
    ),
    'recipe_totaltime' => array(
      'predicates' => array(
        0 => 'v:totalTime',
      ),
    ),
    'recipe_yield' => array(
      'predicates' => array(
        0 => 'v:yield',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'schema:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'field_schemaorg_image' => array(
      'predicates' => array(
        0 => 'schema:photo',
      ),
      'type' => 'rel',
    ),
    'url' => array(
      'predicates' => array(
        0 => 'schema:url',
      ),
      'type' => 'rel',
    ),
  );

  return $schemaorg;
}
