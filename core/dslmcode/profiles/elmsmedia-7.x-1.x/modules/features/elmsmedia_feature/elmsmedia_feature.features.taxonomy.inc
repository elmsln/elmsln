<?php
/**
 * @file
 * elmsmedia_feature.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function elmsmedia_feature_taxonomy_default_vocabularies() {
  return array(
    'elmsmedia_tag' => array(
      'name' => 'Tag',
      'machine_name' => 'elmsmedia_tag',
      'description' => 'Tagging media into groups',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
