<?php
/**
 * @file
 * assessment_gradebook_ux.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function assessment_gradebook_ux_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_actions|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_actions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_submission_details';
  $field_group->data = array(
    'label' => 'Evaluate',
    'weight' => '23',
    'children' => array(
      0 => 'submission_evaluation_form',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Evaluate',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-actions field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_actions|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assignment_description|node|assessment_assignment|gradebook_viewer';
  $field_group->group_name = 'group_assignment_description';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'assessment_assignment';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Assignment Description',
    'weight' => '3',
    'children' => array(
      0 => 'body',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Assignment Description',
      'instance_settings' => array(
        'classes' => 'group-assignment-description field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_assignment_description|node|assessment_assignment|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assignment|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_assignment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_submission_details';
  $field_group->data = array(
    'label' => 'Assignment',
    'weight' => '21',
    'children' => array(
      0 => 'assignment_block',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-assignment field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_assignment|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_submission_details';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '20',
    'children' => array(
      0 => 'field_assignment',
      1 => 'og_group_ref',
      2 => 'author',
      3 => 'post_date',
      4 => 'changed_date',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-details field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_details|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_files|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '20',
    'children' => array(
      0 => 'field_files',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-files field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_files|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '18',
    'children' => array(
      0 => 'field_images',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Images',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-images field-group-tab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_images|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_links|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '21',
    'children' => array(
      0 => 'field_links',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-links field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_links|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '3',
    'children' => array(
      0 => 'group_images',
      1 => 'group_video',
      2 => 'group_links',
      3 => 'group_files',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Media',
      'instance_settings' => array(
        'classes' => 'group-media field-group-htabs',
      ),
    ),
  );
  $field_groups['group_media|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_past_submissions|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_past_submissions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_submission_details';
  $field_group->data = array(
    'label' => 'Past submissions',
    'weight' => '22',
    'children' => array(
      0 => 'other_submissions',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-past-submissions field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_past_submissions|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_submission_details|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_submission_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Submission Details',
    'weight' => '0',
    'children' => array(
      0 => 'group_details',
      1 => 'group_assignment',
      2 => 'group_past_submissions',
      3 => 'group_actions',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Submission Details',
      'instance_settings' => array(
        'classes' => 'group-submission-details field-group-htabs',
      ),
    ),
  );
  $field_groups['group_submission_details|node|cle_submission|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_video|node|cle_submission|gradebook_viewer';
  $field_group->group_name = 'group_video';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Video',
    'weight' => '19',
    'children' => array(
      0 => 'field_video',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_video|node|cle_submission|gradebook_viewer'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Assignment');
  t('Assignment Description');
  t('Details');
  t('Evaluate');
  t('Files');
  t('Images');
  t('Links');
  t('Media');
  t('Past submissions');
  t('Submission Details');
  t('Video');

  return $field_groups;
}
