<?php

/**
 * @file
 * batch related functions for LTI Tool Provider Memberships module.
 */

/**
 * Batch Operation Callback to get membership data.
 *
 * @param boolean $fetch_new_data
 * @param array $context
 */
function lti_tool_provider_memberships_batch_get_memberships($fetch_new_data, &$context) {
  // Store some result for post-processing in the finished callback.
  $context['results']['members'] = lti_tool_provider_memberships_get_memberships($fetch_new_data);
  $context['message'] = t('Fetch membership.');
}

/**
 * Batch Operation Callback to get new memberships.
 *
 * @param array $context
 */
function lti_tool_provider_memberships_batch_get_new_memberships(&$context) {
  // Store some result for post-processing in the finished callback.
  $context['results']['new_members'] = lti_tool_provider_memberships_get_new_memberships($context['results']['members']);
  $context['results']['new_members_chunked'] = array_chunk($context['results']['new_members'], 32, TRUE);
  $context['results']['new_members_chunk_max'] = count($context['results']['new_members_chunked']);
  $context['message'] = t('Find new members.');
}

/**
 * Batch Operation Callback to get dropped memberships.
 *
 * @param array $context
 */
function lti_tool_provider_memberships_batch_get_dropped_memberships(&$context) {
  // Store some result for post-processing in the finished callback.
  $context['results']['dropped_members'] = lti_tool_provider_memberships_get_dropped_memberships($context['results']['members']);
  $context['results']['dropped_members_chunked'] = array_chunk($context['results']['dropped_members'], 32, TRUE);
  $context['results']['dropped_members_chunk_max'] = count($context['results']['dropped_members_chunked']);
  $context['message'] = t('Find dropped members.');
}

/**
 * Batch Operation Callback to get altered memberships.
 *
 * @param array $context
 */
function lti_tool_provider_memberships_batch_get_altered_memberships(&$context) {
  // Store some result for post-processing in the finished callback.
  $context['results']['altered_members'] = lti_tool_provider_memberships_get_altered_memberships($context['results']['members']);
  $context['results']['altered_members_chunked'] = array_chunk($context['results']['altered_members'], 32, TRUE);
  $context['results']['altered_members_chunk_max'] = count($context['results']['altered_members_chunked']);
  $context['message'] = t('Find altered members.');
}

/**
 * Batch Operation Callback to initialise added memberships batch.
 *
 * @param array $members
 * @param array $context
 */
function lti_tool_provider_memberships_batch_init_new_memberships($members, &$context) {
  $context['results']['new_members_chunked'] = array_chunk($members, 32, TRUE);
  $context['results']['new_members_chunk_max'] = count($context['results']['new_members_chunked']);
  $context['message'] = t('Adding members: Init.');
}

/**
 * Batch Operation Callback to initialise dropped memberships batch.
 *
 * @param array $members
 * @param array $context
 */
function lti_tool_provider_memberships_batch_init_dropped_memberships($members, &$context) {
  $context['results']['dropped_members_chunked'] = array_chunk($members, 32, TRUE);
  $context['results']['dropped_members_chunk_max'] = count($context['results']['dropped_members_chunked']);
  $context['message'] = t('Dropping members: Init.');
}

/**
 * Batch Operation Callback to initialise altered memberships batch.
 *
 * @param array $members
 * @param array $context
 */
function lti_tool_provider_memberships_batch_init_altered_memberships($members, &$context) {
  $context['results']['altered_members_chunked'] = array_chunk($members, 32, TRUE);
  $context['results']['altered_members_chunk_max'] = count($context['results']['altered_members_chunked']);
  $context['message'] = t('Altering members: Init.');
}

/**
 * Batch Operation Callback to process added memberships.
 *
 * @param array $context
 */
