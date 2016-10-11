<?php
/**
 * @file
 * Handles all learning registry specific functionality
 */

/**
 * Publish node metadata to specified Learning Registry node.
 *
 * @param object &$node
 *   A reference to the node object. We have to be very careful to not set
 *   anything, only read from the node object reference since the node
 *   reference allows us to edit the node content.
 * @param bool $headless
 *   A flag to determine if this is called from cron (non-user session).
 *
 * @return bool
 *   Returns TRUE if operation was successful, FALSE if not.
 */
function _learning_registry_publish(&$node, $headless = FALSE, $op = LEARNING_REGISTRY_MODE_PUBLISH, $docid = FALSE) {
  $content_info = _learning_registry_get_content_info($node);
  if($docid){
	$content_info['documents'][0]['replaces'] = array($docid);
  }
  if($op == LEARNING_REGISTRY_MODE_DELETE){
	$content_info['documents'][0]['TOS'] = array(
		"submission_TOS" => "http://www.learningregistry.org/tos/cc0/v0-5/",
	);
	$content_info['documents'][0]['payload_placement'] = "none";
	$content_info['documents'][0]['update_timestamp'] = gmdate('Y-m-d\TH:i:s.u\Z');
	unset($content_info['documents'][0]['resource_data']);
  }
  $resource_post_payload = drupal_json_encode($content_info);
  $result = _learning_registry_send_to_registry($node->nid, $resource_post_payload, $op, $headless);
  return $result;
}

/**
 * Return info we submit about nodes to the LR.
 *
 * @param object &$node
 *   A reference to the node object. We have to be very careful to not set
 *   anything, only read from the node object reference since the node
 *   reference allows us to edit the node content.
 */
function _learning_registry_get_content_info(&$node) {
  $keywords = learning_registry_extract_keywords($node);
  array_unshift($keywords, "Drupal7LR");
  $resource_data = _learning_registry_get_resource_data($node);
  $content_info = array();
  $content_info['resource_locator'] = _learning_registry_get_node_url($node);
  $content_info['resource_data'] = $resource_data;
  $content_info['keys'] = $keywords;
  $content_info['TOS'] = array(
		"submission_TOS" => variable_get('learning_registry_tos', NULL),
	);
  $content_info['resource_data_type'] = 'metadata';
  $content_info['payload_placement']  = "inline";
  $content_info['payload_schema'] = array("schema.org", "lrmi", "json-ld");
  $content_info['active'] = TRUE;
  $content_info['doc_type'] = "resource_data";
  $content_info['doc_version'] = LEARNING_REGISTRY_DOC_VERSION;
  $content_info['create_timestamp'] = gmdate('Y-m-d\TH:i:s.u\Z', $node->created);
  $content_info['update_timestamp'] = gmdate('Y-m-d\TH:i:s.u\Z', $node->changed);
  
  $content_info['identity'] = array(
	"owner" => variable_get('learning_registry_submitter', NULL),
  );
  $doc = array();
  $doc['documents'][] = $content_info;
  return $doc;
}

/**
 * Return the absolute URL to a node.  If alias available,  return alias.
 *
 * @param object $node
 *   The node.
 *
 * @return string
 *   The absolute URL to the node.  If alias available, return alias.
 */
function _learning_registry_get_node_url(&$node) {

  // URL Type is an admin setting.  Return either alias or node ID.
  if (variable_get('learning_registry_url_type', LEARNING_REGISTRY_URL_NODE_ID) == LEARNING_REGISTRY_URL_ALIAS) {
    return url('node/' . $node->nid, array('absolute' => TRUE, 'alias' => FALSE));
  }
  else {
    return url('node/' . $node->nid, array('absolute' => TRUE, 'alias' => TRUE));
  }
}

/**
 * Make the drupal_http_request calls to send to the LR node.
 *
 * All the specified nodeapi operations ($ops) call this to send the data.
 *
 * @param string $nid
 *   A string containing the node ID for submission into the registry.
 * @param string $json
 *   A string containing the json object to be sent to the registry node.
 * @param int $service_num
 *   An int that specifies the service that will be called.
 *   0 - publish (default value)
 *   1 - update (future impl)
 *   2 - delete  (future impl)
 * @param bool $headless
 *   A flag to determine if this is called from cron (non-user session).
 *
 * @return bool
 *   True if operation was successful, false if error.
 */
