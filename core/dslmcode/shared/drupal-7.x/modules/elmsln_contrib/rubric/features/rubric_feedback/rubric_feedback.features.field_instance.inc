<?php
/**
 * @file
 * rubric_feedback.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function rubric_feedback_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'field_collection_item-field_rubric_feedback_item-field_feeback_levels'
  $field_instances['field_collection_item-field_rubric_feedback_item-field_feeback_levels'] = array(
    'bundle' => 'field_rubric_feedback_item',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_feeback_levels',
    'label' => 'Related levels',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'og_context' => 0,
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_feedback_item-field_feedback_entity'
  $field_instances['field_collection_item-field_rubric_feedback_item-field_feedback_entity'] = array(
    'bundle' => 'field_rubric_feedback_item',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_feedback_entity',
    'label' => 'Related entity',
    'required' => 1,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'og_context' => 0,
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_feedback_item-field_feedback_points'
  $field_instances['field_collection_item-field_rubric_feedback_item-field_feedback_points'] = array(
    'bundle' => 'field_rubric_feedback_item',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_feedback_points',
    'label' => 'Points',
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

  // Exported field_instance: 'field_collection_item-field_rubric_feedback_item-field_feedback_possible'
  $field_instances['field_collection_item-field_rubric_feedback_item-field_feedback_possible'] = array(
    'bundle' => 'field_rubric_feedback_item',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_feedback_possible',
    'label' => 'Possible',
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
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_feedback_item-field_feedback_text'
  $field_instances['field_collection_item-field_rubric_feedback_item-field_feedback_text'] = array(
    'bundle' => 'field_rubric_feedback_item',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_feedback_text',
    'label' => 'Feedback Text',
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
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_rubric_feedback_item-field_rubric_feedback_audio'
  $field_instances['field_collection_item-field_rubric_feedback_item-field_rubric_feedback_audio'] = array(
    'bundle' => 'field_rubric_feedback_item',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file_entity',
        'settings' => array(
          'autoplay' => FALSE,
          'controls' => TRUE,
          'loop' => FALSE,
          'multiple_file_behavior' => 'tags',
        ),
        'type' => 'file_audio',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_rubric_feedback_audio',
    'label' => 'Audio Feedback',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'audiofeedback',
      'file_extensions' => 'mp3 wav',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media_recorder',
      'settings' => array(
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
        'progress_indicator' => 'bar',
      ),
      'type' => 'media_recorder',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_assessment_assignment'
  $field_instances['node-rubric_submission_assessment-field_assessment_assignment'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_assessment_assignment',
    'label' => 'Assignment',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_assessment_feedback'
  $field_instances['node-rubric_submission_assessment-field_assessment_feedback'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
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
    'field_name' => 'field_assessment_feedback',
    'label' => 'Overall Feedback',
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
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_assessment_points_earned'
  $field_instances['node-rubric_submission_assessment-field_assessment_points_earned'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
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
    'field_name' => 'field_assessment_points_earned',
    'label' => 'Points Earned',
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_assessment_points_possible'
  $field_instances['node-rubric_submission_assessment-field_assessment_points_possible'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_hidden',
        'settings' => array(
          'prefix_suffix' => TRUE,
          'thousand_separator' => ' ',
        ),
        'type' => 'field_hidden_integer',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_assessment_points_possible',
    'label' => 'Points Possible',
    'required' => 1,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_hidden',
      'settings' => array(),
      'type' => 'field_hidden',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_assessment_red_pen'
  $field_instances['node-rubric_submission_assessment-field_assessment_red_pen'] = array(
    'bundle' => 'rubric_submission_assessment',
    'deleted' => 0,
    'description' => 'Use this field to mark up student work when its about images',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_assessment_red_pen',
    'label' => 'Red Pen',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'redpen',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'canvas_field',
      'settings' => array(
        'buttons' => array(
          'color' => TRUE,
          'paint' => FALSE,
          'pen' => TRUE,
          'reset' => TRUE,
        ),
        'color' => 1,
        'mode_edit' => 1,
        'mode_start' => 0,
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
        'style' => array(
          'background-color' => '',
          'border-color' => '#CCC',
          'border-style' => 'solid',
          'border-width' => 5,
          'height' => 300,
          'width' => 300,
        ),
      ),
      'type' => 'canvas_widget',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_assessment_submission'
  $field_instances['node-rubric_submission_assessment-field_assessment_submission'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_assessment_submission',
    'label' => 'Submission',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'og_context' => 0,
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_referenced_rubric'
  $field_instances['node-rubric_submission_assessment-field_referenced_rubric'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_referenced_rubric',
    'label' => 'Rubric',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'og_context' => 0,
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_rubric_feedback_audio'
  $field_instances['node-rubric_submission_assessment-field_rubric_feedback_audio'] = array(
    'bundle' => 'rubric_submission_assessment',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file_entity',
        'settings' => array(
          'autoplay' => FALSE,
          'controls' => TRUE,
          'loop' => FALSE,
          'multiple_file_behavior' => 'tags',
        ),
        'type' => 'file_audio',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_rubric_feedback_audio',
    'label' => 'Audio Feedback',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'audiofeedback',
      'file_extensions' => 'wav mp3',
      'max_filesize' => '10MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media_recorder',
      'settings' => array(
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
        'progress_indicator' => 'bar',
      ),
      'type' => 'media_recorder',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-field_rubric_feedback_item'
  $field_instances['node-rubric_submission_assessment-field_rubric_feedback_item'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection_tabs',
        'settings' => array(
          'title_field' => 'field_feedback_points',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_tabs',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_rubric_feedback_item',
    'label' => 'Feedback',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_collection',
      'settings' => array(
        'collapsed' => 1,
        'last_item_collapsed' => 1,
      ),
      'type' => 'field_collection_hidden',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-rubric_submission_assessment-og_group_ref'
  $field_instances['node-rubric_submission_assessment-og_group_ref'] = array(
    'bundle' => 'rubric_submission_assessment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'og_ui',
        'settings' => array(),
        'type' => 'og_list_default',
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
    'field_name' => 'og_group_ref',
    'label' => 'Groups audience',
    'required' => FALSE,
    'settings' => array(
      'behaviors' => array(
        'og_widget' => array(
          'admin' => array(
            'widget_type' => 'entityreference_autocomplete',
          ),
          'default' => array(
            'widget_type' => 'options_select',
          ),
          'status' => TRUE,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'custom settings' => FALSE,
        'label' => 'Full',
        'type' => 'og_list_default',
      ),
      'teaser' => array(
        'custom settings' => FALSE,
        'label' => 'Teaser',
        'type' => 'og_list_default',
      ),
    ),
    'widget' => array(
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => 6,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assignment');
  t('Audio Feedback');
  t('Feedback');
  t('Feedback Text');
  t('Groups audience');
  t('Overall Feedback');
  t('Points');
  t('Points Earned');
  t('Points Possible');
  t('Possible');
  t('Red Pen');
  t('Related entity');
  t('Related levels');
  t('Rubric');
  t('Submission');
  t('Use this field to mark up student work when its about images');

  return $field_instances;
}
