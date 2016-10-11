<?php

/**
 * @file
 * Administration callbacks for the learning_registry module
 */


/**
 * Form constructor to for basic search form for Learning Registry.
 */
function learning_registry_content_form($form, &$form_state) {

  if (variable_get('learning_registry_node_url', NULL) == NULL) {
    drupal_set_message(t('A Learning Registry URL has not yet been configured in the administration settings.
        Please visit Site Configuration -> Learning Registry settings to configure a URL before continuing.'), 'error');
  }
  else {
	$output = '';
	$submitter = variable_get('learning_registry_submitter', NULL);
	$search = variable_get('learning_registry_node_url', NULL) . '/slice?identity='.$submitter;
	$result = drupal_http_request($search);
	$result_array = drupal_json_decode($result->data);
	if(isset($result_array['documents'])){
		$output = call_user_func('_learning_registry_slice', $result_array);
		$form_state['storage']['results'] = $output;
	}
	else{
		$form_state['storage']['results'] = "";
	}
 }	
    
	$form['learning_registry']['results'] = array(
		'#markup' => $form_state['storage']['results'],
	);

  return $form;
}


/**
 * Slice callback to display results.
 *
 * @param array $result_array
 *   Raw array of results from slice method.
 *
 * @return string
 *   HTML reprsentation of data.
 */
function _learning_registry_slice($result_array) {
  $header = array();
  $header[] = 'Node ID';
  $header[] = 'Title'; 
  $header[] = 'LR Doc Id';
  $header[] = 'Date published';
  $header[] = 'Date updated';
  $header[] = 'Date deleted';
  $header[] = 'Queued';

  $response_rows = array();
  $docs = $result_array['documents'];
  foreach ($docs as $row) {
    if ($row['resource_data_description']['doc_type'] == 'resource_data') {
      $payload_schema = (isset($row['resource_data_description']['payload_schema'])) ? $row['resource_data_description']['payload_schema'] : "";
      $url = (isset($row['resource_data_description']['resource_locator'])) ? $row['resource_data_description']['resource_locator'] : "";
      $lr_url = variable_get('learning_registry_node_url', NULL);
	  $doc_id = $row['resource_data_description']['doc_ID'];
	  $lr_url = $lr_url."/harvest/getrecord?request_ID=".$doc_id."&by_doc_ID=true";
	  $create_date = ($row['resource_data_description']['create_timestamp']) ? $row['resource_data_description']['create_timestamp'] : "";
      $create_date = drupal_substr($create_date, 0, 10);
	  $update_date = ($row['resource_data_description']['update_timestamp']) ? $row['resource_data_description']['update_timestamp'] : "";
      $update_date = drupal_substr($update_date, 0, 10);
	  $delete_date = ($row['resource_data_description']['payload_placement'] == "none") ? $update_date : "";
	  $update_date = ($delete_date != "") ? "" : $update_date;
      $delete_date = drupal_substr($delete_date, 0, 10);
	  $q = db_select('learning_registry','l');
		$q->condition('l.docid',$doc_id,'=');
		$q->fields('l',array('nid', 'queued'));
		$result = $q->execute();
		$record = $result->fetchAssoc();
	  $nid = $record['nid'];
	  $queued = "False";
      $title = (isset($row['resource_data_description']['resource_data']['items']['properties']['name'])) ? $row['resource_data_description']['resource_data']['items']['properties']['name'] : "";
	  

      if (gettype($payload_schema) == 'array' && $record['queued'] === "0") {
          if (drupal_strlen($title) == 0) {
            $title = "[not provided]";
          }
		  else{
			$title = l($title, $url, array('attributes' => array('target' => '_blank')));
		  }
          $link = l($doc_id, $lr_url, array('attributes' => array('target' => '_blank')));
          $create_date = check_plain($create_date);
          $response_rows[] = array($nid, $title, $link, $create_date, $update_date, $delete_date, $queued);
       }
      }
    }
	$query_rows = array();
	$q = db_select('learning_registry','l');
		$q->condition('l.queued',1,'=');
		$q->leftjoin('node','n','n.nid=l.nid');
		$q->fields('l',array('nid'));
		$q->fields('n',array('title'));
		$result = $q->execute();
	while($record = $result->fetchAssoc()){
		$query_rows[$record['nid']] = array($record['nid'], $record['title'], '', '', '', '',  "True");
	}
	$rows = array_merge($response_rows, $query_rows);
	usort($rows, function($a, $b){
		return ($a[0] - $b[0]);
	});
  return theme('table', array('header' => $header, 'rows' => $rows));
}
