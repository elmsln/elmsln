<?php

/**
 * @file
 * Field UI functions for Display Suite.
 */

/**
 * Adds the Display Suite fields and layouts to the form.
 */
function ds_field_ui_fields_layouts(&$form, &$form_state) {
  global $base_root, $base_path;

  // Get the entity_type, bundle and view mode.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  $form['#export_id'] = $entity_type . '|' . $bundle . '|' . $view_mode;

  // Create vertical tabs.
  ds_field_ui_create_vertical_tabs($form);

  // Add layout fieldset.
  _ds_field_ui_table_layouts($entity_type, $bundle, $view_mode, $form, $form_state);

  // Add/alter fields on the table, but only if a layout is selected.
  if ($view_mode != 'form' && !empty($form['#ds_layout'])) {
    _ds_field_ui_fields($entity_type, $bundle, $view_mode, $form, $form_state);

    // Also alter core fields
    _ds_field_ui_core_fields($entity_type, $bundle, $view_mode, $form, $form_state);
  }

  // Add buttons to add fields in overlay.
  if (isset($form['#ds_layout']) && user_access('admin_fields') && $view_mode != 'form' && module_exists('ds_ui')) {
    _ds_field_ui_custom_fields($entity_type, $bundle, $view_mode, $form, $form_state);
  }

  // Special validate function for field group.
  if (isset($form_state['no_field_group'])) {
    array_unshift($form['#validate'], '_ds_field_group_field_ui_fix_notices');
  }

  // Attach js.
  $form['#attached']['js'][] = drupal_get_path('module', 'ds') . '/js/ds.admin.js';

  // Attach css.
  $form['#attached']['css'][] = drupal_get_path('module', 'ds') . '/css/ds.admin.css';

  // Add process function to add the regions.
  $form['#process'][] = 'ds_field_ui_regions';

  // Add a destination so we can get back if layout has been changed.
  $form['ds_source'] = array(
    '#type' => 'hidden',
    '#value' => $base_root . $base_path,
  );
  $form['ds_destination'] = array(
    '#type' => 'hidden',
    '#value' => drupal_get_destination(),
  );
  $form['ds_entity_type'] = array(
    '#type' => 'hidden',
    '#value' => $entity_type,
  );
  $form['ds_bundle'] = array(
    '#type' => 'hidden',
    '#value' => $bundle,
  );
  $form['ds_view_mode'] = array(
    '#type' => 'hidden',
    '#value' => $view_mode,
  );
}

/**
 * Create vertical tabs.
 */
function ds_field_ui_create_vertical_tabs(&$form) {

  // Add additional settings vertical tab.
  if (!isset($form['additional_settings'])) {
    $form['additional_settings'] = array(
      '#type' => 'vertical_tabs',
      '#theme_wrappers' => array('vertical_tabs'),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#tree' => TRUE,
    );
    $form['#attached']['js'][] = 'misc/form.js';
    $form['#attached']['js'][] = 'misc/collapse.js';
  }

  $view_mode_admin_access = user_access('admin_view_modes') && module_exists('ds_ui');
  if (isset($form['modes'])) {
    if ($view_mode_admin_access) {
      $form['modes']['view_modes_custom']['#description'] = l(t('Manage view modes'), 'admin/structure/ds/view_modes');
    }
    $form['additional_settings']['modes'] = $form['modes'];
    $form['additional_settings']['modes']['#weight'] = -10;
    unset($form['modes']);
  }
  else {
    if ($view_mode_admin_access) {
      $form['additional_settings']['modes']['view_modes_custom']['#description'] = l(t('Manage view modes'), 'admin/structure/ds/view_modes');
    }
  }
}

/**
 * Menu callback: Disable layout and field settings form.
 */
function ds_disable_layout_field_settings_form($form, &$form_state, $id = '') {
  $layout = new stdClass();
  ctools_include('export');
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  if (isset($ds_layout_settings[$id])) {
    $layout = $ds_layout_settings[$id];
  }

  if (isset($layout) && $layout->export_type != 1 && empty($layout->disable)) {
    $form['#layout'] = $layout;
    $form['#export_id'] = $id;
    return confirm_form($form,
      t('Are you sure you want to disable the layout and field settings for %layout?', array('%layout' => implode(', ', explode('|', $layout->id)))),
      drupal_get_destination(),
      t('This action cannot be undone.'),
      t('Disable'),
      t('Cancel')
    );
  }
  else {
    drupal_set_message(t('This operation is not possible.'));
  }
}

/**
 * Submit callback: disable layout and field settings.
 */
function ds_disable_layout_field_settings_form_submit(&$form, &$form_state) {
  $layout = $form['#layout'];

  ctools_include('export');
  ctools_export_crud_disable('ds_layout_settings', $form['#export_id']);
  ctools_export_crud_disable('ds_field_settings', $form['#export_id']);
  // @todo layout fields

  // Clear the ds_fields cache.
  cache_clear_all('ds_fields:', 'cache', TRUE);
  cache_clear_all('ds_field_settings', 'cache');

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  drupal_set_message(t('Layout has been disabled.'));

  $form_state['redirect'] = isset($_GET['destination']) ? $_GET['destination'] : drupal_get_destination();
}

/**
 * Menu callback: Enable layout and field settings form.
 */
function ds_enable_layout_field_settings_form($form, &$form_state, $id = '') {
  $layout = new stdClass();
  ctools_include('export');
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  if (isset($ds_layout_settings[$id])) {
    $layout = $ds_layout_settings[$id];
  }

  if (isset($layout) && $layout->export_type != 1 && !empty($layout->disabled)) {
    $form['#layout'] = $layout;
    $form['#export_id'] = $id;
    return confirm_form($form,
      t('Are you sure you want to enable the layout and field settings for %layout?', array('%layout' => implode(', ', explode('|', $layout->id)))),
      drupal_get_destination(),
      t('This action cannot be undone.'),
      t('Enable'),
      t('Cancel')
    );
  }
  else {
    drupal_set_message(t('This operation is not possible.'));
  }
}

/**
 * Submit callback: enable layout and field settings.
 */
function ds_enable_layout_field_settings_form_submit(&$form, &$form_state) {
  $layout = $form['#layout'];

  ctools_include('export');
  ctools_export_crud_enable('ds_layout_settings', $form['#export_id']);
  ctools_export_crud_enable('ds_field_settings', $form['#export_id']);

  // Clear the ds_fields cache.
  cache_clear_all('ds_fields:', 'cache', TRUE);
  cache_clear_all('ds_field_settings', 'cache');

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  drupal_set_message(t('Layout has been enabled'));

  $form_state['redirect'] = isset($_GET['destination']) ? $_GET['destination'] : drupal_get_destination();
}

/**
 * Menu callback: Revert layout and field settings form.
 */
function ds_revert_layout_field_settings_form($form, &$form_state, $id = '') {
  $layout = new stdClass();
  ctools_include('export');
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  if (isset($ds_layout_settings[$id])) {
    $layout = $ds_layout_settings[$id];
  }

  if (isset($layout) && $layout->export_type == 3) {
    $form['#layout'] = $layout;
    return confirm_form($form,
      t('Are you sure you want to revert the layout for %layout?', array('%layout' => implode(', ', explode('|', $layout->id)))),
      drupal_get_destination(),
      t('This action cannot be undone.'),
      t('Revert'),
      t('Cancel')
    );
  }
  else {
    drupal_set_message(t('This operation is not possible.'));
  }
}

/**
 * Submit callback: revert layout and field settings.
 */
function ds_revert_layout_field_settings_form_submit(&$form, &$form_state) {
  $layout = $form['#layout'];

  db_delete('ds_field_settings')
    ->condition('id', $layout->id)
    ->execute();

  db_delete('ds_layout_settings')
    ->condition('id', $layout->id)
    ->execute();

  // Clear the ds_fields cache.
  cache_clear_all('ds_fields:', 'cache', TRUE);
  cache_clear_all('ds_field_settings', 'cache');

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  drupal_set_message(t('Layout has been reverted'));

  $form_state['redirect'] = isset($_GET['destination']) ? $_GET['destination'] : drupal_get_destination();
}

/**
 * Add Regions to 'Manage fields' or 'Manage display' screen.
 *
 * @param $form
 *   The form to add layout fieldset and extra Display Suite fields.
 * @param $form_state
 *   The current form state.
 */
function ds_field_ui_regions($form, $form_state) {

  // Get the entity_type, bundle and view mode.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Ignore fieldgroup options.
  if (isset($form_state['no_field_group'])) {
    unset($form['fields']['_add_new_group']);
    $form['additional_settings']['field_group']['#access'] = FALSE;
  }

  // Check layout.
  $layout = isset($form['#ds_layout']) ? $form['#ds_layout'] : FALSE;

  // Change UI to add Region column if we have a layout.
  if ($layout) {
    $table = &$form['fields'];

    if ($view_mode != 'form') {
      $table['#header'] = array(
        t('Field'),
        t('Weight'),
        t('Parent'),
        t('Region'),
        t('Label'),
        array('data' => t('Format'), 'colspan' => 3),
      );
    }
    else {
      $table['#header'] = array(
        t('Label'),
        t('Weight'),
        t('Parent'),
        t('Region'),
        t('Name'),
        t('Field'),
        t('Widget'),
        array('data' => t('Operations'), 'colspan' => 2),
      );
    }

    // Remove label and format for views.
    if ($entity_type == 'ds_views') {
      $table['#header'][4] = '';
    }

    $table['#regions'] = array();
    foreach ($layout->regions as $region_key => $region_title) {
      $region_options[$region_key] = $region_title;
      $table['#regions'][$region_key] = array(
        'title' => $region_title,
        'message' => t('No fields are displayed in this region'),
      );
    }

    // Let other modules alter the regions.
    $context = array(
      'entity_type' => $entity_type,
      'bundle' => $bundle,
      'view_mode' => $view_mode
    );
    $region_info = array(
      'region_options' => &$region_options,
      'table_regions' => &$table['#regions'],
    );
    drupal_alter('ds_layout_region', $context, $region_info);

    $region_options['hidden'] = $view_mode != 'form' ? t('Disabled') : t('Hidden');
    $table['#regions']['hidden'] = array(
      'title' => $view_mode != 'form' ? t('Disabled') : t('Hidden'),
      'message' => t('No fields are hidden.')
    );

    $region = array(
      '#type' => 'select',
      '#options' => $region_options,
      '#default_value' => 'hidden',
      '#attributes' => array(
        'class' => array('ds-field-region'),
      )
    );

    $limit_items = array(
      '#type' => 'textfield',
      '#size' => 2,
      '#default_value' => '',
      '#weight' => 10,
      '#default_value' => '#',
      '#prefix' => '<div class="limit-float">',
      '#suffix' => '</div><div class="clearfix"></div>',
      '#attributes' => array(
        'alt' => t('Enter a number to limit the number of items or \'delta\' to print a specific delta (usually configured in views or found in entity->ds_delta). Leave empty to display them all. Note that depending on the formatter settings, this option might not always work.'),
        'title' => t('Enter a number to limit the number of items or \'delta\' to print a specific delta (usually configured in views or found in entity->ds_delta). Leave empty to display them all. Note that depending on the formatter settings, this option might not always work.'),
      ),
    );

    // Hide this if we formatter_settings_edit is not empty so it doesn't confuse users.
    if (!empty($form_state['formatter_settings_edit'])) {
      $limit_items['#access'] = FALSE;
    }

    // Update existing rows by changing rowHandler and adding regions.
    foreach (element_children($table) as $name) {
      $row = &$table[$name];
      $row['#js_settings'] = array('rowHandler' => 'ds');
      $row['#region_callback'] = 'ds_field_ui_row_region';

      // Remove hidden format.
      if (isset($row['format']['type']['#options']['hidden'])) {
        unset($row['format']['type']['#options']['hidden']);
      }

      // Add label class.
      if (isset($row['label'])) {
        if (isset($form_state['formatter_settings']) && isset($form_state['formatter_settings'][$name]['ft'])) {
          if (!empty($form_state['formatter_settings'][$name]['ft']['lb'])) {
            $row['human_name']['#markup'] = check_plain($form_state['formatter_settings'][$name]['ft']['lb']) . ' ' . t('(Original: !orig)', array('!orig' => $row['human_name']['#markup']));
          }
        }
      }

      // Limit items.
      $field_info = field_info_field($name);
      if (isset($field_info['cardinality']) && $field_info['cardinality'] != 1 && $view_mode != 'form') {
        $row['format']['type']['#prefix'] = '<div class="limit-float">';
        $row['format']['type']['#suffix'] = '</div>';
        $row['format']['limit'] = $limit_items;
        $row['format']['limit']['#default_value'] = (isset($layout->settings['limit']) && isset($layout->settings['limit'][$name])) ? $layout->settings['limit'][$name] : '#';
      }

      // Disable label and format for views.
      if ($entity_type == 'ds_views') {
        $row['label']['#access'] = FALSE;
      }

      // Add region.
      $split = ($view_mode != 'form') ? 7 : 6;
      if ($row['#row_type'] == 'group' && $view_mode == 'form') {
        $split = ($view_mode != 'form') ? 8 : 7;
      }
      $second = array_splice($row, $split);
      $row['region'] = $region;
      $row['region']['#default_value'] = (isset($layout->settings['fields'][$name]) && isset($region_options[$layout->settings['fields'][$name]])) ? $layout->settings['fields'][$name] : 'hidden';
      $row = array_merge($row, $second);
    }
  }

  return $form;
}

