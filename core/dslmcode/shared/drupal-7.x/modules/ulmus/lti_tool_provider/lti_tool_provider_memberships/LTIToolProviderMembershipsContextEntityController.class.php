<?php
/**
 * @file
 * Contains LTIToolProviderMembershipsContextEntityController.
 */

/**
 * Memberships Context Entity controller interface.
 */
interface LTIToolProviderMembershipsContextEntityControllerInterface
extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);
  public function delete($entity);
}

/**
 * Memberships Context Entity controller.
 */
class LTIToolProviderMembershipsContextEntityController
extends DrupalDefaultEntityController
implements LTIToolProviderMembershipsContextEntityControllerInterface {
  public function create() {
    $entity = new stdClass();
    $entity->lti_tool_provider_memberships_context_id = 0;
    $entity->lti_tool_provider_memberships_context_context_id = NULL;
    $entity->lti_tool_provider_memberships_context_file_id = 0;
    return $entity;
  }

  /**
   * Save a memberships context entity.
   *
   * @param object $entity
   *   The memberships context to be saved.
   *
   * @return object|boolean
   *   The saved entity or FALSE.
   */
  public function save($entity) {
    $transaction = db_transaction();
    try {
      $entity->is_new = empty($entity->lti_tool_provider_memberships_context_id);
      field_attach_presave('lti_tool_provider_memberships_context', $entity);
      $primary_key = $entity->lti_tool_provider_memberships_context_id ? 'lti_tool_provider_memberships_context_id' : array();
      if (empty($primary_key)) {
        drupal_write_record('lti_tool_provider_memberships_context', $entity);
        field_attach_insert('lti_tool_provider_memberships_context', $entity);
        $op = 'insert';
      }
      else {
        drupal_write_record('lti_tool_provider_memberships_context', $entity, $primary_key);
        $op = 'update';
      }
      $function = 'field_attach_' . $op;
      $function('lti_tool_provider_memberships_context', $entity);
      module_invoke_all('entity_' . $op, $entity, 'lti_tool_provider_memberships_context');
      unset($entity->is_new);
      db_ignore_slave();
      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      drupal_set_message(t('%e', array('%e' => $entity->$e)));
      watchdog_exception('lti_tool_provider_memberships_context', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Delete a memberships context entity.
   *
   * @param object $entity
   *   The memberships context to be deleted.
   */
  public function delete($entity) {
    $this->delete_multiple(array($entity));
  }

  /**
   * Delete a list of memberships context entities.
   *
   * @param object $entities
   *   An array of memberships contexts to be deleted.
   */
  public function delete_multiple($entities) {
    $ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          module_invoke_all('lti_tool_provider_memberships_context_delete', $entity);
          module_invoke_all('entity_delete', $entity, 'lti_tool_provider_memberships_context');
          field_attach_delete('lti_tool_provider_memberships_context', $entity);
          $ids[] = $entity->lti_tool_provider_memberships_context_id;
        }
        db_delete('lti_tool_provider_memberships_context')
        ->condition('lti_tool_provider_memberships_context_id', $ids, 'IN')
        ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('lti_tool_provider_memberships_context', $e);
        throw $e;
      }
    }
  }
}
