<?php
/**
 * @file
 * Admin forms and pages for Authcache Form module.
 */

/**
 * Form API callback: Generate admin form.
 */
function authcache_form_admin($form, &$form_state) {
  $links = array(
    '!wikipedia_link' => 'http://en.wikipedia.org/wiki/Cross-site_request_forgery',
    '!owasp_link' => 'http://owasp.com/index.php/Cross-Site_Request_Forgery_(CSRF)_Prevention_Cheat_Sheet',
    '!so_link' => 'http://stackoverflow.com/questions/1845305/is-there-a-reason-to-put-tokens-on-a-search-form',
    '!cacheobject_link' => 'http://drupal.org/project/cacheobject',
  );

  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Help'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['help']['hint']['#markup'] = '<p>' . t('In Drupal every form is protected against Cross-site request forgery (CSRF/XSRF) attacks by default. The implementation follows the synchronizer token pattern favored by OWASP. In short whenever a user is logged-in into your site, a unique token gets embedded as a hidden input field into any form. Because this token is user-specific, authcache normally cannot cache a page for authenticated users when there is a form on it.') . '</p>' .
    '<p>' . t('It follows that if forms are visible on many pages &ndash; or even accross the whole site, the cache hit rate will suffer for authenticated users.') . '</p>' .
    '<p>' . t('More information on CSRF prevention is available on the following sites:') . '<ul>' .
    '<li>' . t('<a href="!wikipedia_link">Wikipedia: Cross-site request forgery</a>', $links) . '</li>' .
    '<li>' . t('<a href="!owasp_link">OWASP: Cross-Site Request Forgery (CSRF) Prevention Cheat Sheet</a>', $links) . '</li>' .
    '</ul>';

  // Token retrieval.
  $p13n_disabled = !module_exists('authcache_p13n');

  $form['config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Retrieve Form Tokens'),
    '#collapsible' => TRUE,
  );

  $form['config']['hint']['#markup'] = '<p>' . t('When the Authcache Personalization module is enabled, it is possible to retrieve the form token using either Ajax or an ESI request.') . '</p>';

  if ($p13n_disabled) {
    $form['config']['hint']['#markup'] .= '<strong>' . t('Enable Authcache Personalization along with Authcache Ajax and/or Authcache ESI modules in order to enable token retrieval.') . '</strong>';
  }

  $form['config']['authcache_form_roles'] = array(
    '#title' => t('Allowed roles'),
    '#description' => t('Allow token retrieval for the selected roles.'),
    '#type' => 'authcache_role_restrict',
    '#default_value' => variable_get('authcache_form_roles'),
    '#disabled' => $p13n_disabled,
    '#members_only' => FALSE,
  );

  // Form token derived from base form id.
  $form['base_id_token'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form token derived from base form id'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $module_info = system_get_info('module');
  $modules_with_base_forms = array();
  foreach (module_implements('forms') as $module) {
    $modules_with_base_forms[] = $module_info[$module]['name'];
  }
  $form['base_id_token']['hint']['#markup'] = '<p>' . t('Some forms are repeated over and over across a site, each one with a slightly different form-id. A good example is the commerce add-to-cart form. Instead of deriving the CSRF token from the unique form-id, the base-form id can be used, such that only one token needs to be generated for all forms having a common base form.') . '</p>';
  if (!empty($modules_with_base_forms)) {
    $form['base_id_token']['hint']['#markup'] .= '<p>' . t('The following modules implement base forms and therefore might be affected by this feature:') . ' ' . implode(', ', $modules_with_base_forms) . '</p>';
  }

  $form['base_id_token']['authcache_form_base_id_token'] = array(
    '#type' => 'textarea',
    '#title' => t('Base forms'),
    '#description' => t('Supply a list of base form-ids where CSRF tokens should be derived from. Defaults to "*", i.e. applied to all base forms.'),
    '#default_value' => variable_get('authcache_form_base_id_token', '*'),
  );

  // Ajax forms.
  $cacheobject_disabled = !module_exists('cacheobject');

  $form['formcache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form cache (Ajax forms)'),
    '#collapsible' => TRUE,
  );

  if ($cacheobject_disabled) {
    $form['formcache']['hint']['#markup'] = '<p>' . t('Ajax enabled forms rely on the form cache. However entries in the form cache expire after a hard coded period of 6 hours. When pages should be cached longer and Ajax forms are in use on them, they will stop working after that period.') . '</p> ' .
      '<p>' . t('In order to circumvent this problem you should install the <a href="!cacheobject_link">Cache Object API</a> module which allows the Authcache Forms module to extend that period to a user supplied value.', $links) . '</p>';
  }

  $form['formcache']['authcache_form_cache_lifespan'] = array(
    '#type' => 'authcache_duration_select',
    '#title' => t('Form cache expiry'),
    '#description' => t('The maximum time a form-prototype for Ajax forms remains in the form cache.'),
    '#durations' => array(21600, 86400, 604800, 2592000),
    '#default_value' => authcache_form_cache_lifespan(),
    '#disabled' => $p13n_disabled || $cacheobject_disabled,
  );

  // Token removal.
  $form['notoken'] = array(
    '#type' => 'fieldset',
    '#title' => t('Remove Form Token'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['notoken']['hint']['#markup'] = '<p>' . t('It is debatable whether search forms need to be protected against CSRF attacks at all, because there is little destructive potential caused by executing a search on behalf of another user.') . '</p>' .
    '<p>' . t('More information on CSRF prevention on search forms is available on the following site:') . '<ul>' .
    '<li>' . t('<a href="!so_link">stackoverflow.com: Is there a reason to put tokens on a serach form?</a>', $links) . '</li>' .
    '</ul>';

  $form['notoken']['authcache_form_notoken'] = array(
    '#type' => 'textarea',
    '#title' => t('Remove Form Token'),
    '#description' => t('Supply a list of form-ids where CSRF tokens should be removed. Note that removing CSRF protection will impact the security of your site. Only remove CSRF tokens from forms which are not used to submit content - e.g., search or filter forms. Never remove CSRF tokens from forms used to create content, like comment or node forms.'),
    '#default_value' => variable_get('authcache_form_notoken', ''),
  );

  $notoken_roles = authcache_get_roles();
  unset($notoken_roles[DRUPAL_ANONYMOUS_RID]);

  $form['notoken']['authcache_form_notoken_roles'] = array(
    '#title' => t('Allowed roles'),
    '#description' => t('Turn off CSRF protection of the forms specified above for the selected roles.'),
    '#type' => 'authcache_role_restrict',
    '#default_value' => variable_get('authcache_form_notoken_roles', array()),
    '#members_only' => TRUE,
  );

  return system_settings_form($form, $form_state);
}
