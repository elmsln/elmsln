<?php

/**
 * @file
 * Contains the CER plugin for User Reference fields.
 */

class CerUserReferenceField extends CerField {

  /**
   * Implements CerField::getTargetType().
   */
  public function getTargetType() {
    return 'user';
  }

}
 