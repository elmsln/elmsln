<?php
/**
 * @file
 * File administration and module settings UI.
 */

require_once dirname(__FILE__) . '/file_entity.pages.inc';

/**
 * List file administration filters that can be applied.
 */
function file_filters() {
  $visible_steam_wrappers = file_get_stream_wrappers(STREAM_WRAPPERS_VISIBLE);
  $options = array();
  foreach ($visible_steam_wrappers as $scheme => $information) {
    $options[$scheme] = check_plain($information['name']);
  }
  $filters['uri'] = array(
    'title' => t('scheme'),
    'options' => array(
      '[any]' => t('any'),
    ) + $options,
  );
  $filters['type'] = array(
    'title' => t('type'),
    'options' => array(
      '[any]' => t('any'),
    ) + file_entity_type_get_names(),
  );
  return $filters;
}

/**
 * Apply filters for file administration filters based on session.
 *
 * @param object $query
 *   A SelectQuery to which the filters should be applied.
 */
function file_entity_build_filter_query(SelectQueryInterface $query) {
  // Build query.
  $filter_data = isset($_SESSION['file_entity_overview_filter']) ? $_SESSION['file_entity_overview_filter'] : array();
  foreach ($filter_data as $index => $filter) {
    list($key, $value) = $filter;
    switch ($key) {
      case 'uri':
        $query->condition('fm.' . $key, $value . '%', 'LIKE');
        break;

      case 'type':
        $query->condition('fm.' . $key, $value);
        break;

    }
  }
}

/**
 * Return form for file administration filters.
 */
function file_entity_filter_form() {
  $session = isset($_SESSION['file_entity_overview_filter']) ? $_SESSION['file_entity_overview_filter'] : array();
  $filters = file_filters();

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
    '#theme' => 'exposed_filters__file_entity',
  );
  foreach ($session as $filter) {
    list($type, $value) = $filter;
    if ($type == 'term') {
      // Load term name from DB rather than search and parse options array.
      $value = module_invoke('taxonomy', 'term_load', $value);
      $value = $value->name;
    }
    else {
      $value = $filters[$type]['options'][$value];
    }
    $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
    if ($i++) {
      $form['filters']['current'][] = array('#markup' => t('and where %property is %value', $t_args));
    }
    else {
      $form['filters']['current'][] = array('#markup' => t('where %property is %value', $t_args));
    }
    if (in_array($type, array('type', 'uri'))) {
      // Remove the option if it is already being filtered on.
      unset($filters[$type]);
    }
  }

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
    '#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '</div>' : ''),
  );
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );
  foreach ($filters as $key => $filter) {
    $form['filters']['status']['filters'][$key] = array(
      '#type' => 'select',
      '#options' => $filter['options'],
      '#title' => $filter['title'],
      '#default_value' => '[any]',
    );
  }

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  if (count($filters)) {
    $form['filters']['status']['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => count($session) ? t('Refine') : t('Filter'),
    );
  }
  if (count($session)) {
    $form['filters']['status']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
    $form['filters']['status']['actions']['reset'] = array('#type' => 'submit', '#value' => t('Reset'));
  }

  drupal_add_js('misc/form.js');

  return $form;
}

/**
 * Process result from file administration filter form.
 */
function file_entity_filter_form_submit($form, &$form_state) {
  $filters = file_filters();
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      // Apply every filter that has a choice selected other than 'any'.
      foreach ($filters as $filter => $options) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '[any]') {
          // Flatten the options array to accommodate hierarchical/nested
          // options.
          $flat_options = form_options_flatten($filters[$filter]['options']);
          // Only accept valid selections offered on the dropdown, block bad
          // input.
          if (isset($flat_options[$form_state['values'][$filter]])) {
            $_SESSION['file_entity_overview_filter'][] = array($filter, $form_state['values'][$filter]);
          }
        }
      }
      break;

    case t('Undo'):
      array_pop($_SESSION['file_entity_overview_filter']);
      break;

    case t('Reset'):
      $_SESSION['file_entity_overview_filter'] = array();
      break;

  }
}

