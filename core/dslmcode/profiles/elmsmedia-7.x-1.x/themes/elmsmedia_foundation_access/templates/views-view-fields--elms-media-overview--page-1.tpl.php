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
  $type = '';
  if (isset($fields['type_1']) && isset($fields['type_1']->content)) {
    $type = $fields['type_1']->content;
  }
  // assemble preview
  if (isset($fields['field_poster'])) {
    $preview = $fields['field_poster']->content;
  }
  elseif ($type == 'document') {
    $preview = $fields['field_document_file']->content;
  }
  elseif (isset($fields['field_image'])) {
    $preview = str_replace('<img', '<img alt="' . t('View @title', array('@title' => $row->node_title)) . '"', $fields['field_image']->content);
  }
  elseif (isset($fields['field_images'])) {
    $images = '';
    // build the images out as a row
    foreach ($row->field_field_images as $image_array) {
      $build_image = array(
        'style_name' => 'image_card_medium',
        'path' => $image_array['raw']['entity']->field_image['und'][0]['uri'],
        'attributes' => array(
          'alt' => $image_array['raw']['entity']->title,
          'title' => $image_array['raw']['entity']->title,
        ),
      );
      // create the image
      $image = theme('image_style', $build_image);
      $images .= '<div class="carousel-item">' . $image . '</div>';
    }
    $preview = '<div class="carousel carousel-slider center" data-indicators="true">' . $images . '</div>';
  }
  elseif (isset($fields['field_external_media'])) {
    $preview = $fields['field_external_media']->content;
  }
  elseif (isset($fields['field_svg'])) {
    $preview = '<span class="element-invisible">' . t('View @title', array('@title' => $row->node_title)) . '</span>' . $fields['field_svg']->content;
  }
  elseif ($type == 'h5p_content') {
    $h5ptype = str_replace('.', '', str_replace(' ', '', strtolower($fields['title_1']->content)));
    // loop through known h5p types and pick an image for it
    switch ($h5ptype) {
      case 'accordion':
      case 'chart':
      case 'collage':
      case 'coursepresentation':
      case 'dialogcards':
      case 'documentationtool':
      case 'draganddrop':
      case 'dragtext':
      case 'fillintheblanks':
      case 'imagehotspots':
      case 'findthehotspot':
      case 'flashcards':
      case 'guesstheanswer':
      case 'iframeembedder':
      case 'markthewords':
      case 'multiplechoice':
      case 'memorygame':
      case 'timeline':
      case 'twitteruserfeed':
      case 'singlechoiceset':
      case 'summary':
      case 'questionset':
      case 'appearinforchatandtalk':
      case 'interactivevideo':
        $preview = '<img src="' . base_path() . drupal_get_path('module', 'elmsmedia_h5p') . '/images/' . $h5ptype . '.png" alt="' . $row->node_title . '" title="' . $row->node_title . '" />';
      break;
      // h5p types we don't have an icon for at least present a title on a blank card
      default:
        $preview = '<div class="elmsln-no-preview-item  light-blue lighten-5 accessible-red-text">' . $fields['title_1']->content . '</div>';
      break;
    }
    $preview .= '<img src="' . base_path() . drupal_get_path('module', 'elmsmedia_h5p') . '/images/h5p.png" class="h5p-overlay-icon" alt="" title="" />';
  }
  elseif ($type == 'figurelabel') {
    $noderender = node_view($row->_field_data['nid']['entity'], 'figurelabel');
    $preview = render($noderender);
  }
  else {
    $preview = '<div class="elmsln-no-preview-item  light-blue lighten-5 accessible-red-text">' . $fields['type']->content . '</div>';
  }

  // course
  if (isset($fields['field_cis_course_ref'])) {
    $course = $fields['field_cis_course_ref']->content;
  }
  else {
    $course = t('no course');
  }
?>
<div class="col s12 m6 l4 elmsln-card">
  <div class="card small sticky-action">
    <div class="card-image waves-effect waves-block waves-light">
      <?php print l($preview, 'node/' . $row->nid . '/view_modes', array('html' => TRUE)); ?>
    </div>
    <div class="card-content">
      <span class="card-title activator grey-text text-darken-4">
        <span class="truncate elmsln-card-title accessible-red-text">
          <?php print l($row->node_title, 'node/' . $row->nid . '/view_modes', array('attributes' => array('class' => 'accessible-red-text')));?>
        </span>
        <i class="material-icons right accessible-red-text" tabindex="0" role="button">more_vert</i>
      </span>
    </div>
    <div class="card-action">
      <?php print l('view', 'node/' . $row->nid . '/view_modes', array('attributes' => array('class' => 'accessible-red-text')));?>
      <?php print l('edit', 'node/' . $row->nid . '/edit', array('attributes' => array('class' => 'accessible-red-text')));?>
    </div>
    <div class="card-reveal">
      <span class="card-title grey-text text-darken-4"><span class="truncate elmsln-card-title"><?php print l($row->node_title, 'node/' . $row->nid . '/view_modes', array('attributes' => array('class' => 'accessible-red-text')));?></span><i class="material-icons right accessible-red-text" tabindex="0" role="button"><?php print t('close');?></i></span>
      <ul class="collection">
        <li class="collection-item">
          <span><?php print $fields['type']->content;?></span>
          <span class="secondary-content"><i class="tiny material-icons accessible-red-text">info_outline</i></span>
        </li>
        <li class="collection-item">
          <span><?php print $course;?></span>
          <span class="secondary-content"><i class="tiny material-icons accessible-red-text">library_books</i></span>
        </li>
        <li class="collection-item">
          <span><?php print $fields['changed']->content;?></span>
          <span class="secondary-content"><i class="tiny material-icons accessible-red-text">schedule</i></span>
        </li>
        <li class="collection-item">
          <span class="secondary-content"><i class="tiny material-icons accessible-red-text">label</i></span>
          <span class="tags"><?php print $fields['field_tagging']->content;?></span>
        </li>
      </ul>
    </div>
  </div>
</div>
