<?php
/**
 * @file
 * schemaorg_person.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function schemaorg_person_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function schemaorg_person_node_info() {
  $items = array(
    'schemaorg_person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('A page representing a person'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_rdf_default_mappings().
 */
function schemaorg_person_rdf_default_mappings() {
  $schemaorg = array();

  // Exported RDF mapping: schemaorg_person
  $schemaorg['node']['schemaorg_person'] = array(
    'rdftype' => array(
      0 => 'schema:Person',
      1 => 'sioc:Item',
      2 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'schema:name',
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
    'url' => array(
      'predicates' => array(
        0 => 'schema:url',
      ),
      'type' => 'rel',
    ),
    'field_schemaorg_jobtitle' => array(
      'predicates' => array(
        0 => 'schema:jobTitle',
      ),
    ),
    'field_schemaorg_affiliation' => array(
      'predicates' => array(
        0 => 'schema:affiliation',
      ),
    ),
    'field_schemaorg_photo' => array(
      'predicates' => array(
        0 => 'schema:image',
      ),
      'type' => 'rel',
    ),
  );

  return $schemaorg;
}
