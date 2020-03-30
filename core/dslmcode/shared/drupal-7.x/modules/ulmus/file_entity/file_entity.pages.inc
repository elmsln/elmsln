<?php

/**
 * @file
 * Supports file operations including View, Edit, and Delete.
 */

/**
 * Menu callback; view a single file entity.
 */
function file_entity_view_page($file) {
  drupal_set_title($file->filename);

  $uri = entity_uri('file', $file);
  // Set the file path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);

  return file_view($file, 'full');
}

/**
 * Menu callback; download a single file entity.
 */
function file_entity_download_page($file) {
  // Ensure there is a valid token to download this file.
  if (!variable_get('file_entity_allow_insecure_download', FALSE)) {
    if (!isset($_GET['token']) || $_GET['token'] !== file_entity_get_download_token($file)) {
      return MENU_ACCESS_DENIED;
    }
  }

  // If the file does not exist it can cause problems with file_transfer().
  if (!is_file($file->uri)) {
    return MENU_NOT_FOUND;
  }
  // @todo Why basename? Why not drupal_basename which was working up until recently.
  $headers = array(
    'Content-Type' => mime_header_encode($file->filemime),
    'Content-Disposition' => 'attachment; filename="' . mime_header_encode(basename($file->uri)) . '"',
    'Content-Length' => $file->filesize,
    'Content-Transfer-Encoding' => 'binary',
    'Pragma' => 'no-cache',
    'Cache-Control' => 'must-revalidate, post-check=0, pre-check=0',
    'Expires' => '0',
  );

  // Let other modules alter the download headers.
  drupal_alter('file_download_headers', $headers, $file);

  // Let other modules know the file is being downloaded.
  module_invoke_all('file_transfer', $file->uri, $headers);

  if (file_entity_file_is_local($file)) {
    // For local files, transfer the file and do not reveal the actual URL.
    file_transfer($file->uri, $headers);
  }
  else if (file_uri_scheme($file->uri) == 's3') {
    $url = file_create_url($file->uri);
    drupal_goto($url);
  }
  else {
    // For remote files, just redirect the user to that file's actual URL.
    $headers['Location'] = file_create_url($file->uri);
    foreach ($headers as $name => $value) {
      drupal_add_http_header($name, $value);
    }
    drupal_send_headers();
    drupal_exit();
  }
}

/**
 * Form callback for adding a file via an upload form.
 *
 * This is a multi step form which has 1-3 pages:
 * - Upload file
 * - Choose filetype
 *   If there is only one candidate (based on mimetype) we will skip this step.
 * - Edit fields
 *   Skip this step if there are no fields on this entity type.
 */
function file_entity_add_upload($form, &$form_state, $options = array()) {
  if (!is_array($options)) {
    $options = array($options);
  }
  $step = (isset($form_state['step']) && in_array($form_state['step'], array(1, 2, 3, 4))) ? $form_state['step'] : 1;
  $form['#step'] = $step;
  $form['#options'] = $options + array(
    'types' => array(),
    'enabledPlugins' => array(),
    'schemes' => array(),
    'max_filesize' => '',
    'uri_scheme' => file_default_scheme(),
    'plugins' => ''
  );

  switch ($step) {
    case 1:
      return file_entity_add_upload_step_upload($form, $form_state, $options);

    case 2:
      return file_entity_add_upload_step_filetype($form, $form_state, $options);

    case 3:
      return file_entity_add_upload_step_scheme($form, $form_state, $options);

    case 4:
      return file_entity_add_upload_step_fields($form, $form_state, $options);

  }
}

/**
 * Generate form fields for the first step in the add file wizard.
 */
