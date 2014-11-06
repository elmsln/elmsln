<?php


/**
 * @file
 * All of the destination handling code needed for Backup and Migrate.
 */

backup_migrate_include('crud', 'locations');

/**
 * Get the available destination types.
 */
function backup_migrate_get_destination_subtypes() {
  return backup_migrate_crud_subtypes('destination');
}

/**
 * Implementation of hook_backup_migrate_destination_subtypes().
 *
 * Get the built in Backup and Migrate destination types.
 */
function backup_migrate_backup_migrate_destination_subtypes() {
  $out = array();
  if (variable_get('backup_migrate_allow_backup_to_file', TRUE)) {
    $out += array(
      'file' => array(
        'description' => t('Save the backup files to any directory on this server which the web-server can write to.'),
        'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.file.inc',
        'class' => 'backup_migrate_destination_files',
        'type_name' => t('Server Directory'),
        'local' => TRUE,
        'can_create' => TRUE,
      ),
      'file_manual' => array(
        'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.file.inc',
        'type_name' => t('Server Directory'),
        'class' => 'backup_migrate_destination_files_manual',
      ),
      'file_scheduled' => array(
        'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.file.inc',
        'type_name' => t('Server Directory'),
        'class' => 'backup_migrate_destination_files_scheduled',
      ),
    );
  }
  $out += array(
    'browser_download' => array(
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.browser.inc',
      'class' => 'backup_migrate_destination_browser_download',
    ),
    'browser_upload' => array(
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.browser.inc',
      'class' => 'backup_migrate_destination_browser_upload',
    ),
    'nodesquirrel' => array(
      'description' => t('Save the backup files to the NodeSquirrel.com backup service.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.nodesquirrel.inc',
      'class' => 'backup_migrate_destination_nodesquirrel',
      'type_name' => t('NodeSquirrel.com'),
      'can_create' => TRUE,
      'remote' => TRUE,
    ),
    'ftp' => array(
      'description' => t('Save the backup files to any a directory on an FTP server.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.ftp.inc',
      'class' => 'backup_migrate_destination_ftp',
      'type_name' => t('FTP Directory'),
      'can_create' => TRUE,
      'remote' => TRUE,
    ),
    's3' => array(
      'description' => t('Save the backup files to a bucket on your !link.', array('!link' => l(t('Amazon S3 account'), 'http://aws.amazon.com/s3/'))),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.s3.inc',
      'class' => 'backup_migrate_destination_s3',
      'type_name' => t('Amazon S3 Bucket'),
      'can_create' => TRUE,
      'remote' => TRUE,
    ),
    'email' => array(
      'type_name' => t('Email'),
      'description' => t('Send the backup as an email attachment to the specified email address.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/destinations.email.inc',
      'class' => 'backup_migrate_destination_email',
      'can_create' => TRUE,
      'remote' => TRUE,
    ),
  );

  return $out;
}

/**
 * Implementation of hook_backup_migrate_destinations().
 *
 * Get the built in backup destinations and those in the db.
 */
function backup_migrate_backup_migrate_destinations() {
  $out              = array();

  // Add the default, out of the box destinations for new users.
  if (variable_get('backup_migrate_allow_backup_to_file', TRUE)) {
    if (variable_get('file_private_path', FALSE)) {
      $out['manual']    = backup_migrate_create_destination('file_manual', array('machine_name' => 'manual'));
      $out['scheduled'] = backup_migrate_create_destination('file_scheduled', array('machine_name' => 'scheduled'));
    }
    else {
      _backup_migrate_message('You must specify a private file system path in the !settings to backup to the server.', array('!settings' => l(t('file system settings'), 'admin/config/media/file-system')), 'warning');
    }
  }
  // Add the browser destination for downloading to the desktop.
  if (variable_get('backup_migrate_allow_backup_to_download', TRUE)) {
    $out['download']  = backup_migrate_create_destination('browser_download');
  }
  $out['upload']    = backup_migrate_create_destination('browser_upload');
  // Expose the configured databases as sources.
  backup_migrate_include('filters');
  $out              += backup_migrate_filters_invoke_all('destinations');

  return $out;
}

/**
 * Get all the available backup destination.
 *
 * @param $op
 *  The operation which will be performed on the destination. Hooks can use this
 *  to return only those destinations appropriate for the given op.
 *  Options include:
 *    'manual backup' - destinations available for manual backup
 *    'scheduled backup' - destinations available for schedules backup
 *    'list files' - destinations whose backup files can be listed
 *    'restore' - destinations whose files can be restored from
 *    'all' - all available destinations should be returned
 */
function backup_migrate_get_destinations($op = 'all') {
  static $destinations = NULL;

  // Get the list of destinations and cache them locally.
  if ($destinations === NULL) {
    $destinations = backup_migrate_crud_get_items('destination');
  }

  // Return all if that's what was asked for.
  if ($op == 'all') {
    return $destinations;
  }

  // Return only those destinations which support the given op.
  $out = array();
  foreach ($destinations as $key => $destination) {
    if ($destination->op($op)) {
      $out[$key] = $destination;
    }
  }
  return $out;
}

/**
 * Get the destination of the given id.
 */
function backup_migrate_get_destination($id) {
  $destinations = backup_migrate_get_destinations('all');
  return empty($destinations[$id]) ? NULL : $destinations[$id];
}

/**
 * Create a destination object of the given type with the given params.
 */
function backup_migrate_create_destination($destination_type, $params = array()) {
  $params['subtype'] = $destination_type;
  return backup_migrate_crud_create_item('destination', $params);
}

/**
 * Load a file from a destination and return the file info.
 */
function backup_migrate_destination_get_file($destination_id, $file_id) {
  if ($destination = backup_migrate_get_destination($destination_id)) {
    return $destination->load_file($file_id);
  }
  return NULL;
}

/**
 * Load a file from a destination and return the file info.
 */
function backup_migrate_destination_get_latest_file($destination_id) {
  $out = NULL;
  if ($destination = backup_migrate_get_destination($destination_id)) {
    $files = $destination->list_files();
    $max = 0;
    foreach ((array)$files as $file) {
      $info = $file->info();

      // If there's a datestamp, it should override the filetime as it's probably more reliable.
      $time = !empty($info['datestamp']) ? $info['datestamp'] : $info['filetime'];
      if ($time > $max) {
        $max = $time;
        $out = $file;
      }
    }
  }
  return $out;
}


/**
 * Check if a file exists in the given destination.
 */
function backup_migrate_destination_file_exists($destination_id, $file_id) {
  if ($destination = backup_migrate_get_destination($destination_id)) {
    return $destination->file_exists($file_id);
  }
  return NULL;
}

/**
 * Send a file to the destination specified by the settings array.
 */
function backup_migrate_destination_confirm_destination(&$settings) {
  if ($destinations = $settings->get_destinations()) {
    foreach ($destinations as $key => $destination) {
      // Check that the destination is ready to go.
      if (!$destination->confirm_destination()) {
        unset($destinations[$key]);
      }
    }
  }
  $settings->destinations = $destinations;
  return count($destinations);
}

/**
 * Send a file to the destination specified by the settings array.
 */
function backup_migrate_destination_save_file($file, &$settings) {
  $saved_to = array();
  if ($destinations = $settings->get_destinations()) {
    foreach ($destinations as $destination) {
      // Make sure the file only gets saved to each destination once.
      $id = $destination->get('id');
      if (!in_array($id, $saved_to)) {
        if ($destination->save_file($file, $settings)) {
          $saved_to[] = $id;
        }
      }
    }
  }
  return $saved_to ? $file : FALSE;
}

/**
 * Delete a file in the given destination.
 */
function backup_migrate_destination_delete_file($destination_id, $file_id) {
  if ($destination = backup_migrate_get_destination($destination_id)) {
    return $destination->delete_file($file_id);
  }
}

/**
 * Get the action links for a file on a given destination.
 */
function _backup_migrate_destination_get_file_links($destination_id, $file_id) {
  $out = array();
  if ($destination = backup_migrate_get_destination($destination_id)) {
    $out = $destination->get_file_links($file_id);
  }
  return $out;
}

/* UI Menu Callbacks */

/**
 * List the backup files in the given destination.
 */
function backup_migrate_ui_destination_display_files($destination_id = NULL) {
  drupal_add_css(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.css');

  $rows = $sort = array();
  if ($destination = backup_migrate_get_destination($destination_id)) {
    drupal_set_title(t('@title Files', array('@title' => $destination->get_name())));
    return _backup_migrate_ui_destination_display_files($destination, 20, TRUE);
  }
  drupal_goto(BACKUP_MIGRATE_MENU_PATH . "/destination");
}

/**
 * List the backup files in the given destination.
 */
function _backup_migrate_ui_destination_display_files($destination = NULL, $limit = NULL, $show_pager = FALSE) {
  if ($destination) {
    // Refresh the file listing cache if requested.
    if (isset($_GET['refresh'])) {
      $destination->file_cache_clear();
      drupal_goto($_GET['q']);
    }
    $files = $destination->list_files();

    $fetch = $out = '';

    // Get the fetch link.
    if ($destination->cache_files && $destination->fetch_time) {
      $fetch = '<div class="description">'. t('This listing was fetched !time ago. !refresh', array('!time' => format_interval(time() - $destination->fetch_time, 1), '!refresh' => l(t('fetch now'), $_GET['q'], array('query' => array('refresh' => 'true'))))) .'</div>';
    }

    $out .= $fetch;
    $out .= _backup_migrate_ui_destination_display_file_list($files, array('limit' => 20, 'pager' => TRUE));
    $out .= $fetch;

    return $out;
  }
}

/**
 * List the backup files in the given destination.
 */
function _backup_migrate_ui_destination_display_file_list($files, $options = array()) {
  drupal_add_css(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.css');

  // Set soem default options
  $options += array(
    'pager' => TRUE,
    'more' => FALSE,
    'operations' => TRUE,
    'limit' => NULL,
    'form_elements' => NULL,
  );

  $rows = $sort = array();
  if ($files) {
    $headers = array(
      array('data' => 'Filename', 'field' => 'filename'),
      array('data' => 'Created', 'field' => 'filetime', 'sort' => 'desc'),
      array('data' => 'Size', 'field' => 'filesize'),
    );
    if ($options['operations']) {
      $headers[] = array('data' => 'Operations');
    }
    if ($options['form_elements']) {
      array_unshift($headers, '');
    }

    $sort_order = tablesort_get_order($headers);
    $sort_key   = $sort_order['sql'] ? $sort_order['sql'] : 'filetime';
    $sort_dir   = tablesort_get_sort($headers) == 'desc' ? SORT_DESC : SORT_ASC;

    $i          = 0;
    foreach ((array)$files as $id => $file) {
      $info = $file->info();

      // If there's a datestamp, it should override the filetime as it's probably more reliable.
      $info['filetime'] = !empty($info['datestamp']) ? $info['datestamp'] : $info['filetime'];

      $description = '';

      // Add the description as a new row.
      if (!empty($info['description'])) {
        $description .= ' <div title="' . check_plain($info['description']) . '" class="backup-migrate-description">' . check_plain($info['description']) . '</div>';
      }
      // Add the backup source.
      if (!empty($info['bam_sourcename'])) {
        $description .= ' <div title="'. check_plain($info['bam_sourcename']) .'" class="backup-migrate-tags"><span class="backup-migrate-label">'. t('Source:') .' </span>' . check_plain($info['bam_sourcename']) . '</div>';
      }
      // Add the tags as a new row.
      if (!empty($info['tags'])) {
        $tags = check_plain(implode(', ', (array)$info['tags']));
        $description .= ' <div title="' . $tags . '" class="backup-migrate-tags"><span class="backup-migrate-label">' . t('Tags:') . ' </span>' . $tags . '</div>';
      }
      // Add the other info.
      if (!empty($info['bam_other_safe'])) {
        foreach ($info['bam_other_safe'] as $label => $data) {
          $description .= ' <div class="backup-migrate-tags"><span class="backup-migrate-label">' . $label . ' </span>' . $data . '</div>';        
        }
      }

      // Show only files that can be restored from.
      $sort[] = $info[$sort_key];
      $row = array(
        check_plain($info['filename']) . $description,
        t('!time ago', array('!time' => format_interval(time() - $info['filetime'], 2))) . '<div class="backup-migrate-date">' . format_date($info['filetime'], 'small') . '</div>',
        format_size($info['filesize']),
      );
      if ($options['operations']) {
        $row[] = array('data' => implode(' &nbsp; ', $file->destination->get_file_links($file->file_id())), 'class' => 'backup-migrate-actions');
      }
      if (isset($options['form_elements'][$id])) {
        array_unshift($row, $options['form_elements'][$id]);
      }

      $rows[] = $row;

    }

    array_multisort($sort, $sort_dir, $rows);

    // Show only some of them if it's limited.
    $showing = $pager = $more = '';
    if ($options['limit']) {
      $limit = $options['limit'];
      $total = count($rows);
      $end = $limit;
      $start = 0;

      if ($options['pager']) {
        $page = isset($_GET['page']) ? $_GET['page'] : '';
        $start = $page * $limit;

        $element = 0;
        $GLOBALS['pager_total'][$element] = ceil($total / $limit);
        $GLOBALS['pager_page_array'][$element] = $page;
        $tags = array(
          t('« newest'),
          t('« newer'),
          '',
          t('older »'),
          t('oldest »'),
          );
        $pager = theme('pager', $tags, $limit, $element, array(), ceil($total/$limit));

        $end = min($total - 1, $start + $limit);
      }
      if ($total > $limit && $options['more']) {
        $more = ' ' . l(t('view all'), $options['more']);
      }
      $showing = t('Showing @start to @end of @total files.', array('@start' => $start + 1, '@end' => $end + 1, '@total' => $total));

      // Limit the number of rows shown.
      $rows = array_slice($rows, $start, $limit, TRUE);
    }

    $out = theme("table", array('header' => $headers, 'rows' => $rows, 'class' => 'backup-migrate-listing backup-migrate-listing-files'));
    $out .= $showing;
    $out .= $pager;
    $out .= $more;
  }
  else {
    $out = t('There are no backup files to display.');
  }
  return $out;
}

/**
 * List the backup files in the given destination.
 */
function _backup_migrate_ui_destination_display_file_list_options($files, $limit = NULL) {
  drupal_add_css(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.css');

  $rows = $sort = array();
  if ($files) {
    $headers = array(
      '',
      array('data' => 'Filename', 'field' => 'filename'),
      array('data' => 'Created', 'field' => 'filetime', 'sort' => 'desc'),
      array('data' => 'Size', 'field' => 'filesize'),
    );

    $sort_order = tablesort_get_order($headers);
    $sort_key   = $sort_order['sql'] ? $sort_order['sql'] : 'filetime';
    $sort_dir   = tablesort_get_sort($headers) == 'desc' ? SORT_DESC : SORT_ASC;

    $i          = 0;
    foreach ((array)$files as $file) {
      $info = $file->info();

      // If there's a datestamp, it should override the filetime as it's probably more reliable.
      $info['filetime'] = !empty($info['datestamp']) ? $info['datestamp'] : $info['filetime'];

      $description = '';

      // Add the description as a new row.
      if (!empty($info['description'])) {
        $description .= ' <div title="' . check_plain($info['description']) . '" class="backup-migrate-description">' . check_plain($info['description']) . '</div>';
      }
      // Add the backup source.
      if (!empty($info['bam_sourcename'])) {
        $description .= ' <div title="'. check_plain($info['bam_sourcename']) .'" class="backup-migrate-tags"><span class="backup-migrate-label">'. t('Source:') .' </span>' . check_plain($info['bam_sourcename']) . '</div>';
      }
      // Add the tags as a new row.
      if (!empty($info['tags'])) {
        $tags = check_plain(implode(', ', (array)$info['tags']));
        $description .= ' <div title="' . $tags . '" class="backup-migrate-tags"><span class="backup-migrate-label">' . t('Tags:') . ' </span>' . $tags . '</div>';
      }
      // Add the other info.
      if (!empty($info['bam_other_safe'])) {
        foreach ($info['bam_other_safe'] as $label => $data) {
          $description .= ' <div class="backup-migrate-tags"><span class="backup-migrate-label">' . $label . ' </span>' . $data . '</div>';        
        }
      }

      // Show only files that can be restored from.
      $sort[] = $info[$sort_key];
      $rows[] = array(
        'radio',
        check_plain($info['filename']) . $description,
        t('!time ago', array('!time' => format_interval(time() - $info['filetime'], 2))) . '<div class="backup-migrate-date">' . format_date($info['filetime'], 'small') . '</div>',
        format_size($info['filesize']),
      );
    }

    array_multisort($sort, $sort_dir, $rows);

    // Show only some of them if it's limited.
    $showing = $pager = '';
    if ($limit) {
      $total = count($rows);
      $end = $limit;
      $start = 0;


      $showing = t('Showing @start to @end of @total files.', array('@start' => $start + 1, '@end' => $end + 1, '@total' => $total));

      // Limit the number of rows shown.
      $rows = array_slice($rows, $start, $limit, TRUE);
    }

    $out = theme("table", array('header' => $headers, 'rows' => $rows, 'class' => 'backup-migrate-listing backup-migrate-listing-files'));
    $out .= $showing;
  }
  else {
    $out = t('There are no backup files to display.');
  }
  return $out;
}


/**
 * Download a file to the browser.
 */
function backup_migrate_ui_destination_download_file($destination_id = NULL, $file_id = NULL) {
  if ($file = backup_migrate_destination_get_file($destination_id, $file_id)) {
    backup_migrate_include('files');
    $file->transfer();
  }
  drupal_goto(BACKUP_MIGRATE_MENU_PATH);
}

/**
 * Restore a backup file from a destination.
 */
function backup_migrate_ui_destination_restore_file($destination_id = NULL, $file_id = NULL) {
  if (backup_migrate_destination_file_exists($destination_id, $file_id)) {
    return drupal_get_form('backup_migrate_ui_destination_restore_file_confirm', $destination_id, $file_id);
  }
  _backup_migrate_message('Cannot restore from the the file: %file_id because it does not exist.', array('%file_id' => $file_id), 'error');
  if ($destination_id && user_access('access backup files')) {
    drupal_goto(BACKUP_MIGRATE_MENU_PATH . '/destination/list/files/' . $destination_id);
  }
  drupal_goto(BACKUP_MIGRATE_MENU_PATH);
}

/**
 * Ask confirmation for file restore.
 */
function backup_migrate_ui_destination_restore_file_confirm($form, &$form_state, $destination_id, $file_id) {
  $sources = _backup_migrate_get_source_form_item_options();
  if (count($sources) > 1) {
    $form['source_id'] = array(
      "#type" => "select",
      "#title" => t("Restore to"),
      "#options" => $sources,
      "#description" => t("Choose the database to restore to. Any database destinations you have created and any databases specified in your settings.php can be restored to."),
      "#default_value" => 'db',
    );
  }
  else {
    $form['source_id'] = array(
      "#type" => "value",
      "#value" => 'db',
    );
  }

  $form['destination_id'] = array('#type' => 'value', '#value' => $destination_id);
  $form['file_id'] = array('#type' => 'value', '#value' => $file_id);
  $form = confirm_form($form, t('Are you sure you want to restore the database?'), BACKUP_MIGRATE_MENU_PATH . "/destination/list/files/". $destination_id, t('Are you sure you want to restore the database from the backup file %file_id? This will delete some or all of your data and cannot be undone. <strong>Always test your backups on a non-production server!</strong>', array('%file_id' => $file_id)), t('Restore'), t('Cancel'));
  drupal_set_message(t('Restoring will delete some or all of your data and cannot be undone. <strong>Always test your backups on a non-production server!</strong>'), 'warning', FALSE);
  $form = array_merge_recursive($form, backup_migrate_filters_settings_form(backup_migrate_filters_settings_default('restore'), 'restore'));
  $form['actions']['#weight'] = 100;

  // Add the advanced fieldset if there are any fields in it.
  if (@$form['advanced']) {
    $form['advanced']['#type'] = 'fieldset';
    $form['advanced']['#title'] = t('Advanced Options');
    $form['advanced']['#collapsed'] = true;
    $form['advanced']['#collapsible'] = true;
  }

  return $form;
}

/**
 * Do the file restore.
 */
function backup_migrate_ui_destination_restore_file_confirm_submit($form, &$form_state) {
  $destination_id = $form_state['values']['destination_id'];
  $file_id = $form_state['values']['file_id'];
  if ($destination_id && $file_id) {
    backup_migrate_perform_restore($destination_id, $file_id, $form_state['values']);
  }
  $redir = user_access('access backup files') ? BACKUP_MIGRATE_MENU_PATH . "/destination/list/files/". $destination_id : BACKUP_MIGRATE_MENU_PATH;
  $form_state['redirect'] = $redir;
}

/**
 * Menu callback to delete a file from a destination.
 */
function backup_migrate_ui_destination_delete_file($destination_id = NULL, $file_id = NULL) {
  if (backup_migrate_destination_file_exists($destination_id, $file_id)) {
    return drupal_get_form('backup_migrate_ui_destination_delete_file_confirm', $destination_id, $file_id);
  }
  _backup_migrate_message('Cannot delete the file: %file_id because it does not exist.', array('%file_id' => $file_id), 'error');
  if ($destination_id && user_access('access backup files')) {
    drupal_goto(BACKUP_MIGRATE_MENU_PATH .'/destination/list/files/' . $destination_id);
  }
  drupal_goto(BACKUP_MIGRATE_MENU_PATH);
}

/**
 * Ask confirmation for file deletion.
 */
function backup_migrate_ui_destination_delete_file_confirm($form, &$form_state, $destination_id, $file_id) {
  $form['destination_id'] = array('#type' => 'value', '#value' => $destination_id);
  $form['file_id'] = array('#type' => 'value', '#value' => $file_id);
  return confirm_form($form, t('Are you sure you want to delete the backup file?'), BACKUP_MIGRATE_MENU_PATH . '/destination/list/files/'. $destination_id, t('Are you sure you want to delete the backup file %file_id? <strong>This action cannot be undone.</strong>', array('%file_id' => $file_id)), t('Delete'), t('Cancel'));
}

/**
 * Delete confirmed, perform the delete.
 */
function backup_migrate_ui_destination_delete_file_confirm_submit($form, &$form_state) {
  if (user_access('delete backup files')) {
    $destination_id = $form_state['values']['destination_id'];
    $file_id = $form_state['values']['file_id'];
    backup_migrate_destination_delete_file($destination_id, $file_id);
    _backup_migrate_message('Database backup file deleted: %file_id', array('%file_id' => $file_id));
  }
  $form_state['redirect'] = user_access('access backup files') ? BACKUP_MIGRATE_MENU_PATH . "/destination/list/files/". $destination_id : BACKUP_MIGRATE_MENU_PATH;
}

/* Utilities */

/**
 * Get pulldown to select existing source options.
 */
function _backup_migrate_get_destination_pulldown($op, $destination_id = NULL, $copy_destination_id = NULL) {
  drupal_add_js(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.js');

  $destinations = _backup_migrate_get_destination_form_item_options($op);
  $form = array(
    '#element_validate' => array('_backup_migrate_destination_pulldown_validate'),
    '#after_build' => array('_backup_migrate_process_destination_pulldown'),
  );
  $form['destination_id'] = array(
    '#type' => 'select',
    '#title' => t('Backup Destination'),
    '#options' => $destinations,
    '#default_value' => $destination_id,
    //'#process' => array('_backup_migrate_process_destination_pulldown'),
  );
  if (user_access('administer backup and migrate')) {
    $form['destination_id']['#description'] = l(t("Create new destination"), BACKUP_MIGRATE_MENU_PATH . "/destination/add");
  }
  $form['copy'] = array(
    '#type' => 'checkbox',
    '#title' => '<span class="backup-migrate-destination-copy-label">' . t('Save a copy to a second destination') . '</span>',
    '#default_value' => !empty($copy_destination_id),
  );
  $form['copy_destination'] = array(
    '#type' => 'backup_migrate_dependent',
    '#dependencies' => array(
      'copy' => TRUE,
    ),
  );
  $form['copy_destination']['copy_destination_id'] = array(
    '#type' => 'select',
    '#title' => t('Second Backup Destination'),
    '#options' => $destinations,
    '#default_value' => $copy_destination_id,
  );



  return $form;
}

/**
 * Return the destination pulldown with an option to save a second copy.
 */
function _backup_migrate_process_destination_pulldown($element) {
  $id = $element['destination_id']['#id'];
  $settings = array(
    'backup_migrate' => array(
      'destination_selectors' => array(
        $id => array(
          'destination_selector' => $id, 
          'copy_destination_selector' => $element['copy_destination']['copy_destination_id']['#id'],
          'copy' => $element['copy']['#id'],
          'labels' => array(
            t('Local') => t('Save an offsite copy to'),
            t('Offsite') => t('Save a local copy to'),
          )
        )
      )
    )
  );
  drupal_add_js($settings, 'setting');

  return $element;
}

/**
 * Validate the destination and second destination widget.
 */
function _backup_migrate_destination_pulldown_validate($element, &$form_state, $form) {
  if (empty($element['copy']['#value']) || $element['copy_destination']['copy_destination_id']['#value'] == $element['destination_id']['#value']) {
    _backup_migrate_destination_pulldown_set_value($form_state['values'], $element['copy_destination']['copy_destination_id']['#parents'], '');
  }
}

/**
 * Set the value of a form field given it's parent array.
 */
function _backup_migrate_destination_pulldown_set_value(&$values, $parents, $value) {
  $key = array_shift($parents);
  if (empty($parents)) {
    $values[$key] = $value;
  }
  else {
    _backup_migrate_destination_pulldown_set_value($values[$key], $parents, $value);
  }
}

/**
 * Get the destination options as an options array for a form item.
 */
function _backup_migrate_get_destination_form_item_options($op) {
  $remote = $local = array();
  foreach (backup_migrate_get_destinations($op) as $key => $destination) {
    if ($destination->op('remote backup')) {
      $remote[$key] = $destination->get_name();
    }
    else {
      $local[$key] = $destination->get_name();
    }
  }
  $out = array();
  if ($remote && $local) {
    $out = array(
      t('Local') => $local,
      t('Offsite') => $remote,
    );
  } 
  else {
    $out = $remote + $local;
  }
  return $out;
}

/**
 * A base class for creating destinations.
 */
class backup_migrate_destination extends backup_migrate_location {
  var $db_table = "backup_migrate_destinations";
  var $type_name = "destination";
  var $default_values = array('settings' => array());
  var $singular = 'destination';
  var $plural = 'destinations';
  var $title_plural = 'Destinations';
  var $title_singular = 'Destination';
  var $cache_files = FALSE;
  var $fetch_time = NULL;
  var $cache_expire = 86400; // 24 hours
  var $weight = 0;

  var $destination_type = "";
  var $supported_ops = array();

  /**
   * This function is not supposed to be called. It is just here to help the po extractor out.
   */
  function strings() {
    // Help the pot extractor find these strings.
    t('Destination');
    t('Destinations');
    t('destinations');
    t('destination');
  }

  /**
   * Save the given file to the destination.
   */
  function save_file($file, $settings) {
    $this->file_cache_clear();

    // Save the file metadata if the destination supports it.
    $this->save_file_info($file, $settings);
    return $this->_save_file($file, $settings);
  }

  /**
   * Save the given file to the destination.
   */
  function _save_file($file, $settings) {
    // This must be overriden.
    return $file;
  }

  /**
   * Save the file metadata
   */
  function save_file_info($file, $settings) {
    $info = $this->create_info_file($file);
    // Save the info file and the actual file.
    return $this->_save_file($info, $settings);
  }

  /**
   * Load the file with the given destination specific id and return as a backup_file object.
   */
  function load_file($file_id) {
    // This must be overriden.
    return NULL;
  }

  /**
   * Check if a file exists in the given destination.
   */
  function file_exists($file_id) {
    // Check if the file exists in the list of available files. Actual destination types may have more efficient ways of doing this.
    $files = $this->list_files();
    return isset($files[$file_id]);
  }

  /**
   * List all the available files in the given destination with their destination specific id.
   */
  function list_files() {
    $files = NULL;
    if ($this->cache_files) {
      $files = $this->file_cache_get();
    }
    if ($files === NULL) {
      $files = $this->_list_files();
      $files = $this->load_files_info($files);
      if ($this->cache_files) {
        $this->file_cache_set($files);
      }
    }

    $out = array();
    if (is_array($files)) {
      foreach ($files as $id => $file) {
        if ($file->is_recognized_type()) {
          $out[$id] = $file;
          $out[$id]->destination = &$this;
        }
      }
    }
    return $out;
  }

  /**
   * List all the available files in the given destination with their destination specific id.
   */
  function count_files() {
    return count($this->list_files());
  }


  /**
   * List all the available files in the given destination with their destination specific id.
   */
  function _list_files() {
    return array();
  }

  /**
   * Load up the file's metadata from the accompanying .info file if applicable.
   */
  function load_files_info($files) {
    foreach ($files as $key => $file) {
      // See if there is an info file with the same name as the backup.
      if (isset($files[$key . '.info'])) {
        $info_file = $this->load_file($files[$key . '.info']->file_id());
        $info = drupal_parse_info_file($info_file->filepath());
        // Allow the stored metadata to override the detected metadata.
        unset($info['filename']);
        $file->file_info = $info + $file->file_info;
        // Remove the metadata file from the list
        unset($files[$key . '.info']);
      }

      // Add destination specific info.
      $file->info_set('destination_id', $this->get('id'));
      $file->info_set('remote', $this->get('remote'));
    }


    return $files;
  }

  /**
   * Create an ini file and write the meta data.
   */
  function create_info_file($file) {
    $info = $this->_file_info_file($file);
    $data = _backup_migrate_array_to_ini($file->file_info);
    $info->put_contents($data);
    return $info;
  }

  /**
   * Create the info file object.
   */
  function _file_info_file($file) {
    $info = new backup_file(array('filename' => $this->_file_info_filename($file->file_id())));
    return $info;
  }

  /**
   * Determine the file name of the info file for a file.
   */
  function _file_info_filename($file_id) {
    return $file_id . '.info';
  }


  /**
   * Cache the file list.
   */
  function file_cache_set($files) {
    cache_set('backup_migrate_file_list:'. $this->get_id(), $files, 'cache', time() + $this->cache_expire);
  }

  /**
   * Retrieve the file list.
   */
  function file_cache_get() {
    backup_migrate_include('files');
    $cache = cache_get('backup_migrate_file_list:'. $this->get_id());
    if (!empty($cache->data) && $cache->created > (time() - $this->cache_expire)) {
      $this->fetch_time = $cache->created;
      return $cache->data;
    }
    $this->fetch_time = 0;
    return NULL;
  }

  /**
   * Retrieve the file list.
   */
  function file_cache_clear() {
    if ($this->cache_files) {
      $this->file_cache_set(NULL);
    }
  }

  /**
   * Delete the file with the given destination specific id.
   */
  function delete_file($file_id) {
    $this->file_cache_clear();
    $this->_delete_file($file_id);
    $this->_delete_file($this->_file_info_filename($file_id));
  }

  /**
   * Delete the file with the given destination specific id.
   */
  function _delete_file($file_id) {
    // This must be overriden.
  }

  /**
   * Get the edit form for the item.
   */
  function edit_form() {
    if (get_class($this) !== 'backup_migrate_destination') {
      $form = parent::edit_form();
      $form['subtype'] = array(
        "#type" => "value",
        "#default_value" => $this->get('subtype'),
      );
    }
    else {
      $types = backup_migrate_get_destination_subtypes();
      $items = array(
        'remote' => array(
          'title' => t('Offsite Destinations'),
          'description' => t('For the highest level of protection, set up an offsite backup destination in a location separate from your website.'),
          'items' => array(),
         ),
        'local' => array(
          'title' => t('Local Destinations'),
          'description' => t('Local backups are quick and convenient but do not provide the additional safety of offsite backups.'),
          'items' => array(),
         ),
        'other' => array(
          'title' => t('Other Destinations'),
          'description' => t('These destinations have not been classified because they were created for Backup and Migrate version 2. They may not work correctly with this version.'),
          'items' => array(),
         ),

      );

      // If no (valid) node type has been provided, display a node type overview.
      $path = $this->get_settings_path();
      foreach ($types as $key => $type) {
        if (@$type['can_create']) {
          $type_url_str = str_replace('_', '-', $key);
          $out = '<dt>'. l($type['type_name'], $path . "/add/$type_url_str", array('attributes' => array('title' => t('Add a new @s destination.', array('@s' => $type['type_name']))))) .'</dt>';
          $out .= '<dd>'. filter_xss_admin($type['description']) .'</dd>';

          if (!empty($type['local'])) {
            $items['local']['items'][] = $out;
          }
          if (!empty($type['remote'])) {
            $items['remote']['items'][] = $out;
          }
          if (empty($type['local']) && empty($type['remote'])) {
            $items['other']['items'][] = $out;
          }
        }
      }
      if (count($items['local']['items']) || count($items['remote']['items']) || count($items['other']['items'])) {
        $output = '<p>' . t('Choose the type of destination you would like to create:') . '</p>';
        foreach ($items as $group) {
          if (count($group['items'])) {
            $group['body'] = '<dl>'. implode('', $group['items']) .'</dl>';
            $output .= theme('backup_migrate_group', $group);
          }
        }
      }
      else {
        $output = t('No destination types available.');
      }
      $form['select_type'] = array(
        '#type' => 'markup',
        '#markup' => $output,
      );
    }
    return $form;
  }

  /**
   * Get the message to send to the user when confirming the deletion of the item.
   */
  function delete_confirm_message() {
    return t('Are you sure you want to delete the destination %name? Backup files already saved to this destination will not be deleted.', array('%name' => $this->get_name()));
  }

  /**
   * Get a boolean representing if the destination is remote or local.
   */
  function get_remote() {
    return $this->op('remote backup');
  }

  /**
   * Get the action links for a destination.
   */
  function get_action_links() {
    $out = parent::get_action_links();
    $item_id = $this->get_id();

    // Don't display the download/delete/restore ops if they are not available for this destination.
    if ($this->op('list files') && user_access("access backup files")) {
      $out = array('list files' => l(t("list files"), $this->get_settings_path() . '/list/files/'. $item_id)) + $out;
    }
    if (!$this->op('configure') || !user_access('administer backup and migrate')) {
      unset($out['edit']);
    }
    return $out;
  }

  /**
   * Get the action links for a file on a given destination.
   */
  function get_file_links($file_id) {
    $out = array();

    // Don't display the download/delete/restore ops if they are not available for this destination.
    $can_read       = $this->can_read_file($file_id);
    $can_delete     = $this->can_delete_file($file_id);

    $path = $this->get_settings_path();

    $destination_id = $this->get_id();
    if ($can_read && user_access("access backup files")) {
      $out[] = l(t("download"), $path . '/downloadfile/'. $destination_id .'/'. $file_id);
    }
    if ($can_read && user_access("restore from backup")) {
      $out[] = l(t("restore"), $path . '/list/restorefile/' . $destination_id .'/'. $file_id);
    }
    if ($can_delete && user_access("delete backup files")) {
      $out[] = l(t("delete"), $path . '/list/deletefile/' . $destination_id .'/'. $file_id);
    }
    return $out;
  }

  /**
   * Determine if we can read the given file.
   */
  function can_read_file($file_id) {
    return $this->op('restore');
  }

  /**
   * Determine if we can read the given file.
   */
  function can_delete_file($file_id) {
    return $this->op('delete');
  }

  /**
   * Get the form for the settings for this destination type.
   */
  function settings_default() {
    return array();
  }

  /**
   * Get the form for the settings for this destination.
   */
  function settings_form($form) {
    return $form;
  }

  /**
   * Validate the form for the settings for this destination.
   */
  function settings_form_validate($form_values) {
  }

  /**
   * Submit the settings form. Any values returned will be saved.
   */
  function settings_form_submit($form_values) {
    return $form_values;
  }

  /**
   * Check that a destination is valid.
   */
  function confirm_destination() {
    return true;
  }

  /**
   * Add the menu items specific to the destination type.
   */
  function get_menu_items() {
    $items = parent::get_menu_items();

    $path = $this->get_settings_path();

    $items[$path . '/list/files'] = array(
      'title' => 'Destination Files',
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('destinations', 'backup_migrate_ui_destination_display_files', TRUE),
      'access arguments' => array('access backup files'),
      'type' => MENU_LOCAL_TASK,
    );
    $items[$path . '/list/deletefile'] = array(
      'title' => 'Delete File',
      'description' => 'Delete a backup file',
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('destinations', 'backup_migrate_ui_destination_delete_file', TRUE),
      'access arguments' => array('delete backup files'),
      'type' => MENU_LOCAL_TASK,
    );
    $items[$path . '/list/restorefile'] = array(
      'title' => 'Restore from backup',
      'description' => 'Restore database from a backup file on the server',
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('destinations', 'backup_migrate_ui_destination_restore_file', TRUE),
      'access arguments' => array('restore from backup'),
      'type' => MENU_LOCAL_TASK,
    );
    $items[$path . '/downloadfile'] = array(
      'title' => 'Download File',
      'description' => 'Download a backup file',
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('destinations', 'backup_migrate_ui_destination_download_file', TRUE),
      'access arguments' => array('access backup files'),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }


}

/**
 * A base class for creating destinations.
 */
class backup_migrate_destination_remote extends backup_migrate_destination {
  /**
   * The location is a URI so parse it and store the parts.
   */
  function get_location() {
    return $this->url(FALSE);
  }

  /**
   * The location to display is the url without the password.
   */
  function get_display_location() {
    return $this->url(TRUE);
  }

  /**
   * Return the location with the password.
   */
  function set_location($location) {
    $this->location = $location;
    $this->set_url($location);
  }

  /**
   * Destination configuration callback.
   */
  function edit_form() {
    $form = parent::edit_form();
    $form['scheme'] = array(
      "#type" => "textfield",
      "#title" => t("Scheme"),
      "#default_value" => @$this->dest_url['scheme'] ? $this->dest_url['scheme'] : '',
      "#required" => TRUE,
      "#weight" => 0,
    );
    $form['host'] = array(
      "#type" => "textfield",
      "#title" => t("Host"),
      "#default_value" => @$this->dest_url['host'] ? $this->dest_url['host'] : 'localhost',
      "#required" => TRUE,
      "#weight" => 10,
    );
    $form['path'] = array(
      "#type" => "textfield",
      "#title" => t("Path"),
      "#default_value" => @$this->dest_url['path'],
      "#required" => TRUE,
      "#weight" => 20,
    );
    $form['user'] = array(
      "#type" => "textfield",
      "#title" => t("Username"),
      "#default_value" => @$this->dest_url['user'],
      "#required" => TRUE,
      "#weight" => 30,
    );
    $form['pass'] = array(
      "#type" => "password",
      "#title" => t("Password"),
      "#default_value" => @$this->dest_url['pass'],
      '#description' => '',
      "#weight" => 40,
    );
    if (@$this->dest_url['pass']) {
      $form['old_password'] = array(
        "#type" => "value",
        "#value" => @$this->dest_url['pass'],
      );
      $form['pass']["#description"] .= t(' You do not need to enter a password unless you wish to change the currently saved password.');
    }
    return $form;
  }

  /**
   * Submit the configuration form. Glue the url together and add the old password back if a new one was not specified.
   */
  function edit_form_submit($form, &$form_state) {
    $form_state['values']['pass'] = $form_state['values']['pass'] ? $form_state['values']['pass'] : $form_state['values']['old_password'];
    $form_state['values']['location'] = $this->glue_url($form_state['values'], FALSE);
    parent::edit_form_submit($form, $form_state);
  }
}

