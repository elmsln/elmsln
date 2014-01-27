<?php
/**
 * @file
 * Contains functions related to retrieving/sending outcomes from/to
 * the consumers outcomes service.
 */

module_load_include('inc', 'lti_tool_provider_outcomes', 'lti_tool_provider_outcomes.connect');

/**
 * Send results to the Consumer.
 *
 * @param string $mode
 *   The scope of results to retrieve.
 * @param string $return_url
 *   To customise return page when URL is accessed.
*/
function lti_tool_provider_outcomes_send_results($mode, $return_url = '') {
  global $user;
  // Consumer_id based on the context.
  $uid = $user->uid;
  $consumer_id = $_SESSION['lti_tool_provider_context_info']['consumer_id'];
  $context_id = $_SESSION['lti_tool_provider_context_info']['context_id'];
  $resource_link_id = $_SESSION['lti_tool_provider_context_info']['resource_link_id'];
  $consumer = lti_tool_provider_consumer_load($consumer_id);
  $url = $consumer->lti_tool_provider_consumer_outcomes_url;
  if (!isset($url)) {
    drupal_set_message(t('Unable to send results. No Outcome URL is avaliable'), 'error');
    drupal_goto($return_url);
  }
  switch ($mode) {
    case 'user': {
      // For outcome of current user.
      $resource = lti_tool_provider_outcomes_get_resource($consumer_id, $context_id, $resource_link_id);
      lti_tool_provider_outcomes_send_outcome_for_user($resource, $consumer, $uid);
      drupal_goto($return_url);
    }
    // For all outcomes in current resource.
    case 'resource': {
      $resource = lti_tool_provider_outcomes_get_resource($consumer_id, $context_id, $resource_link_id);
      $batch_send = array(
        'title' => t('Sending outcomes.'),
        'operations' => array(
          array('lti_tool_provider_outcomes_batch_send', array($resource, $consumer)),
        ),
        'finished' => 'lti_tool_provider_outcomes_batch_finished',
        'init_message' => t('Sending outcomes.'),
        'error_message' => t('Encountered an error while sending outcomes.'),
        'file' => drupal_get_path('module', 'lti_tool_provider_outcomes') . '/lti_tool_provider_outcomes.sync.inc',
      );
      batch_set($batch_send);
      batch_process($return_url);
    }
    // For all outcomes of all resources in current context.
    case 'context': {
      $resources = lti_tool_provider_outcomes_get_resources_for_context($consumer_id, $context_id);
      $operations = array();
      foreach($resources as $resource) {
        $operations[] = array('lti_tool_provider_outcomes_batch_send', array($resource, $consumer));
      }
      $batch_send = array(
        'title' => t('Sending outcomes.'),
        'operations' => $operations,
        'finished' => 'lti_tool_provider_outcomes_batch_finished',
        'init_message' => t('Sending outcomes.'),
        'error_message' => t('Encountered an error while sending outcomes.'),
        'file' => drupal_get_path('module', 'lti_tool_provider_outcomes') . '/lti_tool_provider_outcomes.sync.inc',
      );
      batch_set($batch_send);
      batch_process($return_url);
    }
  }
}

/**
 * Batch Operation Callback to send outcomes for a resource.
 *
 * @param entity $resource
 * @param entity $consumer
 * @param array $context
 */
function lti_tool_provider_outcomes_batch_send($resource, $consumer, &$context) {
  $chunk_size = 32;
  if (!isset($context['sandbox']['current'])) {
    // Find the number of outcomes in this resource;
    $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
    ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id)
    ->propertyOrderBy('lti_tool_provider_outcomes_id');
    $context['sandbox']['count'] = $query->count()->execute();
    $context['sandbox']['current'] = 0;
  }
  // Find next group of outcomes to send.
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
  ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id)
  ->propertyOrderBy('lti_tool_provider_outcomes_id')
  ->range($context['sandbox']['current'], $chunk_size);
  $result = $query->execute();
  $entity_type = 'lti_tool_provider_outcomes';
  if (!empty($result[$entity_type])) {
    $outcomes = entity_load($entity_type, array_keys($result[$entity_type]));
    foreach ($outcomes as $outcome) {
      lti_tool_provider_outcomes_send_outcome($outcome, $consumer);
      $context['sandbox']['current']++;
    }
    $context['finished'] = $context['sandbox']['current']/$context['sandbox']['count'];
    $context['message'] = t('Sending outcomes: @start of @max.', array(
      '@start' => $context['sandbox']['current'],
      '@max' => $context['sandbox']['count'],
    ));
  }
  else {
    $context['finished'] = 1;
    $context['message'] = t('Done sending outcomes.');
  }
}

/**
 * Send an outcome via LTI.
 *
 * @param entity $outcome
 * @param entity $consumer
 *
 * @return boolean
 *   Indicate success.
 */
