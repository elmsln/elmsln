<?php

/**
 * Menu callback for the String Overrides Migrate module to display the import administration
 */
function stringoverrides_migrate_admin_import() {
  $form = array();
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $languages = module_exists('locale') ? locale_language_list() : array('en' => t('English'));
  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('File'),
    '#description' => t('Attach your *.po file here to import the string overrides.'),
  );
  $form['lang'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#description' => t('Which language to import the overrides to.'),
    '#options' => $languages,
  );
  $form['import'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#weight' => 3,
  );
  return $form;
}

/**
 * Triggered when the user imports data.
 */
function stringoverrides_migrate_admin_import_submit($form, &$form_state) {
  // Check if the file uploaded correctly
  $file = file_save_upload('file');
  if (!$file) {
    form_set_error('file', t('A file to import is required.'));
    return;
  }

  // Try to allocate enough time to parse and import the data.
  drupal_set_time_limit(240);
  $lang = $form_state['values']['lang'];

  // Get strings from file (returns on failure after a partial import, or on success)
  $status = _locale_import_read_po('mem-store', $file, LOCALE_IMPORT_OVERWRITE, $lang, 'stringoverrides');
  if ($status === FALSE) {
    // Error messages are set in _locale_import_read_po().
    return FALSE;
  }

  // Get the import result.
  $strings = _locale_import_one_string('mem-report');

  file_delete($file);
  variable_set("locale_custom_strings_$lang", $strings);
  drupal_set_message(t('The overrides have been imported.'));
}

/**
 * Ability to export a *.po file.
 */
function stringoverrides_migrate_admin_export() {
  $languages = module_exists('locale') ? locale_language_list() : array('en' => t('English'));
  $form['lang'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#description' => t('The language you would like to export.'),
    '#options' => $languages,
    '#required' => TRUE,
  );
  $form['export'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
    '#weight' => 3,
  );
  $form['#submit'][] = 'stringoverrides_admin_export_submit';
  return $form;
}

/**
 * Submit-handler for stringoverrides_admin_export.
 */
function stringoverrides_migrate_admin_export_submit($form, &$form_state) {
  $lang = $form_state['values']['lang'];
  $export = stringoverrides_admin_export_text($lang);
  $filename = "my-string-overrides.$lang.po";
  $headers = array(
    'Content-Type' => 'text/plain; charset=UTF-8',
    'Content-Length' => strlen($export),
    'Content-Disposition' => 'attachment; filename="' . $filename . '"',
    'Cache-Control' => 'private',
  );
  foreach ($headers as $name => $value) {
    drupal_add_http_header($name, $value);
  }
  echo $export;
  drupal_exit();
}

/**
 * Returns the exported *.po text from the given language.
 */
function stringoverrides_migrate_admin_export_text($lang = 'en') {
  $languages = language_list();

  $custom_strings = variable_get("locale_custom_strings_$lang", array());
  foreach ($custom_strings as $context => $translations) {
    foreach ($translations as $source => $translation) {
      $strings[] = array(
        'context' => $context,
        'source' => $source,
        'translation' => $translation,
        'comment' => '',
      );
    }
  }
  return _locale_export_po_generate($languages[$lang], $strings);
}
