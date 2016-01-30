<?php
/**
 * @file
 * discuss_thread.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function discuss_thread_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.fences_wrapper"] = 'div';
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|authcache"] = array(
    'clients' => array(
      'authcache_ajax' => array(
        'status' => 1,
        'weight' => 0,
      ),
    ),
    'fallback' => 'cancel',
    'lifespan' => 3600,
    'perpage' => 0,
    'peruser' => 1,
    'status' => 0,
  );
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|allowed_formats|filtered_html"]["DELETED"] = TRUE;
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|allowed_formats|full_html"]["DELETED"] = TRUE;
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|allowed_formats|harmony_filtered"] = 0;
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|allowed_formats|student_format"] = 'student_format';
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|allowed_formats|textbook_editor"] = 0;
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|default_order_wrapper|formats|filtered_html"]["DELETED"] = TRUE;
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|default_order_wrapper|formats|full_html"]["DELETED"] = TRUE;
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|default_order_wrapper|formats|student_format"] = array(
    'weight' => 0,
  );
  $overrides["field_instance.harmony_post-harmony_post-field_harmony_text.settings|better_formats|default_order_wrapper|formats|textbook_editor"] = array(
    'weight' => -10,
  );

 return $overrides;
}
