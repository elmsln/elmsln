<?php
/**
 * @file
 * rubric_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function rubric_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'field_collection_item-field_rubric_categories-field_category_details'
  $field_instances['field_collection_item-field_rubric_categories-field_category_details'] = array(
    'bundle' => 'field_rubric_categories',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_category_details',
    'label' => 'Details',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 0,
          'student_work' => 'student_work',
          'textbook_editor' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_categories-field_category_title'
  $field_instances['field_collection_item-field_rubric_categories-field_category_title'] = array(
    'bundle' => 'field_rubric_categories',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_category_title',
    'label' => 'Title',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_work' => 'student_work',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
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
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_categories-field_rubric_criteria'
  $field_instances['field_collection_item-field_rubric_categories-field_rubric_criteria'] = array(
    'bundle' => 'field_rubric_categories',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'field_collection_tabs',
        'settings' => array(
          'title_field' => 'field_criteria_title',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_tabs',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_rubric_criteria',
    'label' => 'Criteria',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_collection_tabs_widget',
      'settings' => array(
        'fctw_add_new_tab_title' => '+',
        'fctw_empty_tab_title' => '- None -',
        'fctw_new_tab_title' => 'New Criteria',
        'fctw_title_field' => 'field_criteria_title',
        'fctw_title_field_formatter' => 'text_default',
      ),
      'type' => 'field_collection_tabs',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_criteria-field_criteria_details'
  $field_instances['field_collection_item-field_rubric_criteria-field_criteria_details'] = array(
    'bundle' => 'field_rubric_criteria',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_criteria_details',
    'label' => 'Details',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 0,
          'student_work' => 'student_work',
          'textbook_editor' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_criteria-field_criteria_title'
  $field_instances['field_collection_item-field_rubric_criteria-field_criteria_title'] = array(
    'bundle' => 'field_rubric_criteria',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_criteria_title',
    'label' => 'Title',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_work' => 'student_work',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
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
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_criteria-field_rubric_levels'
  $field_instances['field_collection_item-field_rubric_criteria-field_rubric_levels'] = array(
    'bundle' => 'field_rubric_criteria',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'rubric',
        'settings' => array(
          'level_content' => 1,
          'points_field' => 'field_level_points',
          'range_field' => 'field_level_points_range',
          'title_field' => 'field_level_title',
          'view_mode' => 'full',
        ),
        'type' => 'rubric_field_collection',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_rubric_levels',
    'label' => 'Levels',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_collection_tabs_widget',
      'settings' => array(
        'fctw_add_new_tab_title' => '+',
        'fctw_empty_tab_title' => '- None -',
        'fctw_new_tab_title' => 'New',
        'fctw_title_field' => 'field_level_title',
        'fctw_title_field_formatter' => 'text_default',
      ),
      'type' => 'field_collection_tabs',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_levels-field_default_feedback'
  $field_instances['field_collection_item-field_rubric_levels-field_default_feedback'] = array(
    'bundle' => 'field_rubric_levels',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The default feedback message given to students when you choose this option.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_default_feedback',
    'label' => 'Default Feedback',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_work' => 'student_work',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
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
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_levels-field_level_points'
  $field_instances['field_collection_item-field_rubric_levels-field_level_points'] = array(
    'bundle' => 'field_rubric_levels',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This is the default number of points awarded when you select the item for an assessment.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => 0,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_level_points',
    'label' => 'Default Points',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_levels-field_level_points_range'
  $field_instances['field_collection_item-field_rubric_levels-field_level_points_range'] = array(
    'bundle' => 'field_rubric_levels',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Range of possible values',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'rubric',
        'settings' => array(),
        'type' => 'rubric_level_range',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_level_points_range',
    'label' => 'Points Range',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_levels-field_level_rationale'
  $field_instances['field_collection_item-field_rubric_levels-field_level_rationale'] = array(
    'bundle' => 'field_rubric_levels',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This is your reasoning for assessing this level.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'textformatter',
        'settings' => array(
          'textformatter_class' => 'rubric-level-rationale textformatter-list',
          'textformatter_comma_and' => 0,
          'textformatter_comma_full_stop' => 0,
          'textformatter_comma_override' => 0,
          'textformatter_comma_tag' => 'div',
          'textformatter_contrib' => array(),
          'textformatter_separator_custom' => '',
          'textformatter_separator_custom_class' => 'textformatter-separator',
          'textformatter_separator_custom_tag' => 'span',
          'textformatter_term_plain' => 0,
          'textformatter_type' => 'ul',
        ),
        'type' => 'textformatter_list',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_level_rationale',
    'label' => 'Rationale',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_work' => 'student_work',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
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
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_levels-field_level_remediation'
  $field_instances['field_collection_item-field_rubric_levels-field_level_remediation'] = array(
    'bundle' => 'field_rubric_levels',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'These are suggestions for how they could have improved upon their work.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'textformatter',
        'settings' => array(
          'textformatter_class' => 'rubric-level-remediation textformatter-list',
          'textformatter_comma_and' => 0,
          'textformatter_comma_full_stop' => 0,
          'textformatter_comma_override' => 0,
          'textformatter_comma_tag' => 'div',
          'textformatter_contrib' => array(),
          'textformatter_separator_custom' => '',
          'textformatter_separator_custom_class' => 'textformatter-separator',
          'textformatter_separator_custom_tag' => 'span',
          'textformatter_term_plain' => 0,
          'textformatter_type' => 'ul',
        ),
        'type' => 'textformatter_list',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_level_remediation',
    'label' => 'Suggested Remediation',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_work' => 'student_work',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
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
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_levels-field_level_title'
  $field_instances['field_collection_item-field_rubric_levels-field_level_title'] = array(
    'bundle' => 'field_rubric_levels',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_level_title',
    'label' => 'Title',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_work' => 'student_work',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_work' => array(
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
        'size' => 50,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-elms_rubric-field_rubric_assessment_type'
  $field_instances['node-elms_rubric-field_rubric_assessment_type'] = array(
    'bundle' => 'elms_rubric',
    'default_value' => array(
      0 => array(
        'value' => 'rubric_submission_assessment',
      ),
    ),
    'deleted' => 0,
    'description' => 'How would you like to be able to assess this work?  Is this rubric for assessing submissions by others, evaluating peers, or for self assessment?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_rubric_assessment_type',
    'label' => 'Assessment Type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-elms_rubric-field_rubric_categories'
  $field_instances['node-elms_rubric-field_rubric_categories'] = array(
    'bundle' => 'elms_rubric',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'field_collection_tabs',
        'settings' => array(
          'title_field' => 'field_category_title',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_tabs',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_rubric_categories',
    'label' => 'Categories',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_collection_tabs_widget',
      'settings' => array(
        'fctw_add_new_tab_title' => '+',
        'fctw_empty_tab_title' => '- None -',
        'fctw_new_tab_title' => 'New Category',
        'fctw_title_field' => 'field_category_title',
        'fctw_title_field_formatter' => 'text_default',
      ),
      'type' => 'field_collection_tabs',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-elms_rubric-field_rubric_content'
  $field_instances['node-elms_rubric-field_rubric_content'] = array(
    'bundle' => 'elms_rubric',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_rubric_content',
    'label' => 'Content',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 0,
          'student_work' => 0,
          'textbook_editor' => 0,
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 1,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => -48,
            ),
            'student_work' => array(
              'weight' => -50,
            ),
            'textbook_editor' => array(
              'weight' => -49,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assessment Type');
  t('Categories');
  t('Content');
  t('Criteria');
  t('Default Feedback');
  t('Default Points');
  t('Details');
  t('How would you like to be able to assess this work?  Is this rubric for assessing submissions by others, evaluating peers, or for self assessment?');
  t('Levels');
  t('Points Range');
  t('Range of possible values');
  t('Rationale');
  t('Suggested Remediation');
  t('The default feedback message given to students when you choose this option.');
  t('These are suggestions for how they could have improved upon their work.');
  t('This is the default number of points awarded when you select the item for an assessment.');
  t('This is your reasoning for assessing this level.');
  t('Title');

  return $field_instances;
}
