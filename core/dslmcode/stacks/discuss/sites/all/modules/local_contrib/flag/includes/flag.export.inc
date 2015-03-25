<?php

/**
 * @file
 * Import/Export functionality provided by Flag module.
 */

/**
 * Export a flag to code.
 *
 * @param $flags
 *   An array of flag objects, or flag name.
 * @param $module
 *   Optional. The name of the module that will be created if exporting to use
 *   in hook_flag_default_flags().
 */
function flag_export_flags($flags = array(), $module = '', $indent = '') {
  // For features_var_export() (optional).
  module_load_include('inc', 'features', 'features.export');
  $output = $indent . '$flags = array();' . "\n";
  foreach ($flags as $item) {
    if (is_object($item)) {
      $flag = $item;
    }
    else {
      // We got just the flag name, for example from the features
      // implementation.
      if (!($flag = flag_load($item, TRUE))) {
        continue;
      }
    }
    if (!$flag->is_compatible()) {
      drupal_set_message(t('Could not export flag %flag-name: Your flag was created by a different version of the Flag module than is now being used.', array('%flag-name' => $flag->name)), 'error');
      continue;
    }

    $flag->api_version = FLAG_API_VERSION;
    $new_flag = (array) $flag;

    if (!empty($module)) {
      // Even though Flag adds the module name itself later, we add the module
      // name here for reference by other modules (such as Features).
      $new_flag['module'] = $module;
      // Lock the flag name, as is normally desired by modules using
      // hook_flag_default_flags(), and needed by Features.
      $new_flag['locked'] = array('name');
    }
    // Allow other modules to change the exported flag.
    drupal_alter('flag_export', $new_flag);

    // Remove properties we don't export.
    $unset_properties = array(
      // Remove the flag ID.
      'fid',
      // The name is emitted as the key for the array.
      'name',
      // The entity info is just used as helper data.
      'entity_info',
      // Remove roles.
      'roles',
      // Remove errors.
      'errors',
    );
    foreach ($unset_properties as $property) {
      unset($new_flag[$property]);
    }

    $output .= $indent . '// Exported flag: "' . check_plain($flag->get_title()) . '"' . ".\n";
    $output .= $indent . '$flags[\'' . $flag->name . '\'] = ' . (function_exists('features_var_export') ? features_var_export($new_flag, $indent) : var_export($new_flag, TRUE)) . ";\n";
  }
  $output .= $indent . 'return $flags;' . "\n";
  return $output;
}

/**
 * Form to import a flag.
 */
function flag_import_form() {
  $form = array();

  $form['import'] = array(
    '#title' => t('Flag import code'),
    '#type' => 'textarea',
    '#default_value' => '',
    '#rows' => 15,
    '#required' => TRUE,
    '#description' => t('Paste the code from a <a href="@export-url">flag export</a> here to import it into you site. Flags imported with the same name will update existing flags. Flags with a new name will be created.', array('@export-url' => url(FLAG_ADMIN_PATH . '/export'))),
  );
  $form['submit'] = array(
    '#value' => t('Import'),
    '#type' => 'submit',
  );

  return $form;
}

/**
 * Validate handler; Import a flag.
 */
function flag_import_form_validate($form, &$form_state) {
  $flags = array();
  ob_start();
  eval($form_state['values']['import']);
  ob_end_clean();

  if (!isset($flags) || !is_array($flags)) {
    form_set_error('import', t('A valid list of flags could not be found in the import code.'));
    return;
  }

  // Create the flag object.
  foreach ($flags as $flag_name => $flag_info) {
    // Backward compatibility: old exported flags have their names in $flag_info
    // instead, so we use the += operator to not overwrite it.
    $flag_info += array(
      'name' => $flag_name,
    );
    $new_flag = flag_flag::factory_by_array($flag_info);

    // Give new flags with the same name a matching FID, which tells Flag to
    // update the existing flag, rather than creating a new one.
    if ($existing_flag = flag_get_flag($new_flag->name)) {
      $new_flag->fid = $existing_flag->fid;
    }

    if ($errors = $new_flag->validate()) {
      $message = t('The import of the %flag flag failed because the following errors were encountered during the import:', array('%flag' => $new_flag->name));
      $message_errors = array();
      foreach ($errors as $field => $field_errors) {
        foreach ($field_errors as $error) {
          $message_errors[] = $error['message'];
        }
      }
      form_set_error('import', $message . theme('item_list', array('items' => $message_errors)));
    }
    else {
      // Save the new flag for the submit handler.
      $form_state['flags'][] = $new_flag;
    }
  }
}

