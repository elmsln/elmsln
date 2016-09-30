<?php

/**
 * Implements template_preprocess_page.
 */
function mooc_foundation_access_preprocess_page(&$variables) {
  // speedreader is enabled
  if (module_exists('speedreader')) {
    $variables['speedreader'] = TRUE;
  }
  // drop some tabs that don't seem to go away on their own
  if (isset($variables['tabs']['#primary']) && !empty($variables['tabs']['#primary'])) {
    foreach ($variables['tabs']['#primary'] as $key => $value) {
      if (in_array($value['#link']['path'], array('node/%/display', 'node/%/outline', 'node/%/log'))) {
        unset($variables['tabs']['#primary'][$key]);
      }
    }
    // fornow drop secondary entirely for nodes
    if (arg(0) == 'node' && isset($variables['tabs']['#secondary'])) {
      unset($variables['tabs']['#secondary']);
    }
  }
  // support for add child page shortcut
  $node = menu_get_object();
  if ($node && user_access('access printer-friendly version')) {
    $variables['tabs_extras'][200][] = '<div class="divider"></div>';
    $variables['tabs_extras'][200][] = l(t('Print'), 'book/export/html/' . arg(1));
  }
  $child_type = variable_get('book_child_type', 'book');
  if ($node && !empty($node->book) && (user_access('add content to books') || user_access('administer book outlines')) && node_access('create', $child_type) && $node->status == 1 && isset($node->book['depth']) && $node->book['depth'] < MENU_MAX_DEPTH) {
    $variables['tabs_extras'][200][] = '<div class="divider"></div>';
    $variables['tabs_extras'][200][] = '<span class="nolink cis-lmsless-text">' . t('Operations') . '</strong>';
    $variables['tabs_extras'][200][] = l(t('Add child page'), 'node/add/' . str_replace('_', '-', $child_type), array('query' => array('parent' => $node->book['mlid'])));
    $variables['tabs_extras'][200][] = l(t('Duplicate outline'), 'node/' . $node->nid . '/outline/copy', array('query' => array('destination' => 'node/' . $node->nid)));
    $variables['tabs_extras'][200][] = l(t('Edit child outline'), 'node/' . $node->book['nid'] . '/outline/children');
    $variables['tabs_extras'][200][] = l(t('Edit course outline'), 'admin/content/book/' . $node->book['bid']);

  }
  // support hiding the accessibility check UI which is poorly located
  if ($node && user_access('view accessibility tests')) {
    $variables['tabs_extras'][200][] = '<span class="cis_accessibility_check"></span>';
  }
  // remove the prefix that provides a link to the home page
  // as MOOC is the thing that currently provides support directly for this
  // and slightly overrides the behavior
  $keys = array_keys($variables['page']['header']);
  $keyname = array_shift($keys);
  unset($variables['page']['header'][$keyname]['#prefix']);
}

/**
 * Implements theme_breadrumb().
 */
function mooc_foundation_access_breadcrumb($variables) {
  // hide breadcrumbs
}

/**
 * Default theme function for video.
 */
