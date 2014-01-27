<?php
/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_token_info().
 */
function filefield_paths_token_info() {
  $info['tokens']['file']['ffp-name-only'] = array(
    'name' => t("File name"),
    'description' => t("File name without extension."),
  );
  $info['tokens']['file']['ffp-name-only-original'] = array(
    'name' => t("File name - original"),
    'description' => t("File name without extension - original."),
  );
  $info['tokens']['file']['ffp-extension-original'] = array(
    'name' => t("File extension - original"),
    'description' => t("File extension - original."),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function filefield_paths_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);
  if (isset($language)) {
    $url_options['language'] = $language;
  }
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'file' && !empty($data['file'])) {
    $file = $data['file'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'ffp-name-only':
          $info = pathinfo($file->filename);
          $replacements[$original] = $info['filename'];
          break;

        case 'ffp-name-only-original':
          $info = pathinfo($file->origname);
          $replacements[$original] = $info['filename'];
          break;

        case 'ffp-extension-original':
          $info = pathinfo($file->origname);
          $replacements[$original] = isset($info['extension']) ? $info['extension'] : NULL;
          break;
      }
    }
  }

  return $replacements;
}
