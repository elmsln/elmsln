<?php
/**
 * @file
 * mooc_sar.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_sar_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.book_sar.display|default|display_options|fields|views_bulk_operations|vbo_operations|action::hidden_nodes_hide_action"] = array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  );
  $overrides["views_view.book_sar.display|default|display_options|fields|views_bulk_operations|vbo_operations|action::hidden_nodes_unhide_action"] = array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  );
  $overrides["views_view.book_sar.display|default|display_options|fields|views_bulk_operations|vbo_operations|action::vbo_search_and_replace_action|settings|checkbox_columns"] = 0;
  $overrides["views_view.book_sar.display|default|display_options|fields|views_bulk_operations|vbo_operations|action::views_bulk_operations_modify_action"] = array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 1,
    'override_label' => 1,
    'label' => 'Create Revision',
    'settings' => array(
      'show_all_tokens' => 1,
      'display_values' => array(
        'revision' => 'revision',
      ),
    ),
  );
  $overrides["views_view.book_sar.display|default|display_options|fields|views_bulk_operations|vbo_operations|action::views_bulk_operations_move_to_book_action"] = array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  );
  $overrides["views_view.book_sar.display|default|display_options|fields|views_bulk_operations|vbo_operations|action::views_bulk_operations_remove_from_book_action"] = array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  );

 return $overrides;
}
