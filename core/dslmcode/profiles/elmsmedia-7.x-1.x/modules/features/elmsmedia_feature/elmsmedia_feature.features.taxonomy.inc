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
    'elmsmedia_course' => array(
      'name' => 'Course',
      'machine_name' => 'elmsmedia_course',
      'description' => 'Course this is associated with',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
