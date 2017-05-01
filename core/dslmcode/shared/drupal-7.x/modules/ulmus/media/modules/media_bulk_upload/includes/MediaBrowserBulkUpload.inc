<?php

/**
 * @file
 * Definition of MediaBrowserBulkUpload.
 */

/**
 * Media browser plugin for showing the bulk upload form.
 *
 * @deprecated
 */
class MediaBrowserBulkUpload extends MediaBrowserUpload {
  /**
   * Overrides MediaBrowserPlugin::view().
   */
  public function view() {
    module_load_include('inc', 'file_entity', 'file_entity.pages');

    $build = array();
    if ($this->params['multiselect']) {
      $build['form'] = drupal_get_form('file_entity_add_upload_multiple', $this->params);
    }
    else {
      $build['form'] = drupal_get_form('file_entity_add_upload', $this->params);
    }

    return $build;
  }
}
