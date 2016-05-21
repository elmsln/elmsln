<?php

/**
 * Implements hook_default_rules_configuration().
 */
function quiz_test_default_rules_configuration() {
  $configs = array();
  $set = rules_and(array(
    'quiz_result' => array('type' => 'quiz_result', 'label' => t('Quiz attempt')),
  ));
  $set->label = t('Test for rules feedback conditions');
  $set->tags[] = 'quiz';
  $set->condition('data_is', array('data:select' => 'quiz-result:attempt', 'op' => '>', 'value' => 1));

  $configs["quiz_feedback_after2attempts"] = $set;

  return $configs;
}
