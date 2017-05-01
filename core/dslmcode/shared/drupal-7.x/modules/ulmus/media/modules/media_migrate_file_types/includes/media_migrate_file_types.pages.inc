<?php

/**
 * @file
 * Common pages for the Media Migrate File Types module.
 */

/**
 * File type migration page.
 *
 * Allows site administrator to execute migration of old/disabled/deleted
 * file types to new ones.
 */
function media_migrate_file_types_upgrade_file_types($form, &$form_state) {
  $migratable_types = _media_migrate_file_types_get_migratable_file_types();

  // Silently return if there are no file types that need migration.
  if (empty($migratable_types)) {
    return array(
      'message' => array(
        '#markup' => t('There are no file types that need migration. The Media Medigrate File Types module can now be safely <a href="@modules">disabled</a>.', array('@modules' => url('admin/modules'))),
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
    '#value' => t('Start migration'),
  );

  return $form;
}

/**
 * File type migration page submit handler.
 */
function media_migrate_file_types_upgrade_file_types_submit($form, &$form_state) {
  $migratable_types = _media_migrate_file_types_get_migratable_file_types();
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
function media_migrate_file_types_upgrade_file_types_confirm($form, &$form_state) {
  return confirm_form(
    $form,
    t('Do you really want to migrate selected file types?'),
    'admin/structure/file-types/upgrade',
    NULL,
    t('Migrate')
  );
}

/**
 * File types migration confirmation page submit. Executes actual migration.
 */
function media_migrate_file_types_upgrade_file_types_confirm_submit($form, &$form_state) {
  $migratable_types = _media_migrate_file_types_get_migratable_file_types();
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

        if (!empty($fields_to_move)) {
          db_update('field_config_instance')
            ->fields(array('bundle' => $bundle_new->type))
            ->condition('entity_type',  'file')
            ->condition('bundle', $bundle_old->type)
            ->condition('field_name', $fields_to_move, 'IN')
            ->execute();
        }

        if (!empty($fields_to_drop)) {
          db_delete('field_config_instance')
            ->condition('entity_type',  'file')
            ->condition('bundle', $bundle_old->type)
            ->condition('field_name', $fields_to_drop, 'IN')
            ->execute();
        }

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
