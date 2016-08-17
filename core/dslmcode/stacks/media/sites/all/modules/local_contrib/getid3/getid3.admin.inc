<?php
/**
 * @file
 * Admin pages.
 */

/**
 * Administration settings for getID3().
 */
function getid3_admin_settings_form() {
  $form['getid3_show_warnings'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display Warnings"),
    '#default_value' => variable_get('getid3_show_warnings', FALSE),
    '#description' => t("Check this to display the warning messages from the getID3 library when reading and writing ID3 tags. Generally it's a good idea to leave this unchecked, getID3 reports warnings for several trivial problems and the warnings can be confusing to users. This setting can be useful when debugging problems with the ID3 tags."),
  );
  return system_settings_form($form);
}