/**
 * Returns the region to which a row in the Field UI screen belongs.
 *
 * @param $row
 *   The current row that is being rendered in the Field UI screen.
 */
function ds_field_ui_row_region($row) {
  return isset($row['region']['#value']) ? $row['region']['#value'] : 'hidden';
}

/**
 * Move the view modes so Field UI can handle them.
 */
function ds_field_ui_layouts_validate($form, &$form_state) {
  if (isset($form_state['values']['additional_settings']['modes']['view_modes_custom'])) {
    $form_state['values']['view_modes_custom'] = $form_state['values']['additional_settings']['modes']['view_modes_custom'];
  }
}

/**
 * Change a layout for a given entity.
 *
 * @param $entity_type
 *   The name of the entity.
 * @param $bundle
 *   The name of the bundle.
 * @param $view_mode
 *   The name of the view mode.
 */
function ds_field_ui_layout_change($form, $form_state, $entity_type = '', $bundle = '', $view_mode = '', $new_layout = '') {

  $old_layout = NULL;
  $all_layouts = ds_get_layout_info();

  if (!empty($entity_type) && !empty($bundle) && !empty($view_mode)) {
    $old_layout = ds_get_layout($entity_type, $bundle, $view_mode, FALSE);
  }

  if ($old_layout && isset($all_layouts[$new_layout])) {

    $new_layout_key = $new_layout;
    $new_layout = $all_layouts[$new_layout];

    $form['#entity_type'] = $entity_type;
    $form['#bundle'] = $bundle;
    $form['#view_mode'] = $view_mode;
    $form['#old_layout'] = $old_layout;
    $form['#new_layout'] = $new_layout;
    $form['#new_layout_key'] = $new_layout_key;
    $form['#export_id'] = $entity_type . '|' . $bundle . '|' . $view_mode;

    $form['info'] = array(
      '#markup' => t('You are changing from %old to %new layout for !bundle in !view_mode view mode.', array('%old' => $old_layout['label'], '%new' => $new_layout['label'], '!bundle' => $bundle, '!view_mode' => $view_mode)),
      '#prefix' => "<div class='change_ds_layout_info'>",
      '#suffix' => "</div>",
    );

    // Old region options.
    $regions = array();
    foreach ($old_layout['regions'] as $key => $title) {
      $regions[$key] = $title;
    }

    // Let other modules alter the regions.
    // For old regions.
    $context = array(
      'entity_type' => $entity_type,
      'bundle' => $bundle,
      'view_mode' => $view_mode,
    );
    $region_info = array(
      'region_options' => $regions,
    );
    drupal_alter('ds_layout_region', $context, $region_info);
    $regions = $region_info['region_options'];
    $form['#old_layout']['regions'] = $regions;

    // For new regions.
    $region_info = array(
      'region_options' => $new_layout['regions'],
    );
    drupal_alter('ds_layout_region', $context, $region_info);
    $new_layout['regions'] = $region_info['region_options'];
    $form['#new_layout']['regions'] = $new_layout['regions'];

    // Display the region options
    $selectable_regions = array('' => t('- None -')) + $new_layout['regions'];
    $form['regions_pre']['#markup'] = '<div class="ds-layout-regions">';
    foreach ($regions as $region => $region_title) {
      $form['region_' . $region] = array(
        '#type' => 'container',
      );
      $form['region_' . $region]['ds_label_' . $region] = array(
        '#markup' => 'Fields in <span class="change_ds_layout_old_region"> ' . $region_title . '</span> go into',
      );
      $form['region_' . $region]['ds_' . $region] = array(
        '#type' => 'select',
        '#options' => $layout_options = $selectable_regions,
        '#default_value' => $region,
      );
    }
    $form['regions_post']['#markup'] = '</div>';

    // Show previews from old and new layouts
    $form['preview'] = array(
      '#type' => 'container',
      '#prefix' => '<div class="ds-layout-preview"/>',
      '#suffix' => '</div>',
    );

    $fallback_image = drupal_get_path('module', 'ds') . '/images/preview.png';
    $old_image = (isset($old_layout['image']) &&  !empty($old_layout['image'])) ? $old_layout['path'] . '/' . $old_layout['layout'] . '.png' : $fallback_image;
    if (isset($old_layout['panels']) && !empty($old_layout['panels']['icon'])) {
      $old_image = $old_layout['panels']['path'] . '/' . $old_layout['panels']['icon'];
    }
    $new_image = (isset($new_layout['image']) &&  !empty($new_layout['image'])) ? $new_layout['path'] . '/' . $new_layout_key . '.png' : $fallback_image;
    if (isset($new_layout['panels']) && !empty($new_layout['panels']['icon'])) {
      $new_image = $new_layout['panels']['path'] . '/' . $new_layout['panels']['icon'];
    }
    $arrow = drupal_get_path('module', 'ds') . '/images/arrow.png';

    $form['preview']['old_layout'] = array(
      '#markup' => '<div class="ds-layout-preview-image"><img src="' . base_path() . $old_image . '"/></div>',
    );
    $form['preview']['arrow'] = array(
      '#markup' => '<div class="ds-layout-preview-arrow"><img src="' . base_path() . $arrow . '"/></div>',
    );
    $form['preview']['new_layout'] = array(
      '#markup' => '<div class="ds-layout-preview-image"><img src="' . base_path() . $new_image . '"/></div>',
    );
    $form['#attached']['css'][] = drupal_get_path('module', 'ds') . '/css/ds.admin.css';

    // Submit button
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#prefix' => '<div class="ds-layout-change-save">',
      '#suffix' => '</div>',
    );
  }
  else {
    $form['nothing'] = array('#markup' => t('No valid configuration found.'));
  }

  return $form;
}

/**
 * Submit callback: save the layout change.
 */
