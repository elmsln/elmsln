<?php
/**
 * @file
 * Functions only needed on configuration pages.
 */

/**
 * Implements hook_theme().
 */
function _fences_theme($existing, $type, $theme, $path) {
  $hooks = array();

  $fences = fences_get_fences_suggestion_info();

  $supported_hooks = array('field');
  foreach ($supported_hooks as $hook) {
    foreach ($fences[$hook] as $suggestion => $data) {
      // Manually register the suggestions for a module, but let hook_theme
      // auto-discover theme-owned suggestions as it normally does.
      if ($fences[$hook][$suggestion]['type'] == 'module') {
        $hook_suggestion = $hook . '__fences_' . str_replace('-', '_', $suggestion);
        $hook_suggestions = array($hook_suggestion);
        // Register the "-multiple" suggestion if that template was found.
        if ($fences[$hook][$suggestion]['multiple']) {
          $hook_suggestions[] = $hook_suggestion . '_multiple';
        }
        foreach ($hook_suggestions as $name) {
          $hooks[$name] = array(
            'base hook'      => $hook,
            'render element' => $existing[$hook]['render element'],
            'type'           => $fences[$hook][$suggestion]['type'],
            'theme path'     => $existing[$hook]['theme path'],
            'template'       => str_replace('_', '-', $name),
            'path'           => $fences[$hook][$suggestion]['path'],
          );
        }
      }
    }
  }

  // Register theme hook suggestions for field_collection's entity.
  if (module_exists('entity')) {
    $hooks['entity__fences_no_wrapper'] = array(
      'base hook'      => 'entity',
      'render element' => $existing['entity']['render element'],
      'type'           => 'module',
      'theme path'     => $existing['entity']['theme path'],
      'function'       => 'theme_entity__fences_no_wrapper',
    );
  }

  return $hooks;
}

/**
 * Implements hook_theme_registry_alter().
 */
function _fences_theme_registry_alter(&$theme_registry) {
  $fences = fences_get_fences_suggestion_info();

  // Manually registering module-based suggestions means they mistakenly get
  // preprocess and process functions registered to them.
  $supported_hooks = array('field');
  foreach ($supported_hooks as $hook) {
    foreach ($fences[$hook] as $suggestion => $data) {
      if ($fences[$hook][$suggestion]['type'] == 'module') {
        $hook_suggestion = $hook . '__fences_' . str_replace('-', '_', $suggestion);
        foreach (array($hook_suggestion, $hook_suggestion . '_multiple') as $name) {
          unset($theme_registry[$name]['preprocess functions']);
          unset($theme_registry[$name]['process functions']);
        }
      }
    }
  }
}

/**
 * Helper function for fences_get_fences_suggestion_info().
 */
