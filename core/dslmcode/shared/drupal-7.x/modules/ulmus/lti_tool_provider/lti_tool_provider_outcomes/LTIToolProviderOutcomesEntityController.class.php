<?php

/**
 * @file
 * Entity controller class for outcomes.
 */

interface LTIToolProviderOutcomesEntityControllerInterface
extends DrupalEntityControllerInterface {

  /**
   * Create.
   */
  public function create();

  /**
   * Save.
   *
   * @param object $entity
   *   The Outcome to save.
   */
  public function save($entity);

  /**
   * Delete.
   *
   * @param object $entity
   *   The Outcome to delete.
   */
  public function delete($entity);
}

class LTIToolProviderOutcomesEntityController
extends DrupalDefaultEntityController
implements LTIToolProvideroutcomesEntityControllerInterface {

  /**
   * @see LTIToolProviderOutcomesEntityControllerInterface::create
   */
  public function create() {
    $entity = new stdClass();
    $entity->lti_tool_provider_outcomes_id = 0;
    $entity->lti_tool_provider_outcomes_resource_entity_id_fk = 0;
    $entity->lti_tool_provider_outcomes_result_sourcedid = '';
    $entity->lti_tool_provider_outcomes_context_id = '';
    $entity->lti_tool_provider_outcomes_user_id = '';
    $entity->lti_tool_provider_outcomes_score = '';
    return $entity;
  }

  /**
   * @see LTIToolProviderOutcomesEntityControllerInterface::save
   */
  public function save($entity) {
    $transaction = db_transaction();
    try{
      $entity->is_new = empty($enity->lti_tool_provider_outcomes_id);
      if (empty($entity->lti_tool_provider_outcomes_date_joined)) {
        $entity->lti_tool_provider_outcomes_date_joined = REQUEST_TIME;
      }
      field_attach_presave('lti_tool_provider_outcomes', $entity);
      $primary_key = $entity->lti_tool_provider_outcomes_id ? 'lti_tool_provider_outcomes_id' : array();
      if (empty($primary_key)) {
        drupal_write_record('lti_tool_provider_outcomes', $entity);
        field_attach_insert('lti_tool_provider_outcomes', $entity);
        $op = 'insert';
      }
      else {
        drupal_write_record('lti_tool_provider_outcomes', $entity, $primary_key);
        $op = 'update';
      }
      $function = 'field_attach_' . $op;
      $function('lti_tool_provider_outcomes', $entity);
      module_invoke_all('entity_' . $op, $entity, 'lti_tool_provider_outcomes');
      unset($entity->is_new);
      db_ignore_slave();
      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      drupal_set_message(t('%e', array('%e' => $entity->$e)));
      watchdog_exception('lti_tool_provider_outcomes', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * @see LTIToolProviderOutcomesEntityControllerInterface::delete
   */
  public function delete($entity) {
    $this->deleteMultiple(array($entity));
  }

  /**
   * Delete Outcomes.
   *
   * @param array $entities
   *   An array of Outcomes entities to delete.
   *
   * @throws Exception
   */
  public function deleteMultiple($entities) {
    $ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          module_invoke_all('lti_tool_provider_outcomes_delete', $entity);
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'lti_tool_provider_outcomes');
          field_attach_delete('lti_tool_provider_outcomes', $entity);
          $ids[] = $entity->lti_tool_provider_outcomes_id;
        }
        db_delete('lti_tool_provider_outcomes')
        ->condition('lti_tool_provider_outcomes_id', $ids, 'IN')
        ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('lti_tool_provider_outcomes', $e);
        throw $e;
      }
    }
  }
}