function lti_tool_provider_memberships_batch_process_added_memberships(&$context) {
  $current = isset($context['sandbox']['new_members_chunk_current']) ?  $context['sandbox']['new_members_chunk_current'] : 0;
  // Add members chunk by chunk.
  if ($context['results']['new_members_chunk_max'] == 0 || $current >= $context['results']['new_members_chunk_max']) {
    $context['finished'] = 1;
    $context['message'] = t('Process added memberships.');
  }
  else {
    foreach ($context['results']['new_members_chunked'][$current] as $member) {
      lti_tool_provider_memberships_add_member($member);
    }
    $context['sandbox']['new_members_chunk_current'] = ++$current;
    $context['finished'] = $context['sandbox']['new_members_chunk_current']/$context['results']['new_members_chunk_max'];
    $context['message'] = t('Process adding memberships: @start of @max.', array(
      '@start' => $context['sandbox']['new_members_chunk_current'],
      '@max' => $context['results']['new_members_chunk_max'],
    ));
  }
}

/**
 * Batch Operation Callback to process dropped memberships.
 *
 * @param array $delete_content
 * @param array $context
 */
function lti_tool_provider_memberships_batch_process_dropped_memberships($delete_content, &$context) {
  $current = isset($context['sandbox']['dropped_members_chunk_current']) ?  $context['sandbox']['dropped_members_chunk_current'] : 0;
  // Drop members chunk by chunk.
  if ($context['results']['dropped_members_chunk_max'] == 0 || $current >= $context['results']['dropped_members_chunk_max']) {
    $context['finished'] = 1;
    $context['message'] = t('Process dropped memberships.');
  }
  else {
    foreach ($context['results']['dropped_members_chunked'][$current] as $member) {
      lti_tool_provider_memberships_drop_member($member->lti_tool_provider_memberships_id, $delete_content);
    }
    $context['sandbox']['dropped_members_chunk_current'] = ++$current;
    $context['finished'] = $context['sandbox']['dropped_members_chunk_current']/$context['results']['dropped_members_chunk_max'];
    $context['message'] = t('Process dropped memberships: @start of @max.', array(
      '@start' => $context['sandbox']['dropped_members_chunk_current'],
      '@max' => $context['results']['dropped_members_chunk_max'],
    ));
  }
}

/**
 * Batch Operation Callback to process altered memberships.
 *
 * @param array $context
 */
function lti_tool_provider_memberships_batch_process_altered_memberships(&$context) {
  $current = isset($context['sandbox']['altered_members_chunk_current']) ?  $context['sandbox']['altered_members_chunk_current'] : 0;
  // Alter members chunk by chunk.
  if ($context['results']['altered_members_chunk_max'] == 0 || $current >= $context['results']['altered_members_chunk_max']) {
    $context['finished'] = 1;
    $context['message'] = t('Process altered memberships.');
  }
  else {
    foreach ($context['results']['altered_members_chunked'][$current] as $member) {
      lti_tool_provider_memberships_alter_member($member);
    }
    $context['sandbox']['altered_members_chunk_current'] = ++$current;
    $context['finished'] = $context['sandbox']['altered_members_chunk_current']/$context['results']['altered_members_chunk_max'];
    $context['message'] = t('Process altered memberships: @start of @max.', array(
      '@start' => $context['sandbox']['altered_members_chunk_current'],
      '@max' => $context['results']['altered_members_chunk_max'],
    ));
  }
}

/**
 * Batch 'finished' callback after batch_get functions.
 *
 * @param boolean $success
 * @param array $results
 * @param array $operations
 */
function lti_tool_provider_memberships_prepare_form_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $_SESSION['lti_tool_provider_memberships_batch_results'] = $results;
    $_SESSION['lti_tool_provider_memberships_batch_has_run'] = TRUE;
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
}

/**
 * Batch 'finished' callback after batch_process functions.
 *
 * @param boolean $success
 * @param array $results
 * @param array $operations
 */
function lti_tool_provider_memberships_apply_finished($success, $results, $operations) {
  unset($_SESSION['lti_tool_provider_memberships_batch_has_run']);
  if (!$success) {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
}
