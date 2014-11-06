<?php

/**
 * @file
 * CRUD functions for backup and migrate types (schedules, profiles etc.).
 */

define('BACKUP_MIGRATE_STORAGE_NONE', 0);
define('BACKUP_MIGRATE_STORAGE_DB', 1);
define('BACKUP_MIGRATE_STORAGE_OVERRIDEN', 2);

/**
 * Return a list of CRUD types in the module.
 */
function backup_migrate_crud_types() {
  $out = array(
    'schedule' => array(
      'class' => 'backup_migrate_schedule',
      'include' => 'schedules',
    ),
    'source' => array(
      'class' => 'backup_migrate_source',
      'include' => 'sources',
    ),
    'destination' => array(
      'class' => 'backup_migrate_destination',
      'include' => 'destinations',
    ),
    'profile' => array(
      'class' => 'backup_migrate_profile',
      'include' => 'profiles',
    ),
  );
  return $out;
}

/**
 * Get the info for a particular crud type.
 */
function backup_migrate_crud_type_info($type) {
  $types = backup_migrate_crud_types();
  if (isset($types[$type])) {
    return $types[$type];
  }
  return NULL;
}

/**
 * Get a list of avaiable classes of each crud type.
 */
function backup_migrate_crud_subtypes($type) {
  $out = array();
  if ($info = backup_migrate_crud_type_info($type)) {
    // Include the function that contains the type base.
    if (!empty($info['include'])) {
      backup_migrate_include($info['include']);
    }

    // Allow modules (including this one) to declare backup and migrate subtypes.
    // We don't use module_invoke_all so we can avoid the side-effects of array_merge_recursive.
    $out = array();
    foreach (module_implements('backup_migrate_' . $type . '_subtypes') as $module) {
      $function =  $module . '_backup_migrate_' . $type . '_subtypes';
      $result = $function();
      if (isset($result) && is_array($result)) {
      foreach ($result as $key => $val) {
          $out[$key] = $val;
        }
      }
    }
  }

  return $out;
}

/**
 * Get the info for a particular crud subtype.
 */
function backup_migrate_crud_subtype_info($type, $subtype) {
  $types = backup_migrate_crud_subtypes($type);
  if (isset($types[$subtype])) {
    return $types[$subtype];
  }
  return NULL;
}

/**
 * Get a generic object of the given type to be used for static-like functions.
 *
 * I'm not using actual static method calls since they don't work on variables prior to PHP 5.3.0
 */
function backup_migrate_crud_type_load($type, $subtype = NULL) {
  $out = $info = NULL;

  if ($subtype) {
    $info = backup_migrate_crud_subtype_info($type, $subtype);
  }
  else {
    $info = backup_migrate_crud_type_info($type);
  }

  if (!empty($info)) {
    if (!empty($info['include'])) {
      backup_migrate_include($info['include']);
    }
    if (!empty($info['file'])) {
      include_once './'. (isset($info['path']) ? $info['path'] : '') . $info['file'];
    }

    if (class_exists($info['class'])) {
      $out = new $info['class'];
      $out = $out->create(array('subtype' => $subtype));
    }
  }
  return $out;
}

/**
 * Page callback to create a new item.
 */
function backup_migrate_crud_create($type, $subtype = NULL) {
  if ($item = backup_migrate_crud_type_load($type, $subtype)) {
    return $item;
  }
  return NULL;
}

/**
 * Get the menu items handled by the CRUD code.
 */
function backup_migrate_crud_menu() {
  $items = array();
  foreach (backup_migrate_crud_types() as $type => $info) {
    $item = backup_migrate_crud_type_load($type);
    $items += (array)$item->get_menu_items();
    foreach (backup_migrate_crud_subtypes($type) as $subtype => $info) {
      $subitem = backup_migrate_crud_type_load($type, $subtype);
      $items += (array)$subitem->get_menu_items();
    }
  }
  return $items;
}

