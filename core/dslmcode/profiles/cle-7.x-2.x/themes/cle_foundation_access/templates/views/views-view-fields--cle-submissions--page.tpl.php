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
  $noimages = FALSE;
  // ensure we have images, otherwise we can't show a preview at this time
  if (isset($row->field_field_images) && count($row->field_field_images) > 0) {
    $images = '';
  }
  else {
    $images = '<div class="elmsln-no-preview-item blue darken-4 white-text">' . t('no preview') . '</div>';
    $noimages = TRUE;
  }
  // build the images out as a row
  foreach ($row->field_field_images as $image_array) {
    $build_image = array(
      'style_name' => 'cle_submission',
      'path' => $image_array['rendered']['#item']['uri'],
    );
    $link_ary = array(
      'html' => TRUE,
      'attributes' => array(
        'class' => 'colorbox',
        'rel' => 'gallery-all',
      )
    );
    // create the image
    $image = l(theme('image_style', $build_image), file_create_url($image_array['rendered']['#item']['uri']), $link_ary);
    $images .= '<div class="carousel-item ferpa-protect">' . $image . '</div>';
  }
?>
<div class="col s12 m6 l4 elmsln-card">
  <div class="card small sticky-action">
    <div class="card-image waves-effect waves-block waves-light">
    <?php if ($noimages): ?>
      <?php print $images; ?>
    <?php else: ?>
       <div class="carousel carousel-slider center" data-indicators="true">
         <?php print $images; ?>
      </div>
    <?php endif; ?>
    </div>
    <div class="card-content">
      <span class="card-title activator grey-text text-darken-4">
        <span class="truncate elmsln-card-title">
          <?php print l($row->node_title, 'node/' . $row->nid, array('attributes' => array('class' => 'cis-lmsless-text')));?>
        </span>
        <i class="material-icons right cis-lmsless-text" tabindex="0" role="button">more_vert</i>
      </span>
    </div>
    <div class="card-action">
      <?php print l('<paper-button raised>Comment</paper-button>', 'node/' . $row->nid, array('html' => TRUE, 'attributes' => array('class' => 'cis-lmsless-text')));?>
      <?php if (isset($row->node_new_comments) && $row->node_new_comments > 0) : ?>
      <span class="new badge cis-lmsless-color darken-4"><?php print $row->node_new_comments;?></span>
    <?php endif;?>
    </div>
    <div class="card-reveal">
      <span class="card-title grey-text text-darken-4"><span class="truncate elmsln-card-title"><?php print l($row->node_title, 'node/' . $row->nid, array('attributes' => array('class' => 'cis-lmsless-text')));?></span><i class="material-icons right cis-lmsless-text"><?php print t('close');?></i></span>
      <ul class="collection">
        <li class="collection-item">
          <span class="ferpa-protect"><?php print $row->users_node_name?></span>
          <span class="secondary-content"><i class="tiny material-icons cis-lmsless-text">assignment_ind</i></span>
        </li>
        <li class="collection-item">
          <span><?php print $row->node_field_data_field_assignment_title;?></span>
          <span class="secondary-content"><i class="tiny material-icons cis-lmsless-text">assignment</i></span>
        </li>
        <li class="collection-item">
          <span><?php print $fields['changed']->content;?></span>
          <span class="secondary-content"><i class="tiny material-icons cis-lmsless-text">schedule</i></span>
        </li>
        <li class="collection-item">
          <span class="secondary-content"><i class="tiny material-icons cis-lmsless-text">comment</i></span>
          <span class="comments-count"><?php print format_plural($row->node_comment_statistics_comment_count, '@num comment', '@num commments', array('@num' => $row->node_comment_statistics_comment_count)) ;?></span>
        </li>
      </ul>
    </div>
  </div>
</div>
