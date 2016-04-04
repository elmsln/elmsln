<?php

/**
 * @file
 * Contains CerFieldHandler.
 */
 
/**
 * @class
 * Handles low-level operations for a single field on a single entity. Exposes
 * methods to add, delete and check for references. This will also iterate over
 * the references, returning each one as an EntityDrupalWrapper object.
 */
class CerFieldHandler implements Countable, SeekableIterator {

  /**
   * @var CerField
   */
  protected $field;

  /**
   * @var EntityDrupalWrapper
   */
  protected $entity;

  /**
   * @var EntityMetadataWrapper
   */
  protected $value;

  /**
   * @var integer
   */
  protected $delta = 0;
  
  /**
   * @var boolean
   */
  protected $isMultiValue;

  public function __construct(CerField $field, EntityDrupalWrapper $entity) {
    $this->field = $field;
    $this->entity = $entity;
    $this->value = $entity->{ $field->name };
    $this->isMultiValue = ($this->value instanceof EntityListWrapper);

    $this->rewind();
  }

  /**
   * Adds a reference to $entity, validating it first.
   *
   * @param EntityDrupalWrapper $entity
   *  The wrapped entity to reference.
   */
  public function add(EntityDrupalWrapper $entity) {
    if ($this->validate($entity)) {
      $this->write();
    }
  }

  /**
   * Deletes all references to $entity.
   *
   * @param EntityDrupalWrapper $entity
   *  The wrapped entity to dereference.
   */
  public function delete(EntityDrupalWrapper $entity) {
    $entityID = $entity->getIdentifier();

    if ($this->isMultiValue) {
      foreach ($this->value as $delta => $ref) {
        if ($entityID == $ref->getIdentifier()) {
          $this->value[$delta]->set(NULL);
        }
      }
    }
    elseif ($entityID == $this->value->getIdentifier()) {
      $this->value->set(NULL);
    }

    $this->write();
  }

  /**
   * Validates a potential reference. After doing a cardinality check, the
   * reference is validated through the Field Attach API, allowing the module
   * which owns the field to do its normal validation logic. If validation
   * fails, the error(s) are logged.
   *
   * @param EntityDrupalWrapper $entity
   *  The wrapped entity to validate.
   *
   * @return boolean
   */
  protected function validate(EntityDrupalWrapper $entity) {
    // Before we do anything else, check that the field has enough space to add the
    // reference. If there isn't, bail out so we don't blindly overwrite existing
    // field data.
    if ($this->checkCardinality()) {
      // Keep the previous value so we can restore it if validation fails.
      $prev_value = $this->value->value();

      if ($this->isMultiValue) {
        $value = $this->value->value();
        $value[] = $entity->value();
        $this->value->set($value);
      }
      else {
        $this->value->set( $entity->value() );
      }

      // Leverage the Field Attach API to validate the reference. If errors occur,
      // field_attach_validate() throws FieldValidationException, containing an array
      // of every validation error.
      try {
        // Only validate this field.
        field_attach_validate($this->entity->type(), $this->entity->value(), array('field_name' => $this->field->name));

        return TRUE;
      }
      catch (FieldValidationException $e) {
        foreach ($e->errors as $field) {
          foreach ($field as $language) {
            foreach ($language as $errors) {
              foreach ($errors as $error) {
                $this->logError($error['message'], $entity);
              }
            }
          }
        }
        $this->value->set($prev_value);
      }
    }
    else {
      $this->logError('Cannot add reference to !that_link from !field_label on !this_link because there are no more slots available.', $entity);
    }

    return FALSE;
  }

  /**
   * Checks that there are enough slots in the field to add a reference.
   *
   * @return boolean
   */
  protected function checkCardinality() {
    return ($this->field->cardinality == FIELD_CARDINALITY_UNLIMITED ? TRUE : ($this->field->cardinality > $this->count()));
  }

