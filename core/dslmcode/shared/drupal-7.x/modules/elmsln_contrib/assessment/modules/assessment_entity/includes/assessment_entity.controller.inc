<?php

/**
 * @file
 * Assessment Entity controller class.
 */

/**
 * The Controller for Assessment Entity entities.
 */
class AssessmentEntityController extends EntityAPIController {
  /**
   * Create a Assessment Entity.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our entity.
    $values += array(
      'assessment_entity_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
