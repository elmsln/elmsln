<?php
/**
 * @file
 * ELMSLN standard installer functions
 */

/**
 * Initial standard preflight routine.
 */
function _elmsln_installer_preflight($makesection = FALSE) {
  // create a default section if this is a service
  if ($makesection) {
    // add in a master section
    _elmsln_installer_make_default_section();
  }
  // This isn't actually necessary as there are no node_access() entries,
  // but we run it to prevent the "rebuild node access" message from being
  // shown on install.
  node_access_rebuild();
}

/**
 * Set the default theme and some blocks correctly.
 */
function _elmsln_installer_theme($default_theme = 'foundation_access') {
  // Enable some default blocks.
  $admin_theme = 'adminimal';
  // TODO: figure out what to put into variable set. See below...
  //
  //variable_set('theme_adminimal_settings', array('sticky_actions' => 1));
  // disable all themes
  db_update('system')
    ->fields(array('status' => 0))
    ->condition('type', 'theme')
    ->execute();
  // enable $default_theme
  db_update('system')
    ->fields(array('status' => 1))
    ->condition('type', 'theme')
    ->condition('name', $default_theme)
    ->execute();
  // enable $admin_theme
  db_update('system')
    ->fields(array('status' => 1))
    ->condition('type', 'theme')
    ->condition('name', $admin_theme)
    ->execute();
  variable_set('theme_default', $default_theme);
  variable_set('admin_theme', $admin_theme);
  // activate admin theme when editing a node
  variable_set('node_admin_theme', '1');
  $blocks = array(
    array(
      'module' => 'system',
      'delta' => 'main',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'help',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => -10,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'main',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'help',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'help',
      'pages' => '',
      'cache' => -1,
    ),
  );
  // drop system / user blocks to ensure correct building
  db_delete('block')->condition('module', 'system')->execute();
  db_delete('block')->condition('module', 'user')->execute();
  // add in our blocks defined above
  $query = db_insert('block')->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'pages', 'cache'));
  foreach ($blocks as $block) {
    $query->values($block);
  }
  $query->execute();
}

/**
 * Give admin role all permissions and assigns it to user 1.
 */
function _elmsln_installer_admin_role() {
  // load admin role
  $admin_role = user_role_load_by_name('administrator');
  // ensure we got an administrator role though it should be impossible
  if (isset($admin_role->rid)) {
    // assign administrator role all permissions
    user_role_grant_permissions($admin_role->rid, array_keys(module_invoke_all('permission')));
    // Set this as the administrator role.
    variable_set('user_admin_role', $admin_role->rid);
    // Assign user 1 the "administrator" role.
    db_insert('users_roles')
      ->fields(array('uid' => 1, 'rid' => $admin_role->rid))
      ->execute();
  }
}

/**
 * Post install clean up.
 */
function _elmsln_installer_post_install_cleanup() {
  // in Aegir install processes, we need to init strongarm manually as a
  // separate page load isn't available to do this for us.
  if (function_exists('strongarm_init')) {
    strongarm_init();
  }
  // revert all features
  features_revert();
  // rebuild the menu
  menu_rebuild();
  // ignore any other install messages
  drupal_get_messages();
  // Rebuild key tables/caches
  drupal_flush_all_caches();
}

/**
 * Callback to generate a section node; used during profile install.
 */
function _elmsln_installer_make_default_section() {
  if (module_exists('cis_section')) {
    $node = new stdClass();
    $node->type = 'section';
    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;
    $node->uid = 1;
    $node->status = 1;
    $node->promote = 0;
    $node->revision = 1;
    $node->title = t('Master Section');
    // make up a random section id to make things happy but fake
    $node->field_section_id[LANGUAGE_NONE][0]['value'] = 'master';
    // mark this as inactive so it can sync with systems
    $node->field_cis_active[LANGUAGE_NONE][0]['value'] = 0;
    // build out via submit then save
    if($node = node_submit($node)) {
      node_save($node);
    }
    return $node;
  }
}