function ds_field_ui_layout_change_submit($form, &$form_state) {

  // Prepare some variables.
  $old_layout = $form['#old_layout'];
  $new_layout = $form['#new_layout'];
  $new_layout_key = $form['#new_layout_key'];
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Create new record.
  $record = new stdClass();
  $record->id = $form['#export_id'];
  $record->entity_type = $entity_type;
  $record->bundle = $bundle;
  $record->view_mode = $view_mode;
  $record->layout = $new_layout_key;
  $record->settings = $old_layout['settings'];
  unset($record->settings['regions']);
  unset($record->settings['fields']);

  // map old regions to new ones
  foreach ($old_layout['regions'] as $region => $region_title) {
    $new_region = $form_state['values']['ds_' . $region];
    if ($new_region != '' && isset($old_layout['settings']['regions'][$region])) {
      foreach ($old_layout['settings']['regions'][$region] as $field_key => $field) {
        if (!isset($record->settings['regions'][$new_region])) {
          $record->settings['regions'][$new_region] = array();
        }
        $record->settings['regions'][$new_region][] = $field;
        $record->settings['fields'][$field] = $new_region;
      }
    }
  }

  // Remove old record.
  db_delete('ds_layout_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Save new record.
  drupal_write_record('ds_layout_settings', $record);

  // Clear entity info cache.
  cache_clear_all('entity_info', 'cache', TRUE);

  // Show message.
  drupal_set_message(t('The layout change has been saved.'));
}

/**
 * Save the layout settings from the 'Manage display' screen.
 */
function ds_field_ui_layouts_save($form, &$form_state) {
  $weight = 0;

  // Get default values.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Determine layout variables.
  $layout = $form_state['values']['additional_settings']['layout'];
  $old_layout = $form_state['values']['additional_settings']['old_layout'];
  $new_layout = ($layout != $old_layout) || empty($old_layout);

  // Save layout and add regions if necessary.
  $record = new stdClass;
  $record->id = $form['#export_id'];
  $record->entity_type = $entity_type;
  $record->bundle = $bundle;
  $record->view_mode = $view_mode;
  $record->layout = $layout;
  $record->settings = array();

  $form_state['layout_saved'] = FALSE;

  // Remove old layout if necessary.
  if ($new_layout && !empty($old_layout)) {
    db_delete('ds_layout_settings')
      ->condition('entity_type', $entity_type)
      ->condition('bundle', $bundle)
      ->condition('view_mode', $view_mode)
      ->execute();
  }

  if ($new_layout && !empty($layout)) {

    $form_state['layout_saved'] = TRUE;

    // Save new layout.
    $record->settings = $record->settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    // Move current visible fields into a default region, so
    // we keep their current settings.
    $layouts = ds_get_layout_info();
    $sl = $layouts[$layout];
    $first_region = key($sl['regions']);
    $record->settings['regions'] = array();
    $record->settings['fields'] = array();
    $record->settings['classes'] = array();
    $record->settings['wrappers'] = array();
    $record->settings['layout_wrapper'] = 'div';
    $record->settings['layout_attributes'] = '';
    $record->settings['layout_attributes_merge'] = variable_get('ds_layout_attributes_merge', TRUE);
    $record->settings['layout_link_attribute'] = FALSE;
    $record->settings['layout_link_custom'] = '';
    $fields = _ds_sort_fields($form_state['values']['fields'], 'weight');
    foreach ($fields as $field_key => $field) {

      // Ignore new fieldgroup, new field or existing field.
      if (in_array($field_key, array('_add_new_field', '_add_existing_field', '_add_new_group'))) {
        continue;
      }

      // Can either be form or display.
      if ((isset($field['type']) && $field['type'] != 'hidden') || $record->view_mode == 'form') {
        $record->settings['regions'][$first_region][$weight++] = $field_key;
        $record->settings['fields'][$field_key] = $first_region;
      }
    }
    // In case this is the full node view mode and if the comment module
    // is enabled for this content type, add it as well.
    if ($record->entity_type == 'node' && $record->view_mode == 'full' && module_exists('comment')) {
      $record->settings['regions'][$first_region][] = 'comments';
      $record->settings['fields']['comments'] = $first_region;
    }

    // Save the record.
    drupal_write_record('ds_layout_settings', $record);
  }
  // Update existing layout.
  elseif (!empty($layout)) {

    $form_state['layout_saved'] = TRUE;

    $fields = _ds_sort_fields($form_state['values']['fields'], 'weight');

    foreach ($fields as $key => $field) {

      // Make sure we need to save anything for this field.
      if (_ds_field_valid($key, $field, $form_state, $view_mode)) {
        continue;
      }

      if (!isset($record->settings['regions'][$field['region']])) {
        $record->settings['regions'][$field['region']] = array();
      }
      $record->settings['regions'][$field['region']][$weight++] = $key;
      $record->settings['fields'][$key] = $field['region'];

      // Save limit.
      $limit = isset($field['format']['limit']) ? trim($field['format']['limit']) : '';
      if (is_numeric($limit) || $limit === 'delta') {
        $record->settings['limit'][$key] = $limit;
      }
    }

    // Save the region classes.
    $record->settings['classes'] = array();
    foreach (array_keys($form['fields']['#regions']) as $region) {

      // Ignore hidden region.
      if ($region == 'hidden') {
        continue;
      }

      if (isset($form_state['values']['additional_settings']['layout_class'])) {
        $record->settings['classes']['layout_class'] = $form_state['values']['additional_settings']['layout_class'];
      }

      // Additional classes on regions.
      if (isset($form_state['values']['additional_settings'][$region])) {
        // Do not save empty string.
        $classes = is_array($form_state['values']['additional_settings'][$region]) ? implode(' ', $form_state['values']['additional_settings'][$region]) : array();
        if (!empty($classes)) {
          $record->settings['classes'][$region] = $form_state['values']['additional_settings'][$region];
        }
      }

      // Additional wrappers on regions.
      if (isset($form_state['values']['additional_settings']['region_wrapper'][$region])) {
        $record->settings['wrappers'][$region] = $form_state['values']['additional_settings']['region_wrapper'][$region];
      }
    }

    // Layout wrapper
    $record->settings['layout_wrapper'] = $form_state['values']['additional_settings']['region_wrapper']['layout_wrapper'];
    $record->settings['layout_attributes'] = filter_xss_admin($form_state['values']['additional_settings']['region_wrapper']['layout_attributes']);
    $record->settings['layout_attributes_merge'] = $form_state['values']['additional_settings']['region_wrapper']['layout_attributes_merge'];

    // Link attribute.
    $record->settings['layout_link_attribute'] = $form_state['values']['additional_settings']['region_wrapper']['layout_link_attribute'];
    $record->settings['layout_link_custom'] = $form_state['values']['additional_settings']['region_wrapper']['layout_link_custom'];

    // Additional settings
    if (isset($form_state['values']['additional_settings']['preview']['info']['settings']['disable_css'])) {
      $record->settings['layout_disable_css'] = $form_state['values']['additional_settings']['preview']['info']['settings']['disable_css'];
    }
    else {
      $record->settings['layout_disable_css'] = FALSE;
    }

    $record->settings = $record->settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    $l = $form['#ds_layout'];
    if ($l->export_type == 2) {
      drupal_write_record('ds_layout_settings', $record);
    }
    else {
      drupal_write_record('ds_layout_settings', $record, array('id'));
    }

    // Clear entity info cache.
    cache_clear_all('entity_info', 'cache', TRUE);
  }
}

/**
 * Form validation handler for _ds_field_ui_fields().
 */
function ds_field_ui_fields_validate($form, &$form_state) {
  foreach (element_children($form['fields']) as $key) {
    if (isset($form_state['values']['fields'][$key]['settings_edit_form'])) {
      $settings = isset($form_state['values']['fields'][$key]['settings_edit_form']['settings']['ft']) ? $form_state['values']['fields'][$key]['settings_edit_form']['settings']['ft'] : array();
      if (!empty($settings)) {
        $merge = isset($form_state['formatter_settings'][$key]['ft']) ? $form_state['formatter_settings'][$key]['ft'] : array();
        $form_state['formatter_settings'][$key]['ft'] = array_merge($merge, $settings);
      }
    }
  }
}

/**
 * Save the field settings from the 'Manage display' screen.
 */
function ds_field_ui_fields_save($form, &$form_state) {
  // Setup some variables.
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Delete previous field configuration configuration.
  db_delete('ds_field_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  if (empty($form_state['layout_saved'])) {
    return;
  }

  $field_settings = array();

  // Save settings for each field.
  $fields = $form['#ds_fields'];
  foreach ($fields as $key => $field) {

    // Field settings.
    $field_values = $form_state['values']['fields'][$field];

    // In case the region is hidden, do not save.
    if (isset($field_values['region']) && $field_values['region'] == 'hidden') {
      continue;
    }

    // Build settings.
    $settings = array();
    $settings['weight'] = $field_values['weight'];
    $settings['label'] = $field_values['label'];
    $settings['format'] = $field_values['format']['type'];

    // Any formatter settings.
    if (isset($form_state['formatter_settings'][$field])) {
      $settings['formatter_settings'] = $form_state['formatter_settings'][$field];
    }

    $field_settings[$field] = $settings;
  }

  // Allow other modules to modify the field settings before they get saved.
  drupal_alter('ds_field_settings', $field_settings, $form, $form_state);

  // Save the record.
  if (!empty($field_settings)) {
    $record = new stdClass;
    $record->id = $form['#export_id'];
    $record->entity_type = $entity_type;
    $record->bundle = $bundle;
    $record->view_mode = $view_mode;
    $record->settings = $field_settings;
    drupal_write_record('ds_field_settings', $record);
  }

  // Clear the ds_fields cache.
  cache_clear_all('ds_fields:', 'cache', TRUE);
  cache_clear_all('ds_field_settings', 'cache');
}

/**
 * Clone a fields layout.
 */
function ds_field_ui_layout_clone($form, &$form_state) {

  $clone = $form_state['values']['additional_settings']['clone'];
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  ctools_include('export');
  $layout = ctools_export_crud_load('ds_layout_settings', $clone);

  // Delete previous layout settings configuration.
  db_delete('ds_layout_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Delete previous field configuration configuration.
  db_delete('ds_field_settings')
    ->condition('entity_type', $entity_type)
    ->condition('bundle', $bundle)
    ->condition('view_mode', $view_mode)
    ->execute();

  // Save new layout record for ds.
  if ($layout) {
    $record = new stdClass();
    $record->id = $form['#export_id'];
    $record->entity_type = $entity_type;
    $record->bundle = $bundle;
    $record->view_mode = $view_mode;
    $record->layout = $layout->layout;
    $record->settings = $layout->settings;

    // Let other modules alter the layout settings.
    drupal_alter('ds_layout_settings', $record, $form_state);

    // Save layout record.
    drupal_write_record('ds_layout_settings', $record);

    // Copy the view mode settings.
    list($ce, $cb, $cv) = explode('|', $clone);
    _ds_field_ui_clone_view_mode_settings($entity_type, $bundle, $view_mode, $cv);

    // Clear entity info cache.
    cache_clear_all('entity_info', 'cache', TRUE);

    // Show message.
    drupal_set_message(t('The layout has been cloned.'));

  }
  else {
    drupal_set_message(t('No layout was cloned.'));
  }
}

/**
 * Populates display settings for a new view mode from the another view mode.
 *
 * This is almost a straight copy from Field UI, but with the addition
 * that we can pass the view mode from which we want to clone from.
 */
function _ds_field_ui_clone_view_mode_settings($entity_type, $bundle, $view_mode, $copy_view_mode) {

  $settings = field_bundle_settings($entity_type, $bundle);

  // Update display settings for field instances.
  $instances = field_read_instances(array('entity_type' => $entity_type, 'bundle' => $bundle));
  foreach ($instances as $instance) {
    // If this field instance has display settings defined for this view mode,
    // respect those settings.
    if (isset($instance['display'][$copy_view_mode])) {
      $instance['display'][$view_mode] = $instance['display'][$copy_view_mode];
      field_update_instance($instance);
    }
  }

  // Update display settings for 'extra fields'.
  foreach (array_keys($settings['extra_fields']['display']) as $name) {
    if (isset($settings['extra_fields']['display'][$name][$copy_view_mode])) {
      $settings['extra_fields']['display'][$name][$view_mode] = $settings['extra_fields']['display'][$name][$copy_view_mode];
    }
  }

  // Save the settings.
  field_bundle_settings($entity_type, $bundle, $settings);
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function ds_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {

  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  // Taxonomy view modes.
  if ($display['type'] === 'ds_taxonomy_view_mode') {
    $options = array();
    $view_modes = ds_entity_view_modes('taxonomy_term');
    foreach ($view_modes as $key => $info) {
      $options[$key] = $info['label'];
    }
    $element['taxonomy_term_reference_view_mode'] = array(
      '#title'   => t('View mode'),
      '#type'    => 'select',
      '#options' => $options,
      '#default_value' => $settings['taxonomy_term_reference_view_mode'],
    );
    $element['use_content_language'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use current content language'),
      '#default_value' => $settings['use_content_language'],
    );
    return $element;
  }

  // Taxonomy separated.
  if ($display['type'] === 'ds_taxonomy_separator' || $display['type'] == 'ds_taxonomy_separator_localized') {
    $element['taxonomy_term_link'] = array(
      '#title' => t('Link to term'),
      '#type' => 'checkbox',
      '#size' => 10,
      '#default_value' => $settings['taxonomy_term_link'],
    );
    $separators = array(
      ' ' => t('space'),
      ', ' => t('comma'),
      ' - ' => t('dash'),
      ' / ' => t('slash'),
    );
    drupal_alter('ds_taxonomy_term_separators', $separators);
    $element['taxonomy_term_separator'] = array(
      '#title' => t('Separator'),
      '#type' => 'select',
      '#options' => $separators,
      '#default_value' => $settings['taxonomy_term_separator'],
      '#states' => array(
        'visible' => array(
          'select[name="fields[field_tags][settings_edit_form][settings][taxonomy_term_list]"]' => array('value' => 'separated_list'),
        ),
      ),
    );
    return $element;
  }
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function ds_field_formatter_settings_summary($field, $instance, $view_mode) {
  $summary = '';
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  if ($display['type'] === 'ds_taxonomy_view_mode') {
    $entity_info = entity_get_info('taxonomy_term');
    $modes = $entity_info['view modes'];
    $mode = $modes[$settings['taxonomy_term_reference_view_mode']]['label'];
    $summary .= t('View mode: %mode', array('%mode' => $mode)) . '<br />';;
    $summary .= !empty($settings['use_content_language']) ? t('Use current content language') : t('Use field language');
  }

  if ($display['type'] === 'ds_taxonomy_separator' || $display['type'] == 'ds_taxonomy_separator_localized') {
    $separators = array(
      ' ' => t('space'),
      ', ' => t('comma'),
      ' - ' => t('dash'),
      ' / ' => t('slash'),
    );
    drupal_alter('ds_taxonomy_term_separators', $separators);
    $summary .= t('Separated by !sep', array('!sep' => $separators[$settings['taxonomy_term_separator']]));
    $summary .= $settings['taxonomy_term_link'] ? ', ' . t('linked') : ', ' . t('not linked');
  }

  return $summary;
}

/**
 * Creates a summary for the field format configuration summary.
 *
 * @param $field
 *   The configuration of the field.
 *
 * @return $summary
 *   An markup array.
 */
function ds_field_settings_summary($field, $form_state, $form, $view_mode) {

  $summary = '';

  // Not all fields have settings.
  if (isset($field['properties']['settings'])) {
    $summary = module_invoke($field['module'], 'ds_field_format_summary', $field);
  }

  if (module_exists('ds_extras') && variable_get('ds_extras_field_template', FALSE)) {
    module_load_include('inc', 'ds_extras', 'includes/ds_extras.admin');

    // Field template summary
    if (!in_array($field['field_type'], array(DS_FIELD_TYPE_IGNORE, DS_FIELD_TYPE_PREPROCESS))) {
      $functions = module_invoke_all('ds_field_theme_functions_info');
      $default_field_function = variable_get('ft-default', 'theme_field');
      $field_function = isset($form_state['formatter_settings'][$field['name']]['ft']['func']) ? $form_state['formatter_settings'][$field['name']]['ft']['func'] : $default_field_function;

      $summary .= 'Field template: ' . check_plain($functions[$field_function]) . '<br />';
    }
  }

  if (!empty($form_state['complete form'])) {
    $formatter_name = $form_state['complete form']['fields'][$field['name']]['format']['type']['#value'];
  }
  else {
    $formatter_name = $form['fields'][$field['name']]['format']['type']['#default_value'];
  }

  // Allow other modules to alter the formatter summary.
  $context = array(
    'formatter' => $formatter_name,
    'field' => $field,
    'instance' => array(
      'display' => array(
        $view_mode => array(
          'label' => '',
          'type' => '',
          'weight' => '',
          'settings' => isset($field['formatter_settings']) ? $field['formatter_settings'] : array(),
          'module' => '',
        )
      )
    ),
    'view_mode' => $view_mode,
    'ds' => TRUE,
  );
  drupal_alter('field_formatter_settings_summary', $summary, $context);

  if (empty($summary)) {
    return NULL; // no summary return nothing
  }

  return array(
    '#markup' => '<div class="field-formatter-summary">' . $summary . '</div>',
    '#cell_attributes' => array('class' => array('field-formatter-summary-cell')),
  );
}

/**
 * Creates a form for Display Suite fields.
 * .
 * @param $field
 *   The field definition.
 *
 * @return $form
 *   A form definition.
 */
function ds_field_settings_form($field, &$form_state, $entity_form, $view_mode) {
  $form = module_invoke($field['module'], 'ds_field_settings_form', $field);

  // Add field template settings to every field if enabled.
  if (module_exists('ds_extras') && variable_get('ds_extras_field_template', FALSE)) {
    $context = array(
      'instance' => array(
        'entity_type' => $field['entity_type'],
        'bundle' => $field['bundle'],
        'field_name' => $field['name'],
      ),
      'view_mode' => $field['view_mode'],
    );

    // Load the formatter settings form
    module_load_include('inc', 'ds_extras', 'includes/ds_extras.admin');
    // Protect against empty $form.
    if (!is_array($form)) $form = array();
    if (!in_array($field['field_type'], array(DS_FIELD_TYPE_IGNORE, DS_FIELD_TYPE_PREPROCESS))) {
      ds_extras_field_template_settings_form($form, $form_state, $context);
    }
    else {
      $form['#markup'] = t('This field does not support Field templates.');
    }
  }

  $formatter_name = $form_state['complete form']['fields'][$field['name']]['format']['type']['#value'];

  // Allow other modules to alter the formatter settings form.
  $context = array(
    'ds' => TRUE,
    'formatter' => $formatter_name,
    'field' => $field,
    'instance' => array(
      'label' => $field['title'],
      'bundle' => $field['bundle'],
      'entity_type' => $field['entity_type'],
      'display' => array(
        'default' => array(
          'settings' => isset($field['formatter_settings']) ? $field['formatter_settings'] : array(),
        ),
      ),
    ),
    'view_mode' => $view_mode,
    'form' => $entity_form,
    'form_state' => $form_state,
  );
  drupal_alter('field_formatter_settings_form', $form, $context);

  return $form;
}

/**
 * Implements hook_ds_field_format_summary().
 */
function ds_ds_field_format_summary($field) {
  $summary = '';
  $settings = isset($field['formatter_settings']) ? $field['formatter_settings'] : $field['properties']['default'];
  $functions = module_invoke_all('ds_field_theme_functions_info');
  foreach ($settings as $key => $value) {

    // Ignore Field Formatter conditions.
    if ($key == 'conditions') {
      continue;
    }

    if ($key == 'ctools') {
      $conf = unserialize($value);
      $summary .= t('Type: !type', array('!type' => check_plain(drupal_ucfirst(str_replace('_', ' ', $conf['subtype'])))));
    }
    elseif ($key == 'ft' || is_array($value)) {
      // Do nothing
    }
    elseif (!empty($value)) {
      $value = is_numeric($value) ? ($value ? t('Yes') : t('No')) : check_plain($value);
      $summary .= ' ' . str_replace('_', ' ', drupal_ucfirst(check_plain($key))) . ': ' . check_plain($value) . '<br />';
    }
  }

  if (empty($summary) && ($field['field_type'] == DS_FIELD_TYPE_CTOOLS)) {
    $summary .= t('Not configured yet.') . '<br />';
  }

  return $summary;
}

/**
 * Implements hook_ds_field_settings_form().
 */
function ds_ds_field_settings_form($field) {
  $form = array();

  $settings = !empty($field['formatter_settings']) ? $field['formatter_settings'] : (!empty($field['properties']['default']) ? $field['properties']['default'] : array());

  if (empty($field['properties']['settings'])) {
    return $form;
  }

  foreach ($field['properties']['settings'] as $key => $value) {

    switch ($value['type']) {

      case 'textfield':
        $form[$key] = array(
          '#type' => 'textfield',
          '#title' => str_replace('_', ' ', check_plain(drupal_ucfirst($key))),
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#size' => 40,
          '#description' => isset($value['description']) ? check_plain($value['description']) : '',
        );
        break;

      case 'select':
        $form[$key] = array(
          '#type' => 'select',
          '#title' => check_plain(drupal_ucfirst($key)),
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#options' => $value['options'],
          '#description' => isset($value['description']) ? check_plain($value['description']) : '',
        );
        break;

      case 'checkbox':
        $form[$key] = array(
          '#type' => 'checkbox',
          '#title' => str_replace('_', ' ', check_plain(drupal_ucfirst($key))),
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#description' => isset($value['description']) ? check_plain($value['description']) : '',
        );
        break;

      case 'ctools':
        ctools_include('modal');
        ctools_include('object-cache');
        ctools_modal_add_js();
        $form[$key] = array(
          '#type' => 'hidden',
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#weight' => 2,
        );
        $action = 'add';
        $args = '';
        $conf = array();
        $query = array('query' => array('selection' => 1));
        $title = t('Select content');
        if (isset($settings[$key])) {
          $query = array();
          $ctools = unserialize($settings['ctools']);
          $type = $ctools['type'];
          $subtype = $ctools['subtype'];
          $args = '/' . $type . '/' . $subtype;
          $action = 'edit';
          $conf = $ctools['conf'];
          $title = t('Edit content');
        }
        $form['select'] = array(
          '#markup' => '<div class="select-content-link">' . l($title, 'admin/structure/ds/fields/manage_ctools/content/' . $action . '/' . $field['entity_type'] . '/' . $field['name'] . $args, array('attributes' => array('class' => array('ctools-use-modal'))) + $query) . '</div>',
          '#weight' => -10,
        );
        $form['load_terms'] = array(
          '#type' => 'checkbox',
          '#title' => t('Load terms'),
          '#description' => t('Toggle if you are embedding a view with term fields.'),
          '#default_value' => isset($settings['load_terms']) ? $settings['load_terms'] : '',
          '#weight' => -1,
        );
        $form['show_title']['#weight'] = 0;
        $form['title_wrapper']['#weight'] = 1;
        ctools_object_cache_set($field['name'], $field['name'], $conf);
        break;
    }
  }

  return $form;
}

/**
 * Add entity contexts.
 */
function ds_get_entity_context($entity_type) {
  ctools_include('context');
  $arguments = array(
    array(
      'keyword' => $entity_type,
      'identifier' => drupal_ucfirst($entity_type) . ' being viewed',
      'id' => 1,
      'name' => 'entity_id:' . $entity_type,
      'settings' => array(),
    ),
  );

  return ctools_context_get_placeholders_from_argument($arguments);
}

/**
 * Return the configuration settings for the CTools field.
 */
function ds_ctools_content($action = 'add', $entity_type = '', $field_name = '', $type_name = '', $subtype_name = '', $step = NULL) {

  ctools_include('modal');
  ctools_include('ajax');
  ctools_include('content');
  ctools_include('object-cache');

  $commands = array();
  $content_type = ctools_get_content_type($type_name);
  $subtype = ctools_content_get_subtype($content_type, $subtype_name);

  if ($data = ctools_object_cache_get($field_name, $field_name)) {
    $conf = $data;
  }
  else {
    $conf = ctools_content_get_defaults($content_type, $subtype);
  }

  $url = 'admin/structure/ds/fields/manage_ctools/content/' . $action . '/' . $entity_type . '/' . $field_name;
  $base_url = $url;
  if (!empty($type_name) && !empty($subtype_name)) {
    $url .= '/' . $type_name . '/' . $subtype_name . '/%step';
  }
  $form_info = array(
    'path' => $url,
    'show cancel' => TRUE,
    'next callback' => 'ds_ctools_content_next',
  );

  // Get entity context.
  $contexts = ds_get_entity_context($entity_type);

  $form_state = array(
    'contexts' => $contexts,
    'ajax' => TRUE,
    'modal' => TRUE,
    'modal return' => TRUE,
    'field_name' => $field_name,
  );

  // Call the content form.
  $output = ctools_content_form($action, $form_info, $form_state, $content_type, $subtype_name, $subtype, $conf, $step);

  if (!empty($form_state['complete']) || isset($_GET['dismiss'])) {
    $configuration = array(
      'conf' => $form_state['conf'],
      'type' => $type_name,
      'subtype' => $subtype_name,
    );
    $commands[] = ctools_modal_command_dismiss();
    $commands[] = ajax_command_invoke('input[name="fields[' . $field_name . '][settings_edit_form][settings][ctools]"]', 'dsCtoolsContentConfiguration', array(serialize($configuration)));
    $commands[] = ajax_command_invoke('.select-content-link', 'dsCtoolsContentUpdate', array(serialize($configuration)));
    ctools_object_cache_clear($field_name, $field_name);
  }
  // Content selection
  elseif (!empty($form_state['cancel']) || isset($_GET['selection'])) {
    ctools_object_cache_clear($field_name, $field_name);
    $commands[] = ds_ctools_content_select($contexts, $field_name, $action, $entity_type);
  }
  // No configuration anymore.
  elseif ($output === FALSE && !isset($_GET['dismiss'])) {
    $output = t('No further configuration exists for this content type.<br/><br/><a href="!close_modal" class="use-ajax">Click here to close the modal and save the settings.</a><br/><br/><a href="!new_content" class="use-ajax">Click here to select new content</a>.', array('!new_content' => url($base_url, array('query' => array('selection' => TRUE))), '!close_modal' => url($url, array('query' => array('dismiss' => 1)))));
    $commands[] = ctools_modal_command_display(t('Edit content'), $output);
  }
  // Form render.
  else {
    $commands = ctools_modal_form_render($form_state, $output);
  }

  print ajax_render($commands);
  ajax_footer();
  exit;
}

/**
 * Handle the 'next' click on the add/edit field form wizard.
 */
function ds_ctools_content_next(&$form_state) {
  ctools_object_cache_set($form_state['field_name'], $form_state['field_name'], $form_state['conf']);
}

/**
 * Select content.
 *
 * @param $contexts
 *   A collection of contexts, usually the entity.
 * @param $field_name
 *   The name of the field.
 * @param $action
 *   The name of the action.
 * @param $entity_type
 *   The name of the entity type.
 */
function ds_ctools_content_select($contexts, $field_name, $action, $entity_type) {

  // Get content types.
  $content_types = ctools_content_get_available_types($contexts);

  $categories = $category_names = $ordered = array();

  foreach ($content_types as $type_name => $subtypes) {
    foreach ($subtypes as $subtype_name => $content_type) {
      list($category_key, $category) = ds_ctools_get_category($content_type);

      if (empty($categories[$category_key])) {
        $categories[$category_key] = array(
          'title' => $category,
          'content' => array(),
        );
        $category_names[$category_key] = $category;
      }

      $content_title = filter_xss_admin($content_type['title']);

      // Ensure content with the same title doesn't overwrite each other.
      while (isset($categories[$category_key]['content'][$content_title])) {
        $content_title .= '-';
      }

      $categories[$category_key]['content'][$content_title] = $content_type;
      $categories[$category_key]['content'][$content_title]['type_name'] = $type_name;
      $categories[$category_key]['content'][$content_title]['subtype_name'] = $subtype_name;
    }
  }

  // Now sort
  natcasesort($category_names);
  foreach ($category_names as $category => $name) {
    $ordered[$category] = $categories[$category];
  }

  $left = '';
  $right = '<div class="content">' . t('Content options are divided by category. Please select a category from the left to proceed.') . '</div>';
  foreach ($ordered as $section => $section_content) {
    // Section.
    if ($section == 'root') {
      $section_content['title'] = t('Content');
    }
    $left .= '<div class="section"><a href="" id="' . $section . '" class="section-link">' . $section_content['title'] . '</a></div>';
    // Content.
    $right .= '<div id="' . $section . '-container" class="selection-hide content">';
    $right .= '<h2>' . $section_content['title'] . '</h2>';
    foreach ($section_content['content'] as $key => $value) {
      $right .= '<div class="content-item">';
      $variables = array(
        'path' => ctools_content_admin_icon($value),
      );
      $right .= theme('image', $variables) . '&nbsp;';
      $right .= ctools_ajax_text_button($key, 'admin/structure/ds/fields/manage_ctools/content/' . $action . '/' . $entity_type . '/' . $field_name . '/' . $value['type_name'] . '/' . $value['subtype_name'], $key);
      $right .= '</div>';
    }
    $right .= '</div>';
  }

  // Create output.
  $output = '<div id="ctools-content-selection">';
  $output .= '<div id="ds-left">' . $left . '</div>';
  $output .= '<div id="ds-right">' . $right . '</div>';
  $output .= '</div>';

  return ctools_modal_command_display(t('Select content'), $output);
}

/**
 * Helper function to get the category.
 */
function ds_ctools_get_category($content_type) {
  if (isset($content_type['top level'])) {
    $category = 'root';
  }
  elseif (isset($content_type['category'])) {
    if (is_array($content_type['category'])) {
      list($category, $weight) = $content_type['category'];
    }
    else {
      $category = $content_type['category'];
    }
  }
  else {
    $category = t('Uncategorized');
  }

  return array(preg_replace('/[^a-z0-9]/', '-', drupal_strtolower($category)), $category);
}

/**
 * Add fake field group value in.
 */
function _ds_field_group_field_ui_fix_notices($form, &$form_state) {
  $field_group = array(
    'group_name' => '',
    'label' => '',
  );
  $form_state['values']['fields']['_add_new_group'] = $field_group;
}

/**
 * Add the layouts fieldset on the Field UI screen.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 */
function _ds_field_ui_table_layouts($entity_type, $bundle, $view_mode, &$form, $form_state) {

  $layout_options = array();
  $ds_layouts = ds_get_layout_info();
  $layout_options = array('' => t('- None -'));
  foreach ($ds_layouts as $key => $layout) {
    $optgroup = 'Display Suite';

    // Panels can not be used on Views fields and forms.
    if (!empty($layout['module']) && $layout['module'] == 'panels' && isset($form_state['no_panels'])) {
      continue;
    }

    // Create new layout option group.
    if (!empty($layout['module'])) {
      $optgroup = drupal_ucfirst($layout['module']);
    }

    if (!isset($layout_options[$optgroup])) {
      $layout_options[$optgroup] = array();
    }

    // Stack the layout.
    $layout_options[$optgroup][$key] = $layout['label'];
  }

  // If there is only one $optgroup, move it to the root.
  if (count($layout_options) == 2) {
    $options = $layout_options[$optgroup];
    $layout_options = array_merge(array('' => t('- None -')), $options);
  }

  // Add layouts form.
  $form['additional_settings']['ds_layouts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout for !bundle in !view_mode', array('!bundle' => str_replace('_', ' ', $bundle), '!view_mode' => str_replace('_', ' ', $view_mode))),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#parents' => array('additional_settings'),
    '#weight' => -100,
  );

  ctools_include('export');
  $layout = new stdClass();
  $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
  if (isset($ds_layout_settings[$form['#export_id']])) {
    $layout = $ds_layout_settings[$form['#export_id']];
  }

  if (!empty($layout) && isset($layout->layout) && isset($ds_layouts[$layout->layout]) && empty($layout->disabled)) {
    $layout->settings = $layout->settings;
    $layout->regions = $ds_layouts[$layout->layout]['regions'];
    $form['#ds_layout'] = $layout;
  }


  // The layout is defined in code.
  if (isset($layout->export_type)) {
    // Enabled/disable the layout.
    if (empty($layout->disabled)) {
      $link = t('This layout is defined in code') . ': ' . l(t('disable layout.'), 'admin/structure/ds/disable/' . $form['#export_id'], array('query' => drupal_get_destination()));
    }
    else {
      $link = t('A layout is defined in code but has been disabled') . ': ' . l(t('enable layout.'), 'admin/structure/ds/enable/' . $form['#export_id'], array('query' => drupal_get_destination()));
    }
    $form['additional_settings']['ds_layouts']['enable_disable'] = array(
      '#markup' => $link,
      '#weight' => 2,
    );

    // Overridden in database.
    if ($layout->export_type == 3) {
      $form['additional_settings']['ds_layouts']['revert'] = array(
        '#markup' => l(t('This layout is overridden. Click to revert to default settings.'), 'admin/structure/ds/revert-layout/' . $form['#export_id'], array('query' => drupal_get_destination())),
        '#weight' => 1,
      );
    }
  }

  // Load the layout preview form
  $layout->layout_options = $layout_options;
  _ds_field_ui_table_layouts_preview($form, $form_state, $ds_layouts, $layout, $entity_type, $bundle, $view_mode);

  if (!empty($layout) && isset($layout->regions)) {

    // Add wrappers
    $wrapper_options = array(
      'div' => 'Div',
      'span' => 'Span',
      'section' => 'Section',
      'article' => 'Article',
      'header' => 'Header',
      'footer' => 'Footer',
      'aside' => 'Aside',
      'figure' => 'Figure'
    );
    $form['additional_settings']['region_wrapper'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom wrappers'),
      '#description' => t('Choose a wrapper. All Display Suite layouts support this option.')
    );

    // Hide the fieldset in case of the reset layout.
    if ($layout->layout === 'ds_reset') {
      $form['additional_settings']['region_wrapper']['#access'] = FALSE;
    }

    foreach (array_keys($layout->regions) as $region) {
      $form['additional_settings']['region_wrapper'][$region] = array(
        '#type' => 'select',
        '#options' => $wrapper_options,
        '#title' => t('Wrapper for @region', array('@region' => $layout->regions[$region])),
        '#default_value' => isset($layout->settings['wrappers'], $layout->settings['wrappers'][$region]) ? $layout->settings['wrappers'][$region] : 'div',
      );
    }

    $form['additional_settings']['region_wrapper']['layout_wrapper'] = array(
      '#type' => 'select',
      '#options' => $wrapper_options,
      '#title' => t('Layout wrapper'),
      '#default_value' => isset($layout->settings['layout_wrapper']) ? $layout->settings['layout_wrapper'] : 'div',
      '#weight' => 10,
    );

    $form['additional_settings']['region_wrapper']['layout_attributes'] = array(
      '#type' => 'textfield',
      '#title' => t('Layout attributes'),
      '#description' => 'E.g. role="navigation"',
      '#default_value' => isset($layout->settings['layout_attributes']) ? $layout->settings['layout_attributes'] : '',
      '#weight' => 11,
    );
    $form['additional_settings']['region_wrapper']['layout_attributes_merge'] = array(
      '#type' => 'checkbox',
      '#title' => t('Merge other layout attributes'),
      '#description' => 'Certain modules might provide additional attributes for the template wrapper, e.g. RDFa. Disable this option if you prefer to specify these attributes above.',
      '#default_value' => isset($layout->settings['layout_attributes_merge']) ? $layout->settings['layout_attributes_merge'] : variable_get('ds_layout_attributes_merge', TRUE),
      '#weight' => 12,
    );

    $form['additional_settings']['region_wrapper']['layout_link_attribute'] = array(
      '#type' => 'select',
      '#options' => array(
        '' => t('No link'),
        'content' => t('Link to content'),
        'custom' => t('Custom'),
        'tokens' => t('Tokens')
      ),
      '#title' => t('Add link'),
      '#description' => t('This will add an onclick attribute on the layout wrapper.'),
      '#default_value' => isset($layout->settings['layout_link_attribute']) ? $layout->settings['layout_link_attribute'] : FALSE,
      '#weight' => 12,
    );

    $form['additional_settings']['region_wrapper']['layout_link_custom'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom link'),
      '#description' => t('You may use tokens for this link if you selected tokens.'),
      '#default_value' => isset($layout->settings['layout_link_custom']) ? $layout->settings['layout_link_custom'] : FALSE,
      '#weight' => 13,
      '#states' => array(
        'visible' => array(array(
          ':input[name="additional_settings[region_wrapper][layout_link_attribute]"]' => array(array("value" => "tokens"), array("value" => "custom")),
        )),
      ),
    );

    if (module_exists('token')) {
      $form['additional_settings']['region_wrapper']['tokens'] = array(
        '#title' => t('Tokens'),
        '#type' => 'container',
        '#weight' => 14,
        '#states' => array(
          'visible' => array(
            ':input[name="additional_settings[region_wrapper][layout_link_attribute]"]' => array("value" => "tokens"),
          ),
        ),
      );
      $form['additional_settings']['region_wrapper']['tokens']['help'] = array(
        '#theme' => 'token_tree',
        '#token_types' => 'all',
        '#global_types' => FALSE,
        '#dialog' => TRUE,
      );
    }



    // Add extra classes for the regions to have more control while theming.
    $form['additional_settings']['ds_classes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom classes'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#parents' => array('additional_settings'),
      '#access' => empty($chosen_layout['flexible']),
    );

    $classes_access = (user_access('admin_classes') && module_exists('ds_ui'));
    $classes = _ds_classes();
    if (!empty($classes)) {

      $form['additional_settings']['ds_classes']['layout_class'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => $classes,
        '#title' => t('Class for layout'),
        '#default_value' => isset($layout->settings['classes']['layout_class']) ? $layout->settings['classes']['layout_class'] : '',
      );

      foreach (array_keys($layout->regions) as $region) {
        $form['additional_settings']['ds_classes'][$region] = array(
          '#type' => 'select',
          '#multiple' => TRUE,
          '#options' => $classes,
          '#title' => t('Class for @region', array('@region' => $region)),
          '#default_value' => isset($layout->settings['classes'][$region]) ? $layout->settings['classes'][$region] : '',
        );
      }
      if ($classes_access) {
        $form['additional_settings']['ds_classes']['info'] = array('#markup' => l(t('Manage region  and field CSS classes'), 'admin/structure/ds/classes', array('query' => drupal_get_destination())));
      }
      elseif (user_access('admin_classes')) {
        $form['additional_settings']['ds_classes']['info'] = array('#markup' => l(t('To manage region and field CSS classes, the Display Suite UI module should be enabled.'), 'admin/modules', array('query' => drupal_get_destination(), 'fragment' => 'edit-modules-display-suite')));
      }
    }
    else {
      if ($classes_access) {
        $form['additional_settings']['ds_classes']['info'] = array('#markup' => '<p>' . t('You have not defined any CSS classes which can be used on regions.') . '</p><p>' . l(t('Manage region and field CSS classes'), 'admin/structure/ds/classes', array('query' => drupal_get_destination())) . '</p>');
      }
      else {
        $form['additional_settings']['ds_classes']['#access'] = FALSE;
      }
    }
  }
  else {

    if ($view_mode != 'form') {
      // See if we can clone from another view mode.
      $options = array();
      $ds_layout_settings = ctools_export_crud_load_all('ds_layout_settings');
      foreach ($ds_layout_settings as $row) {
        // Do not clone from form layouts.
        if ($row->view_mode == 'form') {
          continue;
        }
        if ($row->entity_type == $entity_type && $row->bundle == $bundle) {
          $name = drupal_ucfirst(str_replace('_', ' ', $row->entity_type)) . ' > ' . drupal_ucfirst(str_replace('_', ' ', $row->bundle)) . ' > ' . drupal_ucfirst(str_replace('_', ' ', $row->view_mode));
          if (!empty($row->disabled)) {
            $name .= ' ' . t('(disabled)');
          }
          $options[$row->id] = $name;
        }
      }

      if (!empty($options)) {

        // Clone from another layout.
        $form['additional_settings']['ds_clone'] = array(
          '#type' => 'fieldset',
          '#title' => t('Clone layout'),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#parents' => array('additional_settings'),
        );
        $form['additional_settings']['ds_clone']['clone'] = array(
          '#title' => t('Select an existing layout to clone.'),
          '#type' => 'select',
          '#options' => $options,
          '#weight' => 20,
        );
        $form['additional_settings']['ds_clone']['clone_submit'] = array(
          '#type' => 'submit',
          '#value' => t('Clone layout'),
          '#submit' => array('ds_field_ui_layout_clone'),
          '#weight' => 21,
        );
      }
    }
  }

  $form['additional_settings']['ds_layouts']['id'] = array(
    '#type' => 'value',
    '#value' => isset($layout->id) ? $layout->id : $form['#export_id'],
  );

  $form['additional_settings']['ds_layouts']['old_layout'] = array(
    '#type' => 'value',
    '#value' => isset($layout->layout) ? $layout->layout : 0,
  );

  // Add validate and submit handlers. Layout needs be first so
  // we can reset the type key for Field API fields.
  $form['#validate'][] = 'ds_field_ui_layouts_validate';
  $submit = $form['#submit'];
  $form['#submit'] = array('ds_field_ui_layouts_save');
  $form['#submit'] = array_merge($form['#submit'], $submit);
}

/**
 * Add the layout previews to the Field UI screen.
 *
 * @param $form
 *   A collection of form properties.
 * @param $form_state
 *   The state of the form
 * @param $ds_layouts
 *   Collection of all the layouts
 * @param $layout
 *   Current selected layout
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 */
function _ds_field_ui_table_layouts_preview(&$form, &$form_state, $ds_layouts, $layout, $entity_type, $bundle, $view_mode) {
  $layout_string = '';

  $form['additional_settings']['ds_layouts']['layout'] = array(
    '#type' => 'select',
    '#title' => t('Select a layout'),
    '#options' => $layout->layout_options,
    '#default_value' => isset($layout->layout) && empty($layout->disabled) ? $layout->layout : '',
    '#prefix' => '<div class="ds-select-layout">',
    '#suffix' => '</div>',
    '#weight' => -1,
    '#ajax' => array(
      'callback' => 'ds_field_ui_table_layouts_preview_callback',
      'wrapper' => 'ds_layout_wrapper',
    ),
  );
  if (!isset($layout->layout)) {
    $form['additional_settings']['ds_layouts']['layout']['#description'] = t("A layout must be selected to enable Display Suite functionality.");
  }

  $form['additional_settings']['ds_layouts']['preview'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="ds_layout_wrapper">',
    '#suffix' => '</div>',
    '#weight' => -3,
  );

  if (isset($layout->layout) || isset($form_state['values']['additional_settings']['layout'])) {
    $layout_string = isset($form_state['values']['additional_settings']['layout']) ? $form_state['values']['additional_settings']['layout'] : $layout->layout;
  }

  if (!empty($layout_string)) {
    $chosen_layout = $ds_layouts[$layout_string];

    if (empty($chosen_layout['flexible'])) {

      $selected = '<strong>' . $chosen_layout['label'] . '</strong>';
      $selected .= '<br/>' . t('The default template can be found in %path', array('%path' => $chosen_layout['path']));
      $suggestions = t('Template suggestions') . ':<ul>';
      $suggestions_array = array();

      $suggestions_array[0] = $layout_string . '--' . $entity_type;
      $suggestions_array[2] = $layout_string . '--' . $entity_type . '-' . $bundle;
      $suggestions_array[4] = $layout_string . '--' . $entity_type . '--{id}';
      if (!isset($form_state['no_view_mode_suggestions']) && $view_mode != 'default') {
        $suggestions_array[1] = $layout_string . '--' . $entity_type . '-' . $view_mode;
        $suggestions_array[3] = $layout_string . '--' . $entity_type . '-' . $bundle . '-' . $view_mode;
      }

      ksort($suggestions_array);
      $suggestions .= '<ul><li>' . implode('.tpl.php</li><li>', $suggestions_array) . '.tpl.php</li></ul>';
    }
    else {
      $suggestions = '';
      $selected = t('You have selected the flexible %layout_label layout.', array('%layout_label' => $chosen_layout['label'], '%path' => $chosen_layout['path']));
    }

    if (isset($form_state['values']['additional_settings']['layout']) || (!empty($layout) && isset($layout->regions))) {
      $fallback_image = drupal_get_path('module', 'ds') . '/images/preview.png';
      $current_layout = isset($form_state['values']['additional_settings']['layout']) && (!isset($layout->layout) || $form_state['values']['additional_settings']['layout'] != $layout->layout) ? t('Current layout (after save)') : t('Current layout');
      $image = (isset($chosen_layout['image']) && !empty($chosen_layout['image'])) ? $chosen_layout['path'] . '/' . $layout_string . '.png' : $fallback_image;
      if (isset($chosen_layout['panels']) && !empty($chosen_layout['panels']['icon'])) {
        $image = $chosen_layout['panels']['path'] . '/' . $chosen_layout['panels']['icon'];
      }

      $form['additional_settings']['ds_layouts']['preview'] ['title'] = array(
        '#markup' => '<div class="ds-layout-preview-title">' . $current_layout . '</div>',
      );
      $form['additional_settings']['ds_layouts']['preview'] ['image'] = array(
        '#markup' => '<div class="ds-layout-preview-image"><img src="' . base_path() . $image . '"/></div>',
      );
      $form['additional_settings']['ds_layouts']['preview']['info'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('ds-layout-preview-suggestion'),
        ),
      );
      $form['additional_settings']['ds_layouts']['preview']['info']['suggestions'] = array(
        '#markup' => '<p>' . $selected . '</p><p>' . t('!suggestions', array('!suggestions' => strtr($suggestions, '_', '-'))) . '</p>',
      );

      if (!empty($chosen_layout['css'])) {
        $disable_css = FALSE;
        if (isset($layout->settings['layout_disable_css'])) {
          $disable_css = $layout->settings['layout_disable_css'];
        }

        $form['additional_settings']['ds_layouts']['preview']['info']['settings']['disable_css'] = array(
          '#type' => 'checkbox',
          '#title' => t('Disable layout CSS styles'),
          '#default_value' => $disable_css,
        );
      }
    }

    if (isset($form_state['values']['additional_settings']['layout']) && (!isset($layout->layout) || $form_state['values']['additional_settings']['layout'] != $layout->layout)) {

      // Get admin path.
      $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);
      if ($view_mode != 'form') {
        $admin_path .= '/display';
      }
      else {
        $admin_path .= '/fields';
      }

      // If regions aren't set we don't have to move fields.
      if (isset($layout->regions)) {
        $url = 'admin/structure/ds/change-layout/' . $entity_type . '/' . $bundle . '/' . $view_mode . '/' . $layout_string . '?destination=' . $admin_path;
        $form['#validate'][] = 'ds_field_ui_change_layout_validate';
      }
      else {
        $url = $admin_path;
      }

      if ($view_mode != 'default' && $view_mode != 'form') {
        $url .= '/' . $view_mode;
      }

      $form['layout_changed_url'] = array(
        '#type' => 'value',
        '#value' => $url,
      );

      $form['#submit'][] = 'ds_field_ui_change_layout_submit';
    }
  }
}

/**
 * Ajax callback for _ds_field_ui_table_layouts_preview().
 */
function ds_field_ui_table_layouts_preview_callback($form, $form_state) {
  return $form['additional_settings']['ds_layouts']['preview'];
}

/**
 * Form validation handler for _ds_field_ui_table_layouts_preview().
 */
function ds_field_ui_change_layout_validate(&$form, &$form_state) {
  $key1 = array_search('ds_field_ui_layouts_save', $form['#submit']);
  $key2 = array_search('ds_field_ui_fields_save', $form['#submit']);
  unset($form['#submit'][$key1]);
  unset($form['#submit'][$key2]);
}

/**
 * Form submission handler for _ds_field_ui_table_layouts_preview().
 */
function ds_field_ui_change_layout_submit($form, &$form_state) {
  $values = $form_state['values'];
  if (isset($values['additional_settings']['preview']['info']['settings']['disable_css'])) {
    $disable_css = $values['additional_settings']['preview']['info']['settings']['disable_css'];
  }
  else {
    $disable_css = FALSE;
  }

  $record = db_select('ds_layout_settings')
    ->fields('ds_layout_settings')
    ->condition('entity_type', $values['ds_entity_type'])
    ->condition('bundle', $values['ds_bundle'])
    ->condition('view_mode', $values['ds_view_mode'])
    ->execute()
    ->fetchObject();

  $record->settings = unserialize($record->settings);
  $record->settings['layout_disable_css'] = $disable_css;

  drupal_write_record('ds_layout_settings', $record, array('id'));

  unset($_GET['destination']);
  global $base_url;
  $url = $base_url . '/' . $values['layout_changed_url'];
  $form_state['redirect'] = $url;
}

/**
 * Add the fields to the Field UI form.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 * @param $form_state
 *   A collection of form_state properties.
 */
function _ds_field_ui_fields($entity_type, $bundle, $view_mode, &$form, &$form_state) {

  // Do not add the fields if there is no layout.
  if (!isset($form['#ds_layout'])) {
    return;
  }

  // Get the fields and put them on the form.
  $fields = ds_get_fields($entity_type, FALSE);

  // Ultimate alter on Field UI fields, only used for edge cases.
  $context = array(
    'entity_type' => $entity_type,
    'bundle' => $bundle,
    'view_mode' => $view_mode,
  );
  // Load views file if entity type is not ds_views.
  // We need to cache the hook it's implementing.
  if ($entity_type != 'ds_views' && module_exists('ds_extras') && variable_get('ds_extras_vd', FALSE)) {
    module_load_include('inc', 'ds_extras', 'includes/ds_extras.vd');
  }
  drupal_alter('ds_fields_ui', $fields, $context);

  // Get field settings.
  $field_settings = ds_get_field_settings($entity_type, $bundle, $view_mode, FALSE);
  $form['#field_settings'] = $field_settings;

  $table = &$form['fields'];
  $form['#ds_fields'] = array();

  $field_label_options = array(
    'above' => t('Above'),
    'inline' => t('Inline'),
    'hidden' => t('<Hidden>'),
  );
  drupal_alter('ds_label_options', $field_label_options);

  // Regions for fields.
  $field_regions = array();
  if (isset($form['#ds_layout']->settings['fields'])) {
    $field_regions = $form['#ds_layout']->settings['fields'];
  }

  foreach ($fields as $key => $field) {

    // Check on ui_limit.
    if (!empty($field['ui_limit'])) {

      $continue = TRUE;
      foreach ($field['ui_limit'] as $limitation) {
        list($limit_bundle, $limit_view_mode) = explode('|', $limitation);
        if ($limit_bundle == '*' || $limit_bundle == $bundle) {
          if ($limit_view_mode == '*' || $limit_view_mode == $view_mode) {
            $continue = FALSE;
          }
        }
      }

      if ($continue) {
        continue;
      }
    }

    $form['#ds_fields'][] = $key;

    // Check on formatter settings.
    if (isset($form_state['formatter_settings'][$key])) {
      $field['formatter_settings'] = $form_state['formatter_settings'][$key];
    }
    elseif (isset($field_settings[$key]['formatter_settings'])) {
      $field['formatter_settings'] = $field_settings[$key]['formatter_settings'];
      $form_state['formatter_settings'][$key] = $field['formatter_settings'];
    }

    if (!isset($field_settings[$key]['ft']) && isset($field_settings[$key]['ft'])) {
      $form_state['formatter_settings'][$key]['ft'] = $field_settings[$key]['ft'];
    }

    $value = isset($form_state['formatter_settings']) ? $form_state['formatter_settings'] : array();

    $hidden = array('hidden' => t('<Hidden>'));
    $formatters = isset($field['properties']['formatters']) ? $hidden + $field['properties']['formatters'] : $hidden + array('default' => t('Default'));

    $table[$key] = array(
      '#row_type' => 'field',
      '#js_settings' => array('field'),
      '#region_callback' => 'field_ui_display_overview_row_region',
      '#attributes' => array('class' => array('draggable', 'tabledrag-leaf')),
      'human_name' => array(
        '#markup' => check_plain($field['title']),
      ),
      'weight' => array(
        '#type' => 'textfield',
        '#default_value' => isset($field_settings[$key]['weight']) ? $field_settings[$key]['weight'] : 0,
        '#size' => 3,
        '#attributes' => array('class' => array('field-weight')),
      ),
      'parent_wrapper' => array(
        'parent' => array(
          '#type' => 'select',
          '#empty_value' => '',
          '#options' => array(),
          '#attributes' => array('class' => array('field-parent')),
          '#parents' => array('fields', $key, 'parent'),
        ),
        'hidden_name' => array(
          '#type' => 'hidden',
          '#default_value' => $key,
          '#attributes' => array('class' => array('field-name')),
        ),
      ),
      'label' => array(
        '#type' => 'select',
        '#options' => $field_label_options,
        '#default_value' => isset($field_settings[$key]['label']) ? $field_settings[$key]['label'] : 'hidden',
      ),
      'format' => array(
        'type' => array(
          '#type' => 'select',
          '#options' => $formatters,
          '#default_value' => isset($field_settings[$key]['format']) ? $field_settings[$key]['format'] : 'hidden',
          '#attributes' => array('class' => array('field-formatter-type')),
        ),
      ),
      'settings_summary' => array(),
      'settings_edit' => array(),
    );

    // Don't show summary or cogwheel in hidden region.
    if (_ds_field_ui_check_hidden_region($key, $form_state, $field_regions)) {
      continue;
    }

    $field['name'] = $key;
    $field['entity_type'] = $entity_type;
    $field['bundle'] = $bundle;
    $field['view_mode'] = $view_mode;

    if ($form_state['formatter_settings_edit'] == $key) {
      $table[$key]['settings_summary']['#attributes']['colspan'] = 2;
      $settings_form = ds_field_settings_form($field, $form_state, $form, $view_mode);
      ds_field_row_form_format_construct($table, $key, $settings_form);
    }
    else {
      // After saving, the settings are updated here as well. First we create
      // the element for the table cell.
      $summary = ds_field_settings_summary($field, $form_state, $form, $view_mode);

      if (isset($summary)) {
        $table[$key]['settings_summary'] = $summary;
        ds_field_row_form_format_summary_construct($table, $key);
      }
    }
  }

  // Add fields submit handler.
  $form['#submit'][] = 'ds_field_ui_fields_save';
}

/**
 * Alter the core field on the the Field UI form.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 * @param $form_state
 *   A collection of form_state properties.
 */
function _ds_field_ui_core_fields($entity_type, $bundle, $view_mode, &$form, &$form_state) {
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];

  // Gather type information.
  $instances = field_info_instances($entity_type, $bundle);

  $field_types = field_info_field_types();
  $extra_fields = field_info_extra_fields($entity_type, $bundle, 'display');

  $table = &$form['fields'];

  // Regions for fields.
  $field_regions = array();
  if (isset($form['#ds_layout']->settings['fields'])) {
    $field_regions = $form['#ds_layout']->settings['fields'];
  }

  // Field rows.
  foreach ($instances as $key => $instance) {

    // Don't show summary or cogwheel in hidden region.
    if (_ds_field_ui_check_hidden_region($key, $form_state, $field_regions)) {
      $table[$key]['settings_summary']['#markup'] = '';
      $table[$key]['settings_edit'] = array();
      continue;
    }

    $field = field_info_field($instance['field_name']);
    $display = $instance['display'][$view_mode];

    // Check the currently selected formatter, and merge persisted values for
    // formatter settings.
    if (isset($form_state['values']['fields'][$key]['type'])) {
      $formatter_type = $form_state['values']['fields'][$key]['type'];
    }
    else {
      $formatter_type = $display['type'];
    }

    $settings = $display['settings'];
    if (isset($form_state['formatter_settings'][$key])) {
      $settings = array_merge($settings, $form_state['formatter_settings'][$key]);
    }
    $settings += field_info_formatter_settings($formatter_type);

    // Import field settings and merge with Field API settings.
    if (!isset($form_state['formatter_settings'][$key]) && !empty($form['#field_settings'][$key]['formatter_settings']['ft'])) {
      $form_state['formatter_settings'][$key] = $settings;
      $form_state['formatter_settings'][$key]['ft'] = $form['#field_settings'][$key]['formatter_settings']['ft'];
    }

    // Change default value or Field API format, so we can change the right
    // settings form when clicking on the cogwheel.
    $form['fields'][$key]['format']['type']['#default_value'] = $formatter_type;

    $instance['display'][$view_mode]['type'] = $formatter_type;
    $formatter = field_info_formatter_types($formatter_type);
    $instance['display'][$view_mode]['module'] = $formatter['module'];
    $instance['display'][$view_mode]['settings'] = $settings;

    // Base button element for the various formatter settings actions.
    $base_button = array(
      '#submit' => array(
        'field_ui_display_overview_multistep_submit',
      ),
      '#ajax' => array(
        'callback' => 'field_ui_display_overview_multistep_js',
        'wrapper' => 'field-display-overview-wrapper',
        'effect' => 'fade',
      ),
      '#field_name' => $key,
    );

    if ($form_state['formatter_settings_edit'] == $key) {
      $formatter_type = $form_state['complete form']['fields'][$key]['format']['type']['#default_value'];
      $formatter = field_info_formatter_types($formatter_type);
      $instance['display'][$view_mode]['type'] = $formatter_type;
      $instance['display'][$view_mode]['module'] = $formatter['module'];
      $instance['display'][$view_mode]['settings'] = $settings + field_info_formatter_settings($formatter_type);
      $function = $formatter['module'] . '_field_formatter_settings_form';

      // Add the default formatter settings if any.
      $settings_form = array();
      if (function_exists($function)) {
        $settings_form = $function($field, $instance, $view_mode, $form, $form_state);
      }

      // Add the field templates form when needed
      if (module_exists('ds_extras') && variable_get('ds_extras_field_template', FALSE)) {
        $context = array(
          'instance' => $instance,
          'view_mode' => $view_mode,
        );

        // Load the form
        module_load_include('inc', 'ds_extras', 'includes/ds_extras.admin');
        if (!is_array($settings_form)) $settings_form = array();
        ds_extras_field_template_settings_form($settings_form, $form_state, $context);
      }

      // Allow other modules to alter the formatter settings form.
      $context = array(
        'module' => $formatter['module'],
        'formatter' => $formatter,
        'field' => $field,
        'instance' => $instance,
        'view_mode' => $view_mode,
        'form' => $form,
        'form_state' => $form_state,
      );
      drupal_alter('field_formatter_settings_form', $settings_form, $context);

      if ($settings_form) {
        $table[$key]['format']['#cell_attributes'] = array('colspan' => 3);
        $table[$key]['format']['settings_edit_form'] = array(
          '#type' => 'container',
          '#attributes' => array('class' => array('field-formatter-settings-edit-form')),
          '#parents' => array('fields', $key, 'settings_edit_form'),
          'label' => array(
            '#markup' => t('Format settings:') . ' <span class="formatter-name">' . $formatter['label'] . '</span>',
          ),
          'settings' => $settings_form,
          'actions' => array(
            '#type' => 'actions',
            'save_settings' => $base_button + array(
              '#type' => 'submit',
              '#name' => $key . '_formatter_settings_update',
              '#value' => t('Update'),
              '#op' => 'update',
            ),
            'cancel_settings' => $base_button + array(
              '#type' => 'submit',
              '#name' => $key . '_formatter_settings_cancel',
              '#value' => t('Cancel'),
              '#op' => 'cancel',
              // Do not check errors for the 'Cancel' button, but make sure we
              // get the value of the 'formatter type' select.
              '#limit_validation_errors' => array(array('fields', $key, 'type')),
            ),
          ),
        );
        $table[$key]['#attributes']['class'][] = 'field-formatter-settings-editing';
        $table[$key]['format']['type']['#attributes']['class'] = array('element-invisible');
      }
    }
    else {
      $summary = module_invoke($formatter['module'], 'field_formatter_settings_summary', $field, $instance, $view_mode);

      // Allow other modules to alter the formatter summary.
      $context = array(
        'module' => $formatter['module'],
        'formatter' => $formatter,
        'field' => $field,
        'instance' => $instance,
        'view_mode' => $view_mode,
      );
      drupal_alter('field_formatter_settings_summary', $summary, $context);

      if (module_exists('ds_extras') && variable_get('ds_extras_field_template', FALSE)) {
        module_load_include('inc', 'ds_extras', 'includes/ds_extras.admin');

        // Field template summary
        $functions = module_invoke_all('ds_field_theme_functions_info');
        $default_field_function = variable_get('ft-default', 'theme_field');
        $field_function = isset($form_state['formatter_settings'][$key]['ft']['func']) ? $form_state['formatter_settings'][$key]['ft']['func'] : $default_field_function;

        if (!empty($summary)) {
          $summary .= '<br />';
        }
        $summary .= 'Field template: ' . check_plain($functions[$field_function]) . '<br />';
      }

      if (!empty($summary)) {
        $table[$key]['settings_summary'] = array();
        $table[$key]['settings_edit'] = array();

        $table[$key]['settings_summary'] = array(
          '#markup' => '<div class="field-formatter-summary">' . $summary . '</div>',
          '#cell_attributes' => array('class' => array('field-formatter-summary-cell')),
        );
        // Render the other part of the summary
        ds_field_row_form_format_summary_construct($table, $key);
      }
    }
  }
}

