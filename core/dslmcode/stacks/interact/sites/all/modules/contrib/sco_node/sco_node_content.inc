<?php

/**
 * @file
 *   SCO Node module content functions.
 */

function sco_node_content_start($node) {

  $href = ''; 
  
  // get default organization
  $org = sco_node_get_organization($node->sco_manifest);
  
  // find the starting resource
  $item = sco_node_content_start_node($org->items);
  if ($item) {
    $res = sco_node_get_resource($node->sco_manifest, $item->res_id);
    if ($res && $res->href) {
      $href = $res->href . $item->parms;
    }
  }
  
  // set url
  $url = sco_node_content_url($node, $href);

  // detect ios devices
  $isiPad = (bool) strpos($_SERVER['HTTP_USER_AGENT'],'iPad');
  $isiPhone = (bool) strpos($_SERVER['HTTP_USER_AGENT'],'iPhone');
  
  // use iframe if IE8 or less or ios
  if (preg_match('/(?i)msie [2-8]/',$_SERVER['HTTP_USER_AGENT']) || $isiPhone || $isiPad) {  
    $html = '<iframe id="sco-node-iframe" name="main"></iframe>';
  }
  else {
    $html = '<object id="sco-node-object" type="text/html"></object>';
  }     
  drupal_add_js('jQuery(document).ready(function () { sco_node_nav_to(\''. $item->id . '\',\'' . $url . '\'); });', array('type' => 'inline', 'preprocess' => FALSE, 'cache' => FALSE));
  
  return $html;
}

function sco_node_content_start_node($items) {

  foreach ($items as $item) {
    if (count($item->items) > 0) {
      return sco_node_content_start_node($item->items);
    }
    if ($item->res_id) {
      return $item;
    }
  }

  return FALSE;
}

function sco_node_content_url($node, $href) {

  $url = '';
  
  if ($href != '') {
    $url = $node->sco_path . '/' . $href;
    $url = file_create_url($url);
  }
  
  return $url;
}