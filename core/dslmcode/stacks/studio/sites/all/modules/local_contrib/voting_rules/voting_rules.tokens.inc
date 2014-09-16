<?php
// $Id$

/**
 * @file
 * Builds placeholder replacement tokens.
 */

/**
 * Implements hook_tokens().
 */
function voting_rules_tokens($type, $tokens, array $data = array(), array $options = array()) {
	$replacements = array();
  $sanitize = !empty($options['sanitize']);

  if ($type == 'vote' && !empty($data['vote'])) {
    foreach ($tokens as $name => $original) {
    	$replacements[$original] = $data[$type][str_replace('-', '_', $name)];
    }
  }

  else if ($type == 'vote_results' && !empty($data['vote_results'])) {
    foreach ($tokens as $name => $original) {
  		$explode = explode('_', str_replace('-', '_', $name));
  		$function = $explode[0];
  		unset($explode[0]);
  		$property = implode('_', $explode);
  		
  		$replacements[$original] = $data[$type][$function][$property];
    }
  }

  return $replacements;
}

/**
 * Implements hook_token_info().
 */
function voting_rules_token_info() {
	module_load_include('inc', 'voting_rules', 'voting_rules.rules');
	
	$data_info = voting_rules_rules_data_info();

	foreach ($data_info as $type => $data) {
	  $info['types'][$type] = array(
	    'name' => $data['label'],
	    'description' => isset($data['description']) ? $data['description'] : NULL,
	    'needs-data' => $type,
	  );
		
		_voting_rules_token_data_info_recursion($info, $type, $data);
	}

  return $info;
}

/**
 * Recursively build token info.
 */
function _voting_rules_token_data_info_recursion(&$info, $type, $data, $prefix = NULL) {
	if (isset($data['property info'])) {
		foreach ($data['property info'] as $property_name => $property_info) {
			$formatted_name = str_replace('_', '-', $property_name);
			$formatted_name = isset($prefix) ? $prefix . '-' . $formatted_name : $formatted_name;
			
			if (!isset($property_info['property info'])) {				
			  $info['tokens'][$type][$formatted_name] = array(
			    'name' => $property_info['label'],
			    'description' => isset($property_info['description']) ? $property_info['description'] : NULL,
			  );
			}
			
		  _voting_rules_token_data_info_recursion($info, $type, $property_info, $formatted_name);
		}
	}
}
