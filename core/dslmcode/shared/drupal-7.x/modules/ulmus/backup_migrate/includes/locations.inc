<?php


/**
 * @file
 * All of the location handling code needed for Backup and Migrate.
 */

backup_migrate_include('crud');

/**
 * Get the available location types.
 */
function backup_migrate_get_location_subtypes() {
  backup_migrate_include('crud', 'destinations', 'sources');
  return backup_migrate_crud_subtypes('destination') + backup_migrate_crud_subtypes('source');
}

/**
 * Implementation of hook_backup_migrate_locations().
 *
 * Get the built in backup locations and those in the db.
 */
function backup_migrate_backup_migrate_locations() {
  $out = array();

  // Allow the filter plugins to declare the default locations.
  backup_migrate_include('filters');
  $out += backup_migrate_filters_invoke_all('locations');

  return $out;
}

/**
 * Get all the available backup location.
 *
 * @param $op
 *  The operation which will be performed on the location. Hooks can use this
 *  to return only those locations appropriate for the given op.
 *  Options include:
 *    'manual backup' - locations available for manual backup
 *    'scheduled backup' - locations available for schedules backup
 *    'list files' - locations whose backup files can be listed
 *    'restore' - locations whose files can be restored from
 *    'all' - all available locations should be returned
 */
function backup_migrate_get_locations($op = 'all') {
  static $locations = NULL;

  // Get the list of locations and cache them locally.
  if ($locations === NULL) {
    $locations = backup_migrate_crud_get_items('location');
  }

  // Return all if that's what was asked for.
  if ($op == 'all') {
    return $locations;
  }

  // Return only those locations which support the given op.
  $out = array();
  if ($locations) {
    foreach ($locations as $key => $location) {
      if ($location->op($op)) {
        $out[$key] = $location;
      }
    }
  }
  return $out;
}

/**
 * Get the location of the given id.
 */
function backup_migrate_get_location($id) {
  $locations = backup_migrate_get_locations('all');
  return empty($locations[$id]) ? NULL : $locations[$id];
}


/**
 * A base class for creating locations.
 */
class backup_migrate_location extends backup_migrate_item {
  var $db_table = "backup_migrate_destinations";
  var $type_name = "location";
  var $default_values = array('settings' => array());
  var $singular = 'location';
  var $plural = 'locations';
  var $title_plural = 'Locations';
  var $title_singular = 'Location';

  var $subtype = "";
  var $supported_ops = array();

  /**
   * This function is not supposed to be called. It is just here to help the po extractor out.
   */
  function strings() {
    // Help the pot extractor find these strings.
    t('location');
    t('locations');
    t('Location');
    t('Locations');
  }

  function ops() {
    return $this->supported_ops;
  }

  /**
   * Does this location support the given operation.
   */
  function op($op) {
    $ops = (array)$this->ops();
    return in_array($op, $ops);
  }

  /**
   * Remove the given op from the support list.
   */
  function remove_op($op) {
    $key = array_search($op, $this->supported_ops);
    if ($key !== FALSE) {
      unset($this->supported_ops[$key]);
    }
  }

  function get_name() {
    return @$this->name;
  }

  function set_name($name) {
    return $this->name = $name;
  }

  function set_location($location) {
    $this->location = $location;
  }

  function get_location() {
    return @$this->location;
  }

  function get_display_location() {
    return $this->get_location();
  }

  function settings($key = NULL) {
    $out = $this->settings;
    if ($key) {
      $out = isset($out[$key]) ? $out[$key] : NULL;
    }
    return $out;
  }

  /**
   * Get the type name of this location for display to the user.
   */
  function get_subtype_name() {
    if ($type = $this->get('subtype')) {
      $types = $this->location_types();
      return isset($types[$type]['type_name']) ? $types[$type]['type_name'] : $type;
    }
  }

