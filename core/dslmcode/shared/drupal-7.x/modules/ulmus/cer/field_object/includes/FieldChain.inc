<?php

/**
 * @file
 * Contains the FieldChain class.
 */

/**
 * @class
 * A doubly linked list of FieldInstance objects.
 */
class FieldChain implements SeekableIterator {

  protected $chain = array();

  protected $index = 0;

  /**
   * Magic post-unserialization callback. Provides every field in the chain
   * with a reference to its parent (if any) and child (if any), effectively
   * turning the chain into a doubly linked list.
   */
  public function __wakeup() {
    foreach ($this->chain as $field) {
      if (isset($parent)) {
        $field->parent($parent)->child($field);
      }
      $parent = $field;
    }
  }

  /**
   * Represents this chain as a machine-readable string, separating the fields
   * with a T_PAAMAYIM_NEKUDOTAYIM (or, as we call it on planet Earth, a
   * double colon).
   */
  public function __toString() {
    $key = array();

    foreach ($this->chain as $field) {
      $key[] = $field->__toString();
    }

    return implode('::', $key);
  }

  /**
   * Prepends a field instance to this chain. If $completed is passed, we'll
   * try to find the parents of the instance and recurse upwards, building
   * a tree of "routes" to the instance.
   */
  public function addField(FieldInstance $field, array &$completed = NULL) {
    array_unshift($this->chain, $field);
    $this->__wakeup();

    if (isset($completed)) {
      $parents = $field->getParents();

      if ($parents) {
        foreach ($parents as $parent) {
          $branch = clone $this;
          $branch->addField($parent, $completed);
        }
      }
      else {
        $completed[] = $this;
      }
    }
  }

  /**
   * Returns the last field in the chain.
   */
  public function end() {
    return end($this->chain);
  }

  /**
   * Implements SeekableIterator::seek().
   */
  public function seek($position) {
    if ($position >= 0 && $position < sizeof($this->chain)) {
      $this->index = $position;
    }
    else {
      throw new OutOfBoundsException(t('Cannot seek to invalid position %position.', array('%position' => $position)));
    }
  }

  /**
   * Implements Iterator::current().
   */
  public function current() {
    return $this->chain[$this->index];
  }

  /**
   * Implements Iterator::key().
   */
  public function key() {
    return $this->current()->__toString();
  }
  
  /**
   * Implements Iterator::next().
   */
  public function next() {
    $this->index++;
  }
  
  /**
   * Implements Iterator::rewind().
   */
  public function rewind() {
    $this->index = 0;
  }

  /**
   * Implements Iterator::valid().
   */
  public function valid() {
    return ($this->index < sizeof($this->chain));
  }

} 
 