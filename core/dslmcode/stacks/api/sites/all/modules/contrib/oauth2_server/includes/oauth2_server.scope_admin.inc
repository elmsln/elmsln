<?php
/**
 * @file
 * Admin UI for scopes.
 */

/**
 * UI controller.
 */
class OAuth2ServerScopeUIController extends EntityDefaultUIController {

  public function __construct($entity_type, $entity_info) {
    $this->statusKey = 'status';
    $this->entityType = $entity_type;
    $this->entityInfo = $entity_info;
    // Stop the UI from mentioning "OAuth2 scope" everywhere.
    $this->entityInfo['label'] = 'Scope';
    // Replace the server placeholder with the server name, since the path
    // is used for links and redirects.
    $this->path = str_replace('%oauth2_server', arg(4), $this->entityInfo['admin ui']['path']);
  }

  /**
   * Overrides EntityDefaultUIController::hook_menu().
   */
  public function hook_menu() {
    $items = array();
    $path = 'admin/structure/oauth2-servers/manage/%/scopes';
    $id_pos = count(explode('/', $path));

    $items[$path] = array(
      'title' => 'Scopes',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('oauth2_server_scope_overview_form', 'oauth2_server_scope'),
      'description' => 'Manage scopes.',
      'access callback' => 'entity_access',
      'access arguments' => array('view', 'oauth2_server_scope'),
      'type' => MENU_LOCAL_TASK,
      'file' => 'includes/entity.ui.inc',
      'weight' => 9,
    );
    $items[$path . '/add'] = array(
      'title' => 'Add scope',
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array('oauth2_server_scope', 4),
      'access callback' => 'entity_access',
      'access arguments' => array('create', 'oauth2_server_scope'),
      'type' => MENU_LOCAL_ACTION,
      'file' => $this->entityInfo['admin ui']['file'],
      'file path' => drupal_get_path('module', 'oauth2_server'),
    );
    // The regular Entity API way would be to use
    // $path . '/manage/%entity_object' here, but Drupal's Menu API is limited
    // to 9 levels, one too little for that to work.
    $items[$path . '/%entity_object'] = array(
      'title' => 'Edit',
      'title callback' => 'entity_label',
      'title arguments' => array('oauth2_server_scope', $id_pos),
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array('oauth2_server_scope', $id_pos),
      'load arguments' => array('oauth2_server_scope'),
      'access callback' => 'entity_access',
      'access arguments' => array('update', 'oauth2_server_scope', $id_pos),
      'file' => $this->entityInfo['admin ui']['file'],
      'file path' => drupal_get_path('module', 'oauth2_server'),
    );
    $items[$path . '/%entity_object/edit'] = array(
      'title' => 'Edit',
      'load arguments' => array('oauth2_server_scope'),
      'type' => MENU_DEFAULT_LOCAL_TASK,
    );
    $items[$path . '/%entity_object/delete'] = array(
      'page callback' => 'drupal_get_form',
      'page arguments' => array('oauth2_server_scope_operation_form', 'oauth2_server_scope', $id_pos, 'delete'),
      'load arguments' => array('oauth2_server_scope'),
      'access callback' => 'entity_access',
      'access arguments' => array('delete', 'oauth2_server_scope', $id_pos),
      'file' => 'includes/entity.ui.inc',
    );

    return $items;
  }

  /**
   * Overrides EntityDefaultUIController::overviewTable().
   */
  public function overviewTable($conditions = array()) {
    $this->server = oauth2_server_load(arg(4));
    $conditions['server'] = arg(4);
    return parent::overviewTable($conditions);
  }

  /**
   * Overrides EntityDefaultUIController::overviewTableHeaders().
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $header = $additional_header;
    array_unshift($header, t('Scope'));
    // Add operations with the right colspan.
    $header[] = array('data' => t('Operations'), 'colspan' => $this->operationCount());
    return $header;
  }

  /**
   * Overrides EntityDefaultUIController::overviewTableRow().
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);
    $entity_label = entity_label($this->entityType, $entity);
    if ($this->server && $this->server->settings['default_scope'] == $entity->name) {
      $entity_label .= ' (' . t('Default') . ')';
    }

    $row[] = array('data' => array(
      '#theme' => 'entity_ui_overview_item',
      '#label' => $entity_label,
      '#name' => FALSE,
      '#url' => $entity_uri ? $entity_uri : FALSE,
      '#entity_type' => $this->entityType),
    );
    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add the edit and delete links.
    $row[] = l(t('edit'), $this->path . '/' . $id);
    if (module_exists('i18n_string')) {
      $row[] = l(t('translate'), $this->path . '/' . $id . '/translate');
    }
    $row[] = l(t('delete'), $this->path . '/' . $id . '/delete', array('query' => drupal_get_destination()));

    return $row;
  }

  /**
   * Overrides EntityDefaultUIController::overviewTableRow().
   */
  public function applyOperation($op, $entity) {
    // If the default scope is about to be deleted, reset the server setting.
    if ($op == 'delete') {
      $server = oauth2_server_load(arg(4));
      if ($server && $server->settings['default_scope'] == $entity->name) {
        $server->settings['default_scope'] = '';
        $server->save();
      }
    }

    return parent::applyOperation($op, $entity);
  }
}

