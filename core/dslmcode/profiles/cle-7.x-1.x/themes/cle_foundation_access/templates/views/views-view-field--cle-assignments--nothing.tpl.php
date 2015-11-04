<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

// hate doing things this way but it's so much faster
if (isset($row->node_field_data_field_cle_assignments_nid)) {
	if ($gid = _cis_section_load_section_by_id(_cis_connector_section_context())) {
	    $field_conditions = array('og_group_ref' => array('target_id', array($gid), 'IN'));
	}
	$field_conditions['field_assignment'] = array('target_id', array($row->node_field_data_field_cle_assignments_nid), 'IN');
	$submission = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', 'title', $field_conditions, array('uid' => $GLOBALS['user']->uid));
	$items= array();
	foreach ($submission as $nid => $title) {
		$items[] = l($title,'node/' . $nid);
	}
	if (empty($items)) {
		$output = l(t('Submit assignment'),'node/add/cle-submission', array('query' => array('field_assignment' => $row->node_field_data_field_cle_assignments_nid)));
	}
	else {
		if (count($items) > 1) {
			$output = '<ol class="cle-assignment-listing-multi-submission">' . "\n";
			foreach ($items as $item) {
				$output .= '<li>' . $item . '</li>' . "\n";
			}
			$output .= '</ol>' . "\n";
		}
		else {
			// if we only have one thing don't print a list item
			$output = $items[0] . "\n";
		}
	}
}
?>
<?php print $output; ?>