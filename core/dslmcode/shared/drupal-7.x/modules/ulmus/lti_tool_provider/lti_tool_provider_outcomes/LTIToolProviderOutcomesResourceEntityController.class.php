<?php

/**
 * @file
 * Entity for outcome resource. Contains all related entity functions.
 * Entity views are found here
 */

interface LTIToolProviderOutcomesResourceEntityControllerInterface
extends DrupalEntityControllerInterface {

  /**
   * Create.
   */
  public function create();

  /**
   * Save.
   *
   * @param object $entity
   *   The Resource to save.
   */
  public function save($entity);

  /**
   * Delete a Resource.
   *
   * @param object $entity
   *   The Resource to delete.
   */
  public function delete($entity);
}

class LTIToolProviderOutcomesResourceEntityController
extends DrupalDefaultEntityController
implements LTIToolProviderOutcomesResourceEntityControllerInterface {

  /**
   * @see LTIToolProviderOutcomesResourceEntityControllerInterface::create
   */
  public function create() {
    $entity = new stdClass();
    $entity->lti_tool_provider_outcomes_resource_id = 0;
    $entity->lti_tool_provider_outcomes_resource_consumer_id = 0;
    $entity->lti_tool_provider_outcomes_resource_resource_link_title = '';
    $entity->lti_tool_provider_outcomes_resource_resource_link_id = '';
    $entity->lti_tool_provider_outcomes_resource_context_id = '';
    $entity->lti_tool_provider_outcomes_resource_resultvalue_sourcedids = '';
    $entity->lti_tool_provider_outcomes_resource_score_datatype = '';
    return $entity;
  }

  /**
   * @see LTIToolProviderOutcomesResourceEntityControllerInterface::save
   */
  public function save($entity) {
    $transaction = db_transaction();
    try{
      $entity->is_new = empty($enity->lti_tool_provider_outcomes_resource_id);
      if (empty($entity->lti_tool_provider_outcomes_resource_timestamp_created)) {
        $entity->lti_tool_provider_outcomes_resource_timestamp_created = REQUEST_TIME;
      }
      field_attach_presave('lti_tool_provider_outcomes_resource', $entity);
      $primary_key = $entity->lti_tool_provider_outcomes_resource_id ? 'lti_tool_provider_outcomes_resource_id' : array();
      if (empty($primary_key)) {
        drupal_write_record('lti_tool_provider_outcomes_resource', $entity);
        field_attach_insert('lti_tool_provider_outcomes_resource', $entity);
        $op = 'insert';
      }
      else {
        drupal_write_record('lti_tool_provider_outcomes_resource', $entity, $primary_key);
        $op = 'update';
      }
      $function = 'field_attach_' . $op;
      $function('lti_tool_provider_outcomes_resource', $entity);
      module_invoke_all('entity_' . $op, $entity, 'lti_tool_provider_outcomes_resource');
      unset($entity->is_new);
      db_ignore_slave();
      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      drupal_set_message(t('%e', array('%e' => $entity->$e)));
      watchdog_exception('lti_tool_provider_outcomes_resource', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * @see LTIToolProviderOutcomesResourceEntityControllerInterface::delete
   */
  public function delete($entity) {
    $this->deleteMultiple(array($entity));
  }

  /**
   * Delete Resources.
   *
   * @param array $entities
   *   An array of Resources to delete.
   *
   * @throws Exception
   */
  public function deleteMultiple($entities) {
    $ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          module_invoke_all('lti_tool_provider_outcomes_resource_delete', $entity);
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'lti_tool_provider_outcomes_resource');
          field_attach_delete('lti_tool_provider_outcomes_resource', $entity);
          $ids[] = $entity->lti_tool_provider_outcomes_resource_id;
        }
        db_delete('lti_tool_provider_outcomes_resource')
        ->condition('lti_tool_provider_outcomes_resource_id', $ids, 'IN')
        ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('lti_tool_provider_outcomes_resource', $e);
        throw $e;
      }
    }
  }
}