/**
 * Make mass update of files.
 *
 * Change all files in the $files array to update them with the field values in
 * $updates.
 *
 * IMPORTANT NOTE: This function is intended to work when called
 * from a form submit handler. Calling it outside of the form submission
 * process may not work correctly.
 *
 * @param array $files
 *   Array of file fids to update.
 * @param array $updates
 *   Array of key/value pairs with file field names and the
 *   value to update that field to.
 */
function file_entity_mass_update($files, $updates) {
  // We use batch processing to prevent timeout when updating a large number
  // of files.
  if (count($files) > 10) {
    $batch = array(
      'operations' => array(
        array(
          '_file_entity_mass_update_batch_process',
          array($files, $updates),
        ),
      ),
      'finished' => '_file_entity_mass_update_batch_finished',
      'title' => t('Processing'),
      // We use a single multi-pass operation, so the default
      // 'Remaining x of y operations' message will be confusing here.
      'progress_message' => '',
      'error_message' => t('The update has encountered an error.'),
      // The operations do not live in the .module file, so we need to
      // tell the batch engine which file to load before calling them.
      'file' => drupal_get_path('module', 'file_entity') . '/file_entity.admin.inc',
    );
    batch_set($batch);
  }
  else {
    foreach ($files as $fid) {
      _file_entity_mass_update_helper($fid, $updates);
    }
    drupal_set_message(t('The update has been performed.'));
  }
}

/**
 * File Mass Update - helper function.
 */
function _file_entity_mass_update_helper($fid, $updates) {
  $file = file_load($fid);
  // For efficiency manually save the original file before applying any changes.
  $file->original = clone $file;
  foreach ($updates as $name => $value) {
    $file->$name = $value;
  }
  file_save($file);
  return $file;
}

/**
 * File Mass Update Batch operation.
 */
function _file_entity_mass_update_batch_process($files, $updates, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($files);
    $context['sandbox']['files'] = $files;
  }

  // Process files by groups of 5.
  $count = min(5, count($context['sandbox']['files']));
  for ($i = 1; $i <= $count; $i++) {
    // For each fid, load the file, reset the values, and save it.
    $fid = array_shift($context['sandbox']['files']);
    $file = _file_entity_mass_update_helper($fid, $updates);

    // Store result for post-processing in the finished callback.
    $context['results'][] = l($file->filename, 'file/' . $file->fid);

    // Update our progress information.
    $context['sandbox']['progress']++;
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * File Mass Update Batch 'finished' callback.
 */
function _file_entity_mass_update_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('The update has been performed.'));
  }
  else {
    drupal_set_message(t('An error occurred and processing did not complete.'), 'error');
    $message = format_plural(count($results), '1 item successfully processed:', '@count items successfully processed:');
    $message .= theme('item_list', array('items' => $results));
    drupal_set_message($message);
  }
}

/**
 * Menu callback: file administration.
 */
function file_entity_admin_file($form, $form_state) {
  if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
    return file_entity_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['files']));
  }
  $form['filter'] = file_entity_filter_form();
  $form['#submit'][] = 'file_entity_filter_form_submit';
  $form['admin'] = file_entity_admin_files();

  return $form;
}

/**
 * Form builder: Builds the file administration overview.
 */
