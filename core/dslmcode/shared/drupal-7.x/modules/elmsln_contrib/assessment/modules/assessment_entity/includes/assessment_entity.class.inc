<?php

/**
 * @file
 * Assessment Entity class.
 */

/**
 * The class used for assessment_entity entities.
 */
class AssessmentEntity extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'assessment_entity');
  }

  /**
   * Defines the default entity label.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Defines the default entity URI.
   */
  protected function defaultUri() {
    return array('path' => 'assessment_entity/' . $this->assessment_entity_id);
  }
}

/**
 * The class used for Assessment Entity type entities.
 */
class AssessmentEntityType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'assessment_entity_type');
  }
}
