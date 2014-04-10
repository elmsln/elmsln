<?php

/**
 * @file
 * Generate form elments for the Mobile Regions settings.
 */
function at_core_context_regions_form(&$form, $info_array) {
  // Regions we don't want to include
  $unset_mobile_regions = array(
    'dashboard_main',
    'dashboard_sidebar',
    'dashboard_inactive',
    'page_bottom',
    'page_top',
    'menu_bar', // exclude the menu bar, it has bespoke region markup and moving something to this will end in tears.
    'content', // exclude the main content region, we don't want to unset this?
  );

  // Initialize variable for detection, we reset this to TRUE if a detection module is installed
  $detection = FALSE;
  $browscap_detect = FALSE;
  $mobile_detect = FALSE;

  // Prepare regions
  foreach ($info_array['regions'] as $key => $value) {
    if (in_array($key, $unset_mobile_regions)) {
      unset($key);
    }
    if (isset($key)) {
      $mobile_regions[$key] = $value;
    }
  }

  // Add a do-not-move option to the move regions list
  $do_not_move = array('do_not_move' => '-- nothing selected --');
  $move_regions_list = array_merge($do_not_move, $mobile_regions);
  array_reverse($move_regions_list);

  // Top level wrapper fieldset
  $form['at']['context-regions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile Regions (beta)'),
    '#description' => t('<h3>Mobile Regions and Blocks <sup>(beta)</sup></h3><p>These settings allow you to either <abbr title="Hiding a region means it won\'t print in the output at all, i.e. they are totally nuked">hide</abbr> regions in mobile devices, or move the regions blocks to another region when a mobile device is detected.</p>'),
    '#weight' => 30,
  );

  // Set various messages based on what detection modules are installed, we can leverage both Browscap (legacy reasons) and Mobile Detect
  if (!function_exists('browscap_get_browser') && !function_exists('mobile_detect_get_object')) {
    $form['at']['context-regions']['requirements'] = array(
      '#markup' => t('<p><strong>Detection:</strong> <span class="no-detection">No detection module installed.</span> Please install either the Browscap or Mobile Detect module.</p>
        <ul>
        <li><a href="!browscap_module" target="_blank">Browscap module</a>: allows you to hide or move blocks for all mobile devices.</li>
        <li><a href="!mobiledetect_module" target="_blank">Mobile Detect module</a>: allows you to hide regions in all just smalltouch devices (exclude tablets) or all mobile devices (smalltouch and tablets).</li>
      </ul>', array('!browscap_module' => 'http://drupal.org/project/browscap', '!mobiledetect_module' => 'http://drupal.org/project/mobile_detect')),
    );
  }
  if (function_exists('browscap_get_browser') && !function_exists('mobile_detect_get_object')) {
    $detection = TRUE;
    $browscap_detect = TRUE;
    $form['at']['context-regions']['requirements'] = array(
      '#markup' => t('<p><strong>Detection module:</strong> <span class="detection">Browscap</span></p>
        <p>Alternatively use the <a href="!mobiledetect_module" target="_blank">Mobile Detect module</a> which allows you to hide regions in all just Smalltouchs or all mobile devices.</p>
      </ul>', array('!mobiledetect_module' => 'http://drupal.org/project/mobile_detect')),
    );
  }
  if (function_exists('mobile_detect_get_object') && !function_exists('browscap_get_browser')) {
    $detection = TRUE;
    $mobile_detect = TRUE;
    $form['at']['context-regions']['requirements'] = array(
      '#markup' => t('<p><strong>Detection module:</strong> <span class="detection">Mobile Detect</span></p>'),
    );
  }
  if (function_exists('browscap_get_browser') && function_exists('mobile_detect_get_object')) {
    $detection = TRUE;
    $mobile_detect = TRUE;
    $browscap_detect = FALSE;
    $form['at']['context-regions']['requirements'] = array(
      '#markup' => t('<p><strong>Detection module:</strong> <span class="detection">Mobile Detect</span>. You have both the Browscap and Mobile Detect modules installed, in this case the Mobile Detect module is being used.</p>'),
    );
  }

  // Only show the form if detection is true
  if ($detection === TRUE) {

    // Include a bunch of hidden form elements, we will save these to the variables table later
    // so we do not need to repeat the logic in alter's or other page building operations
    $form['at']['context-regions']['detection'] = array(
      '#type' => 'hidden',
      '#default_value' => $detection,
    );
    $form['at']['context-regions']['browscap_detect'] = array(
      '#type' => 'hidden',
      '#default_value' => $browscap_detect,
    );
    $form['at']['context-regions']['mobile_detect'] = array(
      '#type' => 'hidden',
      '#default_value' => $mobile_detect,
    );

    // Build form elements for each region
    foreach ($mobile_regions as $mobile_region_name => $mobile_region_label) {

      $mobile_region_title = check_plain($mobile_region_label);
      $mobile_region_name = check_plain($mobile_region_name);

      $form['at']['context-regions']['region-options-' . $mobile_region_name] = array(
        '#type' => 'fieldset',
        '#title' => t($mobile_region_title),
      );

      // UNSET
      $form['at']['context-regions']['region-options-' . $mobile_region_name]['unset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Hide'),
      );

      // When browscap provides detection we only show a simplified option to hide the region - we can use this both as a trigger to show
      // more options when Mobile Detect is active, or as the actual setting when only Browscap is active.
      $form['at']['context-regions']['region-options-' . $mobile_region_name]['unset']['unset_' . $mobile_region_name] = array(
        '#type' => 'checkbox',
        '#title' => t('Hide region'),
        '#default_value' => at_get_setting('unset_' . $mobile_region_name),
        '#states' => array(
          'disabled' => array(
            'input[name=move_region_' . $mobile_region_name . ']' => array('checked' => TRUE),
          )
        ),
      );

      // When Mobile Detect provides detection we have an expanded set of advanced options
      if ($mobile_detect === TRUE) {
        $form['at']['context-regions']['region-options-' . $mobile_region_name]['unset']['unset_options_' . $mobile_region_name] = array(
          '#type' => 'radios',
          '#title' => t('Hide region options'),
          '#options' => array(
            'unset_smalltouch' => t('Hide in Smalltouch devicess'),
            'unset_all_devices' => t('Hide in all mobile devices'),
          ),
          '#default_value' => at_get_setting('unset_options_' . $mobile_region_name) ? at_get_setting('unset_options_' . $mobile_region_name) : 'unset_smalltouch',
          '#states' => array(
            'visible' => array(
              'input[name=unset_' . $mobile_region_name . ']' => array('checked' => TRUE),
            ),
            'disabled' => array(
              'input[name=move_region_' . $mobile_region_name . ']' => array('checked' => TRUE),
            ),
          ),
        );
      }

      // MOVE
      $form['at']['context-regions']['region-options-' . $mobile_region_name]['move'] = array(
        '#type' => 'fieldset',
        '#title' => t('Move'),
      );
      // When browscap provides detection we only show a simplified option to hide the region - we can use this both as a trigger to show
      // more options when Mobile Detect is active, or as the actual setting when only Browscap is active.
      $form['at']['context-regions']['region-options-' . $mobile_region_name]['move']['move_region_' . $mobile_region_name] = array(
        '#type' => 'checkbox',
        '#title' => t('Move blocks'),
        '#default_value' => at_get_setting('move_region_' . $mobile_region_name),
        '#states' => array(
          'disabled' => array(
            'input[name=unset_' . $mobile_region_name . ']' => array('checked' => TRUE),
          )
        ),
      );
      // When Mobile Detect provides detection we have an expanded set of advanced options
      if ($mobile_detect === TRUE) {
        $form['at']['context-regions']['region-options-' . $mobile_region_name]['move']['move_options_' . $mobile_region_name] = array(
          '#type' => 'radios',
          '#title' => t('Move region options'),
          '#options' => array(
            'move_smalltouch' => t('Move in Smalltouchs'),
            'move_all_devices' => t('Move in all mobile devices'),
          ),
          '#default_value' => at_get_setting('move_options_' . $mobile_region_name) ? at_get_setting('move_options_' . $mobile_region_name) : 'move_smalltouch',
          '#states' => array(
            'visible' => array(
              'input[name=move_region_' . $mobile_region_name . ']' => array('checked' => TRUE),
            ),
            'disabled' => array(
              'input[name=unset_region_' . $mobile_region_name . ']' => array('checked' => TRUE),
            ),
          ),
        );
      }
      $form['at']['context-regions']['region-options-' . $mobile_region_name]['move']['move_' . $mobile_region_name] = array(
        '#type' => 'select',
        '#title' => t('Move to:'),
        '#default_value' => at_get_setting('move_' . $mobile_region_name),
        '#options' => $move_regions_list,
        '#states' => array(
          'invisible' => array(
            array('input[name=move_region_' . $mobile_region_name . ']' => array('checked' => FALSE)),
          ),
        ),
      );
    }

    // Caveats
    $form['at']['context-regions']['caveats'] = array(
      '#markup' => t('<p>Caveats:<p><ol><li>Normal weight settings are lost when blocks are moved.</li><li>If the target region has no blocks by default, Adaptivetheme will generate the region markup. The markup is hard coded and does not account for modifications elsewhere in your theme, such as region template suggestion overrides.</li></ol>'),
    );
  }
}
