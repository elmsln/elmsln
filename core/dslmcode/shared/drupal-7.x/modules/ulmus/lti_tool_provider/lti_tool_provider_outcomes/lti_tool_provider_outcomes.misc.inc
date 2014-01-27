<?php
/**
 * @file
 * Contains functions for minor operations like retreiving
 * name of consumer etc.
 */

/**
 * Validate the score if it conforms to the selected datatype.
 *
 * @param string $datatype
 *   The selected datatype
 * @param string $score
 *   The input score
 *
 * @return boolean
 *   Success or failure
 */
function lti_tool_provider_outcomes_validate_score($datatype, $score, $base_no) {
  try{
    $value = floatval($score);
  }catch(Exception $e) {
    return FALSE;
  }
  if (strcasecmp($datatype, 'decimal') == 0) {
    if ($value >= 0 && $value <= 1.0) {
      return TRUE;
    }
  }
  elseif (strcasecmp($datatype, 'percentage') == 0) {
    if ($value >= 0 && $value <= 100 && is_numeric($score)) {
      if (!strpos($value, '.')) {
        return TRUE;
      }
    }
  }
  elseif (strcasecmp($datatype, 'ratio') == 0) {
    if (is_numeric($score)) {
      if (!strpos($value, '.')) {
        if ($score <= $base_no) {
          return TRUE;
        }
      }
    }
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    return TRUE;
  }
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    return TRUE;
  }
  elseif (strcasecmp($datatype, 'passfail') == 0) {
    return TRUE;
  }
  elseif (strcasecmp($datatype, 'freetext') == 0) {
    if (drupal_strlen($score) <= 1024) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Retreives Outcomes.
 *
 * @param string $context_id
 *   Session context id.
 * @param string $resource_link_id
 *   Resource link id.
 * @param string $consumer_id
 *   Consumer entity id.
 * @param int $uid
 *   User id.
 *
 * @return array
 *   An array of Outcomes.
 */
function lti_tool_provider_outcomes_get_outcomes($consumer_id, $context_id, $resource_link_id, $uid = NULL) {
  $resource = lti_tool_provider_outcomes_get_resource($consumer_id, $context_id, $resource_link_id);
  if (isset($resource)) {
    $query = new EntityFieldQuery();
    if (isset($uid)) {
      $query
      ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
      ->propertyCondition('lti_tool_provider_outcomes_user_id', $uid)
      ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id);
    }
    else {
      $query
      ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
      ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id);
    }
    $result = $query->execute();
    $entity_type = 'lti_tool_provider_outcomes';
    if (!empty($result[$entity_type])) {
      $outcomes = entity_load($entity_type, array_keys($result[$entity_type]));
      return $outcomes;
    }
    else {
      drupal_set_message(t('No outcomes record found'));
    }
  }
  else {
    drupal_set_message(t('No resource record found'));
  }
  return array();
}

/**
 * Retrieves Resources for a context.
 *
 * @param int $consumer_id
 *   Consumer entity id.
 * @param int $context_id
 *   Context id.
 *
 * @return array
 *   Resource_Entities. All the retrieved entities.
 */
function lti_tool_provider_outcomes_get_resources_for_context($consumer_id, $context_id) {
  $results_arr = array();
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes_resource')
  ->propertyCondition('lti_tool_provider_outcomes_resource_consumer_id', $consumer_id)
  ->propertyCondition('lti_tool_provider_outcomes_resource_context_id', $context_id);
  $result = $query->execute();
  $entity_type = 'lti_tool_provider_outcomes_resource';
  if (!empty($result[$entity_type])) {
    $resources = entity_load($entity_type, array_keys($result[$entity_type]));
    return $resources;
  }
  else {
    return NULL;
  }
}

/**
 * Retrieve the associated Datatype of the resource record.
 *
 * @param int $resource_id
 *   Resource entity id.
 *
 * @return string
 *   Datatype associated to that resource.
 */
