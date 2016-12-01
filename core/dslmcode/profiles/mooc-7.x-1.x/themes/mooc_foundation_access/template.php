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
  $child_type = variable_get('book_child_type', 'book');
  $node = menu_get_object();
  if ($node && !empty($node->book) && (user_access('add content to books') || user_access('administer book outlines')) && node_access('create', $child_type) && $node->status == 1 && isset($node->book['depth']) && $node->book['depth'] < MENU_MAX_DEPTH) {
    $variables['tabs_extras'][200][] = '<div class="divider"></div>';
    $variables['tabs_extras'][200][] = '<span class="nolink cis-lmsless-text">' . t('Operations') . '</span>';
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

  // Remove title from a page when a gitbook markdown filter is present.
  if(isset($variables['page']['content']['system_main']['nodes'])) {
    foreach($variables['page']['content']['system_main']['nodes'] as $node) {
      if(isset($node['body']['#object'])) {
        if($node['body']['#object']->body['und'][0]['format'] == "git_book_markdown") {
          $variables['title'] = "";
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_node.
 */
function mooc_foundation_access_preprocess_node(&$variables) {
  // Remove title from a page when a gitbook markdown filter is present.
  if(isset($variables['body'][0]['format'])) {
    if($variables['body'][0]['format'] == "git_book_markdown") {
      $variables['title'] = "";
    }
  }
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
  $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
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
  if (isset($node->read_time['words'])) {
    $time = round(($node->read_time['words'] / $wpm), 3);
  }
  else {
    $time = 0;
  }
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
      $class_key = '';
      switch ($key) {
        case 'words':
          $label = t('Reading');
          $icon = '<i class="tiny material-icons ' . $lmsless_classes['text'] . '">library_books</i>';
          $class_key = 'read-time-words';
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
              $value .= ', ' . t('@duration sec', array('@duration' => $duration));
            }
            elseif ($duration < 3600) {
              $value .= ', ' . t('@duration mins', array('@duration' => round(($duration / 60), 1)));
            }
            else {
              $value .= ', ' . t('@duration hours', array('@duration' => round(($duration / 3600), 1)));
            }
          }
          $icon = '<i class="tiny material-icons ' . $lmsless_classes['text'] . '">library_music</i>';
          $class_key = 'read-time-audio';
        break;
        case 'iframe':
          $icon = '<i class="tiny material-icons ' . $lmsless_classes['text'] . '">launch</i>';
          $class_key = 'read-time-iframe';
        break;
        case 'img':
          $label = t('Image');
          $value = format_plural($value, '1 ' . $label, '@count ' . $label . 's');
          $icon = '<i class="tiny material-icons ' . $lmsless_classes['text'] . '">perm_media</i>';
          $class_key = 'read-time-image';
        break;
        case 'svg':
          $label = t('Multimedia');
          $value = $value . ' ' . $label;
          $icon = '<i class="tiny material-icons ' . $lmsless_classes['text'] . '">assessment</i>';
          $class_key = 'read-time-svg';
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
              $value .= ', ' . t('@duration sec', array('@duration' => $duration));
            }
            elseif ($duration < 3600) {
              $value .= ', ' . t('@duration mins', array('@duration' => round(($duration / 60), 1)));
            }
            else {
              $value .= ', ' . t('@duration hours', array('@duration' => round(($duration / 3600), 1)));
            }
          }
          $icon = '<i class="tiny material-icons ' . $lmsless_classes['text'] . '">video_library</i>';
          $class_key = 'read-time-video';
        break;
        default:
          $icon = '';
          $value = '';
        break;
      }
      // make sure there's something to render
      if (!empty($value)) {
        $output .= '<div class="chip ' . $lmsless_classes['color'] . ' ' . $lmsless_classes['light'] . ' ' . $class_key . '">' . $icon . check_plain((empty($label) ? $value . ' ' . ucwords($key) : $value)) . '</div>';
      }
    }
  }
  $output .= '</div>';

  return '<div class="read-time">' . $output . '</div>';
}
