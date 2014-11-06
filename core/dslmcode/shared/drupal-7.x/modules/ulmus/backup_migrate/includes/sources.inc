<?php


/**
 * @file
 * All of the source handling code needed for Backup and Migrate.
 */

backup_migrate_include('crud', 'locations', 'destinations');

/**
 * Get all the available backup sources.
 */
function backup_migrate_get_sources() {
  return backup_migrate_crud_get_items('source');
}

/**
 * Get the available source types.
 */
function backup_migrate_get_source_subtypes() {
  return backup_migrate_crud_subtypes('source');
}

/**
 * Get the destination of the given id.
 */
function backup_migrate_get_source($id) {
  $sources = backup_migrate_get_sources();
  return empty($sources[$id]) ? NULL : $sources[$id];
}

/**
 * Create a source object of the given type with the given params.
 */
function backup_migrate_create_source($subtype, $params = array()) {
  $params['subtype'] = $subtype;
  return backup_migrate_crud_create_item('source', $params);
}

/**
 * Implementation of hook_backup_migrate_source_subtypes().
 *
 * Get the built in Backup and Migrate source types.
 */
function backup_migrate_backup_migrate_source_subtypes() {
  $out = array();
  $out += array(
    'db' => array(
      'type_name' => t('Database'),
      'description' => t('Import the backup directly into another database. Database sources can also be used as a source to backup from.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/sources.db.inc',
      'class' => 'backup_migrate_source_db',
      'can_create' => FALSE,
    ),
    'mysql' => array(
      'type_name' => t('MySQL Database'),
      'description' => t('Import the backup directly into another MySQL database. Database sources can also be used as a source to backup from.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/sources.db.mysql.inc',
      'class' => 'backup_migrate_source_db_mysql',
      'can_create' => TRUE,
    ),
    'filesource' => array(
      'description' => t('A files directory which can be backed up from.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/sources.filesource.inc',
      'class' => 'backup_migrate_destination_filesource',
      'type_name' => t('File Directory'),
      'can_create' => TRUE,
    ),
    'archive' => array(
      'description' => t('Create an archive of your entire site.'),
      'file' => drupal_get_path('module', 'backup_migrate') .'/includes/sources.archivesource.inc',
      'class' => 'backup_migrate_files_destination_archivesource',
      'type_name' => t('Site Archive'),
      'can_create' => FALSE,
    ),
  );

  return $out;
}

/**
 * Implementation of hook_backup_migrate_sources().
 *
 * Get the built in backup sources and those in the db.
 */
function backup_migrate_backup_migrate_sources() {
  $out              = array();

  // Expose the configured databases as sources.
  backup_migrate_include('filters');
  $out += backup_migrate_filters_invoke_all('sources');

  return $out;
}

/**
 * Get the source options as a form element.
 */
function _backup_migrate_get_source_form($source_id = 'db') {
  backup_migrate_include('destinations');

  $form = array();
  $sources = _backup_migrate_get_source_pulldown($source_id);
  if (count($sources['#options']) > 1) {
    $form['source'] = array(
      "#type" => "fieldset",
      "#title" => t("Backup Source"),
      "#collapsible" => TRUE,
      "#collapsed" => FALSE,
      "#tree" => FALSE,
    );
    $sources['#description'] = t("Choose the database to backup. Any database destinations you have created and any databases specified in your settings.php can be backed up.");

    $form['source']['source_id'] = $sources;
  }
  else {
    $form = array();
    $form['source']['source_id'] = array(
      "#type" => "value",
      "#value" => $source_id,
    );
  }
  return $form;
}

/**
 * Get pulldown to select existing source options.
 */
function _backup_migrate_get_source_pulldown($source_id = NULL) {
  $sources = _backup_migrate_get_source_form_item_options();
  $form = array(
    "#type" => "select",
    "#title" => t("Backup Source"),
    "#options" => _backup_migrate_get_source_form_item_options(),
    "#default_value" => $source_id,
  );
  return $form;
}

/**
 * Get the location options as an options array for a form item.
 */
function _backup_migrate_get_source_form_item_options() {
  $out = array();
  foreach (backup_migrate_get_sources() as $key => $location) {
    $out[$key] = $location->get_name();
  }
  return $out;
}

/**
 * A base class for creating sources.
 */
class backup_migrate_source extends backup_migrate_location {
  var $db_table = "backup_migrate_sources";
  var $type_name = 'source';
  var $singular = 'source';
  var $plural = 'sources';
  var $title_plural = 'Sources';
  var $title_singular = 'Source';

  /**
   * This function is not supposed to be called. It is just here to help the po extractor out.
   */
  function strings() {
    // Help the pot extractor find these strings.
    t('source');
    t('sources');
    t('Sources');
    t('Source');
  }

  /**
   * Get the available location types.
   */
  function location_types() {
    return backup_migrate_get_source_subtypes();
  }

}

/**
 * A base class for creating sources.
 */
class backup_migrate_source_remote extends backup_migrate_source {
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
   * source configuration callback.
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

