<?php
/**
 * @file
 * harmony_atjs.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function harmony_atjs_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.widget|settings|atjs_fieldset"] = array(
    'atjs' => 1,
    'atjs_listeners' => array(
      'harmony_users' => 'harmony_users',
    ),
  );

  // Exported overrides for: filter
  $overrides["filter.harmony_filtered.filters|atjs"] = array(
    'settings' => array(
      'atjs_listeners' => array(
        'harmony_users' => 'harmony_users',
      ),
    ),
    'status' => 1,
    'weight' => -44,
  );

 return $overrides;
}
