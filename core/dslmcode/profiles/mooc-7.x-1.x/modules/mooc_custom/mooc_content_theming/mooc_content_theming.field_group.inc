<?php
/**
 * @file
 * mooc_content_theming.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function mooc_content_theming_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_colors|node|page|form';
  $field_group->group_name = 'group_colors';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_visuals';
  $field_group->data = array(
    'label' => 'Colors',
    'weight' => '143',
    'children' => array(
      0 => 'field_fa_primary_color',
      1 => 'field_fa_secondary_color',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Colors',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-colors field-group-htab',
        'description' => 'Modify the colors of primary and secondary headings in this page.',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_colors|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pedagogy|node|page|form';
  $field_group->group_name = 'group_pedagogy';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_settings';
  $field_group->data = array(
    'label' => 'Pedagogy',
    'weight' => '136',
    'children' => array(
      0 => 'field_instructional_significance',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Pedagogy',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-pedagogy field-group-htab',
        'description' => 'Modify settings that help illustrate the pedagogical significance of this content.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_pedagogy|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_banner|node|page|form';
  $field_group->group_name = 'group_topic_banner';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_visuals';
  $field_group->data = array(
    'label' => 'Topic banner',
    'weight' => '142',
    'children' => array(
      0 => 'field_mooc_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Topic banner',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-topic-banner field-group-htab',
        'description' => 'Apply a content banner visually marking which lesson / unit / module is currently being explored.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_topic_banner|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_visual_identifiers|node|page|form';
  $field_group->group_name = 'group_visual_identifiers';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Visual',
    'weight' => '3',
    'children' => array(
      0 => 'field_fa_primary_color',
      1 => 'field_fa_secondary_color',
      2 => 'field_instructional_significance',
      3 => 'field_mooc_image',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Visual',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_visual_identifiers|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_visuals|node|page|form';
  $field_group->group_name = 'group_visuals';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_settings';
  $field_group->data = array(
    'label' => 'Visuals',
    'weight' => '138',
    'children' => array(
      0 => 'group_colors',
      1 => 'group_topic_banner',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Visuals',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-visuals field-group-htab',
        'description' => 'These settings are also applied to any child content in the outline.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_visuals|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Colors');
  t('Pedagogy');
  t('Topic banner');
  t('Visual');
  t('Visuals');

  return $field_groups;
}
