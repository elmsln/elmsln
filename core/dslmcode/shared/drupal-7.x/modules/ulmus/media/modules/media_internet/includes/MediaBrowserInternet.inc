<?php

/**
 * @file
 * Definition of MediaBrowserInternet.
 */

/**
 * Media browser plugin for Media Internet sources.
 */
class MediaBrowserInternet extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return media_internet_access($account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    module_load_include('inc', 'file_entity', 'file_entity.pages');

    $build = array();
    $params = $this->params;
    $params['internet_media'] = TRUE;
    $build['form'] = drupal_get_form('media_internet_add_upload', $params);

    return $build;
  }
}
