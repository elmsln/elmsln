<?php
/**
 * @file
 * mooc_helper.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_helper_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.cis_section_list.display|default|display_options|fields|field_instructional_outlines"] = array(
    'id' => 'field_instructional_outlines',
    'table' => 'field_data_field_instructional_outlines',
    'field' => 'field_instructional_outlines',
    'label' => 'Outline',
    'settings' => array(
      'link' => 1,
    ),
    'delta_offset' => 0,
  );

 return $overrides;
}
