<?php

/**
 * @file
 * Devel generate integration for the File Entity module.
 */

/**
 * Devel generate file form.
 *
 * Options for Devel generate file integration.
 */
function file_entity_generate_file_form() {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('How many files would you like to generate?'),
    '#default_value' => 50,
    '#size' => 4,
  );
  $form['file_types'] = array(
    '#type' => 'select',
    '#title' => t('File types'),
    '#description' => t('Restrict files to these file types.'),
    '#options' => file_entity_type_get_names() + array(FILE_TYPE_NONE => t('Undetermined')),
    '#multiple' => TRUE,
  );
  $form['delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete existing files in specified file types before generating new files.'),
    '#default_value' => FALSE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
  );

  return $form;
}

/**
 * Implements hook_ID_form_submit().
 */
function file_entity_generate_file_form_submit(&$form, &$form_state) {
  $file_types = array_values(array_filter($form_state['values']['file_types']));
  $batch = file_entity_generate_file_batch_info($form_state['values']['count'], $file_types, $form_state['values']['delete']);
  batch_set($batch);
}

/**
 * Implements hook_batch_info().
 */
function file_entity_generate_file_batch_info($count, array $file_types = array(), $delete = FALSE) {
  if (empty($file_types)) {
    $file_types = array_keys(file_entity_type_get_names());
  }

  if ($delete) {
    $operations[] = array('file_entity_generate_file_batch_delete', array($file_types));
  }

  $operations[] = array('file_entity_generate_file_batch_generate', array($file_types, $count));

  return array(
    'operations' => $operations,
    'finished' => 'file_entity_generate_file_batch_finished',
    'file' => drupal_get_path('module', 'file_entity') . '/file_entity.devel_generate.inc',
  );
}

/**
 * Implements hook_batch_delete().
 */
function file_entity_generate_file_batch_delete(array $file_types, array &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_fid'] = 0;
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT fid) FROM {file_managed} WHERE type IN (:types)', array(':types' => $file_types))->fetchField();
  }

  $limit = 20;
  $fids = db_query_range("SELECT fid FROM {file_managed} WHERE type IN (:types) AND fid > :fid ORDER BY fid", 0, $limit, array(':types' => $file_types, ':fid' => $context['sandbox']['current_fid']))->fetchCol();
  file_delete_multiple($fids);

  // Update our progress information.
  $context['sandbox']['progress'] += count($fids);
  $context['sandbox']['current_rid'] = end($fids);
  $context['message'] = t('Deleted file @fid.', array('@fid' => $context['sandbox']['current_rid']));

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

/**
 * Implements hook_generate_file_batch_generate() using Devel generate api.
 */
function file_entity_generate_file_batch_generate(array $file_types, $num, array &$context) {
  if (empty($context['sandbox'])) {
    module_load_include('inc', 'devel_generate');
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $num;
    $context['sandbox']['users'] = devel_get_users();
  }

  $limit = 20;

  for ($i = 0; $i < min($limit, $context['sandbox']['max'] - $context['sandbox']['progress']); $i++) {
    $type = array_rand(drupal_map_assoc($file_types), 1);
    if ($uri = file_entity_generate_file($type)) {
      $file = file_uri_to_object($uri, FALSE);
      $file->uid = array_rand(drupal_map_assoc($context['sandbox']['users']), 1);
      file_save($file);
      if (!empty($file->fid)) {
        $context['results'][] = $file->fid;
      }
    }
  }

  // Update our progress information.
  $context['sandbox']['progress'] += $limit;
  //$context['message'] = t('Deleted URL redirect @rid.', array('@rid' => end($rids)));

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

/**
 * When the batch is finished set a status message.
 */
function file_entity_generate_file_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(format_plural(count($results), 'One file created.', '@count files created.'));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
}

/**
 * Generate file function for file_entity.
 */
function file_entity_generate_file($file_type) {
  $type = file_type_load($file_type);
  $possible_extensions = file_type_get_valid_extensions($type);

  $image_extensions = array('png', 'gif', 'jpg', 'jpeg');
  if (array_intersect($possible_extensions, $image_extensions)) {
    $extension = array_rand(array_flip($image_extensions));
    module_load_include('inc', 'devel_generate', 'image.devel_generate');
    $path = devel_generate_image($extension, '100x100', '1500x1500');
  }
  else {
    $extension = array_rand(array_flip($possible_extensions));
    module_load_include('inc', 'devel_generate', 'file.devel_generate');
    $path = devel_generate_textfile(mt_rand(1024, 102400));
  }

  $uri = file_entity_generate_unique_uri($extension);
  $dir = dirname($uri);
  if (!file_prepare_directory($dir, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    return FALSE;
  }

  if (file_unmanaged_move($path, $uri)) {
    return $uri;
  }

  return FALSE;
}

function file_entity_generate_unique_uri($extension) {
  module_load_include('inc', 'devel_generate');
  do {
    $uri = 'public://devel-generate/' . devel_generate_word(3) . '/' . devel_generate_word(16) . '.' . $extension;
  } while (is_file($uri) || db_query("SELECT 1 FROM {file_managed} WHERE uri = :uri", array(':uri' => $uri))->fetchField());
  return $uri;
}
