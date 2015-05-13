<?php
/**
 * @file
 * cle_submission.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_submission_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_admin|node|cle_submission|form';
  $field_group->group_name = 'group_admin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Admin',
    'weight' => '7',
    'children' => array(
      0 => 'field_energy',
      1 => 'og_group_ref',
      2 => 'field_submission_state',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-admin field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_admin|node|cle_submission|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_files|node|cle_submission|default';
  $field_group->group_name = 'group_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '21',
    'children' => array(
      0 => 'field_files',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => 'group-files field-group-accordion-item',
      ),
    ),
  );
  $export['group_files|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|cle_submission|default';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '19',
    'children' => array(
      0 => 'field_images',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Images',
      'instance_settings' => array(
        'classes' => 'group-images field-group-accordion-item',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_images|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_links|node|cle_submission|default';
  $field_group->group_name = 'group_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '22',
    'children' => array(
      0 => 'field_links',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => 'group-links field-group-accordion-item',
      ),
    ),
  );
  $export['group_links|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|cle_submission|default';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '4',
    'children' => array(
      0 => 'group_images',
      1 => 'group_video',
      2 => 'group_files',
      3 => 'group_links',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'label' => 'Media',
      'instance_settings' => array(
        'classes' => 'group-media field-group-accordion',
        'description' => '',
        'effect' => 'bounceslide',
      ),
    ),
  );
  $export['group_media|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_video|node|cle_submission|default';
  $field_group->group_name = 'group_video';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Video',
    'weight' => '20',
    'children' => array(
      0 => 'field_video',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => 'group-video field-group-accordion-item',
      ),
    ),
  );
  $export['group_video|node|cle_submission|default'] = $field_group;

  return $export;
}
