<?php
/**
 * @file
 * Contains LTIToolProviderConsumerEntityController.
 */

interface LTIToolProviderConsumerEntityControllerInterface
extends DrupalEntityControllerInterface {

  /**
   * Create.
   */
  public function create();

  /**
   * Save.
   *
   * @param object $entity
   *   The consumer.
   */
  public function save($entity);

  /**
   * Delete.
   *
   * @param object $entity
   *   The consumer.
   */
  public function delete($entity);
}

class LTIToolProviderConsumerEntityController
extends DrupalDefaultEntityController
implements LTIToolProviderConsumerEntityControllerInterface {

  /**
   * Create a consumer.
   *
   * @return object
   *   The consumer.
   */
  public function create() {
    $entity = new stdClass();
    $entity->lti_tool_provider_consumer_id = 0;
    $entity->lti_tool_provider_consumer_key = '';
    $entity->lti_tool_provider_consumer_secret = '';
    $entity->lti_tool_provider_consumer_consumer = '';
    $entity->lti_tool_provider_consumer_domain = '';
    $entity->lti_tool_provider_consumer_dummy_pref = FALSE;
    $extra_cols = lti_tool_provider_get_extra_columns();
    foreach ($extra_cols as $col) {
      $entity->$col = '';
    }
    return $entity;
  }

  /**
   * Save a consumer.
   *
   * @param object $entity
   *   The consumer.
   *
   * @return object|boolean
   *   The consumer or false if save failed.
   */
  public function save($entity) {
    $transaction = db_transaction();
    try {
      $entity->is_new = empty($enity->lti_tool_provider_consumer_id);
      if (empty($entity->date_joined)) {
        $entity->date_joined = REQUEST_TIME;
      }
      field_attach_presave('lti_tool_provider_consumer', $entity);
      $primary_key = $entity->lti_tool_provider_consumer_id ? 'lti_tool_provider_consumer_id' : array();
      if (empty($primary_key)) {
        drupal_write_record('lti_tool_provider_consumer', $entity);
        field_attach_insert('lti_tool_provider_consumer', $entity);
        $op = 'insert';
      }
      else {
        drupal_write_record('lti_tool_provider_consumer', $entity, $primary_key);
        $op = 'update';
      }
      $function = 'field_attach_' . $op;
      $function('lti_tool_provider_consumer', $entity);
      module_invoke_all('entity_' . $op, $entity, 'lti_tool_provider_consumer');
      unset($entity->is_new);
      db_ignore_slave();
      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      drupal_set_message(t('%e', array('%e' => $entity->$e)));
      watchdog_exception('lti_tool_provider_consumer', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Delete a consumer.
   *
   * @param object $entity
   *   The consumer.
   */
  public function delete($entity) {
    $this->deleteMultiple(array($entity));
  }

  /**
   * Delete multiple consumers.
   *
   * @param array $entities
   *   An array of consumers.
   *
   * @throws Exception
   *   From the db api.
   */
  public function deleteMultiple($entities) {
    $ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          module_invoke_all('lti_tool_provider_consumer_delete', $entity);
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'lti_tool_provider_consumer');
          field_attach_delete('lti_tool_provider_consumer', $entity);
          $ids[] = $entity->lti_tool_provider_consumer_id;
        }
        db_delete('lti_tool_provider_consumer')
        ->condition('lti_tool_provider_consumer_id', $ids, 'IN')
        ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('lti_tool_provider_consumer', $e);
        throw $e;
      }
    }
  }
}
