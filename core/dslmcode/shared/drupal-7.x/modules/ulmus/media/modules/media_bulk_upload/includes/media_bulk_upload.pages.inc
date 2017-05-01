<?php

/**
 * @file
 * Common pages for the Media Bulk Upload module.
 */

/**
 * Menu callback; Edit multiple files on the same page using multiform module.
 *
 * @todo When http://drupal.org/node/1227706 is fixed, filter the $files
 * array using file_access($file, 'edit').
 *
 * @see media_bulk_upload_file_operation_edit_multiple()
 */
function media_bulk_upload_file_page_edit_multiple($files) {
  if (empty($files)) {
    return MENU_ACCESS_DENIED;
  }

  $forms = array();
  foreach ($files as $file) {
    // To maintain unique form_ids, append the file id.
    $forms[] = array('media_edit_' . $file->fid, $file);
  }

  $form = call_user_func_array('multiform_get_form', $forms);
  $form['#attributes']['class'][] = 'media-bulk-upload-multiedit-form';

  // Improve the display of each file form.
  foreach (element_children($form['multiform']) as $key) {
    $fid = $form['multiform'][$key]['fid']['#value'];
    $file = $files[$fid];

    // Add the filename to each 'subform'.
    $title = t('<em>Edit @type</em> @title', array('@type' => $file->type, '@title' => $file->filename));
    $form['multiform'][$key]['#prefix'] = '<h2>' . $title . '</h2>';

    // Remove the 'replace file' functionality.
    $form['multiform'][$key]['replace_upload']['#access'] = FALSE;

    // Remove any actions.
    $form['multiform'][$key]['actions']['#access'] = FALSE;

    // Hide additional settings under a collapsible fieldset.
    $form['multiform'][$key]['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional settings'),
      '#weight' => 99,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      // FAPI #collapsed and #collapsible not available in a render array.
      '#attached' => array(
        'js' => array(
          'misc/form.js',
          'misc/collapse.js',
        ),
      ),
      '#attributes' => array(
        'class' => array('collapsible', 'collapsed'),
      ),
    );

    $form['multiform'][$key]['settings']['additional_settings'] = $form['multiform'][$key]['additional_settings'];
    unset($form['multiform'][$key]['additional_settings']);
  }

  if (isset($form['buttons']['Delete'])) {
    $form['buttons']['Delete']['#access'] = FALSE;
  }

  // Add a cancel button at the bottom of the form.
  $form['buttons']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#weight' => 50,
  );
  if (isset($_GET['destination'])) {
    $form['buttons']['cancel']['#href'] = $_GET['destination'];
  }
  else if (user_access('administer files')) {
    $form['buttons']['cancel']['#href'] = 'admin/content/file';
  }
  else {
    $form['buttons']['cancel']['#href'] = '<front>';
  }

  // Override the page title since each file form sets a title.
  drupal_set_title(t('Edit multiple files'));

  // Allow other modules to alter the form.
  drupal_alter('media_bulk_upload_edit_multiple_form', $form);

  return $form;
}
