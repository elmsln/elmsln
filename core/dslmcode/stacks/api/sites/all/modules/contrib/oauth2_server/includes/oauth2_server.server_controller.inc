<?php

/**
 * The entity controller for oauth2_server entities.
 *
 * Provides enhanced exportables, allowing scopes to be exported with servers.
 */
class OAuth2ServerEntityController extends EntityAPIControllerExportable {

  /**
   * Overrides EntityAPIControllerExportable::invoke().
   */
  public function invoke($hook, $entity) {
    if ($hook == 'delete') {
      // To ease figuring out whether this is a revert, make sure that the
      // entity status is updated in case the providing module has been
      // disabled.
      if (entity_has_status('oauth2_server_scope', $entity, ENTITY_IN_CODE) && !module_exists($entity->module)) {
        $entity->status = ENTITY_CUSTOM;
      }
      $is_revert = entity_has_status('oauth2_server_scope', $entity, ENTITY_IN_CODE);
    }

    // The server serves as a bundle for scopes and clients.
    if ($hook == 'insert') {
      field_attach_create_bundle('oauth2_server_scope', $entity->name);
      field_attach_create_bundle('oauth2_server_client', $entity->name);
    }
    elseif ($hook == 'delete' && empty($is_revert)) {
      field_attach_delete_bundle('oauth2_server_scope', $entity->name);
      field_attach_delete_bundle('oauth2_server_client', $entity->name);
    }
    elseif ($hook == 'update' && $entity->original->name != $entity->name) {
      field_attach_rename_bundle('oauth2_server_scope', $entity->original->name, $entity->name);
      field_attach_rename_bundle('oauth2_server_client', $entity->original->name, $entity->name);
    }

    parent::invoke($hook, $entity);
  }

  /**
   * Overrides EntityAPIControllerExportable::export().
   */
  public function export($entity, $prefix = '') {
    $vars = get_object_vars($entity);
    unset($vars['server_id'], $vars['status'], $vars['module'], $vars['is_new']);
    $vars['scopes'] = array();
    // Get a list of all scopes belonging to this server.
    // Add the "oauth2_server_scope_export" tag so that other modules can
    // restrict which scopes should be exported.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'oauth2_server_scope');
    $query->propertyCondition('server', $entity->name);
    $query->addTag('oauth2_server_scope_export');
    $query->addMetaData('oauth2_server', $entity);
    $results = $query->execute();
    if ($results) {
      $scope_ids = array_keys($results['oauth2_server_scope']);
      $scopes = entity_load('oauth2_server_scope', $scope_ids);
      foreach ($scopes as $scope) {
        $scope_vars = get_object_vars($scope);
        unset($scope_vars['scope_id'], $scope_vars['server']);
        $vars['scopes'][] = $scope_vars;
      }
    }

    return entity_var_json_export($vars, $prefix);
  }

  /**
   * Overrides EntityAPIControllerExportable::save().
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // There are scopes to be saved.
    if (!empty($entity->scopes)) {
      $existing_scopes = array();
      // Gather scope names, load all existing scopes, rekey them by name.
      $scope_names = array();
      foreach ($entity->scopes as $scope_values) {
        $scope_names[] = $scope_values['name'];
      }
      $scopes = oauth2_server_scope_load_multiple($entity->name, $scope_names);
      foreach ($scopes as $scope) {
        $existing_scopes[$scope->name] = $scope;
      }

      // Handle the insert / update.
      foreach ($entity->scopes as $scope_values) {
        $scope = entity_create('oauth2_server_scope', $scope_values);
        $scope->server = $entity->name;
        // A scope with the same name exists, steal its id, do an update.
        if (isset($existing_scopes[$scope->name])) {
          $existing_scope = $existing_scopes[$scope->name];
          $scope->scope_id = $existing_scope->scope_id;
          unset($scope->is_new);
        }
        $scope->save();
      }
    }

    return parent::save($entity, $transaction);
  }
}
