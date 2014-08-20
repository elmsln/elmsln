<?php

/**
 * @file
 * Hooks provided by Path Breadcrumbs module.
 */

/**
 * Expose Path Breadcrumbs settings.
 *
 * This hook is called by CTools. For this hook to work, you need
 * hook_ctools_plugin_api(). The values of this hook can be overridden
 * and reverted through the UI.
 *
 * @return array
 *   Array with importable objects.
 */
function hook_path_breadcrumbs_settings_info() {
  $path_breadcrumbs = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'example_breadcrumb';
  $path_breadcrumb->name = 'Example breadcrumb';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Content',
      1 => '%node:title',
      2 => '%node:comment-count',
    ),
    'paths' => array(
      0 => 'node',
      1 => 'node/%node:nid',
      2 => '<none>',
    ),
    'home' => 1,
    'translatable' => 0,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(),
  );
  $path_breadcrumb->weight = 0;

  $path_breadcrumbs['example_breadcrumb'] = $path_breadcrumb;

  return $path_breadcrumbs;
}

/**
 * Respond to saving path_breadcrumbs.
 *
 * This hook is invoked after creating new path_breadcrumbs or updating
 * existing one.
 * @param object $path_breadcrumbs
 *    Object with all necessary information from saving form.
 */
function hook_path_breadcrumbs_save($path_breadcrumbs) {
  // @todo Needs function body.
}

/**
 * Respond to path_breadcrumbs deletion.
 *
 * This hook is invoked before path_breadcrumbs variant is removed from
 * the database.
 *
 * @param object $path_breadcrumbs
 */
function hook_path_breadcrumbs_delete($path_breadcrumbs) {
  // @todo Needs function body.
}

/**
 * Act on a path_breadcrumbs object is preparing for view.
 *
 * This hook is invoked before any token replacement.
 *
 * @param object $path_breadcrumbs
 *    Object with path breadcrumb variant loaded from database.
 * @param array $contexts
 *    Ctools contexts from current URL.
 * @return object $path_breadcrumbs
 */
function hook_path_breadcrumbs_view(&$path_breadcrumbs, $contexts) {
  // @todo Needs function body.
}

/**
 * Alter built breadcrumbs.
 *
 * This hook is invoked after breadcrumbs were built or after they were loaded from cache.
 *
 * @param array $breadcrumbs
 *    Alterable array of build breadcrumbs.
 * @param object $path_breadcrumbs
 *    Unalterable object contains both processed and raw titles and paths.
 * @param array $contexts
 *    Ctools contexts from current URL.
 */
function hook_path_breadcrumbs_view_alter(&$breadcrumbs, $path_breadcrumbs, $contexts) {
  // @todo Needs function body.
  if ($path_breadcrumbs->from_cache == FALSE) {
    // Do heavy work here.
  }
  else {
    // Alter cached items here.
  }
}

/**
 * Possibility to add custom breadcrumb settings on 4th step.
 * See example: https://drupal.org/node/1946760#comment-7194426
 */
function hook_path_breadcrumbs_settings_form_custom_alter(&$form, $path_breadcrumbs) {
  // @todo Needs function body.
}

/**
 * Possibility to implement custom breadcrumb settings on 4th step.
 */
function hook_path_breadcrumbs_settings_form_submit_custom_alter(&$custom, $form_state) {
  // @todo Needs function body.
}

/**
 * Alter CTools cleanstring settings for Path Breadcrumbs URLs.
 * @see ctools_cleanstring() function for more info.
 */
function hook_ctools_cleanstring_path_breadcrumbs_url_alter(&$clean_settings) {
  // Disable transliteration (https://drupal.org/project/transliteration).
  $clean_settings['transliterate'] = FALSE;
  // Allow non-ASCII symbols.
  $clean_settings['reduce ascii'] = FALSE;
  // Use underscore as a separator.
  $clean_settings['separator'] = '_';
}
