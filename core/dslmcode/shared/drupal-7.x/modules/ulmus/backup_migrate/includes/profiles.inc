<?php


/**
 * @file
 * All of the settings profiles handling code for Backup and Migrate.
 */

backup_migrate_include('crud');


/**
 * Implementation of hook_backup_migrate_profile_subtypes().
 *
 * Get the built in Backup and Migrate profile types.
 */
function backup_migrate_backup_migrate_profile_subtypes() {
  $out = array();
  $out += array(
    'backup' => array(
      'include' => 'profiles',
      'type_name' => t('Backup Settings Profile'),
      'class' => 'backup_migrate_profile',
    ),
  );
  return $out;
}


/**
 * Get all the available backup profiles.
 */
function backup_migrate_get_profiles() {
  backup_migrate_include('filters');
  static $profiles = NULL;

  // Get the list of profiles and cache them locally.
  if ($profiles === NULL) {
    $profiles = backup_migrate_crud_get_items('profile');
  }
  return $profiles;
}

/**
 * Implementation of hook_backup_migrate_profiles_alter().
 *
 * Add default settings for any plugins which didn't exist when the profile was saved.
 */
function backup_migrate_backup_migrate_profiles_alter(&$profiles) {
  foreach ($profiles as $id => $profile) {
    // Set the default values for filter setting which don't exist in the profile.
    $profiles[$id]->filters = (array)@$profile->filters + (array)backup_migrate_filters_settings_default('backup');
  }
}

/**
 * Get the profile info for the profile with the given ID, or NULL if none exists.
 */
function backup_migrate_get_profile($profile_id) {
  $profiles = backup_migrate_get_profiles();
  return @$profiles[$profile_id];
}

/**
 * Implementation of hook_backup_migrate_profiles().
 */
function backup_migrate_backup_migrate_profiles() {
  $out = array();

  // Get the module default profile.
  $out['default'] = backup_migrate_crud_create_item('profile', array('name' => t("Default Settings"), 'machine_name' => 'default'));

  return $out;
}

/* Utilities */

/**
 * Get the available profiles as an options array for a form item.
 */
function _backup_migrate_get_profile_form_item_options() {
  $out = array();
  foreach ((array)backup_migrate_get_profiles() as $key => $profile) {
    $out[$key] = $profile->get('name');
  }
  return $out;
}

/**
 * Get a form to configure the profile.
 */