/**
 * Helper function to check if we are in a hidden region or not.
 */
function _ds_field_ui_check_hidden_region($key, $form_state, $field_regions) {
  $continue = FALSE;
  if (isset($form_state['input']['fields'][$key]['region'])) {
    if ($form_state['input']['fields'][$key]['region'] == 'hidden') {
      $continue = TRUE;
    }
  }
  elseif (!isset($field_regions[$key]) || $field_regions[$key] == 'hidden') {
    $continue = TRUE;
  }

  return $continue;
}

/**
 * Helper function for building the formatter settings.
 */
function ds_field_row_form_format_construct(&$table, $key, $settings_form) {

  $base_button = array(
    '#submit' => array(
      'field_ui_display_overview_multistep_submit',
    ),
    '#validate' => array(
      'ds_field_ui_fields_validate',
    ),
    '#ajax' => array(
      'callback' => 'field_ui_display_overview_multistep_js',
      'wrapper' => 'field-display-overview-wrapper',
      'effect' => 'fade',
    ),
    '#field_name' => $key,
  );
  $table[$key]['format']['settings_edit'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('field-formatter-settings-edit-form')),
    '#parents' => array('fields', $key, 'settings_edit_form'),
    '#weight' => -5,
    // Create a settings form where hooks can pick in.
    'settings' => $settings_form,
    'actions' => array(
      '#type' => 'actions',
      'save_settings' => $base_button + array(
        '#type' => 'submit',
        '#name' => $key . '_formatter_settings_update',
        '#value' => t('Update'),
        '#op' => 'update',
      ),
      'cancel_settings' => $base_button + array(
        '#type' => 'submit',
        '#name' => $key . '_formatter_settings_cancel',
        '#value' => t('Cancel'),
        '#op' => 'cancel',
        // Do not check errors for the 'Cancel' button.
        '#limit_validation_errors' => array(),
      ),
    ),
  );
  $table[$key]['#attributes']['class'][] = 'field-formatter-settings-editing';
  $table[$key]['format']['type']['#attributes']['class'] = array('element-invisible');
}