function lti_tool_provider_outcomes_get_resource_datatype($resource_id) {
  // Return the selected datatype.
  $results_arr = array();
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes_resource')
  ->propertyCondition('lti_tool_provider_outcomes_resource_id', $resource_id);
  $result = $query->execute();
  if (isset($result['lti_tool_provider_outcomes_resource'])) {
    $entity = entity_load('lti_tool_provider_outcomes_resource', array_keys($result['lti_tool_provider_outcomes_resource']));
    $outcome = reset($entity);
    return $outcome->lti_tool_provider_outcomes_resource_score_datatype;
  }
  drupal_set_message(t('Resource not found.'), 'error');
  return '';
}

/**
 * Updates the Outcome Service Url of the Consumer Record.
 *
 * @param string $consumer_id
 *   Consumer id.
 * @param string $url
 *   Consumer outcomes url.
 * @param boolean $ext_bool
 *   Extension check.
 */
function lti_tool_provider_outcomes_update_outcome_service_url($consumer_id, $url, $ext_bool) {
  $consumer = lti_tool_provider_consumer_load($consumer_id);
  if ($consumer->lti_tool_provider_consumer_outcomes_url != $url) {
    $consumer->lti_tool_provider_consumer_outcomes_url = $url;
  }
  if ($consumer->lti_tool_provider_consumer_ext != $ext_bool) {
    $consumer->lti_tool_provider_consumer_ext = $ext_bool;
  }
  entity_get_controller('lti_tool_provider_consumer')->save($consumer);
}

/**
 * Update the score in an outcome.
 *
 * @param object $outcome
 *   Outcome entity.
 * @param string $score
 *   Score.
 */
function lti_tool_provider_outcomes_update_score($outcome, $score) {
  $outcome->lti_tool_provider_outcomes_score = $score;
  $outcome->lti_tool_provider_outcomes_last_updated = REQUEST_TIME;
  lti_tool_provider_outcomes_save($outcome);
}

/**
 * Count all affected outcomes.
 *
 * @param object $resource
 *   The Resource.
 *
 * @return array
 *   All the affected outcomes.
 */
function lti_tool_provider_outcomes_get_outcomes_for_resource($resource) {
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
  ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id);
  $result = $query->execute();
  if (!empty($result)) {
    $outcomes = entity_load('lti_tool_provider_outcomes', array_keys($result['lti_tool_provider_outcomes']));
    return $outcomes;
  }
  return array();
}

/**
 * Returns the selection array for passfail.
 *
 * @return array
 *   passfail array.
 */
function lti_tool_provider_outcomes_passfail_datatype_arr() {
  return array(
    'pass',
    'fail',
  );
}

/**
 * Returns the selection array for letteraf.
 *
 * @return array
 *   letteraf array.
 */
function lti_tool_provider_outcomes_letteraf_datatype_arr() {
  return array(
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
  );
}

/**
 * Returns the selection array for letterafplus.
 *
 * @return array
 *   letterafplus array.
 */
function lti_tool_provider_outcomes_letterafplus_datatype_arr() {
  return array(
    'A+',
    'A',
    'A-',
    'B+',
    'B',
    'B-',
    'C+',
    'C',
    'C-',
    'D+',
    'D',
    'D-',
    'E+',
    'E',
    'E-',
    'F+',
    'F',
    'F-',
  );
}

/**
 * Returns the default value of datatype.
 *
 * @param string $datatype
 *   The datatype.
 *
 * @return string
 *   The default value of the datatype.
 */
function lti_tool_provider_outcomes_get_datatype_default_value($datatype) {
  if (strcasecmp($datatype, 'decimal') == 0) {
    return '0.0';
  }
  elseif (strcasecmp($datatype, 'percentage') == 0) {
    return '0.00';
  }
  elseif (strcasecmp($datatype, 'ratio') == 0) {
    return (0 / 1);
  }
  elseif (strcasecmp($datatype, 'passfail') == 0) {
    return (0 / 1);
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    return (0 / 5);
  }
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    return (0 / 17);
  }
  elseif (strcasecmp($datatype, 'freetext') == 0) {
    return 'None';
  }
  else {
    return '0.0';
  }
  return NULL;
}

