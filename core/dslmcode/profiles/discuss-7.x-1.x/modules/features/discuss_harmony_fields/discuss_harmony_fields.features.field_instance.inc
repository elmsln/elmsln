<?php
/**
 * @file
 * discuss_harmony_fields.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function discuss_harmony_fields_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'harmony_thread-harmony_thread-field_cis_tag'
  $field_instances['harmony_thread-harmony_thread-field_cis_tag'] = array(
    'bundle' => 'harmony_thread',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'harmony_thread',
    'fences_wrapper' => 'div',
    'field_name' => 'field_cis_tag',
    'label' => 'Tag',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'harmony_filtered' => 'harmony_filtered',
          'plain_text' => 'plain_text',
          'student_format' => 'student_format',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'harmony_filtered' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_format' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 7,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Tag');

  return $field_instances;
}
