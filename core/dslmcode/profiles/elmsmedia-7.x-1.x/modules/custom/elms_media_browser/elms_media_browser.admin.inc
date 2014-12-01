<?php

/**
 * Page callback for admin/config/media/visual-select-file.
 */
function elms_media_browser_settings_form($form, &$form_state) {
  $form['elms_media_browser_public_is_public'] = array(
    '#type' => 'checkbox',
    '#title' => t('Public files are public'),
    '#default_value' => variable_get('elms_media_browser_public_is_public', 0),
    '#description' => t("Drupal and FileField Sources add some weird access checks to public files. This checkbox will undo that: public is public, period.<br>Without this checkbox, you can't reference some files, like files uploaded by EMB Upload."),
  );

  return system_settings_form($form);
}