function file_entity_add_upload_step_upload($form, &$form_state, array $options = array()) {
  $form['upload'] = array(
    '#type' => 'managed_file',
    '#title' => t('Upload a new file'),
    '#upload_location' => file_entity_upload_destination_uri($options),
    '#upload_validators' => file_entity_get_upload_validators($options),
    '#progress_indicator' => 'bar',
    '#required' => TRUE,
    '#pre_render' => array('file_managed_file_pre_render', 'file_entity_upload_validators_pre_render'),
    '#default_value' => isset($form_state['storage']['upload']) ? $form_state['storage']['upload'] : NULL,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  form_load_include($form_state, 'inc', 'file_entity', 'file_entity.pages');

  return $form;
}

/**
 * Generate form fields for the second step in the add file wizard.
 */
function file_entity_add_upload_step_filetype($form, &$form_state, array $options = array()) {
  $file = file_load($form_state['storage']['upload']);
  $selected_files = $form['#options']['types'];

  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('File type'),
    '#options' => file_entity_get_filetype_candidates($file, $selected_files),
    '#default_value' => isset($form_state['storage']['type']) ? $form_state['storage']['type'] : NULL,
    '#required' => TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['previous'] = array(
    '#type' => 'submit',
    '#value' => t('Previous'),
    '#limit_validation_errors' => array(),
    '#submit' => array('file_entity_add_upload_submit'),
  );
  $form['actions']['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  return $form;
}

/**
 * Generate form fields for the third step in the add file wizard.
 */
function file_entity_add_upload_step_scheme($form, &$form_state, array $options = array()) {
  $file = file_load($form_state['storage']['upload']);

  $schemes = array();
  foreach (file_get_stream_wrappers(STREAM_WRAPPERS_WRITE_VISIBLE) as $scheme => $info) {
    $schemes[$scheme] = check_plain($info['description']);
  }

  // Remove any schemes not found in the instance settings.
  if (!empty($options['schemes'])) {
    $schemes = array_intersect_key($schemes, array_flip($options['schemes']));
  }

  // Determine which scheme to use as the default value.
  if (isset($form_state['storage']['scheme'])) {
    $fallback_scheme = $form_state['storage']['scheme'];
  }
  elseif (!empty($options['uri_scheme'])) {
    $fallback_scheme = $options['uri_scheme'];
  }
  else {
    $fallback_scheme = file_default_scheme();
  }

  $form['scheme'] = array(
    '#type' => 'radios',
    '#title' => t('Destination'),
    '#options' => $schemes,
    '#default_value' => $fallback_scheme,
    '#required' => TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['previous'] = array(
    '#type' => 'submit',
    '#value' => t('Previous'),
    '#limit_validation_errors' => array(),
    '#submit' => array('file_entity_add_upload_submit'),
  );
  $form['actions']['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  return $form;
}

/**
 * Generate form fields for the fourth step in the add file wizard.
 */
function file_entity_add_upload_step_fields($form, &$form_state, array $options = array()) {
  // Load the file and overwrite the filetype set on the previous screen.
  $file = file_load($form_state['storage']['upload']);
  $file->type = $form_state['storage']['type'];

  // Let users modify the filename here.
  $form['filename'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $file->filename,
    '#required' => TRUE,
    '#maxlength' => 255,
    '#weight' => -10,
  );

  // Add fields.
  field_attach_form('file', $file, $form, $form_state);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['previous'] = array(
    '#type' => 'submit',
    '#value' => t('Previous'),
    '#limit_validation_errors' => array(),
    '#submit' => array('file_entity_add_upload_submit'),
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Page callback to show file usage information.
 */
function file_entity_usage_page($file) {
  drupal_set_title(t('<em>Usage of @type</em> @title', array('@type' => $file->type, '@title' => $file->filename)), PASS_THROUGH);

  $rows = array();
  $occured_entities = array();

  // Determine all of the locations where a file is used, then loop through the
  // occurrences and filter out any duplicates.
  foreach (file_usage_list($file) as $module => $type) {
    foreach ($type as $entity_type => $entity_ids) {
      // There are cases where the actual entity doesn't exist.
      // We have to handle this.
      $entity_info = entity_get_info($entity_type);
      $entities = empty($entity_info) ? NULL : entity_load($entity_type, array_keys($entity_ids));

      foreach ($entity_ids as $entity_id => $count) {
        // If this entity has already been listed in the table, just add any
        // additional usage to the total count column in the table row and
        // continue on to the next iteration of the loop.
        if (isset($occured_entities[$entity_type][$entity_id])) {
          $rows[$occured_entities[$entity_type][$entity_id]][2] += $count;
          continue;
        }

        // Retrieve the label and the URI of the entity.
        $label = empty($entities[$entity_id]) ? $module : entity_label($entity_type, $entities[$entity_id]);
        $entity_uri = empty($entities[$entity_id]) ? NULL : entity_uri($entity_type, $entities[$entity_id]);

        // Link the label to the URI when possible.
        if (!empty($entity_uri['path']) && $entity_type != 'paragraphs_item') {
          $entity_label = l($label, $entity_uri['path']);
        }
        // For paragraphs items, we are searching for usages in nodes.
        elseif ($entity_type == 'paragraphs_item') {
          $paragraph_fields = field_read_fields(array('type' => 'paragraphs'));
          foreach ($paragraph_fields as $paragraph_field) {
            $field_name = $paragraph_field['field_name'];
            $query = new EntityFieldQuery();
            $query->entityCondition('entity_type', 'node')
              ->fieldCondition($field_name, 'value', $entity_id, '=');
            $nid = $query->execute();
            if (!empty($nid)) {
              $nid = implode(array_keys($nid['node']));
              if ($nid) {
                $node = node_load($nid);
                $entity_label = l($node->title, 'node/' . $nid);
              }
            }
          }
        }
        else {
          $entity_label = check_plain($label);
        }

        $rows[] = array($entity_label, $entity_type, $count);

        // Record the occurrence of the entity to ensure that it isn't listed in
        // the table again.
        $occured_entities[$entity_type][$entity_id] = count($rows) - 1;
      }
    }
  }

  $header = array(t('Entity'), t('Entity type'), t('Use count'));
  $build['usage_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#caption' => t('This table lists all of the places where @filename is used.', array('@filename' => $file->filename)),
    '#empty' => t('This file is not currently used.'),
  );

  return $build;
}

/**
 * Get the candidate filetypes for a given file.
 *
 * Only filetypes for which the user has access to create entities are returned.
 *
 * @param array $file
 *   An upload file array from form_state.
 *
 * @return array
 *   An array of file type bundles that support the file's mime type.
 */
function file_entity_get_filetype_candidates($file, $selected_files = array()) {
  $types = module_invoke_all('file_type', $file);
  drupal_alter('file_type', $types, $file);

  // If no file types are selected in field instance settings, allow all
  // available types.
  if (!empty($selected_files)) {
    // Limit file type candidates to field allowed types.
    $types = array_intersect($types, $selected_files);
  }

  $candidates = array();
  foreach ($types as $type) {
    $file->type = $type;
    if (file_entity_access('create', $file)) {
      $candidates[$type] = file_entity_type_get_name($file);
    }
  }
  return $candidates;
}

/**
 * Submit handler for the add file form.
 */
function file_entity_add_upload_submit($form, &$form_state) {
  $form_state['storage'] = isset($form_state['storage']) ? $form_state['storage'] : array();
  $form_state['storage'] = array_merge($form_state['storage'], $form_state['values']);

  // Field selected allowed types.
  $selected_files = $form['#options']['types'];

  // This var is set to TRUE when we are ready to save the file.
  $save = FALSE;
  $trigger = $form_state['triggering_element']['#id'];
  $triggered_next = $trigger == 'edit-next' || (strpos($trigger, 'edit-next--') === 0);
  $triggered_previous = $trigger == 'edit-previous' || (strpos($trigger, 'edit-previous--') === 0);
  $step_delta = ($triggered_previous) ? -1 : 1;

  $steps_to_check = array(2, 3);
  if ($triggered_previous) {
    // If the previous button was hit,
    // the step checking order should be reversed 3, 2.
    $steps_to_check = array_reverse($steps_to_check);
  }

  foreach ($steps_to_check as $step) {
    // Check if we can skip step 2 and 3.
    if (($form['#step'] == $step - 1 && $triggered_next) || ($form['#step'] == $step + 1 && $triggered_previous)) {
      $file = file_load($form_state['storage']['upload']);
      if ($step == 2) {
        // Check if we can skip step 2.
        $candidates = file_entity_get_filetype_candidates($file, $selected_files);
        if (count($candidates) == 1) {
          $candidates_keys = array_keys($candidates);
          // There is only one possible filetype for this file.
          // Skip the second page.
          $form['#step'] += $step_delta;
          $form_state['storage']['type'] = reset($candidates_keys);
        }
        elseif (!$candidates || variable_get('file_entity_file_upload_wizard_skip_file_type', FALSE)) {
          // Do not assign the file a file type.
          $form['#step'] += $step_delta;
          $form_state['storage']['type'] = FILE_TYPE_NONE;
        }
      }
      else {
        // Check if we can skip step 3.
        $options = $form['#options'];
        $schemes = file_get_stream_wrappers(STREAM_WRAPPERS_WRITE_VISIBLE);

        // Remove any schemes not found in the instance settings.
        if (!empty($options['schemes'])) {
          $schemes = array_intersect_key($schemes, $options['schemes']);
        }

        if (!file_entity_file_is_writeable($file)) {
          // The file is read-only (remote) and must use its provided scheme.
          $form['#step'] += $step_delta;
          $form_state['storage']['scheme'] = file_uri_scheme($file->uri);
        }
        elseif (count($schemes) == 1) {
          // There is only one possible stream wrapper for this file.
          // Skip the third page.
          $form['#step'] += $step_delta;
          $form_state['storage']['scheme'] = key($schemes);
        }
        elseif (variable_get('file_entity_file_upload_wizard_skip_scheme', FALSE)) {
          $form['#step'] += $step_delta;

          // Fallback to the URI scheme specified in the field settings
          // otherwise use the default file scheme.
          if (!empty($options['uri_scheme'])) {
            $form_state['storage']['scheme'] = $options['uri_scheme'];
          }
          else {
            $form_state['storage']['scheme'] = file_default_scheme();
          }
        }
      }
    }
  }

  // We have the filetype, check if we can skip step 4.
  if ($form['#step'] == 3 && $triggered_next) {
    $file = file_load($form_state['storage']['upload']);
    $form_state['file'] = $file;
    if (!field_info_instances('file', $form_state['storage']['type'])) {
      // This filetype doesn't have fields, save the file.
      $save = TRUE;
    }
    elseif (variable_get('file_entity_file_upload_wizard_skip_fields', FALSE)) {
      // Save the file with blanks fields.
      $save = TRUE;
    }
    // Allow other modules to choose to skip or complete step 4.
    drupal_alter('file_entity_file_upload_skip_fields', $save, $form_state);
  }

  // Form id's can vary depending on how many other forms are displayed, so we
  // need to do string comparissons. e.g edit-submit--2.
  if ($triggered_next) {
    $form_state['step'] = $form['#step'] + 1;
  }
  elseif ($triggered_previous) {
    $form_state['step'] = $form['#step'] - 1;
  }
  elseif (strpos($trigger, 'edit-submit') !== FALSE) {
    $save = TRUE;
  }

  if ($save) {
    $file = file_load($form_state['storage']['upload']);
    if ($file) {
      if (file_uri_scheme($file->uri) != $form_state['storage']['scheme']) {
        $file_destination = $form_state['storage']['scheme'] . '://' . file_uri_target($file->uri);
        $file_destination = file_stream_wrapper_uri_normalize($file_destination);
        if ($moved_file = file_move($file, $file_destination, FILE_EXISTS_RENAME)) {
          // Only re-assign the file object if file_move() did not fail.
          $file = $moved_file;
        }
      }
      $file->type = $form_state['storage']['type'];
      $file->display = TRUE;

      // Change the file from temporary to permanent.
      $file->status = FILE_STATUS_PERMANENT;

      // Save the form fields.
      // Keep in mind that the values for the Field API fields must be in
      // $form_state['values'] and not in ['storage']. This is true as long as
      // the fields are on the last page of the multi step form.
      entity_form_submit_build_entity('file', $file, $form, $form_state);

      file_save($file);
      $form_state['file'] = $file;
      drupal_set_message(t('@type %name was uploaded.', array('@type' => file_entity_type_get_name($file), '%name' => $file->filename)));
    }
    else {
      drupal_set_message(t('An error occurred and no file was uploaded.'), 'error');
      return;
    }

    // Figure out destination.
    if (user_access('administer files')) {
      $path = 'admin/content/file';
    }
    else {
      $path = 'file/' . $file->fid;
    }
    $form_state['redirect'] = $path;
  }
  else {
    $form_state['rebuild'] = TRUE;
  }

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Determines the upload location for the file add upload form.
 *
 * @param array $params
 *   An array of parameters from the media browser.
 * @param array $data
 *   (optional) An array of token objects to pass to token_replace().
 *
 * @return string
 *   A file directory URI with tokens replaced.
 *
 * @see token_replace()
 */
function file_entity_upload_destination_uri(array $params, array $data = array()) {
  $params += array(
    'uri_scheme' => file_default_scheme(),
    'file_directory' => variable_get('file_entity_default_file_directory', ''),
  );

  $destination = trim($params['file_directory'], '/');

  // Replace tokens.
  $destination = decode_entities(token_replace($destination, $data));

  return $params['uri_scheme'] . '://' . $destination;
}

/**
 * Form for uploading multiple files.
 */
function file_entity_add_upload_multiple($form, &$form_state, $params = array()) {
  $form = file_entity_add_upload($form, $form_state, $params);
  unset($form['upload']['#title']);
  // The validators will be set from plupload anyway. This isn't pretty,
  // but don't allow it to show up twice.
  unset($form['upload']['#description']);

  $form['upload']['#type'] = 'plupload';

  // Ensure that we call the plupload_element_pre_render function.
  // If it isn't called, it doesn't set the JS settings that transfers the
  // list of allowed file extensions to the PLUpload widget.
  // We override the 'file_entity_upload_validators_pre_render' setting if it
  // exists, because both pre-render hooks adds the upload-help with list of
  // allowed file extensions.
  $index = array_search('file_entity_upload_validators_pre_render', $form['upload']['#pre_render']);
  if ($index !== FALSE) {
    $form['upload']['#pre_render'][$index] = 'plupload_element_pre_render';
  }
  else {
    $form['upload']['#pre_render'][] = 'plupload_element_pre_render';
  }

  $form['submit']['#value'] = t('Start upload');
  return $form;
}

/**
 * Submit handler for the multiple upload form.
 */
function file_entity_add_upload_multiple_submit($form, &$form_state) {
  $upload_location = !empty($form['upload']['#upload_location']) ?
    $form['upload']['#upload_location'] . '/' :
    variable_get('file_default_scheme', 'public') . '://';

  // Ensure writable destination directory for the files.
  file_prepare_directory($upload_location, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

  // We can't use file_save_upload() because of
  // http://www.jacobsingh.name/content/tight-coupling-no-not.
  foreach ($form_state['values']['upload'] as $uploaded_file) {
    if ($uploaded_file['status'] == 'done') {
      $source = $uploaded_file['tmppath'];
      $destination = file_stream_wrapper_uri_normalize($upload_location . $uploaded_file['name']);
      // Rename it to its original name, and put it in its final home.
      // Note - not using file_move here because if we call file_get_mime
      // (in file_uri_to_object) while it has a .tmp extension, it horks.
      $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);

      $file = file_uri_to_object($destination);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);

      $form_state['files'][$file->fid] = $file;
    }
    else {
      // @todo: move this to element validate or something.
      form_set_error('pud', t('The specified file %name could not be uploaded.', array('%name' => $uploaded_file['name'])));
    }
  }

  // Redirect to the file edit page.
  if (file_entity_access('update', $file) && module_exists('media_bulk_upload')) {
    $destination = array();
    if (isset($_GET['destination'])) {
      $destination = drupal_get_destination();
      unset($_GET['destination']);
    }
    elseif (user_access('administer files')) {
      $destination = array('destination' => 'admin/content/file');
    }
    $form_state['redirect'] = array('admin/content/file/edit-multiple/' . implode(' ', array_keys($form_state['files'])), array('query' => $destination));
  }
  else {
    $form_state['redirect'] = user_access('administer files') ? 'admin/content/file' : '<front>';
  }

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Page callback: Form constructor for the file edit form.
 *
 * Path: file/%file/edit
 *
 * @param object $file
 *   A file object from file_load().
 *
 * @see file_entity_menu()
 *
 * @todo Rename this form to file_edit_form to ease into core.
 */
function file_entity_edit($form, &$form_state, $file) {
  drupal_set_title(t('<em>Edit @type</em> @title', array('@type' => $file->type, '@title' => $file->filename)), PASS_THROUGH);

  $form_state['file'] = $file;

  $form['#attributes']['class'][] = 'file-form';
  if (!empty($file->type)) {
    $form['#attributes']['class'][] = 'file-' . $file->type . '-form';
  }

  // Basic file information.
  // These elements are just values so they are not even sent to the client.
  foreach (array('fid', 'type', 'uid', 'timestamp') as $key) {
    $form[$key] = array(
      '#type' => 'value',
      '#value' => isset($file->$key) ? $file->$key : NULL,
    );
  }

  $form['filename'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $file->filename,
    '#required' => TRUE,
    '#maxlength' => 255,
    '#weight' => -10,
  );

  // Add a 'replace this file' upload field if the file is writeable.
  if (file_entity_file_is_writeable($file)) {
    // Set up replacement file validation.
    $replacement_options = !empty($form_state['#upload_options']) ? $form_state['#upload_options'] : array();

    // The replacement file must have an extension valid for the original type.
    $file_extensions = array();
    $file_type_name = isset($file->type) ? $file->type : file_get_type($file);
    if (!empty($replacement_options['file_extensions'])) {
      $file_extensions = explode(' ', $replacement_options['file_extensions']);
    }
    elseif ($file_type_name && ($file_type = file_type_load($file_type_name))) {
      $file_extensions = file_type_get_valid_extensions($file_type);
    }

    // Set allowed file extensions.
    if (!empty($file_extensions)) {
      // Set to type based file extensions.
      $replacement_options['file_extensions'] = implode(' ', $file_extensions);
    }
    else {
      // Fallback to the extension of the current file.
      $replacement_options['file_extensions'] = pathinfo($file->uri, PATHINFO_EXTENSION);
    }

    $form['replace_upload'] = array(
      '#type' => 'file',
      '#title' => t('Replace file'),
      '#description' => t('This file will replace the existing file. This action cannot be undone.'),
      '#upload_validators' => file_entity_get_upload_validators($replacement_options),
      '#pre_render' => array('file_entity_upload_validators_pre_render'),
    );
    $form['replace_keep_original_filename'] = array(
      '#type' => 'checkbox',
      '#title' => t('Keep original filename'),
      '#default_value' => variable_get('file_entity_file_replace_options_keep_original_filename', FALSE),
      '#description' => t('Rename the newly uploaded file to the name of the original file. This action cannot be undone.'),
    );
  }

  $form['preview'] = file_view_file($file, 'preview');

  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );

  // File destination information for administrators.
  $form['destination'] = array(
    '#type' => 'fieldset',
    '#access' => user_access('administer files') && file_entity_file_is_writeable($file),
    '#title' => t('Destination'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#attributes' => array(
      'class' => array('file-form-destination'),
    ),
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'file_entity') . '/file_entity.js',
      ),
    ),
  );

  $options = array();
  foreach (file_get_stream_wrappers(STREAM_WRAPPERS_WRITE_VISIBLE) as $scheme => $info) {
    $options[$scheme] = check_plain($info['name']);
  }

  $form['destination']['scheme'] = array(
    '#type' => 'radios',
    '#title' => t('Destination'),
    '#options' => $options,
    '#default_value' => file_uri_scheme($file->uri),
  );

  // File user information for administrators.
  $form['user'] = array(
    '#type' => 'fieldset',
    '#access' => user_access('administer files'),
    '#title' => t('User information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#attributes' => array(
      'class' => array('file-form-user'),
    ),
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'file_entity') . '/file_entity.js',
        array(
          'type' => 'setting',
          'data' => array('anonymous' => variable_get('anonymous', t('Anonymous'))),
        ),
      ),
    ),
    '#weight' => 90,
  );
  $form['user']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Associated with'),
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => (!empty($file->uid) && $user = user_load($file->uid)) ? $user->name : '',
    '#weight' => -1,
    '#description' => t('Leave blank for %anonymous.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
  );

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('file_entity_edit_submit'),
    '#validate' => array('file_entity_edit_validate'),
  );
  $form['actions']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#weight' => 10,
    '#submit' => array('file_entity_edit_delete_submit'),
    '#access' => file_entity_access('delete', $file),
  );

  // Build the URL for the cancel button taking into account that there might be
  // a "destination" that includes query string variables.
  $parameters = drupal_get_query_parameters();
  $destination = isset($parameters['destination']) ? $parameters['destination'] : 'file/' . $file->fid;
  $url = drupal_parse_url($destination);

  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => $url['path'],
    '#options' => array('query' => $url['query']),
    '#weight' => 15,
  );

  $langcode = function_exists('entity_language') ? entity_language('file', $file) : NULL;
  field_attach_form('file', $file, $form, $form_state, $langcode);

  return $form;
}

