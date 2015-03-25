<?php

/**
 * @file
 * Contains the flag_flag class.
 * Flag type classes use an object oriented style inspired by that
 * of Views 2.
 */

/**
 * This abstract class represents a flag, or, in Views 2 terminology,
 * "a handler".
 *
 * This is the base class for all flag implementations. Notable derived
 * classes are flag_node and flag_comment.
 *
 * There are several ways to obtain a flag handler, operating at different
 * levels.
 *
 * To load an existing flag that's defined in database or code, use one of:
 * - flag_get_flag(), the main flag API function.
 * - flag_load(), the loader for hook_menu().
 * - flag_get_flags(), the main API function for loading all flags. This calls
 *   flag_get_default_flags() to get flags in code.
 *
 * The above all use factory methods to instantiate the object for the flag and
 * load in its settings from configuration. The factory methods are:
 * - flag_flag::factory_by_row(), creates a flag handler from a database row.
 *   This is used by all the API functions above.
 * - flag_flag::factory_by_array(), creates a flag handler from a configuration
 *   array. This is used by flag_get_default_flags() and the flag import form.
 * - flag_flag::factory_by_entity_type(), creates an empty flag handler for the
 *   given entity type. This is used when a new or dummy flag handler is
 *   required and there is no configuration yet.
 *
 * The factory methods in turn all call the low-level function
 * flag_create_handler(), which obtains the correct handler for the flag, or if
 * that can't be found, the special handler flag_broken. Finally, this calls
 * $flag->construct() on the new handler object.
 */
class flag_flag {

  /**
   * The database ID.
   *
   * NULL for flags that haven't been saved to the database yet.
   *
   * @var integer
   */
  var $fid = NULL;

  /**
   * The entity type this flag works with.
   *
   * @var string
   */
  var $entity_type = NULL;

  /**
   * The flag's "machine readable" name.
   *
   * @var string
   */
  var $name = '';

  /**
   * The human-readable title for this flag.
   *
   * @var string
   */
  var $title = '';

  /**
   * Whether this flag state should act as a single toggle to all users.
   *
   * @var bool
   */
  var $global = FALSE;

  /**
   * The sub-types, AKA bundles, this flag applies to.
   *
   * This may be an empty array to indicate all types apply.
   *
   * @var array
   */
  var $types = array();

  /**
   * The roles array. This can be populated by fetch_roles() when needed.
   */
  var $roles = array(
    'flag' => array(),
    'unflag' => array(),
  );

  /**
   * An associative array containing textual errors that may be created during
   * validation.
   *
   * The array keys should reflect the type of error being set. At this time,
   * the only "special" behavior related to the array keys is that
   * drupal_access_denied() is called when the key is 'access-denied' and
   * javascript is disabled.
   *
   * @var array
   */
  public $errors = array();

  /**
   * Creates a flag from a database row. Returns it.
   *
   * This is static method.
   *
   * The reason this isn't a non-static instance method --like Views's init()--
   * is because the class to instantiate changes according to the 'entity_type'
   * database column. This design pattern is known as the "Single Table
   * Inheritance".
   */
  static function factory_by_row($row) {
    $flag = flag_create_handler($row->entity_type);

    // Lump all data unto the object...
    foreach ($row as $field => $value) {
      $flag->$field = $value;
    }
    // ...but skip the following two.
    unset($flag->options, $flag->type);

    // Populate the options with the defaults.
    $options = (array) unserialize($row->options);
    $options += $flag->options();

    // Make the unserialized options accessible as normal properties.
    foreach ($options as $option => $value) {
      $flag->$option = $value;
    }

    if (!empty($row->type)) {
      // The loop loading from the database should further populate this
      // property.
      $flag->types[] = $row->type;
    }

    return $flag;
  }

  /**
   * Create a complete flag (except an FID) from an array definition.
   */
  static function factory_by_array($config) {
    // Allow for flags with a missing entity type.
    $config += array(
      'entity_type' => FALSE,
    );
    $flag = flag_create_handler($config['entity_type']);

    foreach ($config as $option => $value) {
      $flag->$option = $value;
    }

    if (isset($config['locked']) && is_array($config['locked'])) {
      $flag->locked = drupal_map_assoc($config['locked']);
    }

    return $flag;
  }

  /**
   * Another factory method. Returns a new, "empty" flag; e.g., one suitable for
   * the "Add new flag" page.
   */
  static function factory_by_entity_type($entity_type) {
    return flag_create_handler($entity_type);
  }

  /**
   * Declares the options this flag supports, and their default values.
   *
   * Derived classes should want to override this.
   */
  function options() {
    $options = array(
      // The text for the "flag this" link for this flag.
      'flag_short' => '',
      // The description of the "flag this" link.
      'flag_long' => '',
      // Message displayed after flagging an entity.
      'flag_message' => '',
      // Likewise but for unflagged.
      'unflag_short' => '',
      'unflag_long' => '',
      'unflag_message' => '',
      'unflag_denied_text' => '',
      // The link type used by the flag, as defined in
      // hook_flag_link_type_info().
      'link_type' => 'toggle',
      'weight' => 0,
    );

    // Merge in options from the current link type.
    $link_type = $this->get_link_type();
    $options = array_merge($options, $link_type['options']);

    // Allow other modules to change the flag options.
    drupal_alter('flag_options', $options, $this);
    return $options;
  }
  /**
   * Provides a form for setting options.
   *
   * Derived classes should want to override this.
   */
  function options_form(&$form) {
  }

  /**
   * Default constructor. Loads the default options.
   */
  function construct() {
    $options = $this->options();
    foreach ($options as $option => $value) {
      $this->$option = $value;
    }
  }

