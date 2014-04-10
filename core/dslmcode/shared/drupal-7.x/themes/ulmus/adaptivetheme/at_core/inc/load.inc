<?php

/**
 * @file
 * Provides frequently used functions that load something, ususally CSS or JS
 * files, or that provide assistance to those loaders.
 */

/**
 * Set messages if files are not found
 *
 *  Adaptivetheme makes heavy use of generated CSS files, if one or more are not
 *  found we set a message warning the user, and dump an error in watchdog.
 *
 * @param $filepath, path to the missing file.
 * @param $theme_name, the active theme.
 */
function at_load_failure($filepath, $theme_name) {
  $message = t('<p>One or more CSS files were not found or does not exist: <em>!files_list</em>. Did you delete any files or change a file name? You may need to save the theme settings or check all files names are correct in your theme. Please view the <a href="!docs_link" target="_blank">online documentation</a>.</p>', array('!files_list' => $filepath, '!docs_link' => 'http://adaptivethemes.com/documentation/file-generation-system'));

  if (!empty($filepath)) {
    watchdog($theme_name, 'CSS file missing or not found @filename', array('@filename' => $filepath), WATCHDOG_ERROR);
    if (user_is_logged_in()) {
      drupal_set_message($message, 'warning');
    }
  }
}

/**
 * Conditionally load stylesheets to set the layout.
 *
 * Each time you save the theme settings AT builds 3 layout stylesheets:
 * 1. themeName.default.layout.css
 * 2. themeName.responsive.layout.css
 * 3. themeName.lt-ie9.layout.css
 *
 * Now we need to load them, but only under certain conditions:
 * a. Is the default layout the standard layout?
 * b. Is the responsive capability disabled?
 *
 * If either a or b equate to TRUE, then we are NOT doing mobile first.
 * If a is FALSE then this is mobile first.
 * If b is FALSE then we are doing responsive design.
 *
 * @param $path
 * @param $theme_name
 */
function at_load_layout_css($path, $theme_name) {

  // Get the info file data
  $info = at_get_info($theme_name);

  // Set a boolean to test which IE stylesheet to load.
  $load_ie8_css = TRUE;

  // Load the default layout if Standard layout is default or responsive styles are disabled
  if (at_get_setting('global_default_layout', $theme_name) === 'standard-layout' || at_get_setting('disable_responsive_styles', $theme_name) === 1) {
    $file = $theme_name . '.default.layout.css';
    $filepath = $path . '/' . $file;
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }
  }

  // Next - check if we need to load the responsive layout
  if (at_get_setting('disable_responsive_styles', $theme_name) === 0) {

    // Responsiveness is not disabled, load the responsive layout
    $filepath = $path . '/' . $theme_name . '.responsive.layout.css';
    $media_query = 'only screen'; // keyword "only" hide this from unsupporting user agents
    at_load_subtheme_responsive_styles($filepath, $media_query, $theme_name, $weight = 0);

    // The lt-ie9.layout.css stylesheet loads under specific conditions:
    // 1. Responsive capabilities are ON
    // 2. Mobile first is ON
    // 3. Respond.js is OFF
    if (at_get_setting('global_default_layout', $theme_name) !== 'standard-layout') {
      if (at_get_setting('load_respondjs', $theme_name) === 0) {
        $load_ie8_css = FALSE;
        $filepath = $path . '/' . $theme_name . '.lt-ie9.layout.css';
        $ie_style['media'] = 'screen';
        $ie_style['condition'] = 'lt IE 9';
        at_load_conditional_styles($filepath, $ie_style, $theme_name);
      }
    }
  }

  // The lt-ie8.layout.css file loads under the exact opposite conditions to the
  // lt-ie9 file. In other words, when lt-ie9 is loading, this is not, when it
  // isn't, this loads. This file only ever holds panels layout overrides for
  // legacy IE browsers and is disabled by default in theme settings.
  if ($load_ie8_css == TRUE) {
    if (at_get_setting('load_ltie8css', $theme_name) === 1) {
      $filepath = $path . '/' . $theme_name . '.lt-ie8.layout.css';
      $ie_style['media'] = 'screen';
      $ie_style['condition'] = 'lt IE 8';
      at_load_conditional_styles($filepath, $ie_style, $theme_name);
    }
  }
}

