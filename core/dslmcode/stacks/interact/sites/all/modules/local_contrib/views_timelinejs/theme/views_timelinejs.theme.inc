<?php
/**
 * @file
 * Theme preprocessors.
 */

/**
 * Preprocessor for views template.
 */
function template_preprocess_views_timelinejs(&$vars) {
  global $language;

  // Load required libraries and styles.
  if (($library = libraries_load('timeline')) && !empty($library['loaded'])) {
    $view = $vars['view'];
    $vars['timelinejs_id'] = 'timelinejs_' . $view->name . '_' . $view->current_display;

    $width_unit = $vars['options']['timeline_theme']['width_unit'] ? '%' : '';
    $height_unit = $vars['options']['timeline_theme']['height_unit'] ? '%' : '';

    $width = check_plain($vars['options']['timeline_theme']['width']) . $width_unit;
    $height = check_plain($vars['options']['timeline_theme']['height']) . $height_unit;

    $settings = array(
      'width' => $width,
      'height' => $height,
      'source' => $vars['rows'],
      'embed_id' => $vars['timelinejs_id'],
      'embed_path' => base_path() . libraries_get_path('timeline') . '/compiled/',
      'lang' => $language->language,
      'processed' => FALSE,
    );

    if ($vars['options']['timeline_config']['hash_bookmark']) {
      $settings['hash_bookmark'] = TRUE;
    }

    if ($vars['options']['timeline_config']['start_at_end']) {
      $settings['start_at_end'] = TRUE;
    }

    if (isset($vars['options']['timeline_config']['start_zoom_adjust'])) {
      $settings['start_zoom_adjust'] = check_plain($vars['options']['timeline_config']['start_zoom_adjust']);
    }

    // Add inline JavaScript.
    drupal_add_js(array('timelineJS' => array($settings)), 'setting');
    drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');
  } else {
    drupal_set_message(t('TimelineJS libraries not found in libraries/timeline directory. Timeline will not work.'), 'error', FALSE);
  }
}

/**
 * Add "read more" link after event body text.
 */
function theme_views_timelinejs_link_to_entity($vars) {
  return '<p class="read-more">' . l($vars['link_text'], $vars['uri']) . '</p>';
}
