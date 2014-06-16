<?php

/**
 * @file
 *   SCO Node module SCO package/manifest functions.
 */

// extract sco archive and parse manifest
function sco_node_process_sco($file = NULL) {

  static $sco;
  
  if ($file) {
  
    $settings = variable_get('sco_node_settings', array());

    $dir = '';
    if (isset($settings['upload_path'])) {
      $dir = $settings['upload_path'];
    }
    if ($dir == '') {
      $dir = 'public://';
    }
    
    $sco_folder = getGUID();
    $sco_folder = str_replace('{', '', $sco_folder);
    $sco_folder = str_replace('}', '', $sco_folder);
    
    $dir .= '/' . $sco_folder;
    drupal_mkdir($dir);
    
    $sco = new StdClass();
    $sco->sco_path = FALSE;
    $sco->sco_manifest = FALSE;
    
    $archive = sco_node_unpack($file, $dir);
    if ($archive) {
      $sco->sco_path = $dir;
      foreach ($archive as $item) {
        if ($item->filename == 'imsmanifest.xml') {
          $sco->sco_manifest = sco_node_parse_imsmanifest($item);
          break;
        }
      }
    }
  }
  
  return $sco;
}

// create a guid - from http://guid.us/GUID/PHP
function getGUID(){

    if (function_exists('com_create_guid')){
        return com_create_guid();
    }
    else{
        mt_srand((double)microtime()*10000);//optional for php 4.2.0 and up.
        $charid = strtoupper(md5(uniqid(rand(), true)));
        $hyphen = chr(45);// "-"
        $uuid = chr(123)// "{"
            .substr($charid, 0, 8).$hyphen
            .substr($charid, 8, 4).$hyphen
            .substr($charid,12, 4).$hyphen
            .substr($charid,16, 4).$hyphen
            .substr($charid,20,12)
            .chr(125);// "}"
        return $uuid;
    }
}

// extract files from an sco archive
function sco_node_unpack($file, $dir) {

  $archiver = archiver_get_archiver($file->uri);
  if (!$archiver) {
    drupal_set_message(t('Cannot extract %file, not a valid archive.', array ('%file' => $file)));
    return FALSE;
  }
  $archiver->extract($dir);
  
  return sco_node_enumerate_sco($dir);
}

// return archive file list
function sco_node_enumerate_sco($dir) {

  return file_scan_directory($dir, '/.*\.*$/');
}

