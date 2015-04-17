<?php
/**
 * @file
 * API documentation for Authcache Panels module.
 */

/**
 * Declare panel displays and associated context providers.
 */
function hook_authcache_panels_base_fragments() {
  $base_fragments = array();

  foreach (mymodule_get_displays() as $did) {
    $base_fragments[$did] = array(
      'admin group' => t('Panels (by My Module)'),
      'panels context provider' => array(
        '#class' => 'MyModuleContextProvider',
        '#key' => 'panels',
        '#member_of' => 'context providers',
      ),
    );
  }

  array(
    'my_module' => $base_fragments,
  );
}


/**
 * Modify panels displays and context providers declared by other modules.
 */
function hook_authcache_panels_base_fragments_alter(&$base_fragment_groups) {
}