/**
 * Form validation handler for file_entity_edit().
 */
function file_entity_edit_validate($form, &$form_state) {
  $file = (object) $form_state['values'];

  // Validate the "associated user" field.
  if (!empty($file->name) && !($account = user_load_by_name($file->name))) {
    // The use of empty() is mandatory in the context of usernames
    // as the empty string denotes the anonymous user. In case we
    // are dealing with an anonymous user we set the user ID to 0.
    form_set_error('name', t('The username %name does not exist.', array('%name' => $file->name)));
  }

  // Handle the replacement file if uploaded.
  if (isset($form_state['values']['replace_upload'])) {
    // Save the file as a temporary file.
    $file = file_save_upload('replace_upload', $form['replace_upload']['#upload_validators']);
    if (!empty($file)) {
      // Put the temporary file in form_values so we can save it on submit.
      $form_state['values']['replace_upload'] = $file;
    }
    elseif ($file === FALSE) {
      // File uploaded failed.
      form_set_error('replace_upload', t('The replacement file could not be uploaded.'));
    }
  }

  // Run entity form validation.
  entity_form_field_validate('file', $form, $form_state);
}

/**
 * Form submission handler for the 'Save' button for file_entity_edit().
 */
function file_entity_edit_submit($form, &$form_state) {
  $file = $form_state['file'];
  $orphaned_uri = '';

  // Check if a replacement file has been uploaded.
  if (!empty($form_state['values']['replace_upload'])) {
    $replacement = $form_state['values']['replace_upload'];
    // Existing image metadata is stored in $file->height and $file->width.
    // Loop through the replacement metadata and update existing values.
    if (!empty($replacement->metadata)) {
      foreach ($replacement->metadata as $metadata_key => $metadata_value) {
        if (isset($file->{$metadata_key})) {
          $file->{$metadata_key} = $metadata_value;
        }
      }
    }
    // Move file from temp to permanent home.
    if (!empty($form_state['values']['replace_keep_original_filename'])
    && $form_state['values']['replace_keep_original_filename']) {
      $destination_uri = rtrim($file->uri, drupal_basename($file->uri)) . drupal_basename($file->uri);
    }
    else {
      $destination_uri = rtrim($file->uri, drupal_basename($file->uri)) . drupal_basename($replacement->uri);
    }
    $replace_mode = $destination_uri == $file->uri ? FILE_EXISTS_REPLACE : FILE_EXISTS_RENAME;
    if ($new_file_uri = file_unmanaged_copy($replacement->uri, $destination_uri, $replace_mode)) {
      // @todo Add watchdog() about replaced file here?

      // Remove temporary file.
      file_delete($replacement);

      // Update if the uri target has changed.
      if ($new_file_uri != $file->uri) {
        // Store the original file uri to delete if save is successful.
        $orphaned_uri = $file->uri;

        // Update file entity uri.
        $file->uri = $new_file_uri;
      }
    }
  }

  // Run entity form submit handling and save the file.
  entity_form_submit_build_entity('file', $file, $form, $form_state);

  // A user might assign the associated user by entering a user name in the file
  // edit form, which we then need to translate to a user ID.
  if (isset($file->name)) {
    // The use of isset() is mandatory in the context of user IDs, because
    // user ID 0 denotes the anonymous user.
    if ($user = user_load_by_name($file->name)) {
      $file->uid = $user->uid;
    }
    else {
      // Anonymous user.
      $file->uid = 0;
    }
  }
  elseif ($file->uid) {
    $user = user_load($file->uid);
    $file->name = $user->name;
  }

  if (file_uri_scheme($file->uri) != $form_state['values']['scheme']) {
    $file_destination = $form_state['values']['scheme'] . '://' . file_uri_target($file->uri);
    $file_destination = file_stream_wrapper_uri_normalize($file_destination);
    $file_destination_dirname = drupal_dirname($file_destination);
    // Create the directory in case it doesn't exist.
    file_prepare_directory($file_destination_dirname, FILE_CREATE_DIRECTORY);
    if ($moved_file = file_move($file, $file_destination, FILE_EXISTS_RENAME)) {
      // Only re-assign the file object if file_move() did not fail.
      $file = $moved_file;
    }
  }

  file_save($file);

  $args = array(
    '@type' => file_entity_type_get_name($file),
    '%title' => entity_label('file', $file),
  );
  watchdog('file', '@type: updated %title.', $args);
  drupal_set_message(t('@type %title has been updated.', $args));

  // Clean up orphaned file.
  if (!empty($orphaned_uri)) {
    file_unmanaged_delete($orphaned_uri);

    $args['@orphaned'] = file_uri_target($orphaned_uri);
    watchdog('file', '@type: deleted orphaned file @orphaned for %title.', $args);
    drupal_set_message(t('The replaced @type @orphaned has been deleted.', $args));
  }

  $form_state['redirect'] = 'file/' . $file->fid;

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Form submission handler for the 'Delete' button for file_entity_edit().
 */
function file_entity_edit_delete_submit($form, &$form_state) {
  $fid = $form_state['values']['fid'];
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $form_state['redirect'] = array('file/' . $fid . '/delete', array('query' => $destination));

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Page callback: Form constructor for the file deletion confirmation form.
 *
 * Path: file/%file/delete
 *
 * @param object $file
 *   A file object from file_load().
 *
 * @see file_entity_menu()
 */
function file_entity_delete_form($form, &$form_state, $file) {
  $form_state['file'] = $file;

  $form['fid'] = array(
    '#type' => 'value',
    '#value' => $file->fid,
  );

  $description = t('This action cannot be undone.');
  if ($references = file_usage_list($file)) {
    $description .= ' ' . t('This file is currently in use and may cause problems if deleted.');
  }

  return confirm_form($form,
    t('Are you sure you want to delete the file %title?', array(
      '%title' => entity_label('file', $file),
    )),
    'file/' . $file->fid,
    $description,
    t('Delete')
  );
}

/**
 * Form submission handler for file_entity_delete_form().
 */
function file_entity_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm'] && $file = file_load($form_state['values']['fid'])) {
    // Use file_delete_multiple() rather than file_delete() since we want to
    // avoid unwanted validation and usage checking.
    file_delete_multiple(array($file->fid));

    $args = array(
      '@type' => file_entity_type_get_name($file),
      '%title' => entity_label('file', $file),
    );
    watchdog('file', '@type: deleted %title.', $args);
    drupal_set_message(t('@type %title has been deleted.', $args));
  }

  $form_state['redirect'] = '<front>';

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Form constructor for file deletion confirmation form.
 *
 * @param array $files
 *   An array of file objects.
 */
function file_entity_multiple_delete_form($form, &$form_state, array $files) {
  $form['files'] = array(
    '#prefix' => '<ul>',
    '#suffix' => '</ul>',
    '#tree' => TRUE,
  );

  $files_have_usage = FALSE;
  foreach ($files as $fid => $file) {
    $title = entity_label('file', $file);
    $usage = file_usage_list($file);
    if (!empty($usage)) {
      $files_have_usage = TRUE;
      $title = t('@title (in use)', array('@title' => $title));
    }
    else {
      $title = check_plain($title);
    }
    $form['files'][$fid] = array(
      '#type' => 'hidden',
      '#value' => $fid,
      '#prefix' => '<li>',
      '#suffix' => $title . "</li>\n",
    );
  }

  $form['operation'] = array(
    '#type' => 'hidden',
    '#value' => 'delete',
  );

  $description = t('This action cannot be undone.');
  if ($files_have_usage) {
    $description .= ' ' . t('Some of the files are currently in use and may cause problems if deleted.');
  }

  return confirm_form(
    $form,
    format_plural(count($files), 'Are you sure you want to delete this file?', 'Are you sure you want to delete these files?'),
    'admin/content/file',
    $description,
    t('Delete')
  );
}

/**
 * Form submission handler for file_entity_multiple_delete_form().
 */
function file_entity_multiple_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm'] && $fids = array_keys($form_state['values']['files'])) {
    file_delete_multiple($fids);
    $count = count($fids);
    watchdog('file', 'Deleted @count files.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted one file.', 'Deleted @count files.'));
  }
  $form_state['redirect'] = 'admin/content/file';

  // Clear the page and block caches.
  cache_clear_all();
}

