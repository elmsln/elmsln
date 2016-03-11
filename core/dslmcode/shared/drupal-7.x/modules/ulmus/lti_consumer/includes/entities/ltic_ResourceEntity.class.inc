<?php

/**
 *  LtiResourceBasicController extends DrupalDefaultEntityController.
 *
 * Our subclass of DrupalDefaultEntityController lets us add a few
 * important create, update, and delete methods.
 */
class LtiResourceBasicController extends DrupalDefaultEntityController implements LticGenericBasicControllerInterface {

  /**
   * Create and return a new ltic_resource entity.
   */
  public function create() {
    $entity = new stdClass();
    $entity->type = 'ltic_resource';
    $entity->ltic_resource_id = 0;
    $entity->bundle_type = 'first_example_bundle';
    $entity->ltic_resource_link_title = '';
    $entity->ltic_resource_link_description = '';
    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record().
   */
  public function save($entity) {
// If our entity has no basic_id, then we need to give it a
// time of creation.
    if (empty($entity->ltic_resource_id)) {
      $entity->created = time();
    }
// Invoke hook_entity_presave().
    module_invoke_all('entity_presave', $entity, 'ltic_resource');
// The 'primary_keys' argument determines whether this will be an insert
// or an update. So if the entity already has an ID, we'll specify
// basic_id as the key.
    $primary_keys = $entity->ltic_resource_id ? 'ltic_resource_id' : array();
// Write out the entity record.
    drupal_write_record('ltic_resource', $entity, $primary_keys);
// We're going to invoke either hook_entity_update() or
// hook_entity_insert(), depending on whether or not this is a
// new entity. We'll just store the name of hook_entity_insert()
// and change it if we need to.
    $invocation = 'entity_insert';
// Now we need to either insert or update the fields which are
// attached to this entity. We use the same primary_keys logic
// to determine whether to update or insert, and which hook we
// need to invoke.
    if (empty($primary_keys)) {
      field_attach_insert('ltic_resource', $entity);
    }
    else {
      field_attach_update('ltic_resource', $entity);
      $invocation = 'entity_update';
    }
// Invoke either hook_entity_update() or hook_entity_insert().
    module_invoke_all($invocation, $entity, 'ltic_resource');
    return $entity;
  }

  /**
   * Delete a single entity.
   *
   * Really a convenience function for deleteMultiple().
   */
  public function delete($entity) {
    $this->deleteMultiple(array($entity));
  }

  /**
   * Delete one or more ltic_resource entities.
   *
   * Deletion is unfortunately not supported in the base
   * DrupalDefaultEntityController class.
   *
   * @param array $entities
   *   An array of entity IDs or a single numeric ID.
   */
  public function deleteMultiple($entities) {
    $basic_ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
// Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'ltic_resource');
          field_attach_delete('ltic_resource', $entity);
          $basic_ids[] = $entity->ltic_resource_id;
        }
        db_delete('ltic_resource')
            ->condition('ltic_resource_id', $basic_ids, 'IN')
            ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('ltic_resource', $e);
        throw $e;
      }
    }
  }

}