  /**
   * Get the edit form for the item.
   */
  function edit_form() {
    if (!empty($this->supported_ops)) {
      $form = parent::edit_form();
      $form['subtype'] = array(
        "#type" => "value",
        "#default_value" => $this->get('subtype'),
      );
    }
    else {
      $types = $this->location_types();
      $items = array();
      // If no (valid) node type has been provided, display a node type overview.
      foreach ($types as $key => $type) {
        if (@$type['can_create']) {
          $type_url_str = str_replace('_', '-', $key);
          $out = '<dt>'. l($type['type_name'], BACKUP_MIGRATE_MENU_PATH . "/settings/$this->type_name/add/$type_url_str", array('attributes' => array('title' => t('Add a new @s location.', array('@s' => $type['type_name']))))) .'</dt>';
          $out .= '<dd>'. filter_xss_admin($type['description']) .'</dd>';
          $items[] = $out;
        }
      }
      if (count($items)) {
        $output = t('Choose the type of location you would like to create:') .'<dl>'. implode('', $items) .'</dl>';
      }
      else {
        $output = t('No types available.');
      }
      $form['select_type'] = array(
        '#type' => 'markup',
        '#markup' => $output,
      );
    }
    return $form;
  }

  /**
   * Get the available location types.
   */
  function location_types() {
    return backup_migrate_get_location_subtypes();
  }

  /**
   * Get the message to send to the user when confirming the deletion of the item.
   */
  function delete_confirm_message() {
    return t('Are you sure you want to delete the %name?', array('%name' => $this->get_name()));
  }

  /**
   * Get the columns needed to list the type.
   */  
  function get_list_column_info() {
    $out = parent::get_list_column_info();
    $out = array(
      'name'                  => array('title' => t('Name')),
      'subtype_name'    => array('title' => t('Type')),
      'display_location'      => array('title' => t('Location')),
    ) + $out;
    return $out;
  }

  /**
   * Get a row of data to be used in a list of items of this type.
   */  
  function get_list_row() {
    $out = parent::get_list_row();

    // Supress locations with no actions as there's no value in showing them (and they may confuse new users).
    if (empty($out['actions'])) {
      return NULL;
    }
    return $out;
  }