function _backup_migrate_ui_backup_settings_form($profile) {
  drupal_add_js(array('backup_migrate' => array('checkboxLinkText' => t('View as checkboxes'))), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.js', array('type' => 'file', 'scope' => 'footer'));
  drupal_add_css(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.css');

  backup_migrate_include('files', 'destinations', 'filters');

  $form    = array();

  $form['file'] = array(
    "#type" => "fieldset",
    "#title" => t("Backup File"),
    "#collapsible" => TRUE,
    "#collapsed" => FALSE,
    "#tree" => FALSE,
  );
  $form['file']['filename'] = array(
    "#type" => "textfield",
    "#title" => t("Backup file name"),
    "#default_value" => $profile->filename,
  );
  if (module_exists('token')) {
    $form['file']['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['file']['token_help']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('current-date', 'site'),
      '#global_types' => FALSE,
    );
    $form['file']['filename']['#description'] = t('You can use tokens in the file name.');
  }

  $form['file']['append_timestamp'] = array(
    "#type" => "checkbox",
    "#title" => t("Append a timestamp."),
    "#default_value" => $profile->append_timestamp,
  );
  $form['file']['timestamp_format_wrapper'] = array(
    '#type' => 'backup_migrate_dependent',
    '#dependencies' => array(
      'append_timestamp' => TRUE,
    ),
  );
  $form['file']['timestamp_format_wrapper']['timestamp_format'] = array(
    "#type" => "textfield",
    "#title" => t("Timestamp format"),
    "#default_value" => $profile->timestamp_format,
    "#description" => t('Should be a PHP <a href="!url">date()</a> format string.', array('!url' => 'http://www.php.net/date')),
  );

  $form['advanced'] = array('#weight' => 10);
  $form = array_merge_recursive($form, backup_migrate_filters_settings_form($profile->filters, 'backup'));

  // Add the advanced fieldset if there are any fields in it.
  if ($form['advanced']) {
    $form['advanced']['#type'] = 'fieldset';
    $form['advanced']['#title'] = t('Advanced Options');
    $form['advanced']['#collapsed'] = true;
    $form['advanced']['#collapsible'] = true;
  }

  $form['#validate'][]  = '_backup_migrate_ui_backup_settings_form_validate';
  $form['#submit'][]    = '_backup_migrate_ui_backup_settings_form_submit';

  return $form;
}

/**
 * Validate the profile form.
 */
function _backup_migrate_ui_backup_settings_form_validate($form, &$form_state) {
  backup_migrate_filters_settings_form_validate('backup', $form, $form_state);
}

/**
 * Submit the profile form.
 */
function _backup_migrate_ui_backup_settings_form_submit($form, &$form_state) {
  backup_migrate_filters_settings_form_submit('backup', $form, $form_state);
}
  
/**
 * Get the default profile.
 */
function _backup_migrate_profile_default_profile() {
  backup_migrate_include('files', 'filters');
  return array(
    'source_id' => 'db',
    'filename' => _backup_migrate_default_filename(),
    'append_timestamp' => 1,
    'timestamp_format' => 'Y-m-d\TH-i-s',
    'filters' => backup_migrate_filters_settings_default('backup'),
  );
}

/**
 * Get the default profile saved by the user (or the module default if none exists).
 */
function _backup_migrate_profile_saved_default_profile($profile_id = NULL) {
  $profile_id = $profile_id ? $profile_id : variable_get("backup_migrate_profile_id", 'default');
  $profile = NULL;
  if ($profile_id) {
    $profile = backup_migrate_get_profile($profile_id);
  }
  if (!$profile) {
    $profile = backup_migrate_get_profile('default');
  }
  return $profile;
}

/**
 * A profile class for crud operations.
 */
class backup_migrate_profile extends backup_migrate_item {
  var $db_table = "backup_migrate_profiles";
  var $type_name = "profile";
  var $singular = 'settings profile';
  var $plural = 'settings profiles';
  var $title_plural = 'Settings Profiles';
  var $title_singular = 'Settings Profile';

  /**
   * This function is not supposed to be called. It is just here to help the po extractor out.
   */
  function strings() {
    // Help the pot extractor find these strings.
    t('Settings Profile');
    t('Settings Profiles');
    t('settings profile');
    t('settings profiles');
  }

  /**
   * Get the default values for standard parameters.
   */
  function get_default_values() {
    return _backup_migrate_profile_default_profile() + array('name' => t("Untitled Profile"));
  }

  /**
   * Get a table of all items of this type.
   */  
  function get_list() {
    drupal_add_css(drupal_get_path('module', 'backup_migrate') .'/backup_migrate.css');
    return parent::get_list();
  }

  /**
   * Get the columns needed to list the type.
   */  
  function get_list_column_info() {
    $out = parent::get_list_column_info();
    $out = array(
      'name'                  => array('title' => t('Name')),
      'source_name'           => array('title' => t('Source')),
      'filename'              => array('title' => t('Filename')),
    ) + $out;
    return $out;
  }

  /**
   * Set the source of this setings profile. Takes either a source object or source id.
   */
  function set_source($source) {
    if (is_object($source)) {
      $this->source = $source;
      $this->source_id = $source->get_id();
    }
    else {
      $this->source_id = $source;
      unset($this->source);
    }
  }

  /**
   * Get the source of the profile.
   */
  function get_source() {
    backup_migrate_include('locations');
    if (!empty($this->source_id) && (empty($this->source) || $this->source->get_id() !== $this->source_id)) {
      $this->source = backup_migrate_get_source($this->source_id);
    }
    return empty($this->source) ? NULL : $this->source;
  }

  /**
   * Get the name of the source.
   */
  function get_source_name() {
    if ($source = $this->get_source()) {
      return $source->get_name();
    }
    return t("Missing");
  }

  /**
   * Get the destination of the profile.
   */
  function get_destination() {
    $destinations = (array)$this->get_destinations();
    return reset($destinations);
  }

  /**
   * Get the destination of the profile.
   */
  function get_destinations() {
    backup_migrate_include('destinations');
    if (empty($this->destinations)) {
      $this->destinations = array();
      $ids = $weights = array();
      if (!empty($this->destination_id)) {
        foreach ((array)$this->destination_id as $destination_id) {
          if (!in_array($destination_id, $ids) && $destination = backup_migrate_get_destination($destination_id)) {            
            $this->destinations[] = $destination;
            $weights[] = $destination->get('weight');
            $ids[] = $destination_id;
          }
        }
      }
      // Sort the destinations by weight.
      array_multisort($weights, SORT_NUMERIC, $this->destinations);
    }

    return $this->destinations;
  }

  /**
   * Get the name of the destination.
   */
  function get_destination_name() {
    $out = array();
    foreach ($this->get_destinations() as $destination) {
      $out[] = $destination->get_name();
    }
    if ($out) {
      return implode(', ', $out);
    }
    return t("Missing");
  }

  /**
   * Get the source and destinations specified in the given settings profile
   */
  function get_all_locations() {
    $out = array();
    $out += $this->get('destinations');
    $out[] = $this->get('source');
    return $out;
  }

  /**
   * Get the edit form.
   */
  function edit_form() {
    $form = parent::edit_form();
    $form['name'] = array(
      "#type" => "textfield",
      "#title" => t("Profile Name"),
      '#required' => TRUE,
      "#default_value" => $this->get('name'),
    );
    $form += _backup_migrate_ui_backup_settings_form($this);
    return $form;
  }

  /**
   * Get the message to send to the user when confirming the deletion of the item.
   */
  function delete_confirm_message() {
    return t('Are you sure you want to delete the profile %name? Any schedules using this profile will be disabled.', array('%name' => $this->get('name')));
  }
}