function _learning_registry_send_to_registry($nid, $json, $service_num = LEARNING_REGISTRY_MODE_PUBLISH, $headless = FALSE) {
  $url = variable_get('learning_registry_node_url', NULL);
  if ($url == NULL) {
    drupal_set_message(t('This node has not been published because the Learning Registry URL has not been set.
      Please visit Site configuration -> Learning Registry settings to set the URL of the Learning Registry.'), 'warning');

    return FALSE;
  }
  else {
    $url .= '/publish';
    $oauth_consumer = learning_registry_oauth_verify();
    $oauth_consumer->fetch($url, $json, OAUTH_HTTP_METHOD_POST, array('Content-Type' => 'application/json'));
    $result = $oauth_consumer->getLastResponse();
    $response_info = $oauth_consumer->getLastResponseInfo();
    $submission_result = _learning_registry_parse_result($result, $response_info['http_code']);
    if (isset($submission_result['success'], $submission_result['doc_id']) && $submission_result['success'] === TRUE) {
      $result = _learning_registry_update_submission_status($nid, $result);
      // Allow other modules to act on SUCCESS
      module_invoke_all('learning_registry_publish_success', $nid, $result);
      return TRUE;
    }
    else {
      // TODO: This is temp workaround until the learning registry returns proper error messages. Until then I'll assume that it went through properly
      $result = _learning_registry_update_submission_status($nid, $result);
      watchdog('learning_registry', '<pre>'.print_r(json_decode($json), TRUE).'</pre><hr><pre>' . print_r(json_decode($result), TRUE) . '</pre>');
      // Allow other modules to act on FAILURE
      module_invoke_all('learning_registry_publish_failure');
      return FALSE;
    }
  }
}


/**
 * Adds a status record in the learning_registry table to record submission.
 *
 * @param int $nid
 *   Drupal node ID of item to submit.
 * @param string $result
 *   JSON response from Learning Registry.
 */
function _learning_registry_update_submission_status($nid, $result) {
  if ($result) {

    $result_array = drupal_json_decode($result);

    if ($result_array['document_results'][0]['OK']) {
      // Check to see if submission already in database.
      $submission_check_result = db_query('SELECT * FROM {learning_registry} WHERE nid = :nid', array(':nid' => $nid));
      $submission_record = $submission_check_result->fetch();

      // Check if this has been published before.
      // If no, set the published timestamp.
      // Else, the updated timestamp.
      if ($submission_record) {
        if ($submission_record->published == 0) {
          db_update('learning_registry')
            ->fields(array(
              'published' => REQUEST_TIME,
              'docid' => $result_array['document_results'][0]['doc_ID'],
              'queued' => 0,
            ))
            ->condition('nid', $nid)
            ->execute();
        }
        else {
          db_update('learning_registry')
            ->fields(array(
              'updated' => REQUEST_TIME,
              'docid' => $result_array['document_results'][0]['doc_ID'],
              'queued' => 0,
            ))
            ->condition('nid', $nid)
            ->execute();
        }
      }
      else {
        // Insert new record.
        //
        // Fill parameter array.
        $data = array(
          'nid' => $nid,
          'published' => REQUEST_TIME,
          'docid' => $result_array['document_results'][0]['doc_ID'],
        );
        // Write it to the database.
        drupal_write_record('learning_registry', $data);
      }
      return $result_array['document_results'][0]['doc_ID'];
    }
    else {
      watchdog('learning_registry', 'Error publishing node ID %nid to the registry.  Full response: %msg', array('%nid' => $nid, '%msg' => $result), WATCHDOG_ERROR);
      return FALSE;
    }
  }
}

/**
 * Parse out result from Learning Registry submission.
 *
 * @param object $result
 *   JSON array result from Learning Registry submission
 * @param string $code
 *   Error string from curl (if error occured)
 *
 * @return object
 *   Array with status information from submission
 */
function _learning_registry_parse_result($result, $code) {
  $submission_result = array();

  if ($code == 200) {
    // We have something back from the Learning Registry service.
    $result_array = drupal_json_decode($result);

    if ($result_array['OK']) {
      // Submission okay.
      $submission_result['success'] = TRUE;
      $submission_result['doc_id'] = $result_array['document_results'][0]['doc_ID'];
    }
    else {
      $submission_result['success'] = FALSE;
      if (!is_null($result_array['document_results'][0]['error'])) {
        $submission_result['error_message'] = $result_array['document_results'][0]['error'];
      }
      else {
        // If the error message comes back in form of a HTML page, let's just
        // pop off the title tag as Couch will tell us what's wrong there.
        // Current impl of LR spits two title tags, so we're grabbing the
        // last one as it displays better error message.  If not two
        // present, we'd just grab the first.
        if (strpos($result, '<html') > 0) {
          $start = strripos($result, '<title>');
          $end = strripos($result, '</title');
          // Error msg is between the title tags (+7 skips first title tag).
          $submission_result['error_message'] = drupal_substr($result, $start + 7, $end - $start - 7);
        }
      }
    }
  }
  else {
    // We didn't contact the Learning Registry, must be a network error.
    $submission_result['SUCCESS'] = FALSE;
    $submission_result['error_message'] = $result;
  }

  return $submission_result;
}

/**
 * Queues a node for submission to the LR via the learning_registry table.
 *
 * @param int $nid
 *   Drupal node ID of item to submit.
 */
function _learning_registry_queue_node($nid) {

  // Check if this record exists in submission table.
  $q = db_select('learning_registry','l');
		$q->condition('l.nid',$nid,'=');
		$q->fields('l',array('docid'));
		$result = $q->execute();
		$submission_record = $result->fetchAssoc();

  // If exists, update, else insert new record.
  if ($submission_record) {
    db_update('learning_registry')
      ->fields(array(
        'queued' => 1,
      ))
      ->condition('nid', $nid)
      ->execute();
  }
  else {
    $id = db_insert('learning_registry')
      ->fields(array(
        'nid' => $nid,
        'queued' => 1,
      ))
      ->execute();
  }
}

/**
 * Creates resource_data array with information from node.
 *
 * @param object $node
 *   Drupal node
 *
 * @return array
 */
function _learning_registry_get_resource_data(&$node) {

  $author_user = user_load($node->uid);

  // Set the title to the node title.
  $title = $node->title;

  // Set the description to the node body.
  $description = (isset($node->body['und'][0]['value'])) ? $node->body['und'][0]['value'] : "";

  // Set the date to the node create date.
  $date_created = format_date($node->created, 'custom', 'Y-m-d');

  // Set the identifier to the absolute URL of the node.
  $identifier = _learning_registry_get_node_url($node);

  // Set the submitter.
  $submitter = variable_get('learning_registry_submitter', null);
  $keywords = learning_registry_extract_keywords($node); 
  $educational_alignment = array(); 
  if(variable_get('learning_registry_standarts-select', "none") == 0){
	$vocab_st = variable_get('learning_registry_standarts-term-select', null) ? taxonomy_vocabulary_load(variable_get('learning_registry_standarts-term-select', null)) : "";
	$target_name_st = is_object($vocab_st) ? $vocab_st->name : "";
	$educational_alignment[] = array(
				"type" => "http://schema.org/CreativeWork",
				"properties" => array(
					"alignmentType" => "teaches",
					"educationalFramework" => variable_get('learning_registry_standarts-framework', ""),
					"targetName" => $target_name_st,
				),
	); 
  }
  else if(variable_get('learning_registry_standarts-select', "none") == 1){
	$educational_alignment[] = array(
				"type" => "http://schema.org/CreativeWork",
				"properties" => array(
					"alignmentType" => "teaches",
					"targetName" => variable_get('learning_registry_standarts-variable', ""),
				),
	);
  }
  if(variable_get('learning_registry_levels-select', "none") == 0){
	$vocab_lev = variable_get('learning_registry_levels-term-select', null) ? taxonomy_vocabulary_load(variable_get('learning_registry_levels-term-select', null)) : "";
	$target_name_lev = is_object($vocab_lev) ? $vocab_lev->name : "";
	$educational_alignment[] = array(
				"type" => "http://schema.org/CreativeWork",
				"properties" => array(
					"alignmentType" => "teaches",
					"educationalFramework" => variable_get('learning_registry_levels-framework', ""),
					"targetName" => $target_name_lev,
				),
	); 
  }
  else if(variable_get('learning_registry_levels-select', "none") == 1){
	$educational_alignment[] = array(
				"type" => "http://schema.org/CreativeWork",
				"properties" => array(
					"alignmentType" => "teaches",
					"targetName" => variable_get('learning_registry_levels-variable', ""),
				),
	); 
  }
  
  $subjects = array();
  if(variable_get('learning_registry_subjects-select', "none") == 0){
	$vocab_subj = variable_get('learning_registry_subjects-term-select', null) ? taxonomy_vocabulary_load(variable_get('learning_registry_subjects-term-select', null)) : "";
	$terms = taxonomy_get_tree($vocab_subj->vid);
	foreach($terms as $term){
		$subjects[] = $term->name;
	}
  }
  else if(variable_get('learning_registry_subjects-select', "none") == 1){
	$subjects[] = variable_get('learning_registry_subjects-variable', "");
  }
  
  $resourse_type = array();
  if(variable_get('learning_registry_type-select', "none") == 0){
	$vocab_type = variable_get('learning_registry_type-term-select', null) ? taxonomy_vocabulary_load(variable_get('learning_registry_type-term-select', null)) : "";
	$terms = taxonomy_get_tree($vocab_type->vid);
	foreach($terms as $term){
		$resourse_type[] = $term->name;
	}
  }
  else if(variable_get('learning_registry_type-select', "none") == 1){
	$resourse_type[] = variable_get('learning_registry_type-variable', "");
  }
  
  $resource_data = array(
	"items"  =>  array(
		"type" => "http://schema.org/CreativeWork",
		"id" => $identifier,
		"properties" => array(
			"publisher"  => array(
				"type"  => "http://schema.org/" . variable_get('learning_registry_submitter_type'),
				"properties"  => array(
					"name" => $submitter,
				),
			),
			"name" => $title,
			"author" => array(
				"type" => "http://schema.org/" . variable_get('learning_registry_submitter_type'),
				"properties" => array(
					"name" => $submitter,
				),
			),
			"url" => $identifier,
			"dateCreated" => $date_created,
			"keywords" => $keywords,
			"description" => $description,
			"educationalAlignment" => $educational_alignment,
			"subjects" => $subjects,
			"learningResourceType" => $resourse_type,
		),
	),
  );

  return $resource_data;
}
