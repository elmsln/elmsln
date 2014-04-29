<?php

/**
 * @file
 * Support for the Migrate package.
 */
class MigrateEmailFieldHandler extends MigrateFieldHandler {

  public function __construct() {
    $this->registerTypes(array('email'));
  }

  public function prepare($entity, array $field_info, array $instance, array $values) {
    // Setup the Field API array for saving.
    $arguments = (isset($values['arguments'])) ? $values['arguments']: array();
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);
    $delta = 0;
    foreach ($values as $value) {
      $return[$language][$delta]['email'] = $value;
      $delta++;
    }
    return isset($return) ? $return : NULL;
  }
}
