<?php

/**
 * Callback for getting comment data out of Drupal
 */
function _elmsln_lrnapp_comments_recent($machine_name, $app_route, $params, $args) {
  $comments = array();
  $status = 404;
  $query = new EntityFieldQuery();
  $query
  ->entityCondition('entity_type', 'comment')
  ->propertyCondition('status', 1)
  ->propertyOrderBy('changed', 'DESC')
  ->range(0, 5);
  $result = $query->execute();
  // flip the results if it found them
  if (isset($result['comment'])) {
	  foreach ($result['comment'] as $commentdata) {
	    $comment = comment_load($commentdata->cid);
	    $comments[$comment->cid] = array(
	    	'title' => $comment->subject,
	    	'body' => $comment->comment_body['und'][0]['safe_value'],
	    	'view' => base_path() . 'apps/lrnapp-studio-submission/submissions/' . $comment->nid,
        'date' => date('m/d h:m A', $comment->changed),
        'username' => $comment->name,
	    );
	  }
	  $status = 200;
  }
  return array(
    'status' => $status,
    'data' => $comments
  );
}