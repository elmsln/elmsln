<?php

/**
 * @file
 * Token integration for the file_entity module.
 */

/**
 * Implements hook_token_info().
 */
function file_entity_token_info() {
  // File type tokens.
  $info['types']['file-type'] = array(
    'name' => t('File type'),
    'description' => t('Tokens associated with file types.'),
    'needs-data' => 'file_type',
  );
  $info['tokens']['file-type']['name'] = array(
    'name' => t('Name'),
    'description' => t('The name of the file type.'),
  );
  $info['tokens']['file-type']['machine-name'] = array(
    'name' => t('Machine-readable name'),
    'description' => t('The unique machine-readable name of the file type.'),
  );
  $info['tokens']['file-type']['count'] = array(
    'name' => t('File count'),
    'description' => t('The number of files belonging to the file type.'),
  );
  $info['tokens']['file-type']['edit-url'] = array(
    'name' => t('Edit URL'),
    'description' => t("The URL of the file type's edit page."),
  );

  // File tokens.
  $info['tokens']['file']['type'] = array(
    'name' => t('File type'),
    'description' => t('The file type of the file.'),
    'type' => 'file-type',
  );
  $info['tokens']['file']['download-url'] = array(
    'name' => t('Download URL'),
    'description' => t('The URL to download the file directly.'),
    'type' => 'url',
  );

  return $info;
}

/**
 * Implements hook_token_info_alter().
 */
function file_entity_token_info_alter(&$info) {
  $info['tokens']['file']['name']['description'] = t('The name of the file.');
}

/**
 * Implements hook_tokens().
 */
function file_entity_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  $url_options = array('absolute' => TRUE);
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  // File tokens.
  if ($type == 'file' && !empty($data['file'])) {
    $file = $data['file'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'type':
          if ($file_type = file_type_load($file->type)) {
            $replacements[$original] = $sanitize ? check_plain($file_type->label) : $file_type->label;
          }
          break;

        case 'download-url':
          $uri = file_entity_download_uri($file);
          $replacements[$original] = url($uri['path'], $uri['options'] + $url_options);
          break;
      }
    }

    // Chained token relationships.
    if (($file_type_tokens = token_find_with_prefix($tokens, 'type')) && $file_type = file_type_load($file->type)) {
      $replacements += token_generate('file-type', $file_type_tokens, array('file_type' => $file_type), $options);
    }
    if ($download_url_tokens = token_find_with_prefix($tokens, 'download-url')) {
      $replacements += token_generate('url', $download_url_tokens, file_entity_download_uri($file), $options);
    }
  }

  // File type tokens.
  if ($type == 'file-type' && !empty($data['file_type'])) {
    $file_type = $data['file_type'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'name':
          $replacements[$original] = $sanitize ? check_plain($file_type->label) : $file_type->label;
          break;

        case 'machine-name':
          // This is a machine name so does not ever need to be sanitized.
          $replacements[$original] = $file_type->type;
          break;

        case 'count':
          $query = db_select('file_managed');
          $query->condition('type', $file_type->type);
          $query->addTag('file_type_file_count');
          $count = $query->countQuery()->execute()->fetchField();
          $replacements[$original] = (int) $count;
          break;

        case 'edit-url':
          $replacements[$original] = url('admin/structure/file-types/manage/' . $file_type->type . '/fields', $url_options);
          break;
      }
    }
  }

  return $replacements;
}