/**
 * Generates the scope editing form.
 */
function oauth2_server_scope_form($form, &$form_state, $scope, $op = 'edit') {
  // Make sure the parent server is present in form state.
  if (!isset($form_state['server'])) {
    $server = oauth2_server_load(arg(4));
    if (!$server) {
      return $form;
    }
    $form_state['server'] = $server;
  }
  // Set the server on new scope entities, since it serves as the bundle.
  // Needed by field_attach_form().
  if (empty($scope->server)) {
    $scope->server = $form_state['server']->name;
  }
  // entity_form_field_validate() builds a fake entity from
  // $form_state['values'], so the bundle needs to be in there.
  $form['server'] = array(
    '#type' => 'value',
    '#value' => $form_state['server']->name,
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $scope->name,
    '#disabled' => entity_has_status('oauth2_server_scope', $scope, ENTITY_IN_CODE),
    '#machine_name' => array(
      'exists' => 'oauth2_server_scope_exists',
      'replace_pattern' => '[^a-z0-9_\.]+',
    ),
    '#description' => t('A unique machine-readable name for this scope. It must only contain lowercase letters, numbers, and underscores.'),
    '#weight' => -2,
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => $scope->description,
    '#description' => t('Used to describe the scope to the user on the authorization form.'),
    '#required' => TRUE,
    '#weight' => -1,
  );

  field_attach_form('oauth2_server_scope', $scope, $form, $form_state);

  $is_default = FALSE;
  if (!empty($scope->name) && $form_state['server']->settings['default_scope'] == $scope->name) {
    $is_default = TRUE;
  }
  $form['default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Default'),
    '#default_value' => $is_default,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save scope'),
    '#weight' => 40,
  );

  if ($op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete scope'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('oauth2_server_scope_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Validation callback.
 */
function oauth2_server_scope_form_validate($form, &$form_state) {
  entity_form_field_validate('oauth2_server_scope', $form, $form_state);
}

/**
 * Form API submit callback for the type form.
 */
function oauth2_server_scope_form_submit(&$form, &$form_state) {
  $server = $form_state['server'];
  $previous_scope = $form_state['build_info']['args'][0];
  // The default scope is stored on the server. Update it there.
  $default = $form_state['values']['default'];
  if ($default) {
    $server->settings['default_scope'] = $form_state['values']['name'];
    $server->save();
  }
  elseif (!$default && $server->settings['default_scope'] == $previous_scope->name) {
    // This scope is no longer marked as default, reset the server setting.
    $server->settings['default_scope'] = '';
    $server->save();
  }
  // Unset the value of "Default" so that it doesn't get set on the entity.
  unset($form_state['values']['default']);

  $scope = entity_ui_form_submit_build_entity($form, $form_state);
  $scope->save();

  $form_state['redirect'] = 'admin/structure/oauth2-servers/manage/' . $server->name . '/scopes';
}

/**
 * Form API submit callback for the delete button.
 */
function oauth2_server_scope_form_submit_delete(&$form, &$form_state) {
  $server = arg(4);
  $form_state['redirect'] = 'admin/structure/oauth2-servers/manage/' . $server
                             . '/scopes/' . $form_state['oauth2_server_scope']->scope_id . '/delete';
}

/**
 * Check whether a given scope exists.
 *
 * @param $name
 *   The name of the scope.
 * @param $element
 *   The name form element array.
 * @param $form_state
 *   Form state.
 *
 * @return
 *   TRUE if the given scope exists. FALSE otherwise.
 */
function oauth2_server_scope_exists($name, $element, $form_state) {
  $server = $form_state['server'];
  return oauth2_server_scope_load($server->name, $name);
}
