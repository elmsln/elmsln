<?php

/**
 * Implements hook_default_rules_configuration().
 */
function quiz_default_rules_configuration() {
  $configs = array();
  foreach (quiz_get_feedback_times() as $key => $when) {
    $set = rules_and(array(
      'quiz_result' => array('type' => 'quiz_result', 'label' => t('Quiz attempt')),
    ));
    $set->label = t('@title feedback conditions', array('@title' => $when['name']));
    $set->tags[] = 'quiz';

    $configs["quiz_feedback_$key"] = $set;
  }

  $configs["rules_send_results_at_the_end_of_a_quiz"] = rules_import('
{ "rules_send_results_at_the_end_of_a_quiz" : {
    "LABEL" : "Send quiz results at the end of a quiz",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : false,
    "OWNER" : "rules",
    "TAGS" : [ "quiz" ],
    "REQUIRES" : [ "rules", "entity" ],
    "ON" : { "quiz_result_update" : [] },
    "IF" : [
      { "data_is" : { "data" : [ "quiz-result-unchanged:is-evaluated" ], "value" : "0" } },
      { "data_is" : { "data" : [ "quiz-result:is-evaluated" ], "value" : "1" } }
    ],
    "DO" : [
      { "mail" : {
          "to" : [ "quiz-result:uid:mail" ],
          "subject" : "[site:name]: Your results for [quiz-result:nid:title]",
          "message" : "[quiz-result:uid:name],\r\n\r\nYou finished the quiz [quiz-result:nid:title] on [quiz-result:time-start]\r\n\r\nYour score: [quiz-result:score]%\r\n\r\nYou can access the result here: [site:url]node\/[quiz-result:nid:nid]\/quiz-results\/[quiz-result:result-id]",
          "language" : [ "" ]
        }
      },
      { "mail" : {
          "to" : [ "quiz-result:nid:author:mail" ],
          "subject" : "[site:name]: [quiz-result:uid:name]\u0027s results for [quiz-result:nid:title]",
          "message" : "[quiz-result:nid:author:name],\r\n\r\n[quiz-result:uid:name] finished the quiz [quiz-result:nid:title] on [quiz-result:time-start]\r\n\r\nTheir score: [quiz-result:score]%\r\n\r\nYou can access the result here: [site:url]node\/[quiz-result:nid:nid]\/quiz\/results\/[quiz-result:result-id]\/view",
          "language" : [ "" ]
        }
      }
    ]
  }
}
');

  return $configs;
}
