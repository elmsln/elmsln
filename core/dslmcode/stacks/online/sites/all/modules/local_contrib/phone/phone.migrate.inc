<?php
/**
 * @file phone.migrate.inc
 * Code to implement hook_content_migrate_field_alter, content_migrate_instance_alter() and content_migrate_data_record_alter()
 * on behalf of the former phone module, moved into a separate file for efficiency.
 */

/**
 * Implements hook_content_migrate_field_alter().
 * 
 * Use this to tweak the conversion of field settings
 * from the D6 style to the D7 style for specific
 * situations not handled by basic conversion,
 * as when field types or settings are changed.
 */
function phone_field_alter(&$field_value, $instance_value) {
  if (substr($field_value['type'], 2) === '_phone') {
    $code = substr($field_value['type'], 0, 2);
    $field_value['type'] = 'phone';
    $field_value['settings']['country'] = $code;
  }
}

/**
 * Implements hook_migrate_api().
 */
function phone_migrate_api() {
  return array('api' => 2);
}

/**
 * Wrap Migrate's simple field handler for 'phone' fields.
 */
class MigratePhoneFieldHandler extends MigrateSimpleFieldHandler {

  public function __construct() {
    $this->registerTypes(array('phone'));
  }

}
