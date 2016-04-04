<?php

/**
 * @file
 * Contains the CerFieldChainHandler object.
 */

/**
 * @class
 * Wraps around every CerFieldHandler object in a chain. In any given chain, there
 * could be many entities that need to be processed -- think about multi-value field
 * collections embedded within other multi-value field collections, and you quickly
 * see how extensive the recursion can be. CER needs to be able to handle crazy
 * scenarios like that and still perform add/delete operations transparently. That's
 * what this guy does.
 */
class CerFieldChainHandler {

  /**
   * @var CerFieldChain
   */
  protected $chain;

  /**
   * @var EntityDrupalWrapper
   */
  protected $entity;

  /**
   * @var array or RecursiveIteratorIterator
   */
  protected $handlers;

  public function __construct(CerFieldChain $chain, EntityDrupalWrapper $entity) {
    $this->chain = $chain;
    $this->entity = $entity;

    $chain->__wakeup();
    $chain->seek($entity->cer->depth->value());

    $field = $chain->current();

    // If the field has a child, there could be extensive recusion here. So we'll need
    // to iterate over the entire chain recursively -- luckily, SPL provides the
    // RecursiveIteratorIterator class for this purpose. But if there are no children,
    // we don't need to recurse; the only handler we'll need to load is the current
    // field's, for the current entity.
    if ($field->child()) {
      $this->handlers = new RecursiveIteratorIterator(new CerEndPointIterator($field, $entity));
    }
    else {
      // Wrap the handler in an array, just to normalize things internally.
      $this->handlers = array( $field->getHandler($entity) );
    }
  }

  /**
   * Returns the IDs of every entity referenced in this chain. If there are no references,
   * an empty array is returned.
   *
   * @return array
   */
  public function getIDs() {
    $IDs = array();

    foreach ($this->handlers as $handler) {
      $IDs = array_merge($handler->getIDs(), $IDs);
    }

    return array_unique($IDs);
  }

  /**
   * Adds a reference to the given entity.
   */
  public function add(EntityDrupalWrapper $entity) {
    $owner = $this->entity;

    foreach ($this->chain as $field) {
      // If the current field implements CerEntityContainerInterface, we can
      // create an entity on-the-fly to receive the reference, if there isn't
      // one already.
      if ($field instanceof CerEntityContainerInterface) {
        $items = $field->getHandler($owner);

        // If there is are items which could receive the reference, seek to the
        // last one. Otherwise, create one.
        if (sizeof($items) == 0) {
          $owner = $field->createInnerEntity($owner);
        }
        else {
          $items->seek(-1);
          $owner = $items->current();
        }
      }
    }

    $field->getHandler($owner)->add($entity);
  }

  public function delete(EntityDrupalWrapper $entity) {
    foreach ($this->handlers as $handler) {
      $handler->delete($entity);
    }
  }

}
