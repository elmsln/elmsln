<?php

/**
 * @file
 * Contains CerEndPointIterator.
 */

/**
 * @class
 * The purpose of this iterator is to wrap around all the "endpoints" in a field chain.
 * An endpoint is a CerFieldHandler for a field that hasn't got a child. This is necessary
 * in order to support infinite levels of embedded entities (read: field collections).
 * This class is only instantiated by CerFieldChainHandler if its initial field handler
 * has a child (@see CerFieldHandler::__construct()).
 */
class CerEndPointIterator implements RecursiveIterator {

  /**
   * @var CerField
   */
  protected $field;

  /**
   * @var CerFieldHandler
   */
  protected $handler;

  public function __construct(CerField $field, EntityDrupalWrapper $entity) {
    $this->field = $field;
    $this->handler = $field->getHandler($entity);
  }

  /**
   * Implements Iterator::current().
   */
  public function current() {
    return $this->field->child()->getHandler($this->handler->current());
  }

  /**
   * Implements Iterator::key().
   */
  public function key() {
    return $this->handler->key();
  }

  /**
   * Implements Iterator::next().
   */
  public function next() {
    $this->handler->next();
  }

  /**
   * Implements Iterator::rewind().
   */
  public function rewind() {
    $this->handler->rewind();
  }

  /**
   * Implements Iterator::handler().
   */
  public function valid() {
    return $this->handler->valid();
  }

  /**
   * Implements RecursiveIterator::hasChildren().
   */
  public function hasChildren() {
    return ($this->field->child() instanceof CerEntityContainerInterface);
  }

  /**
   * Implements RecursiveIterator::getChildren().
   */
  public function getChildren() {
    return new CerEndPointIterator($this->field->child(), $this->handler->current());
  }

}
