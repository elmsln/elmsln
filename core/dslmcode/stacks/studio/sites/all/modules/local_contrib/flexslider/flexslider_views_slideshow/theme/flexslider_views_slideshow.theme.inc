<?php

/**
 * @file
 * Theme and preprocess functions for Flexslider Views
 *
 * @author Mathew Winstone (minorOffense) <mwinstone@coldfrontlabs.ca>
 */

/**
 * FlexSlider Views theme for the main wrapper element
 *
 * @ingroup themeable
 */
function _flexslider_views_slideshow_preprocess_flexslider_views_slideshow_main_frame(&$vars) {
  // Load the settings, row information, view data and views slideshow ID into
  // more conveniently named variables.
  $settings = $vars['settings'];
  $rows = $vars['rows'];
  $view = $vars['view'];
  $vss_id = $vars['vss_id'];

  // Load the option set data
  $optionset = $settings['optionset'];
  $settings = flexslider_optionset_load($settings['optionset']);
  $settings = $settings->options;

  
  // Cast the strings into int or bool as necessary
  $new_settings = array();
  foreach ($settings as $key => $value) {
    if (is_string($value)) {

      $value = str_ireplace("\n", ' ', $value);
      $value = trim($value);
      
      // Check for numbers and/or boolean values
      if (is_numeric($value)) {
        $value = (int)$value;
      }
      elseif (strtolower($value) == 'true') {
        $value = TRUE;
      }
      elseif (strtolower($value) == 'false') {
        $value = FALSE;
      }
    }
    
    $new_settings[$key] = $value;
  }

  // Merge the existing settings with the generated ones
  $settings = array_merge(
    array(
      'num_divs' => sizeof($rows),
      'id_prefix' => '#flexslider_views_slideshow_main_',
      //'div_prefix' => '#'
      // @todo figure out what the div prefix is used for
      'vss_id' => $vss_id,
    ),
    $new_settings
  );
  
  // We need to go through the current js setting values to make sure the one we
  // want to add is not already there. If it is already there then append -[num]
  // to the id to make it unique.
  $slideshow_count = 1;
  $current_settings = drupal_add_js();
  foreach ($current_settings['settings']['data'] AS $current_setting) {
    if (isset($current_setting['flexslider_views_slideshow'])) {
      $current_keys = array_keys($current_setting['flexslider_views_slideshow']);
      if (stristr($current_keys[0], '#flexslider_views_slideshow_main_' . $vss_id)) {
        $slideshow_count++;
      }
    }
  }
  
  // Append the new unique IDs if required
  if ($slideshow_count > 1) {
    $vss_id .= '-' . $slideshow_count;
    $settings['vss_id'] = $vss_id;
  }
  
  // Load the FlexSlider library for use
  flexslider_add();

  // Create the settings container
  // Due to a limitation inside of views_slideshow, the ID for the settings container
  // must end with _main
  //
  // @see lines 162 through 169 in views_slideshow.theme.inc
  drupal_add_js(array('flexslider_views_slideshow' => array('#flexslider_views_slideshow_main_' . $vss_id => $settings)), 'setting');

  // Load the initilization javascript
  drupal_add_js(drupal_get_path('module', 'flexslider_views_slideshow') . '/js/flexslider_views_slideshow.js');

  // Required container class for FlexSlider
  $vars['classes_array'][] = 'slides';

  // Render the rows
  $rendered_rows = '';
  $slideshow_count = 0;
  foreach($rows as $count => $row) {
    $items[] = $row;
    // @todo see if we can group multiple items per slide
    $rendered_rows .= theme('flexslider_views_slideshow_main_frame_row', array('vss_id' => $vss_id, 'items' => $items, 'count' => $count, 'view' => $view));

    // Clear the items array
    $items = array();
    // Count the number of slides created
    $slideshow_count++;
  }

  // Save the rendered rows
  $vars['rendered_rows'] = $rendered_rows;
}

/**
 * FlexSlider Views theme for the row element
 *
 * @ingroup themeable
 */
function _flexslider_views_slideshow_preprocess_flexslider_views_slideshow_main_frame_row(&$vars) {
  $current = $vars['count'] + 1;
  $vars['classes_array'][] = 'flexslider_views_slideshow_slide views-row-' . $current;

  // @todo figure out why this if statement is here
  if ($vars['count']) {
    $vars['classes_array'][] =  'views_slideshow_cycle_hidden';
  }
  // @todo add option to toggle views rows counters on/off
  $vars['classes_array'][] = ($vars['count'] % 2) ? 'views-row-even' : 'views-row-odd';

  $vars['rendered_items'] = '';
  foreach ($vars['items'] as $item_count => $item) {
    $vars['rendered_items'] .= theme('flexslider_views_slideshow_main_frame_row_item', array('item' => $item, 'item_count' => $item_count, 'view' => $vars['view']));
  }
}

/**
 * FlexSlider Views theme for an item within a row
 *
 * @ingroup themeable
 */
function _flexslider_views_slideshow_preprocess_flexslider_views_slideshow_main_frame_row_item(&$vars) {
  $vars['classes_array'][] = 'views-row views-row-' . $vars['item_count'];
  if (!$vars['item_count']) {
    $vars['classes_array'][] = 'views-row-first';
  }
  if ($vars['item_count'] % 2) {
    $vars['classes_array'][] = 'views-row-even';
  }
  else {
    $vars['classes_array'][] = 'views-row-odd';
  }

  /**
   * Support custom row classes.
   */
  if ($row_class = $vars['view']->style_plugin->get_row_class($vars['item_count'])) {
    $vars['classes_array'][] = $row_class;
  }
}
