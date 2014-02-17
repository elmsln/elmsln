<?php
/**
 * @file
 * cle_submission.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cle_submission_default_rules_configuration() {
  $items = array();
  $items['rules_cle_submission_comment'] = entity_import('rules_config', '{ "rules_cle_submission_comment" : {
      "LABEL" : "Submission Comment",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CLE" ],
      "REQUIRES" : [ "rules", "radioactivity", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "comment:node" ],
            "type" : { "value" : { "cle_submission" : "cle_submission" } }
          }
        },
        { "user_has_role" : {
            "account" : [ "comment:author" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ],
      "DO" : [
        { "radioactivity_emit" : { "data" : [ "comment:node:field-energy" ], "value" : "-5" } }
      ]
    }
  }');
  $items['rules_cle_submission_vote'] = entity_import('rules_config', '{ "rules_cle_submission_vote" : {
      "LABEL" : "Submission Vote",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CLE" ],
      "REQUIRES" : [ "rules", "radioactivity", "voting_rules" ],
      "ON" : [ "voting_rules_insert_node" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "cle_submission" : "cle_submission" } }
          }
        }
      ],
      "DO" : [
        { "radioactivity_emit" : { "data" : [ "node:field-energy" ], "value" : "-1" } }
      ]
    }
  }');
  return $items;
}