  /**
   * Load this flag's role data from permissions.
   *
   * Loads an array of roles into the flag, where each key is an action ('flag'
   * and 'unflag'), and each value is a flat array of role ids which may perform
   * that action.
   *
   * This should only be used when a complete overview of a flag's permissions
   * is needed. Use $flag->access or $flag->user_access() instead.
   */
  function fetch_roles() {
    $actions = array('flag', 'unflag');
    foreach ($actions as $action) {
      // Build the permission string.
      $permission = "$action $this->name";
      // We want a flat array of rids rather than $rid => $role_name.
      $this->roles[$action] = array_keys(user_roles(FALSE, $permission));
    }
  }

  /**
   * Update the flag with settings entered in a form.
   */
  function form_input($form_values) {
    // Load the form fields indiscriminately unto the flag (we don't care about
    // stray FormAPI fields because we aren't touching unknown properties
    // anyway).
    foreach ($form_values as $field => $value) {
      $this->$field = $value;
    }
    $this->types = array_values(array_filter($this->types));
    // Clear internal titles cache:
    $this->get_title(NULL, TRUE);
  }

  /**
   * Validates this flag's options.
   *
   * @return
   *   A list of errors encountered while validating this flag's options.
   */
  function validate() {
    // TODO: It might be nice if this used automatic method discovery rather
    // than hard-coding the list of validate functions.
    return array_merge_recursive(
      $this->validate_name(),
      $this->validate_access()
    );
  }

  /**
   * Validates that the current flag's name is valid.
   *
   * @return
   *   A list of errors encountered while validating this flag's name.
   */
  function validate_name() {
    $errors = array();

    // Ensure a safe machine name.
    if (!preg_match('/^[a-z_][a-z0-9_]*$/', $this->name)) {
      $errors['name'][] = array(
        'error' => 'flag_name_characters',
        'message' => t('The flag name may only contain lowercase letters, underscores, and numbers.'),
      );
    }
    // Ensure the machine name is unique.
    $flag = flag_get_flag($this->name);
    if (!empty($flag) && (!isset($this->fid) || $flag->fid != $this->fid)) {
      $errors['name'][] = array(
        'error' => 'flag_name_unique',
        'message' => t('Flag names must be unique. This flag name is already in use.'),
      );
    }

    return $errors;
  }

  /**
   * Validates that the current flag's access settings are valid.
   */
  function validate_access() {
    $errors = array();

    // Require an unflag access denied message a role is not allowed to unflag.
    if (empty($this->unflag_denied_text)) {
      foreach ($this->roles['flag'] as $key => $rid) {
        if ($rid && empty($this->roles['unflag'][$key])) {
          $errors['unflag_denied_text'][] = array(
            'error' => 'flag_denied_text_required',
            'message' => t('The "Unflag not allowed text" is required if any user roles are not allowed to unflag.'),
          );
          break;
        }
      }
    }

    // Do not allow unflag access without flag access.
    foreach ($this->roles['unflag'] as $key => $rid) {
      if ($rid && empty($this->roles['flag'][$key])) {
        $errors['roles'][] = array(
          'error' => 'flag_roles_unflag',
          'message' => t('Any user role that has the ability to unflag must also have the ability to flag.'),
        );
        break;
      }
    }

    return $errors;
  }

  /**
   * Fetches, possibly from some cache, an entity this flag works with.
   */
  function fetch_entity($entity_id, $object_to_remember = NULL) {
    static $cache = array();
    if (isset($object_to_remember)) {
      $cache[$entity_id] = $object_to_remember;
    }
    if (!array_key_exists($entity_id, $cache)) {
      $entity = $this->_load_entity($entity_id);
      $cache[$entity_id] = $entity ? $entity : NULL;
    }
    return $cache[$entity_id];
  }

  /**
   * Loads an entity this flag works with.
   * Derived classes must implement this.
   *
   * @abstract
   * @private
   * @static
   */
  function _load_entity($entity_id) {
    return NULL;
  }

  /**
   * Store an object in the flag handler's cache.
   *
   * This is needed because otherwise fetch_object() loads the object from the
   * database (by calling _load_entity()), whereas sometimes we want to fetch
   * an object that hasn't yet been saved to the database. Subsequent calls to
   * fetch_entity() return the remembered object.
   *
   * @param $entity_id
   *  The ID of the object to cache.
   * @param $object
   *  The object to cache.
   */
  function remember_entity($entity_id, $object) {
    $this->fetch_entity($entity_id, $object);
  }

  /**
   * @defgroup access Access control
   * @{
   */

  /**
   * Returns TRUE if the flag applies to the given entity.
   *
   * Derived classes must implement this.
   *
   * @abstract
   */
  function applies_to_entity($entity) {
    return FALSE;
  }

  /**
   * Returns TRUE if the flag applies to the entity with the given ID.
   *
   * This is a convenience method that simply loads the object and calls
   * applies_to_entity(). If you already have the object, don't call
   * this function: call applies_to_entity() directly.
   */
  function applies_to_entity_id($entity_id) {
    return $this->applies_to_entity($this->fetch_entity($entity_id));
  }

  /**
   * Provides permissions for this flag.
   *
   * @return
   *  An array of permissions for hook_permission().
   */
  function get_permissions() {
    return array(
      "flag $this->name" => array(
        'title' => t('Flag %flag_title', array(
          '%flag_title' => $this->title,
        )),
      ),
      "unflag $this->name" => array(
        'title' => t('Unflag %flag_title', array(
          '%flag_title' => $this->title,
        )),
      ),
    );
  }

  /**
   * Determines whether the user has the permission to use this flag.
   *
   * @param $action
   *   (optional) The action to test, either "flag" or "unflag". If none given,
   *   "flag" will be tested, which is the minimum permission to use a flag.
   * @param $account
   *   (optional) The user object. If none given, the current user will be used.
   *
   * @return
   *   Boolean TRUE if the user is allowed to flag/unflag. FALSE otherwise.
   *
   * @see flag_permission()
   */
  function user_access($action = 'flag', $account = NULL) {
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }

