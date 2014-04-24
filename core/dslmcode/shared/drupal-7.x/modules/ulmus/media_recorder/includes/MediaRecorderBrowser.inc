<?php

/**
 * @file
 * Definition of MediaRecorderBrowser.
 */

/**
 * Media browser plugin for Media Recorder.
 */
class MediaRecorderBrowser extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return file_entity_access('create');
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    $build['form'] = drupal_get_form('media_recorder_add', $this->params['types'], $this->params['multiselect']);
    return $build;
  }
}
