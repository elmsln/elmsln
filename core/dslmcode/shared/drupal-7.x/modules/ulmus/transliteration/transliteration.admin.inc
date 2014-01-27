<?php

/**
 * @file
 * Retroactive transliteration and admin settings UI.
 */

/**
 * Form builder function; generates retroactive transliteration confirm form.
 *
 * @see transliteration_retroactive_submit()
 * @ingroup forms
 */
function transliteration_retroactive() {
  if (!$query = transliteration_file_query()) {
    drupal_set_message(t('Database not supported.'), 'error');
    $form['description']['#markup'] = t('Retroactive transliteration is not supported for the database system of this Drupal installation. If you think this should be fixed please <a href="@issues-url">file an issue</a> in the project issue queue.', array('@issues-url' => 'http://drupal.org/project/issues/transliteration'));
    return $form;
  }

  $count = $query->countQuery()->execute()->fetchColumn();
  if (!$count) {
    drupal_set_message(t('Transliteration is not required.'), 'status');
    $form['description']['#markup'] = t('There are currently no files names containing non-ASCII characters.');
    return $form;
  }

  $form['#redirect'] = 'admin/config/media/file-system/settings';
  $question = t('Are you sure you want to transliterate existing file names?');

  // Generate a sample list.
  $rows = array();
  $header = array(
    t('Original file name'),
    t('Transliterated file name')
  );
  foreach ($query->range(0, 10)->execute() as $file) {
    $filename = basename($file->uri);
    $rows[] = array(l($filename, file_create_url($file->uri)), transliteration_clean_filename($filename));
  }
  $description = '<p><strong>' . t('The database currently lists @x_filenames containing non-ASCII characters.', array('@x_filenames' => format_plural($count, '1 file name', '@count file names'))) . '</strong><br />';
  $description .= t('This count might be inaccurate, though, since some files may not need to be renamed. For example, off-site files will never be changed.') . '</p>';
  $description .= theme('table', array('header' => $header, 'rows' => $rows));
  if ($count > 10) {
    $description .= '<p>' . t('Note: table shows only the first 10 entries.') . '</p>';
  }
  $description .= '<p>' . t('<strong>WARNING:</strong> if you have manually entered image or file paths in text fields (for example, text areas or WYSIWYG editors), renaming the files will break these references. Since there is currently no automated way to also fix referenced files in textual contents, it is a very good idea to backup the database and %files directory beforehand. Modules accessing files using their internal system ids are not affected.', array('%files' => drupal_realpath(file_default_scheme() . '://'))) . '</p>';
  $description .= '<p style="color: red; font-weight: bold; font-size: 18px;">' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $question, 'admin/config/media/file-system/settings', $description, t('Transliterate'));
}

/**
 * Form submit function; retroactively transliterates existing file names.
 *
 * @see transliteration_retroactive()
 */
function transliteration_retroactive_submit($form, &$form_state) {
  $count = 0;
  $errors = array();
  $result = transliteration_file_query()->execute();

  while ($file = $result->fetchObject()) {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $scheme = file_uri_scheme($file->uri);

    // Missing implementation.
    if (!$wrapper) {
      $errors[] = file_uri_target($file->uri);
      continue;
    }

    // Skip non-writable stream wrappers.
    $writeable_stream_wrappers = file_get_stream_wrappers(STREAM_WRAPPERS_WRITE);
    if (!isset($writeable_stream_wrappers[$scheme])) {
      continue;
    }

    // Missing file.
    if (!file_exists($wrapper->realpath())) {
      $errors[] = file_uri_target($file->uri);
      continue;
    }

    // Sanitize file name.
    $filename = transliteration_clean_filename(basename($file->uri));
    // Build destination URI.
    $destination = file_stream_wrapper_uri_normalize(drupal_dirname($file->uri) . '/' . $filename);
    $destination = file_destination($destination, FILE_EXISTS_RENAME);

    // Rename and update the file record accordingly.
    if ($wrapper->rename($file->uri, $destination)) {
      // If possible, add a url redirect to handle old URL references.
      if (module_exists('redirect')) {
        $redirect = new stdClass();
        redirect_object_prepare($redirect, array(
          'source' => $wrapper->getDirectoryPath() . '/' . file_uri_target($file->uri),
          'redirect' => $wrapper->getDirectoryPath() . '/' . file_uri_target($destination),
          'status_code' => 301)
        );
        redirect_save($redirect);
      }
      $file->uri = $destination;
      // Don't use file_save() as it modifies the timestamp.
      drupal_write_record('file_managed', $file, 'fid');
      // Inform modules that the file has been updated.
      module_invoke_all('file_update', $file);
      $count++;
    }
    else {
      $errors[] = file_uri_target($file->uri);
    }
  }

  if ($errors) {
    $message = t('Not all file names could be converted. The following files could not be accessed and have been ignored:');
    $message .= theme('item_list', array('items' => $errors));
    drupal_set_message($message, 'error');
  }
  else {
    drupal_set_message(t('@filenames have been successfully transliterated.', array('@filenames' => format_plural($count, '1 file name', '@count file names'))));
  }

  // Flush page cache.
  cache_clear_all();
}

/**
 * Builds a query that returns all file names from the database containing non-ASCII characters.
 *
 * @return
 *   SelectQuery
 */
function transliteration_file_query() {
  // Regular expressions are not supported by Drupal's database layer and
  // operators differ between manufacturers.
  switch (db_driver()) {
    case 'mysql':
    case 'mysqli':
      $operator = 'NOT REGEXP';
      if (variable_get('transliteration_file_lowercase', TRUE)) {
        $operator .= ' BINARY';
      }
      $regex = '/[a-z0-9_.-]+$';
      break;

    case 'pgsql':
      $operator = '!~*';
      $regex = '/[a-z0-9_.-]+$';
      break;

    default:
      return FALSE;
  }

  return db_select('file_managed')
    ->fields('file_managed')
    ->condition('uri', $regex, $operator);
}
