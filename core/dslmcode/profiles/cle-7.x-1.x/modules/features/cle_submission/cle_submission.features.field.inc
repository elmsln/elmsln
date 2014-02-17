<?php
/**
 * @file
 * cle_submission.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function cle_submission_field_default_fields() {
  $fields = array();

  // Exported field: 'comment-comment_node_cle_submission-comment_body'.
  $fields['comment-comment_node_cle_submission-comment_body'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'comment',
      ),
      'field_name' => 'comment_body',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(

      ),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'comment_node_cle_submission',
      'default_value' => NULL,
      'deleted' => '0',
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
      'entity_type' => 'comment',
      'field_name' => 'comment_body',
      'label' => 'Comment',
      'required' => 1,
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
                'weight' => '10',
              ),
              'student_work' => array(
                'weight' => '0',
              ),
              'textbook_editor' => array(
                'weight' => '-10',
              ),
            ),
          ),
        ),
        'text_processing' => '1',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => 0,
      ),
    ),
  );

  // Exported field: 'node-cle_submission-body'.
  $fields['node-cle_submission-body'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'node',
      ),
      'field_name' => 'body',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(

      ),
      'translatable' => '0',
      'type' => 'text_with_summary',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '1',
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(
            'trim_length' => 600,
          ),
          'type' => 'text_summary_or_trimmed',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'body',
      'label' => 'Body',
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
                'weight' => '10',
              ),
              'student_work' => array(
                'weight' => '0',
              ),
              'textbook_editor' => array(
                'weight' => '-10',
              ),
            ),
          ),
        ),
        'display_summary' => 1,
        'text_processing' => '1',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '20',
          'summary_rows' => 5,
        ),
        'type' => 'text_textarea_with_summary',
        'weight' => '3',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-field_assignment'.
  $fields['node-cle_submission-field_assignment'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_assignment',
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 1,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(
            'cle_assignment' => 'cle_assignment',
          ),
        ),

        'target_type' => 'node',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'default_value' => NULL,
      'default_value_function' => 'entityreference_prepopulate_field_default_value',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'entityreference',
          'settings' => array(
            'link' => 1,
          ),
          'type' => 'entityreference_label',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_assignment',
      'label' => 'Assignment',
      'required' => 0,
      'settings' => array(
        'behaviors' => array(
          'prepopulate' => array(
            'action' => 'none',
            'action_on_edit' => 0,
            'fallback' => 'none',
            'og_context' => 0,
            'skip_perm' => '0',
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
        'weight' => '2',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-field_energy'.
  $fields['node-cle_submission-field_energy'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_energy',
      'foreign keys' => array(),
      'indexes' => array(
        'energy' => array(
          0 => 'radioactivity_energy',
        ),
      ),
      'locked' => '0',
      'module' => 'radioactivity',
      'settings' => array(

      ),
      'translatable' => '0',
      'type' => 'radioactivity',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'default_value' => array(
        0 => array(
          'radioactivity_energy' => '100',
          'radioactivity_timestamp' => '1363026125',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '4',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_energy',
      'label' => 'Energy',
      'required' => FALSE,
      'settings' => array(
        'profile' => 'cle_half_week',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'radioactivity',
        'settings' => array(),
        'type' => 'radioactivity_basic_widget',
        'weight' => '8',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-field_files'.
  $fields['node-cle_submission-field_files'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_files',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => '0',
      'module' => 'file',
      'settings' => array(
        'display_default' => 1,
        'display_field' => 0,

        'uri_scheme' => 'private',
      ),
      'translatable' => '0',
      'type' => 'file',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'file',
          'settings' => array(),
          'type' => 'file_table',
          'weight' => '6',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_files',
      'label' => 'Files',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'file_directory' => 'submission_files',
        'file_extensions' => 'txt doc docx pdf',
        'max_filesize' => '10MB',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'file',
        'settings' => array(
          'progress_indicator' => 'throbber',
        ),
        'type' => 'file_generic',
        'weight' => '6',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-field_images'.
  $fields['node-cle_submission-field_images'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_images',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => '0',
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,

        'uri_scheme' => 'private',
      ),
      'translatable' => '0',
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'flexslider_fields',
          'settings' => array(
            'flexslider_optionset' => 'cle_submission',
            'flexslider_reference_img_src' => NULL,
          ),
          'type' => 'flexslider',
          'weight' => '3',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_images',
      'label' => 'Images',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'file_directory' => 'submission_media',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'plup',
        'settings' => array(
          'image_style' => 'thumbnail',
        ),
        'type' => 'image_plupload',
        'weight' => '5',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-field_links'.
  $fields['node-cle_submission-field_links'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_links',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'link',
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'rel' => '',
          'target' => 'default',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,

        'title' => 'optional',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
      ),
      'translatable' => '0',
      'type' => 'link_field',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => '7',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_links',
      'label' => 'Links',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'configurable_title' => 0,
          'rel' => 'nofollow',
          'target' => 'default',
          'title' => '',
        ),
        'display' => array(
          'url_cutoff' => '80',
        ),
        'enable_tokens' => 1,
        'rel_remove' => 'default',
        'title' => 'optional',
        'title_maxlength' => '128',
        'title_value' => '',
        'url' => 0,
        'user_register_form' => FALSE,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_field',
        'weight' => '7',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-field_video'.
  $fields['node-cle_submission-field_video'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_video',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'video_embed_field',
      'settings' => array(

      ),
      'translatable' => '0',
      'type' => 'video_embed_field',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'video_embed_field',
          'settings' => array(
            'description' => 1,
            'video_style' => 'cle_default',
          ),
          'type' => 'video_embed_field',
          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_video',
      'label' => 'Video',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'description_length' => 128,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'video_embed_field',
        'settings' => array(),
        'type' => 'video_embed_field_video',
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'node-cle_submission-og_group_ref'.
  $fields['node-cle_submission-og_group_ref'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'og_group_ref',
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'og',
        'handler_settings' => array(
          'behaviors' => array(
            'og_behavior' => array(
              'status' => TRUE,
            ),
            'views-select-list' => array(
              'status' => 1,
            ),
          ),
          'membership_type' => 'og_membership_type_default',
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(
            'section' => 'section',
          ),
        ),
        'handler_submit' => 'Change handler',

        'target_type' => 'node',
      ),
      'target_type' => 'node',
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'cle_submission',
      'default_value' => NULL,
      'default_value_function' => 'entityreference_prepopulate_field_default_value',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '5',
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
      'label' => 'Section',
      'required' => 1,
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
          'prepopulate' => array(
            'action' => 'hide',
            'action_on_edit' => 1,
            'fallback' => 'none',
            'og_context' => 1,
            'skip_perm' => '0',
            'status' => 1,
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
        'active' => 0,
        'module' => 'og',
        'settings' => array(),
        'type' => 'og_complex',
        'weight' => '0',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assignment');
  t('Body');
  t('Comment');
  t('Energy');
  t('Files');
  t('Images');
  t('Links');
  t('Section');
  t('Video');

  return $fields;
}
