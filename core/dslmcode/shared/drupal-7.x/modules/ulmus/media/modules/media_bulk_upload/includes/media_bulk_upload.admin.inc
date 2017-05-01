<?php

/**
 * @file
 * This file contains the admin functions for the Media Bulk Upload module.
 */

/**
 * Form callback for mass import.
 */
function media_bulk_upload_import($form, &$form_state) {
  if (!isset($form_state['storage']['files'])) {
    $form_state['storage']['step'] = 'choose';
    $form_state['storage']['next_step'] = 'preview';
    $form['directory'] = array(
      '#type' => 'textfield',
      '#title' => t('Directory'),
      '#description' => t('Enter the absolute directory on the web server to look for files. Subdirectories inside this directory will not be scanned.'),
      '#required' => TRUE,
    );

    $form['pattern'] = array(
      '#type' => 'textarea',
      '#title' => t('Pattern'),
      '#description' => t("Only files matching these patterns will be imported. Enter one pattern per line. The '*' character is a wildcard. Example patterns are %png_example to import all PNG files.", array('%png_example' => '*.png')),
      '#default_value' => '*',
      '#required' => TRUE,
    );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Preview'),
    );
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => isset($_GET['destination']) ? $_GET['destination'] : 'admin/content/file',
    );
  }
  else {
    $form['preview'] = array(
      '#markup' => theme('item_list', array('items' => $form_state['storage']['files'])),
    );

    $form = confirm_form($form, t('Import these files?'), 'admin/content/file/import');
  }
  return $form;

}

/**
 * Validate handler for media_import().
 */
function media_bulk_upload_import_validate($form, &$form_state) {
  if ($form_state['values']['op'] != t('Confirm')) {
    $directory = $form_state['values']['directory'];
    $pattern = $form_state['values']['pattern'];
    if (!is_dir($directory)) {
      form_set_error('directory', t('The provided directory does not exist.'));
    }
    if (!is_readable($directory)) {
      form_set_error('directory', t('The provided directory is not readable.'));
    }

    $pattern_quoted = preg_quote($pattern, '/');
    $pattern_quoted = preg_replace('/(\r\n?|\n)/', '|', $pattern_quoted);
    $pattern_quoted = strtr($pattern_quoted, array(
      '\\|' => '|',
      '\\*' => '.*',
      '\\?' => '.?',
    ));
    $files = file_scan_directory($directory, '/^(' . $pattern_quoted . ')$/', array('recurse' => FALSE));
    $files = array_keys($files);
    if (empty($files)) {
      form_set_error('pattern', t('No files were found in %directory matching the regular expression %pattern', array('%directory' => $directory, '%pattern' => $pattern_quoted)));
    }
    $form_state['storage']['files'] = $files;
  }
}

/**
 * Submit handler for media_import().
 */
function media_bulk_upload_import_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Confirm')) {
    $files = $form_state['storage']['files'];
    $batch = array(
      'title' => t('Importing'),
      'operations' => array(
        array('media_bulk_upload_import_batch_import_files', array($files)),
      ),
      'finished' => 'media_bulk_upload_import_batch_import_complete',
      'file' => drupal_get_path('module', 'media_bulk_upload') . '/includes/media_bulk_upload.admin.inc',
    );
    batch_set($batch);
    return;

  }
  $form_state['rebuild'] = TRUE;
}

/**
 * BatchAPI callback op for media import.
 */
function media_bulk_upload_import_batch_import_files($files, &$context) {
  if (!isset($context['sandbox']['files'])) {
    // This runs the first time the batch runs.
    // This is stupid, but otherwise, I don't think it will work...
    $context['results'] = array('success' => array(), 'errors' => array());
    $context['sandbox']['max'] = count($files);
    $context['sandbox']['files'] = $files;
  }
  $files =& $context['sandbox']['files'];

  // Take a cut of files.  Let's do 10 at a time.
  $import_batch_size = variable_get('media_bulk_upload_import_batch_size', 20);
  $length = (count($files) > $import_batch_size) ? $import_batch_size : count($files);
  $to_process = array_splice($files, 0, $length);
  $image_in_message = '';

  foreach ($to_process as $file) {
    try {
      $file_obj = media_parse_to_file($file);
      $context['results']['success'][] = $file;
      if (!$image_in_message) {
        // @todo Is this load step really necessary? When there's time, test
        //   this, and either remove it, or comment why it's needed.
        $loaded_file = file_load($file_obj->fid);
        $image_in_message = file_view_file($loaded_file, 'preview');
      }
    }
    catch (Exception $e) {
      $context['results']['errors'][] = $file . " Reason: " . $e->getMessage();
    }
  }

  $context['message'] = "Importing " . theme('item_list', array('items' => $to_process));
  // Show the image that is being imported.
  $context['message'] .= drupal_render($image_in_message);

  $context['finished'] = ($context['sandbox']['max'] - count($files)) / $context['sandbox']['max'];
}

/**
 * BatchAPI complete callback for media import.
 */
function media_bulk_upload_import_batch_import_complete($success, $results, $operations) {
  if ($results['errors']) {
    drupal_set_message(theme('item_list', array('items' => $results['errors'])), 'error');
  }
  if ($results['success']) {
    drupal_set_message(theme('item_list', array('items' => $results['success'])));
  }
}
