<?php
/**
 * @file
 * Drupal Field Hidden module Migration integration
 */

/**
 * Registers field hidden field types as ordinary 'value' based field types, because that suffices.
 */
class FieldHiddenMigrateFieldHandler extends MigrateSimpleFieldHandler {
  public function __construct() {
    parent::__construct(array(
      'value_key' => 'value',
      'skip_empty' => FALSE,
    ));
    $this->registerTypes(
      array(
        'field_hidden_text',
        'field_hidden_text_long',
        'field_hidden_integer',
        'field_hidden_decimal',
        'field_hidden_float'
      )
    );
  }
}