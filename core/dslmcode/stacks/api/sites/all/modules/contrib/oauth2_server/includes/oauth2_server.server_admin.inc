<?php
/**
 * @file
 * Admin UI for servers.
 */

/**
 * UI controller.
 */
class OAuth2ServerUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage servers and their associated clients and scopes.';

    // Fix the "Add oauth2 server" and "Import oauth2 server" titles.
    unset($items[$this->path . '/add']['title callback']);
    unset($items[$this->path . '/add']['title arguments']);
    unset($items[$this->path . '/import']['title callback']);
    unset($items[$this->path . '/import']['title arguments']);
    $items[$this->path . '/add']['title'] = 'Add server';
    $items[$this->path . '/import']['title'] = 'Import server';

    return $items;
  }

  /**
   * Overrides EntityDefaultUIController::overviewTableHeaders().
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $additional_header[] = t('Clients');
    $additional_header[] = t('Scopes');
    return parent::overviewTableHeaders($conditions, $rows, $additional_header);
  }

  /**
   * Overrides EntityDefaultUIController::overviewTableRow().
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $additional_cols[] = l(t('clients'), $this->path . '/manage/' . $id . '/clients');
    $additional_cols[] = l(t('scopes'), $this->path . '/manage/' . $id . '/scopes');
    return parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
  }

  /**
   * Overrides EntityDefaultUIController::operationForm().
   */
  public function operationForm($form, &$form_state, $entity, $op) {
    if ($op == 'delete') {
      $query = new EntityFieldQuery;
      $query->entityCondition('entity_type', 'oauth2_server_scope');
      $query->propertyCondition('server', $entity->name);
      $query->count();
      $num_scopes = $query->execute();

      $num_clients = 0;
      // If there's at least one scope, we know the delete can't proceed,
      // so no need to count clients.
      if ($num_scopes == 0) {
        $query = new EntityFieldQuery;
        $query->entityCondition('entity_type', 'oauth2_server_client');
        $query->propertyCondition('server', $entity->name);
        $query->count();
        $num_clients = $query->execute();
      }

      if ($num_scopes > 0 || $num_clients > 0) {
        drupal_set_message(t('This server has associated scopes and/or clients, it cannot be deleted.'), 'error');
        return array();
      }
    }

    return parent::operationForm($form, $form_state, $entity, $op);
  }
}

/**
 * Generates the server editing form.
 */
