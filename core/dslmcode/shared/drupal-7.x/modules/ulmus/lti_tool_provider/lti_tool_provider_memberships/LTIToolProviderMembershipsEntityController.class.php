<?php
/**
 * @file
 * Contains LTIToolProviderMembershipsEntityController.
 */

/**
 * Memberships Entity controller interface.
 */
interface LTIToolProviderMembershipsEntityControllerInterface
extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);
  public function delete($entity);
}

/**
 * Memberships Entity controller.
 */
class LTIToolProviderMembershipsEntityController
extends DrupalDefaultEntityController
implements LTIToolProviderMembershipsEntityControllerInterface {
  public function create() {
    $entity = new stdClass();
    $entity->lti_tool_provider_memberships_id = 0;
    $entity->lti_tool_provider_memberships_context_id = NULL;
    $entity->lti_tool_provider_memberships_uid = NULL;
    $entity->lti_tool_provider_memberships_user_id = NULL;
    $entity->lti_tool_provider_memberships_role = '';
    $entity->lti_tool_provider_memberships_person_name_full = '';
    $entity->lti_tool_provider_memberships_status = 'Active';
    $entity->date_added = REQUEST_TIME;
    $entity->date_updated = NULL;
    $entity->date_dropped = NULL;
    return $entity;
  }

  /**
   * Save a memberships entity.
   *
   * @param object $entity
   *   The memberships entity to be saved.
   *
   * @return object|boolean
   *   The saved memberships entity or FALSE.
   */
  public function save($entity) {
    $transaction = db_transaction();
    try {
      $entity->is_new = empty($entity->lti_tool_provider_memberships_id);
      if (!isset($entity->date_dropped)) {
        $entity->date_updated = REQUEST_TIME;
      }
      field_attach_presave('lti_tool_provider_memberships', $entity);
      $primary_key = $entity->lti_tool_provider_memberships_id ? 'lti_tool_provider_memberships_id' : array();
      if (empty($primary_key)) {
        drupal_write_record('lti_tool_provider_memberships', $entity);
        field_attach_insert('lti_tool_provider_memberships', $entity);
        $op = 'insert';
      }
      else {
        drupal_write_record('lti_tool_provider_memberships', $entity, $primary_key);
        $op = 'update';
      }
      $function = 'field_attach_' . $op;
      $function('lti_tool_provider_memberships', $entity);
      module_invoke_all('entity_' . $op, $entity, 'lti_tool_provider_memberships');
      unset($entity->is_new);
      db_ignore_slave();
      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      drupal_set_message(t('%e', array('%e' => $entity->$e)));
      watchdog_exception('lti_tool_provider_memberships', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Delete a memberships entity.
   *
   * @param object $entity
   *   The memberships etity to be deleted.
   */
  public function delete($entity) {
    $this->delete_multiple(array($entity));
  }

  /**
   * Delete a list of memberships entities.
   *
   * @param array $entities
   *   An array of memberships entities to be deleted.
   *
   * @throws Exception
   */
  public function delete_multiple($entities) {
    $ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          module_invoke_all('lti_tool_provider_memberships_delete', $entity);
          module_invoke_all('entity_delete', $entity, 'lti_tool_provider_memberships');
          field_attach_delete('lti_tool_provider_memberships', $entity);
          $ids[] = $entity->lti_tool_provider_memberships_id;
        }
        db_delete('lti_tool_provider_memberships')
        ->condition('lti_tool_provider_memberships_id', $ids, 'IN')
        ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('lti_tool_provider_memberships', $e);
        throw $e;
      }
    }
  }
}
