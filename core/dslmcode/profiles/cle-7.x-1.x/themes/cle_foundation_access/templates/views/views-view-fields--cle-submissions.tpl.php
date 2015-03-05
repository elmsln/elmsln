<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
  // account for radioactivity
  $opacity_style = '';
  if (!empty($row->_field_data['nid']['entity']->field_energy)) {
    $energy = $row->_field_data['nid']['entity']->field_energy['und'][0]['radioactivity_energy']; 
    if ($energy >= 0) {
      $opacity = 1 - ((100 - $energy) / 100);
      if ($opacity < .2) {
        $opacity = .2;
      }
      $opacity_style = ' style="opacity:' . $opacity;
    }
    $opacity_style .= ';"';
  }
  // pull background style
  $item_style = 'background-color:#';
  if (!empty($row->field_field_color)) {
    $item_style .= $row->field_field_color[0]['rendered']['#markup'];
  }
  else {
  $item_style .= CLE_ASSIGNMENT_DEFAULT_COLOR;
  }
  // generate hover-container info
  print '<a' . $opacity_style . ' href="node/' . $row->_field_data['nid']['entity']->nid . '" class="cle-tile-wrapper" id="cle-node-' . $row->_field_data['nid']['entity']->nid . '">';
?>
<?php foreach ($fields as $id => $field):

 if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>
  <?php
    print $field->wrapper_prefix;
    print $field->label_html;
		print '<div style="' . $item_style . '">';
		if ($id == 'field_images' && $field->content == '<div class="field-content cle-image"></div>') {
			print '<div class="field-content cle-image"><img src="' . base_path() . drupal_get_path('module', 'cle_submission') . '/images/video.png" width="250px" height="150px" /></div>';
		}
    else {
			print $field->content;
		}
		print '</div>';
    print $field->wrapper_suffix;
  ?>
<?php endforeach; ?>
<?php print '</a>';