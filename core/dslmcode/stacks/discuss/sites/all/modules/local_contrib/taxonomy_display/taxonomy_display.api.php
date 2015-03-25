<?php

/**
 * @file
 * Hooks provided by the taxonomy_display module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter breadcrumb parents before rendering into breadcrumb on term page.
 *
 * This would be an ideal place to perform translation, set active menus, or
 * modify the crumbs.
 *
 * @param array $parents
 *   An array of term objects that are parents of the current term.
 *
 * @return void
 *
 * @see TaxonomyDisplayBreadcrumbDisplayHandlerCore::buildBreadcrumb()
 */
function hook_taxonomy_display_breadcrumb_parents_alter(&$parents) {
  // Manipulate or act upon the term parents.
  foreach ($parents as &$parent_term) {
    if ($parent_term->name == 'example alter') {
      $parent_term->name = 'a better term name';
    }
  }
}

/**
 * Provide plugins to taxonomy_display.
 * 
 * @return
 *   An associative array containing 'associated' and 'term' arrays listing 
 *   plugins for taxonomy_display to call. Within each array another associative
 *   array is provided where each key is a class name of the handler and the
 *   value is displayed to the administrator when selecting the plugin. Note
 *   that any class names provided must have their file listed in the containing
 *   module's .info file so that the class can be auto loaded.
 *
 * @see taxonomy_display_plugins()
 * @see taxonomy_display_taxonomy_display_plugins()
 */
function hook_taxonomy_display_plugins() {
  return array(
    'associated' => array(
      'HookAssociatedDisplayHandlerImplementingClassName' => t('My term display handler'),
    ),
    'term' => array(
      'HookTermDisplayHandlerImplementingClassName' => t('My associated display handler'),
    ),
  );
}

/**
 * Alter plugins list used by taxonomy_display.
 *
 * @param array $plugins
 *
 * @return void
 *
 * @see hook_taxonomy_display_plugins()
 * @see taxonomy_display_plugins()
 */
function hook_taxonomy_display_plugins_alter(&$plugins) {
  // Hijack taxonomy_display's Views plugin.
  if (isset($plugins['associated']['TaxonomyDisplayAssociatedDisplayHandlerViews'])) {
    // Remove this from even being an option to users!
    unset($plugins['associated']['TaxonomyDisplayAssociatedDisplayHandlerViews']);

    // Now hijack all existing taxonomy_display settings to use my plugin that
    // previously using taxonomy_display's Views plugin.
    $count = (bool) db_update('taxonomy_display')
        ->fields(array('associated_display_plugin', 'MyViewsPluginHandler'))
        ->condition('associated_display_plugin', 'TaxonomyDisplayAssociatedDisplayHandlerViews')
        ->execute();

    // Note that the plugin handler 'MyViewsPluginHandler' in the db_update()
    // should be defined in hook_taxonomy_display_plugins() to allow other
    // modules to overwrite it if desired.
  }
}

/**
 * Alter a vocabulary's taxonomy_display settings before save.
 *
 * @param array $save_data
 *   Associative array containing the values to save in the database, note that
 *   all associative keys listed in taxonomy_display_save_taxonomy_display() may
 *   not be available if plugins are missing upon save.
 *
 * @return void
 *
 * @see taxonomy_display_save_taxonomy_display()
 */
function hook_taxonomy_display_save_fields_alter(&$save_data) {
  // If this is a particular vocabulary
  if ($save_data['machine_name'] == 'my_vocabulary_name') {
    // If a particular term display plugin was selected.
    if ($save_data['term_display_plugin'] == 'HookAssociatedDisplayHandlerImplementingClassName') {
      // Set an option for the display plugin, note that key/values will be
      // unique to each plugin so the plugin's handler class should be
      // referenced to see what values are valid to set.
      // Note that after hook_taxonomy_display_save_fields_alter()
      // display_options are serialized before storage.
      $save_data['term_display_options']['show_feed'] = TRUE;
    }
    // Else set the term display to the hidden plugin.
    else {
      $save_data['term_display_plugin'] = 'TaxonomyDisplayTermDisplayHandlerHidden';
      // Set options to customize the display, in this case we don't set any.
      $save_data['term_display_options'] = NULL;
    }
  }
}

/**
 * Alter a term object before display on its term page.
 *
 * @return void
 *
 * @see taxonomy_display_taxonomy_term_page()
 */
function hook_taxonomy_display_term_page_term_object_alter(&$term) {
  // Manipulate or act upon term object.
  if ($term->vocabulary_machine_name == 'example') {
    if (empty($term->field_longtext['und'][0]['safe_value'])) {
      $term->field_longtext['und'][0]['value'] = t('Not provided');
      $term->field_longtext['und'][0]['safe_value'] = t('Not provided');
    }

    $term->name = t('Example: @name', array('@name' => $term->name));

    drupal_add_js(array('taxonomy_display' => array('mykey' => 'myvalue')), 'setting');
  }
}

/**
 * @} End of "addtogroup hooks".
 */
