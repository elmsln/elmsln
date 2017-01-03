<?php
/**
 * @file
 * assessment_quiz.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function assessment_quiz_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function assessment_quiz_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