/**
 * Load Responsive Styles.
 *
 * AT has two modes - Production and Development. Depending on the mode it
 * will load different files. Production mode assume you have finished CSS
 * development and will not need to update styles in the responsive
 * stylesheets, if you do you will need to re-save the theme settings at
 * least once to re-write your $theme_name.responsive.styles.css file which
 * is in public files.
 *
 * @param $path
 * @param $theme_name
 */
function at_load_responsive_css($path, $theme_name) {

  // Set the mode, when CSS is aggregated by Drupal Production mode is TRUE
  $mode = variable_get('preprocess_css', '') == 1 ? TRUE : FALSE;

  // Development Mode
  // These files are for "design style" only, the layout is handled
  // seperately.
  //
  // We only load these files if:
  // - 1: We're not in production mode
  // - 2: Responsiveness is not disabled
  //
  // When in production mode these files are aggregated into one file
  // and loaded using at_load_subtheme_responsive_styles().
  //
  // You can disable responsive capability using the theme settings - look under
  // the Global settings. Do not delete or alter this - use the theme setting!
  if ($mode == FALSE) {

    // Build a keyed array of CSS file-names as key, and media query as value.
    // The file names must match the files in your themes CSS directory, if
    // you change them you must update to match.
    $files = array(
      // Maintian backwards compatibility with older themes that use smartphone
      'responsive.smartphone.portrait'  => at_get_setting('smalltouch_portrait_media_query', $theme_name) ? at_get_setting('smalltouch_portrait_media_query', $theme_name) : at_get_setting('smartphone_portrait_media_query', $theme_name),
      'responsive.smartphone.landscape' => at_get_setting('smalltouch_landscape_media_query', $theme_name) ? at_get_setting('smalltouch_landscape_media_query', $theme_name) : at_get_setting('smartphone_landscape_media_query', $theme_name),
      // Standard files for the 7.x-3.2 and beyond
      'responsive.smalltouch.portrait'  => at_get_setting('smalltouch_portrait_media_query', $theme_name),
      'responsive.smalltouch.landscape' => at_get_setting('smalltouch_landscape_media_query', $theme_name),
      'responsive.tablet.portrait'      => at_get_setting('tablet_portrait_media_query', $theme_name),
      'responsive.tablet.landscape'     => at_get_setting('tablet_landscape_media_query', $theme_name),
      'responsive.desktop'              => at_get_setting('bigscreen_media_query', $theme_name),
    );

    // Add the custom responsive stylesheet if enabled
    if (at_get_setting('enable_custom_media_queries', $theme_name) === 1) {
      $item = array('responsive.custom' => 'only screen');
      $files = array_merge($item, $files);
    }

    // Loop over the files array and load each CSS file.
    // at_load_subtheme_responsive_styles() takes three parameters:
    // - $css_file - the name of the css file
    // - $media_query - the media query from theme settings
    // - $theme_name - to generate the path-to-theme for drupal_add_css()
    foreach ($files as $key => $value) {
      $filepath = drupal_get_path('theme', $theme_name) . '/css/' . $key . '.css';
      $media_query = $value;
      at_load_subtheme_responsive_styles($filepath, $media_query, $theme_name, $weight = 100);
    }
  }

  // Production Mode
  // In Production mode we only load one file for our design styles.
  // We use a media query to prevent non media query browsers from downloading it.
  // The embedded media queries in this file take precedence always.
  elseif ($mode == TRUE) {
    $filepath = $path . '/' . $theme_name . '.responsive.styles.css';
    $media_query = 'only screen'; // keyword "only" should hide this from older user agents
    at_load_subtheme_responsive_styles($filepath, $media_query, $theme_name, $weight = 100);
  }
}

/**
 * Load Extension Settings CSS.
 *
 * @param $theme_name
 */
function at_load_extensions_css($theme_name) {
  global $path_to_at_core;
  $settings_css = array();
  // Heading settings
  if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
    $settings_css[] = 'at.settings.style.headings.css';
  }
  // Image alignment settings
  if (at_get_setting('enable_image_settings', $theme_name) === 1) {
    $settings_css[] = 'at.settings.style.image.css';
  }
  // Float block settings
  if (at_get_setting('enable_float_region_blocks', $theme_name) === 1) {
    $settings_css[] = 'at.settings.style.floatblocks.css';
  }
  // Login block settings
  if (at_get_setting('horizontal_login_block_enable', $theme_name) === 'on') {
    if (at_get_setting('horizontal_login_block', $theme_name) === 1) {
      $settings_css[] = 'at.settings.style.login.css';
   }
  }
  if (!empty($settings_css)) {
    foreach ($settings_css as $css_file) {
      $filepath = $path_to_at_core . '/css/' . $css_file;
      drupal_add_css($filepath, array(
        'preprocess' => TRUE,
        'group' => CSS_THEME,
        'media' => 'screen',
        'every_page' => TRUE,
        'weight' => -100,
        )
      );
    }
  }
  else {
    $settings_css = NULL;
  }
}

