<?php

/**
 * @file
 * Tokens for the File (Field) Paths module.
 */

/**
 * Implements hook_token_info().
 *
 * @return mixed
 */
function filefield_paths_token_info() {
  $info['tokens']['file']['ffp-name-only']          = array(
    'name'        => t("File name"),
    'description' => t("File name without extension."),
  );
  $info['tokens']['file']['ffp-name-only-original'] = array(
    'name'        => t("File name - original"),
    'description' => t("File name without extension - original."),
  );
  $info['tokens']['file']['ffp-extension-original'] = array(
    'name'        => t("File extension - original"),
    'description' => t("File extension - original."),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 *
 * @param       $type
 * @param       $tokens
 * @param array $data
 *
 * @return array
 */
function filefield_paths_tokens($type, $tokens, array $data = array()) {
  $url_options = array('absolute' => TRUE);
  if (isset($language)) {
    $url_options['language'] = $language;
  }

  $replacements = array();

  if ($type == 'file' && !empty($data['file'])) {
    $file = $data['file'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'ffp-name-only':
          $basename                = drupal_basename($file->filename);
          $extension               = preg_match('/\.[^.]+$/', $basename, $matches) ? $matches[0] : NULL;
          $replacements[$original] = !is_null($extension) ? drupal_substr($basename, 0, drupal_strlen($basename) - drupal_strlen($extension)) : $basename;
          break;

        case 'ffp-name-only-original':
          $basename                = drupal_basename($file->origname);
          $extension               = preg_match('/\.[^.]+$/', $basename, $matches) ? $matches[0] : NULL;
          $replacements[$original] = !is_null($extension) ? drupal_substr($basename, 0, drupal_strlen($basename) - drupal_strlen($extension)) : $basename;
          break;

        case 'ffp-extension-original':
          $replacements[$original] = preg_match('/[^.]+$/', drupal_basename($file->origname), $matches) ? $matches[0] : NULL;
          break;
      }
    }
  }

  return $replacements;
}
