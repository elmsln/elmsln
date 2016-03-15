<?php
/*
 * @file
 * Default Rules
 */
/**
 * Implements hook_default_rules_configuration().
 */
function entityform_notifications_default_rules_configuration() {
  $exported_rules = array();
  $exported_rules['rules_entityform_notification_add_submission'] = '{ "rules_entityform_notification_add_submission" : {
    "LABEL" : "Entityform Notification Add Submission",
    "PLUGIN" : "rule",
    "REQUIRES" : [ "rules" ],
    "USES VARIABLES" : {
      "entityform" : { "label" : "Entityform", "type" : "entityform" },
      "email_body" : { "label" : "Email Body", "type" : "text" },
      "show_submission" : { "label" : "Show Submission", "type" : "boolean" }
    },
    "IF" : [ { "NOT data_is_empty" : { "data" : [ "show-submission" ] } } ],
    "DO" : [
      { "data_set" : {
          "data" : [ "email-body" ],
          "value" : "[email-body:value]\r\n\r\nSubmission:\r\n[entityform:textexport-email]"
        }
      }
    ],
    "PROVIDES VARIABLES" : [ "email_body" ]
  }
}';
  $exported_rules['rules_entityform_notification_email_admin'] = '{ "rules_entityform_notification_email_admin" : {
      "LABEL" : "Entityform Notification Email Admin",
      "PLUGIN" : "rule",
      "TAGS" : [ "entity_rules_entityform_submission" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "entity" : { "label" : "Entity", "type" : "entityform" },
        "continue" : { "label" : "Continue Rules", "type" : "boolean" },
        "email_subject" : { "label" : "Email Subject", "type" : "text" },
        "email_body" : { "label" : "Email Body", "type" : "text" },
        "show_submission" : { "label" : "Show Submission", "type" : "boolean" },
        "to_email" : { "label" : "To Email", "type" : "text" }
      },
      "DO" : [
        { "component_rules_entityform_notifications_email_send" : {
            "entityform" : [ "entity" ],
            "email_address" : [ "to-email" ],
            "show_submission" : [ "show-submission" ],
            "email_subject" : [ "email-subject" ],
            "email_body" : [ "email-body" ]
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "continue" ]
    }
  }';
  $exported_rules['rules_entityform_notification_email_submitter'] = '{ "rules_entityform_notification_email_submitter" : {
      "LABEL" : "Entityform Notification Email Submitter",
      "PLUGIN" : "rule",
      "TAGS" : [ "entity_rules_entityform_submission" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "entity" : { "label" : "Entity", "type" : "entityform" },
        "continue" : { "label" : "Continue Rules", "type" : "boolean" },
        "email_subject" : { "label" : "Email Subject", "type" : "text" },
        "email_body" : { "label" : "Email Body", "type" : "text" },
        "show_submission" : { "label" : "Show Submission", "type" : "boolean" }
      },
      "IF" : [
        { "user_has_role" : { "account" : [ "entity:user" ], "roles" : { "value" : { "2" : "2" } } } }
      ],
      "DO" : [
        { "component_rules_entityform_notifications_email_send" : {
            "entityform" : [ "entity" ],
            "email_address" : [ "entity:user:mail" ],
            "show_submission" : [ "show-submission" ],
            "email_subject" : [ "email-subject" ],
            "email_body" : [ "email-body" ]
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "continue" ]
    }
  }';
  $exported_rules['rules_entityform_notifications_email_send'] = '{ "rules_entityform_notifications_email_send" : {
      "LABEL" : "Entityform Notifications Email Send",
      "PLUGIN" : "rule",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "entityform" : { "label" : "Entityform", "type" : "entityform" },
        "email_address" : { "label" : "Email Address", "type" : "text" },
        "show_submission" : { "label" : "Show submitted data", "type" : "boolean" },
        "email_subject" : { "label" : "Email Subject", "type" : "text" },
        "email_body" : { "label" : "Email Body", "type" : "text" }
      },
      "IF" : [ { "data_is_empty" : { "data" : [ "entityform:draft" ] } } ],
      "DO" : [
        { "component_rules_entityform_notification_add_submission" : {
            "USING" : {
              "entityform" : [ "entityform" ],
              "email_body" : [ "email-body" ],
              "show_submission" : [ "show-submission" ]
            },
            "PROVIDE" : { "email_body" : { "email_body_updated" : "Email Body Updated" } }
          }
        },
        { "mail" : {
            "to" : [ "email-address" ],
            "subject" : [ "email-subject" ],
            "message" : [ "email-body-updated" ],
            "language" : [ "" ]
          }
        }
      ]
    }
  }';
  foreach ($exported_rules as $exported_rule) {
    $rule = rules_import($exported_rule);
    $configs[$rule->name] = $rule;
  }

  return $configs;
}