    // Anonymous user can't use this system unless Session API is installed.
    if ($account->uid == 0 && !module_exists('session_api')) {
      return FALSE;
    }

    $permission_string = "$action $this->name";
    return user_access($permission_string, $account);
  }

  /**
   * Determines whether the user may flag, or unflag, the given entity.
   *
   * This method typically should not be overridden by child classes. Instead
   * they should implement type_access(), which is called by this method.
   *
   * @param $entity_id
   *   The entity ID to flag/unflag.
   * @param $action
   *   The action to test. Either 'flag' or 'unflag'. Leave NULL to determine
   *   by flag status.
   * @param $account
   *   The user on whose behalf to test the flagging action. Leave NULL for the
   *   current user.
   *
   * @return
   *   Boolean TRUE if the user is allowed to flag/unflag the given entity.
   *   FALSE otherwise.
   */
  function access($entity_id, $action = NULL, $account = NULL) {
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }

    if (isset($entity_id) && !$this->applies_to_entity_id($entity_id)) {
      // Flag does not apply to this entity.
      return FALSE;
    }

    if (!isset($action)) {
      $uid = $account->uid;
      $sid = flag_get_sid($uid);
      $action = $this->is_flagged($entity_id, $uid, $sid) ? 'unflag' : 'flag';
    }

    // Base initial access on the user's basic permission to use this flag.
    $access = $this->user_access($action, $account);

    // Check for additional access rules provided by sub-classes.
    $child_access = $this->type_access($entity_id, $action, $account);
    if (isset($child_access)) {
      $access = $child_access;
    }

    // Allow modules to disallow (or allow) access to flagging.
    // We grant access to the flag if both of the following conditions are met:
    // - No modules say to deny access.
    // - At least one module says to grant access.
    // If no module specified either allow or deny, we fall back to the
    // default access check above.
    $module_access = module_invoke_all('flag_access', $this, $entity_id, $action, $account);
    if (in_array(FALSE, $module_access, TRUE)) {
      $access = FALSE;
    }
    elseif (in_array(TRUE, $module_access, TRUE)) {
      // WARNING: This allows modules to bypass the default access check!
      $access = TRUE;
    }

    return $access;
  }

  /**
   * Determine access to multiple objects.
   *
   * Similar to user_access() but works on multiple IDs at once. Called in the
   * pre_render() stage of the 'Flag links' field within Views to find out where
   * that link applies. The reason we do a separate DB query, and not lump this
   * test in the Views query, is to make 'many to one' tests possible without
   * interfering with the rows, and also to reduce the complexity of the code.
   *
   * This method typically should not be overridden by child classes. Instead
   * they should implement type_access_multiple(), which is called by this
   * method.
   *
   * @param $entity_ids
   *   The array of entity IDs to check. The keys are the entity IDs, the
   *   values are the actions to test: either 'flag' or 'unflag'.
   * @param $account
   *   (optional) The account for which the actions will be compared against.
   *   If left empty, the current user will be used.
   *
   * @return
   *   An array whose keys are the object IDs and values are booleans indicating
   *   access.
   *
   * @see hook_flag_access_multiple()
   */
  function access_multiple($entity_ids, $account = NULL) {
    $account = isset($account) ? $account : $GLOBALS['user'];
    $access = array();

    // First check basic user access for this action.
    foreach ($entity_ids as $entity_id => $action) {
      $access[$entity_id] = $this->user_access($entity_ids[$entity_id], $account);
    }

    // Check for additional access rules provided by sub-classes.
    $child_access = $this->type_access_multiple($entity_ids, $account);
    if (isset($child_access)) {
      foreach ($child_access as $entity_id => $entity_access) {
        if (isset($entity_access)) {
          $access[$entity_id] = $entity_access;
        }
      }
    }

    // Merge in module-defined access.
    foreach (module_implements('flag_access_multiple') as $module) {
      $module_access = module_invoke($module, 'flag_access_multiple', $this, $entity_ids, $account);
      foreach ($module_access as $entity_id => $entity_access) {
        if (isset($entity_access)) {
          $access[$entity_id] = $entity_access;
        }
      }
    }

    return $access;
  }

  /**
   * Implements access() implemented by each child class.
   *
   * @abstract
   *
   * @return
   *  FALSE if access should be denied, or NULL if there is no restriction to
   *  be made. This should NOT return TRUE.
   */
  function type_access($entity_id, $action, $account) {
    return NULL;
  }

  /**
   * Implements access_multiple() implemented by each child class.
   *
   * @abstract
   *
   * @return
   *  An array keyed by entity ids, whose values represent the access to the
   *  corresponding entity. The access value may be FALSE if access should be
   *  denied, or NULL (or not set) if there is no restriction to  be made. It
   *  should NOT be TRUE.
   */
  function type_access_multiple($entity_ids, $account) {
    return array();
  }

  /**
   * @} End of "defgroup access".
   */

  /**
   * Given an entity, returns its ID.
   * Derived classes must implement this.
   *
   * @abstract
   */
  function get_entity_id($entity) {
    return NULL;
  }

  /**
   * Utility function: Checks whether a flag applies to a certain type, and
   * possibly subtype, of entity.
   *
   * @param $entity_type
   *   The type of entity being checked, such as "node".
   * @param $content_subtype
   *   The subtype being checked. For entities this will be the bundle name (the
   *   node type in the case of nodes).
   *
   * @return
   *   TRUE if the flag is enabled for this type and subtype.
   */
  function access_entity_enabled($entity_type, $content_subtype = NULL) {
    $entity_type_matches = ($this->entity_type == $entity_type);
    $sub_type_matches = FALSE;
    if (!isset($content_subtype) || !count($this->types)) {
      // Subtype automatically matches if we're not asked about it,
      // or if the flag applies to all subtypes.
      $sub_type_matches = TRUE;
    }
    else {
      $sub_type_matches = in_array($content_subtype, $this->types);
    }
    return $entity_type_matches && $sub_type_matches;
  }

  /**
   * Determine whether the flag should show a flag link in entity links.
   *
   * Derived classes are likely to implement this.
   *
   * @param $view_mode
   *   The view mode of the entity being displayed.
   *
   * @return
   *   A boolean indicating whether the flag link is to be shown in entity
   *   links.
   */
  function shows_in_entity_links($view_mode) {
    return FALSE;
  }

  /**
   * Returns TRUE if this flag requires anonymous user cookies.
   */
  function uses_anonymous_cookies() {
    global $user;
    return $user->uid == 0 && variable_get('cache', 0);
  }

  /**
   * Flags, or unflags, an item.
   *
   * @param $action
   *   Either 'flag' or 'unflag'.
   * @param $entity_id
   *   The ID of the item to flag or unflag.
   * @param $account
   *   The user on whose behalf to flag. Leave empty for the current user.
   * @param $skip_permission_check
   *   Flag the item even if the $account user don't have permission to do so.
   * @param $flagging
   *   (optional) This method works in tandem with Drupal's Field subsystem.
   *   Pass in a Flagging entity if you want operate on it as well. This may be
   *   used either of the following cases:
   *   - to save field data on a new Flagging entity at the same time as
   *     flagging an entity. In this case, using Entity API's entity_create()
   *     is recommended, although the Flagging entity may also be created
   *     directly as a new stdClass object.
   *   - to update field data an existing flagging. The $action parameter should
   *     be set to 'flag'. The Flagging entity will need to be loaded first with
   *     flagging_load().
   *  As with Drupal core API functions for saving entities, no validation of
   *  Field API fields is performed here. It is the responsibility of the caller
   *  to take care of Field API validation, using either
   *  field_attach_form_validate() or field_attach_validate().
   *
   * @return
   *   FALSE if some error occured (e.g., user has no permission, flag isn't
   *   applicable to the item, etc.), TRUE otherwise.
   */
  function flag($action, $entity_id, $account = NULL, $skip_permission_check = FALSE, $flagging = NULL) {
    // Get the user.
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }

    // Check access and applicability.
    if (!$skip_permission_check) {
      if (!$this->access($entity_id, $action, $account)) {
        $this->errors['access-denied'] = t('You are not allowed to flag, or unflag, this content.');
        // User has no permission to flag/unflag this object.
        return FALSE;
      }
    }
    else {
      // We are skipping permission checks. However, at a minimum we must make
      // sure the flag applies to this entity type:
      if (!$this->applies_to_entity_id($entity_id)) {
        $this->errors['entity-type'] = t('This flag does not apply to this entity type.');
        return FALSE;
      }
    }

    if (($this->errors = module_invoke_all('flag_validate', $action, $this, $entity_id, $account, $skip_permission_check, $flagging))) {
      return FALSE;
    }

    // Find out which user id to use.
    $uid = $this->global ? 0 : $account->uid;

    // Find out which session id to use.
    if ($this->global) {
      $sid = 0;
    }
    else {
      $sid = flag_get_sid($uid, TRUE);
      // Anonymous users must always have a session id.
      if ($sid == 0 && $account->uid == 0) {
        $this->errors['session'] = t('Internal error: You are anonymous but you have no session ID.');
        return FALSE;
      }
    }

    // @todo: Discuss: Core wraps everything in a try { }, should we?

    $existing_flagging_id = $this->_is_flagged($entity_id, $uid, $sid);
    $flagged = (bool) $existing_flagging_id;

    // Ensure we have a Flagging entity and it is correctly formed.
    if (isset($flagging)) {
      // We were given a Flagging entity.
      // Ensure that it has the uid and sid that we were also given.
      $flagging->uid = $uid;
      $flagging->sid = $sid;

      // This is an ugly hack to preserve previous behaviour.
      $flagging->given_as_parameter = TRUE;
    }
    else {
      // We were not given a Flagging entity.
      if ($flagged) {
        // Load the existing Flagging entity.
        $flagging = flagging_load($existing_flagging_id);
      }
      else {
        // Construct a new Flagging entity to flag with.
        $flagging = $this->new_flagging($entity_id, $uid, $sid);
      }
    }

    // Perform the flagging or unflagging of this flag.
    if ($action == 'unflag') {
      if ($flagged) {
        $this->flagging_delete($flagging, $entity_id, $account);
      }
      // We do nothing in the case of an attempt to unflag something that isn't
      // actually flagged.
    }
    elseif ($action == 'flag') {
      if (!$flagged) {
        $this->flagging_insert($flagging, $entity_id, $account);
      }
      else {
        $this->flagging_update($flagging, $entity_id, $account);
      }
    }

    return TRUE;
  }

  /**
   * Create a new Flagging to flag an entity.
   *
   * @param $flagging
   *  The flagging entity that is to be saved.
   * @param $entity_id
   *  The entity ID of entity being flagged.
   * @param $account
   *  The account performing the flagging.
   */
  private function flagging_insert($flagging, $entity_id, $account) {
    if ($this->uses_anonymous_cookies()) {
      $this->_flag_anonymous($entity_id);
    }

    // Invoke presave hooks.
    field_attach_presave('flagging', $flagging);
    // Invoke hook_entity_presave().
    module_invoke_all('entity_presave', $flagging, 'flagging');

    // Set the timestamp.
    $flagging->timestamp = REQUEST_TIME;

    // Save the flagging entity.
    drupal_write_record('flagging', $flagging);

    // Clear various caches; we don't want code running after us to report
    // wrong counts or false flaggings.
    drupal_static_reset('flag_get_user_flags');
    drupal_static_reset('flag_get_entity_flags');
    // Despite being named in the same pattern as the count API functions, these
    // query the {flagging} table, so are reset here.
    drupal_static_reset('flag_get_entity_flag_counts');
    drupal_static_reset('flag_get_user_flag_counts');

    $this->_increase_count($entity_id);
    // We're writing out a flagging entity even when we aren't passed one
    // (e.g., when flagging via JavaScript toggle links); in this case
    // Field API will assign the fields their default values.

    // Invoke insert hooks.
    field_attach_insert('flagging', $flagging);
    // Invoke hook_entity_insert().
    module_invoke_all('entity_insert', $flagging, 'flagging');

    module_invoke_all('flag_flag', $this, $entity_id, $account, $flagging);
    // Invoke Rules event.
    if (module_exists('rules')) {
      $this->invoke_rules_event('flag', $flagging, $entity_id, $account);
    }
  }

  /**
   * Update a Flagging.
   *
   * @param $flagging
   *  The flagging entity that is being updated.
   * @param $entity_id
   *  The entity ID of entity the flagging is on.
   * @param $account
   *  The account performing the action.
   */
  private function flagging_update($flagging, $entity_id, $account) {
    // Invoke presave hooks.
    // This is technically still a presave, even though the {flagging} table
    // itself is not changed.
    field_attach_presave('flagging', $flagging);
    // Invoke hook_entity_presave().
    module_invoke_all('entity_presave', $flagging, 'flagging');

    // This check exists solely to preserve previous behaviour with re-flagging.
    // TODO: consider removing it.
    if (!empty($flagging->given_as_parameter)) {
      field_attach_update('flagging', $flagging);
      // Update the cache.
      entity_get_controller('flagging')->resetCache();
      // Invoke hook_entity_update().
      // Since there are no fields on the {flagging} table that can be
      // meaningfully changed, we don't perform an update on it. However, this
      // technically still counts as updating the flagging entity, since we update
      // its fields.
      module_invoke_all('entity_update', $flagging, 'flagging');
    }
  }

  /**
   * Unflag an entity by deleting a Flagging.
   *
   * @param $flagging
   *  The flagging entity that is to be removed.
   * @param $entity_id
   *  The entity ID of entity being unflagged.
   * @param $account
   *  The account performing the unflagging.
   */
  private function flagging_delete($flagging, $entity_id, $account) {
    if ($this->uses_anonymous_cookies()) {
      $this->_unflag_anonymous($entity_id);
    }

    $transaction = db_transaction();
    try {
      // Note the order: We decrease the count first so hooks have accurate
      // data, then invoke hooks, then delete the flagging entity.
      $this->_decrease_count($entity_id);
      module_invoke_all('flag_unflag', $this, $entity_id, $account, $flagging);
      // Invoke Rules event.
      if (module_exists('rules')) {
        $this->invoke_rules_event('unflag', $flagging, $entity_id, $account);
      }

      // Invoke hook_entity_delete().
      module_invoke_all('entity_delete', $flagging, 'flagging');
      // Delete field data.
      field_attach_delete('flagging', $flagging);

      // Delete the flagging entity.
      db_delete('flagging')->condition('flagging_id', $flagging->flagging_id)->execute();

      // Remove from the cache.
      entity_get_controller('flagging')->resetCache();

      // Clear various caches; we don't want code running after us to report
      // wrong counts or false flaggings.
      drupal_static_reset('flag_get_user_flags');
      drupal_static_reset('flag_get_entity_flags');
      // Despite being named in the same pattern as the count API functions, these
      // query the {flagging} table, so are reset here.
      drupal_static_reset('flag_get_entity_flag_counts');
      drupal_static_reset('flag_get_user_flag_counts');
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('flag', $e);
      throw $e;
    }
  }

  /**
   * Invoke a Rules event in reaction to a flagging or unflagging.
   *
   * @param $action
   *   Either 'flag' or 'unflag'.
   * @param $flagging
   *  The flagging entity that is either newly created or about to be deleted.
   * @param $entity_id
   *  The entity ID of entity being flagged or unflagged.
   * @param $account
   *  The account performing the action.
   */
  protected function invoke_rules_event($action, $flagging, $entity_id, $account) {
    // We only support flags on entities: do nothing in this class.
    // See flag_entity::invoke_rules_event().
    return;
  }

  /**
   * Construct a new, empty flagging entity object.
   *
   * @param mixed $entity_id
   *   The unique identifier of the object being flagged.
   * @param int $uid
   *   (optional) The user id of the user doing the flagging.
   * @param mixed $sid
   *   (optional) The user SID (provided by Session API) who is doing the
   *   flagging. The SID is 0 for logged in users.
   *
   * @return stdClass
   *   The returned object has at least the 'flag_name' property set, which
   *   enables Field API to figure out the bundle, but it's your responsibility
   *   to eventually populate 'entity_id' and 'flagging_id'.
   */
  function new_flagging($entity_id = NULL, $uid = NULL, $sid = NULL) {
    return (object) array(
      'flagging_id' => NULL,
      'flag_name' => $this->name,
      'fid' => $this->fid,
      'entity_type' => $this->entity_type,
      'entity_id' => $entity_id,
      'uid' => $uid,
      'sid' => $sid,
      // The timestamp is not set until this is saved.
    );
  }

  /**
   * Determines if a certain user has flagged this object.
   *
   * Thanks to using a cache, inquiring several different flags about the same
   * item results in only one SQL query.
   *
   * @param $uid
   *   (optional) The user ID whose flags we're checking. If none given, the
   *   current user will be used.
   *
   * @return
   *   TRUE if the object is flagged, FALSE otherwise.
   */
  function is_flagged($entity_id, $uid = NULL, $sid = NULL) {
    return (bool) $this->get_flagging_record($entity_id, $uid, $sid);
  }

  /**
   * Returns the flagging record.
   *
   * This method returns the "flagging record": the {flagging} record that
   * exists for each flagged item (for a certain user). If the item isn't
   * flagged, returns NULL. This method could be useful, for example, when you
   * want to find out the 'flagging_id' or 'timestamp' values.
   *
   * Thanks to using a cache, inquiring several different flags about the same
   * item results in only one SQL query.
   *
   * Parameters are the same as is_flagged()'s.
   */
  function get_flagging_record($entity_id, $uid = NULL, $sid = NULL) {
    $uid = $this->global ? 0 : (!isset($uid) ? $GLOBALS['user']->uid : $uid);
    $sid = $this->global ? 0 : (!isset($sid) ? flag_get_sid($uid) : $sid);

    // flag_get_user_flags() does caching.
    $user_flags = flag_get_user_flags($this->entity_type, $entity_id, $uid, $sid);
    return isset($user_flags[$this->name]) ? $user_flags[$this->name] : NULL;
  }

  /**
   * Similar to is_flagged() excepts it returns the flagging entity.
   */
  function get_flagging($entity_id, $uid = NULL, $sid = NULL) {
    if (($record = $this->get_flagging_record($entity_id, $uid, $sid))) {
      return flagging_load($record->flagging_id);
    }
  }

  /**
   * Determines if a certain user has flagged this object.
   *
   * You probably shouldn't call this raw private method: call the
   * is_flagged() method instead.
   *
   * This method is similar to is_flagged() except that it does direct SQL and
   * doesn't do caching. Use it when you want to not affect the cache, or to
   * bypass it.
   *
   * @return
   *   If the object is flagged, returns the value of the 'flagging_id' column.
   *   Else, returns FALSE.
   *
   * @private
   */
  function _is_flagged($entity_id, $uid, $sid) {
    return db_select('flagging', 'fc')
      ->fields('fc', array('flagging_id'))
      ->condition('fid', $this->fid)
      ->condition('uid', $uid)
      ->condition('sid', $sid)
      ->condition('entity_id', $entity_id)
      ->execute()
      ->fetchField();
  }

  /**
   * Increases the flag count for an object and clears the static counts cache.
   *
   * @param $entity_id
   *   For which item should the count be increased.
   * @param $number
   *   The amount of counts to increasing. Defaults to 1.
   *
   * @private
   */
  function _increase_count($entity_id, $number = 1) {
    db_merge('flag_counts')
      ->key(array(
        'fid' => $this->fid,
        'entity_id' => $entity_id,
      ))
      ->fields(array(
        'entity_type' => $this->entity_type,
        'count' => $number,
        'last_updated' => REQUEST_TIME,
      ))
      ->updateFields(array(
        'last_updated' => REQUEST_TIME,
      ))
      ->expression('count', 'count + :inc', array(':inc' => $number))
      ->execute();

    // Reset the static cache of flag counts, so code running after this gets
    // correct counts.
    drupal_static_reset('flag_get_counts');
    drupal_static_reset('flag_get_flag_counts');
  }

  /**
   * Decreases the flag count for an object and clears the static counts cache.
   *
   * @param $entity_id
   *   For which item should the count be descreased.
   * @param $number
   *   The amount of counts to decrease. Defaults to 1.
   *
   * @private
   */
  function _decrease_count($entity_id, $number = 1) {
    // Delete rows with count 0, for data consistency and space-saving.
    // Done before the db_update() to prevent out-of-bounds errors on "count".
    db_delete('flag_counts')
      ->condition('fid', $this->fid)
      ->condition('entity_id', $entity_id)
      ->condition('count', $number, '<=')
      ->execute();

    // Update the count with the new value otherwise.
    db_update('flag_counts')
      ->expression('count', 'count - :inc', array(':inc' => $number))
      ->fields(array(
        'last_updated' => REQUEST_TIME,
      ))
      ->condition('fid', $this->fid)
      ->condition('entity_id', $entity_id)
      ->execute();

    // Reset the static cache of flag counts, so code running after this gets
    // correct counts.
    drupal_static_reset('flag_get_counts');
    drupal_static_reset('flag_get_flag_counts');
  }

  /**
   * Set a cookie for anonymous users to record their flagging.
   *
   * @private
   */
  function _flag_anonymous($entity_id) {
    $storage = FlagCookieStorage::factory($this);
    $storage->flag($entity_id);
  }

  /**
   * Remove the cookie for anonymous users to record their unflagging.
   *
   * @private
   */
  function _unflag_anonymous($entity_id) {
    $storage = FlagCookieStorage::factory($this);
    $storage->unflag($entity_id);
  }

  /**
   * Returns the number of times an item is flagged.
   *
   * Thanks to using a cache, inquiring several different flags about the same
   * item results in only one SQL query.
   */
  function get_count($entity_id) {
    $counts = flag_get_counts($this->entity_type, $entity_id);
    return isset($counts[$this->name]) ? $counts[$this->name] : 0;
  }

  /**
   * Returns the number of items a user has flagged.
   *
   * For global flags, pass '0' as the user ID and session ID.
   */
  function get_user_count($uid, $sid = NULL) {
    if (!isset($sid)) {
      $sid = flag_get_sid($uid);
    }
    return db_select('flagging', 'fc')->fields('fc', array('flagging_id'))
      ->condition('fid', $this->fid)
      ->condition('uid', $uid)
      ->condition('sid', $sid)
      ->countQuery()
      ->execute()
      ->fetchField();
  }

  /**
   * Processes a flag label for display. This means language translation and
   * token replacements.
   *
   * You should always call this function and not get at the label directly.
   * E.g., do `print $flag->get_label('title')` instead of `print
   * $flag->title`.
   *
   * @param $label
   *   The label to get, e.g. 'title', 'flag_short', 'unflag_short', etc.
   * @param $entity_id
   *   The ID in whose context to interpret tokens. If not given, only global
   *   tokens will be substituted.
   *
   * @return
   *   The processed label.
   */
  function get_label($label, $entity_id = NULL) {
    if (!isset($this->$label)) {
      return;
    }
    $label = t($this->$label);
    if (strpos($label, '[') !== FALSE) {
      $label = $this->replace_tokens($label, array(), array('sanitize' => FALSE), $entity_id);
    }
    return filter_xss_admin($label);
  }

  /**
   * Get the link type for this flag.
   */
  function get_link_type() {
    $link_types = flag_get_link_types();
    return (isset($this->link_type) && isset($link_types[$this->link_type])) ? $link_types[$this->link_type] : $link_types['normal'];
  }

  /**
   * Replaces tokens in a label. Only the 'global' token context is recognized
   * by default, so derived classes should override this method to add all
   * token contexts they understand.
   */
  function replace_tokens($label, $contexts, $options, $entity_id) {
    if (strpos($label , 'flagging:') !== FALSE) {
      if (($flagging = $this->get_flagging($entity_id))) {
        $contexts['flagging'] = $flagging;
      }
    }
    return token_replace($label, $contexts, $options);
  }

  /**
   * Returns the token types this flag understands in labels. These are used
   * for narrowing down the token list shown in the help box to only the
   * relevant ones.
   *
   * Derived classes should override this.
   */
  function get_labels_token_types() {
    return array('flagging');
  }

  /**
   * A convenience method for getting the flag title.
   *
   * `$flag->get_title()` is shorthand for `$flag->get_label('title')`.
   */
  function get_title($entity_id = NULL, $reset = FALSE) {
    static $titles = array();
    if ($reset) {
      $titles = array();
    }
    $slot = intval($entity_id); // Convert NULL to 0.
    if (!isset($titles[$this->fid][$slot])) {
      $titles[$this->fid][$slot] = $this->get_label('title', $entity_id);
    }
    return $titles[$this->fid][$slot];
  }

  /**
   * Returns a 'flag action' object. It exists only for the sake of its
   * informative tokens. Currently, it's utilized only for the 'mail' action.
   *
   * Derived classes should populate the 'content_title' and 'content_url'
   * slots.
   */
  function get_flag_action($entity_id) {
    $flag_action = new stdClass();
    $flag_action->flag = $this->name;
    $flag_action->entity_type = $this->entity_type;
    $flag_action->entity_id = $entity_id;
    return $flag_action;
  }

  /**
   * Returns an array of errors set during validation.
   */
  function get_errors() {
    return $this->errors;
  }

  /**
   * @addtogroup actions
   * @{
   * Methods that can be overridden to support Actions.
   */

  /**
   * Returns an array of all actions that are executable with this flag.
   */
  function get_valid_actions() {
    $actions = module_invoke_all('action_info');
    foreach ($actions as $callback => $action) {
      if ($action['type'] != $this->entity_type && !in_array('any', $action['triggers'])) {
        unset($actions[$callback]);
      }
    }
    return $actions;
  }

  /**
   * Returns objects the action may possibly need. This method should return at
   * least the 'primary' object the action operates on.
   *
   * This method is needed because get_valid_actions() returns actions that
   * don't necessarily operate on an object of a type this flag manages. For
   * example, flagging a comment may trigger an 'Unpublish post' action on a
   * node; So the comment flag needs to tell the action about some node.
   *
   * Derived classes must implement this.
   *
   * @abstract
   */
  function get_relevant_action_objects($entity_id) {
    return array();
  }

  /**
   * @} End of "addtogroup actions".
   */

  /**
   * @addtogroup views
   * @{
   * Methods that can be overridden to support the Views module.
   */

  /**
   * Returns information needed for Views integration. E.g., the Views table
   * holding the flagged object, its primary key, and various labels. See
   * derived classes for examples.
   *
   * @static
   */
  function get_views_info() {
    return array();
  }

  /**
   * @} End of "addtogroup views".
   */

  /**
   * Saves a flag to the database. It is a wrapper around update() and insert().
   */
  function save() {
    // Allow the 'global' property to be a boolean, particularly when defined in
    // hook_flag_default_flags(). Without this, a value of FALSE gets casted to
    // an empty string which violates our schema. Other boolean properties are
    // fine, as they are serialized.
    $this->global = (int) $this->global;

    if (isset($this->fid)) {
      $this->update();
      $this->is_new = FALSE;
    }
    else {
      $this->insert();
      $this->is_new = TRUE;
    }
    // Clear the page cache for anonymous users.
    cache_clear_all('*', 'cache_page', TRUE);
  }

  /**
   * Saves an existing flag to the database. Better use save().
   */
  function update() {
    db_update('flag')->fields(array(
      'name' => $this->name,
      'title' => $this->title,
      'global' => $this->global,
      'options' => $this->get_serialized_options()))
      ->condition('fid', $this->fid)
      ->execute();
    db_delete('flag_types')->condition('fid', $this->fid)->execute();
    foreach ($this->types as $type) {
      db_insert('flag_types')->fields(array(
        'fid' => $this->fid,
        'type' => $type))
        ->execute();
    }
  }

  /**
   * Saves a new flag to the database. Better use save().
   */
  function insert() {
    $this->fid = db_insert('flag')
      ->fields(array(
        'entity_type' => $this->entity_type,
        'name' => $this->name,
        'title' => $this->title,
        'global' => $this->global,
        'options' => $this->get_serialized_options(),
      ))
      ->execute();
    foreach ($this->types as $type) {
      db_insert('flag_types')
        ->fields(array(
          'fid' => $this->fid,
          'type' => $type,
        ))
        ->execute();
    }
  }

  /**
   * Options are stored serialized in the database.
   */
  function get_serialized_options() {
    $option_names = array_keys($this->options());
    $options = array();
    foreach ($option_names as $option) {
      $options[$option] = $this->$option;
    }
    return serialize($options);
  }

  /**
   * Deletes a flag from the database.
   */
  function delete() {
    db_delete('flag')->condition('fid', $this->fid)->execute();
    db_delete('flagging')->condition('fid', $this->fid)->execute();
    db_delete('flag_types')->condition('fid', $this->fid)->execute();
    db_delete('flag_counts')->condition('fid', $this->fid)->execute();
    module_invoke_all('flag_delete', $this);
  }

  /**
   * Returns TRUE if this flag's declared API version is compatible with this
   * module.
   *
   * An "incompatible" flag is one exported (and now being imported or exposed
   * via hook_flag_default_flags()) by a different version of the Flag module.
   * An incompatible flag should be treated as a "black box": it should not be
   * saved or exported because our code may not know to handle its internal
   * structure.
   */
  function is_compatible() {
    if (isset($this->fid)) {
      // Database flags are always compatible.
      return TRUE;
    }
    else {
      if (!isset($this->api_version)) {
        $this->api_version = 1;
      }
      return $this->api_version == FLAG_API_VERSION;
    }
  }

  /**
   * Finds the "default flag" corresponding to this flag.
   *
   * Flags defined in code ("default flags") can be overridden. This method
   * returns the default flag that is being overridden by $this. Returns NULL
   * if $this overrides no default flag.
   */
  function find_default_flag() {
    if ($this->fid) {
      $default_flags = flag_get_default_flags(TRUE);
      if (isset($default_flags[$this->name])) {
        return $default_flags[$this->name];
      }
    }
  }

  /**
   * Reverts an overriding flag to its default state.
   *
   * Note that $this isn't altered. To see the reverted flag you'll have to
   * call flag_get_flag($this->name) again.
   *
   * @return
   *   TRUE if the flag was reverted successfully; FALSE if there was an error;
   *   NULL if this flag overrides no default flag.
   */
  function revert() {
    if (($default_flag = $this->find_default_flag())) {
      if ($default_flag->is_compatible()) {
        $default_flag = clone $default_flag;
        $default_flag->fid = $this->fid;
        $default_flag->save();
        drupal_static_reset('flag_get_flags');
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
  }

  /**
   * Disable a flag provided by a module.
   */
  function disable() {
    if (isset($this->module)) {
      $flag_status = variable_get('flag_default_flag_status', array());
      $flag_status[$this->name] = FALSE;
      variable_set('flag_default_flag_status', $flag_status);
    }
  }

  /**
   * Enable a flag provided by a module.
   */
  function enable() {
    if (isset($this->module)) {
      $flag_status = variable_get('flag_default_flag_status', array());
      $flag_status[$this->name] = TRUE;
      variable_set('flag_default_flag_status', $flag_status);
    }
  }

  /**
   * Returns administrative menu path for carrying out some action.
   */
  function admin_path($action) {
    if ($action == 'edit') {
      // Since 'edit' is the default tab, we omit the action.
      return FLAG_ADMIN_PATH . '/manage/' . $this->name;
    }
    else {
      return FLAG_ADMIN_PATH . '/manage/' . $this->name . '/' . $action;
    }
  }

  /**
   * Renders a flag/unflag link.
   *
   * This is a wrapper around theme('flag') that channels the call to the right
   * template file.
   *
   * @param $action
   *  The action the link is about to carry out, either "flag" or "unflag".
   * @param $entity_id
   *  The ID of the object to flag.
   * @param $variables = array()
   *  An array of further variables to pass to theme('flag'). For the full list
   *  of parameters, see flag.tpl.php. Of particular interest:
   *  - after_flagging: Set to TRUE if this flag link is being displayed as the
   *    result of a flagging action.
   *  - errors: An array of error messages.
   *
   * @return
   *  The HTML for the flag link.
   */
  function theme($action, $entity_id, $variables = array()) {
    static $js_added = array();
    global $user;

    $after_flagging = !empty($variables['after_flagging']);

    // If the flagging user is anonymous, set a boolean for the benefit of
    // JavaScript code. Currently, only our "anti-crawlers" mechanism uses it.
    if ($user->uid == 0 && !isset($js_added['anonymous'])) {
      $js_added['anonymous'] = TRUE;
      drupal_add_js(array('flag' => array('anonymous' => TRUE)), 'setting');
    }

    // If the flagging user is anonymous and the page cache is enabled, we
    // update the links through JavaScript.
    if ($this->uses_anonymous_cookies() && !$after_flagging) {
      if ($this->global) {
        // In case of global flags, the JavaScript template is to contain
        // the opposite of the current state.
        $js_action = ($action == 'flag' ? 'unflag' : 'flag');
      }
      else {
        // In case of non-global flags, we always show the "flag!" link,
        // and then replace it with the "unflag!" link through JavaScript.
        $js_action = 'unflag';
        $action = 'flag';
      }
      if (!isset($js_added[$this->name . '_' . $entity_id])) {
        $js_added[$this->name . '_' . $entity_id] = TRUE;
        $js_template = theme($this->theme_suggestions(), array(
          'flag' => $this,
          'action' => $js_action,
          'entity_id' => $entity_id,
          'after_flagging' => $after_flagging,
        ));
        drupal_add_js(array('flag' => array('templates' => array($this->name . '_' . $entity_id => $js_template))), 'setting');
      }
    }

    return theme($this->theme_suggestions(), array(
      'flag' => $this,
      'action' => $action,
      'entity_id' => $entity_id,
    ) + $variables);
  }

  /**
   * Provides an array of possible themes to try for a given flag.
   */
  function theme_suggestions() {
    $suggestions = array();
    $suggestions[] = 'flag__' . $this->name;
    $suggestions[] = 'flag__' . $this->link_type;
    $suggestions[] = 'flag';
    return $suggestions;
  }

  /**
   * A shortcut function to output the link URL.
   */
  function _flag_url($path, $fragment = NULL, $absolute = TRUE) {
    return url($path, array('fragment' => $fragment, 'absolute' => $absolute));
  }
}

/**
 * A dummy flag to be used where the real implementation can't be found.
 */
class flag_broken extends flag_flag {
  function options_form(&$form) {
    drupal_set_message(t("The module providing this flag wasn't found, or this flag type, %type, isn't valid.", array('%type' => $this->entity_type)), 'error');
    $form = array();
  }
}