/**
 * Load Fonts
 *
 * @param $path
 * @param $theme_name
 */
function at_load_fonts($path, $theme_name) {
  // Google fonts
  $google_font_string = &drupal_static(__FUNCTION__, array());
  if (empty($google_font_string)) {
    $google_font_string = at_load_google_fonts($theme_name);
  }
  if (!empty($google_font_string)) {
    drupal_add_css($google_font_string, array(
      'group' => CSS_THEME,
      'type' => 'external',
      'weight' => -100,
      )
    );
  }
  // Load the fonts CSS from public files
  $filepath = $path . '/' . $theme_name . '.fonts.css';
  if (file_exists($filepath)) {
    drupal_add_css($filepath, array(
      'preprocess' => TRUE,
      'group' => CSS_THEME,
      'media' => 'screen',
      'every_page' => TRUE,
      )
    );
  }
  else {
    at_load_failure($filepath, $theme_name);
  }
}

/**
 * Load custom css file.
 *
 * @param $path
 * @param $theme_name
 */
function at_load_custom_css($path, $theme_name) {
  $filepath = $path . '/' . $theme_name . '.custom.css';
  if (file_exists($filepath)) {
    drupal_add_css($filepath, array(
      'preprocess' => TRUE,
      'group' => CSS_THEME,
      'weight' => 1000,
      'media' => 'screen',
      'every_page' => TRUE,
      )
    );
  }
  else {
    at_load_failure($filepath, $theme_name);
  }
}

/**
 * Load Polyfill Scripts
 * Conditional scripts are returned to the preprocess function - in AT Core that
 * means adaptivetheme_preprocess_html() and adaptivetheme_preprocess_maintenance_page().
 * There are two sources for conditional scripts - the subtheme info file and
 * AT Core itself can load html5.js and respond.js.
 * Unconditional scripts (those not printed within an IE conditioanl comment)
 * load directly via drupal_add_js in this function, while the conditional scripts
 * are returned as an array to preprocess, then rendered in process. This is done
 * to allow themers to manipulate the data structure in preprocess if they feel
 * the need to.
 *
 * @param $theme_name
 */
function at_load_polyfills($theme_name) {
  global $path_to_at_core;

  // Get the info file data
  $info = at_get_info($theme_name);

  // Build an array of polyfilling scripts
  $polyfills = &drupal_static('adaptivetheme_preprocess_html_polyfills_array');
  if (empty($polyfills)) {

    $theme_path = drupal_get_path('theme', $theme_name);
    $polyfills_array = array();

    // Info file loaded conditional scripts
    if (array_key_exists('ie_scripts', $info)) {
      foreach ($info['ie_scripts'] as $condition => $ie_scripts_path) {
        foreach ($ie_scripts_path as $key => $value) {
          $filepath = $theme_path . '/' . $value;
          $polyfills_array['ie'][$condition][] = at_theme_conditional_script($filepath);
        }
      }
    }

    // AT Core Conditional Scripts
    if (at_get_setting('load_html5js') === 1) {
      $polyfills_array['ie']['lt IE 9'][] = at_theme_conditional_script($path_to_at_core . '/scripts/html5.js');
    }
    if (at_get_setting('load_respondjs') === 1) {
      $polyfills_array['ie']['lt IE 9'][] = at_theme_conditional_script($path_to_at_core . '/scripts/respond.js');
    }

    // AT Core Un-conditional Scripts
    if (at_get_setting('load_scalefixjs') === 1) {
      $polyfills_array['all'][] = 'scripts/scalefix.js';
    }
    if (at_get_setting('load_onmediaqueryjs') === 1) {
      $polyfills_array['all'][] = 'scripts/onmediaquery.js';
    }
    if (at_get_setting('load_matchmediajs') === 1) {
      $polyfills_array['all'][] = 'scripts/matchMedia.js';
      $polyfills_array['all'][] = 'scripts/matchMedia.addListener.js';
    }

    // Load Polyfills
    if (!empty($polyfills_array)) {

      // Default query string for cache control finger printing
      $query_string = variable_get('css_js_query_string', '0');

      // "all" - no conditional comment needed, use drupal_add_js()
      if (isset($polyfills_array['all'])) {
        foreach ($polyfills_array['all'] as $script) {
          drupal_add_js($path_to_at_core . '/' . $script, array(
            'type' => 'file',
            'scope' => 'header',
            'group' => JS_THEME,
            'preprocess' => TRUE,
            'cache' => TRUE,
            )
          );
        }
      }

      // IE conditional scripts, we need some semblance of structered data...
      if (isset($polyfills_array['ie'])) {
        $polyfills = array();
        foreach ($polyfills_array['ie'] as $conditional_comment => $scripts) {
          $ie_script = array(
            '#type' => 'markup',
            '#markup' => implode("\n", $scripts),
            '#prefix' => "<!--[if " . $conditional_comment . "]>\n",
            '#suffix' => "\n<![endif]-->\n",
          );
          $polyfills[$conditional_comment] = $ie_script;
        }
      }
    }
    else {
      $polyfills = '';
    }
  }

  return $polyfills;
}


