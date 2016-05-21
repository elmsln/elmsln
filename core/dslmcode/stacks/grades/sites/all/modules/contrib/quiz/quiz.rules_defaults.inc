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

  return $configs;
}
