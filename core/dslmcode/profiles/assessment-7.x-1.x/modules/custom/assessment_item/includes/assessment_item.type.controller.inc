<?php

/**
 * @file
 * Assessment Item controller class.
 */

/**
 * The Controller for Assessment Item entities.
 */
class AssessmentItemTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Assessment Item type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Assessment Item.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
