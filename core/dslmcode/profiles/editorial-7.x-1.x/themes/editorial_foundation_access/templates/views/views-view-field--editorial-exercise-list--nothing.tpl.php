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
if (isset($row->tid)) {
	if ($gid = _cis_section_load_section_by_id(_cis_connector_section_context())) {
	  $field_conditions = array('og_group_ref' => array('target_id', array($gid), 'IN'));
	}
	$field_conditions['field_editorial_exercise'] = array('tid', array($row->tid), 'IN');
	$submission = _cis_connector_assemble_entity_list('node', 'editorial_journal_entry', 'nid', 'title', $field_conditions, array('uid' => $GLOBALS['user']->uid));
	$output = '';
	foreach ($submission as $nid => $title) {
		$output .= l($title, 'node/' . $nid) . ' ';
	}
}
if (empty($output)) {
	$output = l(t('Submit entry'),'node/add/editorial-journal-entry', array('query' => array('edit[field_editorial_exercise][und]=' => $row->tid)));
}
?>
<?php print $output; ?>