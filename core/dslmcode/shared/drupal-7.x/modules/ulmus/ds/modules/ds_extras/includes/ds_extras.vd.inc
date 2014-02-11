<?php

/**
 * @file
 * Views displays functions.
 */

/**
 * Show the overview form and the selection list.
 */
function ds_extras_vd_overview() {

  $entity_info = entity_get_info('ds_views');
  $build = $rows = array();

  ctools_include('export');
  $vd_settings = ctools_export_crud_load_all('ds_vd');

  if ($entity_info) {
    foreach ($entity_info['bundles'] as $key => $value) {

      // If no initial bundles were created, entity API will create
      // one by default, so make sure we do not list that one.
      if ($key == 'ds_views') {
        continue;
      }

      $row = array();
      $row[] = $value['label'];
      $operations = l(t('Manage layout'), 'admin/structure/ds/vd/manage/' . $key . '/display');

      if (isset($vd_settings[$key]) && $vd_settings[$key]->export_type == 1) {
        $operations .= ' - ' . l(t('Remove'), 'admin/structure/ds/vd/manage/' . $key . '/remove');
      }
      $row[] = $operations;

      $rows[$key] = $row;
    }
  }

  if (empty($rows)) {
    $rows = array(
      array(array('data' => t('No views selected.'), 'colspan' => '2')),
    );
  }

  $variables = array(
    'header' => array(t('Title'), t('Operations')),
    'rows' => $rows,
  );
  $build['list'] = array('#markup' => theme('table', $variables));
  $build['form'] = drupal_get_form('ds_extras_vd_bundle_form', $rows);

  return $build;
}

/**
 * Return the views select form to create a bundle.
 */
function ds_extras_vd_bundle_form($form, $form_state, $rows) {

  $options = array();
  $views = views_get_all_views();
  foreach ($views as $view_key => $view) {

    // Ignore disabled views.
    if (isset($view->disabled) && $view->disabled) {
      continue;
    }

    $get_view = views_get_view($view->name);

    // Loop through all displays.
    foreach ($view->display as $display_key => $display) {
      // Ignore default displays.
      if ($display_key == 'default') {
        continue;
      }

      $key = $view_key . '-' . $display_key;
      $name = drupal_ucfirst($view->name) . ': ' . $display->display_title;
      if (!isset($rows[$key])) {
        $options[$key] = $name . ' (Views template)';
      }
      $get_view->set_display($display_key);
      if ($get_view->display_handler->uses_fields() && !isset($rows[$key . '-fields'])) {
        $options[$key . '-fields'] = $name . ' (Fields)';
      }
    }
  }

  $form['vd'] = array(
    '#title' => t('Select view'),
    '#description' => t('Select a View that you want to manage with Display Suite. If a View uses fields you can also select that view to select a layout and position the fields. Note that html for the label and field are limited.'),
    '#type' => 'select',
    '#options' => $options,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );

  return $form;
}

/**
 * Submit callback: save the new bundle.
 */
function ds_extras_vd_bundle_form_submit($form, &$form_state) {

  // Save new bundle.
  $record = new stdClass();
  $record->vd = $form_state['values']['vd'];
  $record->label = $form['vd']['#options'][$record->vd];
  drupal_write_record('ds_vd', $record);

  // Clear entity cache and field info fields cache.
  cache_clear_all('field_info_fields', 'cache_field');
  cache_clear_all('entity_info', 'cache', TRUE);

  // Message and redirect.
  drupal_set_message(t('Bundle @label has been added.', array('@label' => $record->label)));
  $form_state['redirect'] = 'admin/structure/ds/vd';
}

/**
 * Edit the display or remove a views display.
 *
 * @param $bundle
 *   The name of the bundle
 * @param $action
 *   The action to take (edit or remove)
 */
function ds_extras_vd_manage($bundle = '', $action = '') {
  $entity_info = entity_get_info('ds_views');

  if (!empty($bundle) && isset($entity_info['bundles'][$bundle]) && $action == 'remove') {
    return drupal_get_form('ds_extras_vd_bundle_remove', $bundle, $entity_info['bundles'][$bundle]['label']);
  }

  if (!empty($bundle) && isset($entity_info['bundles'][$bundle]) && $action == 'display') {
    return ds_extras_vd_field_ui($bundle);
  }

  // Redirect to overview.
  drupal_set_message(t('No view found to layout.'));
  drupal_goto('admin/structure/ds/vd');
}

