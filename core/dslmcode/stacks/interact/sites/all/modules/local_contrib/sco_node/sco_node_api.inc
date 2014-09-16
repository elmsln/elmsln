<?php

/**
 * @file
 *   SCO Node module AJAX API functions.
 */


// sco ajax handler
function sco_node_api($node, $op, $attid = FALSE) {

  if ($op == 'FETCH') {
    sco_node_api_fetch($node, $attid);
  }
  
  if ($op == 'STORE') {
    sco_node_api_store($node, $attid);
  }
  
  drupal_exit();  
}

// initialize cmi data
function sco_node_api_fetch($node, $attid) {

  global $user;
  
  $data = array();
  $data['learner_id'] = $user->uid;
  $data['learner_name'] = $user->name;
  
  // if no attempt id, must be review mode
  if (!$attid) {
    $data['mode'] = 'review';
    drupal_json_output($data);  
    return;
  }
  
  $att = db_query("SELECT * FROM {sco_node_attempt} WHERE id = :id", array(':id' => $attid))->fetchObject();
  if ($att != NULL) {
    if ($att->uid == $user->uid && $att->nid == $node->nid) {

      $data['total_time'] = $att->total_time;

      $cmi = unserialize($att->cmi_data);
      
      if (isset($cmi['location'])) {
        $data['location'] = $cmi['location'];
      }
      if (isset($cmi['suspend_data'])) {
        $data['suspend_data'] = $cmi['suspend_data'];
      }
      if (isset($cmi['completion_status'])) {
        $data['completion_status'] = $cmi['completion_status'];
      }
      if (isset($cmi['success_status'])) {
        $data['success_status'] = $cmi['success_status'];
      }
      if (isset($cmi['progress_measure'])) {
        $data['progress_measure'] = $cmi['progress_measure'];
      }
      if (isset($cmi['score_min'])) {
        $data['score_min'] = $cmi['score_min'];
      }      
      if (isset($cmi['score_max'])) {
        $data['score_max'] = $cmi['score_max'];
      }      
      if (isset($cmi['score_scaled'])) {
        $data['score_scaled'] = $cmi['score_scaled'];
      }      
      if (isset($cmi['score_raw'])) {
        $data['score_raw'] = $cmi['score_raw'];
      }      
      if (isset($cmi['pref_audio'])) {
        $data['pref_audio'] = $cmi['pref_audio'];
      }      
      if (isset($cmi['pref_lang'])) {
        $data['pref_lang'] = $cmi['pref_lang'];
      }      
      if (isset($cmi['pref_speed'])) {
        $data['pref_speed'] = $cmi['pref_speed'];
      }      
      if (isset($cmi['pref_caption'])) {
        $data['pref_caption'] = $cmi['pref_caption'];
      }
      
      if (isset($cmi['objectives'])) {
        $data['objectives'] = $cmi['objectives'];
      }
      else {
        // see if any objectives exist in manifest
        $objs = array();
        foreach ($node->sco_manifest->organizations[0]->items as $item) {
          if (isset($item->objectives) && is_array($item->objectives)) {
            foreach ($item->objectives as $mobj) {
              if (!$mobj->primary) {
                $obj = array();
                $obj['id'] = $mobj->id;
                $objs[] = $obj;
              }
            }
          }
        }
        if (count($objs) > 0) {
          $data['objectives'] = $objs;
        }
      }
      
      if (isset($cmi['interactions'])) {
        $data['interactions'] = $cmi['interactions'];
      }
      
      // set entry value
      if ($att->exit_status == 'suspend' || $att->exit_status == 'logout') {
        $data['entry'] = 'resume';
      }
      
      // reset session time
      if ($att->session_time > 0) {
        $attupd = new StdClass();
        $attupd->id = $attid;
        $attupd->session_time = 0;
        drupal_write_record('sco_node_attempt', $attupd, 'id');
      }

      // call hooks before fetch data sent
      $hook = 'sco_node_fetch';
      foreach (module_implements($hook) as $mod) {
        $function = $mod . '_' . $hook;
        $function($att, $data);
      }
      
      drupal_json_output($data);  
    }
    else {
      echo 'fetch error - attempt does not belong to this user or sco node';
    }
  }
  else {
    echo 'fetch error - attempt not found';
  }
}

// store cmi data
function sco_node_api_store($node, $attid) {

  global $user;
  
  // if no attempt id, must be review mode
  if (!$attid) {
    echo 'store complete - review mode';
    return;
  }
  
  // lookup attempt record
  $dbatt = db_query("SELECT * FROM {sco_node_attempt} WHERE id = :id", array(':id' => $attid))->fetchObject();
  if ($dbatt != NULL) {
  
    // verify attempt record matches current user and node
    if ($dbatt->uid == $user->uid && $dbatt->nid == $node->nid) {
      $ts = date('Y-m-d H:i:s');
      $att = new StdClass();
      $att->id = $attid;
      $att->log = $dbatt->log;
      
      // get and parse cmi data (json)
      if (!array_key_exists('cmidata', $_POST)) {
        $msg = 'store error - no cmi data received';
        echo $msg;
        watchdog('sco_node', $msg);
        $att->log .= date('m/d/Y H:i:s') . ' - No cmi data received: ' . print_r($_POST, TRUE) . "\n\r";
      }
      else {
        $cmidata = $_POST['cmidata'];
        $cmi = drupal_json_decode($cmidata);
  
        if ($cmi == NULL) {
          $msg = 'store error - invalid cmi data received';
          echo $msg;
          watchdog('sco_node', $msg);
          $att->log .= date('m/d/Y H:i:s') . ' - Unable to parse cmi data: ' . $cmidata . "\n\r";
        }
        else {
          // update log and remove from cmi log from data
          if (array_key_exists('log', $cmi)) {
            $att->log .= $cmi['log'];
            unset($cmi['log']);
          }
          
          // update status
          $att->status = $cmi['completion_status'];
          $att->outcome = $cmi['success_status'];
          
          // update completion time if status indicates complete or passed
          if (($att->status == 'completed' || $att->status == 'passed') && $dbatt->completed == NULL) {
            $att->completed = $ts;
          }
          
          // get last session time received - used to calc total time later
          $session_time = $dbatt->session_time;
          // update if new value received
          if (array_key_exists('session_time', $cmi)) {
            $session_time = $cmi['session_time'];
            $att->session_time = $session_time;
          }
          
          // see if new exit value received
          if (array_key_exists('exit', $cmi)) {
            $att->exit_status = $cmi['exit'];
            // accumulate total time on exit
            $att->total_time = $dbatt->total_time + $session_time;
          }
  
          unset($cmi['exit']);
          unset($cmi['session_time']);
  
          $att->cmi_data = serialize($cmi);
          $att->score = sco_node_score_attempt($node, $att);
          echo 'store complete - ' . strlen($cmidata) . ' bytes received';
        }
      }
      // set update timestamp
      $att->updated = $ts;
      // update attempt record
      drupal_write_record('sco_node_attempt', $att, 'id');

      // call hooks after store
      $hook = 'sco_node_store';
      foreach (module_implements($hook) as $mod) {
        $function = $mod . '_' . $hook;
        $function($att, $cmidata);
      }
    }
    else {
      $msg = 'store error - attempt does not belong to this user or sco node';
      echo $msg;
      watchdog('sco_node', $msg);
    }
  }
  else {
    $msg = 'store error - attempt not found';
    echo $msg;
    watchdog('sco_node', $msg);
  }
}
