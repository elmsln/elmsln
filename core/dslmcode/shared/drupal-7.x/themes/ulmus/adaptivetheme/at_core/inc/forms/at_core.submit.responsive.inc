<?php

/**
 * @file
 * Build and save the responsive layouts and styles
 *
 * This is the main submit handler for building the core layout and processing
 * the responsive stylesheets. The output is five stylesheets saved to public
 * files - the main responsive layout, two conditional stylesheets, the main
 * responsive styles (the aggregated styles with embedded media queries) and a
 * default layout CSS file (for when desktop first method has been selected).
 */
function at_core_submit_reponsive($values, $theme_name, $path) {
  global $path_to_at_core;

  // Set up some paths we use to get and save files
  $path_to_responsive_css = drupal_get_path('theme', $theme_name) . '/css/';
  $path_to_panels_css = $path_to_at_core . '/layouts/css/';

  // Initialize
  $smalltouch_landscape_panels_data = array();

  // Get the page layout config array
  $layout_variables = page_layout();

  // $layouts will hold all the page level layouts
  $layouts = array();

  // Initialize the $is_default_layout variable, we use this to test against
  $is_default_layout = $values['global_default_layout'];

  // Get the panels config array
  $rpl = responsive_panels_data_structure();

  // We need to add a float to some panels layouts in certain instances
  $float = ".at-panel .region {display:inline;float:left}";

  // Holds all styles from the responsive stylesheets
  $responsive_styles = array();
  $panel_subtypes = array();
  $panel_styles = array();

  // Get the values for the panels layouts
  unset($rpl['one']); // unset panels layout one, it has no layout data
  foreach ($rpl as $grouped => $panels_layout_groups) {
    foreach ($panels_layout_groups as $panel_layout_group) {
      foreach ($panel_layout_group as $group_items => $item_value) {
        $panel_subtypes[] = $item_value['theme'];
        if (array_key_exists('styles', $item_value)) {
          $panel_styles[] = $item_value['styles'];
        }
      }
    }
  }

  // If the Cascading media queries CSS file is enabled, load these styles first
  if ($values['enable_custom_media_queries'] === 1) {
    if (file_exists($path_to_responsive_css . 'responsive.custom.css')) {
      $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.custom.css', FALSE);
      $responsive_styles[] = $responsive_css . "\n";
    }
  }

  // Set variables for respond.js
  $load_respondjs = FALSE;
  if ($values['load_respondjs'] === 1) {
    $load_respondjs = TRUE;
  }

  // Set variables for onmediaquery.js and media_queries.js
  $responsive_js_css = '';
  $responsive_js = FALSE;
  if ($values['load_onmediaqueryjs'] === 1 && $values['disable_responsive_styles'] === 0) {
    $responsive_js = TRUE;
  }

  // Gutter width
  $gutters = "/* Gutters are not currently overridden in theme settings, but may be in theme CSS */";
  if (isset($values['enable_markup_overides']) && $values['enable_markup_overides'] === 1) {
    if (isset($values['global_gutter_width']) && is_numeric($values['global_gutter_width'])) {
      $gutter = check_plain($values['global_gutter_width']) . 'px';
      $gutters = "/* Gutters */" . "\n" . "#main-content,.block-inner,.pane-inner,.menu-wrapper,.branding-elements,.breadcrumb-wrapper,.attribution,.at-panel .rounded-corner,.block-panels-mini > .block-title,.rendered-by-ds .at-panel .region-inner,div.messages,.at-gutter {margin-left:$gutter;margin-right:$gutter;} #content .panel-display,#content .panel-flexible {margin-left:-$gutter;margin-right:-$gutter;}";
    }
  }

  // Smalltouch Portrait
  if ($values['smalltouch_portrait_media_query']) {

    $device = 'smalltouch_portrait';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $smalltouch_portrait_layout_data[$value] = filter_xss_admin($values["$device" . '_' . "$value"]);
      }
    }
    // In smalltouch portrait we invoke the layout builder, but the values are not
    // used since the CSS is actually hard coded. I have done this because, at some
    // stage in the future this layout might not be hard coded and we might really
    // need to return a dynamically built layout. Note that $layout is only ever
    // used in desktop first - never in mobile first.
    $layout = at_build_page_layout($smalltouch_portrait_layout_data['layout'], $smalltouch_portrait_layout_data['sidebar_first'], $smalltouch_portrait_layout_data['sidebar_second'], $smalltouch_portrait_layout_data['sidebar_unit'], $theme_name);

    $method = $smalltouch_portrait_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $smalltouch_portrait_layout_data['page_width'] . $smalltouch_portrait_layout_data['page_unit'] . '}';
    $media_query = $smalltouch_portrait_layout_data['media_query'];

    if ($responsive_js == TRUE) {
      $responsive_js_css = 'html {font-family: smalltouch_portrait} /* Font family for media_queries.js */';
    }

    // If mobile first then smalltouch portrait needs to do nothing, else its
    // problematic to set the layout later due to the cascade and inheritance
    if ($is_default_layout === 'smalltouch-portrait') {
      $css = '';
      // If responsive js is TRUE we output the media query with CSS styles
      if ($responsive_js == TRUE) {
        $css = $comment . '@media ' . $media_query . ' {' . "\n" . $responsive_js_css . "\n" . '}';
      }
    }
    else {
      // Smalltouch portrait panels are all 100% width and stacked, we need to
      // overpower the default layouts when in desktop first mode
      $smalltouch_portrait_panels_layout = '.at-panel .region,.at-panel .panel-row,.at-panel .panel-row .region,.at-panel .inset-wrapper{float:none;display:block;width:100%}';

      // Build the styles string
      $styles = $width . "\n" . $layout . "\n" . $smalltouch_portrait_panels_layout;

      // Reset styles if we are loading responsive js
      if ($responsive_js == TRUE) {
        $styles = "\n" . $responsive_js_css . "\n" . $width . "\n" . $layout . "\n" . $smalltouch_portrait_panels_layout;
      }

      // CSS wrapped in the media query
      $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';
    }

    // Get and wrap the responsive CSS styles in the relative media query
    $responsive_smalltouch_portrait_css = '';
    if (file_exists($path_to_responsive_css . 'responsive.smalltouch.portrait.css')) {
      $responsive_smalltouch_portrait_css = $path_to_responsive_css . 'responsive.smalltouch.portrait.css';
    }
    // Legacy support for pre 7.x-3.2 subthemes
    elseif (file_exists($path_to_responsive_css . 'responsive.smartphone.portrait.css')) {
      $responsive_smalltouch_portrait_css = $path_to_responsive_css . 'responsive.smartphone.portrait.css';
    }
    if (!empty($responsive_smalltouch_portrait_css)) {
      $responsive_css = drupal_load_stylesheet($responsive_smalltouch_portrait_css, FALSE);
      $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';
    }

    $layouts[] = $css;
  }

  // Smalltouch Landscape
  if ($values['smalltouch_landscape_layout']) {

    $device = 'smalltouch_landscape';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $smalltouch_landscape_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    $layout = at_build_page_layout($smalltouch_landscape_layout_data['layout'], $smalltouch_landscape_layout_data['sidebar_first'], $smalltouch_landscape_layout_data['sidebar_second'], $smalltouch_landscape_layout_data['sidebar_unit'], $theme_name);

    $method = $smalltouch_landscape_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $smalltouch_landscape_layout_data['page_width'] . $smalltouch_landscape_layout_data['page_unit'] . '}';
    $media_query = $smalltouch_landscape_layout_data['media_query'];

    // Get the panel layout settings
    foreach ($panel_subtypes as $subtype) {
      $smalltouch_landscape_panel_settings[] = $device . '_' . $subtype;
    }

    foreach ($smalltouch_landscape_panel_settings as $setting) {
      if (!empty($values[$setting])) {
        $option = $values[$setting];
      }
      else {
        // Provide a fallback layout in case settings fail during submit
        $smalltouch_landscape_panel_substr_setting = substr($setting, 21);
        $smalltouch_landscape_panel_substr_setting = str_replace('_', '-', $smalltouch_landscape_panel_substr_setting) . '-stack';
        $option = $smalltouch_landscape_panel_substr_setting;
      }
      $smalltouch_landscape_panels_data[] = $option;
    }

    // Generate the panels layouts
    $smalltouch_landscape_panels_css = at_build_panels_layout_css($panel_styles, $smalltouch_landscape_panels_data);
    $panels_layouts = $float . $smalltouch_landscape_panels_css;

    // Build the styles string
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;

    // Reset styles if we are loading responsive js
    if ($responsive_js == TRUE) {
      $responsive_js_css = "\n" . 'html {font-family: smalltouch_landscape} /* Font family for media_queries.js */';
      $styles = $responsive_js_css . $width . "\n" . $layout . "\n" . $panels_layouts;
    }

    // CSS wrapped in the media query
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

    // Get and wrap the responsive CSS styles in the relative media query
    $responsive_smalltouch_landscape_css = '';
    if (file_exists($path_to_responsive_css . 'responsive.smalltouch.landscape.css')) {
      $responsive_smalltouch_landscape_css = $path_to_responsive_css . 'responsive.smalltouch.landscape.css';
    }
    // Legacy support for pre 7.x-3.2 subthemes
    elseif (file_exists($path_to_responsive_css . 'responsive.smartphone.landscape.css')) {
      $responsive_smalltouch_landscape_css = $path_to_responsive_css . 'responsive.smartphone.landscape.css';
    }
    if (!empty($responsive_smalltouch_landscape_css)) {
      $responsive_css = drupal_load_stylesheet($responsive_smalltouch_landscape_css, FALSE);
      $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';
    }

    $layouts[] = $css;
  }

  // Tablet Portrait
  if ($values['tablet_portrait_layout']) {

    $device = 'tablet_portrait';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $tablet_portrait_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    // Workaround upgrade issues for some settings
    if ($tablet_portrait_layout_data['layout'] == 'two_col_stack') {
      $tablet_portrait_layout_data['layout'] = 'two_sidebars_right_stack';
    }
    $layout = at_build_page_layout($tablet_portrait_layout_data['layout'], $tablet_portrait_layout_data['sidebar_first'], $tablet_portrait_layout_data['sidebar_second'], $tablet_portrait_layout_data['sidebar_unit'], $theme_name);

    $method = $tablet_portrait_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $tablet_portrait_layout_data['page_width'] . $tablet_portrait_layout_data['page_unit'] . '}';
    $media_query = $tablet_portrait_layout_data['media_query'];

    $tablet_portrait_panel_settings = array();
    $tablet_portrait_panels_data = array();
    // Get the panel layout settings and CSS for these layouts
    foreach ($panel_subtypes as $subtype) {
      $tablet_portrait_panel_settings[] = $device . '_' . $subtype;
    }

    foreach ($tablet_portrait_panel_settings as $setting) {
      if (!empty($values[$setting])) {
        $option = $values[$setting];
      }
      else {
        // Provide a fallback layout in case settings fail during submit
        $tablet_portrait_panel_substr_setting = substr($setting, 16);
        $tablet_portrait_panel_substr_setting = str_replace('_', '-', $tablet_portrait_panel_substr_setting);
        $option = $tablet_portrait_panel_substr_setting;
      }
      $tablet_portrait_panels_data[] = $option;
    }

    // Generate the panels layouts
    $tablet_portrait_panels_css = at_build_panels_layout_css($panel_styles, $tablet_portrait_panels_data);
    $panels_layouts = $float . $tablet_portrait_panels_css;

    // Build the styles string
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;

    // Reset styles if we are loading responsive js
    if ($responsive_js == TRUE) {
      $responsive_js_css = "\n" . 'html {font-family: tablet_portrait} /* Font family for media_queries.js */';
      $styles = $responsive_js_css . $width . "\n" . $layout . "\n" . $panels_layouts;
    }

    // CSS wrapped in the media query
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

     // Get and wrap the responsive CSS styles in the relative media query
    if (file_exists($path_to_responsive_css . 'responsive.tablet.portrait.css')) {
      $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.tablet.portrait.css', FALSE);
      $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';
    }

    $layouts[] = $css;
  }

  // Tablet Landscape
  if ($values['tablet_landscape_layout']) {

    $device = 'tablet_landscape';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $tablet_landscape_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    // Workaround upgrade issues for some settings
    if ($tablet_portrait_layout_data['layout'] == 'two_col_stack') {
      $tablet_portrait_layout_data['layout'] = 'two_sidebars_right_stack';
    }
    $layout = at_build_page_layout($tablet_landscape_layout_data['layout'], $tablet_landscape_layout_data['sidebar_first'], $tablet_landscape_layout_data['sidebar_second'], $tablet_landscape_layout_data['sidebar_unit'], $theme_name);

    $method = $tablet_landscape_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $tablet_landscape_layout_data['page_width'] . $tablet_landscape_layout_data['page_unit'] . '}';
    $media_query = $tablet_landscape_layout_data['media_query'];

    // Get the panel layout settings
    foreach ($panel_subtypes as $subtype) {
      $tablet_landscape_panel_settings[] = $device . '_' . $subtype;
    }
    foreach ($tablet_landscape_panel_settings as $setting) {
      if (!empty($values[$setting])) {
        $option = $values[$setting];
      }
      else {
        // Provide a fallback layout in case settings fail during submit
        $tablet_landscape_panel_substr_setting = substr($setting, 17);
        $tablet_landscape_panel_substr_setting = str_replace('_', '-', $tablet_landscape_panel_substr_setting);
        $option = $tablet_landscape_panel_substr_setting;
      }
      $tablet_landscape_panels_data[] = $option;
    }
    // Generate the panels layouts
    $tablet_landscape_panels_css = at_build_panels_layout_css($panel_styles, $tablet_landscape_panels_data);
    $panels_layouts = $float . $tablet_landscape_panels_css;

    // Build the styles string
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;

    // Reset styles if we are loading responsive js
    if ($responsive_js == TRUE) {
      $responsive_js_css = "\n" . 'html {font-family: tablet_landscape} /* Font family for media_queries.js */';
      $styles = $responsive_js_css . $width . "\n" . $layout . "\n" . $panels_layouts;
    }

    // CSS wrapped in the media query
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

     // Get and wrap the responsive CSS styles in the relative media query
    if (file_exists($path_to_responsive_css . 'responsive.tablet.landscape.css')) {
      $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.tablet.landscape.css', FALSE);
      $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';
    }

    $layouts[] = $css;
  }

  // Standard Layout (bigscreen)
  if ($values['bigscreen_layout']) {

    $device = 'bigscreen';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $bigscreen_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    $layout = at_build_page_layout($bigscreen_layout_data['layout'], $bigscreen_layout_data['sidebar_first'], $bigscreen_layout_data['sidebar_second'], $bigscreen_layout_data['sidebar_unit'], $theme_name);

    $method = $bigscreen_layout_data['layout'];
    $comment = "/* $device $method */";
    $width = "\n" . '.container {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . '}';
    $media_query = $bigscreen_layout_data['media_query'];

    // Standard layout can have a max-width
    if ($values['bigscreen_set_max_width'] === 1 && $bigscreen_layout_data['page_unit'] === '%') {
      if (!empty($values['bigscreen_max_width'])) {
        $width = "\n" . '.container {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . ';max-width:' . $values['bigscreen_max_width'] . $values['bigscreen_max_width_unit'] . '}';
      }
      else {
        $width = "\n" . '.container {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . ';max-width:' . $values['bigscreen_max_width'] . $values['bigscreen_max_width_unit'] . '}';
      }
    }
    $bigscreen_panels_data = array();
    // Get the panel layout settings
    foreach ($panel_subtypes as $subtype) {
      $bigscreen_panel_settings[] = $device . '_' . $subtype;
    }
    foreach ($bigscreen_panel_settings as $setting) {
      if (!empty($values[$setting])) {
        $option = $values[$setting];
      }
      else {
        // Provide a fallback layout in case settings fail during submit
        $bigscreen_panel_substr_setting = substr($setting, 16);
        $bigscreen_panel_substr_setting = str_replace('_', '-', $bigscreen_panel_substr_setting);
        $option = $bigscreen_panel_substr_setting;
      }
      $bigscreen_panels_data[] = $option;
    }
    // Generate the panels layouts
    $bigscreen_panels_css = at_build_panels_layout_css($panel_styles, $bigscreen_panels_data);

    // Prepend the float
    $panels_layouts = $float . $bigscreen_panels_css;

    // Build the styles string
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;

    // Reset styles if we are loading responsive js
    if ($responsive_js == TRUE) {
      $responsive_js_css = "\n" . 'html {font-family: standard} /* Font family for media_queries.js */';
      $styles = $responsive_js_css . $width . "\n" . $layout . "\n" . $panels_layouts;
    }

    // We need to do some conditional checks to account for the users settings:
    // - is this mobile first or desktop first?
    // - is the responsive capability disabled?

    // Mobile first or Desktop first?
    if ($is_default_layout === 'standard-layout') {
      // DESKTOP FIRST
      // Just the responsive js font family
      $css = '';
      if ($responsive_js == TRUE) {
        $css = $comment . "\n" . '@media ' . $media_query . ' {' . $responsive_js_css . "\n" . '}';
      }

      // Prepare a "default layout" for output to file when desktop first
      $desktop_first_layout = $gutters . "\n" . $comment . $styles . "\n";
    }
    else {
      // MOIBLE FIRST
      $css = $comment . "\n" . '@media ' . $media_query . ' {' . $styles . "\n" . '}';
      $desktop_first_layout = '/* Not likely, this is mobile first - this themer is rocking the hardest! */';
    }

    // Responsive capability OFF?
    if ($values['disable_responsive_styles'] === 1) {
      // If its off we have to load something, so we choose to use the bigscreen
      // layout and load that
      $desktop_first_layout = $gutters . "\n" . $comment . $styles;
    }

    // add $css to the layouts array
    $layouts[] = $css;
  }
  //****** END bigscreen layout ******//

  // Internet Exploder
  // We only want to load what is absolutely required for IE, depending on the
  // theme settings and what version we are targeting, remember, this only takes
  // care of generating the stylesheets so what you see here are lots of messages
  // being set for the themer to get a handle on what is going on, load.inc and
  // adaptivetheme_preprocess_html() are actually loading the files.

  // $lt_ie9_css's assigned values all come from the bigscreen layout, since its
  // the last layout to assign values to those variables
  $lt_ie9_css = $comment . $width . "\n" . $layout . "\n" . $panels_layouts;

  // Reset $lt_ie9_css if we are loading responsive js
  if ($responsive_js == TRUE) {
    $lt_ie9_css = $comment . $responsive_js_css . $width . "\n" . $layout . "\n" . $panels_layouts;
  }

  // Get the lt ie8 panels layouts if enabled
  $lt_ie8_css = '/* IE6/7 percentage rounding error fixes are OFF */';
  if ($values['load_ltie8css'] === 1) {
    $ie_panels_layouts = drupal_load_stylesheet($path_to_panels_css . 'ie_defaults.css', FALSE);
    $lt_ie8_css = $ie_panels_layouts;
  }

  // Respond.js is OFF
  if ($load_respondjs == FALSE) {

    // should we load the IE6/7 rounding error fixes?
    if ($values['load_ltie8css'] === 1) {

      // add the E6/7 rounding error fixes to $lt_ie9_css, set a message in $lt_ie8_css
      $lt_ie9_css = $comment . $width . "\n" . $layout . "\n" . $panels_layouts . "\n" . $ie_panels_layouts;
      $lt_ie8_css = '/* The IE6/7 panels layouts are loading in the lt IE9 CSS, to save an HTTP request hit on your server */';

      // Desktop first?
      if ($is_default_layout === 'standard-layout') {
        // repopulate $lt_ie8_css
        $lt_ie8_css = $ie_panels_layouts;
      }
    }
  }

  // Respond.js is ON
  if ($load_respondjs == TRUE) {
    $lt_ie9_css = '/* respond.js is loading so we dont load this file. IE6, 7 and 8 will rely on respond.js to work its magic */';
  }

  // Desktop first?
  if ($is_default_layout === 'standard-layout') {
    $lt_ie9_css = '/* The standard layout is the default layout, IE styles are not required because you are doing desktop first design */';
  }

  // Responsive capability OFF?
  if ($values['disable_responsive_styles'] === 1) {
    $lt_ie9_css = '/* Responsive capabilites are disabled, we no longer need to load an IE specific layout */';
  }

  // Get and wrap the responsive CSS styles in the relative media query
  if (file_exists($path_to_responsive_css . 'responsive.desktop.css')) {
    $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.desktop.css', FALSE);
    $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';
  }

  // Generate the layout and responsive styles stylesheets
  // Here we generate five files:
  // 1. $theme_name.default.layout
  // 2. $theme_name.responsive.layout
  // 3. $theme_name.lt-ie9.layout
  // 4. $theme_name.lt-ie8.layout
  // 5. $theme_name.responsive.styles
  // adaptivetheme_preprocess_html() will take care of loading the right ones
  // when they are needed.

  // responsive layout
  $responsive_layout_data = implode("\n", $layouts);

  // Prepend the gutters to the responsive layout if we're doing mobile first
  if ($is_default_layout !== 'standard-layout') {
    $responsive_layout = $gutters . "\n" . $responsive_layout_data;
  }
  else {
    $responsive_layout = $responsive_layout_data;
  }

  // Nuke $responsive_layout if we really don't need it
  if ($values['disable_responsive_styles'] == 1) {
    $responsive_layout = '/* Responsive capabilites are disabled, only the standard layout is loaded in themename.default.layout.css */';
  }

  // IE assignments, not sure why I am doing this, could be that I meant to do
  // something at this stage and have forgotton for now...
  $lt_ie9_layout = $lt_ie9_css;
  $lt_ie8_layout = $lt_ie8_css;

  // Aggregate the design stylesheets
  $responsive_css = implode("\n", $responsive_styles);

  // Regex relative paths. This mimics Drupal cores drupal_build_css_cache(), but
  // its not as powerful because assets must be relative to the theme root.
  $_base = base_path() . $path_to_responsive_css;
  _drupal_build_css_path(NULL, $_base);
  $responsive_css = preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_drupal_build_css_path', $responsive_css);

  // Build a keyed array: file names as key, layout data as value
  $files = array(
    "$theme_name.default.layout" => $desktop_first_layout,
    "$theme_name.responsive.layout" => $responsive_layout,
    "$theme_name.lt-ie9.layout" => $lt_ie9_layout,
    "$theme_name.lt-ie8.layout" => $lt_ie8_layout,
    "$theme_name.responsive.styles" => $responsive_css,
  );

  // Loop over the array and save each file, and we're done!
  foreach ($files as $key => $value) {
    $filepath = "$path/$key.css";
    file_unmanaged_save_data($value, $filepath, FILE_EXISTS_REPLACE);
  }
}