function _fences_get_fences_suggestion_info(&$fences) {
  $fences = $files = array();

  // Call hook_fences_suggestion_info for modules. We need to search each
  // module for template files to get their paths, so we can't use
  // module_invoke_all().
  foreach (module_implements('fences_suggestion_info') as $module) {
    $function = $module . '_fences_suggestion_info';
    if (function_exists($function)) {
      $result = $function();
      if (isset($result) && is_array($result)) {
        // Search the module for template files.
        $files[$module] = drupal_system_listing('/\-\-fences\-.*\.tpl\.php$/', drupal_get_path('module', $module), 'name', 0);
        // Go through each of the results of hook_fences_suggestion_info().
        foreach (array_keys($result) as $hook) {
          foreach (array_keys($result[$hook]) as $suggestion) {
            $template = str_replace('_', '-', $hook . '--fences-' . $suggestion) . '.tpl';
            // Only record the suggestion if a corresponding template file is found.
            if (isset($files[$module][$template])) {
              $fences[$hook][$suggestion] = $result[$hook][$suggestion];
              // We need the path and project type for hook_theme().
              $fences[$hook][$suggestion]['path'] = dirname($files[$module][$template]->uri);
              $fences[$hook][$suggestion]['type'] = 'module';
              // Record if there is a "multiple-" version of the template.
              $template = str_replace('_', '-', $hook . '--fences-' . $suggestion . '-multiple') . '.tpl';
              $fences[$hook][$suggestion]['multiple'] = isset($files[$module][$template]) ? TRUE : FALSE;
            }
          }
        }
      }
    }
  }

  // Create a list of the default theme and its base themes.
  $theme_default = $GLOBALS['conf']['theme_default'];
  // We can't use list_themes() here because of #761608.
  $theme_data = _system_rebuild_theme_data();
  if (isset($theme_data[$theme_default]->base_themes)) {
    foreach (array_keys($theme_data[$theme_default]->base_themes) as $base_theme) {
      $themes[$base_theme] = 'base_theme_engine';
    }
  }
  $themes[$theme_default] = 'theme_engine';
  // Include the template.php files of the entire theme stack.
  foreach (array_keys($themes) as $theme) {
    $file = './' . drupal_get_path('theme', $theme) . '/template.php';
    if (file_exists($file)) {
      include_once $file;
    }
  }

  // Call hook_fences_suggestion_info for themes.
  foreach ($themes as $theme => $type) {
    // Search the theme for template files.
    $files[$theme] = drupal_system_listing('/\-\-fences\-.*\.tpl\.php$/', drupal_get_path('theme', $theme), 'name', 0);
    $function = $theme . '_fences_suggestion_info';
    if (function_exists($function)) {
      $result = $function();
      if (isset($result) && is_array($result)) {
        // Go through each of the results of hook_fences_suggestion_info().
        foreach (array_keys($result) as $hook) {
          foreach (array_keys($result[$hook]) as $suggestion) {
            $template = str_replace('_', '-', $hook . '--fences-' . $suggestion) . '.tpl';
            // Only record the suggestion if a corresponding template file is found.
            if (isset($files[$theme][$template])) {
              $fences[$hook][$suggestion] = $result[$hook][$suggestion];
              // We need the project type in hook_theme().
              $fences[$hook][$suggestion]['type'] = $type;
            }
          }
        }
      }
    }
    // If hook_fences_suggestion_info() doesn't exist for the theme, do a
    // "lazy" hook implementation by parsing the file names of matching
    // template files.
    else {
      foreach ($files[$theme] as $template => $data) {
        list($hook, $suggestion) = explode('--', $template);
        $suggestion = str_replace(array('fences-', '-multiple', '.tpl'), '', $suggestion);
        if (!isset($fences[$hook][$suggestion])) {
          $fences[$hook][$suggestion] = array(
            'label'       => $suggestion,
            'element'     => $suggestion,
            'description' => t('A <@tag> tag', array('@tag' => $suggestion)),
            'groups'      => array(t('Provided by @theme_name', array('@theme_name', $theme))),
            'type'        => $type,
          );
        }
      }
    }
  }

  // Allow modules and themes to alter the fences info.
  drupal_alter('fences_suggestion_info', $fences);

  foreach (array_keys($fences) as $hook) {
    ksort($fences[$hook]);
  }
}

/**
 * Helper function for fences_get_fences_options().
 */