  /**
   * Get the action links for a location.
   */
  function get_action_links() {
    $out = parent::get_action_links();
    $item_id = $this->get_id();

    // Don't display the download/delete/restore ops if they are not available for this location.
    if ($this->op('list files') && user_access("access backup files")) {
      $out = array('list files' => l(t("list files"), BACKUP_MIGRATE_MENU_PATH . "/$this->type_name/list/files/". $item_id)) + $out;
    }
    if (!$this->op('configure') || !user_access('administer backup and migrate')) {
      unset($out['edit']);
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
   * Get the form for the settings for this location type.
   */
  function settings_default() {
    return array();
  }

  /**
   * Get the form for the settings for this location.
   */
  function settings_form($form) {
    return $form;
  }

  /**
   * Validate the form for the settings for this location.
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
   * Get the form for the settings for this filter.
   */
  function backup_settings_default() {
    return array();
  }

  /**
   * Get the form for the settings for this filter.
   */
  function backup_settings_form($settings) {
    return array();
  }

  /**
   * Get the form for the settings for this filter.
   */
  function backup_settings_form_validate($form, &$form_state) {
  }

  /**
   * Submit the settings form. Any values returned will be saved.
   */
  function backup_settings_form_submit($form, &$form_state) {
  }

  /**
   * Get the form for the settings for this filter.
   */
  function restore_settings_default() {
    return array();
  }

  /**
   * Get the form for the settings for this filter.
   */
  function restore_settings_form($settings) {
    return array();
  }

  /**
   * Get the form for the settings for this filter.
   */
  function restore_settings_form_validate($form_values) {
  }

  /**
   * Submit the settings form. Any values returned will be saved.
   */
  function restore_settings_form_submit($form_values) {
    return $form_values;
  }

  /**
   * Create a new location of the correct type.
   */
  function create($params = array()) {
    $out = NULL;
    $types = backup_migrate_get_location_subtypes();
    // Get the type passed in in the params, or if none, check the url for a valid type name.
    // This is to allow new location type to be specified in the path.
    $location_type = !empty($params['subtype']) ? $params['subtype'] : NULL;

    if ($location_type && ($type = @$types[$location_type])) {
      // Include the necessary file if specified by the type.
      if (!empty($type['file'])) {
        require_once './'. $type['file'];
      }
      $out = new $type['class']($params + array('subtype' => $location_type));
    }

    if (empty($out)) {
      $out = parent::create($params);
    }
    return $out;
  }

   /**
   * Get a url from the parts.
   */
  function url($hide_password = TRUE) {
    return $this->glue_url($this->dest_url, $hide_password);
  }

  /**
   * Glue a URLs component parts back into a URL.
   */
  function glue_url($parts, $hide_password = TRUE) {
    // Obscure the password if we need to.
    $parts['pass'] = $hide_password ? "" : $parts['pass'];

    // Assemble the URL.
    $out = "";
    $out .= $parts['scheme'] .'://';
    $out .= $parts['user'] ? urlencode($parts['user']) : '';
    $out .= ($parts['user'] && $parts['pass']) ? ":". urlencode($parts['pass']) : '';
    $out .= ($parts['user'] || $parts['pass']) ? "@" : "";
    $out .= $parts['host'];
    $out .= !empty($parts['port']) ? ':'. $parts['port'] : '';
    $out .= "/". $parts['path'];
    return $out;
  }

  /**
   * Break a URL into it's component parts.
   */
  function set_url($url) {
    $parts          = (array)parse_url($url);
    $parts['user'] = urldecode(@$parts['user']);
    $parts['pass'] = urldecode(@$parts['pass']);
    $parts['path'] = urldecode(@$parts['path']);
    $parts['path']  = ltrim(@$parts['path'], "/");
    $this->dest_url = $parts;
  }

  /**
   * Retrieve a list of filetypes supported by this source/destination.
   */
  function file_types() {
    return array();
  }

}

/**
 * A base class for creating locations.
 */
class backup_migrate_location_remote extends backup_migrate_location {
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
   * Get a url from the parts.
   */
  function url($hide_password = TRUE) {
    return $this->glue_url($this->dest_url, $hide_password);
  }

  /**
   * Glue a URLs component parts back into a URL.
   */
  function glue_url($parts, $hide_password = TRUE) {
    // Obscure the password if we need to.
    $parts['pass'] = $hide_password ? "" : $parts['pass'];

    // Assemble the URL.
    $out = "";
    $out .= $parts['scheme'] .'://';
    $out .= $parts['user'] ? urlencode($parts['user']) : '';
    $out .= ($parts['user'] && $parts['pass']) ? ":". urlencode($parts['pass']) : '';
    $out .= ($parts['user'] || $parts['pass']) ? "@" : "";
    $out .= $parts['host'];
    $out .= !empty($parts['port']) ? ':'. $parts['port'] : '';
    $out .= "/". $parts['path'];
    return $out;
  }

  /**
   * Break a URL into it's component parts.
   */
  function set_url($url) {
    $parts          = (array)parse_url($url);
    $parts['user'] = urldecode(@$parts['user']);
    $parts['pass'] = urldecode(@$parts['pass']);
    $parts['path'] = urldecode(@$parts['path']);
    $parts['path']  = ltrim(@$parts['path'], "/");
    $this->dest_url = $parts;
  }

  /**
   * location configuration callback.
   */
  function edit_form() {
    $form = parent::edit_form();
    $form['scheme'] = array(
      "#type" => "select",
      "#title" => t("Scheme"),
      "#default_value" => @$this->dest_url['scheme'] ? $this->dest_url['scheme'] : 'mysql',
      "#required" => TRUE,
      "#options" => array($GLOBALS['db_type'] => $GLOBALS['db_type']),
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

