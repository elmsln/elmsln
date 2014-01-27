<?php

/**
 * @file
 * Main administration page for default config.
 */

/**
 * Main administration page callback.
 */
function defaultconfig_admin() {
  $components = defaultconfig_get_components();
  $page = array();
  $page['tables'] = array(
    '#type' => 'vertical_tabs',
  );
  foreach ($components as $hook => $component) {
    $table = defaultconfig_component_table($component);
    if ($table) {
      $page['tables'][] = array(
        '#title' => $component['label'],
        '#type' => 'fieldset',
        'table' => defaultconfig_component_table($component),
      );
    }
  }
  return $page;
}

/**
 * Render a a table with all modules having components of a particular type.
 */
function defaultconfig_component_table($component) {
  $modules = defaultconfig_modules($component);
  if (count($modules)) {
    $data = array();
    // @todo fetch more information about the modules. For now, let's just
    // use the machine name.
    foreach ($modules as $module) {
      $data[] = array(
        $module,
        l(t('rebuild'), 'admin/structure/defaultconfig/rebuild/' . $module . '/' . $component['name']),
      );
    }
    return array(
      '#theme' => 'table',
      '#header' => array(t('Module'), t('Operations')),
      '#rows' => $data
    );
  }
  return FALSE;
}


/**
 * Rebuild confirmation form.
 */
function defaultconfig_component_rebuild_form($form, &$form_state, $module, $name) {
  $components = defaultconfig_get_components();
  if (!module_exists($module) || !isset($components[$name])) {
    drupal_not_found();
    return '';
  }
  $component = $components[$name];
  $form_state['component'] = $component;
  $form_state['module'] = $module;
  return confirm_form(
    $form,
    t('Are you sure you want to rebuild the defaults in %module for %component?',
      array('%module' => $module, '%component' => $component['label'])),
    'admin/structure/defaultconfig',
    t('Any changes you have made might be undone.')
  );
}

function defaultconfig_component_rebuild_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/defaultconfig';
  defaultconfig_component_rebuild($form_state['component'], $form_state['module']);
  drupal_set_message(t('The component %component in %module has been rebuilt.',
    array('%module' => $form_state['module'], '%component' => $form_state['component']['label'])));
}

function defaultconfig_optional_admin($form, &$form_state) {
  $form = array();
  $form_state['optional_settings'] = $optional_settings = defaultconfig_get_optionals();
  $optionals = defaultconfig_optional_info();
  $show_submit = FALSE;
  $form['components'] = array(
    '#tree' => TRUE,
  );
  foreach ($optionals as $type => $type_optionals) {
    $form['components'][$type] = array(
      '#tree' => TRUE,
    );
    foreach ($type_optionals as $optional => $info) {
      $optional_name = $type . ':' . $optional;
      if ($info['applicable']) {
        $show_submit = TRUE;
        $form['components'][$type][$optional] = array(
          '#type' => 'checkbox',
          '#title' => $info['title'],
          '#default_value' => isset($optional_settings[$optional_name]) ?
          $optional_settings[$optional_name]->status : $info['default'],
          '#description' => $info['description'],
        );
      }
    }
  }
  if ($show_submit) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save settings'),
    );
  }
  else {
    $form['description'] = array(
      '#markup' => t('No extensions were provided by any of the enabled modules.'),
    );
  }
  return $form;
}

function defaultconfig_optional_admin_submit($form, &$form_state) {
  $components = defaultconfig_get_components();
  $enabled_optionals = array();
  defaultconfig_include();
  foreach ($form_state['values']['components'] as $type => $optionals) {
    $optional_values = array();
    if (isset($components[$type])) {
      defaultconfig_component_include($components[$type]);
      $defaults = module_invoke_all($components[$type]['hook']);
      $selected_defaults = array();
      $not_selected = array();
      foreach ($optionals as $name => $status) {
        if (!empty($defaults[$name]) && $status) {
          $selected_defaults[$name] = $defaults[$name];
        }
        else {
          $not_selected[$name] = $defaults[$name];
        }
        $optional_values[$name] = $status;
      }
      // Save enabled stuff.
      $components[$type]['rebuild callback']($components[$type], $selected_defaults);
      // Disable the rest.
      if (isset($components[$type]['disable callback'])) {
        $components[$type]['disable callback']($components[$type], $not_selected);
      }
      foreach ($optional_values as $name => $optional_status) {
        $name = $type . ':' . $name;
        if (isset($form_state['optional_settings'][$name])) {
          $optional = $form_state['optional_settings'][$name];
        }
        else {
          $optional = new stdClass;
          $optional->export_type = 0;
        }
        $enabled_optionals[] = $name;
        $optional->name = $name;
        $optional->status = $optional_status;
        ctools_export_crud_save('defaultconfig_optionals', $optional);
      }
    }
  }
}

function theme_defaultconfig_optional_admin(&$variables) {
  $form = &$variables['form'];
  $rows = array();
  $output = '';
  foreach (element_children($form['components']) as $component) {
    foreach (element_children($form['components'][$component]) as $ext_name) {
      $extension = &$form['components'][$component][$ext_name];
      $item = array(
        '#type' => 'item',
        '#title' => $extension['#title'],
        '#description' => $extension['#description'],
      );
      $title = $extension['#title'];
      $description = $extension['#description'];
      unset($extension['#title'], $extension['#description']);
      $rows[] = array(drupal_render($item), drupal_render($extension));
    }
  }
  if (count($rows)) {
    $header = array(t('Extension'), t('Enabled'));
    $output = theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id' => 'entity_collection-table'),
    ));
  }
  $output .= drupal_render_children($form);
  return $output;
}
