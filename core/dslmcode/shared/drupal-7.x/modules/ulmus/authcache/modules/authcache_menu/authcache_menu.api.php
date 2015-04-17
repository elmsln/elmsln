<?php
/**
 * @file
 * API documentation for Authcache Menu hooks.
 */

/**
 * Return invariant menu access callbacks.
 *
 * Declare a list of menu access callbacks which are guaranteed to return the
 * same result for each user having the same set of roles. By comparing this
 * access callback whitelist with the entries from the menu_router table, a
 * list of tab root paths is derived. When a page is rendered, its tab root is
 * looked up in the tab root blacklist. If a matching entry is found this means
 * that the set of displayed tabs is not guaranteed to be the same for all
 * users with the same authcache key. Therefore tabs need to be loaded using a
 * personalization fragment (i.e. using Ajax or ESI).
 */
function hook_authcache_menu_invariant_access_callbacks() {
  return array(
    '0',
    '1',
    'user_access',
    'user_is_anonymous',
    'user_is_logged_in',
    'user_register_access',
    'search_is_active',
  );
}

/**
 * Modify the list of invariant menu access callbacks.
 */
function hook_authcache_menu_invariant_access_callbacks_alter(&$callbacks) {
}

/**
 * Modify the list of tab root paths where fragment substitution is necessary.
 */
function hook_authcache_menu_tab_root_blacklist_alter(&$tab_roots, $type_mask) {
  if ($type_mask & MENU_IS_LOCAL_TASK) {
    // If no node access modules are present and no cacheable role has an
    // 'edit own X content' permission, it is save to cache the tabs on the
    // node/X pages.
    unset($tab_roots['node/%']);
  }
}
