<?php

/**
 * @file
 * Assessment Item class.
 */

/**
 * The class used for assessment_item entities.
 */
class AssessmentItem extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'assessment_item');
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
    return array('path' => 'assessment_item/' . $this->assessment_item_id);
  }
}

/**
 * The class used for Assessment Item type entities.
 */
class AssessmentItemType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'assessment_item_type');
  }
}
