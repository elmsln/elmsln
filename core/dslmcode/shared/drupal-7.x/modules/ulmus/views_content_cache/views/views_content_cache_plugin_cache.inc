<?php
/**
 * @file
 * Provides the Views content cache, views cache plugin.
 */

/**
 * Simple caching of query results for Views displays.
 * Includes listening for changes/posts/deletions of
 * certain node types.
 */
class views_content_cache_plugin_cache extends views_plugin_cache {
  function option_definition() {
    $options = parent::option_definition();

    $options['results_min_lifespan'] = array('default' => 0);
    $options['results_max_lifespan'] = array('default' => 21600);
    $options['output_min_lifespan'] = array('default' => 0);
    $options['output_max_lifespan'] = array('default' => 21600);
    $options['keys'] = array('default' => array());

    return $options;
  }

  function option_defaults(&$options) {
    $options['results_max_lifespan'] = 21600;
    $options['output_max_lifespan'] = 21600;
  }


  function options_form(&$form, &$form_state) {
    $form['keys'] = array(
      '#title' => t('Cache segments'),
      '#type' => 'fieldset',
      '#description' => t("Choose which events will update this View's cache."),
    );
    foreach (views_content_cache_get_plugin() as $key_id => $plugin) {
      $option_value = isset($this->options['keys'][$key_id]) ? $this->options['keys'][$key_id] : array();
      $form['keys'][$key_id] = $plugin->options_form($option_value, $this);
    }

    $options = array(60, 300, 1800, 3600, 21600, 518400);
    $options = drupal_map_assoc($options, 'format_interval');
    $options = array(-1 => t('None')) + $options;

    $form['results_min_lifespan'] = array(
      '#type' => 'select',
      '#title' => t('Query results - Minimum lifetime'),
      '#description' => t('Query results will be cached for <strong>at least</strong> this amount of time, even if a selected event has occured more recently.'),
      '#options' => $options,
      '#default_value' => $this->options['results_min_lifespan'],
    );
    $form['results_max_lifespan'] = array(
      '#type' => 'select',
      '#title' => t('Query results - Maximum lifetime'),
      '#description' => t('Query results will be cached for <strong>at most</strong> this amount of time.'),
      '#options' => $options,
      '#default_value' => $this->options['results_max_lifespan'],
    );

    $form['output_min_lifespan'] = array(
      '#type' => 'select',
      '#title' => t('Rendered output - Minimum lifetime'),
      '#description' => t('Rendered HTML output will be cached for <strong>at least</strong> this amount of time, even if a selected event has occured more recently.'),
      '#options' => $options,
      '#default_value' => $this->options['output_min_lifespan'],
    );
    $form['output_max_lifespan'] = array(
      '#type' => 'select',
      '#title' => t('Rendered output - Maximum lifetime'),
      '#description' => t('Rendered HTML output will be cached for <strong>at most</strong> this amount of time.'),
      '#options' => $options,
      '#default_value' => $this->options['output_max_lifespan'],
    );
  }

  function summary_title() {
    return t('Content cache');
  }

  /**
   * Return the expiry time for this cache plugin.
   *
   * This should be the last time that the content has changed, altered to allow
   * for the the min/max lifetimes.
   */
  function cache_expire($type) {
    $cutoff = 0;

    // Retrieve the latest update time matching the settings on this View.
    $cid = array();
    if (!empty($this->options['keys'])) {
      foreach ($this->options['keys'] as $key_id => $key_values) {
        if ($plugin = views_content_cache_get_plugin($key_id)) {
          $cid[$key_id] = $plugin->view_key($key_values, $this);
        }
      }
    }
    if (!empty($cid) && $timestamp = views_content_cache_update_get($cid)) {
      $cutoff = $timestamp;
    }

    // If there's a minimum lifetime, enforce it:
    if ($min_lifespan = $this->options[$type . '_min_lifespan']) {
      $min_lifespan = REQUEST_TIME - $min_lifespan;
      $cutoff = min($min_lifespan, $cutoff);
    }

    // Only enforce a maximum lifetime if it's been specifically selected:
    if ($max_lifespan = $this->options[$type . '_max_lifespan']) {
      if ($max_lifespan != -1) {
        $max_lifespan = REQUEST_TIME - $max_lifespan;
        $cutoff = max($max_lifespan, $cutoff);
      }
    }
    return $cutoff;
  }

  /**
   * Determine expiration time in the cache table of the cache type
   * or CACHE_PERMANENT if item shouldn't be removed automatically from cache.
   *
   * @param $type
   *   The cache type, either 'query', 'result' or 'output'.
   * @return int
   *   The timestamp of the expiration time.
   */
  function cache_set_expire($type) {
    $expiration_time = CACHE_PERMANENT;

    // Only enforce a maximum lifetime if it's been specifically selected:
    if ($max_lifespan = $this->options[$type . '_max_lifespan']) {
      if ($max_lifespan != -1) {
        $max_lifespan = REQUEST_TIME + $max_lifespan;
        $expiration_time = max($max_lifespan, $expiration_time);
      }
    }
    return $expiration_time;
  }
}
