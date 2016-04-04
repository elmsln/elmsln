<?php

/**
 * @file
 * Contains the CER plugin for Field Collection fields.
 */

class CerFieldCollectionField extends CerField implements CerEntityContainerInterface {

  /**
   * Implements CerField::getTargetType().
   */
  public function getTargetType() {
    return 'field_collection_item';
  }

  /**
   * @override CerField::getTargetBundles().
   */
  public function getTargetBundles() {
    return array($this->name);
  }

  /**
   * Implements CerEntityContainerInterface::createInnerEntity().
   */
  public function createInnerEntity(EntityDrupalWrapper $owner) {
    // Create an empty field collection item.
    $collection = new EntityDrupalWrapper('field_collection_item', entity_create('field_collection_item', array('field_name' => $this->name)));
    $collection->host_entity->set( $owner );
    $collection->save(TRUE);

    // 'Reference' the newly created field collection item.
    $this->getHandler($owner)->add($collection);

    return $collection;
  }

}
