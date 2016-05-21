<?php

class QuizMetadataController extends EntityDefaultMetadataController {

  function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $info['node']['properties']['quiz']['label'] = t('Quiz');
    $info['node']['properties']['quiz']['description'] = t('Quiz properties');
    $info['node']['properties']['quiz']['type'] = 'quiz';

    $info['quiz']['properties']['quiz_open']['label'] = 'Open date';
    $info['quiz']['properties']['quiz_open']['type'] = 'date';
    $info['quiz']['properties']['quiz_close']['label'] = 'Close date';
    $info['quiz']['properties']['quiz_close']['type'] = 'date';

    return $info;
  }

}
