<?php

/**
 * @file
 * Generate form elments for the Panel and Gpanel Reponsive Layout settings.
 */
function at_core_responsive_panels_form(&$form, $theme_name, $info_array) {
  // Supported devices
  $devices = array(
    'bigscreen',
    'tablet_landscape',
    'tablet_portrait',
    'smalltouch_landscape',
  );

  // Get the configuration array for panel layouts
  $rpl = responsive_panels_data_structure();

  // Check if panels exists
  $panels = module_exists('panels') ? TRUE : FALSE;

  // Set variables here for active Gpanels, we need to test on this later
  $active_gpanels = array();
  $active_gpanels_arrays = array();

  // Build a keyed array of the regions, we need to reset the keys for
  // array_intersect() to figure out which Gpanels are being used
  foreach ($info_array['regions'] as $key => $value) {
    $theme_regions[] = $key;
  }

  // Get the standard Gpanel regions list
  $gpanel_regions = gpanel_regions();

  // Figure out which gpanels are actually being used in the theme
  $active_gpanels = array();
  foreach ($gpanel_regions as $gpanel => $gpanel_array) {
    if (array_intersect($theme_regions, $gpanel_array['regions'])) {
      $active_gpanels[] = $gpanel;
      $active_gpanels_arrays[] = $gpanel_array;
    }
  }

  // Make certain we only list each Gpanel once
  array_unique($active_gpanels);

  // Make a list of all active Gpanel titles, if any
  $used_gpanels = '';
  if (!empty($active_gpanels)) {
    foreach ($active_gpanels_arrays as $active_gpanel) {
      $gpanels_titles[] = $active_gpanel['title'];
    }
    $used_gpanels = t('<p>Your theme currently uses these Gpanels:</p>!used_gpanels', array('!used_gpanels' => theme('item_list', array('items' => $gpanels_titles))));
  }

  // Get all standard Plugin layout names
  foreach ($rpl as $rpl_key => $values) {
    foreach ($values as $value) {
      foreach ($value as $k => $v) {
        $active_rpl[] = $v['theme'];
        $active_types[] = $v['type'];
      }
    }
  }

  // This is will not be sustaintable, what I need is a function that sorts the
  // layouts properly, alphabetical is no good, it needs to be in a very precise
  // order to make sense in the UI.
  if (isset($rpl['one'])) {
    unset($rpl['one']);
  }
  if (isset($rpl['six'])) {
    $six = $rpl['six']; unset($rpl['six']); $rpl['six'] = $six;
  }
  if (isset($rpl['inset'])) {
    $inset = $rpl['inset']; unset($rpl['inset']); $rpl['inset'] = $inset;
  }

  // Get the admin css files for each plugin
  $panels_admin_css_files = responsive_plugins_admin_css($theme_name, $plugin_type = 'panels');
  foreach ($panels_admin_css_files as $filepath) {
    if (file_exists($filepath)) {
      $panels_css_files['css'][] = array('type' => 'file', 'data' => $filepath, 'weight' => 100);
    }
  }

  // Set title and message
  $panels_title = t('Panels &amp; Gpanels');
  $panels_message = t('<h3>!panels_title</h3><p>Adaptivetheme supports responsive Panels and Gpanel layouts. To use this capability you can use the <a href="!panels_link" target="_blank">Panels module</a>, <a href="!ds_link" target="_blank">Display Suite</a> (with Panels) or Adaptivethemes native <a href="!gpanels_link" target="_blank">Gpanels</a> layouts. To views all layouts on one page and test your settings you can enable the panels test, see the Debuggers tab.</p><p><b>Usage:</b> select options for each device range and layout type.</p>!gpanels_message', array('!panels_title' => $panels_title, '!panels_link' => 'http://drupal.org/project/panels', '!gpanels_link' => 'http://adaptivethemes.com/documentation/using-gpanels', '!ds_link' => 'http://drupal.org/project/ds', '!gpanels_message' => $used_gpanels));

  // Gpanels and Panels top level wrapper
  $form['at-settings']['panels'] = array(
    '#type' => 'fieldset',
    '#title' => $panels_title,
    '#description' => $panels_message,
    '#attached' => $panels_css_files,
  );

  // Disabled message
  $panels_disable_message = t('<p>The responsive layout is disabled, only the default layout for each Gpanel and Panel layout will be used.</p><p>To re-enable uncheck the "Disable responsive layout and styles" checkbox under the "Global Settings" tab.</p>');

  if(at_get_setting('disable_responsive_styles') === 1) {
    $form['at-settings']['panels']['disabled'] = array(
      '#markup' => '<div class="messages warning">' . $panels_disable_message . '</div>',
    );
  }

  $form['at-settings']['panels']['panels-wrapper'] = array(
    '#type' => 'fieldset',
    '#attributes' => array('class' => array('panel-option-lists')),
    '#states' => array(
      'disabled' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  foreach ($devices as $device) {
    $title = str_replace('_', ' ', drupal_ucfirst($device));
    if ($device == 'bigscreen') {
      $title = 'Standard layout';
    }
    $form['at-settings']['panels']['panels-wrapper'][$device] = array(
      '#type' => 'fieldset',
      '#title' => t($title),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('Select the layouts you want to use when the site is being viewed in !device.', array('!device' => strtolower($title))),
    );
    if (isset($rpl)) {
      foreach ($rpl as $group => $layouts) {
        if (!empty($layouts)) {
          $form['at-settings']['panels']['panels-wrapper'][$device][$group] = array(
            '#type' => 'fieldset',
            '#title' => t($group),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
          );
          foreach ($layouts as $layout) {
            foreach ($layout as $key => $value) {
              if (isset($value['theme'])) {
                $default_value = at_get_setting($device . '_' . $value['theme']);
                // Add a check for backwards compatibility with pre 7.x-3.2 themes
                if ($device == 'smalltouch_landscape') {
                  $default_value = at_get_setting('smalltouch_landscape_' . $value['theme']) ? at_get_setting('smalltouch_landscape_' . $value['theme']) : at_get_setting('smartphone_landscape_' . $value['theme']);
                }
                $form['at-settings']['panels']['panels-wrapper'][$device][$group][$device . '_' . $value['theme']] = array(
                  '#type' => 'radios',
                  '#title' => t($value['title']),
                  '#default_value' => $default_value,
                  '#options' => $value['options'],
                );
              }
            }
          }
        }
      }
    }
  }
}