/**
 * Page callback for the file edit form.
 *
 * @deprecated
 *   Use drupal_get_form('file_entity_edit')
 */
function file_entity_page_edit($file) {
  return drupal_get_form('file_entity_edit', $file);
}

/**
 * Page callback for the file deletion confirmation form.
 *
 * @deprecated
 *   Use drupal_get_form('file_entity_delete_form')
 */
function file_entity_page_delete($file) {
  return drupal_get_form('file_entity_delete_form');
}

/**
 * Retrieves the upload validators for a file.
 *
 * @param array $options
 *   (optional) An array of options for file validation.
 *
 * @return array
 *   An array suitable for passing to file_save_upload() or for a managed_file
 *   or upload element's '#upload_validators' property.
 */
function file_entity_get_upload_validators(array $options = array()) {
  // Set up file upload validators.
  $validators = array();

  // Validate file extensions. If there are no file extensions in $params and
  // there are no Media defaults, there is no file extension validation.
  if (!empty($options['file_extensions'])) {
    $validators['file_validate_extensions'] = array($options['file_extensions']);
  }
  else {
    $validators['file_validate_extensions'] = array(variable_get('file_entity_default_allowed_extensions', 'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm'));
  }

  // Cap the upload size according to the system or user defined limit.
  $max_filesize = parse_size(file_upload_max_size());
  $file_entity_max_filesize = parse_size(variable_get('file_entity_max_filesize', ''));

  // If the user defined a size limit, use the smaller of the two.
  if (!empty($file_entity_max_filesize)) {
    $max_filesize = min($max_filesize, $file_entity_max_filesize);
  }

  if (!empty($options['max_filesize']) && $options['max_filesize'] < $max_filesize) {
    $max_filesize = parse_size($options['max_filesize']);
  }

  // There is always a file size limit due to the PHP server limit.
  $validators['file_validate_size'] = array($max_filesize);

  // Add image validators.
  $options += array('min_resolution' => 0, 'max_resolution' => 0);
  if ($options['min_resolution'] || $options['max_resolution']) {
    $validators['file_validate_image_resolution'] = array($options['max_resolution'], $options['min_resolution']);
  }

  // Add other custom upload validators from options.
  if (!empty($options['upload_validators'])) {
    $validators += $options['upload_validators'];
  }

  return $validators;
}