/**
 * Page callback to create a new item.
 */
function backup_migrate_crud_ui_create($type, $subtype = NULL) {
  if ($item = backup_migrate_crud_create($type, $subtype)) {
    return drupal_get_form('backup_migrate_crud_edit_form', $item);
  }
  return drupal_not_found();
}

/**
 * Page callback to list all items.
 */
function backup_migrate_crud_ui_list($type) {
  $out = '';
  if ($type = backup_migrate_crud_type_load($type)) {
    $out = $type->get_list();
  }
  return $out;
}

/**
 * Page callback to list all items.
 */
function backup_migrate_crud_ui_list_all() {
  $out = '';
  foreach (backup_migrate_crud_types() as $type => $info) {
    $type = backup_migrate_crud_type_load($type);
    $out[] = theme('backup_migrate_group', array('title' => t($type->title_plural), 'body' => $type->get_list()));
  }
  return implode('', $out);
}


/**
 * Page callback to edit an item.
 */
function backup_migrate_crud_ui_edit($type, $item_id = NULL) {
  if ($type = backup_migrate_crud_type_load($type)) {
    if ($item_id && $item = $type->item($item_id)) {
      return drupal_get_form('backup_migrate_crud_edit_form', $item);
    }
    drupal_goto($type->get_settings_path());
  }
}

/**
 * Does a crud item with the given name exist.
 * 
 * Callback for the 'machine_name' form type.
 */
function backup_migrate_crud_item_exists($machine_name, $element, $form_state) {
  return $form_state['values']['item']->item_exists($machine_name);
}

/**
 * A form callback to edit an item.
 */
function backup_migrate_crud_edit_form($form, $form_state, $item) {
  $form = $item->edit_form();

  $form['item'] = array(
    '#type' => 'value',
    '#value' => $item,
  );
  $form['#validate'][]  = 'backup_migrate_crud_edit_form_validate';
  $form['#submit'][]    = 'backup_migrate_crud_edit_form_submit';

  return $form;
}

/**
 * Validate the item edit form.
 */
function backup_migrate_crud_edit_form_validate($form, &$form_state) {
  $item = $form_state['values']['item'];
  $item->edit_form_validate($form, $form_state);
}

/**
 * Submit the item edit form.
 */
function backup_migrate_crud_edit_form_submit($form, &$form_state) {
  $item = $form_state['values']['item'];

  $item->edit_form_submit($form, $form_state);
  if (empty($form_state['redirect'])) {
    $form_state['redirect'] = $item->get_settings_path();
  }
}


/**
 * Page callback to delete an item.
 */
function backup_migrate_crud_ui_delete($type, $item_id = NULL) {
  if ($type = backup_migrate_crud_type_load($type)) {
    if ($item_id && $item = $type->item($item_id)) {
      return drupal_get_form('backup_migrate_crud_delete_confirm_form', $item);
    }
    drupal_goto($type->get_settings_path());
  }
}

/**
 * Ask confirmation for deletion of a item.
 */
function backup_migrate_crud_delete_confirm_form($form, &$form_state, $item) {
  $form['item'] = array(
    '#type' => 'value',
    '#value' => $item,
  );
  if ($item->storage == BACKUP_MIGRATE_STORAGE_OVERRIDEN) {
    $message = $item->revert_confirm_message();
    return confirm_form($form, t('Are you sure?'), $item->get_settings_path(), $message, t('Revert'), t('Cancel'));
  } else {
    $message = $item->delete_confirm_message();
    return confirm_form($form, t('Are you sure?'), $item->get_settings_path(), $message, t('Delete'), t('Cancel'));
  }  
}

/**
 * Delete a item after confirmation.
 */
function backup_migrate_crud_delete_confirm_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $item = $form_state['values']['item'];
    $item->delete();
  }
  $form_state['redirect'] = $item->get_settings_path();
}

/**
 * Export an item.
 */
