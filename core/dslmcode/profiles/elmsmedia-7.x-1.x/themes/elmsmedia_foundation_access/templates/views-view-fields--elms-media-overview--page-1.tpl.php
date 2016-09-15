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
  foreach ($fields as $id => $field):
    //dpm($id);
  //dpm($field);
  endforeach;

  // assemble preview
  if (isset($fields['field_poster'])) {
    $preview = $fields['field_poster']->content;
  }
  elseif (isset($fields['field_document_file'])) {
    $preview = $fields['field_document_file']->content;
  }
  elseif (isset($fields['field_image'])) {
    $preview = $fields['field_image']->content;
  }
  elseif (isset($fields['field_images'])) {
    $preview = $fields['field_images']->content;
  }
  elseif (isset($fields['field_external_media'])) {
    $preview = $fields['field_external_media']->content;
  }
  elseif (isset($fields['field_svg'])) {
    $preview = $fields['field_svg']->content;
  }
  else {
    $preview = '<div class="elmsmedia-no-preview-item  light-blue lighten-5">' . t('no preview') . '</div>';
  }

  // course
  if (isset($fields['field_cis_course_ref'])) {
    $course = $fields['field_cis_course_ref']->content;
  }
  else {
    $course = 'no course';
  }
?>
<div class="col s12 m6 l4 elmsmedia-card">
  <div class="card small sticky-action">
    <div class="card-image waves-effect waves-block waves-light">
      <?php print $preview; ?>
    </div>
    <div class="card-content">
      <span class="card-title activator grey-text text-darken-4"><span class="truncate elmsln-card-title"><?php print $row->node_title;?></span><i class="material-icons right">more_vert</i></span>
    </div>
    <div class="card-action">
      <?php print l('view', 'node/' . $row->nid . '/view_modes');?>
      <?php print l('edit', 'node/' . $row->nid . '/edit');?>
    </div>
    <div class="card-reveal">
      <span class="card-title grey-text text-darken-4"><span class="truncate elmsln-card-title"><?php print $row->node_title;?></span><i class="material-icons right"><?php print t('close');?></i></span>
      <ul class="collection">
        <li class="collection-item">
          <span><?php print $fields['type']->content;?></span>
          <span class="secondary-content"><i class="tiny material-icons">info_outline</i></span>
        </li>
        <li class="collection-item">
          <span><?php print $course;?></span>
          <span class="secondary-content"><i class="tiny material-icons">library_books</i></span>
        </li>
        <li class="collection-item">
          <span><?php print $fields['changed']->content;?></span>
          <span class="secondary-content"><i class="tiny material-icons">schedule</i></span>
        </li>
        <li class="collection-item">
          <span class="secondary-content"><i class="tiny material-icons">label</i></span>
          <span class="tags"><?php print $fields['field_tagging']->content;?></span>
        </li>
      </ul>
    </div>
  </div>
</div>