function file_entity_upload_archive_form($form, &$form_state) {
  $options = array(
    'file_extensions' => archiver_get_extensions(),
  );

  $form['upload'] = array(
    '#type' => 'managed_file',
    '#title' => t('Upload an archive file'),
    '#upload_location' => NULL, // Upload to the temporary directory.
    '#upload_validators' => file_entity_get_upload_validators($options),
    '#progress_indicator' => 'bar',
    '#required' => TRUE,
    '#pre_render' => array('file_managed_file_pre_render', 'file_entity_upload_validators_pre_render'),
  );

  $form['pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Pattern'),
    '#description' => t('Only files matching this pattern will be imported. For example, to import all jpg and gif files, the pattern would be <em>*.jpg|*.gif</em>. Use <em>.*</em> to extract all files in the archive.'),
    '#default_value' => '.*',
    '#required' => TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  form_load_include($form_state, 'inc', 'file_entity', 'file_entity.pages');

  return $form;
}

/**
 * Upload a file.
 */
function file_entity_upload_archive_form_submit($form, &$form_state) {
  $form_state['files'] = array();

  if ($archive = file_load($form_state['values']['upload'])) {
    if ($archiver = archiver_get_archiver($archive->uri)) {
      $files = $archiver->listContents();
      $destination = pathinfo($archive->filename, PATHINFO_FILENAME);

      // Prepare a temporary directory to extract the archive to before saving
      // it is content.
      $extract_location = 'temporary://' . $destination;
      $extract_location = file_destination($extract_location, FILE_EXISTS_RENAME);
      if (!file_prepare_directory($extract_location, FILE_MODIFY_PERMISSIONS | FILE_CREATE_DIRECTORY)) {
        throw new Exception(t('Unable to prepar, a temporary directory %dir for extraction.', array('%dir' => $extract_location)));
      }

      // Prepare target directory where files are going to be saved.
      $target_dir = file_default_scheme() . '://' . $destination;
      $target_dir = file_destination($target_dir, FILE_EXISTS_RENAME);
      if (!file_prepare_directory($target_dir, FILE_MODIFY_PERMISSIONS | FILE_CREATE_DIRECTORY)) {
        throw new Exception(t('Unable to prepar, a directory %dir for extraction.', array('%dir' => $target_dir)));
      }

      $archiver->extract($extract_location);
      $pattern = '/' . $form_state['values']['pattern'] . '/';
      if ($extracted_files = file_scan_directory($extract_location, $pattern)) {
        foreach ($extracted_files as $extracted_file) {
          $file = new stdClass();
          $file->fid = NULL;
           $file->uid = $archive->uid;
          $file->filename = $extracted_file->filename;
          $file->origname = $extracted_file->filename;
          $file->status = FILE_STATUS_PERMANENT;
          $file->filemime = file_get_mimetype($extracted_file->filename);

          // destination uri should match the current file directory hierarchy.
          $file->uri = $target_dir . str_replace($extract_location, '', $extracted_file->uri);

          // Rename potentially executable files, to help prevent exploits (i.e. will
          // rename filename.php.foo and filename.php to filename.php.foo.txt and
          // filename.php.txt, respectively). Don't rename if 'allow_insecure_uploads'
          // evaluates to TRUE.
          if (!variable_get('allow_insecure_uploads', 0) && preg_match('/\.(php|pl|py|cgi|asp|js)(\.|$)/i', $file->filename) && (substr($file->filename, -4) != '.txt')) {
            $file->filemime = 'text/plain';
            $file->uri .= '.txt';
            $file->filename .= '.txt';
          }

          // prepare destination path for the extracted file while keeping the
          // directory hierarchy of the file.
          $destination = pathinfo($file->uri, PATHINFO_DIRNAME);
          if (!file_prepare_directory($destination, FILE_MODIFY_PERMISSIONS | FILE_CREATE_DIRECTORY)) {
            throw new Exception(t('Unable to prepar, a directory %dir for extraction.', array('%dir' => $destination)));
          }

          if (!file_unmanaged_move($extracted_file->uri, $file->uri)) {
            throw new Exception(t('Could not move uploaded file %file to destination %destination.', array('%file' => $extracted_file->filename, '%destination' => $file->uri)));
            return FALSE;
          }

          file_save($file);
          $form_state['files'][$file->fid] = $file;
        }
      }
      // Delete extract location
      file_unmanaged_delete_recursive($extract_location);
      drupal_set_message(t('Extracted %file and added @count new files.', array('%file' => $archive->filename, '@count' => count($files))));
    }
    else {
      throw new Exception(t('Cannot extract %file, not a valid archive.', array('%file' => $archive->uri)));
    }
  }

  // Redirect to the file edit page.
  if (file_entity_access('edit') && module_exists('multiform')) {
    $destination = array('destination' => 'admin/content/file');
    if (isset($_GET['destination'])) {
      $destination = drupal_get_destination();
      unset($_GET['destination']);
    }
    $form_state['redirect'] = array('admin/content/file/edit-multiple/' . implode(' ', array_keys($form_state['files'])), array('query' => $destination));
  }
  else {
    $form_state['redirect'] = 'admin/content/file';
  }
}