function file_entity_admin_files() {
  $admin_access = user_access('administer files');

  // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
    '#access' => $admin_access,
  );
  $options = array();
  foreach (module_invoke_all('file_operations') as $operation => $array) {
    $options[$operation] = $array['label'];
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array('file_entity_admin_files_validate'),
    '#submit' => array('file_entity_admin_files_submit'),
  );

  // Build the sortable table header.
  $header = array(
    'title' => array('data' => t('Title'), 'field' => 'fm.filename'),
    'type' => array('data' => t('Type'), 'field' => 'fm.type'),
    'size' => array('data' => t('Size'), 'field' => 'fm.filesize'),
    'author' => t('Author'),
    'timestamp' => array(
      'data' => t('Updated'),
      'field' => 'fm.timestamp',
      'sort' => 'desc'),
    'usage' => array('data' => t('Used in'), 'field' => 'total_count'),
    'operations' => array('data' => t('Operations')),
  );

  $query = db_select('file_managed', 'fm')->extend('PagerDefault')->extend('TableSort');
  $query->leftJoin('file_usage', 'fu', 'fm.fid = fu.fid');
  $query->groupBy('fm.fid');
  $query->groupBy('fm.uid');
  $query->groupBy('fm.timestamp');
  $query->addExpression('SUM(fu.count)', 'total_count');
  file_entity_build_filter_query($query);

  $result = $query
    ->fields('fm', array('fid', 'uid'))
    ->limit(50)
    ->orderByHeader($header)
    ->addTag('file_access')
    ->execute()
    ->fetchAllAssoc('fid');
  $files = file_load_multiple(array_keys($result));

  $uids = array();
  foreach ($files as $file) {
    $uids[] = $file->uid;
  }
  $accounts = !empty($uids) ? user_load_multiple(array_unique($uids)) : array();

  // Prepare the list of files.
  $destination = drupal_get_destination();
  $options = array();
  foreach ($files as $file) {
    $file_type = file_type_load($file->type);
    $account = isset($accounts[$file->uid]) ? $accounts[$file->uid] : NULL;
    $options[$file->fid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $file->filename,
          '#href' => 'file/' . $file->fid,
        ),
      ),
      'type' => $file_type ? check_plain($file_type->label) : FILE_TYPE_NONE,
      'size' => format_size($file->filesize),
      'author' => theme('username', array('account' => $account)),
      'timestamp' => format_date($file->timestamp, 'short'),
      'usage' => format_plural((int) $result[$file->fid]->total_count, '1 place', '@count places'),
    );

    // Show a warning for files that do not exist.
    if (@!is_file($file->uri)) {
      $options[$file->fid]['#attributes']['class'][] = 'error';
      if (!file_stream_wrapper_get_instance_by_uri($file->uri)) {
        $options[$file->fid]['#attributes']['title'] = t('The stream wrapper for @scheme files is missing.', array('@scheme' => file_uri_scheme($file->uri)));
      }
      else {
        $options[$file->fid]['#attributes']['title'] = t('The file does not exist.');
      }
    }

    // Build a list of all the accessible operations for the current file.
    $operations = array();
    if (file_entity_access('update', $file)) {
      // Convert the usage count to a link.
      $options[$file->fid]['usage'] = l($options[$file->fid]['usage'], 'file/' . $file->fid . '/usage');
      $operations['edit'] = array(
        'title' => t('Edit'),
        'href' => 'file/' . $file->fid . '/edit',
        'query' => $destination,
      );
    }
    if (file_entity_access('delete', $file)) {
      $operations['delete'] = array(
        'title' => t('Delete'),
        'href' => 'file/' . $file->fid . '/delete',
        'query' => $destination,
      );
    }
    $options[$file->fid]['operations'] = array();
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$file->fid]['operations'] = array(
        'data' => array(
          '#theme' => 'links__file_entity_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
    }
    elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$file->fid]['operations'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => array('query' => $link['query']),
        ),
      );
    }
  }

  // Only use a tableselect when the current user is able to perform any
  // operations.
  if ($admin_access) {
    $form['files'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No files available.'),
    );
  }
  // Otherwise, use a simple table.
  else {
    $form['files'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      '#empty' => t('No files available.'),
    );
  }

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

/**
 * Validate file_entity_admin_files form submissions.
 *
 * Check if any files have been selected to perform the chosen
 * 'Update option' on.
 */
function file_entity_admin_files_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['files']) || !count(array_filter($form_state['values']['files']))) {
    form_set_error('', t('No items selected.'));
  }
}

/**
 * Process file_entity_admin_files form submissions.
 *
 * Execute the chosen 'Update option' on the selected files.
 */
