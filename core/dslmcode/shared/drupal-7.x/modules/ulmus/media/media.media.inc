<?php

/**
 * @file
 * Media module integration for the Media module.
 */

/**
 * Implements hook_media_browser_plugin_info().
 */
function media_media_browser_plugin_info() {
  $info['upload'] = array(
    'title' => t('Upload'),
    'weight' => -10,
    'class' => 'MediaBrowserUpload',
  );

  // Add a plugin for each View display using the 'media_browser' display type.
  $view_weight = 10;
  foreach (views_get_enabled_views() as $view) {
    foreach ($view->display as $display) {
      if ($display->display_plugin == 'media_browser') {
        $title = $display->display_title;
        if (!empty($display->display_options['title'])) {
          $title = $display->display_options['title'];
        }
        $info["{$view->name}--{$display->id}"] = array(
          'title' => $title,
          // @TODO make this configurable.
          'weight' => $view_weight++,
          'class' => 'MediaBrowserView',
          'view_name' => $view->name,
          'view_display_id' => $display->id,
        );
      }
    }
  }

  return $info;
}

/**
 * Implements hook_query_media_browser_alter().
 */
function media_query_media_browser_alter($query) {
  // Ensure that the query is against the file_managed table.
  $tables = $query->getTables();
  if (empty($tables['file_managed'])) {
    throw new Exception(t('Media browser being queried without the file_managed table.'));
  }
  $alias = $tables['file_managed']['alias'];

  $params = drupal_get_query_parameters();
  // How do we validate these?  I don't know.
  // I think PDO should protect them, but I'm not 100% certain.
  array_walk_recursive($params, 'media_recursive_check_plain');

  $types = !empty($params['types']) ? $params['types'] : NULL;
  $url_include_patterns = !empty($params['url_include_patterns']) ? $params['url_include_patterns'] : NULL;
  $url_exclude_patterns = !empty($params['url_exclude_patterns']) ? $params['url_exclude_patterns'] : NULL;
  $allowed_schemes = !empty($params['schemes']) ? array_filter($params['schemes']) : array();
  $extensions = !empty($params['file_extensions']) ? array_filter(explode(' ', $params['file_extensions'])) : array();

  $or_condition = db_or();

  if (!empty($allowed_schemes)) {
    // Include local files with the allowed extensions and types.
    $local_wrappers = array_intersect_key(media_get_local_stream_wrappers(), $allowed_schemes);
    if (!empty($extensions) && !empty($local_wrappers)) {
      // Extension filtering.
      $local_condition = db_or();
      foreach (array_keys($local_wrappers) as $scheme) {
        foreach ($extensions as $extension) {
          $local_condition->condition($alias . '.uri', db_like($scheme . '://') . '%' . db_like('.' . $extension), 'LIKE');
        }
      }
      $or_condition->condition($local_condition);
    }
    if (!empty($types) && !empty($local_wrappers)) {
      // Type filtering.
      $local_condition = db_or();
      foreach (array_keys($local_wrappers) as $scheme) {
        $local_condition->condition($alias . '.type', $types, 'IN');
      }
      $or_condition->condition($local_condition);
    }

    // Include remote files with the allowed file types.
    // We cant filter extensions here, because remote file filenames usually
    // are a url or a parameter of a query.
    $remote_wrappers = array_intersect_key(media_get_remote_stream_wrappers(), $allowed_schemes);
    if (!empty($types) && !empty($remote_wrappers)) {
      $remote_condition = db_and();
      $wrapper_condition = db_or();
      foreach (array_keys($remote_wrappers) as $scheme) {
        $wrapper_condition->condition($alias . '.uri', db_like($scheme . '://') . '%', 'LIKE');
      }
      $remote_condition->condition($wrapper_condition);
      $remote_condition->condition($alias . '.type', $types, 'IN');
      $or_condition->condition($remote_condition);
    }
  }
  else {
    if (!empty($types)) {
      $query->condition($alias . '.type', $types, 'IN');
    }
    if (!empty($extensions)) {
      foreach ($extensions as $extension) {
        $or_condition->condition($alias . '.uri', db_like('.' . $extension), 'LIKE');
      }
    }
  }

  if ($or_condition->count()) {
    $query->condition($or_condition);
  }

  if ($url_include_patterns) {
    $query->condition($alias . '.uri', '%' . db_like($url_include_patterns) . '%', 'LIKE');
    // Insert stream related restrictions here.
  }
  if ($url_exclude_patterns) {
    $query->condition($alias . '.uri', '%' . db_like($url_exclude_patterns) . '%', 'NOT LIKE');
  }

  if (!user_access('administer files')) {
    $query->condition($alias . '.uri', db_like('private://') . '%', 'NOT LIKE');
  }

  // @todo This is possibly redundant since it's already filtered in the view.
  $query->condition($alias . '.status', FILE_STATUS_PERMANENT);

  foreach (array_keys(file_entity_get_hidden_stream_wrappers()) as $name) {
    $query->condition($alias . '.uri', db_like($name . '://') . '%', 'NOT LIKE');
  }
}
