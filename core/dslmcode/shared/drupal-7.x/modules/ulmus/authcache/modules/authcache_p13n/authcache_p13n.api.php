<?php
/**
 * @file
 * Documentation for hooks provided by the authcache personalization module.
 */

/**
 * Declare markup fragments which contain personalized information.
 *
 * Return an associative array where the key represents the fragment id and the
 * value an array with the following keys:
 * - fragment': The name of the class used to build the markup. The class must
 *   implement the AuthcacheP13nFragmentInterface.
 * - fragment validator: (Optional) The name of the class used to validate the
 *   parameters for the fragment renderer. The class must implement the
 *   AuthcacheP13nFragmentValidator interface. If not given, the 'fragment'
 *   instance is used if it implements the interface mentioned before.
 * - fragment loader: (Optional) The name of the class used to load the
 *   necessary data. The class must implement the AuthcacheP13nFragmentLoader
 *   interface. If not given, the 'fragment' instance is used if it implements
 *   the interface mentioned before.
 * - fragment access: (Optional) The name of a class used to check access to
 *   the data. The class must implement the AuthcacheP13nFragmentAccess
 *   interface. If not given, the 'fragment' instance is used if it implements
 *   the interface mentioned before.
 * - cache maxage: (Optional) The number of seconds a rendered fragment should
 *   be cacheable in the users browser or in intermediate cache servers.
 * - cache granularity (Optional) A bitmask describing the criteria used to
 *   distinguish between multiple variants of a fragment. A combination of the
 *   following contstants can be used:
 *   - AuthcacheP13nCacheGranularity::PER_USER: Content is different for
 *     each session.
 *   - AuthcacheP13nCacheGranularity::PER_PAGE: Content changes when
 *     fragment is rendered on different pages.
 * - bootstrap phase: (Optional) The minimal bootstrap phase necessary to
 *   render the fragment. One of the DRUPAL_BOOTSTRAP_X constants.
 */
function hook_authcache_p13n_fragment() {
  return array(
    'form-token' => array(
      'fragment' => array(
        '#class' => 'AuthcacheFormTokenFragment',
      ),
    ),
  );
}

/**
 * Alter markup fragment definitions.
 *
 * @see hook_authcache_p13n_fragment()
 */
function hook_authcache_p13n_fragment_alter(&$info) {
  // Extend the maximal age for the form-token fragment to one week.
  $info['form-token']['cache maxage'] = 604800;
}

/**
 * Declare fragment assemblies containing personalized information.
 *
 * Return an associative array where the key represents the fragment assembly
 * id and the value an array with the following keys:
 *
 * - partial: An associative array with the following key-value pairs:
 *   - renderer: The name of the class used to build the markup. The class must
 *     implement the AuthcacheP13nFragmentInterface.
 *   - validator: (Optional) The name of the class used to validate the
 *     parameters for the fragment renderer. The class must implement the
 *     AuthcacheP13nFragmentValidator interface. If not given, the 'renderer'
 *     instance is used if it implements the interface mentioned before.
 *   - loader: (Optional) The name of the class used to load the
 *     necessary data. The class must implement the AuthcacheP13nFragmentLoader
 *     interface. If not given, the 'renderer' instance is used if it implements
 *     the interface mentioned before.
 *   - access: (Optional) The name of a class used to check access to
 *     the data. The class must implement the AuthcacheP13nFragmentAccess
 *     interface. If not given, the 'renderer' instance is used if it implements
 *     the interface mentioned before.
 * - cache maxage: (Optional) The number of seconds a rendered fragment should
 *   be cacheable in the users browser or in intermediate cache servers.
 * - cache granularity (Optional) A bitmask describing the criteria used to
 *   distinguish between multiple variants of a fragment. A combination of the
 *   following constants can be used:
 *   - AuthcacheP13nCacheGranularity::PER_USER: Content is different for
 *     each session.
 *   - AuthcacheP13nCacheGranularity::PER_PAGE: Content changes when
 *     fragment is rendered on different pages.
 * - bootstrap phase: (Optional) The minimal bootstrap phase necessary to
 *   render the fragment. One of the DRUPAL_BOOTSTRAP_X constants.
 */
function hook_authcache_p13n_assembly() {
  return array(
    'flags' => array(
      'admin name' => 'All flags',
      'admin group' => 'Flag',
      'admin description' => 'All flags on a page',
      'cache maxage' => 600,
      'bootstrap phase' => DRUPAL_BOOTSTRAP_FULL,
      'fragment f1' => array(
        '#class' => 'AuthcacheFlagFlagFragment',
        '#arguments' => array(
          'bookmarks',
        ),
        '#member_of' => 'partial f1',
        '#key' => 'renderer',
      ),
      'partial f1' => array(
        '#collection' => 'partial f1',
        '#member_of' => 'partials',
        '#key' => 'f1',
      ),
      'fragment f1' => array(
        '#class' => 'AuthcacheFlagFlagFragment',
        '#arguments' => array(
          'friends',
        ),
        '#member_of' => 'partial f2',
        '#key' => 'renderer',
      ),
      'partial f2' => array(
        '#collection' => 'partial f2',
        '#member_of' => 'partials',
        '#key' => 'f2',
      ),
    ),
  );
}

/**
 * Modify fragment assemblies declared by other modules.
 *
 * @see hook_authcache_p13n_assembly()
 */
function hook_authcache_p13n_assembly_alter(&$info) {
}

