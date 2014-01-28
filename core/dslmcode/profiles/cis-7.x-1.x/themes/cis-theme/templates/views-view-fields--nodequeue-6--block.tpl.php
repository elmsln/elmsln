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
 global $tmp_featured_row;
 $tmp_featured_row++;
foreach ($fields as $id => $field) {
	if ($tmp_featured_row == 1) {
		if ($id == 'field_news_image') {
			print $field->wrapper_prefix ."\n";
			print $field->label_html ."\n";
			print $field->content ."\n";
			print $field->wrapper_suffix ."\n";
			print '</div><div class="columns small-12 large-6">';
		}
		else if ($id == 'field_color') {
			print $field->content ."\n";
		}
		else if($id == 'title') {
			print $field->wrapper_prefix ."\n";
			print $field->label_html ."\n";
			print '<h2 class="featured-front-page-h2-title">'. $field->content ."</h2>\n";
			print $field->wrapper_suffix ."\n";
		}
		else {
			print $field->wrapper_prefix ."\n";
			print $field->label_html ."\n";
			print $field->content ."\n";
			print $field->wrapper_suffix ."\n";
		}
	}
	else {
		if ($id != 'field_news_image' && $id != 'field_subtext') {
			print $field->wrapper_prefix ."\n";
			print $field->label_html ."\n";
			print $field->content ."\n";
			print $field->wrapper_suffix ."\n";
		}
	}
}
?>