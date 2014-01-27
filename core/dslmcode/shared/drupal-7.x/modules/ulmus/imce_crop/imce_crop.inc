<?php

/**
 * Implements hook_form_formID_alter().
 */
function _imce_crop_form_imce_fileop_form_alter(&$form, &$form_state, &$imce) {
  $form['fset_crop'] = array(
    '#type' => 'fieldset',
    '#title' => t('Crop'),
  ) + imce_crop_form($imce);
}

/**
 * Returns crop form.
 */
function imce_crop_form(&$imce) {
  $form['crop_x'] = array(
    '#type' => 'textfield',
    '#title' => t('Start from (X:Y)'),
    '#size' => 4,
    '#maxlength' => 4,
    '#prefix' => '<div class="container-inline">',
  );
  $form['crop_y'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#maxlength' => 4,
    '#prefix' => ':',
    '#suffix' => '</div>',
  );
  $form['crop_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width x Height'),
    '#size' => 4,
    '#maxlength' => 4,
    '#prefix' => '<div class="container-inline">',
  );
  $form['crop_height'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#maxlength' => 4,
    '#prefix' => 'x',
  );
  $form['crop'] = array(
    '#type' => 'submit',
    '#value' => t('Crop'),
    '#submit' => $imce['perm']['crop'] ? array('imce_crop_submit') : NULL,
    '#suffix' => '</div>',
  );
  $form['crop_copy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create a new image'),
    '#default_value' => 1,
  );
  $path = drupal_get_path('module', 'imce_crop');
  $form['#attached'] = array(
    'js' => array($path . '/imce_crop.js'),
    'css' => array($path . '/imce_crop.css'),
  );
  return $form;
}

/**
 * Submits crop form.
 */
function imce_crop_submit($form, &$form_state) {
  $form_state['redirect'] = FALSE;
  $imce =& $form_state['build_info']['args'][0]['imce'];

  // Check dimensions & coordinates
  $x = (int) $form_state['values']['crop_x'];
  $y = (int) $form_state['values']['crop_y'];
  $width = (int) $form_state['values']['crop_width'];
  $height = (int) $form_state['values']['crop_height'];

  $cropped = imce_process_files($form_state['values']['filenames'], $imce, 'imce_crop_image', array($x, $y, $width, $height, $form_state['values']['crop_copy']));

  if (!empty($cropped)) {
    drupal_set_message(t('Image cropping successful: %files.', array('%files' => utf8_encode(implode(', ', $cropped)))));
  }

}

/**
 * Crops an image.
 */
function imce_crop_image($filename, &$imce, $x, $y, $width, $height, $copy = TRUE) {
  $destdir = imce_dir_uri($imce);
  $imguri = $destdir . $filename;

  // Check if the file is an image
  if (!$imce['files'][$filename]['width']) {
    drupal_set_message(t('%filename is not an image.', array('%filename' => utf8_encode($filename))), 'error', FALSE);
    return FALSE;
  }

  // Check boundaries
  if ($x < 0 || $y < 0 || $width < 1 || $height < 1 || $imce['files'][$filename]['width'] < ($x + $width) || $imce['files'][$filename]['height'] < ($y + $height)) {
    drupal_set_message(t('Crop must be inside the image boundaries.'), 'error', FALSE);
    return FALSE;
  }

  // Crop the image
  $image = image_load($imguri);
  if (!$image || !image_crop($image, $x, $y, $width, $height)) {
    drupal_set_message(t('%filename cannot be cropped.', array('%filename' => utf8_encode($filename))), 'error', FALSE);
    return FALSE;
  }

  // Copy to a temp file
  if (!$tempuri = drupal_tempnam('temporary://', 'imce')) {
    return FALSE;
  }
  register_shutdown_function('file_unmanaged_delete', $tempuri);
  if (!image_save($image, $tempuri) || !$image->info) {
    return FALSE;
  }

  // Create file object
  $file = new stdClass();
  $file->uri = $copy ? file_create_filename($filename, $destdir) : $imguri;
  $file->filename = basename($file->uri);

  // Validate quota
  $file->filesize = $image->info['file_size'];
  $quotadiff = $file->filename == $filename ? -$imce['files'][$filename]['size'] : 0;
  if (!imce_validate_quotas($file, $imce, $quotadiff)) {
    return FALSE;
  }

  // Build the rest of the file object
  $file->uid = $imce['uid'];
  $file->filemime = $image->info['mime_type'];
  $file->status = FILE_STATUS_PERMANENT;
  $file->timestamp = REQUEST_TIME;

  // Copy from temp to file uri
  $destination = $file->uri;
  $file->uri = $tempuri;
  if (!$file = file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
    return FALSE;
  }
  imce_file_register($file);

  // Add to the list
  $file->width = $width;
  $file->height = $height;
  imce_add_file($file, $imce);

  return $file;
}