function file_entity_admin_files_submit($form, &$form_state) {
  $operations = module_invoke_all('file_operations');
  $operation = $operations[$form_state['values']['operation']];
  // Filter out unchecked files.
  $files = array_filter($form_state['values']['files']);
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($files), $operation['callback arguments']);
    }
    else {
      $args = array($files);
    }
    call_user_func_array($function, $args);

    cache_clear_all();
  }
  else {
    // We need to rebuild the form to go to a second step. For example, to
    // show the confirmation form for the deletion of files.
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * File entity delete confirmation.
 */
function file_entity_multiple_delete_confirm($form, &$form_state, $files) {
  $form['files'] = array(
    '#prefix' => '<ul>',
    '#suffix' => '</ul>',
    '#tree' => TRUE,
  );
  // array_filter returns only elements with TRUE values.
  foreach ($files as $fid => $value) {
    $filename = db_query('SELECT filename FROM {file_managed} WHERE fid = :fid', array(':fid' => $fid))->fetchField();
    $form['files'][$fid] = array(
      '#type' => 'hidden',
      '#value' => $fid,
      '#prefix' => '<li>',
      '#suffix' => check_plain($filename) . "</li>\n",
    );
  }
  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
  $form['#submit'][] = 'file_entity_multiple_delete_confirm_submit';
  $confirm_question = format_plural(count($files),
                                  'Are you sure you want to delete this item?',
                                  'Are you sure you want to delete these items?');
  return confirm_form($form,
                    $confirm_question,
                    'admin/content/file', t('This action cannot be undone.'),
                    t('Delete'), t('Cancel'));
}

/**
 * Submit handler for delete confirmation.
 */
function file_entity_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    file_delete_multiple(array_keys($form_state['values']['files']));
    $count = count($form_state['values']['files']);
    watchdog('file_entity', 'Deleted @count files.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 file.', 'Deleted @count files.'));
  }
  $form_state['redirect'] = 'admin/content/file';
}

/**
 * Displays the file type admin overview page.
 */
function file_entity_list_types_page() {
  $file_entity_info = entity_get_info('file');
  // Newer versions of Drupal core require the "administer fields" permission
  // to access the Field UI.
  $field_ui = module_exists('field_ui') && (user_access('administer fields') || !function_exists('field_ui_admin_access'));
  $colspan = $field_ui ? 5 : 3;
  $header = array(
    array('data' => t('Name')),
    array('data' => t('Operations'), 'colspan' => $colspan),
    array('data' => t('Status')),
  );
  $rows = array();
  $weight = 0;
  $types = file_type_load_all(TRUE);
  $count = count($types);
  foreach ($types as $type) {
    $weight++;
    $row = array(
      array(
        'data' => theme('file_entity_file_type_overview',
          array(
            'label' => $type->label,
            'description' => $type->description,
          )
        ),
      ),
    );
    $path = isset($file_entity_info['bundles'][$type->type]['admin']['real path']) ? $file_entity_info['bundles'][$type->type]['admin']['real path'] : NULL;

    if (empty($type->disabled) && isset($path)) {
      $row[] = array('data' => l(t('edit file type'), $path . '/edit'));
      if ($field_ui) {
        $row[] = array('data' => l(t('manage fields'), $path . '/fields'));
        $row[] = array('data' => l(t('manage display'), $path . '/display'));
      }
      $row[] = array('data' => l(t('manage file display'), $path . '/file-display'));
    }
    else {
      $row += array_fill(1, $colspan - 1, '');
    }

    $admin_path = 'admin/structure/file-types/manage/' . $type->type;
    switch ($type->ctools_type) {
      // Configuration is in code.
      case 'Default':
        if (!empty($type->disabled)) {
          $row[] = l(t('enable'), $admin_path . '/enable');
        }
        else {
          $row[] = l(t('disable'), $admin_path . '/disable');
        }
        break;

      // Configuration is in DB.
      case 'Normal':
        if (!empty($type->disabled)) {
          $status = l(t('enable'), $admin_path . '/enable');
        }
        else {
          $status = l(t('disable'), $admin_path . '/disable');
        }
        $row[] = $status . ' | ' . l(t('delete'), $admin_path . '/delete');
        break;

      // Configuration is in code, but overridden in DB.
      case 'Overridden':
        if (!empty($type->disabled)) {
          $row[] = l(t('enable'), $admin_path . '/enable');
        }
        else {
          $row[] = l(t('disable'), $admin_path . '/disable') . ' | ' . l(t('revert'), $admin_path . '/revert');
        }
        break;
    }

    if (!empty($type->disabled)) {
      $row[] = t('Disabled');
      $rows[$weight + $count] = array('data' => $row, 'class' => array('ctools-export-ui-disabled'));
    }
    else {
      $row[] = $type->ctools_type;
      $rows[$weight] = array('data' => $row);
    }
  }

  // Move disabled items to the bottom.
  ksort($rows);

  $build['file_type_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No file types available.'),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'ctools') . '/css/export-ui-list.css'),
    ),
  );

  return $build;
}