/**
 * Load debugging helper files.
 *
 * @param $theme_name
 */
function at_load_debuggers($theme_name) {
  global $path_to_at_core;

  // Do some debugging/development stuff
  if (at_get_setting('expose_regions', $theme_name) === 1) {
    drupal_add_css($path_to_at_core . '/css/debug-regions.css');
  }

  if (at_get_setting('load_all_panels', $theme_name) === 1) {
    drupal_add_css($path_to_at_core . '/css/debug-panels.css', array(
      'preprocess' => FALSE,
      'group' => CSS_THEME,
      'media' => 'screen',
      'every_page' => FALSE,
      'weight' => 2000,
      )
    );
  }

  // Load window size bookmarklet
  if (at_get_setting('show_window_size', $theme_name) === 1) {
    drupal_add_js($path_to_at_core . '/scripts/window-size.js', array(
      'type' => 'file',
      'scope' => 'footer',
      'group' => JS_THEME,
      'preprocess' => TRUE,
      'cache' => TRUE,
      )
    );
    drupal_add_css($path_to_at_core . '/css/debug-windowsize.css', array(
      'preprocess' => FALSE,
      'group' => CSS_THEME,
      'media' => 'screen',
      'every_page' => FALSE,
      'weight' => 2000,
      )
    );
  }
}

/**
 * Load Sub-theme Responsive Stylesheets.
 * Wrapper function for drupal_add_css() that takes advantage of Drupals's
 * CSS aggregation logic to trick Drupal into always loading responsive
 * stylesheets in link elements.
 *
 * This is almost always called from adaptivetheme_preprocess_html(), only in
 * a rare instance might this be called from a sub-theme (to load additional
 * responsive stylesheets).
 *
 * @param $filepath, path to the CSS file.
 * @param $media_query, the media query from theme settings.
 * @param $theme_name, the active theme.
 * @param $weight, optional.
 */
function at_load_subtheme_responsive_styles($filepath, $media_query, $theme_name, $weight = 0) {
  if (file_exists($filepath)) {
    drupal_add_css($filepath, array(
      'preprocess' => variable_get('preprocess_css', '') == 1 ? TRUE : FALSE,
      'group' => CSS_THEME,
      'media' => $media_query,
      'every_page' => TRUE,
      'weight' => $weight,
      )
    );
  }
}

/**
 * Build arrays of conditional styles to load
 * Sub-themes can declare conditional stylesheets in the info file, we need to
 * get this info file data and process it.
 *
 * @param $theme_name, the active theme.
 */
function at_load_subtheme_conditional_styles($theme_name) {
  $info = &drupal_static(__FUNCTION__, array());
  if (empty($info)) {
    // Get the info file data
    $info = at_get_info($theme_name);

    // General IE stylesheets from the info file
    if (array_key_exists('ie_stylesheets', $info)) {
      $ie_style = '';
      foreach ($info['ie_stylesheets'] as $media => $stylesheets) {
        // Set default value for media in case the themer forgets, all is an
        // "assumed" value and not printed in the output.
        if (is_numeric($media)) {
          $media = 'all';
        }
        foreach ($stylesheets as $condition => $file) {
          foreach($file as $ie_styles_path) {
            $ie_style['media'] = $media;
            $ie_style['condition'] = $condition;
            $ie_style['path'] = $ie_styles_path;
            $filepath = drupal_get_path('theme', $theme_name) . '/' . $ie_style['path'];
            at_load_conditional_styles($filepath, $ie_style, $theme_name);
          }
        }
      }
    }
  }
}

