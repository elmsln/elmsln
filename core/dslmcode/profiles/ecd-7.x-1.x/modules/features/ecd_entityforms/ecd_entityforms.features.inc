<?php
/**
 * @file
 * ecd_entityforms.features.inc
 */

/**
 * Implements hook_default_entityform_type().
 */
function ecd_entityforms_default_entityform_type() {
  $items = array();
  $items['ecd_access'] = entity_import('entityform_type', '{
    "type" : "ecd_access",
    "label" : "Access Request",
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
      "roles" : { "2" : "2", "1" : 0, "3" : 0 },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : {
        "value" : "Using this form you can give someone access to parts of ELMSLN.",
        "format" : "plain_text"
      }
    },
    "weight" : "0",
    "paths" : []
  }');
  return $items;
}
