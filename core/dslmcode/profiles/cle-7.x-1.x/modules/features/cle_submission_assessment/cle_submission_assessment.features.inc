<?php
/**
 * @file
 * cle_submission_assessment.features.inc
 */

/**
 * Implements hook_default_assessment_entity_type().
 */
function cle_submission_assessment_default_assessment_entity_type() {
  $items = array();
  $items['submission_evaluation'] = entity_import('assessment_entity_type', '{
    "type" : "submission_evaluation",
    "label" : "Submission evaluation",
    "weight" : "0"
  }');
  return $items;
}
