<?php

/**
 * @file
 *   SCO Node module SCO navigation function.
 */

function sco_node_nav_info($node) {

  // get default organization
  $org = sco_node_get_organization($node->sco_manifest);

  $html = '';  
  // set urls to be used to fetch and store cmi data for the attempt
  $attid = '';
  if (arg(3) != '') {
    $attid = arg(3);
  }
  $html .= 'if (cmi) {';
  $html .= 'cmi.lms_init_url = "' . url('node/' . $node->nid . '/api/FETCH/' . $attid) . '";';
  $html .= 'cmi.lms_commit_url = "' . url('node/' . $node->nid . '/api/STORE/' . $attid) . '";';
  $html .= 'cmi.lms_exit_url = "' . url('node/' . $node->nid) . '";';
  // set various options
  $auto_exit = sco_node_get_option_value($node, 'auto_exit_when_completed', FALSE);
  if ($auto_exit) {
    $html .= 'cmi.lms_completed_auto_exit = true;';
  }
  $url = sco_node_get_option_value($node, 'completed_url', '');
  if ($url != "") {
    $html .= 'cmi.lms_completed_url = "' . url($url) . '";';
  }
  $delay = sco_node_get_option_value($node, 'completed_url_delay', '');
  if ($delay != "") {
    $html .= 'cmi.lms_completed_url_delay = ' . $delay . ';';
  }
  $check = sco_node_get_option_value($node, 'comm_check', FALSE);
  if ($check) {
    $html .= 'cmi.comm_check = true;';
  }
  $commit_async = sco_node_get_option_value($node, 'commit_async', FALSE);
  if ($commit_async) {
    $html .= 'cmi.commit_async = true;';
  }
  $log_suspend = sco_node_get_option_value($node, 'log_suspend', FALSE);
  if ($log_suspend) {
    $html .= 'cmi.log_suspend = true;';
  }

  $html .= '}';

  $html .= 'sco_node_nav_list = new Array();';
  $html .= sco_node_nav_list_items($node, $org->items);

  return $html;
}

function sco_node_nav_list_items($node, $items) {

  $html = '';
  
  foreach($items as $item) {
    // only add items with resources
    if ($item->res_id) {
      $res = sco_node_get_resource($node->sco_manifest, $item->res_id);
      if ($res && $res->href) {
        $url = sco_node_content_url($node, $res->href . $item->parms);
        $html .= 'sco_node_nav_list.push({id:"' . $item->id . '", url:"' . $url . '", active:false, lmsdata:"' . $item->lmsdata . '"});';
      }
    }
    // recurse to add inner items
    if (count($item->items) > 0) {
      $html .= sco_node_nav_list_items($node, $item->items);
    }
  }

  return $html;
}