/**
 * Create the score form parameters.
 *
 * @param string $datatype
 *   The datatype.
 * @param object $outcome
 *   Outcome object.
 *
 * @return array
 *   The form data.
 */
function lti_tool_provider_outcomes_create_score_form_params($datatype, $base_no, $outcome) {
  $result = array();
  if (strcasecmp($datatype, 'decimal') == 0) {
    $result[] = array(
      '#prefix' => '<div align="center">',
      '#suffix' => '</div>',
      '#type' => 'textfield',
      '#default_value' => $outcome->lti_tool_provider_outcomes_score,
      '#size' => 9,
      '#maxlength' => 9,
      '#required' => TRUE ,
    );
  }
  elseif (strcasecmp($datatype, 'percentage') == 0) {
    $value = $outcome->lti_tool_provider_outcomes_score * $base_no;
    $result[] = array(
      '#prefix' => '<div class="container-inline" align="center">',
      '#type' => 'textfield',
      '#default_value' => $value,
      '#size' => 3,
      '#maxlength' => 3,
      '#suffix' => '%</div>',
      '#required' => TRUE ,
    );
  }
  elseif (strcasecmp($datatype, 'ratio') == 0) {
    $value = $outcome->lti_tool_provider_outcomes_score * $base_no;
    $result[] = array(
      '#prefix' => '<div class="container-inline" align="center">',
      '#type' => 'textfield',
      '#default_value' => round($value),
      '#size' => 1,
      '#maxlength' => 3,
      '#required' => TRUE,
      '#suffix' => '/',
    );
    $result[] = array(
      '#type' => 'textfield',
      '#default_value' => $base_no,
      '#size' => 1,
      '#maxlength' => 3,
      '#attributes' => array('readonly' => 'readonly'),
      '#required' => TRUE,
      '#suffix' => '</div>',
    );
  }
  elseif (strcasecmp($datatype, 'passfail') == 0) {
    $index = lti_tool_provider_outcomes_format_score_array($outcome->lti_tool_provider_outcomes_score, $datatype);
    $result[] = array(
      '#prefix' => '<div align="center">',
      '#suffix' => '</div>',
      '#type' => 'select',
      '#options' => lti_tool_provider_outcomes_passfail_datatype_arr(),
      '#default_value' => $index,
    );
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    $index = lti_tool_provider_outcomes_format_score_array($outcome->lti_tool_provider_outcomes_score, $datatype);
    $result[] = array(
      '#prefix' => '<div align="center">',
      '#suffix' => '</div>',
      '#type' => 'select',
      '#options' => lti_tool_provider_outcomes_letteraf_datatype_arr(),
      '#default_value' => $index,
    );
  }
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    $index = lti_tool_provider_outcomes_format_score_array($outcome->lti_tool_provider_outcomes_score, $datatype);
    $result[] = array(
      '#prefix' => '<div align="center">',
      '#suffix' => '</div>',
      '#type' => 'select',
      '#options' => lti_tool_provider_outcomes_letterafplus_datatype_arr(),
      '#default_value' => $index,
    );
  }
  elseif (strcasecmp($datatype, 'freetext') == 0) {
    $result[] = array(
      '#prefix' => '<div align="center">',
      '#suffix' => '</div>',
      '#type' => 'textfield',
      '#default_value' => $outcome->lti_tool_provider_outcomes_score,
      '#size' => 9,
      '#maxlength' => 1024,
      '#required' => TRUE,
    );
  }
  else {
    $result[] = array(
      '#prefix' => '<div align="center">',
      '#suffix' => '</div>',
      '#type' => 'textfield',
      '#default_value' => $outcome->lti_tool_provider_outcomes_score,
      '#size' => 9,
      '#maxlength' => 9,
      '#required' => TRUE,
    );
  }
  return $result;
}

/**
 * Retrieves the score from the form.
 *
 * @param int $row_no
 *   The row identifier.
 * @param array $form_state
 *   The form state array.
 * @param object $outcome
 *   The outcome object.
 * @param string $datatype
 *   The corresponding datatype.
 *
 * @return string
 *   The formatted score.
 */