/**
 * Helper function for formatter summary settings.
 */
function ds_field_row_form_format_summary_construct(&$table, $key) {

  $base_button = array(
    '#submit' => array('field_ui_display_overview_multistep_submit'),
    '#ajax' => array(
      'callback' => 'field_ui_display_overview_multistep_js',
      'wrapper' => 'field-display-overview-wrapper',
      'effect' => 'fade',
    ),
    '#field_name' => $key,
  );

  // Add the configure button.
  $table[$key]['settings_edit'] = $base_button + array(
    '#type' => 'image_button',
    '#name' => $key . '_formatter_settings_edit',
    '#src' => 'misc/configure.png',
    '#attributes' => array('class' => array('field-formatter-settings-edit'), 'alt' => t('Edit')),
    '#op' => 'edit',
    // Do not check errors for the 'Edit' button.
    '#limit_validation_errors' => array(),
    '#prefix' => '<div class="field-formatter-settings-edit-wrapper">',
    '#suffix' => '</div>',
  );
}

/**
 * Add tab for adding new fields on the fly.
 *
 * @param $entity_type
 *   The name of the entity type.
 * @param $bundle
 *   The name of the bundle
 * @param $view_mode
 *   The name of the view_mode
 * @param $form
 *   A collection of form properties.
 * @param $form_state
 *   A collection of form_state properties.
 */
