<?php

/**
 * @file
 * Implimentation of hook_form_system_theme_settings_alter()
 *
 * @param $form: Nested array of form elements that comprise the form.
 * @param $form_state: A keyed array containing the current state of the form.
 */
function adaptivetheme_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  // Get our plugin system functions.
  require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/plugins.inc');

  // We need some getters.
  require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/get.inc');
  $path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Get the active theme name, we need it at some stage.
  $theme_name = $form_state['build_info']['args'][0];

  // Get the active themes info array
  $info_array = at_get_info($theme_name);

  // Set up variables for legacy and non-legacy themes
  $legacy_theme = FALSE;
  if (!isset($info_array['release']) || $info_array['release'] === '7.x-2.x') {
    $legacy_theme = TRUE;
  }
  elseif (isset($legacy_info['release']) && $legacy_info['release'] === '7.x-3.x') {
    $legacy_theme = FALSE;
  }

  // Version messages
  $version_message = '';
  if (at_get_setting('atcore_version_test', $theme_name) === 1) {
    if ($legacy_theme == TRUE) {
      $version_message = t('<p>The version of your theme (@theme) is not designed to run on <a href="!link_project" target="_blank">Adaptivetheme 7.x.3.x</a>. It will probably run, but your experience will not be optimal. You have three courses of action to choose from:</p>', array('!link_project' => 'http://drupal.org/project/adaptivetheme', '@theme' => $theme_name));
      $version_message .= t('<ol><li>Downgrade Adaptivetheme to 7.x-2.x</li><li>Upgrade your theme to the 7.x-3.x branch&thinsp;&mdash;&thinsp;you will need to check if an upgrade exists.</li><li>Add the line <code>"release = 7.x-3.x"</code> (less quotes) to your sub-themes info file and clear the cache to make this message go away.</li></ol>');
      $version_message .= t('<p>You can turn off this message in the Debug settings, look for "Sub-theme compatibility test".</p>');
      drupal_set_message(filter_xss_admin($version_message), 'warning');
    }
    elseif ($legacy_theme == FALSE) {
      $version_message = t('<p>This theme (@theme) is compatible with <a href="!link_project" target="_blank">Adaptivetheme 7.x.3.x</a>. You are good to go! You can turn off this message in the Debug settings, look for "Sub-theme compatibility test".</p>', array('!link_project' => 'http://drupal.org/project/adaptivetheme', '@theme' => $theme_name));
      drupal_set_message(filter_xss_admin($version_message), 'status');
    }
  }

  // Get the admin theme so we can set a class for styling this form,
  // variable_get() returns 0 if the admin theme is the default theme.
  $admin_theme = variable_get('admin_theme') ? variable_get('admin_theme') : $theme_name;
  $admin_theme_class = 'admin-theme-' . drupal_html_class($admin_theme);

  // LAYOUT SETTINGS
  // Build a custom header for the layout settings form.
  $logo = file_create_url(drupal_get_path('theme', 'adaptivetheme') . '/logo.png');
  $layout_header  = '<div class="at-settings-form layout-settings-form ' . $admin_theme_class . '"><div class="layout-header theme-settings-header clearfix">';
  $layout_header .= '<h1>' . t('Layout &amp; General Settings') . '</h1>';
  $layout_header .= '<p class="docs-link"><a href="http://adaptivethemes.com/documentation/adaptivetheme-7x-3x" title="View online documentation" target="_blank">View online documentation</a></p>';
  $layout_header .= '<p class="logo-link"><a href="http://adaptivethemes.com" title="Adaptivethemes.com - Rocking the hardest since 2006" target="_blank"><img class="at-logo" src="' . $logo . '" /></a></p>';
  $layout_header .= '</div>';

  // INCLUDES
  $includes_array = array(
    'pagelayout',
    'responsivepanels',
    'global',
    'filemanagement',
    'css',
    'polyfills',
    'metatags',
    'debug',
    'extensions',
  );
  foreach ($includes_array as $include_file) {
    require_once($path_to_at_core . '/inc/forms/settings.' . $include_file . '.inc');
  }

  $form['at-settings'] = array(
    '#type' => 'vertical_tabs',
    '#description' => t('Layout'),
    '#prefix' => $layout_header,
    '#suffix' => '</div>',
    '#weight' => -10,
    '#attached' => array(
      'css' => array(drupal_get_path('theme', 'adaptivetheme') . '/css/at.settings.form.css'),
    ),
  );

  // Call all the default settings forms.
  at_core_page_layout_form($form, $theme_name);
  at_core_responsive_panels_form($form, $theme_name, $info_array);
  at_core_global_form($form, $theme_name);
  at_core_filemanagement_form($form, $theme_name);
  at_core_css_form($form, $theme_name);
  at_core_polyfills_form($form, $theme_name);
  at_core_metatags_form($form);
  at_core_debug_form($form);
  at_core_extensions_form($form);

  // EXTENSIONS
  $enable_extensions = isset($form_state['values']['enable_extensions']);
  if (($enable_extensions && $form_state['values']['enable_extensions'] == 1) || (!$enable_extensions && $form['at-settings']['extend']['enable_extensions']['#default_value'] == 1)) {

    // Build a custom header for the Extensions settings form.
    $styles_header  = '<div class="at-settings-form style-settings-form ' . $admin_theme_class . '"><div class="styles-header theme-settings-header clearfix">';
    $styles_header .= '<h1>' . t('Extensions') . '</h1>';
    $styles_header .= '<p class="docs-link"><a href="http://adaptivethemes.com/documentation/extensions" title="View online documentation for Extensions" target="_blank">View online documentation</a></p>';
    $styles_header .= '</div>';

    $form['at'] = array('#type' => 'vertical_tabs',
      '#weight' => -9,
      '#prefix' => $styles_header,
      '#suffix' => '</div>',
    );

    // Include fonts.inc by default, the conditional logic to wrap around this is
    // too hairy to even comtemplate.
    require_once($path_to_at_core . '/inc/fonts.inc');

    // Fonts
    $enable_font_settings = isset($form_state['values']['enable_font_settings']);
    if (($enable_font_settings && $form_state['values']['enable_font_settings'] == 1) || (!$enable_font_settings && $form['at-settings']['extend']['enable']['enable_font_settings']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.fonts.inc');
      at_core_fonts_form($form);
    }

    // Heading styles
    $enable_heading_settings = isset($form_state['values']['enable_heading_settings']);
    if (($enable_heading_settings && $form_state['values']['enable_heading_settings'] == 1) || (!$enable_heading_settings && $form['at-settings']['extend']['enable']['enable_heading_settings']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.headings.inc');
      at_core_headings_form($form);
    }

    // Image alignment
    $enable_image_settings = isset($form_state['values']['enable_image_settings']);
    if (($enable_image_settings && $form_state['values']['enable_image_settings'] == 1) || (!$enable_image_settings && $form['at-settings']['extend']['enable']['enable_image_settings']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.images.inc');
      at_core_images_form($form);
    }

    // Exclude CSS
    $enable_exclude_css = isset($form_state['values']['enable_exclude_css']);
    if (($enable_exclude_css && $form_state['values']['enable_exclude_css'] == 1) || (!$enable_exclude_css && $form['at-settings']['extend']['enable']['enable_exclude_css']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.cssexclude.inc');
      at_core_css_exclude_form($form, $theme_name);
    }

    // Touch icons
    $enable_apple_touch_icons = isset($form_state['values']['enable_apple_touch_icons']);
    if (($enable_apple_touch_icons && $form_state['values']['enable_apple_touch_icons'] == 1) || (!$enable_apple_touch_icons && $form['at-settings']['extend']['enable']['enable_apple_touch_icons']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.touchicons.inc');
      at_core_touch_icons_form($form, $theme_name);
    }

    // Custom CSS
    $enable_custom_css = isset($form_state['values']['enable_custom_css']);
    if (($enable_custom_css && $form_state['values']['enable_custom_css'] == 1) || (!$enable_custom_css && $form['at-settings']['extend']['enable']['enable_custom_css']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.customcss.inc');
      at_core_custom_css_form($form);
    }

    // Mobile regions and blocks (context regions)
    $enable_context_regions = isset($form_state['values']['enable_context_regions']);
    if (($enable_context_regions && $form_state['values']['enable_context_regions'] == 1) || (!$enable_context_regions && $form['at-settings']['extend']['enable']['enable_context_regions']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.contextregions.inc');
      at_core_context_regions_form($form, $info_array);
    }

    // Menu toggle
    $enable_menu_toggle = isset($form_state['values']['enable_menu_toggle']);
    if (($enable_menu_toggle && $form_state['values']['enable_menu_toggle'] == 1) || (!$enable_context_regions && $form['at-settings']['extend']['enable']['enable_menu_toggle']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.menutoggle.inc');
      at_core_menu_toggle_form($form);
    }

    // Float Region blocks
    $enable_float_region_blocks = isset($form_state['values']['enable_float_region_blocks']);
    if (($enable_float_region_blocks && $form_state['values']['enable_float_region_blocks'] == 1) || (!$enable_float_region_blocks && $form['at-settings']['extend']['enable']['enable_float_region_blocks']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.floatregionblocks.inc');
      at_core_float_region_blocks_form($form, $info_array);
    }

    // Modify output
    $enable_markup_overides = isset($form_state['values']['enable_markup_overides']);
    if (($enable_markup_overides && $form_state['values']['enable_markup_overides'] == 1) || (!$enable_markup_overides && $form['at-settings']['extend']['enable']['enable_markup_overides']['#default_value'] == 1)) {
      require_once($path_to_at_core . '/inc/forms/settings.modifyoutput.inc');
      at_core_modify_output_form($form);
    }

    // Print a message if no extensions are enbabled, this is quite hard to detect
    // so we hack it by counting the elements in the array, if there are 4 or less
    // we assume no extensions are enabled.
    $count = count($form['at']);
    if ($count <= 4) {
      $form['at']['no_extensions_enabled'] = array(
        '#type' => 'markup',
        '#markup' => t('No extensions are currently active. Enable Extensions by clicking the Extensions tab above and checking the required extensions, then save the configuration.'),
        '#prefix' => '<div class="no-extensions-enabled">',
        '#suffix' => '</div>',
      );
    }
  }

  // Include a hidden form field with the current release information
  $form['at-release']['at_core'] = array(
    '#type' => 'hidden',
    '#default_value' => '7.x-3.x',
  );

  // Collapse annoying forms
  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;

  /**
   * Originally posted by dvessel (http://drupal.org/user/56782).
   * The following will be processed even if the theme is inactive.
   * If you are on a theme specific settings page but it is not an active
   * theme (example.com/admin/apearance/settings/THEME_NAME), it will
   * still be processed.
   *
   * Build a list of themes related to the theme specific form. If the form
   * is specific to a sub-theme, all parent themes leading to it will have
   * hook_form_theme_settings invoked. For example, if a theme named
   * 'grandchild' has its settings form in focus, the following will be invoked.
   * - parent_form_theme_settings()
   * - child_form_theme_settings()
   * - grandchild_form_theme_settings()
   *
   * If 'child' was in focus it will invoke:
   * - parent_form_theme_settings()
   * - child_form_theme_settings()
   *
   *  @see http://drupal.org/node/943212
   */
  $form_themes = array();
  $themes = list_themes();
  $_theme = $GLOBALS['theme_key'];
  while (isset($_theme)) {
    $form_themes[$_theme] = $_theme;
    $_theme = isset($themes[$_theme]->base_theme) ? $themes[$_theme]->base_theme : NULL;
  }
  $form_themes = array_reverse($form_themes);

  foreach ($form_themes as $theme_key) {
    if (function_exists($form_settings = "{$theme_key}_form_theme_settings")) {
      $form_settings($form, $form_state);
    }
  }

  // Include custom form validation and submit functions
  require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/forms/at_core.validate.inc');
  require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/forms/at_core.submit.inc');

  // Custom validate and submit functions
  $form['#validate'][] = 'at_core_settings_validate';
  $form['#submit'][] = 'at_core_settings_submit';
}
