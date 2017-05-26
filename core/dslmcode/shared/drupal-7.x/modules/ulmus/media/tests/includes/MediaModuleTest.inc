<?php

/**
 * @file
 * Definition of MediaModuleTest.
 */

/**
 * Test browser plugin.
 */
class MediaModuleTest extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return TRUE;
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    $build = array();
    $build['test'] = array(
      '#markup' => '<p>' . t('Test browser plugin output.') . '</p>',
    );

    return $build;
  }
}