function _ds_field_ui_custom_fields($entity_type, $bundle, $view_mode, &$form, $form_state) {

  $form['additional_settings']['add_custom_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom fields'),
    '#description' => t('Click on one of the buttons to create a new field.') . '<p></p>',
    '#access' => user_access('admin_fields'),
  );

  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();

  $field_types = array(
    'custom_field' => t('Add a code field'),
    'manage_ctools' => t('Add a dynamic field'),
  );
  $field_types['manage_block'] = t('Add a block field');
  $field_types['manage_preprocess'] = t('Add a preprocess field');

  foreach ($field_types as $field_key => $field_title) {

    $form['ctools_add_field_' . $field_key . '_url'] = array(
      '#type' => 'hidden',
      '#attributes' => array('class' => array('ctools_add_field_' . $field_key . '-url')),
      '#value' => url('admin/structure/ds/nojs/add_field/' . $field_key),
    );

    $form['additional_settings']['add_custom_fields']['ctools_add_field_' . $field_key] = array(
      '#type' => 'button',
      '#value' => $field_title,
      '#attributes' => array('class' => array('ctools-use-modal')),
      '#id' => 'ctools_add_field_' . $field_key,
    );
  }
  $form['additional_settings']['add_custom_fields']['manage_fields'] = array(
    '#type' => 'link',
    '#title' => 'Manage fields',
    '#href' => 'admin/structure/ds/fields',
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );
}

