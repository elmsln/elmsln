<?php

/**
 * Generic Interface for all entities.
 * @see hook_entity_info_alter()
 */
interface LticGenericBasicControllerInterface extends DrupalEntityControllerInterface {

  /**
   * Create an entity.
   */
  public function create();

  /**
   * Save an entity.
   *
   * @param object $entity
   *   The entity to save.
   */
  public function save($entity);

  /**
   * Delete an entity.
   *
   * @param object $entity
   *   The entity to delete.
   */
  public function delete($entity);
}
