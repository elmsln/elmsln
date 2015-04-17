<?php

/**
 * @file
 * Authcache Panels cache plugin.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Authcache'),
  'description' => t('Authcache Panels. Panes are rendered using Ajax or ESI tags.'),
  'cache get' => 'authcache_panels_cache_get_cache',
  'cache set' => 'authcache_panels_cache_set_cache',
  'cache clear' => 'authcache_panels_cache_clear_cache',
  'settings form' => 'authcache_panels_cache_settings_form',
  'settings form submit' => 'authcache_panels_cache_settings_form_submit',
  'defaults' => array(
    'authcache' => array(
      'status' => 1,
      'perpage' => 1,
    ) + authcache_p13n_config_defaults(),
    'machine_name' => NULL,
  ),
);

/**
 * Get cached content.
 */
function authcache_panels_cache_get_cache($conf, $display, $args, $contexts, $pane = NULL) {
}

/**
 * Sets cached content.
 */
function authcache_panels_cache_set_cache($conf, $content, $display, $args, $contexts, $pane = NULL) {
}

/**
 * Clears cached content.
 *
 * Cache clears are always for an entire display, regardless of arguments.
 */
function authcache_panels_cache_clear_cache($display) {
}

/**
 * Settings form.
 */
function authcache_panels_cache_settings_form($conf, $display, $pid) {
  if ($pid !== 'display') {
    if (!isset($conf['machine_name'])) {
      $conf['machine_name'] = authcache_panels_pane_machine_name_generate($display, $pid);
    }
    $form['machine_name'] = array(
      '#type' => 'machine_name',
      '#default_value' => $conf['machine_name'],
      '#machine_name' => array(
        'exists' => 'authcache_panels_pane_machine_name_exists',
      ),
    );
    $form['authcache'] = array(
      '#type' => 'authcache_p13n_config',
      '#default_value' => $conf['authcache'],
    );
  }
  else {
    $form['authcache'] = array(
      '#markup' => '<p>' . t('Authcache currently does not support caching of whole displays. Only per content pane caching is possible for now.') . '</p>',
    );
  }
  return $form;
}

/**
 * Settings form submit callback.
 */
function authcache_panels_cache_settings_form_submit($form, &$form_state) {
}
