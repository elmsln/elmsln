<?php

/**
 * @file
 *  Contains CerPresetHandler.
 */

/**
 * @class
 * Contains the logic for performing CER operations on a single entity, 
 * using a single preset.
 */
class CerPresetHandler {

  /**
   * @var CerFieldChain
   */
  protected $left;
  
  /**
   * @var CerFieldChain
   */
  protected $right;

  /**
   * @var EntityDrupalWrapper
   */
  protected $entity;

  /**
   * @var array
   */
  protected $refIDs;

  public function __construct(CerPreset $preset, EntityDrupalWrapper $entity) {
    $this->left = $preset->wrapper->cer_left->chain->value();
    $this->right = $preset->wrapper->cer_right->chain->value();
    $this->entity = $entity;

    // Store the current set of reference IDs so that we only need to instantiate
    // the left handler once.
    $this->refIDs = $this->left->getHandler( $entity )->getIDs();
  }

  /**
   * Process an entity insert. This loops through the referenced entity $IDs and
   * adds a reference to this entity if the reference doesn't already have one.
   */
  public function insert(array $IDs = array()) {
    // If no IDs were passed in, use the current reference set.
    $IDs = ($IDs ? $IDs : $this->refIDs);

    // Get this entity's ID right now, so we don't have to keep calling
    // $this->entity->cer->owner->getIdentifier(). Hooray for micro-optimization!
    $myID = $this->entity->cer->owner->getIdentifier();

    foreach ($this->load( $IDs ) as $ref) {
      $handler = $this->right->getHandler( $ref );

      // Only create the backreference if the reference doesn't already reference
      // this entity (which it might, if there is more than one preset that references
      // a single field instance).
      if (! in_array($myID, $handler->getIDs())) {
        $handler->add( $this->entity->cer->owner );
      }
    }
  }

  /**
   * Process an entity update. This could be either a normal update done by a user,
   * or a bulk update.
   */
  public function update() {
    // Get the previous set of reference IDs. $entity->cer->original will return either
    // $entity->original, if it exists, or the current entity. So, if this is a bulk
    // update, $originalIDs will be identical to $this->refIDs.
    $originalIDs = $this->left->getHandler( $this->entity->cer->original )->getIDs();

    // If there are any references that were in the previous set but not the current
    // set, delete those backreferences. Under normal circumstances, there will be
    // nothing to delete during a bulk update, since the previous set and current
    // set should be identical.
    $deleted = array_diff($originalIDs, $this->refIDs);
    if ($deleted) {
      $this->delete($deleted);
    }

    // If the previous set is identical to the current set, we'll be processing
    // all existing references (see the first line of $this->insert()).
    $added = array_diff($this->refIDs, $originalIDs);
    $this->insert($added);
  }

  /**
   * Process an entity delete. Loops through the referenced entity IDs and clears
   * their references to this entity.
   */
  public function delete(array $IDs = array()) {
    // As with $this->insert(), we can process a specific set of references or
    // everything in the current set.
    $IDs = ($IDs ? $IDs : $this->refIDs);

    foreach ($this->load( $IDs ) as $ref) {
      $this->right->getHandler( $ref )->delete( $this->entity->cer->owner );
    }
  }
  
  /**
   * Loads referenced entities. This might seem like a convenience method, but it
   * is a critical part CER's core logic.
   *
   * @param array $IDs
   *  Array of entity IDs to load.
   *
   * @return array
   *  The requested entities, wrapped by EntityDrupalWrapper. If nothing could be
   *  loaded, an empty array is returned.
   */
  protected function load(array $IDs) {
    if (empty($IDs)) {
      return array();
    }

    $this->right->rewind();
    $right = $this->right->current();
    $entity_type = $right->entityType;

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type);
    $query->entityCondition('entity_id', $IDs);

    // If the right entity type has bundles, we need to filter by that too. If we don't,
    // we could run into a bug where, if the left field can reference multiple bundles,
    // we might try to modify the wrong entity. Essentially, the loading of referenced
    // entities should be as targeted as possible to prevent ambiguities and buggery.
    if ($right->isBundleable) {
      $query->entityCondition('bundle', $right->bundle);
    }

    $result = $query->execute();
    if (isset($result[$entity_type])) {
      $result[$entity_type] = entity_load($entity_type, array_keys($result[$entity_type]));
      
      foreach ($result[$entity_type] as $id => $entity) {
        $result[$entity_type][$id] = new EntityDrupalWrapper($entity_type, $entity);
      }

      return $result[$entity_type];
    }
    else {
      return array();
    }
  }

} 
