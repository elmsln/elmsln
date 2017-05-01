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
 * Implements hook_query_TAG_alter().
 *
 * @todo: Potentially move this into media.module in a future version of Media.
 */
function media_query_media_browser_alter($query) {
  // Ensure that the query is against the file_managed table.
  $tables = $query->getTables();

  if (empty($tables['file_managed'])) {
    throw new Exception(t('Media browser being queried without the file_managed table.'));
  }

  $alias = $tables['file_managed']['alias'];

  // How do we validate these?  I don't know.
  // I think PDO should protect them, but I'm not 100% certain.
  $params = media_get_browser_params();

  // Gather any file restrictions.
  $types = !empty($params['types']) ? $params['types'] : array();
  $schemes = !empty($params['schemes']) ? $params['schemes'] : array();
  $extensions = !empty($params['file_extensions']) ? explode(' ', $params['file_extensions']) : array();

  $or = db_or();

  // Filter out files with restricted types.
  if (!empty($types)) {
    $query->condition($alias . '.type', $types, 'IN');
  }

  // Filter out files with restricted schemes.
  if (!empty($schemes)) {
    $local_or = db_or();
    $local_and = db_and();

    // Gather all of the local stream wrappers.
    $local_stream_wrappers = media_get_local_stream_wrappers();

    foreach ($schemes as $scheme) {
      // Only local files have extensions.
      // Filter out files with restricted extensions.
      if (!empty($extensions) && isset($local_stream_wrappers[$scheme])) {
        $mimetypes = array();
        foreach ($extensions as $extension) {
          $mimetype = media_get_extension_mimetype($extension);
          if ($mimetype) {
            $mimetypes[] = $mimetype;
          }
        }
        $local_and->condition($alias . '.uri', db_like($scheme . '://') . '%', 'LIKE');
        if (count($mimetypes)) {
          $local_and->condition($alias . '.filemime', $mimetypes, 'IN');
        }
        $local_or->condition($local_and);
        $local_and = db_and();
      }
      else {
        $local_or->condition($alias . '.uri', db_like($scheme . '://') . '%', 'LIKE');
      }
    }

    $or->condition($local_or);
  }

  if ($or->count()) {
    $query->condition($or);
  }
}
