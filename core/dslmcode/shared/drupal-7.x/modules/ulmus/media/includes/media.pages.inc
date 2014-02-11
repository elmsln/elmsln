<?php

/**
 * @file
 * Common pages for the Media module.
 */


/**
 * Menu callback; Edit multiple files on the same page using multiform module.
 *
 * @todo When http://drupal.org/node/1227706 is fixed, filter the $files
 * array using file_access($file, 'edit').
 *
 * @see media_file_operation_edit_multiple()
 */
function media_file_page_edit_multiple($files) {
  if (empty($files)) {
    return MENU_ACCESS_DENIED;
  }

  $forms = array();
  foreach ($files as $file) {
    // To maintain unique form_ids, append the file id.
    $forms[] = array('media_edit_' . $file->fid, $file);
  }

  $form = call_user_func_array('multiform_get_form', $forms);
  $form['#attributes']['class'][] = 'media-multiedit-form';

  // Add the title to each 'subform'.
  foreach (element_children($form['multiform']) as $key) {
    $fid = $form['multiform'][$key]['fid']['#value'];
    $file = $files[$fid];
    $title = t('<em>Edit @type</em> @title', array('@type' => $file->type, '@title' => $file->filename));
    $form['multiform'][$key]['#prefix'] = '<h2>' . $title . '</h2>';
    $form['multiform'][$key]['actions']['#access'] = FALSE;
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
  drupal_alter('media_edit_multiple_form', $form);

  return $form;
}

/**
 * CTools modal callback for editing a file.
 */
function media_file_edit_modal($form, &$form_state, $file, $js) {
  ctools_include('modal');
  ctools_include('ajax');

  $form_state['ajax'] = $js;
  form_load_include($form_state, 'inc', 'file_entity', 'file_entity.pages');

  $output = ctools_modal_form_wrapper('file_entity_edit', $form_state);

  if ($js) {
    $commands = $output;

    if ($form_state['executed']) {
      $commands = array(ctools_modal_command_dismiss(t('File saved')));
    }

    print ajax_render($commands);
    exit();
  }

  // Otherwise, just return the output.
  return $output;
}

/**
 * File type migration page.
 *
 * Allows site administrator to execute migration of old/disabled/deleted
 * file types to new ones.
 */
function media_upgrade_file_types($form, &$form_state) {
  $migratable_types = _media_get_migratable_file_types();

  // Silently return if there are no file types that need migration.
  if (empty($migratable_types)) {
    return array(
      'message' => array(
        '#markup' => t('There are no file types that need migration.'),
      ),
    );
  }

  $form['message'] = array(
    'message' => array(
      '#markup' => t('This page allows you to migrate deprecated and/or disabled file types to new ones. It will migrate files from old type to new one and optionally migrate fields and delete old type.'),
    ),
  );

  $form['migrate_fields'] = array(
    '#type' => 'checkbox',
    '#title' => t('Migrate fields'),
    '#default_value' => TRUE,
    '#description' => t('Migrate fields and their values from old file types to new ones.'),
  );
  $form['delete_old_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete old type'),
    '#default_value' => FALSE,
    '#description' => t('Delete old file type if migration was successful and delete operation is possible (type is not exported in code).'),
  );
  $form['migrate_mimes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Migrate type mime-type'),
    '#default_value' => TRUE,
    '#description' => t('Move mime-type from old type to new one.'),
  );

  $form['upgradable_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upgradable file types'),
  );

  $options = array('- ' . t('Do not upgrade') . ' -');
  foreach (file_type_get_enabled_types() as $type) {
    $options[$type->type] = $type->label;
  }

  foreach ($migratable_types as $machine_name) {
    $type = file_type_load($machine_name);
    if (!$type) {
      $type = new stdClass;
      $type->label = $type->type = $machine_name;
    }
    $form['upgradable_types'][$machine_name] = array(
      '#type' => 'select',
      '#title' => $type->label,
      '#options' => $options,
      '#description' => t(
        'Select file type which you want to migrate @type to. Select %no_upgrade if type should stay as it is.',
        array('@type' => $type->label, '%no_upgrade' => '- ' . t('Do not upgrade') . ' -')),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Start migraton'),
  );

  return $form;
}

