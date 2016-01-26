<?php
/**
 * @file
 * mooc_sar.features.inc
 */

/**
 * Implements hook_views_default_views_alter().
 */
function mooc_sar_views_default_views_alter(&$data) {
  if (isset($data['book_sar'])) {
    $data['book_sar']->display['default']->display_options['fields']['views_bulk_operations']['vbo_operations']['action::hidden_nodes_hide_action'] = array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ); /* WAS: '' */
    $data['book_sar']->display['default']->display_options['fields']['views_bulk_operations']['vbo_operations']['action::hidden_nodes_unhide_action'] = array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ); /* WAS: '' */
    $data['book_sar']->display['default']->display_options['fields']['views_bulk_operations']['vbo_operations']['action::vbo_search_and_replace_action']['settings']['checkbox_columns'] = 0; /* WAS: 1 */
    $data['book_sar']->display['default']->display_options['fields']['views_bulk_operations']['vbo_operations']['action::views_bulk_operations_modify_action'] = array(
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
    ); /* WAS: '' */
    $data['book_sar']->display['default']->display_options['fields']['views_bulk_operations']['vbo_operations']['action::views_bulk_operations_move_to_book_action'] = array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ); /* WAS: '' */
    $data['book_sar']->display['default']->display_options['fields']['views_bulk_operations']['vbo_operations']['action::views_bulk_operations_remove_from_book_action'] = array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ); /* WAS: '' */
  }
}
