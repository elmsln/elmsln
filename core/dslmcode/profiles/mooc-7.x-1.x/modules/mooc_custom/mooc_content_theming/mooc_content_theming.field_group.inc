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
  $field_group->parent_name = 'group_interface';
  $field_group->data = array(
    'label' => 'Colors',
    'weight' => '147',
    'children' => array(
      0 => 'field_fa_primary_color',
      1 => 'field_fa_secondary_color',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Colors',
      'instance_settings' => array(
        'required_fields' => 0,
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
  $field_group->identifier = 'group_inst_strat|node|page|form';
  $field_group->group_name = 'group_inst_strat';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_settings';
  $field_group->data = array(
    'label' => 'Strategies',
    'weight' => '140',
    'children' => array(
      0 => 'field_instructional_significance',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Strategies',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-inst-strat field-group-htab',
        'description' => 'Settings to apply instructional strategies to this material. Things like xAPI feedback, course significance, research and more.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_inst_strat|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_interface|node|page|form';
  $field_group->group_name = 'group_interface';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_settings';
  $field_group->data = array(
    'label' => 'Interface',
    'weight' => '141',
    'children' => array(
      0 => 'group_colors',
      1 => 'group_topic_banner',
      2 => 'group_navigation_block',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Interface',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-interface field-group-htab',
        'description' => 'Change interface elements such as navigation, colors and content banners.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_interface|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_banner|node|page|form';
  $field_group->group_name = 'group_topic_banner';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_interface';
  $field_group->data = array(
    'label' => 'Topic banner',
    'weight' => '146',
    'children' => array(
      0 => 'field_mooc_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Topic banner',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-topic-banner field-group-htab',
        'description' => 'Apply a content banner visually marking which lesson / unit / module is currently being explored.',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_topic_banner|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Colors');
  t('Interface');
  t('Strategies');
  t('Topic banner');

  return $field_groups;
}