function mooc_foundation_access_read_time($variables) {
  $defaults = read_time_defaults();
  $node = $variables['node'];
  // add in the children element to all totals if they exist
  if (isset($node->read_time['metadata']['children'])) {
    foreach ($node->read_time['metadata']['children'] as $key => $value) {
      if (!isset($node->read_time[$key])) {
        $node->read_time[$key] = 0;
      }
      $node->read_time[$key] += $value;
    }
  }
  // Get read time bundle settings.
  $format = variable_get('read_time_format_' . $node->type, $defaults['format']);
  $display = variable_get('read_time_display_' . $node->type, $defaults['display']);
  $wpm = variable_get('read_time_wpm_' . $node->type, $defaults['wpm']);

  // convert words into time
  $time = round(($node->read_time['words'] / $wpm), 3);
  // Format read time.
  if (in_array($format, array('hour_short', 'hour_long'))) {
    $hours = floor($time / 60);
    $minutes = ceil(fmod($time, 60));
  }
  else {
    $minutes = ceil($time);
  }
  if (in_array($format, array('hour_long', 'min_long'))) {
    $hour_suffix = 'hour';
    $min_suffix = 'minute';
  }
  else {
    $hour_suffix = 'hr';
    $min_suffix = 'min';
  }
  $minute_format = format_plural($minutes, '1 ' . $min_suffix, '@count ' . $min_suffix . 's');
  if (!empty($hours)) {
    $hour_format = format_plural($hours, '1 ' . $hour_suffix, '@count ' . $hour_suffix . 's');
    $read_time = format_string('@h, @m', array('@h' => $hour_format, '@m' => $minute_format));
  }
  else {
    $read_time = $minute_format;
  }
  $node->read_time['words'] = $read_time;
  // chip read time is different
  $output = '<div class="read-time-wrapper">';
  // pick out the chips
  foreach ($node->read_time as $key => $value) {
    if ($value != 0 && $key != 'metadata') {
      $label = '';
      switch ($key) {
        case 'words':
          $label = t('Reading');
          $icon = '<i class="tiny material-icons">library_books</i>';
        break;
        case 'audio':
          $label = t('Audio');
          $value .= ' ' . $label;
          // support for duration if we've got it assembled
          if (isset($node->read_time['metadata']['audio']['duration']) || isset($node->read_time['metadata']['children']['audio_duration'])) {
            $duration = 0;
            if (isset($node->read_time['metadata']['audio']['duration'])) {
              $duration += $node->read_time['metadata']['audio']['duration'];
            }
            if (isset($node->read_time['metadata']['children']['audio_duration'])) {
              $duration += $node->read_time['metadata']['children']['audio_duration'];
            }
            // account for possibility of not reading duration off media
            if ($duration == 0) {

            }
            elseif ($duration < 60) {
              $value .= ' ' . t('(@duration sec)', array('@duration' => $duration));
            }
            elseif ($duration < 3600) {
              $value .= ' ' . t('(@duration mins)', array('@duration' => round(($duration / 60), 1)));
            }
            else {
              $value .= ' ' . t('(@duration hours)', array('@duration' => round(($duration / 3600), 1)));
            }
          }
          $icon = '<i class="tiny material-icons">library_music</i>';
        break;
        case 'iframe':
          $icon = '<i class="tiny material-icons">launch</i>';
        break;
        case 'img':
          $label = t('Image');
          $value = format_plural($value, '1 ' . $label, '@count ' . $label . 's');
          $icon = '<i class="tiny material-icons">perm_media</i>';
        break;
        case 'svg':
          $label = t('Multimedia');
          $value = $value . ' ' . $label;
          $icon = '<i class="tiny material-icons">assessment</i>';
        break;
        case 'video':
          $label = t('Video');
          $value = format_plural($value, '1 ' . $label, '@count ' . $label . 's');
          // support for duration if we've got it assembled
          if (isset($node->read_time['metadata']['video']['duration']) || isset($node->read_time['metadata']['children']['video_duration'])) {
            $duration = 0;
            if (isset($node->read_time['metadata']['video']['duration'])) {
              $duration += $node->read_time['metadata']['video']['duration'];
            }
            if (isset($node->read_time['metadata']['children']['video_duration'])) {
              $duration += $node->read_time['metadata']['children']['video_duration'];
            }
            // account for possibility of not reading duration off media
            if ($duration == 0) {

            }
            elseif ($duration < 60) {
              $value .= ' ' . t('(@duration sec)', array('@duration' => $duration));
            }
            elseif ($duration < 3600) {
              $value .= ' ' . t('(@duration mins)', array('@duration' => round(($duration / 60), 1)));
            }
            else {
              $value .= ' ' . t('(@duration hours)', array('@duration' => round(($duration / 3600), 1)));
            }
          }
          $icon = '<i class="tiny material-icons">video_library</i>';
        break;
        default:
          $icon = '';
          $value = '';
        break;
      }
      // make sure there's something to render
      if (!empty($value)) {
        $output .= '<div class="chip">' . $icon . check_plain((empty($label) ? $value . ' ' . ucwords($key) : $value)) . '</div>';
      }
    }
  }
  $output .= '</div>';

  return '<span class="read-time">' . $output . '</span>';
}
