<?php
/**
 * @file
 * ecd_entityforms.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ecd_entityforms_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_entityform_type().
 */
function ecd_entityforms_default_entityform_type() {
  $items = array();
  $items['course_access_request'] = entity_import('entityform_type', '{
    "type" : "course_access_request",
    "label" : "Course Access Request",
    "data" : {
      "draftable" : 0,
      "draft_redirect_path" : "",
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "plain_text" },
      "submit_button_text" : "",
      "submit_confirm_msg" : "",
      "your_submissions" : "",
      "disallow_resubmit_msg" : "",
      "delete_confirm_msg" : "",
      "page_title_view" : "",
      "preview_page" : 0,
      "submission_page_title" : "",
      "submission_text" : { "value" : "", "format" : "plain_text" },
      "submission_show_submitted" : 0,
      "submissions_view" : "default",
      "user_submissions_view" : "default",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : {
        "166149871" : "166149871",
        "30037204" : "30037204",
        "1" : 0,
        "2" : 0,
        "6065076" : 0,
        "135574917" : 0,
        "66784200" : 0,
        "67296478" : 0,
        "75987638" : 0,
        "76550217" : 0
      },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : {
        "value" : "Using this form you can give someone access to courses in ELMSLN",
        "format" : "plain_text"
      }
    },
    "weight" : "0",
    "paths" : []
  }');
  $items['system_access_request'] = entity_import('entityform_type', '{
    "type" : "system_access_request",
    "label" : "System Access Request",
    "data" : {
      "draftable" : 0,
      "draft_redirect_path" : "",
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "plain_text" },
      "submit_button_text" : "",
      "submit_confirm_msg" : "",
      "your_submissions" : "",
      "disallow_resubmit_msg" : "",
      "delete_confirm_msg" : "",
      "page_title_view" : "",
      "preview_page" : 0,
      "submission_page_title" : "",
      "submission_text" : { "value" : "", "format" : "plain_text" },
      "submission_show_submitted" : 0,
      "submissions_view" : "default",
      "user_submissions_view" : "default",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : {
        "166149871" : "166149871",
        "30037204" : "30037204",
        "1" : 0,
        "2" : 0,
        "6065076" : 0,
        "135574917" : 0,
        "66784200" : 0,
        "67296478" : 0,
        "75987638" : 0,
        "76550217" : 0
      },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : {
        "value" : "Using this form you can give someone access to courses in ELMSLN",
        "format" : "plain_text"
      }
    },
    "weight" : "0",
    "paths" : []
  }');
  return $items;
}