/**
 * File type migration page submit handler.
 */
function media_upgrade_file_types_submit($form, &$form_state) {
  $migratable_types = _media_get_migratable_file_types();
  $migrate = FALSE;
  foreach ($migratable_types as $type) {
    if ($form_state['values'][$type]) {
      $migrate = TRUE;
      break;
    }
  }

  // Return silently if no types were selected for migration.
  if (!$migrate) {
    return;
  }

  // Use confirmation page/form.
  $query = $form_state['values'];
  unset($query['op']);
  unset($query['submit']);
  unset($query['form_id']);
  unset($query['form_token']);
  unset($query['form_build_id']);

  $form_state['redirect'] = array(
    'admin/structure/file-types/upgrade/confirm',
    array('query' => $query),
  );
}

/**
 * File types migration confirmation page.
 */
function media_upgrade_file_types_confirm($form, &$form_state) {
  return confirm_form(
    $form,
    t('Do you really want to migrate selected file types?'),
    'admin/structure/file-types/upgrade',
    NULL,
    t('Migrate')
  );
}

/**
 * File types migration confirmation page sumit. Executes actual migration.
 */
function media_upgrade_file_types_confirm_submit($form, &$form_state) {
  $migratable_types = _media_get_migratable_file_types();
  foreach ($migratable_types as $type) {
    if ($_GET[$type] && $bundle_new = file_type_load($_GET[$type])) {
      // Old bundle might be deleted so let's fake some values.
      $bundle_old = file_type_load($type);
      if (empty($bundle_old)) {
        $bundle_old = new stdClass;
        $bundle_old->type = $type;
        $bundle_old->mimetypes = array();
        $bundle_old->export_type = 2;
      }

      // Migrate fields to new bundle.
      if ($_GET['migrate_fields']) {
        $old_fields = db_select('field_config_instance', 'fc')->fields('fc', array('field_name'))->condition('entity_type',  'file')->condition('bundle', $bundle_old->type)->execute()->fetchCol();
        $new_fields = db_select('field_config_instance', 'fc')->fields('fc', array('field_name'))->condition('entity_type',  'file')->condition('bundle', $bundle_new->type)->execute()->fetchCol();
        $fields_to_move = array_diff($old_fields, $new_fields);
        $fields_to_drop = array_diff($old_fields, $fields_to_move);

        db_update('field_config_instance')
          ->fields(array('bundle' => $bundle_new->type))
          ->condition('entity_type',  'file')
          ->condition('bundle', $bundle_old->type)
          ->condition('field_name', $fields_to_move, 'IN')
          ->execute();

        db_delete('field_config_instance')
          ->condition('entity_type',  'file')
          ->condition('bundle', $bundle_old->type)
          ->condition('field_name', $fields_to_drop, 'IN')
          ->execute();

        field_cache_clear();
        module_invoke_all('field_attach_rename_bundle', 'file', $bundle_old->type, $bundle_new->type);
      }

      // Migrate mimetypes to new bundle.
      if ($_GET['migrate_mimes']) {
        $changed = FALSE;
        foreach ($bundle_old->mimetypes as $mime) {
          if (!file_entity_match_mimetypes($bundle_new->mimetypes, $mime)) {
            $bundle_new->mimetypes[] = $mime;
            $changed = TRUE;
          }
        }

        if ($changed) {
          file_type_save($bundle_new);
        }
      }

      // Delete old bundle.
      if ($_GET['delete_old_type'] && $bundle_old->export_type == 1) {
        file_type_delete($bundle_old);
      }

      // Migrate files.
      db_update('file_managed')
        ->fields(array('type' => $bundle_new->type))
        ->condition('type', $bundle_old->type)
        ->execute();
    }
  }

  $form_state['redirect'] = 'admin/structure/file-types';
}
