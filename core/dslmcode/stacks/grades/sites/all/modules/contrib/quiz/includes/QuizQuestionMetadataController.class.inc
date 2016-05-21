<?php

class QuizQuestionMetadataController extends EntityDefaultMetadataController {

  function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $info['quiz_question']['properties']['nid']['type'] = 'node';

    return $info;
  }

}
