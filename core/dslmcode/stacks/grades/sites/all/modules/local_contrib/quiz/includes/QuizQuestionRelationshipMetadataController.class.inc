<?php

class QuizQuestionRelationshipMetadataController extends EntityDefaultMetadataController {

  function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $info['quiz_question_relationship']['properties']['child_nid']['type'] = 'node';
    $info['quiz_question_relationship']['properties']['child_vid']['type'] = 'integer';
    $info['quiz_question_relationship']['properties']['parent_nid']['type'] = 'node';
    $info['quiz_question_relationship']['properties']['parent_vid']['type'] = 'integer';

    return $info;
  }

}