function oauth2_server_form($form, &$form_state, $server, $op = 'edit') {
  // Make sure all needed settings keys are set, to prevent notices.
  $new_server = entity_create('oauth2_server', array());
  $server->settings += $new_server->settings;

  if ($op == 'clone') {
    $server->label .= ' (cloned)';
  }

  $form['#tree'] = TRUE;
  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $server->label,
    '#description' => t('The human-readable name of this server.'),
    '#required' => TRUE,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $server->name,
    '#disabled' => (entity_has_status('oauth2_server', $server, ENTITY_IN_CODE) || $op == 'edit'),
    '#machine_name' => array(
      'exists' => 'oauth2_server_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this server. It must only contain lowercase letters, numbers, and underscores.'),
  );

  field_attach_form('oauth2_server', $server, $form, $form_state);

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['settings']['enforce_state'] = array(
    '#type' => 'value',
    '#value' => $server->settings['enforce_state'],
  );
  // The default scope is actually edited from the Scope UI to avoid showing
  // a select box with potentially thousands of options here.
  $form['settings']['default_scope'] = array(
    '#type' => 'value',
    '#value' => $server->settings['default_scope'],
  );
  $form['settings']['allow_implicit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow the implicit flow'),
    '#description' => t('Allows clients to receive an access token without the need for an authorization request token.'),
    '#default_value' => !empty($server->settings['allow_implicit']),
  );
  $form['settings']['use_openid_connect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use OpenID Connect'),
    '#description' => t("Strongly recommended for login providers."),
    '#default_value' => !empty($server->settings['use_openid_connect']),
    '#access' => extension_loaded('openssl'),
  );
  $documentation_link = l('documentation', 'http://bshaffer.github.io/oauth2-server-php-docs/overview/jwt-access-tokens/');
  $form['settings']['use_crypto_tokens'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use JWT Access Tokens'),
    '#description' => t("Sends encrypted JWT access tokens that aren't stored in the database. See the !documentation for more details.", array('!documentation' => $documentation_link)),
    '#default_value' => !empty($server->settings['use_crypto_tokens']),
    '#access' => extension_loaded('openssl'),
  );
  $grant_types = oauth2_server_grant_types();
  // Prepare a list of available grant types.
  $grant_type_options = array();
  foreach ($grant_types as $type => $grant_type) {
    $grant_type_options[$type] = $grant_type['name'];
  }
  $form['settings']['grant_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled grant types'),
    '#options' => $grant_type_options,
    '#default_value' => $server->settings['grant_types'],
  );
  // Add any grant type specific settings.
  foreach ($grant_types as $type => $grant_type) {
    // Merge-in any provided defaults.
    if (isset($grant_type['default settings'])) {
      $server->settings += $grant_type['default settings'];
    }
    // Add the form elements.
    if (isset($grant_type['settings callback'])) {
      $dom_ids = array();
      $dom_ids[] = 'edit-settings-grant-types-' . str_replace('_', '-', $type);
      $form['settings'] += $grant_type['settings callback']($server->settings, $dom_ids);
    }
  }

  $form['settings']['advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['settings']['advanced_settings']['access_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Access token lifetime'),
    '#description' => t('The number of seconds the access token will be valid for.'),
    '#default_value' => $server->settings['access_lifetime'],
    '#size' => 11,
  );
  $form['settings']['advanced_settings']['id_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('ID token lifetime'),
    '#description' => t('The number of seconds the ID token will be valid for.'),
    '#default_value' => $server->settings['id_lifetime'],
    '#size' => 11,
    '#states' => array(
      'visible' => array(
        '#edit-settings-use-openid-connect' => array('checked' => TRUE),
      ),
    ),
  );
  $form['settings']['advanced_settings']['refresh_token_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Refresh token lifetime'),
    '#description' => t('The number of seconds the refresh token will be valid for. 0 for forever.'),
    '#default_value' => $server->settings['refresh_token_lifetime'],
    '#size' => 11,
  );
  $form['settings']['advanced_settings']['require_exact_redirect_uri'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require exact redirect uri'),
    '#description' => t("Require the redirect url to be an exact match of the client's redirect url
    If not enabled, the redirect url in the request can contain additional segments, such as a query string."),
    '#default_value' => isset($server->settings['require_exact_redirect_uri']) ? $server->settings['require_exact_redirect_uri'] : TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save server'),
    '#weight' => 40,
  );

  if (!entity_has_status('oauth2_server', $server, ENTITY_IN_CODE)
      && !in_array($op, array('add', 'clone'))) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete server'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('oauth2_server_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Validation callback.
 */
function oauth2_server_form_validate($form, &$form_state) {
  entity_form_field_validate('oauth2_server', $form, $form_state);
}

/**
 * Form API submit callback for the type form.
 */
function oauth2_server_form_submit(&$form, &$form_state) {
  // Save the previous / initial server settings for later comparison.
  $previous_settings = $form_state['build_info']['args'][0]->settings;
  // Advanced settings are a part of the main settings array.
  $form_state['values']['settings'] += $form_state['values']['settings']['advanced_settings'];
  unset($form_state['values']['settings']['advanced_settings']);
  // Create the server from form values and save it.
  $server = entity_ui_form_submit_build_entity($form, $form_state);
  $server->save();
  // If OpenID Connect was just enabled, create its scopes.
  $previous_value = !empty($previous_settings['use_openid_connect']);
  $current_value = !empty($server->settings['use_openid_connect']);
  if (!$previous_value && $current_value) {
    $site_name = variable_get('site_name', 'Drupal');
    $openid_scopes = array(
      'openid' => format_string('Know who you are on @site', array('@site' => $site_name)),
      'offline_access' => "Access the API when you're not present.",
      'email' => 'View your email address.',
      'profile' => 'View basic information about your account.',
    );
    foreach ($openid_scopes as $name => $description) {
      $scope = entity_create('oauth2_server_scope', array());
      $scope->server = $server->name;
      $scope->name = $name;
      $scope->description = $description;
      $scope->save();
    }
  }
  // If OpenID Connect was just disabled, delete its scopes.
  if ($previous_value && !$current_value) {
    $scope_names = array('openid', 'offline_access', 'email', 'profile');
    $scopes = oauth2_server_scope_load_multiple($server->name, $scope_names);
    foreach ($scopes as $scope) {
      $scope->delete();
    }
    // If we just deleted a default scope, update the server.
    if (in_array($server->settings['default_scope'], $scope_names)) {
      $server->settings['default_scope'] = '';
      $server->save();
    }
  }

  $form_state['redirect'] = 'admin/structure/oauth2-servers';
}

/**
 * Form API submit callback for the delete button.
 */
function oauth2_server_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/oauth2-servers/manage/' . $form_state['oauth2_server']->name . '/delete';
}
