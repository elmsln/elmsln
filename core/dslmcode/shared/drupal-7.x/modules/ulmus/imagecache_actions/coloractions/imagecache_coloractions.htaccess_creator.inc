<?php
/**
 * @file Functions to create .htaccess files in public://styles/{image-style}
 * directories that force the correct Content-Type header.
 */

/**
 * Checks for all image style if a .htaccess should be created to force a
 * correct Content-Type header.
 */
function imagecache_coloractions_create_htaccess_all_styles() {
  $styles = image_styles();
  foreach ($styles as $style) {
    imagecache_coloractions_create_htaccess_for_style($style);
  }
}

/**
 * Checks if an image style has a convert format image effect and if so, creates
 * an .htaccess in the folder where the derivatives for this style are stored
 * to force the correct Content-Type header.
 *
 * @param array $style
 *
 * @return bool|null
 *   True if .htaccess created successfully, false om error, null if no
 *  .htaccess needed to be created.
 */
function imagecache_coloractions_create_htaccess_for_style(array $style) {
  // If we have multiple convert effects in the same style (I found one during
  // testing) the last determines the mime type.
  $format = NULL;
  foreach ($style['effects'] as $effect) {
    if ($effect['name'] === 'coloractions_convert') {
      if (!empty($effect['data']['format'])) {
        $format = $effect['data']['format'];
      }
    }
  }
  return $format ? imagecache_coloractions_create_htaccess($style['name'], $format) : NULL;
}

/**
 * Creates an .htaccess file in the folder public://styles/%style_name.
 *
 * The folder itself will also be created if necessary.
 *
 * @param string $style_name
 * @param string $mimeType
 *
 * @return bool
 *   True on success, false otherwise.
 */
function imagecache_coloractions_create_htaccess($style_name, $mimeType) {
  $forceType = "ForceType $mimeType\n";
  $directory = "public://styles/$style_name";
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog('imagecache_actions', 'Failed to create style directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }
  if (!file_put_contents("$directory/.htaccess", $forceType)) {
    watchdog('imagecache_actions', 'Failed to create .htaccess in style directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }
  return TRUE;
}