/**
 * Utility function to check if we need to save anything for this field.
 */
function _ds_field_valid($key, $field, &$form_state, $view_mode = 'default') {
  $continue = FALSE;

  // Ignore the Field group module and the region to block plugin.
  if ($key == '_add_new_group' || $key == '_add_new_field' || $key == '_add_new_block_region') {
    $continue = TRUE;
  }

  // If the field is in hidden region, do not save. Check if the
  // field has a type key which means it's from Field API and
  // we need to reset that type to 'hidden' so it doesn't get
  // fired by Field API in the frontend.
  if (isset($field['region']) && $field['region'] == 'hidden') {
    if (isset($field['type']) && $view_mode != 'form') {
      $form_state['values']['fields'][$key]['type'] = 'hidden';
    }

    // In case of a form, fields will be set with #access to FALSE.
    if ($view_mode != 'form') {
      $continue = TRUE;
    }
  }

  return $continue;
}

/**
 * Utility function to return CSS classes.
 */
function _ds_classes($name = 'ds_classes_regions') {
  static $classes = array();

  if (!isset($classes[$name])) {
    $classes[$name] = array();
    $custom_classes = trim(variable_get($name, ''));
    if (!empty($custom_classes)) {
      $classes[$name][''] = t('None');
      $custom_classes = explode("\n", $custom_classes);
      foreach ($custom_classes as $key => $value) {
        $classes_splitted = explode("|", $value);
        $key = trim($classes_splitted[0]);
        $friendly_name = isset($classes_splitted[1]) ? trim($classes_splitted[1]) : $key;
        $classes[$name][check_plain($key)] = $friendly_name;
      }
    }
    $name_clone = $name; // Prevent the name from being changed.
    drupal_alter('ds_classes', $classes[$name], $name_clone);
  }

  return $classes[$name];
}

/**
 * Utility function to sort a multidimensional array by a value in a sub-array.
 *
 * @param $a
 *   The array to sort.
 * @param $subkey
 *   The subkey to sort by.
 */
function _ds_sort_fields($a, $subkey) {
  foreach ($a as $k => $v) {
    if (isset($v[$subkey])) {
      $b[$k] = $v[$subkey];
    }
  }
  asort($b);
  foreach ($b as $key => $val) {
    $c[$key] = $a[$key];
  }
  return $c;
}
