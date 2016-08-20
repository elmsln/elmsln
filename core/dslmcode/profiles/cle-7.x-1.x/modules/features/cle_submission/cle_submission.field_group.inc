<?php
/**
 * @file
 * cle_submission.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_submission_field_group_info() {
  $field_groups = array();

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
    'weight' => '5',
    'children' => array(
      0 => 'field_energy',
      1 => 'og_group_ref',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Admin',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-admin field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_admin|node|cle_submission|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ferpacontent|node|cle_submission|full';
  $field_group->group_name = 'group_ferpacontent';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Ferpa elements',
    'weight' => '3',
    'children' => array(
      0 => 'body',
      1 => 'field_files',
      2 => 'field_images',
      3 => 'field_links',
      4 => 'field_video',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Ferpa elements',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-ferpacontent field-group-div ferpa-protect',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ferpacontent|node|cle_submission|full'] = $field_group;

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
    'weight' => '3',
    'children' => array(
      0 => 'field_files',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Files',
      'instance_settings' => array(
        'classes' => 'group-files field-group-accordion-item',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_files|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_files|node|cle_submission|form';
  $field_group->group_name = 'group_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '15',
    'children' => array(
      0 => 'field_files',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Files',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_files|node|cle_submission|form'] = $field_group;

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
    'weight' => '1',
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
  $field_groups['group_images|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|cle_submission|form';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '13',
    'children' => array(
      0 => 'field_images',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Images',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_images|node|cle_submission|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_info|node|cle_submission|critique';
  $field_group->group_name = 'group_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'critique';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Information',
    'weight' => '0',
    'children' => array(
      0 => 'field_assignment',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Information',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'cle__info',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_info|node|cle_submission|critique'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_info|node|cle_submission|full';
  $field_group->group_name = 'group_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Information',
    'weight' => '2',
    'children' => array(
      0 => 'field_assignment',
      1 => 'field_submission_state',
      2 => 'submitted_by',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Information',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'cle__info',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_info|node|cle_submission|full'] = $field_group;

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
    'weight' => '4',
    'children' => array(
      0 => 'field_links',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Links',
      'instance_settings' => array(
        'classes' => 'group-links field-group-accordion-item',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_links|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_links|node|cle_submission|form';
  $field_group->group_name = 'group_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '16',
    'children' => array(
      0 => 'field_links',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Links',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_links|node|cle_submission|form'] = $field_group;

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
    'weight' => '1',
    'children' => array(
      0 => 'group_files',
      1 => 'group_images',
      2 => 'group_links',
      3 => 'group_video',
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
  $field_groups['group_media|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|cle_submission|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '3',
    'children' => array(
      0 => 'group_files',
      1 => 'group_images',
      2 => 'group_links',
      3 => 'group_video',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Media',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_media|node|cle_submission|form'] = $field_group;

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
    'weight' => '2',
    'children' => array(
      0 => 'field_video',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Video',
      'instance_settings' => array(
        'classes' => 'group-video field-group-accordion-item',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_video|node|cle_submission|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_video|node|cle_submission|form';
  $field_group->group_name = 'group_video';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_submission';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Video',
    'weight' => '14',
    'children' => array(
      0 => 'field_video',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Video',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_video|node|cle_submission|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Admin');
  t('Ferpa elements');
  t('Files');
  t('Images');
  t('Information');
  t('Links');
  t('Media');
  t('Video');

  return $field_groups;
}
