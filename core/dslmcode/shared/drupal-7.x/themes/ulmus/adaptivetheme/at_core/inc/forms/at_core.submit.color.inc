<?php

/**
 * @file
 * Saves a parsable inc file with the full color info array for the active theme.
 *
 * If a custom color scheme has been created in the UI it is injected into the
 * schemes array and saved. You must rename the Custom scheme and give it a
 * unique array key before using the generated file in your theme.
 *
 * Note that color module validates the input of the color form and this is not
 * run if there is a problem, e.g. the user inputting non hexadecimal CSS color
 * strings, which color module validates to avoid XSS.
 */
function at_core_submit_color($values, $theme_name, $path) {
  $palette = $values['palette'];
  if ($values['info']['schemes']) {
    $values['info']['schemes']['']['colors'] = $palette;
  }
  $info = $values['info'];
  $color_info = array();
  $color_info[] = "<?php" . "\n";
  $color_info[] = '$info = ';
  $color_info[] = var_export($info, TRUE);
  $color_info[] = ';' . "\n";
  $color_info_export = implode('', $color_info);
  if (!empty($color_info_export)) {
    $filepath = $path . '/' . $theme_name . '_color.inc';
    file_unmanaged_save_data($color_info_export, $filepath, FILE_EXISTS_REPLACE);
  }
}