/**
 * Load Sub-theme IE Stylesheets.
 * Wrapper function for drupal_add_css() that makes use the 'browser' option
 * to load stylesheets for Internet Explorer.
 *
 * @param $filepath, path to the file.
 * @param $ie_style, an arry containing the media attribute value and the IE
 * conditional comment.
 * @param $theme_name, the active theme.
 * @param $weight, optional.
 */
function at_load_conditional_styles($filepath, $ie_style, $theme_name, $weight = 0) {
  if (file_exists($filepath)) {
    drupal_add_css($filepath, array(
      'group' => CSS_THEME,
      'browsers' => array(
        'IE' => $ie_style['condition'],
        '!IE' => FALSE,
      ),
      'media' => $ie_style['media'],
      'preprocess' => TRUE,
      'weight' => $weight,
      )
    );
  }
  else {
    at_load_failure($filepath, $theme_name);
  }
}

/**
 * Load scripts from the sub-theme
 * Wrapper function for drupal_add_js(). In the core theme this is only used to
 * load media_queries.js if the Responsive JavaScript plugin is enabled in theme
 * settings. You can call this in your subtheme.
 *
 * @param $filepath, path to the file.
 * @param $theme_name, the active theme.
 * @param $scope, header or footer.
 * @param $weight, optional.
 */
function at_load_subtheme_script($filepath, $theme_name, $scope, $weight = NULL) {
  $filepath = drupal_get_path('theme', $theme_name) . '/' . $filepath;
  if (file_exists($filepath)) {
    drupal_add_js($filepath, array(
      'type' => 'file',
      'scope' => $scope,
      'group' => JS_THEME,
      'weight' => $weight,
      'preprocess' => TRUE,
      'cache' => TRUE,
      )
    );
  }
}

/**
 * Return a themed script.
 * Since Drupal 7 does not (yet) support the 'browser' option in drupal_add_js()
 * Adaptivetheme provides a way to load scripts inside conditional comments.
 * This function wraps a file in script elements and returns a string.
 *
 * @param $filepath, path to the file.
 */
function at_theme_conditional_script($filepath) {
  $script = '';

  // We need the default query string for cache control finger printing
  $query_string = variable_get('css_js_query_string', '0');

  if (file_exists($filepath)) {
    $file = file_create_url($filepath);
    $script = '<script src="' . $file . '?' . $query_string . '"></script>';
  }

  return $script;
}

/**
 * Google Font loader.
 * Adaptivetheme can load websafe fonts, Google fonts, custom font stacks and
 * integrate with @font-your-face module. All can be configured in the "Fonts"
 * theme settings. Here we only need to load Google webfonts. Websafe and custom
 * fonts are stored in a generated CSS file (in public files) and
 * @font-your-face module takes care of loading its own fonts.
 *
 * @param $theme_name
 */
function at_load_google_fonts($theme_name) {
  $google_font_string = &drupal_static(__FUNCTION__, array());
  if (empty($google_font_string)) {

    $used_fonts = array();
    $font_elements = font_elements();
    $charsets = google_font_charsets();
    $styles = google_font_styles();
    $used_styles = array();
    $used_charsets = array();

    foreach ($font_elements as $key => $value) {
      $setting = $value['setting'];
      if (at_get_setting($setting . '_type', $theme_name) === 'gwf') {
        $used_settings[] = $setting . '_gwf';
        $font_name = at_get_setting($setting . '_gwf', $theme_name);
        $used_font = str_replace(' ', '+', $font_name);
        $used_fonts[] = $used_font;
      }
    }
    if (!empty($used_fonts)) {
      $used_fonts = array_unique($used_fonts);
      $google_fonts = implode('|', $used_fonts);

      foreach ($used_settings as $used_setting) {
        // Styles
        if (at_get_setting($used_setting . '_add_styles', $theme_name) === 1) {
          foreach ($styles as $styles_key => $styles_value) {
            if (at_get_setting($used_setting . '_add_styles_' . $styles_key, $theme_name)) {
              $used_styles[] = $styles_key;
            }
          }
        }
        // Charsets
        if (at_get_setting($used_setting . '_add_charsets', $theme_name) === 1) {
          foreach ($charsets as $charset_key => $charset_value) {
            if (at_get_setting($used_setting . '_add_charsets_' . $charset_key, $theme_name)) {
              $used_charsets[] = $charset_key;
            }
          }
        }
      }
      if (!empty($used_styles)) {
        $styles_array = array_unique($used_styles);
        $google_styles = ':' . implode(',', $styles_array);
      }
      else {
        $google_styles = '';
      }
      if (!empty($used_charsets)) {
        $charset_array = array_unique($used_charsets);
        $google_charsets = '&subset=' . implode(',', $charset_array);
      }
      else {
        $google_charsets = '';
      }

      // Build the final string
      $google_font_string = '//fonts.googleapis.com/css?family=' . $google_fonts . $google_styles . $google_charsets;
    }
  }

  return $google_font_string;
}

