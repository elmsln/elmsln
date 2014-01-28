<?php
/**
 * @file
 * mooc_cis_ux.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_cis_ux_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field
  $overrides["field.node-section-field_instructional_outlines.field_config|active"] = 1;
  $overrides["field.node-section-field_instructional_outlines.field_config|cardinality"] = -1;
  $overrides["field.node-section-field_instructional_outlines.field_config|deleted"] = 0;
  $overrides["field.node-section-field_instructional_outlines.field_config|translatable"] = 0;
  $overrides["field.node-section-field_instructional_outlines.field_instance|deleted"] = 0;
  $overrides["field.node-section-field_instructional_outlines.field_instance|settings|behaviors|prepopulate|skip_perm"] = 0;
  $overrides["field.node-section-field_instructional_outlines.field_instance|widget|weight"] = 3;

  return $overrides;
}