  /**
   * Saves changes to the entity and resets the iterator.
   */
  protected function write() {
    $entity_type = $this->entity->type();
    $entityID = $this->entity->getIdentifier();
    $entity = $this->entity->value();

    $entity->cer_processed = TRUE;
    entity_save($entity_type, $entity);

    // Reload the entity we just saved and cleared from the static cache.
    $entities = entity_load($entity_type, (array) $entityID);
    $this->entity->set($entities[$entityID]);

    $this->__construct($this->field, $this->entity);
  }

  /**
   * Logs an error, optionally against a specific entity. If the cer_debug
   * variable is set, the error will also be set as a message.
   *
   * @param string $message
   *  The untranslated message to log.
   *
   * @param EntityDrupalWrapper $entity
   *  The entity that has caused the error, if any.
   */
  protected function logError($message, EntityDrupalWrapper $entity = NULL) {
    $variables = array(
      '!field_name' => $this->field->name,
      '!field_type' => $this->field->fieldTypeLabel,
      '!field_label' => $this->field->label,
    );

    $variables['!this_type'] = $this->entity->type();
    $variables['!this_label'] = $this->entity->label();

    // If the entity has a URI, provide a link to it. Otherwise, its "link"
    // will just be an unlinked label. Entity API doesn't reliably expose a url
    // property on entities, and there doesn't appear to be a way to check for
    // it without risking an EntityMetadataWrapperException. So I need to use
    // this clunky BS instead...ugh.
    $this_uri = entity_uri($this->entity->type(), $this->entity->value());
    if (isset($this_uri)) {
      $variables['!this_url'] = url($this_uri['path'], $this_uri['options']);
      $variables['!this_link'] = l($this->entity->label(), $this_uri['path'], $this_uri['options']);
    }
    else {
      $variables['!this_link'] = $this->entity->label();
    }

    if ($entity) {
      $variables['!that_type'] = $entity->type();
      $variables['!that_label'] = $entity->label();

      // If the entity has a URI, link to it.
      $that_uri = entity_uri($entity->type(), $entity->value());
      if (isset($that_uri)) {
        $variables['!that_url'] = url($that_uri['path'], $that_uri['options']);
        $variables['!that_link'] = l($entity->label(), $that_uri['path'], $that_uri['options']);
      }
      else {
        $variables['!that_link'] = $entity->label();
      }
    }

    watchdog('cer', $message, $variables, WATCHDOG_ERROR);

    if (variable_get('cer_debug', FALSE)) {
      drupal_set_message(t($message, $variables), 'error');
    }
  }

  public function getIDs() {
    $IDs = array();

    if ($this->isMultiValue) {
      foreach ($this->value as $ref) {
        $IDs[] = $ref->raw();
      }
    }
    else {
      $IDs[] = $this->value->raw();
    }

    return array_unique(array_filter($IDs));
  }

  /**
   * Implements Countable::count().
   */
  public function count() {
    if ($this->isMultiValue) {
      return sizeof($this->value);
    }
    else {
      return ($this->value->value() ? 1 : 0);
    }
  }

  /**
   * Implements SeekableIterator::seek().
   */
  public function seek($position) {
    $length = $this->count();

    if ($position < 0) {
      $position += $length;
    }

    if ($position >= 0 && $position < $length) {
      $this->delta = $position;
    }
    else {
      throw new OutOfBoundsException(t('Cannot seek to invalid position.'));
    }
  }

  /**
   * Implements Iterator::current().
   */
  public function current() {
    return ($this->isMultiValue ? $this->value[$this->delta] : $this->value);
  }

  /**
   * Implements Iterator::key().
   */
  public function key() {
    return $this->current()->getIdentifier();
  }

  /**
   * Implements Iterator::next().
   */
  public function next() {
    $this->delta++;
  }
  
  /**
   * Implements Iterator::rewind().
   */
  public function rewind() {
    $this->delta = 0;
  }

  /**
   * Implements Iterator::valid().
   */
  public function valid() {
    return ($this->delta < $this->count());
  }

}
 