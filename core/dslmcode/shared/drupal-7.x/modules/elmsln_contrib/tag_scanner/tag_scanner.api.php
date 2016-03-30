<?php

/**
 * Example of hook_tag_scanner_tag_list_alter
 *
 * Allows you to add information about the tag to the table output.
 * @param  array 										&$value          
 *         														- keys 						table header label
 *         				          					- value 					information about the tag
 * @param  entity_metadata_wrapper 	$entity_wrapper 		wrapper of the parent entity containing the tag.
 * @param  string 									$bundle         		machine name of the parent entity bundle
 * @param  string 									$field          		machine name of the parent entity field containing contains the tag.
 */
function hook_tag_scanner_tag_list_alter(&$value, $entity_wrapper, $bundle, $field) {
	if (isset($entity_wrapper->book)) {
		$value = array('#bid' => $entity_wrapper->book->value()->book['bid']) + $value;
		$value = array('#book_title' => $entity_wrapper->book->value()->book['title']) + $value;
	}
}