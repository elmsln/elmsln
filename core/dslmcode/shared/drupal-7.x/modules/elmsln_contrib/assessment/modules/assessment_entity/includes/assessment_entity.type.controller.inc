<?php

/**
 * @file
 * Assessment Entity controller class.
 */

/**
 * The Controller for Assessment Entity entities.
 */
class AssessmentEntityTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Assessment Entity type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Assessment Entity.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