/**
 * Submit handler; Import a flag.
 */
function flag_import_form_submit($form, &$form_state) {
  module_load_include('inc', 'flag', 'includes/flag.admin');

  // Build up values for the cache clear.
  $entity_types = array();
  $new = FALSE;

  foreach ($form_state['flags'] as $flag) {
    $flag->save();
    if (!empty($flag->status)) {
      $flag->enable();
    }
    if ($flag->is_new) {
      drupal_set_message(t('Flag @name has been imported.', array('@name' => $flag->name)));
      $new = TRUE;
    }
    else {
      drupal_set_message(t('Flag @name has been updated.', array('@name' => $flag->name)));
    }
    $entity_types[] = $flag->entity_type;
  }
  _flag_clear_cache($entity_types, $new);

  $form_state['redirect'] = FLAG_ADMIN_PATH;
}

/**
 * Export a flag and display it in a form.
 */
function flag_export_form($form, &$form_state, $flag = NULL) {
  // If we were passed a flag, use it as the list of flags to export.
  if ($flag) {
    $flags = array($flag);
  }

  // Display a list of flags to export.
  if (!isset($flags)) {
    if (isset($form_state['values']['flags'])) {
      $flags = array();
      foreach ($form_state['values']['flags'] as $flag_name) {
        if ($flag_name && $flag = flag_get_flag($flag_name)) {
          $flags[] = $flag;
        }
      }
    }
    else {
      $form['flags'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Flags to export'),
        '#options' => drupal_map_assoc(array_keys(flag_get_flags())),
        '#description' => t('Exporting your flags is useful for moving flags from one site to another, or when including your flag definitions in a module.'),
      );
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Export'),
      );
    }
  }

  if (isset($flags)) {
    $code = flag_export_flags($flags);

    // Link to the Features page if module is present, otherwise link to the
    // Drupal project page.
    $features_link = module_exists('features') ? url('admin/build/features') : url('http://drupal.org/project/features');

    $form['export'] = array(
      '#type' => 'textarea',
      '#title' => t('Flag exports'),
      '#description' => t('Use the exported code to later <a href="@import-flag">import</a> it. Exports can be included in modules using <a href="http://drupal.org/node/305086#default-flags">hook_flag_default_flags()</a> or using the <a href="@features-url">Features</a> module.', array('@import-flag' => url(FLAG_ADMIN_PATH . '/import'), '@features-url' => $features_link)),
      '#value' => $code,
      '#rows' => 15,
    );
  }

  return $form;
}

/**
 * Submit handler; Rebuild the export form after the list of flags has been set.
 */
function flag_export_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Page for displaying an upgrade message and export form for Flag 1.x flags.
 */
function flag_update_page($flag) {
  if ($flag->is_compatible()) {
    drupal_set_message(t('The flag %name is already up-to-date with the latest Flag API and does not need upgrading.', array('%name' => $flag->name)));
    drupal_goto(FLAG_ADMIN_PATH);
  }

  drupal_set_message(t('The flag %name is currently using the Flag API version @version, which is not compatible with the current version of Flag. You can upgrade this flag by pasting the below code into <em>@module_flag_default_flags()</em> function in the @module.module file.', array('%name' => $flag->name, '@version' => $flag->api_version, '@module' => $flag->module)), 'warning');

  flag_update_export($flag);

  return drupal_get_form('flag_export_form', $flag);
}

/**
 * Update a flag before export.
 *
 * @param $flag
 *   The flag object passed by reference.
 */
