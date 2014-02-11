<?php

/**
 * @file
 * Media Theming
 *
 * Theming functions for the Media module.
 */


/**
 * Display a media file list.
 *
 * @param array $element
 *   The form element.
 *
 * @return string
 *   HTML of the file list
 */
function theme_media_file_list($element) {
  // Add the CSS for our display.
  return '<div class="media-file-list">' . theme('form_element', $element, $element['#children']) . '</div>';
}

/**
 * Add messages to the page.
 */
function template_preprocess_media_dialog_page(&$variables) {
  $variables['messages'] = theme('status_messages');
}

/**
 * Adds a wrapper around a preview of a media file.
 */
function theme_media_thumbnail($variables) {
  $label = '';
  $element = $variables['element'];

 // Wrappers to go around the thumbnail.
  $attributes = array(
    'title' => $element['#name'],
    'class' => 'media-item',
    'data-fid' => $element['#file']->fid,
  );
  $prefix = '<div ' . drupal_attributes($attributes) . '><div class="media-thumbnail">';
  $suffix = '</div></div>';

  // Arguments for the thumbnail link.
  $thumb = $element['#children'];
  $target = 'file/' . $element['#file']->fid . '/edit';
  $options = array(
    'query' => drupal_get_destination(),
    'html' => TRUE,
    'attributes' => array('title' => t('Click to edit details')),
  );

  // Element should be a field renderable array. This should be improved.
  if (!empty($element['#show_names']) && $element['#name']) {
    $label = '<div class="label-wrapper"><label class="media-filename">' . $element['#name'] . '</label></div>';
  }

  $output = $prefix;
  if (!empty($element['#add_link'])) {
    $output .= l($thumb, $target, $options);
  }
  else {
    $output .= $thumb;
  }
  $output .= $label . $suffix;
  return $output;
}

/**
 * Preprocess the media thumbnail.
 */
function template_preprocess_media_thumbnail(&$variables) {
  // Set the name for the thumbnail to be the filename.  This is done here so
  // that other modules can hijack the name displayed if it should not be the
  // filename.
  $variables['element']['#name'] = isset($variables['element']['#file']->filename) ? check_plain($variables['element']['#file']->filename) : NULL;
}

/**
 * Field formatter for displaying a file as a large icon.
 */
function theme_media_formatter_large_icon($variables) {
  $file = $variables['file'];
  $icon_dir = variable_get('media__icon_base_directory', 'public://media-icons') . '/' . variable_get('media__icon_set', 'default');
  $icon = file_icon_path($file, $icon_dir);
  $variables['path'] = $icon;

  // theme_image() requires the 'alt' attribute passed as its own variable.
  // @see http://drupal.org/node/999338
  if (!isset($variables['alt']) && isset($variables['attributes']['alt'])) {
    $variables['alt'] = $variables['attributes']['alt'];
  }

  // Add image height and width for the image theme functions.
  if ($info = image_get_info($icon)) {
    $variables += $info;
  }

  if ($variables['style_name']) {
    $output = theme('image_style', $variables);
  }
  else {
    $output = theme('image', $variables);
  }
  return $output;
}
