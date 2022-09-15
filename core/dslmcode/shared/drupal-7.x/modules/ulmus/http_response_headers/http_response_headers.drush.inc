<?php

/**
 * @file
 * HTTP response headers drush command.
 */

/**
 * Implements hook_drush_command().
 */
function http_response_headers_drush_command() {
  $items = array();

  // The 'http-header-add' command.
  $items['http-header-add'] = array(
    'description' => 'Creates new HTTP header rule',
    'arguments' => array(
      'machine_name' => 'The machine name rule ID) of the header rule.',
      'header' => 'The HTTP header.',
      'header_value' => 'Value of the header.',
    ),
    'options' => array(
      'description' => array(
        'description' => 'Human readable name of the header rule',
        'example-value' => 'Global cache header',
      ),
      'pages' => array(
        'description' => 'Specific pages to set HTTP headers',
        'example-value' => 'admin/*, node/123',
      ),
      'visibility' => array(
        'description' => 'Visibility option for page settings. Allowed values are 0 (HTTP_RESPONSE_HEADERS_VISIBILITY_NOTLISTED) and 1 (HTTP_RESPONSE_HEADERS_VISIBILITY_LISTED)',
        'example-value' => '0 or 1',
      ),
      'types' => array(
        'description' => 'Specific content types(comma separated) t to set HTTP headers.',
        'example-value' => 'article, page',
      ),
      'roles' => array(
        'description' => 'Specific role IDs(comma separated) to set HTTP headers. Check "drush role-list" for available role IDs',
        'example-value' => '1, 2',
      ),
    ),
    'examples' => array(
      'drush http-header-add global_expires "Global expires" Expires 6000  --path=node/* --type=article --role=anonymous' => 'Make a header rule with cache set for 30 seconds on pages under node/ and type article viewed by anonymous user.',
    ),
    'aliases' => array('header-add'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The 'http-header-set' command.
  $items['http-header-set'] = array(
    'description' => 'Modify HTTP header rule',
    'arguments' => array(
      'machine_name' => 'The machine name (rule ID) of the header rule.',
    ),
    'options' => array(
      'visibility' => array(
        'description' => 'Visibility option for page settings. Allowed values are 0 (HTTP_RESPONSE_HEADERS_VISIBILITY_NOTLISTED) and 1 (HTTP_RESPONSE_HEADERS_VISIBILITY_LISTED)',
        'example-value' => '0 or 1',
      ),
      'pages' => array(
        'description' => 'Specific pages to set HTTP headers',
        'example-value' => 'admin/*, node/123',
      ),
      'types' => array(
        'description' => 'Specific content types to set HTTP headers',
        'example-value' => 'article, page',
      ),
      'roles' => array(
        'description' => 'Specific roles to set HTTP headers',
        'example-value' => 'anonymous, authenticated',
      ),
    ),
    'examples' => array(
      'drush http-header-set global_expires --path=node/* --type=article --role=anonymous' => 'Update the header rule with with path as node/* and article content type viewed by anonymous user.',
    ),
    'aliases' => array('header-set'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The 'http-header-get' command.
  $items['http-header-get'] = array(
    'description' => 'Retrieves HTTP header rule by machine name',
    'arguments' => array(
      'machine_name' => 'The machine name of the header rule.',
    ),
    'examples' => array(
      'drush http-header-get global_expires' => 'Get the header rule with machine name global_expires',
    ),
    'aliases' => array('header-get'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The 'http-header-del' command.
  $items['http-header-del'] = array(
    'description' => 'Delete a HTTP header rule by machine name',
    'arguments' => array(
      'machine_name' => 'The machine name of the header rule.',
    ),
    'examples' => array(
      'drush http-header-del global_expires' => 'Delete the header rule with machine name global_expires',
    ),
    'aliases' => array('header-del'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The 'http-header-list' command.
  $items['http-header-list'] = array(
    'description' => 'Lists all HTTP header rules available',
    'examples' => array(
      'drush http-header-list' => 'List of all HTTP header rules available.',
    ),
    'aliases' => array('header-list'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  return $items;

}

/**
 * Validation callback for drush_http_response_headers_http_header_set().
 *
 * @param string $machine_name
 *   A string rule ID.
 * @param string $header
 *   A string header.
 * @param mixed $header_value
 *   Header value.
 */
function drush_http_response_headers_http_header_add_validate($machine_name, $header, $header_value) {
  $args = func_get_args();

  // Should have all arguments.
  if (count($args) < 3) {
    return drush_set_error(t('Mandatory arguments missing.'));
  }

  // Validate header.
  $allowed_headers = variable_get('http_response_headers_allowed_headers');
  if (!in_array($header, $allowed_headers)) {
    return drush_set_error(t('@header is not a valid header. Try "drush vget http_response_headers_allowed_headers" to see list of allowed headers to create header rules.', array('@header' => $header)));
  }

  if (http_response_headers_rule_load($machine_name)) {
    return drush_set_error(t('@machine_name is already exist!.', array('@machine_name' => $machine_name)));
  }

  // Do the basic validations.
  _drush_http_response_headers_basic_validation();
}

/**
 * Sets header rule.
 *
 * Update if rule id exists, create one otherwise.
 *
 * @param string $machine_name
 *   A string rule ID.
 * @param string $header
 *   A string header name.
 * @param string $header_value
 *   A string header value.
 */
function drush_http_response_headers_http_header_add($machine_name, $header, $header_value) {
  $description = drush_get_option('description', NULL) ? trim(check_plain(drush_get_option('description', NULL))) : trim(check_plain($machine_name));
  $pages = drush_get_option('pages', NULL);

  $rule = new HttpResponseHeadersRule();
  $rule->setMachineName($machine_name)
    ->setDescription($description)
    ->setHeader(trim($header))
    ->setHeaderValue(trim($header_value))
    ->setPages(trim($pages))
    ->setVisibility(drush_get_option('visibility', HTTP_RESPONSE_HEADERS_VISIBILITY_NOTLISTED))
    ->setRoles(drush_get_option('roles', NULL))
    ->setTypes(drush_get_option('types', NULL));

  http_response_headers_rule_save($rule);

  drush_log(dt('!rule was added.', array('!machine_name' => $machine_name)));
}

/**
 * Validation callback for drush_http_response_headers_http_header_set().
 *
 * @param string $machine_name
 *   A string rule ID.
 */
function drush_http_response_headers_http_header_set_validate($machine_name) {
  // Validate rule ID.
  if (!http_response_headers_rule_load($machine_name)) {
    return drush_set_error(t('@machine_name is not a valid header rule', array('@machine_name' => $machine_name)));
  }

  // Do the basic validations.
  _drush_http_response_headers_basic_validation();
}

/**
 * Sets header rule.
 *
 * @param string $machine_name
 *   A string rule ID.
 */
function drush_http_response_headers_http_header_set($machine_name) {
  $rule = http_response_headers_rule_load($machine_name);

  if ($pages = drush_get_option('pages', NULL)) {
    $rule->setPages($pages);
  }
  if ($visibility = drush_get_option('visibility', NULL)) {
    $rule->setTypes($visibility);
  }
  if ($types = drush_get_option('types', NULL)) {
    $rule->setTypes($types);
  }
  if ($roles = drush_get_option('roles', NULL)) {
    $rule->setRoles($roles);
  }

  http_response_headers_rule_save($rule);
  drush_log(dt('!rule was update.', array('!machine_name' => $machine_name)));
}

/**
 * Validates the given rule ID is valid.
 *
 * @param string $machine_name
 *   A string rule ID.
 */
function drush_http_response_headers_http_header_get_validate($machine_name) {
  if (!http_response_headers_rule_load($machine_name)) {
    return drush_set_error(t('@machine_name is not a valid header rule', array('@machine_name' => $machine_name)));
  }
}

/**
 * Gets a header rule by rule ID.
 *
 * @param string $machine_name
 *   A string rule ID.
 */
function drush_http_response_headers_http_header_get($machine_name) {
  if ($rule = http_response_headers_rule_load($machine_name)) {
    drush_print_table(drush_key_value_to_array_table((array) $rule));
  }
}

/**
 * Deletes a header rule.
 *
 * @return string
 *   A string message for choice or confirming success.
 */
function drush_http_response_headers_http_header_del() {
  $args = func_get_args();
  // Look for similar variable names.
  $result = drush_http_response_headers_like($args[0]);

  $options = array();
  while ($name = drush_db_result($result)) {
    $options[] = $name;
  }
  if (drush_get_option('exact', FALSE)) {
    $options = in_array($args[0], $options) ? array($args[0]) : array();
  }

  if (count($options) == 0) {
    drush_print(dt('!name not found.', array('!name' => $args[0])));
    return '';
  }

  if ((count($options) == 1) && drush_get_context('DRUSH_AFFIRMATIVE')) {
    drush_op('http_response_headers_rule_delete', $args[0]);
    drush_log(dt('!name was deleted.', array('!name' => $args[0])), 'success');
    return '';
  }
  else {
    $choice = drush_choice($options, 'Enter a number to choose which header rule to delete.');
    if ($choice !== FALSE) {
      $choice = $options[$choice];
      drush_op('http_response_headers_rule_delete', $choice);
      drush_log(dt('!choice was deleted.', array('!choice' => $choice)), 'success');
    }
  }
}

/**
 * Lists all header rules available.
 */
function drush_http_response_headers_http_header_list() {
  $rules = http_response_headers_rule_load_all();
  $rows = array();
  foreach ($rules as $rule) {

    $rows[] = array(
      'machine_name' => $rule->getMachineName(),
      '' => $rule->getDescription(),
      'header' => $rule->getHeader(),
      'header_value' => $rule->getHeaderValue(),
    );
  }
  if (!empty($rows)) {
    $headers = array(
      'machine_name' => dt('Machine name'),
      'description' => dt('Description'),
      'header' => dt('Header'),
      'header_value' => dt('Header value'),
    );
    array_unshift($rows, $headers);
  }

  drush_print_table($rows, TRUE);
}

/**
 * Query for similar rule names.
 *
 * @param string $machine_name
 *   A string rule ID.
 */
function drush_http_response_headers_like($machine_name) {
  return drush_db_select('http_response_headers', 'machine_name', 'machine_name LIKE :keyword OR description LIKE :keyword', array(':keyword' => '%' . $machine_name . '%'), NULL, NULL, 'machine_name');
}

/**
 * Validates options has valid data.
 */
function _drush_http_response_headers_basic_validation() {
  $pages = drush_get_option('pages', NULL);
  $types_raw = drush_get_option('types', NULL);
  $roles_raw = drush_get_option('roles', NULL);
  $visibility = drush_get_option('visibility', NULL);

  // Do not process, if no visibility settings.
  if (empty($pages) && empty($types_raw) && empty($roles_raw)) {
    drush_set_error(dt('There is no visibility configuration.'));
  }

  // Do not set page without page visibility flag.
  if (!empty($pages) && $visibility === NULL) {
    drush_set_error(dt('No page visibility settings provided. Should be 0 (HTTP_RESPONSE_HEADERS_VISIBILITY_NOTLISTED) or 1 (HTTP_RESPONSE_HEADERS_VISIBILITY_LISTED)'));
  }

  // Make sure roles are valid, if present.
  $roles = explode(',', trim($roles_raw));
  if (is_array($roles)) {
    $rule_roles = array_unique(array_filter($roles));
  }
  if (isset($rule_roles)) {
    $invalid_roles = array();
    $user_roles = user_roles();
    foreach ($rule_roles as $rule_role) {
      if (array_search($rule_role, $user_roles) === FALSE) {
        $invalid_roles[] = $rule_role;
      }
    }
    if (!empty($invalid_roles)) {
      $message = (count($invalid_roles) > 1) ? '!roles are not valid roles.' : '!roles is not a valid role.';
      $message .= ' Try drush role-list for list of available roles.';
      drush_set_error(dt($message, array('!roles' => implode(', ', $invalid_roles))));
    }
  }

  // Make sure content types are valid, if present.
  $types = explode(',', trim($types_raw));
  if (is_array($types)) {
    $rule_types = array_unique(array_filter($types));
  }
  if (isset($rule_types)) {
    $node_types = array_keys(node_type_get_names());
    foreach ($rule_types as $rule_type) {
      if (array_search($rule_type, $node_types) === FALSE) {
        $invalid_types[] = $rule_type;
      }
    }
    if (!empty($invalid_types)) {
      $message = (count($invalid_types) > 1) ? '!types are not valid content types.' : '!types is not a valid content type.';
      drush_set_error(dt($message, array('!types' => implode(', ', $invalid_types))));
    }
  }
}
