<?php

/**
 * @file
 * Definition of views_plugin_cache_none.
 */

/**
 * Caching plugin that provides no caching at all.
 *
 * @ingroup views_cache_plugins
 */
class views_plugin_cache_none extends views_plugin_cache {

  /**
   * {@inheritdoc}
   */
  public function cache_start() {
    // Do nothing.
  }

  /**
   * {@inheritdoc}
   */
  public function summary_title() {
    return t('None');
  }

  /**
   * {@inheritdoc}
   */
  public function cache_get($type) {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function cache_set($type) {
  }

}