function _fences_get_fences_options($theme_hook) {
  $options = array();

  // Get the list of suggestions.
  $fences = fences_get_fences_suggestion_info();
  foreach (array_keys($fences[$theme_hook]) as $key) {
    $tags = '';
    if ($fences[$theme_hook][$key]['element'] && $fences[$theme_hook][$key]['element'] != $fences[$theme_hook][$key]['label']) {
      $tags = ' — <' . implode('> <', explode(' ', $fences[$theme_hook][$key]['element'])) . '>';
    }
    $option = $fences[$theme_hook][$key]['label'] . $tags . ' — ' . $fences[$theme_hook][$key]['description'];
    if (empty($fences[$theme_hook][$key]['groups'])) {
      $options[$key] = $option;
    }
    else {
      foreach ($fences[$theme_hook][$key]['groups'] as $optgroup) {
        $options[$optgroup][$key] = $option;
      }
    }
  }

  // Sort the option groups, but put the "no markup" option first.
  ksort($options);
  if ($no_wrapper = $options['no_wrapper']) {
    unset($options['no_wrapper']);
    $options = array('no_wrapper' => $no_wrapper) + $options;
  }

  return $options;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function _fences_form_field_ui_field_edit_form_alter(&$form, &$form_state) {
  $suggestion = fences_get_suggestion($form['#instance']['entity_type'], $form['#instance']['bundle'], $form['#instance']['field_name']);

  $form['instance']['fences_wrapper'] = array(
    '#type' => 'select',
    '#title' => t('Wrapper markup'),
    '#default_value' => $suggestion ? $suggestion : 'div',
    '#options' => fences_get_fences_options('field'),
    '#description' => t('Choose the HTML to use to wrap the field.'),
  );
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function _fences_form_views_ui_add_item_form_alter(&$form, &$form_state) {
  // Add our own submit handler to run before the standard one.
  array_unshift($form['buttons']['submit']['#submit'], 'fences_views_ui_add_item_form_submit');
}

/**
 * Helper function for submit handler fences_views_ui_add_item_form_submit().
 */
function _fences_views_ui_add_item_form_submit($form, &$form_state) {
  // Sanity check; this temporary property shouldn't exist before the form is
  // submitted.
  if (isset($form_state['view']->fences_new_fields)) {
    unset($form_state['view']->fences_new_fields);
  }
  // Loop through each of the items that were checked.
  if (!empty($form_state['values']['name']) && is_array($form_state['values']['name'])) {
    foreach (array_keys(array_filter($form_state['values']['name'])) as $field) {
      // Check if the checked item is a field api field.
      if (strpos($field, 'field_data_') === 0) {
        // Find the field's proper name.
        list($table, $field_name) = explode('.', $field, 2);
        if ($cut = strpos($field_name, '$')) {
          $field_name = substr($field_name, 0, $cut);
        }
        // Note that the field has just been added by adding it's name to a
        // temporary property of the view.
        $form_state['view']->fences_new_fields[] = $field_name;
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Alter the views field item form to change some of the default values. Note:
 * we only act on an item if it is among the list of fields added to the view's
 * fences_new_fields property in _fences_views_ui_add_item_form_submit().
 */
function _fences_form_views_ui_config_item_form_alter(&$form, &$form_state) {
  // Check if the current item is a field.
  if ($form_state['type'] == 'field' && isset($form_state['view']->fences_new_fields)) {
    if (!empty($form_state['view']->fences_new_fields)) {
      // Check if the current item is one of the fields we marked earlier.
      $key = array_search($form_state['id'], $form_state['view']->fences_new_fields);
      if ($key !== FALSE) {
        // Disable the label option.
        $form['options']['custom_label']['#default_value'] = FALSE;

        // Since we are altering this fieldset's defaults, expand it.
        $form['options']['style_settings']['#collapsed'] = FALSE;

        // Enable the element_type style to be none.
        $form['options']['element_type_enable']['#default_value'] = TRUE;
        $form['options']['element_type']['#default_value'] = 0;

        // Enable the element_wrapper style to be none.
        $form['options']['element_wrapper_type_enable']['#default_value'] = TRUE;
        $form['options']['element_wrapper_type']['#default_value'] = 0;

        // Disable the default element classes.
        $form['options']['element_default_classes']['#default_value'] = FALSE;

        // Set the field settings to use the field_api for rendering.
        $form['options']['field_api_classes']['#default_value'] = TRUE;

        // Remove this field from the list of items to alter.
        unset($form_state['view']->fences_new_fields[$key]);
      }
    }
    // Remove the temporary property set when we added items.
    if (empty($form_state['view']->fences_new_fields)) {
      unset($form_state['view']->fences_new_fields);
    }
  }
}

/**
 * Menu callback: admin settings form.
 *
 * @return
 *   The settings form used by Menu block.
 */
function fences_admin_settings_form($form, &$form_state) {
  $form['fences_default_markup'] = array(
    '#type' => 'radios',
    '#title' => t('Default “div” markup for unconfigured fields'),
    '#default_value' => variable_get('fences_default_markup', 0),
    '#options' => array(
      0 => t('Use the default wrapper markup from Drupal (nested <code>div</code>s).'),
      1 => t('Override the default wrapper markup with Fences’ lean markup (single <code>div</code> wrapper).'),
    ),
    '#description' => t('Drupal’s default field markup will be used by any field that has <em>not</em> been configured while Fences is enabled. Use this option to override the default markup for all unconfigured fields.'),
  );

  $form['fences_default_classes'] = array(
    '#type' => 'radios',
    '#title' => t('Default classes'),
    '#default_value' => variable_get('fences_default_classes', 0),
    '#options' => array(
      0 => t('Use Drupal’s default classes (<code>field</code>, <code>field-name-field-NAME</code>, <code>field-type-TYPE</code>, <code>field-label-LABELTYPE</code>, <code>clearfix</code>, <code>field-item</code>, <code>odd</code>, <code>even</code>).'),
      1 => t('Override the default classes with Fences’ single <code>field-NAME</code> class.'),
    ),
    '#description' => t('Drupal’s default classes are verbose and most are useless, but some themes may require them.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Form submission handler.
 */
function fences_admin_settings_form_submit($form, &$form_state) {
  if ($form_state['values']['fences_default_markup']) {
    variable_set('fences_default_markup', 1);
  }
  else {
    variable_del('fences_default_markup');
  }

  if ($form_state['values']['fences_default_classes']) {
    variable_set('fences_default_classes', 1);
  }
  else {
    variable_del('fences_default_classes');
  }

  drupal_set_message(t('The configuration options have been saved.'));
}
