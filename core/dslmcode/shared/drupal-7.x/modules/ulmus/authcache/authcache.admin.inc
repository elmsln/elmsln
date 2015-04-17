<?php

/**
 * @file
 * Admin forms and pages.
 */

/**
 * Main Authcache configuration form.
 */
function authcache_admin_config($form, &$form_state) {
  drupal_set_title(t('Authcache Configuration'));

  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Authcache Roles'),
    '#collapsible' => TRUE,
  );
  $form['roles']['authcache_roles'] = array(
    '#title' => t('Enable caching for specified user roles'),
    '#description' => t('If no roles are selected, Authcache page caching will not be enabled. Unchecked roles will never be cached.'),
    '#type' => 'checkboxes',
    '#options' => authcache_get_roles(TRUE),
    '#default_value' => variable_get('authcache_roles', array()),
  );

  $form['key'] = array(
    '#type' => 'fieldset',
    '#title' => t('Key Management'),
    '#collapsible' => TRUE,
  );

  $session_cookie_lifetime = (int) ini_get('session.cookie_lifetime');
  if ($session_cookie_lifetime > 0) {
    $session_period = format_interval($session_cookie_lifetime);
  }
  else {
    $session_period = t('Temporary');
  }
  $session_period_option = t('Same as Session (@period)', array('@period' => $session_period));
  // @ignore sniffer_array_array_longlinedeclaration
  $durations = array(0, 600, 3600, 10800, 43200, 86400, 259200, 604800, 1209600);
  $form['key']['key_lifetime'] = array(
    '#type' => 'authcache_duration_select',
    '#title' => t('Key lifetime'),
    '#default_value' => variable_get('authcache_key_lifetime'),
    '#durations' => $durations,
    '#empty_option' => $session_period_option,
    '#empty_value' => 'session',
    '#zero_duration' => t('Temporary'),
    '#description' => t('Select <em>Temporary</em> if keys shold last for one browser session (when using Cookies) or keys should be removed during cron runs.'),
  );

  $form['adv'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
  );
  $form['adv']['noajax'] = array(
    '#type' => 'checkbox',
    '#title' => t("Don't cache Drupal Ajax requests"),
    '#default_value' => variable_get('authcache_noajax', 0),
    '#description' => t('Note that most Ajax callbacks issued by Drupal core and contrib modules use POST requests. As a result they are not cacheable in the first place. A notable exception is the autocomplete callback.'),
  );
  $form['adv']['http200'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only cache HTTP 200 OK pages (exclude 404, 403, etc)'),
    '#default_value' => variable_get('authcache_http200', 0),
    '#description' => t("It's recommended to cache all Drupal pages, though error response pages can be excluded if required."),
  );
  $form['adv']['su'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow caching for superuser (uid = 1)'),
    '#default_value' => variable_get('authcache_su', 0),
    '#description' => t('Specify whether pages should also be cached for the superuser.'),
  );
  $form['adv']['mimetype'] = array(
    '#type' => 'textarea',
    '#title' => t('Cacheable content-types'),
    '#description' => t('Specify which content-types can be cached.'),
    '#default_value' => variable_get('authcache_mimetype', AUTHCACHE_MIMETYPE_DEFAULT),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save & clear cached pages'),
  );

  // Status messages.
  $modules = module_implements('authcache_backend_cache_save');
  if (empty($modules)) {
    drupal_set_message(t('No cache backend module enabled. See <a href="@url">README.txt</a>.', array('@url' => base_path() . drupal_get_path('module', 'authcache') . '/README.txt')), 'error');
  }

  if (!variable_get('page_compression', TRUE)) {
    drupal_set_message(t('Note: Page compression is not enabled!  It is strongly recommend that you <a href="@url">turn this setting on</a> through Drupal to allow for faster page response times.', array('@url' => url('admin/config/development/performance'))), 'warning');
  }

  return $form;
}


/**
 * Authcache config form submit.
 */
function authcache_admin_config_validate($form, &$form_state) {

}

/**
 * Authcache config form submit.
 */
function authcache_admin_config_submit($form, &$form_state) {
  // Roles.
  $cache_roles = drupal_map_assoc(array_filter($form_state['values']['authcache_roles']));

  // Figure out key lifetime.
  if ($form_state['values']['key_lifetime'] === 'session') {
    variable_del('authcache_key_lifetime');
  }
  else {
    variable_set('authcache_key_lifetime', $form_state['values']['key_lifetime']);
  }

  // Delete variable if not in use.
  foreach (array('http200', 'su', 'noajax', 'mimetype') as $key) {
    if ($value = $form_state['values'][$key]) {
      variable_set("authcache_{$key}", $value);
    }
    else {
      variable_del("authcache_{$key}");
    }
  }

  variable_set('authcache_roles', $cache_roles);

  drupal_set_message(t('Your Authcache settings have been saved.'));

  cache_clear_all('*', 'cache_page', TRUE);
  drupal_set_message(t('Cached pages cleared.'));
}


