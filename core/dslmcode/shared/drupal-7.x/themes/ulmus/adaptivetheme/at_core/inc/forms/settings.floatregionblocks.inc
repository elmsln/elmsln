<?php

/**
 * @file
 * Generate form elments for the Float Region Blocks settings.
 */
function at_core_float_region_blocks_form(&$form, $info_array) {
  // Regions we don't want to include
  $unset_regions = array(
    'dashboard_main',
    'dashboard_sidebar',
    'dashboard_inactive',
    'page_bottom',
    'page_top',
    'content', // exclude the main content region
  );

  // Prepare regions
  foreach ($info_array['regions'] as $key => $value) {
    if (in_array($key, $unset_regions)) {
      unset($key);
    }
    if (isset($key)) {
      $regions[$key] = $value;
    }
  }

  // Setup the options for the select list
  $fbr_options = array(
    '<none>' => t('none'),
    '2' => '2',
    '3' => '3',
    '4' => '4',
    '5' => '5',
    '6' => '6',
    '7' => '7',
    '8' => '8',
    '9' => '9',
    '10' => '10',
    '11' => '11',
    '12' => '12',
  );

  $direction_options = array(
    'left' => t('Left'),
    'right' => t('Right'),
  );

  // Don't include this feature for now, its too late in the cycle
  // $breakpoints = array(
  //   '<none>' => t('none - I can handle this in CSS'),
  //   'smalltouch_portrait' => t('Smalltouch Portrait'),
  //   'smalltouch_landscape' => t('Smalltouch Landscape'),
  //   'tablet_portrait' => t('Tablet Portrait'),
  //   'tablet_landscape' => t('Tablet Landscape'),
  // );

  // Top level wrapper fieldset
  $form['at']['float-region-blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Float Region Blocks'),
    '#description' => t('<h3>Float Region Blocks</h3><p>Select number of columns<sup>(i)</sup> for each region. For example if you want four blocks to line horizontally up choose 4, then select the float direction. Clearing<sup>(ii)</sup> (if you are trying to create a grid) and mobile displays<sup>(iii)</sup> must be accounted for in your theme.<p><ol><li>This will not create real columns, it merely sets a width on each block in the region. For example if you select 4, each block will be 25% wide, if you then add a fifth block to that region it will wrap below the other four, and so on.</li><li>There is no automagical clearing for uneven height blocks, so be weary of trying to create a grid with this. If you need real columns use a <a href="!gpanels_link" target="_blank">Gpanel</a> or the <a href="!panels_link" target="_blank">Panels module</a>.</li><li>See <code>responsive.custom.css</code> in your theme for an example of how to control blocks in mobile displays.</li></ol>', array('!gpanels_link' => 'http://adaptivethemes.com/documentation/using-gpanels', '!panels_link' => 'http://drupal.org/project/panels')),
    '#weight' => 35,
  );

  // Build form elements for each region
  foreach ($regions as $region_name => $region_label) {

    $title = check_plain($region_label);
    $region_name = check_plain($region_name);

    $form['at']['float-region-blocks']['region-options-' . $region_name] = array(
      '#type' => 'fieldset',
      '#title' => t("Options for the $title region"),
    );
    $form['at']['float-region-blocks']['region-options-' . $region_name]['float_block_' . $region_name] = array(
      '#type' => 'select',
      '#title' => t($title),
      '#default_value' => at_get_setting('float_block_' . $region_name),
      '#options' => $fbr_options,
    );
    $form['at']['float-region-blocks']['region-options-' . $region_name]['float_block_direction_' . $region_name] = array(
      '#type' => 'radios',
      '#title' => t('Float'),
      '#default_value' => at_get_setting('float_block_direction_' . $region_name) ? at_get_setting('float_block_direction_' . $region_name) : 'left',
      '#options' => $direction_options,
      '#states' => array('invisible' => array('select[name=float_block_' . $region_name . ']' => array('value' => '<none>'))),
    );

    // Don't include this feature for now, its too late in the cycle, better to
    // work on a much improved way of doing this for a point release later on.
    //$form['at']['float-region-blocks']['region-options-' . $region_name]['float_block_breakpoint_' . $region_name] = array(
    //  '#type' => 'select',
    //  '#title' => t('Breakpoint'),
    //  '#default_value' => at_get_setting('float_block_breakpoint_' . $region_name),
    //  '#options' => $breakpoints,
    //);
  }
}
