<?php

/**
 * @file
 * API documentation for the entity_view_mode module.
 */

/**
 * Describe the view modes for entity types.
 *
 * View modes let entities be displayed differently depending on the context.
 * For instance, a node can be displayed differently on its own page ('full'
 * mode), on the home page or taxonomy listings ('teaser' mode), or in an RSS
 * feed ('rss' mode). Modules taking part in the display of the entity (notably
 * the Field API) can adjust their behavior depending on the requested view
 * mode. An additional 'default' view mode is available for all entity types.
 * This view mode is not intended for actual entity display, but holds default
 * display settings. For each available view mode, administrators can configure
 * whether it should use its own set of field display settings, or just
 * replicate the settings of the 'default' view mode, thus reducing the amount
 * of display configurations to keep track of.
 *
 * Note: This hook is invoked inside an implementation of
 * hook_entity_info_alter() so care must be taken not to call anything that
 * will result in an additional, and hence recurisve call to entity_get_info().
 *
 * @return array
 *   An associative array of all entity view modes, keyed by the entity
 *   type name, and then the view mode name, with the following keys:
 *   - label: The human-readable name of the view mode.
 *   - custom_settings: A boolean specifying whether the view mode should by
 *     default use its own custom field display settings. If FALSE, entities
 *     displayed in this view mode will reuse the 'default' display settings
 *     by default (e.g. right after the module exposing the view mode is
 *     enabled), but administrators can later use the Field UI to apply custom
 *     display settings specific to the view mode.
 *
 * @see entity_view_mode_entity_info_alter()
 * @see hook_entity_view_mode_info_alter()
 */
function hook_entity_view_mode_info() {
  $view_modes['user']['full'] = array(
    'label' => t('User account'),
  );
  $view_modes['user']['compact'] = array(
    'label' => t('Compact'),
    'custom_settings' => TRUE,
  );
  return $view_modes;
}

/**
 * Alter the view modes for entity types.
 *
 * Note: This hook is invoked inside an implementation of
 * hook_entity_info_alter() so care must be taken not to call anything that
 * will result in an additional, and hence recurisve call to entity_get_info().
 *
 * @param array $view_modes
 *   An array of view modes, keyed first by entity type, then by view mode name.
 *
 * @see entity_view_mode_entity_info_alter()
 * @see hook_entity_view_mode_info()
 */
function hook_entity_view_mode_info_alter(&$view_modes) {
  $view_modes['user']['full']['custom_settings'] = TRUE;
}