/**
 * Form callback; presents file display settings for a given view mode.
 */
function file_entity_file_display_form($form, &$form_state, $file_type, $view_mode) {
  $form['#file_type'] = $file_type->type;
  $form['#view_mode'] = $view_mode;
  $form['#tree'] = TRUE;
  $form['#attached']['js'][] = drupal_get_path('module', 'file_entity') . '/file_entity.admin.js';

  // Retrieve available formatters for this file type and load all configured
  // filters for existing text formats.
  $formatters = file_info_formatter_types();
  foreach ($formatters as $name => $formatter) {
    if (!empty($formatter['hidden'])) {
      unset($formatters[$name]);
    }
    if (isset($formatter['mime types'])) {
      if (file_entity_match_mimetypes($formatter['mime types'], $file_type->mimetypes)) {
        continue;
      }
      unset($formatters[$name]);
    }
  }
  $current_displays = file_displays_load($file_type->type, $view_mode, TRUE);
  foreach ($current_displays as $name => $display) {
    $current_displays[$name] = (array) $display;
  }

  // Formatter status.
  $form['displays']['status'] = array(
    '#type' => 'item',
    '#title' => t('Enabled displays'),
    '#prefix' => '<div id="file-displays-status-wrapper">',
    '#suffix' => '</div>',
  );
  $i = 0;
  foreach ($formatters as $name => $formatter) {
    $form['displays']['status'][$name] = array(
      '#type' => 'checkbox',
      '#title' => check_plain($formatter['label']),
      '#default_value' => !empty($current_displays[$name]['status']),
      '#description' => isset($formatter['description']) ? filter_xss($formatter['description']) : NULL,
      '#parents' => array('displays', $name, 'status'),
      '#weight' => (isset($formatter['weight']) ? $formatter['weight'] : 0) + ($i / 1000),
    );
    $i++;
  }

  // Formatter order (tabledrag).
  $form['displays']['order'] = array(
    '#type' => 'item',
    '#title' => t('Display precedence order'),
    '#theme' => 'file_entity_file_display_order',
  );
  foreach ($formatters as $name => $formatter) {
    $form['displays']['order'][$name]['label'] = array(
      '#markup' => check_plain($formatter['label']),
    );
    $form['displays']['order'][$name]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight for @title', array('@title' => $formatter['label'])),
      '#title_display' => 'invisible',
      '#delta' => 50,
      '#default_value' => isset($current_displays[$name]['weight']) ? $current_displays[$name]['weight'] : 0,
      '#parents' => array('displays', $name, 'weight'),
    );
    $form['displays']['order'][$name]['#weight'] = $form['displays']['order'][$name]['weight']['#default_value'];
  }

  // Formatter settings.
  $form['display_settings_title'] = array(
    '#type' => 'item',
    '#title' => t('Display settings'),
  );
  $form['display_settings'] = array(
    '#type' => 'vertical_tabs',
  );
  $i = 0;
  foreach ($formatters as $name => $formatter) {
    if (isset($formatter['settings callback']) && ($function = $formatter['settings callback']) && function_exists($function)) {
      $defaults = !empty($formatter['default settings']) ? $formatter['default settings'] : array();
      $settings = !empty($current_displays[$name]['settings']) ? $current_displays[$name]['settings'] : array();
      $settings += $defaults;
      $settings_form = $function($form, $form_state, $settings, $name, $file_type->type, $view_mode);
      if (!empty($settings_form)) {
        $form['displays']['settings'][$name] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($formatter['label']),
          '#parents' => array('displays', $name, 'settings'),
          '#group' => 'display_settings',
          '#weight' => (isset($formatter['weight']) ? $formatter['weight'] : 0) + ($i / 1000),
        ) + $settings_form;
      }
    }
    $i++;
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Process file display settings form submissions.
 */
