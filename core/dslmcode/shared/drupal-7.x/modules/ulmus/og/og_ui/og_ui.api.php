<?php


/**
 * @file
 * Hooks provided by the Organic groups UI module.
 */

/**
 * @addtgrouproup hooks
 * @{
 */

/**
 * Add a menu item that should appear in the group admin page.
 */
function hook_og_ui_get_group_admin() {
  $items = array();
  $items['add_people'] = array(
    'title' => t('Add people'),
    'description' => t('Add group members.'),
    // The final URL will be "group/$entity_type/$etid/admin/people/add-user".
    'href' => 'admin/people/add-user',
  );

  return $items;
}

/**
 * Alter existing group admin menu items.
 *
 * @param $data
 *   The menu items passed by reference.
 * @param $gid
 *   The group being viewed.
 */
function hook_og_ui_get_group_admin_alter(&$data, $context) {
  // Hijack the add people to use a custom implementation.
  if (og_ui_user_access_group('add user', $context['entity_type'], $context['etid'])) {
    $data['add_people']['href'] = 'admin/people/mass-add-user-filter';
  }
}

/**
 * @} End of "addtgrouproup hooks".
 */