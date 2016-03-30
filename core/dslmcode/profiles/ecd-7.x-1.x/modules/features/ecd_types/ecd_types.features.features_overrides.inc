<?php
/**
 * @file
 * ecd_types.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function ecd_types_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: ds_layout_settings
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_accessibility_audit"] = 'right';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_cis_course_uuid"] = 'left';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_copyright_audit"] = 'right';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_course_address"] = 'left';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_course_machine_name"] = 'left';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_last_quality_date"] = 'right';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_notes"] = 'footer';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_quality_audit"] = 'right';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|field_resource_uuid_bind"] = 'footer';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|group_audits"] = 'right';
  $overrides["ds_layout_settings.node|cis_course|form.settings|fields|path"] = 'hidden';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|footer|3"]["DELETED"] = TRUE;
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|footer|5"] = 'field_notes';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|footer|6"] = 'field_resource_uuid_bind';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|hidden|4"]["DELETED"] = TRUE;
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|hidden|7"] = 'path';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|hidden|8"] = '_add_existing_field';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|left|1"] = 'field_course_machine_name';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|left|2"] = 'field_cis_course_uuid';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|left|3"] = 'field_course_address';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|1"]["DELETED"] = TRUE;
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|10"] = 'field_copyright_audit';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|11"] = 'field_quality_audit';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|12"] = 'field_last_quality_date';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|2"]["DELETED"] = TRUE;
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|4"] = 'group_audits';
  $overrides["ds_layout_settings.node|cis_course|form.settings|regions|right|9"] = 'field_accessibility_audit';

 return $overrides;
}
