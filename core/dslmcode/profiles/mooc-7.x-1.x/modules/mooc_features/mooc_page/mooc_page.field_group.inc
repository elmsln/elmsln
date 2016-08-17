<?php
/**
 * @file
 * mooc_page.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function mooc_page_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_advanced_tabs|node|page|form';
  $field_group->group_name = 'group_advanced_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_advanced';
  $field_group->data = array(
    'label' => 'Advanced tabs',
    'weight' => '125',
    'children' => array(
      0 => 'group_author',
      1 => 'group_outline',
      2 => 'group_tag',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-advanced-tabs field-group-htabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_advanced_tabs|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_advanced|node|page|form';
  $field_group->group_name = 'group_advanced';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_settings';
  $field_group->data = array(
    'label' => 'Advanced',
    'weight' => '146',
    'children' => array(
      0 => 'group_advanced_tabs',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Advanced',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-advanced field-group-tab',
        'description' => 'These settings allow for advanced capabilities and generally will not need modified.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_advanced|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_author|node|page|form';
  $field_group->group_name = 'group_author';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_advanced_tabs';
  $field_group->data = array(
    'label' => 'Author',
    'weight' => '129',
    'children' => array(
      0 => 'author',
      1 => 'revision_information',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Author',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-author field-group-htab',
        'description' => 'Modify authoring information of this content. This should only need modified if an author is no longer working on the course.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_author|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cis_tag_group|node|page|form';
  $field_group->group_name = 'group_cis_tag_group';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tags',
    'weight' => '3',
    'children' => array(
      0 => 'field_cis_tag',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Tags',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-cis-tag-group field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_cis_tag_group|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_outline|node|page|form';
  $field_group->group_name = 'group_outline';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_advanced_tabs';
  $field_group->data = array(
    'label' => 'Outline',
    'weight' => '127',
    'children' => array(
      0 => 'book',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Outline',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-outline field-group-htab',
        'description' => 'Use this to move content within the current outline or to break it out of its current outline over to another course outline. The weight has to do with the depth in the outline though the Outline Designer will adjust this automatically when dragging content around.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_outline|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_settings|node|page|form';
  $field_group->group_name = 'group_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Settings',
    'weight' => '2',
    'children' => array(
      0 => 'group_inst_strat',
      1 => 'group_interface',
      2 => 'group_advanced',
      3 => 'group_visibility',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-settings field-group-htabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_settings|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tag|node|page|form';
  $field_group->group_name = 'group_tag';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_advanced_tabs';
  $field_group->data = array(
    'label' => 'Tag',
    'weight' => '128',
    'children' => array(
      0 => 'field_cis_tag',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Tag',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-tag field-group-htab',
        'description' => 'Tag this resource if you plan on having multiple versions of it across sections. This allows for additional forms of short-codes which can figure out the correct "tagged" resource to use based on the section of the user viewing the tag. Only use this if you know why you are doing so as it is atypical.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_tag|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_visibility|node|page|form';
  $field_group->group_name = 'group_visibility';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_settings';
  $field_group->data = array(
    'label' => 'Visibility',
    'weight' => '145',
    'children' => array(
      0 => 'hidden_nodes',
      1 => 'options',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Visibility',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-visibility field-group-htab',
        'description' => 'Modify who can see this. Students won\'t see things marked Hidden, while unpublished will only show to the author of this piece of content.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_visibility|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Advanced');
  t('Advanced tabs');
  t('Author');
  t('Outline');
  t('Settings');
  t('Tag');
  t('Tags');
  t('Visibility');

  return $field_groups;
}
