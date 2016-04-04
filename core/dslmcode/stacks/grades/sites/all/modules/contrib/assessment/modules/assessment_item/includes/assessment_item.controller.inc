<?php

/**
 * @file
 * Assessment Item controller class.
 */

/**
 * The Controller for Assessment Item entities.
 */
class AssessmentItemController extends EntityAPIController {
  /**
   * Create a Assessment Item.
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
      'assessment_item_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