/**
 * Return Field UI display screen for a view and bundle.
 *
 * @param $bundle
 *   The name of the bundle
 */
function ds_extras_vd_field_ui($bundle) {

  global $conf;

  // Use drupal_build_form instead of drupal_get_form.
  $form_state = array();
  $arguments = array('ds_views', $bundle, 'default');
  $form_state['build_info']['args'] = $arguments;
  $form_state['no_view_mode_suggestions'] = TRUE;
  $form_state['no_panels'] = TRUE;
  form_load_include($form_state, 'inc', 'field_ui', 'field_ui.admin');
  form_load_include($form_state, 'inc', 'ds_extras', 'includes/ds_extras.vd');

  // Deny access to field_group if it exists.
  if (module_exists('field_group')) {
    $form_state['no_field_group'] = TRUE;
  }

  // Build form.
  $build = drupal_build_form('field_ui_display_overview_form', $form_state);

  // Deny access to view modes.
  $build['additional_settings']['modes']['#access'] = FALSE;

  // Deny access to disabling blocks and regions.
  $build['additional_settings']['ds_layouts']['hide_sidebars']['#access'] = FALSE;

  // Deny access to fields table if there's no layout.
  if (!ds_get_layout('ds_views', $bundle, 'default')) {
    $build['fields']['#access'] = FALSE;
  }

  // Add additional validate function so we can remove notices.
  if (module_exists('field_group')) {
    array_unshift($build['#validate'], 'ds_vd_field_ui_fix_notices');
  }

  return $build;
}

/**
 * Implements hook_ds_fields_ui_alter().
 */
function ds_extras_ds_fields_ui_alter(&$fields, $context) {

  // Check on the $bundle string to see if the key 2 exists. If it exists,
  // we'll call the view to put the fields of this view on and remove
  // the fields which comes default by ds_extras_field_extra_fields()
  // and only work for the views template.
  $bundle = $context['bundle'];
  $fields_check = explode('-', $bundle);

  if (isset($fields_check[2])) {

    $field_copy = array(
      'title' => 'dummy',
      'field_type' => DS_FIELD_TYPE_IGNORE,
    );

    // Remove the view template fields.
    $remove_fields = ds_extras_ds_fields_info('ds_views');
    foreach ($remove_fields['ds_views'] as $key => $properties) {
      unset($fields[$key]);
    }

    // Get the view and its fields.
    $view = views_get_view($fields_check[0]);
    $view->set_display($fields_check[1]);
    $fields = $view->display_handler->get_field_labels();
    foreach ($fields as $field_key => $field_label) {
      $field_properties = $field_copy;
      $field_properties['title'] = $field_label;
      $fields[$field_key] = $field_properties;
    }
  }
}

/**
 * Return confirm form to remove a views bundle
 */
function ds_extras_vd_bundle_remove($form, $form_state, $bundle, $label) {
  $form['#bundle'] = $bundle;
  $form['#label'] = $label;
  return confirm_form($form, t('Are you sure you want to remove bundle @label ?', array('@label' => $label)), 'admin/structure/ds/vd');
}

/**
 * Submit callback: remove a views bundle
 */
function ds_extras_vd_bundle_remove_submit($form, &$form_state) {

  $bundle = $form['#bundle'];
  $label = $form['#label'];

  // Remove bundle.
  db_delete('ds_vd')
    ->condition('vd', $bundle)
    ->execute();

  // Remove layout.
  db_delete('ds_layout_settings')
    ->condition('bundle', $bundle)
    ->execute();

  // Remove settings.
  db_delete('ds_field_settings')
    ->condition('bundle', $bundle)
    ->execute();

  // Remove from bundle settings.
  variable_del('field_bundle_settings_ds_views__' . $bundle);

  // Clear entity cache and field info fields cache.
  cache_clear_all('field_info_fields', 'cache_field');
  cache_clear_all('entity_info', 'cache', TRUE);

  drupal_set_message(t('Bundle @label has been removed.', array('@label' => $label)));
}