/**
 * Add new page caching rule to form (part of ajax).
 */
function _authcache_pagecache_form($delta, $details, $count) {
  $form['#tree'] = TRUE;

  // Cacheability settings.
  $options = array(t('Cache every page except the listed pages.'), t('Cache only the listed pages.'));
  $description = t("To delete this ruleset, leave the textbox empty. Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '%blog' for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
    '%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  if (user_access('use PHP for settings')) {
    $options[] = t('Cache pages for which the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
    $description .= t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can severely break your Drupal site.', array('%php' => '<?php ?>'));
  }
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Caching Ruleset #%delta', array('%delta' => $delta + 1)),
    '#collapsible' => TRUE,
  );
  $form['fieldset']['option'] = array(
    '#type' => 'radios',
    '#title' => t('Cache specified pages'),
    '#options' => $options,
    '#default_value' => $details['option'],
  );

  $form['fieldset']['pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#description' => $description,
    '#default_value' => $details['pages'],
  );
  $form['fieldset']['noadmin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exclude Admin pages'),
    '#description' => t('Do not cache administrative pages.'),
    '#default_value' => $details['noadmin'],
  );
  $form['fieldset']['roles'] = array(
    '#title' => 'Apply to these roles',
    '#type' => 'authcache_role_restrict',
    '#default_value' => $details['roles'],
  );

  if ($count > 1) {
    $form['fieldset']['remove_rule'] = array(
      '#type' => 'submit',
      '#value' => t('Delete ruleset #@delta', array('@delta' => $delta + 1)),
      '#submit' => array('authcache_admin_pagecaching_remove_one'),
      '#ajax' => array(
        'callback' => 'authcache_admin_pagecaching_ajax_callback',
        'wrapper' => 'ajax-wrapper',
      ),
      '#authcache_rule_id' => $delta,
    );
  }

  return $form;

}

/**
 * Page caching rules form.
 */
function authcache_admin_pagecaching($form, &$form_state) {
  drupal_set_title(t('Authcache Page Caching Settings'));

  if (!count(authcache_get_roles())) {
    drupal_set_message(t('You must first select roles to cache before defining page caching setting.'), 'error');
    return $form;
  }

  $form['ajax_wrapper'] = array(
    '#tree' => FALSE,
    '#prefix' => '<div class="clear-block" id="ajax-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['rules'])) {
    $form_state['rules'] = variable_get('authcache_pagecaching', _authcache_default_pagecaching());
  }

  $form['ajax_wrapper']['ajax']['#tree'] = TRUE;
  $count = count($form_state['rules']);
  foreach ($form_state['rules'] as $delta => $detail) {
    $form['ajax_wrapper']['ajax'][$delta] = _authcache_pagecache_form($delta, $detail, $count);
  }

  $form['ajax_wrapper']['add_rule'] = array(
    '#type' => 'submit',
    '#value' => t('Add ruleset'),
    '#submit' => array('authcache_admin_pagecaching_add_one'),
    '#ajax' => array(
      'callback' => 'authcache_admin_pagecaching_ajax_callback',
      'wrapper' => 'ajax-wrapper',
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save & clear cached pages'),
    '#prefix' => '<br/><hr size="1"><br/>',
  );

  return $form;
}

/**
 * Page caching rules form submit.
 */
function authcache_admin_pagecaching_submit($form, &$form_state) {
  $pagecaching = array();

  foreach ($form_state['values']['ajax'] as $key => $ray) {
    $values = $ray['fieldset'];
    if ($values['pages']) {
      $pagecaching[] = $values;
    }
    $effective_roles = authcache_get_role_restrict_roles($values['roles']);
    if (empty($effective_roles)) {
      drupal_set_message(t('Ruleset #%key is disabled since no roles are associated with it.', array('%key' => ($key + 1))), 'warning');
    }
  }

  if (!empty($pagecaching)) {
    variable_set('authcache_pagecaching', $pagecaching);
  }
  else {
    variable_del('authcache_pagecaching');
  }

  drupal_set_message(t('Your page caching settings have been saved.'));
  cache_clear_all();
  drupal_set_message(t('Cached pages cleared.'));
}

/**
 * Callback for ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the names in it.
 */
function authcache_admin_pagecaching_ajax_callback($form, $form_state) {
  return $form['ajax_wrapper'];
}

/**
 * Submit handler for the add button.
 *
 * Appends a new item to the end of the rules array.
 */
function authcache_admin_pagecaching_add_one($form, &$form_state) {
  list($default_rule) = _authcache_default_pagecaching();
  $form_state['rules'][] = $default_rule;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the remove button.
 *
 * Removes the item specified in the #authcache_rule_id attribute specified in
 * the triggering_element.
 */
function authcache_admin_pagecaching_remove_one($form, &$form_state) {
  if (isset($form_state['triggering_element']['#authcache_rule_id'])) {
    unset($form_state['rules'][$form_state['triggering_element']['#authcache_rule_id']]);
  }
  $form_state['rebuild'] = TRUE;
}