// parse an sco manifest file
function sco_node_parse_imsmanifest($file) {

  $manifest = FALSE;
  $contents = file_get_contents($file->uri);
  
  $parser = xml_parser_create();
  xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0);
  xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);

  $ok = xml_parse_into_struct($parser, $contents, $values, $tags);
  xml_parser_free($parser);

  if ($ok) {

    $manifest = new StdClass();
    $manifest->identifier = '';
    $manifest->version = '';
    $manifest->schema = '';
    $manifest->schemaversion = '';
    $manifest->root = '';
    $manifest->resource_root = '';
    $manifest->organizations = array();
    $manifest->resources = array();
    $manifest->sequencing = array();
    
    $default_org_id = '';
    $organization = NULL;
    $resource = NULL;
    $item = NULL;
    $item_stack = array();
    $stack = array();
    $ctag = '';
    
    // iterate through values
    foreach ($values as $e) {
    
      // open tag - set the current open object
      if ($e['type'] == 'open') {
    
        $tag = $e['tag'];
        if ($tag == 'manifest') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $ctag = $tag;
          $manifest->identifier = isset($e['attributes']['identifier']) ? $e['attributes']['identifier'] : '';
          $manifest->version = isset($e['attributes']['version']) ? $e['attributes']['version'] : '';
          $manifest->root = isset($e['attributes']['xml:base']) ? $e['attributes']['xml:base'] : '';
        }
        elseif ($tag == 'metadata') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $ctag = $tag;
        }
        elseif ($tag == 'organizations') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $ctag = $tag;
          $default_org_id = isset($e['attributes']['default']) ? $e['attributes']['default'] : '';
        }
        elseif ($tag == 'organization') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $ctag = $tag;
          $organization = new StdClass();
          $organization->id = isset($e['attributes']['identifier']) ? $e['attributes']['identifier'] : '';
          $organization->default = FALSE;
          if ($organization->id == $default_org_id) {
            $organization->default = TRUE;
          }
          $organization->items = array();
          $organization->controlModeChoice = FALSE;
          $organization->controlModeFlow = FALSE;
        }
        elseif ($tag == 'item') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          if ($ctag == 'item') {
            array_push($item_stack, $item);
          }
          else {
            $ctag = $tag;
          }
          $item = new StdClass();
          $item->id = isset($e['attributes']['identifier']) ? $e['attributes']['identifier'] : '';
          $item->res_id = isset($e['attributes']['identifierref']) ? $e['attributes']['identifierref'] : '';
          $item->parms = isset($e['attributes']['parameters']) ? $e['attributes']['parameters'] : '';
          $item->timelimitaction = '';
          $item->lmsdata = '';
          $item->completionThreshold = FALSE;
          $item->completedByMeasure = FALSE;
          $item->minProgressMeasure = FALSE;
          $item->progressWeight = FALSE;
          $item->items = array();
          $item->objectives = array();
          $item->completionSetByContent = FALSE;
          $item->objectiveSetByContent = FALSE;
        }
        elseif ($tag == 'resources') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $manifest->resource_root = isset($e['attributes']['xml:base']) ? $e['attributes']['xml:base'] : '';
        }
        elseif ($tag == 'resource') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $resource = new StdClass();
          $resource->id = isset($e['attributes']['identifier']) ? $e['attributes']['identifier'] : '';
          $resource->type = isset($e['attributes']['type']) ? $e['attributes']['type'] : '';
          $resource->sco_type = isset($e['attributes']['adicp:scormType']) ? $e['attributes']['adicp:scormType'] : '';
          $resource->href = isset($e['attributes']['href']) ? $e['attributes']['href'] : '';
          $resource->root = isset($e['attributes']['xml:base']) ? $e['attributes']['xml:base'] : '';
          $resource->files = array();
          $resource->depends = array();
        }
        elseif ($tag == 'imsss:sequencing') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
        }
        elseif ($tag == 'imsss:objectives') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
        }
        elseif ($tag == 'imsss:primaryObjective') {
          if ($ctag) {
            array_push($stack, $ctag);
          }
          $objective = new StdClass();
          $objective->primary = true;
          $objective->id = isset($e['attributes']['objectiveID']) ? $e['attributes']['objectiveID'] : '';
          $objective->satisfiedByMeasure = isset($e['attributes']['satisfiedByMeasure']) ? $e['attributes']['satisfiedByMeasure'] : FALSE;
        }
      }
      
      // complete tag - set a value
      elseif ($e['type'] == 'complete') {

        $tag = $e['tag'];
        
        if ($tag == 'schema') {
          $manifest->schema = isset($e['value']) ? $e['value'] :'';
        }
        elseif ($tag == 'schemaversion') {
          $manifest->schemaversion = isset($e['value']) ? $e['value'] :'';
        }
        elseif ($tag == 'title') {
          if ($ctag == 'organization') {
            $organization->title = isset($e['value']) ? $e['value'] :'';
          }
          else if ($ctag == 'item') {
            $item->title = isset($e['value']) ? $e['value'] :'';
          }
        }
        elseif ($tag == 'file') {
          $resource->files[] = isset($e['attributes']['href']) ? $e['attributes']['href'] : '';
        }
        elseif ($tag == 'dependency') {
          $resource->depends[] = isset($e['attributes']['identifierref']) ? $e['attributes']['identifierref'] : '';
        }
        elseif ($tag == 'adlcp:timeLimitAction') {
          $item->timelimitaction = isset($e['value']) ? $e['value'] :'';
        }
        elseif ($tag == 'adlcp:dataFromLMS') {
          $item->lmsdata = isset($e['value']) ? $e['value'] :'';
        }
        elseif ($tag == 'adlcp:completionThreshold') {
          $item->completionThreshold = isset($e['value']) ? $e['value'] : 0;
          $item->completedByMeasure = isset($e['attributes']['completedByMeasure']) ? $e['attributes']['completedByMeasure'] : 0;
          $item->minProgressMeasure = isset($e['attributes']['minProgressMeasure']) ? $e['attributes']['minProgressMeasure'] : 0;
          $item->progressWeight = isset($e['attributes']['progressWeight']) ? $e['attributes']['progressWeight'] : 0;
        }
        elseif ($tag == 'imsss:objective') {
          $objective = new StdClass();
          $objective->primary = false;
          $objective->id = isset($e['attributes']['objectiveID']) ? $e['attributes']['objectiveID'] : '';
          $item->objectives[] = $objective;
        }
        elseif ($tag == 'imsss:minNormalizedMeasure') {
          $objective->minNormalizedMeasure = isset($e['value']) ? $e['value'] : 0;
        }
        elseif ($tag == 'imsss:deliveryControls') {
          $item->completionSetByContent = isset($e['attributes']['completionSetByContent']) ? $e['attributes']['completionSetByContent'] : FALSE;
          $item->objectiveSetByContent = isset($e['attributes']['objectiveSetByContent']) ? $e['attributes']['objectiveSetByContent'] : FALSE;
        }
        elseif ($tag == 'imsss:controlMode') {
          $organization->controlModeChoice = isset($e['attributes']['choice']) ? $e['attributes']['choice'] : FALSE;
          $organization->controlModeFlow = isset($e['attributes']['flow']) ? $e['attributes']['flow'] : FALSE;
        }
      }
      
      // close the open object and pop the previous open object
      elseif ($e['type'] == 'close') {
      
        $tag = $e['tag'];
      
        if ($tag == 'metadata') {
          $ctag = array_pop($stack);
        }
        elseif ($tag == 'organizations') {
          $ctag = array_pop($stack);
        }
        elseif ($tag == 'organization') {
          $ctag = array_pop($stack);
          $manifest->organizations[] = $organization;
          $organization = NULL;
        }
        elseif ($tag == 'item') {
          $ctag = array_pop($stack);
          if ($ctag == 'item') {
            $parent_item = array_pop($item_stack);
            $parent_item->items[] = $item;
            $item = $parent_item;
          }
          else {
            $organization->items[] = $item;
            $item = NULL;
          }
        }
        elseif ($tag == 'resources') {
          $ctag = array_pop($stack);
        }
        elseif ($tag == 'resource') {
          $ctag = array_pop($stack);
          $manifest->resources[] = $resource;
          $resource = NULL;
        }
        elseif ($tag == 'imsss:sequencing') {
          $ctag = array_pop($stack);
        }
        elseif ($tag == 'imsss:objectives') {
          $ctag = array_pop($stack);
        }
        elseif ($tag == 'imsss:primaryObjective') {
          $ctag = array_pop($stack);
          $item->objectives[] = $objective;
        }
      }
    }
  }  
  
  return $manifest;
}

function sco_node_get_organization($manifest, $org_id = FALSE) {
  
  $org = FALSE;
  
  foreach ($manifest->organizations as $o) {
    // if no org id specified and org is default, return it
    if (!$org_id && $o->default) {
      $org = $o;
      break;
    }
    // check for id match
    if ($org_id && $o->id == $org_id) {
      $org = $o;
      break;
    }
  }
  
  return $org;
}

function sco_node_get_resource($manifest, $res_id) {

  $res = FALSE;
  
  foreach ($manifest->resources as $r) {
    if ($r->id == $res_id) {
      $res = $r;
      break;
    }
  }
  
  return $res;
}