function lti_tool_provider_outcomes_send_outcome($outcome, $consumer) {
  if ($consumer->lti_tool_provider_consumer_ext) {
    $params = lti_tool_provider_outcomes_construct_params_array_update($outcome->lti_tool_provider_outcomes_result_sourcedid, $outcome->lti_tool_provider_outcomes_score, $resource->lti_tool_provider_outcomes_resource_score_datatype_base_value, lti_tool_provider_outcomes_get_resource_datatype($outcome->lti_tool_provider_outcomes_resource_entity_id_fk, 2));
    $response = lti_tool_provider_outcomes_lti_service_post($params, $consumer->lti_tool_provider_consumer_key, $consumer->lti_tool_provider_consumer_outcomes_url);
    $success = lti_tool_provider_outcomes_decode_ext_xml_reply($response);
  }
  else {
    $response = lti_tool_provider_outcomes_lti_service_xml($consumer, $consumer->lti_tool_provider_consumer_outcomes_url, 1, $outcome->lti_tool_provider_outcomes_result_sourcedid, $outcome->lti_tool_provider_outcomes_score);
    $success = lti_tool_provider_outcomes_decode_xml_reply($response);
  }
  if ($success) {
    // Once sent, update timestamp.
    lti_tool_provider_outcomes_update_timestamp($outcome);
    return TRUE;
  }
  else {
    // Unable to update.
    drupal_set_message(t('Unable to send result ID: @outcome', array('@outcome' => $outcome->lti_tool_provider_outcomes_id)), 'error');
    return FALSE;
  }
}

/**
 * Send an outcome for a user.
 *
 * @param entity $resource
 *   Resource entity.
 * @param entity $consumer
 *   Consumer entity.
 * @param int $uid
 *   User id.
 *
 * @return boolean
 *   Indicates success.
 */
function lti_tool_provider_outcomes_send_outcome_for_user($resource, $consumer, $uid) {
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
  ->propertyCondition('lti_tool_provider_outcomes_user_id', $uid)
  ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id);
  $result = $query->execute();
  $entity_type = 'lti_tool_provider_outcomes';
  if (!empty($result[$entity_type])) {
    $outcomes = entity_load($entity_type, array_keys($result[$entity_type]));
    return lti_tool_provider_outcomes_send_outcome(reset($outcomes), $consumer);
  }
  else {
    drupal_set_message(t('No outcomes record found'));
    return FALSE;
  }
}

/**
 * Batch 'finished' callback after batch_send/pull function.
 *
 * @param boolean $success
 * @param array $results
 * @param array $operations
 */
function lti_tool_provider_outcomes_batch_finished($success, $results, $operations) {
  if (!$success) {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
}

/**
 * Retrieves results from the Consumer.
 *
 * @param string $mode
 *   The scope of results to retrieve.
 * @param string $return_url
 *   To customise return page when URL is accessed.
 */
function lti_tool_provider_outcomes_pull_results($mode, $return_url = '') {
  global $user;
  $uid = $user->uid;
  $consumer_id = $_SESSION['lti_tool_provider_context_info']['consumer_id'];
  $context_id = $_SESSION['lti_tool_provider_context_info']['context_id'];
  $result_sourcedid = isset($_SESSION['lti_tool_provider_context_info']['lis_result_sourcedid']) ? $_SESSION['lti_tool_provider_context_info']['lis_result_sourcedid'] : NULL;
  $resource_link_id = $_SESSION['lti_tool_provider_context_info']['resource_link_id'];
  $consumer = lti_tool_provider_consumer_load($consumer_id);
  $url = $consumer->lti_tool_provider_consumer_outcomes_url;
  if (!isset($url)) {
    drupal_set_message(t('Unable to retrieve results. No Outcome URL is avaliable'), 'error');
    drupal_goto($return_url);
  }
  // Get the outcomes to pull.
  switch ($mode) {
    case 'user': {
      // For this user.
      $resource = lti_tool_provider_outcomes_get_resource($consumer_id, $context_id, $resource_link_id);
      lti_tool_provider_outcomes_pull_outcome_for_user($resource, $consumer, $uid);
      drupal_goto($return_url);
    }
    // For all results in current resource.
    case 'resource': {
      $resource = lti_tool_provider_outcomes_get_resource($consumer_id, $context_id, $resource_link_id);
      $batch_pull = array(
        'title' => t('Retrieving outcomes.'),
        'operations' => array(
          array('lti_tool_provider_outcomes_batch_pull', array($resource, $consumer)),
        ),
        'finished' => 'lti_tool_provider_outcomes_batch_finished',
        'init_message' => t('Retrieving outcomes.'),
        'error_message' => t('Encountered an error while retrieving outcomes.'),
        'file' => drupal_get_path('module', 'lti_tool_provider_outcomes') . '/lti_tool_provider_outcomes.sync.inc',
      );
      batch_set($batch_pull);
      batch_process($return_url);
    }
    // For all results in current context.
    case 'context': {
      $resources = lti_tool_provider_outcomes_get_resources_for_context($consumer_id, $context_id);
      $operations = array();
      foreach($resources as $resource) {
        $operations[] = array('lti_tool_provider_outcomes_batch_pull', array($resource, $consumer));
      }
      $batch_pull = array(
        'title' => t('Retrieving outcomes.'),
        'operations' => $operations,
        'finished' => 'lti_tool_provider_outcomes_batch_finished',
        'init_message' => t('Retrieving outcomes.'),
        'error_message' => t('Encountered an error while retrieving outcomes.'),
        'file' => drupal_get_path('module', 'lti_tool_provider_outcomes') . '/lti_tool_provider_outcomes.sync.inc',
      );
      batch_set($batch_pull);
      batch_process($return_url);
    }
  }
}


/**
 * Batch Operation Callback to pull outcomes for a resource.
 *
 * @param entity $resource
 * @param entity $consumer
 * @param array $context
 */
function lti_tool_provider_outcomes_batch_pull($resource, $consumer, &$context) {
  $chunk_size = 32;
  if (!isset($context['sandbox']['current'])) {
    // Find the number of outcomes in this resource;
    $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
    ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id)
    ->propertyOrderBy('lti_tool_provider_outcomes_id');
    $context['sandbox']['count'] = $query->count()->execute();
    $context['sandbox']['current'] = 0;
  }
  // Find next group of outcomes to pull.
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
  ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id)
  ->propertyOrderBy('lti_tool_provider_outcomes_id')
  ->range($context['sandbox']['current'], $chunk_size);
  $result = $query->execute();
  $entity_type = 'lti_tool_provider_outcomes';
  if (!empty($result[$entity_type])) {
    $outcomes = entity_load($entity_type, array_keys($result[$entity_type]));
    foreach ($outcomes as $outcome) {
      lti_tool_provider_outcomes_pull_outcome($outcome, $consumer);
      $context['sandbox']['current']++;
    }
    $context['finished'] = $context['sandbox']['current']/$context['sandbox']['count'];
    $context['message'] = t('Retrieving outcomes: @start of @max.', array(
      '@start' => $context['sandbox']['current'],
      '@max' => $context['sandbox']['count'],
    ));
  }
  else {
    $context['finished'] = 1;
    $context['message'] = t('Done pulling outcomes.');
  }
}

