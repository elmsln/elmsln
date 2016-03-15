<?php
/**
 * @file
 * entityform_test.features.inc
 */

/**
 * Implements hook_default_entityform_type().
 */
function entityform_test_default_entityform_type() {
  $items = array();
  $items['simpletest_entityform'] = entity_import('entityform_type', '{
    "type" : "simpletest_entityform",
    "label" : "simpletest_entityform",
    "data" : {
      "draftable" : 1,
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "filtered_html" },
      "submit_button_text" : "",
      "submission_page_title" : "",
      "submission_text" : { "value" : "", "format" : "filtered_html" },
      "submission_show_submitted" : 0,
      "submissions_view" : "entityforms",
      "user_submissions_view" : "user_entityforms",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : { "2" : "2", "1" : 0, "3" : 0 },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : { "value" : "Test Instructions", "format" : "filtered_html" }
    },
    "weight" : "0",
    "rdf_mapping" : [],
    "paths" : []
  }');
  return $items;
}
