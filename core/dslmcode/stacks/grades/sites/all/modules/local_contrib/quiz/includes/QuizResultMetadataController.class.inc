<?php

class QuizResultMetadataController extends EntityDefaultMetadataController {

  function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $info['quiz_result']['properties']['nid']['type'] = 'node';
    $info['quiz_result']['properties']['vid']['type'] = 'integer';
    $info['quiz_result']['properties']['uid']['type'] = 'user';
    $info['quiz_result']['properties']['time_start']['label'] = 'Date started';
    $info['quiz_result']['properties']['time_start']['type'] = 'date';
    $info['quiz_result']['properties']['time_end']['label'] = 'Date finished';
    $info['quiz_result']['properties']['time_end']['type'] = 'date';
    $info['quiz_result']['properties']['released']['type'] = 'date';
    $info['quiz_result']['properties']['score']['label'] = 'Score';
    $info['quiz_result']['properties']['score']['type'] = 'integer';
    $info['quiz_result']['properties']['is_invalid']['label'] = 'Invalid';
    $info['quiz_result']['properties']['is_invalid']['type'] = 'boolean';
    $info['quiz_result']['properties']['is_evaluated']['label'] = 'Evaluated';
    $info['quiz_result']['properties']['is_evaluated']['type'] = 'boolean';
    $info['quiz_result']['properties']['time_left']['type'] = 'duration';

    return $info;
  }

}
