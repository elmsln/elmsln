<?php

/**
 * @file
 * Provide Views data and handlers for media.module
 */

/**
 * Implements hook_views_plugins().
 *
 * Generate a list of which base-tables to enabled the plugins for.
 */
function media_views_plugins() {
  $plugins = array();

  // Always allow the actual file-table
  $base = array('file_managed');

  if (module_exists('search_api')) {
    // If the Search API module exists, also allow indices of the file-entity
    // that has the fid field indexed.
    $indices = search_api_index_load_multiple(FALSE);
    foreach ($indices as $machine_name => $index) {
      if ($index->item_type == 'file' && isset($index->options['fields']['fid'])) {
        $base[] = 'search_api_index_' . $machine_name;
      }
    }
  }

  // Display plugin.
  $plugins['display']['media_browser'] = array(
    'title' => t('Media browser tab'),
    'help' => t('Display as a tab in the media browser.'),
    'handler' => 'media_views_plugin_display_media_browser',
    'theme' => 'views_view',
    'base' => $base,
    'use ajax' => TRUE,
    'use pager' => TRUE,
    'accept attachments' => TRUE,
  );

  // Style plugin.
  $plugins['style']['media_browser'] = array(
    'title' => t('Media browser'),
    'help' => t('Displays rows as an HTML list.'),
    'handler' => 'media_views_plugin_style_media_browser',
    'theme' => 'media_views_view_media_browser',
    'base' => $base,
    'uses row plugin' => FALSE,
    'uses row class' => FALSE,
    'uses options' => FALSE,
    'uses fields' => FALSE,
    'type' => 'normal',
    'help topic' => 'style-media-browser',
  );
  return $plugins;
}

/**
 * Display the view as a media browser.
 */
function template_preprocess_media_views_view_media_browser(&$vars) {
  module_load_include('inc', 'media', 'includes/media.browser');
  // Load file objects for each View result.
  $fids = array();
  foreach ($vars['rows'] as $index => $row) {
    // The Search API module returns the row in a slightly different format,
    // so convert it to the format that the normal file_managed table returns.
    if (!empty($row->entity->fid)) {
      $vars['rows'][$index]->fid = $row->entity->fid;
    }
    $fids[$index] = $row->fid;
  }
  $files = file_load_multiple($fids);

  // Render the preview for each file.
  $params = media_get_browser_params();
  $view_mode = isset($params['view_mode']) ? $params['view_mode'] : 'preview';

  foreach ($vars['rows'] as $index => $row) {

    // If the view result is cached, then the result may include fids that no
    // longer exist.
    if (!isset($files[$row->fid])) {
      unset($vars['rows'][$index]);
      continue;
    }

    $file = $files[$row->fid];
    // Add url/preview to the file object.
    media_browser_build_media_item($file, $view_mode);
    $vars['rows'][$index] = $file;
    $vars['rows'][$index]->preview = $file->preview;
  }

  // Add the files to JS so that they are accessible inside the browser.
  drupal_add_js(array('media' => array('files' => array_values($files))), 'setting');

  // Add the browser parameters to the settings and that this display exists.
  drupal_add_js(array(
    'media' => array(
      'browser' => array(
        'params' => media_get_browser_params(),
        'views' => array(
          $vars['view']->name => array(
            $vars['view']->current_display,
          ),
        ),
      ),
    ),
  ), 'setting');

  // Add classes and wrappers from the style plugin.
  $handler = $vars['view']->style_plugin;

  $class = explode(' ', $handler->options['class']);
  $class = array_map('drupal_clean_css_identifier', $class);

  $wrapper_class = explode(' ', $handler->options['wrapper_class']);
  $wrapper_class = array_map('drupal_clean_css_identifier', $wrapper_class);

  $vars['class'] = implode(' ', $class);
  $vars['wrapper_class'] = implode(' ', $wrapper_class);
  $vars['wrapper_prefix'] = '<div class="' . implode(' ', $wrapper_class) . '">';
  $vars['wrapper_suffix'] = '</div>';
  $vars['list_type_prefix'] = '<' . $handler->options['type'] . ' id="media-browser-library-list" class="' . implode(' ', $class) . '">';
  $vars['list_type_suffix'] = '</' . $handler->options['type'] . '>';

  // Run theming variables through a standard Views preprocess function.
  template_preprocess_views_view_unformatted($vars);

  // Add media browser JavaScript and CSS.
  drupal_add_js(drupal_get_path('module', 'media') . '/js/plugins/media.views.js');
}

/**
 * Implements hook_views_invalidate_cache().
 */
function media_views_invalidate_cache() {
  drupal_static_reset('media_get_browser_plugin_info');
}