function file_entity_file_display_form_submit($form, &$form_state) {
  $file_type = $form['#file_type'];
  $view_mode = $form['#view_mode'];
  $displays = isset($form_state['values']['displays']) ? $form_state['values']['displays'] : array();
  $displays_original = file_displays_load($file_type, $view_mode, TRUE);
  foreach ($displays as $formatter_name => $display) {
    $display_original = isset($displays_original[$formatter_name]) ? $displays_original[$formatter_name] : file_display_new($file_type, $view_mode, $formatter_name);
    $display += (array) $display_original;
    file_display_save((object) $display);
  }
  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Returns HTML for the file type overview page.
 *
 * Specifically, this returns HTML for a file type label and description.
 */
function theme_file_entity_file_type_overview($variables) {
  return check_plain($variables['label']) . '<div class="description">' . $variables['description'] . '</div>';
}

/**
 * Returns HTML for a file display's display order table.
 */
function theme_file_entity_file_display_order($variables) {
  $element = $variables['element'];

  $rows = array();
  foreach (element_children($element, TRUE) as $name) {
    $element[$name]['weight']['#attributes']['class'][] = 'file-display-order-weight';
    $rows[] = array(
      'data' => array(
        drupal_render($element[$name]['label']),
        drupal_render($element[$name]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  $output = drupal_render_children($element);
  $output .= theme('table', array('rows' => $rows, 'attributes' => array('id' => 'file-displays-order')));
  drupal_add_tabledrag('file-displays-order', 'order', 'sibling', 'file-display-order-weight', NULL, NULL, TRUE);

  return $output;
}

/**
 * Form constructor for the file type settings form.
 *
 * @param object $type
 *   The file type.
 *
 * @see file_entity_file_type_form_validate()
 * @see file_entity_file_type_form_submit()
 */
function file_entity_file_type_form($form, &$form_state, $type = NULL) {
  if (!isset($type->type)) {
    // This is a new type.
    $type = (object) array(
      'type' => '',
      'label' => '',
      'description' => '',
      'mimetypes' => array(),
    );
  }
  $form['#file_type'] = $type;

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('This is the human readable name of the file type.'),
    '#required' => TRUE,
    '#default_value' => $type->label,
  );

  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => $type->type,
    '#maxlength' => 255,
    '#disabled' => (bool) $type->type,
    '#machine_name' => array(
      'exists' => 'file_type_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this file type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('This is the description of the file type.'),
    '#default_value' => $type->description,
  );

  $form['mimetypes'] = array(
    '#type' => 'textarea',
    '#title' => t('Mimetypes'),
    '#description' => t('Enter one mimetype per line.'),
    '#default_value' => implode("\n", $type->mimetypes),
  );

  include_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';
  $mimetypes = file_mimetype_mapping();

  $form['mimetype_mapping'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mimetype List'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['mimetype_mapping']['mapping'] = array(
    '#theme' => 'item_list',
    '#items' => $mimetypes['mimetypes'],
  );

  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  if (!empty($type->type)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }

  return $form;
}

/**
 * Form validation handler for file_entity_file_type_form().
 *
 * @see file_entity_file_type_form_submit()
 */
function file_entity_file_type_form_validate($form, &$form_state) {
  include_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';
  $mimetype_mapping = file_mimetype_mapping();

  $valid_mimetypes = $mimetype_mapping['mimetypes'];
  $submitted_mimetypes = array_filter(array_map('trim', explode("\n", $form_state['values']['mimetypes'])));

  $invalid_mimetypes = array();
  foreach ($submitted_mimetypes as $mimetype) {
    if (!file_entity_match_mimetypes($mimetype, $valid_mimetypes)) {
      $invalid_mimetypes[] = $mimetype;
    }
  }

  foreach ($invalid_mimetypes as $mimetype) {
    form_set_error('mimetypes', t('The mimetype %mimetype is not a valid mimetype.', array('%mimetype' => $mimetype)));
  }
}

/**
 * Form submission handler for file_entity_file_type_form().
 *
 * @see file_entity_file_type_form_validate()
 */
function file_entity_file_type_form_submit($form, &$form_state) {
  if (!empty($form['#file_type']->type)) {
    $type = file_type_load($form['#file_type']->type);
  }
  else {
    $type = (object) array(
      'type' => $form_state['values']['type'],
    );
  }
  if ($form_state['values']['op'] == t('Delete')) {
    $form_state['redirect'] = 'admin/structure/file-types/manage/' . $type->type . '/delete';
    return;
  }
  $type->label = $form_state['values']['label'];
  $type->description = $form_state['values']['description'];
  $type->mimetypes = array_filter(array_map('trim', explode("\n", $form_state['values']['mimetypes'])));

  file_type_save($type);

  drupal_set_message(t('The file type %type has been updated.', array('%type' => $type->label)));
  $form_state['redirect'] = 'admin/structure/file-types';
}


/**
 * Menu callback; disable a single file type.
 */
function file_entity_type_enable_confirm($form, &$form_state, $type) {
  $form['type'] = array('#type' => 'value', '#value' => $type->type);
  $form['label'] = array('#type' => 'value', '#value' => $type->label);
  $message = t('Are you sure you want to enable the file type %type?', array('%type' => $type->label));
  return confirm_form($form, $message, 'admin/structure/file-types', '', t('Enable'));
}


/**
 * Process file type disable confirm submissions.
 */
function file_entity_type_enable_confirm_submit($form, &$form_state) {
  file_type_enable($form_state['values']['type']);
  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The file type %label has been enabled.', $t_args));
  watchdog('file_entity', 'Enabled file type %label.', $t_args, WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/structure/file-types';
  return;
}


/**
 * Menu callback; disable a single file type.
 */
function file_entity_type_disable_confirm($form, &$form_state, $type) {
  $form['type'] = array('#type' => 'value', '#value' => $type->type);
  $form['label'] = array('#type' => 'value', '#value' => $type->label);

  $message = t('Are you sure you want to disable the file type %type?', array('%type' => $type->label));
  $caption = '';

  $num_files = db_query("SELECT COUNT(*) FROM {file_managed} WHERE type = :type", array(':type' => $type->type))->fetchField();
  if ($num_files) {
    $caption .= '<p>' . format_plural($num_files, '%type is used by 1 file on
      your site. If you disable this file type, you will not be able to edit
      the %type file and it may not display correctly.', '%type is used by
      @count files on your site. If you remove %type, you will not be able to
      edit the %type file and it may not display correctly.',
    array('%type' => $type->label)) . '</p>';
  }

  return confirm_form($form, $message, 'admin/structure/file-types', $caption, t('Disable'));
}


/**
 * Process file type disable confirm submissions.
 */
function file_entity_type_disable_confirm_submit($form, &$form_state) {
  file_type_disable($form_state['values']['type']);
  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The file type %label has been disabled.', $t_args));
  watchdog('file_entity', 'Disabled file type %label.', $t_args, WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/structure/file-types';
  return;
}


/**
 * Menu callback; revert a single file type.
 */
function file_entity_type_revert_confirm($form, &$form_state, $type) {
  $form['type'] = array('#type' => 'value', '#value' => $type->type);
  $form['label'] = array('#type' => 'value', '#value' => $type->label);
  $message = t('Are you sure you want to revert the file type %type?', array('%type' => $type->label));
  return confirm_form($form, $message, 'admin/structure/file-types', '', t('Revert'));
}


/**
 * Process file type delete confirm submissions.
 */
function file_entity_type_revert_confirm_submit($form, &$form_state) {
  // @NOTE deleting the file_type from the DB actually reverts it to code.
  file_type_delete($form_state['values']['type']);
  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The file type %label has been reverted.', $t_args));
  watchdog('file_entity', 'Reverted file type %label.', $t_args, WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/structure/file-types';
  return;
}


/**
 * Menu callback; delete a single file type.
 */
function file_entity_type_delete_confirm($form, &$form_state, $type) {
  $form['type'] = array('#type' => 'value', '#value' => $type->type);
  $form['label'] = array('#type' => 'value', '#value' => $type->label);

  $message = t('Are you sure you want to delete the file type %type?', array('%type' => $type->label));
  $caption = '';

  $num_files = db_query("SELECT COUNT(*) FROM {file_managed} WHERE type = :type", array(':type' => $type->type))->fetchField();
  if ($num_files) {
    $caption .= '<p>' . format_plural($num_files, '%type is used by 1 file on your site. If you remove this file type, you will not be able to edit the %type file and it may not display correctly.', '%type is used by @count pieces of file on your site. If you remove %type, you will not be able to edit the %type file and it may not display correctly.', array('%type' => $type->label)) . '</p>';
  }

  $caption .= '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $message, 'admin/structure/file-types', $caption, t('Delete'));
}

/**
 * Process file type delete confirm submissions.
 */
function file_entity_type_delete_confirm_submit($form, &$form_state) {
  file_type_delete($form_state['values']['type']);

  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The file type %label has been deleted.', $t_args));
  watchdog('file_entity', 'Deleted file type %label.', $t_args, WATCHDOG_NOTICE);

  $form_state['redirect'] = 'admin/structure/file-types';
  return;
}

/**
 * Form callback for file_entity settings.
 */
function file_entity_settings_form($form, &$form_state) {
  $form['file_entity_max_filesize'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum upload size'),
    '#default_value' => variable_get('file_entity_max_filesize', ''),
    '#description' => t('Enter a value like "512" (bytes), "80 KB" (kilobytes) or "50 MB" (megabytes) in order to restrict the allowed file size. If left empty the file sizes will be limited only by PHP\'s maximum post and file upload sizes (current max limit <strong>%limit</strong>).', array('%limit' => format_size(file_upload_max_size()))),
    '#size' => 10,
    '#element_validate' => array('_file_generic_settings_max_filesize'),
  );

  $form['file_entity_default_allowed_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Default allowed file extensions'),
    '#default_value' => variable_get('file_entity_default_allowed_extensions', 'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm'),
    '#description' => t('Separate extensions with a space or comma and do not include the leading dot.'),
    '#maxlength' => NULL,
  );

  $form['file_entity_alt'] = array(
    '#type' => 'textfield',
    '#title' => t('Alt attribute'),
    '#description' => t('The text to use as value for the <em>img</em> tag <em>alt</em> attribute.'),
    '#default_value' => variable_get('file_entity_alt', '[file:field_file_image_alt_text]'),
  );
  $form['file_entity_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title attribute'),
    '#description' => t('The text to use as value for the <em>img</em> tag <em>title</em> attribute.'),
    '#default_value' => variable_get('file_entity_title', '[file:field_file_image_title_text]'),
  );

  // Provide default token values.
  if (module_exists('token')) {
    $form['token_help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('file'),
      '#dialog' => TRUE,
    );
    $form['file_entity_alt']['#description'] .= t('This field supports tokens.');
    $form['file_entity_title']['#description'] .= t('This field supports tokens.');
  }
  $form['file_upload_wizard'] = array(
    '#type' => 'fieldset',
    '#title' => t('File upload wizard'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Configure the steps available when uploading a new file.'),
  );
  $form['file_upload_wizard']['file_entity_file_upload_wizard_skip_file_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip filetype selection.'),
    '#default_value' => variable_get('file_entity_file_upload_wizard_skip_file_type', FALSE),
    '#description' => t('The file type selection step is only available if the uploaded file falls into two or more file types. If this step is skipped, files with no available file type or two or more file types will not be assigned a file type.'),
  );
  $form['file_upload_wizard']['file_entity_file_upload_wizard_skip_scheme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip scheme selection.'),
    '#default_value' => variable_get('file_entity_file_upload_wizard_skip_scheme', FALSE),
    '#description' => t('The scheme selection step is only available if two or more file destinations, such as public local files served by the webserver and private local files served by Drupal, are available. If this step is skipped, files will automatically be saved using the default download method.'),
  );
  $form['file_upload_wizard']['file_entity_file_upload_wizard_skip_fields'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip available fields.'),
    '#default_value' => variable_get('file_entity_file_upload_wizard_skip_fields', FALSE),
    '#description' => t('The field selection step is only available if the file type the file belongs to has any available fields. If this step is skipped, any fields on the file will be left blank.'),
  );

  return system_settings_form($form);
}