function lti_tool_provider_outcomes_format_score($row_no, $form_state, $outcome, $datatype, $base_no) {
  if (strcasecmp($datatype, 'decimal') == 0) {
    return reset($form_state['values']['table'][$row_no]['score']);
  }
  elseif (strcasecmp($datatype, 'percentage') == 0) {
    $value = (reset($form_state['values']['table'][$row_no]['score'])) / $base_no;
    return $value;
  }
  elseif (strcasecmp($datatype, 'ratio') == 0) {
    $str_arr = $form_state['values']['table'][$row_no]['score'];
    $value = $str_arr[0] / $base_no;
    return $value;
  }
  elseif (strcasecmp($datatype, 'passfail') == 0) {
    $passfail_arr = lti_tool_provider_outcomes_passfail_datatype_arr();
    switch (reset($form_state['values']['table'][$row_no]['score'])) {
      case 0: {
        $value = 1 / 1;
        break;
      }
      case 1: {
        $value = 0 / 1;
        break;
      }
    }
    return $value;
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    $letteraf_arr = lti_tool_provider_outcomes_letteraf_datatype_arr();
    switch (reset($form_state['values']['table'][$row_no]['score'])) {
      case 0: {
        $value = 5 / 5;
        break;
      }
      case 1: {
        $value = 4 / 5;
        break;
      }
      case 2: {
        $value = 3 / 5;
        break;
      }
      case 3: {
        $value = 2 / 5;
        break;
      }
      case 4: {
        $value = 1 / 5;
        break;
      }
      case 5: {
        $value = 0 / 5;
        break;
      }
    }
    return $value;
  }
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    switch (reset($form_state['values']['table'][$row_no]['score'])) {
      case 0: {
        $value = 17 / 17;
        break;
      }
      case 1: {
        $value = 16 / 17;
        break;
      }
      case 2: {
        $value = 15 / 17;
        break;
      }
      case 3: {
        $value = 14 / 17;
        break;
      }
      case 4: {
        $value = 13 / 17;
        break;
      }
      case 5: {
        $value = 12 / 17;
        break;
      }
      case 6: {
        $value = 11 / 17;
        break;
      }
      case 7: {
        $value = 10 / 17;
        break;
      }
      case 8: {
        $value = 9 / 17;
        break;
      }
      case 9: {
        $value = 8 / 17;
        break;
      }
      case 10: {
        $value = 7 / 17;
        break;
      }
      case 11: {
        $value = 6 / 17;
        break;
      }
      case 12: {
        $value = 5 / 17;
        break;
      }
      case 13: {
        $value = 4 / 17;
        break;
      }
      case 14: {
        $value = 3 / 17;
        break;
      }
      case 15: {
        $value = 2 / 17;
        break;
      }
      case 16: {
        $value = 1 / 17;
        break;
      }
      case 17: {
        $value = 0 / 17;
        break;
      }
    }
    return round($value, 5);
  }
  elseif (strcasecmp($datatype, 'freetext') == 0) {
    return reset($form_state['values']['table'][$row_no]['score']);
  }
  else {
    return reset($form_state['values']['table'][$row_no]['score']);
  }
}

/**
 * Set the base or denominator for a score.
 *
 * @param string $datatype
 *   The datatype of the score.
 * @param string $base_no
 *   The denominator or base of the ratio.
 *
 * @return string
 *   The base number.
 */
function lti_tool_provider_outcomes_set_base($datatype, $base_no = NULL) {
  if (strcasecmp($datatype, 'decimal') == 0) {
    return 'EMPTY';
  }
  elseif (strcasecmp($datatype, 'percentage') == 0) {
    return 100;
  }
  elseif (strcasecmp($datatype, 'ratio') == 0) {
    return isset($base_no) ? $base_no : 100;
  }
  elseif (strcasecmp($datatype, 'passfail') == 0) {
    return 2;
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    return 6;
  }
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    return 18;
  }
  elseif (strcasecmp($datatype, 'freetext') == 0) {
    return 'EMPTY';
  }
  else {
    return 'EMPTY';
  }
}