/**
 * Declare settings containing personalized information.
 *
 * Return an associative array where the key represents the setting id and the
 * value an array with the following keys:
 * - setting': The name of the class used to build the markup. The class must
 *   implement the AuthcacheP13nSetting interface.
 * - setting validator: (Optional) The name of the class used to validate the
 *   parameters for the setting renderer. The class must implement the
 *   AuthcacheP13nSettingValidator interface. If not given, the 'setting'
 *   instance is used if it implements the interface mentioned before.
 * - setting loader: (Optional) The name of the class used to load the
 *   necessary data. The class must implement the AuthcacheP13nSettingLoader
 *   interface. If not given, the 'setting' instance is used if it implements
 *   the interface mentioned before.
 * - setting access: (Optional) The name of a class used to check access to
 *   the data. The class must implement the AuthcacheP13nSettingAccess
 *   interface. If not given, the 'setting' instance is used if it implements
 *   the interface mentioned before.
 * - cache maxage: (Optional) The number of seconds a rendered setting should
 *   be cacheable in the users browser or in intermediate cache servers.
 * - cache granularity (Optional) A bitmask describing the criteria used to
 *   distinguish between multiple variants of a setting. A combination of the
 *   following contstants can be used:
 *   - AuthcacheP13nCacheGranularity::PER_USER: Content is different for
 *     each session.
 *   - AuthcacheP13nCacheGranularity::PER_PAGE: Content changes when
 *     setting is rendered on different pages.
 * - bootstrap phase: (Optional) The minimal bootstrap phase necessary to
 *   render the setting. One of the DRUPAL_BOOTSTRAP_X constants.
 */
function hook_authcache_p13n_setting() {
  return array(
    'authcache-contact' => array(
      'setting' => array(
        '#class' => 'AuthcacheContactSetting',
      ),
      'setting target' => 'authcacheContact',
      'cache maxage' => 86400,
    ),
  );
}

/**
 * Modify setting declared by other modules.
 *
 * @see hook_authcache_p13n_setting()
 */
function hook_authcache_p13n_setting_alter(&$info) {
}

/**
 * Called when the external cache for personalized fragments should be cleared.
 */
function hook_authcache_p13n_session_invalidate() {
}

/**
 * Declare a client method used to defer retrieval of personalized content.
 *
 * Return an associative array where the key represents the client method
 * (normally equal to the module name) and the value is an associative array
 * with the following key-value pairs:
 * - title: The human readable description of the client method.
 * - enabled: Whether or not this client can be used for content delivered
 *   during the current request.
 */
function hook_authcache_p13n_client() {
  return array(
    'authcache_ajax' => array(
      'title' => t('Ajax'),
      'enabled' => !empty($_COOKIE['has_js']),
    ),
  );
}

/**
 * Modify client methods declared by other modules.
 *
 * @see hook_authcache_p13n_client()
 */
function hook_authcache_p13n_client_alter(&$info) {
  global $base_root;

  // Never use ESI on localhost.
  if (stristr($base_root, 'localhost')) {
    $info['authcache_esi']['enabled'] = FALSE;
  }
}

/**
 * Change the order of client methods for a given operation.
 *
 * @param array &$clients
 *   Associative array of client records indexed by client-id. Each record is
 *   an array with key-value pairs. Assign an integer value to the weight key
 *   to influence the client order.
 *
 * @param string $type
 *   One of "fragment", "setting" or "assembly".
 *
 * @param string $id
 *   The fragment id (e.g., "form").
 *
 * @param string $param
 *   The parameter for the personalization operation.
 *
 * @see authcache_p13n_client_get_preferred()
 */
function hook_authcache_p13n_client_order_alter(&$clients, $type, $id, $param) {
  if ($type === 'fragment' && $id === 'form') {
    // Prefer esi over ajax for form-token retrieval.
    $clients['authcache_esi']['weight'] = -99;
    $clients['authcache_ajax']['weight'] = 0;
  }
}

/**
 * Change the fallback markup inserted when no client is available.
 *
 * @param string &$markup
 *   The markup replacing the rendered fragment.
 * @param string $method
 *   The fallback method, e.g., 'hide', 'cancel'
 * @param array $context
 *   An associative array containing the following key-value pairs:
 *   - type: One of 'fragment', 'setting', 'assembly' or 'partial'.
 *   - id: The fragment-, setting-, assembly-, partial-identifier.
 *   - param: The parameter for this instance.
 *   - clients: An array of weighted client definitions supplied to the
 *     theming-function.
 */
function hook_authcache_p13n_client_fallback_alter(&$markup, $method, $context) {
  switch ($method) {
    case 'cancel':
      authcache_cancel(t('No client for %type %id', array('%type' => $context['type'], '%id' => $context['id'])));
      break;
  }
}

/**
 * Return resource record with default request blueprint.
 *
 * @see authcache_p13n_authcache_p13n_base_request()
 */
function hook_authcache_p13n_base_request() {
}

/**
 * Modify resource record for default request.
 *
 * @see hook_authcache_p13n_base_request()
 */
function hook_authcache_p13n_base_request_alter(&$resource) {
}

/**
 * Return AuthcacheP13nRequestHandler instances.
 *
 * @see authcache_p13n_authcache_p13n_request()
 */
function hook_authcache_p13n_request() {
}

/**
 * Modify request-array.
 *
 * @see hook_authcache_p13n_request()
 */
function hook_authcache_p13n_request_alter(&$resources) {
}

/**
 * Define additional object factory resource processors.
 *
 * @see AuthcacheP13nObjectFactory
 */
function hook_authcache_p13n_resource_processors() {
}

/**
 * Alter resource processor definitions.
 *
 * @see hook_authcache_p13n_resource_processors()
 */
function hook_authcache_p13n_resource_processors_alter(&$processors) {
}
