<?php
/**
 * @file
 * Administrative interface for the authcache personalization module.
 */

/**
 * Display a list of available routes and frontcontroller settings.
 */
function authcache_p13n_admin_routes($form, &$form_state) {
  $router = authcache_p13n_request_get_router();
  $resources = authcache_p13n_request_resources();

  $form['help'] = array(
    '#title' => t('Frontcontroller'),
    '#type' => 'fieldset',
  );
  $form['help']['description'] = array(
    '#markup' =>
    '<p>' . t('The personalization frontcontroller is responsible for dispatching Ajax / ESI requests to an appropriate handler class and serving fragments to the browser or to a reverse caching proxy server.') . '</p>' .
    '<p>' . t('The table below lists all defined routes. The second table shows important variables and their values. Normally those settings need not to be changed. If this is nontheless necessary, customization may be done through <code>settings.php</code> file.') . '</p>',
  );

  $variables = array(
    'authcache_p13n_frontcontroller_path' => array(
      'title' => t('Front controller path'),
      'description' => t('The path to the frontcontroller script used to serve personalized content. By copying the safe frontcontroller script into the drupal root directory, it is possible to reduce the URL length. See the README.txt for more information.'),
      'value' => variable_get('authcache_p13n_frontcontroller_path', drupal_get_path('module', 'authcache_p13n') . '/frontcontroller/authcache.php'),
    ),
    'authcache_p13n_checkheader' => array(
      'title' => t('Check header flag'),
      'description' => t('Specifies whether the X-Authcache header should be examined on incomming requests to the personalization frontcontroller in order to prevent XSS attacks'),
      'value' => variable_get('authcache_p13n_checkheader', TRUE) ? t('Yes') : t('No'),
    ),
    'authcache_p13n_router' => array(
      'title' => t('Router class'),
      'description' => t('The class used to dispatch incomming personalization requests to appropriate handler objects.'),
      'value' => variable_get('authcache_p13n_router', 'AuthcacheP13nDefaultRequestRouter'),
    ),
    'authcache_p13n_default_request_router_autorebuild' => array(
      'title' => t('Autorebuild router'),
      'description' => t('Specifies whether the request router should try to rebuild the routing information when a request handler is missing'),
      'value' => variable_get('authcache_p13n_default_request_router_autorebuild', TRUE) ? t('Yes') : t('No'),
    ),
  );

  $header = array(
    t('Route ID'),
    t('Request handler'),
    t('URL generator'),
    t('Route exists'),
    '',
  );
  $rows = array();
  foreach ($resources as $route_id => $resource) {
    $rows[] = array(
      $route_id,
      $resource['handler']['#class'],
      $resource['url generator']['#class'],
      authcache_p13n_request_exists($route_id) ? t('Yes') : t('No'),
      l(t('Details'), 'admin/config/system/authcache/p13n/frontcontroller/route/' . $route_id),
    );
  }

  $form['routes'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  $header = array(t('Variable'), t('Value and description'));
  $rows = array();
  foreach ($variables as $varname => $record) {
    $rows[] = array(
      array(
        'valign' => 'top',
        'rowspan' => 2,
        'data' => '<strong>' . $record['title'] . '</strong>' . ' (' . check_plain($varname) . ')',
      ),
      $record['value'],
    );
    $rows[] = array(
      array(
        'data' => $record['description'],
      ),
    );
  }

  $form['variables'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['rebuild'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild routes'),
  );

  return $form;
}

/**
 * Form API submit callback.
 *
 * @see authcache_p13n_admin_routes()
 */
function authcache_p13n_admin_routes_submit() {
  authcache_p13n_request_router_rebuild();
  drupal_set_message(t('Rebuilt router'));
}

/**
 * Display details for a given route.
 */
function authcache_p13n_admin_route_page() {
  $route_id = implode('/', func_get_args());
  $resources = authcache_p13n_request_resources();

  drupal_set_title(t('Definition for route @route_id', array('@route_id' => $route_id)));

  require_once DRUPAL_ROOT . '/includes/utility.inc';
  $page['definition'] = array(
    '#markup' => '<code><pre>' . drupal_var_export($resources[$route_id]) . '</code></pre>',
  );

  return $page;
}

/**
 * Display a list of markup substitution configurations.
 */
function authcache_p13n_admin_markup_configs($form, &$form_state) {
  $resources = authcache_p13n_request_resources();
  $processors = authcache_p13n_resource_processors();

  // Gather group information from modules.
  $group_descriptions = module_invoke_all('authcache_p13n_admin_groups');

  // Preseed groups with group names from group descriptions.
  $groups = array_fill_keys(array_keys($group_descriptions), array());
  foreach ($resources as $route_id => $resource) {
    try {
      $factory = new AuthcacheP13nObjectFactory($resource, $processors);
      $entry = $factory->get('admin entry object');
      $groups[$entry->group][$route_id] = $entry;
    }
    catch (Exception $e) {
      drupal_set_message(t('Failed to retrieve info for route %route_id', array('%route_id' => $route_id)));
    }
  }

  ksort($groups);

  $header = array(
    t('Name'),
    t('Location'),
    t('Client'),
    t('Cache lifetime'),
    t('Cache granularity'),
    t('Route ID'),
    '',
  );
  $rows = array();
  foreach ($groups as $groupname => $group) {
    $rows[] = array(
      array(
        'class' => array('p13n-markup-substitution-group'),
        'colspan' => 7,
        'data' => $groupname,
      ),
    );
    if (isset($group_descriptions[$groupname])) {
      $rows[] = array(
        array(
          'class' => array('p13n-markup-substitution-message'),
          'colspan' => 7,
          'data' => $group_descriptions[$groupname],
        ),
      );
    }
    foreach ($group as $route_id => $entry) {
      $rows[] = array(
        array(
          'class' => array('p13n-markup-substitution-title'),
          'data' => $entry->name,
        ),
        $entry->description,
        implode(', ', _authcache_p13n_admin_format_clients($entry->clients)),
        !empty($entry->cacheMaxage) ? format_interval($entry->cacheMaxage) : '',
        implode(', ', _authcache_p13n_admin_cache_granularity($entry->cacheGranularity)),
        $route_id,
        !empty($entry->adminPath) ? l(t('Edit'), $entry->adminPath, array('query' => array('destination' => $_GET['q']))) : '',
      );
    }
  }

  $page['configs'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'authcache_p13n') . '/authcache_p13n.admin.css',
      ),
    ),
  );

  return $page;
}

/**
 * Given a client-array, return an ordered list of client names.
 */
function _authcache_p13n_admin_format_clients($config_clients = NULL) {
  $client_info = authcache_p13n_client_info();

  if (isset($config_clients)) {
    uasort($config_clients, 'drupal_sort_weight');
  }
  else {
    // Use original ordered client list by default.
    $config_clients = $client_info;
  }

  $client_names = array();
  foreach ($config_clients as $key => $config_client) {
    if (!empty($client_info[$key]['title']) && (!isset($config_client['status']) || !empty($config_client['status']))) {
      $client_names[] = $client_info[$key]['title'];
    }
  }

  return $client_names;
}

/**
 * Return a list of human readable cache granularity properties.
 */
function _authcache_p13n_admin_cache_granularity($granularity) {
  $result = array();

  if ($granularity->is(AuthcacheP13nCacheGranularity::PER_USER)) {
    $result[] = t('Per user');
  }

  if ($granularity->is(AuthcacheP13nCacheGranularity::PER_PAGE)) {
    $result[] = t('Per page');
  }

  return $result;
}
