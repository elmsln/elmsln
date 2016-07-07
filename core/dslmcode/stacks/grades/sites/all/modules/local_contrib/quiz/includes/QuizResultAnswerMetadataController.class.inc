<?php

class QuizResultAnswerMetadataController extends EntityDefaultMetadataController {

  function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $info['quiz_result_answer']['properties']['result_id']['type'] = 'quiz_result';
    $info['quiz_result_answer']['properties']['question_nid']['type'] = 'node';
    $info['quiz_result_answer']['properties']['is_correct']['type'] = 'boolean';
    $info['quiz_result_answer']['properties']['is_skipped']['type'] = 'boolean';
    $info['quiz_result_answer']['properties']['is_doubtful']['type'] = 'boolean';
    $info['quiz_result_answer']['properties']['answer_timestamp']['type'] = 'date';

    return $info;
  }

}
