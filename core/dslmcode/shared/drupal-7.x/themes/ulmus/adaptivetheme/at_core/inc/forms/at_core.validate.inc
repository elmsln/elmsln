<?php

/**
 * @file
 * Validatation for theme settings.
 *
 * @param $form
 * @param $form_state
 */
function at_core_settings_validate($form, &$form_state) {
  $values = $form_state['values'];
  $theme_name = $form_state['build_info']['args'][0];

  // "Design approach" uses radios, if this becomes unset for some reason bad
  // things can happen.
  if (empty($values['global_default_layout'])) {
    form_set_error('global_default_layout', t('No setting detected for <b>Mobile first or Desktop first</b>. Please review "Settings > Mobile first or Desktop first" and select an option.'));
  }

  // For each breakpoint we need to have a layout selected
  if (empty($values['bigscreen_layout'])) {
    form_set_error('bigscreen_layout', t('No layout selection detected for the <b>Standard Layout</b>. Please review "Standard Layout > Choose sidebar positions" and select an option.'));
  }
  if (empty($values['tablet_landscape_layout'])) {
    form_set_error('tablet_landscape_layout', t('No layout selection detected for the <b>Tablet Landscape Layout</b>. Please review "Tablet Layout > Landscape > Choose sidebar positions" and select an option.'));
  }
  if (empty($values['tablet_portrait_layout'])) {
    form_set_error('tablet_portrait_layout', t('No layout selection detected for the <b>Tablet Portrait Layout</b>. Please review "Tablet Layout > Portrait > Choose sidebar positions" and select an option.'));
  }
  if (empty($values['smalltouch_landscape_layout'])) {
    form_set_error('smalltouch_landscape_layout', t('No layout selection detected for the <b>Smalltouch Landscape Layout</b>. Please review "Smalltouch Layout > Landscape > Choose sidebar positions" and select an option.'));
  }

  // Validate our form #state required fields, #states are UI only.

  // Bigscreen
  if (empty($values['bigscreen_sidebar_first'])) {
    form_set_error('bigscreen_sidebar_first', t('Standard Layout <em>First sidebar</em> width is empty - you must enter a value.'));
  }
  if (empty($values['bigscreen_sidebar_second'])) {
    form_set_error('bigscreen_sidebar_second', t('Standard Layout <em>Second sidebar</em> width is empty - you must enter a value.'));
  }
  if ($values['bigscreen_set_max_width'] === 1) {
    if (empty($values['bigscreen_max_width'])) {
      form_set_error('bigscreen_max_width', t('Standard layout max-width is empty - enter a value or deselect "Set a max width".'));
    }
  }

  // Tablet
  if (empty($values['tablet_landscape_sidebar_first'])) {
    form_set_error('tablet_landscape_sidebar_first', t('Tablet Landscape <em>First sidebar</em> width is empty - you must enter a value.'));
  }
  if ($values['tablet_landscape_layout'] === 'three_col_grail' || $values['tablet_landscape_layout'] === 'two_sidebars_left' || $values['tablet_landscape_layout'] === 'two_sidebars_right') {
    if (empty($values['tablet_landscape_sidebar_second'])) {
      form_set_error('tablet_landscape_sidebar_second', t('Tablet Landscape <em>First sidebar</em> width is empty - you must enter a value. The layout you selected requires values for both sidebars.'));
    }
  }

  // Smalltouch
  if ($values['smalltouch_landscape_layout'] === 'one_col_vert') {
    if (empty($values['smalltouch_landscape_sidebar_first'])) {
      form_set_error('smalltouch_landscape_sidebar_first', t('Smalltouch First Sidebar width is empty - enter a value or choose another layout.'));
    }
    if (empty($values['smalltouch_landscape_sidebar_second'])) {
      form_set_error('smalltouch_landscape_sidebar_second', t('Smalltouch Second Sidebar width is empty - enter a value or choose another layout.'));
    }
  }

  // Validate extensions
  if (isset($values['enable_extensions']) && $values['enable_extensions'] === 1) {
    // Apple touch icon paths
    if (isset($values['enable_apple_touch_icons']) && $values['enable_apple_touch_icons'] === 1) {
      if (!empty($values['apple_touch_icon_path_l'])) {
        $l = drupal_get_path('theme', $theme_name) . '/' . $values['apple_touch_icon_path_l'];
        if (!file_exists($l)) {
          form_set_error('apple_touch_icon_path_l', t('Ops! The Apple touch 57x57 icon path is not right, check the file exists or the path to the file is correct.'));
        }
      }
      if (!empty($values['apple_touch_icon_path_m'])) {
        $m = drupal_get_path('theme', $theme_name) . '/' . $values['apple_touch_icon_path_m'];
        if (!file_exists($m)) {
          form_set_error('apple_touch_icon_path_m', t('Ops! The Apple touch 72x72 icon path is not right, check the file exists or the path to the file is correct.'));
        }
      }
      if (!empty($values['apple_touch_icon_path_h'])) {
        $h = drupal_get_path('theme', $theme_name) . '/' . $values['apple_touch_icon_path_h'];
        if (!file_exists($h)) {
          form_set_error('apple_touch_icon_path_h', t('Ops! The Apple touch 114x114 icon path is not right, check the file exists or the path to the file is correct.'));
        }
      }
    }
    // Gutter value
    if (isset($values['enable_markup_overides']) && $values['enable_markup_overides'] === 1) {
      if (!empty($values['global_gutter_width']) && !is_numeric($values['global_gutter_width'])) {
        $invalid_gutter_value = check_plain($values['global_gutter_width']);
        form_set_error('global_gutter_width', t('The gutter width is not valid: <b>!invalid_gutter_value</b> is not a usable value', array('!invalid_gutter_value' => $invalid_gutter_value)));
      }
    }
  }

  // Check if the custom files directory exists
  if ($values['global_files_path'] == 'custom_path') {
    $directory = $values['custom_files_path'];
    if (!is_dir($directory) && !drupal_mkdir($directory, NULL, TRUE)) {
      // If the directory does not exists and cannot be created.
      form_set_error('custom_files_path', t('The directory %directory does not exist and could not be created.', array('%directory' => $directory)));
      watchdog('file system', 'The directory %directory does not exist and could not be created.', array('%directory' => $directory), WATCHDOG_ERROR);
    }
  }
}
