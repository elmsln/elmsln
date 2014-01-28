<?php
/**
 * @file
 * cis_ux.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cis_ux_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: context
  $overrides["context.regions_admin.conditions|path|values|~ajax*"]["DELETED"] = TRUE;
  $overrides["context.regions_admin.conditions|path|values|~node/*/*"]["DELETED"] = TRUE;
  $overrides["context.regions_admin.conditions|path|values|~node/edit/*"] = '~node/edit/*';

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.filters|lazyloader_filter"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => 0,
  );
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|1/2"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|1/3"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|1/4"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|1/5"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|1/6"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|1/8"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|2/3"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|2/5"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|3/4"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|3/5"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|3/8"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|4/5"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|5/6"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|5/8"] = 0;
  $overrides["filter.textbook_editor.filters|typogrify|settings|fractions|7/8"] = 0;

  return $overrides;
}
