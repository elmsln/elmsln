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
if (isset($row->nid)) {
  $field_conditions['field_ecd_related_asset'] = array('target_id', array($row->nid), 'IN');
  $documentation = _cis_connector_assemble_entity_list('node', 'ecd_documentation', 'nid', 'title', $field_conditions);
  $items= array();
  // loop through any documentation found
  foreach ($documentation as $nid => $title) {
    $items[] = l($title,'node/' . $nid);
  }
  if (empty($items)) {
    $output = l(t('Add documentation'),'node/add/ecd-documentation', array('query' => array('field_ecd_related_asset' => $row->nid, 'destination' => 'assets')));
  }
  else {
    if (count($items) > 1) {
      $output = '<ol class="ecd-asset-listing">' . "\n";
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