/**
 * Pull an outcome via LTI.
 *
 * @param entity $outcome
 * @param entity $consumer
 *
 * @return boolean
 *   Indicate success.
 */
function lti_tool_provider_outcomes_pull_outcome($outcome, $consumer) {
  if ($consumer->lti_tool_provider_consumer_ext) {
    $params = lti_tool_provider_outcomes_construct_params_array_read($outcome->lti_tool_provider_outcomes_result_sourcedid);
    $response = lti_tool_provider_outcomes_lti_service_post($params, $consumer->lti_tool_provider_consumer_key, $consumer->lti_tool_provider_consumer_outcomes_url);
    $score = lti_tool_provider_outcomes_extract_ext_xml_score_reply($response);
    $success = isset($score) ? TRUE : FALSE;
  }
  else {
    $response = lti_tool_provider_outcomes_lti_service_xml($consumer, $consumer->lti_tool_provider_consumer_outcomes_url, 2, $outcome->lti_tool_provider_outcomes_result_sourcedid);
    $score = lti_tool_provider_outcomes_extract_xml_score_reply($response);
    $success = isset($score) ? TRUE : FALSE;
  }
  if ($success) {
    // Once retrieved, update score.
    lti_tool_provider_outcomes_update_score($outcome, $score);
    return TRUE;
  }
  else {
    // Unable to update.
    drupal_set_message(t('Unable to retreive result ID: @outcome', array('@outcome' => $outcome->lti_tool_provider_outcomes_id)), 'error');
    return FALSE;
  }
}

/**
 * Pull an outcome for a user.
 *
 * @param entity $resource
 *   Resource entity.
 * @param entity $consumer
 *   Consumer entity.
 * @param int $uid
 *   User id.
 *
 * @return boolean
 *   Indicates success.
 */
function lti_tool_provider_outcomes_pull_outcome_for_user($resource, $consumer, $uid) {
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'lti_tool_provider_outcomes')
  ->propertyCondition('lti_tool_provider_outcomes_user_id', $uid)
  ->propertyCondition('lti_tool_provider_outcomes_resource_entity_id_fk', $resource->lti_tool_provider_outcomes_resource_id);
  $result = $query->execute();
  $entity_type = 'lti_tool_provider_outcomes';
  if (!empty($result[$entity_type])) {
    $outcomes = entity_load($entity_type, array_keys($result[$entity_type]));
    return lti_tool_provider_outcomes_pull_outcome(reset($outcomes), $consumer);
  }
  else {
    drupal_set_message(t('No outcomes record found'));
    return FALSE;
  }
}