function backup_migrate_crud_ui_export($type, $item_id = NULL) {
  if ($type = backup_migrate_crud_type_load($type)) {
    if ($item_id && $item = $type->item($item_id)) {
      return drupal_get_form('backup_migrate_crud_export_form', $item->export());
    }
    drupal_goto($type->get_settings_path());
  }
}

/**
 * Ask confirmation for deletion of a destination.
 */
function backup_migrate_crud_export_form($form, &$form_state, $export) {
  $form['export'] = array(
    '#title' => t('Exported content'),
    '#type' => 'textarea',
    '#rows' => min(30, count(explode("\n", $export))),
    '#value' => $export,
  );
  return $form;
}

/**
 * Page callback to import an item.
 */
function backup_migrate_crud_ui_import() {
  return drupal_get_form('backup_migrate_crud_import_form');
}

/**
 * Ask confirmation for deletion of a item.
 */
function backup_migrate_crud_import_form($form, &$form_state) {
  $form['code'] = array(
    '#type' => 'textarea',
    '#title' => t('Paste Exported Code Here'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );
  return $form;
}

/**
 * Validate handler to import a view
 */
function backup_migrate_crud_import_form_validate($form, &$form_state) {
  $item = backup_migrate_crud_create_from_import($form_state['values']['code']);
  if ($item) {
    $form_state['values']['item'] = $item;
  }
  else {
   form_set_error('code', t('Unable to import item.'));
  }
}

/**
 * import a item after confirmation.
 */
function backup_migrate_crud_import_form_submit($form, &$form_state) {
  $item = $form_state['values']['item'];
  $item->save();
  _backup_migrate_message('Your !type was imported', array('!type' => t($item->singular)));
  $form_state['redirect'] = $item->get_settings_path();
}

/**
 * Create an object from the exported object.
 */
function backup_migrate_crud_create_from_import($code) {
  $item = NULL;
  $code = 'return ' . $code . ';';
  ob_start();
  $values = eval($code);
  ob_end_clean();

  if ($values) {
    if (!empty($values['type_name']) && $type = backup_migrate_crud_type_load($values['type_name'])) {
      $item = $type->create($values);
      // Make sure the item's ID doesn't already exist.
      $item->unique_id();
    }
  }
  return $item;
}

/**
 * Get all items of the given type.
 */
function backup_migrate_crud_get_items($type) {
  if ($type = backup_migrate_crud_type_load($type)) {
    return $type->all_items();
  }
}


/**
 * Get an item of the specified type.
 */
function backup_migrate_crud_get_item($type, $id) {
  if ($type = backup_migrate_crud_type_load($type)) {
    return $type->item($id);
  }
}

/**
 * Create a new item of the given type.
 */
function backup_migrate_crud_create_item($type, $params) {
  if ($type = backup_migrate_crud_type_load($type)) {
    return $type->create($params);
  }
}

/**
 * A base class for items which can be stored in the database, listed, edited, deleted etc.
 */
class backup_migrate_item {
  var $show_in_list = TRUE;
  var $settings_path = '/settings/';
  var $db_table = '';
  var $type_name = '';
  var $storage = FALSE;
  var $default_values = array();
  var $singular = 'item';
  var $plural = 'items';
  var $title_plural = 'Items';
  var $title_singular = 'Item';

  /**
   * This function is not supposed to be called. It is just here to help the po extractor out.
   */
  function strings() {
    // Help the pot extractor find these strings.
    t('item');
    t('items');
    t('Items');
    t('Item');

    // Help the pot extractor find these strings.
    t('List !type');
    t('Create !type');
    t('Delete !type');
    t('Edit !type');
    t('Export !type');
  }


  /**
   * Constructor, set the basic info pulled from the db or generated programatically.
   */
  function __construct($params = array()) {
    $this->from_array($this->_merge_defaults((array)$params, (array)$this->get_default_values()));
  }

  /**
   * Merge parameters with the given defaults.
   *
   * Works like array_merge_recursive, but it doesn't turn scalar values into arrays.
   */
  function _merge_defaults($params, $defaults) {
    foreach ($defaults as $key => $val) {
      if (!isset($params[$key])) {
        $params[$key] = $val;
      }
      else if (is_array($params[$key])) {
        $params[$key] = $this->_merge_defaults($params[$key], $val);
      }
    }
    return $params;
  }

  /**
   * Get the default values for standard parameters.
   */
  function get_default_values() {
    return $this->default_values;
  }

  /**
   * Save the item to the database.
   */  
  function save() {
    if (!$this->get_id()) {
      $this->unique_id();
    }
    $record = $this->to_array();
    drupal_write_record($this->db_table, $record, !empty($this->storage) ? $this->get_primary_key() : array());
  }

  /**
   * Delete the item from the database.
   */  
  function delete() {
    $keys = (array)$this->get_machine_name_field();
    db_query('DELETE FROM {' . $this->db_table . '} WHERE ' . $keys[0] . ' = :id', array(':id' => $this->get_id()));
  }


  /**
   * Load an existing item from an array.
   */
  function from_array($params) {
    foreach ($params as $key => $value) {
      if (method_exists($this, 'set_'. $key)) {
        $this->{'set_'. $key}($value);
      }
      else {
        $this->{$key} = $value;
      }
    }
  }

  /**
   * Return as an array of values.
   */
  function to_array() {
    $out = array();
    // Return fields as specified in the schema.
    $schema = $this->get_schema();
    if (!empty($schema['fields']) && is_array($schema['fields'])) {
      foreach ($schema['fields'] as $field => $info) {
        $out[$field] = $this->get($field);
      }
    }
    return $out;
  }

  /**
   * Return as an exported array of values.
   */
  function export() {
    $out = $this->to_array();
    $out['type_name'] = $this->type_name;

    ob_start();
    var_export($out);
    $out = ob_get_contents();
    ob_end_clean();
    return $out;
  }

  /**
   * Load an existing item from an database (serialized) array.
   */
  function load_row($data) {
    $params = array();
    $schema = $this->get_schema();
    // Load fields as specified in the schema.
    foreach ($schema['fields'] as $field => $info) {
      $params[$field] = empty($info['serialize']) ? $data[$field] : unserialize($data[$field]);
    }
    $this->from_array($params);
  }


  /**
   * Decode a loaded db row (unserialize necessary fields).
   */
  function decode_db_row($data) {
    $params = array();
    $schema = $this->get_schema();
    // Load fields as specified in the schema.
    foreach ($schema['fields'] as $field => $info) {
      $params[$field] = empty($info['serialize']) ? $data[$field] : unserialize($data[$field]);
    }
    return $params;
  }

  /**
   * Return the fields which must be serialized before saving to the db.
   */
  function get_serialized_fields() {
    $out = array();
    $schema = $this->get_schema();
    foreach ($schema['fields'] as $field => $info) {
      if (!empty($info['serialize'])) {
        $out[] = $field;
      }
    }
    return $out;
  }

  /**
   * Get the primary key field title from the schema.
   */
  function get_primary_key() {
    $schema = $this->get_schema();
    return @$schema['primary key'];
  }

  /**
   * Get the machine name field name from the schema.
   */
  function get_machine_name_field() {
    $schema = $this->get_schema();
    if (isset($schema['export']['key'])) {
      return $schema['export']['key'];
    }
    return @$schema['primary key'];
  }

  /**
   * Get the schema for the item type.
   */
  function get_schema() {
    return drupal_get_schema($this->db_table);
  }

  /**
   * Get the primary id for this item (if any is set).
   *
   * We only handle single field keys since that's all we need.
   */
  function get_id() {
    $keys = (array)$this->get_machine_name_field();
    return !empty($keys[0]) && !empty($this->{$keys[0]}) ? (string)$this->{$keys[0]} : '';
  }

  /**
   * Set the primary id for this item (if any is set).
   */
  function set_id($id) {
    $keys = (array)$this->get_machine_name_field();
    if (!empty($keys[0])) {
      return $this->{$keys[0]} = $id;
    }
    return NULL;
  }

  /**
   * Return a random (very very likely unique) string id for a new item.
   */
  function generate_id() {
    $id = md5(uniqid(mt_rand(), true));

    // Find the shortest possible unique id from (min 4 chars).
    for ($i = 4; $i < 32; $i++) {
      $new_id = substr($id, 0, $i);
      if (!$this->item($new_id)) {
        return $new_id;
      }
    }
    // If we get here, then all 28 increasingly complex ids were already taken so we'll try again.
    // this could theoretially lead to an infinite loop, but the odds are incredibly low.
    return $this->generate_id();
  }

  /**
   * Make sure this item has a unique id. Should only be called for new items or the item will collide with itself.
   */
  function unique_id() {
    $id = $this->get_id();

    // Unset the autoincrement field so it can be regenerated.
    foreach ((array)$this->get_primary_key() as $key) {
      $this->{$key} = NULL;    
    }

    // If the item doesn't have an ID or if it's id is already taken, generate random one.
    if (!$id || $this->item($id)) {
      $this->set_id($this->generate_id());
    }
  }

  /**
   * Get the name of the item.
   */
  function get_name() {
    return @$this->name;
  }

  /**
   * Get the member with the given key.
   */  
  function get($key) {
    if (method_exists($this, 'get_'. $key)) {
      return $this->{'get_'. $key}();
    }
    return @$this->{$key};
  }

  /* UI Stuff */

  /**
   * Get the action links for a destination.
   */
  function get_action_links() {
    $out = array();

    $item_id = $this->get_id();

    $path = $this->get_settings_path();

    if (@$this->storage == BACKUP_MIGRATE_STORAGE_DB || @$this->storage == BACKUP_MIGRATE_STORAGE_OVERRIDEN) {
      $out['edit'] = l(t("edit"), $path . "/edit/$item_id");
    }
    else if (@$this->storage == BACKUP_MIGRATE_STORAGE_NONE) {
      $out['edit'] = l(t("override"), $path . "/edit/$item_id");
    }
    if (@$this->storage == BACKUP_MIGRATE_STORAGE_DB) {
      $out['delete'] = l(t("delete"), $path . "/delete/$item_id");
    }
    else if (@$this->storage == BACKUP_MIGRATE_STORAGE_OVERRIDEN) {
      $out['delete'] = l(t("revert"), $path . "/delete/$item_id");
    }
    $out['export'] = l(t("export"), $path . "/export/$item_id");

    return $out;
  }

  /**
   * Get a table of all items of this type.
   */  
  function get_list() {
    $items = $this->all_items();
    $rows = array();
    foreach ((array)$items as $item) {
      if ($item->show_in_list()) {
        if ($row = $item->get_list_row()) {
          $rows[] = $row;
        }
      }
    }
    if (count($rows)) {
      $out = theme('table', array('header' => $this->get_list_header(), 'rows' => $rows));
    }
    else {
      $out = t('There are no !items to display.', array('!items' => $this->plural));
    }
    if (user_access('administer backup and migrate')) {
      $out .= ' '. l(t('Create a new !item', array('!item' => $this->singular)), $this->get_settings_path() .'/add');
    }
    return $out;
  }

  /**
   * Get the columns needed to list the type.
   */  
  function show_in_list() {
    return $this->show_in_list;
  }

  /**
   * Get the columns needed to list the type.
   */  
  function get_settings_path() {
    return BACKUP_MIGRATE_MENU_PATH . $this->settings_path . $this->type_name;
  }


  /**
   * Get the columns needed to list the type.
   */  
  function get_list_column_info() {
    return array(
      'actions' => array('title' => t('Operations'), 'html' => TRUE),
    );
  }

  /**
   * Get header for a lost of this type.
   */  
  function get_list_header() {
    $out = array();
    foreach ($this->get_list_column_info() as $key => $col) {
      $out[] = $col['title'];
    }
    return $out;
  }

  /**
   * Get a row of data to be used in a list of items of this type.
   */  
  function get_list_row() {
    $out = array();
    foreach ($this->get_list_column_info() as $key => $col) {
      $out[$key] = empty($col['html']) ? check_plain($this->get($key)) : $this->get($key);
      if (isset($col['class'])) {
        $out[$key] = array('data' => $out[$key], 'class' => $col['class']);
      }
    }
    return $out;
  }

  /**
   * Get the rendered action links for a destination.
   */
  function get_actions() {
    $links = $this->get_action_links();
    return implode(" &nbsp; ", $links);
  }

  /**
   * Get the edit form for the item.
   */
  function edit_form() {
    $form = array();
    $form['item'] = array(
      '#type' => 'value',
      '#value' => $this,
    );
    $name = $this->get('name');
    $form['name'] = array(
      "#type" => "textfield",
      "#title" => t("!type name", array('!type' => $this->title_singular)),
      "#default_value" => empty($name) ? t('Untitled !type', array('!type' => $this->title_singular)) : $name,
      "#required" => TRUE,
    );
    $form['id'] = array(
      '#type' => 'value',
      '#value' => $this->get_id(),
    );

    $form['machine_name'] = array(
      '#type' => 'machine_name',
      '#default_value' => $this->get_id(),
      '#maxlength' => 255,
      '#machine_name' => array(
        'source' => array('name'),
        'exists' => 'backup_migrate_crud_item_exists',
      ),
    );

    $form['actions'] = array('#prefix' => '<div class="container-inline">', '#suffix' => '</div>', '#weight' => 99);
    $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save !type', array('!type' => t($this->singular))));
    $form['actions']['cancel'] = array('#value' => l(t('Cancel'), $this->get_settings_path()));
    return $form;
  }

  /**
   * Validate the edit form for the item.
   */
  function edit_form_validate($form, &$form_state) {
  }

  /**
   * Submit the edit form for the item.
   */
  function edit_form_submit($form, &$form_state) {
    $this->from_array($form_state['values']);
    $this->save();
    _backup_migrate_message('Your !type was saved', array('!type' => t($this->singular)));
  }

  /**
   * Get the message to send to the user when confirming the deletion of the item.
   */
  function delete_confirm_message() {
    return t('Are you sure you want to delete the !type %name?', array('!type' => t($this->singular), '%name' => $this->get('name')));
  }

  /**
   * Get the message to send to the user when confirming the deletion of the item.
   */
  function revert_confirm_message() {
    return t('Are you sure you want to revert the !type %name back to the default settings?', array('!type' => t($this->singular), '%name' => $this->get('name')));
  }

  /* Static Functions */ 
  /**
   * Get the menu items for manipulating this type.
   */
  function get_menu_items() {
    $path = $this->get_settings_path();

    $type = $this->type_name;
    $items[$path] = array(
      'title' => $this->title_plural,
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('crud', 'backup_migrate_crud_ui_list', TRUE, $this->type_name),
      'access arguments' => array('administer backup and migrate'),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
    );
    $items[$path .'/list'] = array(
      'title' => 'List !type',
      'title arguments' => array('!type' => t($this->title_plural)),
      'weight' => 1,
      'type' => MENU_DEFAULT_LOCAL_TASK,
    );
    $items[$path .'/add'] = array(
      'title' => 'Add !type',
      'title arguments' => array('!type' => t($this->title_singular)),
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('crud', 'backup_migrate_crud_ui_create', TRUE, $this->type_name),
      'access arguments' => array('administer backup and migrate'),
      'weight' => 2,
      'type' => MENU_LOCAL_ACTION,
    );
    $items[$path .'/delete'] = array(
      'title' => 'Delete !type',
      'title arguments' => array('!type' => t($this->title_singular)),
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('crud', 'backup_migrate_crud_ui_delete', TRUE, $this->type_name),
      'access arguments' => array('administer backup and migrate'),
      'type' => MENU_CALLBACK,
    );
    $items[$path .'/edit'] = array(
      'title' => 'Edit !type',
      'title arguments' => array('!type' => t($this->title_singular)),
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('crud', 'backup_migrate_crud_ui_edit', TRUE, $this->type_name),
      'access arguments' => array('administer backup and migrate'),
      'type' => MENU_CALLBACK,
    );
    $items[$path .'/export'] = array(
      'title' => 'Export !type',
      'title arguments' => array('!type' => t($this->title_singular)),
      'page callback' => 'backup_migrate_menu_callback',
      'page arguments' => array('crud', 'backup_migrate_crud_ui_export', TRUE, $this->type_name),
      'access arguments' => array('administer backup and migrate'),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }


  /**
   * Create a new items with the given input. Doesn't load the parameters, but could use them to determine what type to create.
   */
  function create($params = array()) {
    $type = get_class($this);
    return new $type($params);
  }

  /**
   * Get all of the given items.
   */
  function all_items() {
    static $cache = array();
    $items = array();

    // Get any items stored as a variable. This allows destinations to be defined in settings.php
    $defaults = (array)variable_get($this->db_table . '_defaults', array());
    foreach ($defaults as $info) {
      if (is_array($info) && $item = $this->create($info)) {
        $items[$item->get_id()] = $item;
      }
    }

    // Get the items from the db.
    $result = db_query("SELECT * FROM {{$this->db_table}}", array(), array('fetch' => PDO::FETCH_ASSOC));
    foreach ($result as $info) {
      $info = $this->decode_db_row($info);
      if ($item = $this->create($info)) {
        $item->storage = empty($items[$item->get_id()]) ? BACKUP_MIGRATE_STORAGE_DB : BACKUP_MIGRATE_STORAGE_OVERRIDEN;
        $items[$item->get_id()] = $item;
      }
    }

    // Allow other modules to declare destinations programatically.
    $default_items = module_invoke_all($this->db_table);

    // Get CTools exported versions.
    if (function_exists('ctools_include')) {
      ctools_include('export');
      $defaults = ctools_export_load_object($this->db_table);
      foreach ($defaults as $info) {
        $info = (array)$info;
        if (!empty($info) && $item = $this->create($info)) {
          $default_items[$item->get_id()] = $item;
        }
      }
    }

    // Get any items stored as a variable again to correctly mark overrides.
    $defaults = (array)variable_get($this->db_table . '_defaults', array());
    foreach ($defaults as $info) {
      if (is_array($info) && $item = $this->create($info)) {
        $default_items[] = $item;
      }
    }

    // Add the default items to the array or set the storage flag if they've already been overridden.
    foreach ($default_items as $item) {
      if (isset($items[$item->get_id()])) {
        $items[$item->get_id()]->storage = BACKUP_MIGRATE_STORAGE_OVERRIDEN;
      }
      else {
        $item->storage = BACKUP_MIGRATE_STORAGE_NONE;
        $items[$item->get_id()] = $item;
      }
    }

    // Allow other modules to alter the items. This should maybe be before the db override code above
    // but then the filters are not able to set defaults for missing values. Other modules should just
    // be careful not to overwrite the user's UI changes in an unexpected way.
    drupal_alter($this->db_table, $items);

    return $items;
  }

  /**
   * A particular item.
   */
  function item($item_id) {
    $items = $this->all_items();
    return !empty($items[$item_id]) ? $items[$item_id] : NULL;
  }

  /**
   * A particular item.
   */
  function item_exists($item_id) {
    $items = $this->all_items();
    return !empty($items[$item_id]);
  }
}
