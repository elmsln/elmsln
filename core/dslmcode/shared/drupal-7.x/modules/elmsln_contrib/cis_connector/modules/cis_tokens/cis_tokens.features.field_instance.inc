<?php
/**
 * @file
 * cis_tokens.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cis_tokens_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-section-field_cis_tokens'
  $field_instances['node-section-field_cis_tokens'] = array(
    'bundle' => 'section',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This is a list of token replacement|value pairs that can be used throughout the course. This is useful when wanting to centralize where you update noodle-y information throughout course content which might otherwise be standalone. For example, writing start_date|June 15, 2015 would allow you to write [ elmsln_section:start_date ] in your content and have it automatically replaced with June 15, 2015.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_cis_tokens',
    'label' => 'Tokens',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
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
        'rows' => 10,
      ),
      'type' => 'text_textarea',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('This is a list of token replacement|value pairs that can be used throughout the course. This is useful when wanting to centralize where you update noodle-y information throughout course content which might otherwise be standalone. For example, writing start_date|June 15, 2015 would allow you to write [ elmsln_section:start_date ] in your content and have it automatically replaced with June 15, 2015.');
  t('Tokens');

  return $field_instances;
}