function flag_update_export(&$flag) {
  // Set the API version to 1 by default: version 1 did not explicitly define
  // the API version.
  if (empty($flag->api_version)) {
    $flag->api_version = 1;
  }

  // Get all our update classes.
  // This is not terribly graceful, but the alternative is declaring our classes
  // explicitly, or registering them with the Drupal autoloader and then running
  // a database query, which seems a waste of space given we only ever need
  // these here.
  $classes = get_declared_classes();
  $update_handlers = array();
  foreach ($classes as $class) {
    // Any class whose name is of the form 'FlagUpdate_foo' is one of ours, we
    // assume. Should this prove problematic, we can add use of reflection here.
    if (substr($class, 0, 11) == 'FlagUpdate_') {
      // @todo: change this to work with the static class when we drop support
      // for PHP 5.2: see commit d5b517.
      $update_handler = new $class();
      // Cast to string, as decimals as array keys seem to be rounded down to
      // ints, WTF PHP?
      $version = (string) $update_handler->old_api_version;

      $update_handlers[$version] = $update_handler;
    }
  }
  // Sort the classes by old version number.
  uksort($update_handlers, 'version_compare');

  // Work through each update handler.
  foreach ($update_handlers as $old_api_version => $update_handler) {
    // Skip update classes that are older than our current flag.
    if (version_compare($old_api_version, $flag->api_version, '<')) {
      continue;
    }

    // Run the update and change the API version on the flag.
    $update_handler->update($flag);
    $flag->api_version = $update_handler->new_api_version;
  }
}

/**
 * Flag update class for API 1 flags -> API 2.
 *
 * The class name after the prefix is immaterial, though we follow the Drupal
 * system update convention whereby the number here is what we update to.
 */
class FlagUpdate_2 {

  /**
   * The API version this class updates a flag from.
   *
   * @todo: Change this to a class constant when we drop support for PHP 5.2.
   */
  public $old_api_version = 1;

  /**
   * The API version this class updates a flag to.
   */
  public $new_api_version = 2;

  /**
   * The update function for the flag.
   */
  static function update(&$flag) {
    if (isset($flag->roles) && !isset($flag->roles['flag'])) {
      $flag->roles = array(
        'flag' => $flag->roles,
        'unflag' => $flag->roles,
      );
    }
  }
}

/**
 * Flag update class for API 2 flags -> API 3.
 */
class FlagUpdate_3 {

  public $old_api_version = 2;
  public $new_api_version = 3;

  static function update(&$flag) {
    // Change the content_type property to entity_type.
    if (isset($flag->content_type)) {
      $flag->entity_type = $flag->content_type;
      unset($flag->content_type);
    }

    // We can't convert the flag roles data to user permissions at this point
    // because the flag is disabled and hence hook_permission() doesn't see it
    // to define its permissions.
    // Instead, we copy it to import_roles, which the flag add form will handle
    // on new flags (which this flag will behave as when it is re-enabled).
    // @see flag_form()
    if (isset($flag->roles)) {
      $flag->import_roles = $flag->roles;
    }

    // Update show_on_teaser property to use new view mode settings.
    if (!empty($flag->show_on_teaser)) {
      $flag->show_in_links['teaser'] = TRUE;
      unset($flag->show_on_teaser);
    }

    // Update show_on_page property to use new view mode settings.
    if (!empty($flag->show_on_page)) {
      $flag->show_in_links['full'] = TRUE;
      unset($flag->show_on_page);
    }

    // Update show_on_comment and show_on_entity properties to use new view
    // mode settings. Since the old logic was to show on all view modes, do
    // that.
    if (!empty($flag->show_on_entity) || !empty($flag->show_on_comment)) {
      if ($entity_info = entity_get_info($flag->entity_type)) {
        foreach ($entity_info['view modes'] as $view_mode => $value) {
          $flag->show_in_links[$view_mode] = TRUE;
        }
      }

      unset($flag->show_on_entity, $flag->show_on_comment);
    }
  }
}