/**
 * Add js settings for the layout type and media query
 */
function at_load_layout_js_settings($theme_name) {
  $breakpoints = array(
    'bigscreen',
    'tablet_landscape',
    'tablet_portrait',
    'smalltouch_landscape',
    'smalltouch_portrait',
  );
  $cfg = array();
  foreach ($breakpoints as $breakpoint) {
    $layout = at_get_setting($breakpoint . '_layout', $theme_name);
    $media_query = at_get_setting($breakpoint . '_media_query', $theme_name);
    if ($layout) {
      $layout = str_replace('_', '-', $layout);
      $cfg[$theme_name]['layout_settings'][$breakpoint] = $layout;
    }
    if ($media_query) {
      check_plain($media_query);
      $cfg[$theme_name]['media_query_settings'][$breakpoint] = $media_query;
    }
  }
  drupal_add_js(array('adaptivetheme' => $cfg), 'setting');
}

/**
 * Return JS and CSS for the Menu Toggle for mobile.
 */
function at_load_menu_toggle($path, $theme_name) {
  // Add JS settings for each enabled option (breakpoint)
  $menu_toggle_settings = array(
    'menu_toggle_tablet_portrait',
    'menu_toggle_tablet_landscape',
  );
  $cfg = array();
  foreach ($menu_toggle_settings as $toggle_setting) {
    $setting = at_get_setting($toggle_setting, $theme_name);
    if ($setting == 1) {
      $cfg[$theme_name]['menu_toggle_settings'][$toggle_setting] = 'true';
    }
    else {
      $cfg[$theme_name]['menu_toggle_settings'][$toggle_setting] = 'false';
    }
  }
  drupal_add_js(array('adaptivetheme' => $cfg), 'setting');

  $path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

  // Load additional plugins
  drupal_add_js($path_to_at_core . '/scripts/outside-events.js', array(
    'type' => 'file',
    'scope' => 'header',
    'group' => JS_THEME,
    'weight'=> 999,
    'preprocess' => TRUE,
    'cache' => TRUE,
    )
  );

  // Load the JS file
  drupal_add_js($path_to_at_core . '/scripts/menu-toggle.js', array(
    'type' => 'file',
    'scope' => 'header',
    'group' => JS_THEME,
    'weight'=> 999,
    'preprocess' => TRUE,
    'cache' => TRUE,
    )
  );

  // Load the generated CSS
  $filepath = $path . '/' . $theme_name . '.menutoggle.css';
  if (file_exists($filepath)) {
    drupal_add_css($filepath, array(
      'preprocess' => TRUE,
      'group' => CSS_THEME,
      'media' => 'all',
      'every_page' => TRUE,
      'weight' => 99,
      )
    );
  }
}

//
// Functions to maintain 7.x-2.x backward compatibility,
// DO NOT use these for 7.x-3.x or greater.
// Note to self - do not namespace these, that will certainly break existing sites.
//
// Load sub-theme media queries, 7.x-2.x backward compatibility
function load_subtheme_media_queries($files, $theme_name) {
  $path_to_theme = drupal_get_path('theme', $theme_name);
  foreach ($files as $file) {
    $filepath = $path_to_theme . '/css/' . $file;
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
        'preprocess' => variable_get('preprocess_css', '') == 1 ? TRUE : FALSE,
        'group' => CSS_THEME,
        'media' => 'all',
        'every_page' => TRUE,
        'weight' => 99,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }
  }
}

// Load subtheme IE stylesheets, 7.x-2.x backward compatibility
function load_subtheme_ie_styles($files, $theme_name) {
  $path_to_theme = drupal_get_path('theme', $theme_name);
  foreach ($files as $key => $value) {
    $filepath = $path_to_theme . '/css/' . $value;
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
        'group' => CSS_THEME,
        'browsers' => array(
          'IE' => $key,
          '!IE' => FALSE,
        ),
        'media' => 'screen',
        'preprocess' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }
  }
}