/**
 * Formats raw score input.
 *
 * @param string $raw_score
 *   The raw score from form.
 * @param string $base_no
 *   The base number.
 * @param string $datatype
 *   The datatype.
 *
 * @return string
 *   The formatted score.
 */
function lti_tool_provider_outcomes_format_raw_score($raw_score, $base_no, $datatype) {
  if (strcasecmp($datatype, 'decimal') == 0) {
    return $raw_score;
  }
  elseif (strcasecmp($datatype, 'percentage') == 0) {
    return $raw_score;
  }
  elseif (strcasecmp($datatype, 'ratio') == 0) {
    $new_score = $raw_score * $base_no;
    // Return floor($new_score) . '/' . $base_no;
    return $raw_score;
  }
  elseif (strcasecmp($datatype, 'passfail') == 0) {
    return $raw_score;
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    $array = lti_tool_provider_outcomes_letteraf_datatype_arr();
    $index = floor($raw_score * $base_no);
    return $array[$index];
  }
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    $array = lti_tool_provider_outcomes_letterafplus_datatype_arr();
    $index = floor($raw_score * $base_no);
    return $array[$index];
  }
  elseif (strcasecmp($datatype, 'freetext') == 0) {
    return $raw_score;
  }
  else {
    return $raw_score;
  }
}

/**
 * Formats the score and return the appropriate value.
 *
 * @param string $score
 *   The raw score.
 * @param string $datatype
 *   The datatype.
 *
 * @return int
 *   The index of the array.
 */
function lti_tool_provider_outcomes_format_score_array($score, $datatype) {
  if (strcasecmp($datatype, 'passfail') == 0) {
    if ($score == 1) {
      $value = 0;
    }
    elseif ($score >= 0) {
      $value = 1;
    }
    return $value;
  }
  elseif (strcasecmp($datatype, 'letteraf') == 0) {
    $letteraf_arr = lti_tool_provider_outcomes_letteraf_datatype_arr();
    if ($score == 1) {
      $value = 0;
    }
    elseif ($score >= 0.8) {
      $value = 1;
    }
    elseif ($score >= 0.6) {
      $value = 2;
    }
    elseif ($score >= 0.4) {
      $value = 3;
    }
    elseif ($score >= 0.2) {
      $value = 4;
    }
    elseif ($score >= 0) {
      $value = 5;
    }
    else {
      $value = 0;
    }
    return $value;
  }
  // 5 decmial places.
  elseif (strcasecmp($datatype, 'letterafplus') == 0) {
    if ($score == 1) {
      $value = 0;
    }
    elseif ($score >= 0.94118) {
      $value = 1;
    }
    elseif ($score >= 0.88235) {
      $value = 2;
    }
    elseif ($score >= 0.82353) {
      $value = 3;
    }
    elseif ($score >= 0.76471) {
      $value = 4;
    }
    elseif ($score >= 0.70588) {
      $value = 5;
    }
    elseif ($score >= 0.64706) {
      $value = 6;
    }
    elseif ($score >= 0.58824) {
      $value = 7;
    }
    elseif ($score >= 0.52941) {
      $value = 8;
    }
    elseif ($score >= 0.47059) {
      $value = 9;
    }
    elseif ($score >= 0.41176) {
      $value = 10;
    }
    elseif ($score >= 0.35294) {
      $value = 11;
    }
    elseif ($score >= 0.29412) {
      $value = 12;
    }
    elseif ($score >= 0.23529) {
      $value = 13;
    }
    elseif ($score >= 0.17647) {
      $value = 14;
    }
    elseif ($score >= 0.11765) {
      $value = 15;
    }
    elseif ($score >= 0.05882) {
      $value = 16;
    }
    elseif ($score >= 0) {
      $value = 17;
    }
    return $value;
  }
}
/**
 * Returns the default datatypes.
 *
 * @return string
 *   The string of datatypes separated by comma.
 */
function lti_tool_provider_outcomes_default_resultvalue_sourcedids() {
  return 'decimal,percentage,ratio,passfail,letteraf,letterafplus';
}
