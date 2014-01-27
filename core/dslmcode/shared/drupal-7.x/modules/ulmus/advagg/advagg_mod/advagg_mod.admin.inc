<?php

/**
 * @file
 * Admin page callbacks for the advagg bundler module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function advagg_mod_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Modifications'));

  $form = array();
  $form['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS'),
  );
  $form['js']['advagg_mod_js_footer'] = array(
    '#type' => 'radios',
    '#title' => t('Move JS to the footer'),
    '#default_value' => variable_get('advagg_mod_js_footer', ADVAGG_MOD_JS_FOOTER),
    '#options' => array(
        0 => t('Disabled'),
        1 => t('All but JavaScript Libraries'),
        2 => t('All'),
      ),
    '#description' => t("If you have JavaScript inline in the body of your document, such as if you are displaying ads, you may need to keep Drupal JS Libraries in the head instead of moving them to the footer. This will keep all JS added with the JS_LIBRARY group in the head while still moving all other JavaScript to the footer."),
  );
  $form['js']['advagg_mod_js_preprocess'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable preprocess on all JS'),
    '#default_value' => variable_get('advagg_mod_js_preprocess', ADVAGG_MOD_JS_PREPROCESS),
  );
  $form['js']['advagg_mod_js_async_shim'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rewrite asynchronous script tags to inline, old-browser-compatible scripts.'),
    '#default_value' => variable_get('advagg_mod_js_async_shim', ADVAGG_MOD_JS_ASYNC_SHIM),
    '#description' => t('Rewrites all scripts in the page with an "async" attribute to an inline JavaScript loading the script asynchronously in an old browser compatible way. List of <a href="@link">supported browsers</a>. Once all commonly used browsers support the "async" attribute you can happily disable this checkbox.', array('@link' => 'http://caniuse.com/script-async')),
  );
  $form['js']['advagg_mod_js_defer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add the defer tag to all script tags'),
    '#default_value' => variable_get('advagg_mod_js_defer', ADVAGG_MOD_JS_DEFER),
    '#description' => t('This will most likely break javascript on different browsers; and/or on all browsers. Use with extreme caution.'),
  );
  $form['js']['advagg_mod_js_remove_unused'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove unused JavaScript tags if possible'),
    '#default_value' => variable_get('advagg_mod_js_remove_unused', ADVAGG_MOD_JS_REMOVE_UNUSED),
    '#description' => t('This is still experimental. Use with extreme caution. This will scan all included JS files for references to jquery and drupal. If none are found then the default JavaScript is removed from the page.'),
  );
  $form['js']['advagg_mod_js_adjust_sort_external'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all external scripts to the top of the execution order'),
    '#default_value' => variable_get('advagg_mod_js_adjust_sort_external', ADVAGG_MOD_JS_ADJUST_SORT_EXTERNAL),
    '#description' => t('This is experimental. This will group all external JavaScript files to be above all other JavaScript.'),
  );
  $form['js']['advagg_mod_js_adjust_sort_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all inline scripts to the bottom of the execution order'),
    '#default_value' => variable_get('advagg_mod_js_adjust_sort_inline', ADVAGG_MOD_JS_ADJUST_SORT_INLINE),
    '#description' => t('This is experimental. This will group all inline JavaScript to be below all other JavaScript.'),
  );
  $form['js']['advagg_mod_js_adjust_sort_browsers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all browser conditional JavaScript to the bottom of the group'),
    '#default_value' => variable_get('advagg_mod_js_adjust_sort_browsers', ADVAGG_MOD_JS_ADJUST_SORT_BROWSERS),
    '#description' => t('This is experimental. This will group all browser conditional JavaScript to be in the lowest group of that conditional rule.'),
  );

  $config_path = advagg_admin_config_root_path();
  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
  );
  $form['css']['advagg_mod_css_preprocess'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable preprocess on all CSS'),
    '#default_value' => variable_get('advagg_mod_css_preprocess', ADVAGG_MOD_CSS_PREPROCESS),
    '#description' => module_exists('advagg_bundler') ? t('You might want to increase the <a href="@link">CSS Bundles Per Page</a> if this is checked.', array('@link' => url($config_path . '/advagg/bundler'))) : t(''),
  );
  // Only test the translate option if
  //  the locale function is defined OR
  //  the locale_custom_strings variable is not empty.
  $locale_custom_strings = variable_get('locale_custom_strings_' . isset($GLOBALS['language']->language) ? $GLOBALS['language']->language : 'en', array());
  if (function_exists('locale') || !empty($locale_custom_strings)) {
    // Only show option if something comes back translated.
    $files = advagg_mod_admin_test_css_files('css');
    if (!empty($files)) {
      $form['css']['advagg_mod_css_translate'] = array(
        '#type' => 'checkbox',
        '#title' => t('Translate CSS content strings'),
        '#default_value' => variable_get('advagg_mod_css_translate', ADVAGG_MOD_CSS_TRANSLATE),
        '#description' => t('Run strings inside of quotes of the content attribute through the <a href="@t">t() function</a>. An alternative to this can be found in this <a href="@post">blog post</a>.', array(
          '@t' => 'https://api.drupal.org/api/drupal/includes!bootstrap.inc/function/t/7',
          '@post' => 'http://fourkitchens.com/blog/2013/08/15/multilingual-css-generated-content-drupal',
        )),
      );
    }
  }
  $form['css']['advagg_mod_css_adjust_sort_external'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all external CSS to the top of the execution order'),
    '#default_value' => variable_get('advagg_mod_css_adjust_sort_external', ADVAGG_MOD_CSS_ADJUST_SORT_EXTERNAL),
    '#description' => t('This is experimental. This will group all external CSS files to be above all other CSS.'),
  );
  $form['css']['advagg_mod_css_adjust_sort_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all inline CSS to the bottom of the execution order'),
    '#default_value' => variable_get('advagg_mod_css_adjust_sort_inline', ADVAGG_MOD_CSS_ADJUST_SORT_INLINE),
    '#description' => t('This is experimental. This will group all inline CSS to be below all other CSS.'),
  );
  $form['css']['advagg_mod_css_adjust_sort_browsers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all browser conditional CSS to the bottom of the group'),
    '#default_value' => variable_get('advagg_mod_css_adjust_sort_browsers', ADVAGG_MOD_CSS_ADJUST_SORT_BROWSERS),
    '#description' => t('This is experimental. This will group all browser conditional CSS to be in the lowest group of that conditional rule.'),
  );

  $form['landing_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inline CSS/JS on specific pages'),
  );
  // Taken from block_admin_configure().
  $access = user_access('use PHP for settings');
  $visibility = variable_get('advagg_mod_inline_visibility', BLOCK_VISIBILITY_LISTED);
  $pages = variable_get('advagg_mod_inline_pages', '');
  if ($visibility == BLOCK_VISIBILITY_PHP && !$access) {
    $form['landing_page']['path']['visibility'] = array(
      '#type' => 'value',
      '#value' => $visibility,
    );
    $form['landing_page']['path']['pages'] = array(
      '#type' => 'value',
      '#value' => $pages,
    );
  }
  else {
    $options = array(
//       BLOCK_VISIBILITY_NOTLISTED => t('All pages except those listed'),
      BLOCK_VISIBILITY_LISTED => t('Only the listed pages'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

    if (module_exists('php') && $access) {
      $options += array(BLOCK_VISIBILITY_PHP => t('Pages on which this PHP code returns <code>TRUE</code> (experts only)'));
      $title = t('Pages or PHP code');
      $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    else {
      $title = t('Pages');
    }
    $form['landing_page']['path']['advagg_mod_inline_settings'] = array(
      '#type' => 'radios',
      '#title' => t('Inline CSS/JS on specific pages'),
      '#options' => $options,
      '#default_value' => $visibility,
    );
    $form['landing_page']['path']['advagg_mod_inline_pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $pages,
      '#description' => $description,
    );
  }

  $form['unified_multisite'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unified Multisite'),
  );
  $form['unified_multisite']['advagg_mod_unified_multisite_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Shared Directory'),
    '#default_value' => variable_get('advagg_mod_unified_multisite_dir', ''),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('This allows you to have a shared directory for all CSS/JS aggregates if this install of drupal is used as a <a href="@multisite">multisite</a>. If this servers multisites share a similar CSS/JS structure then a lot of resources can be saved by not rebuilding the same aggregates in each site of the multisite. Make sure that you use the same directory and advagg settings in each multisite for this setting to work efficiently. Current <a href="@info">hash value</a> of settings on this site: %value. If this value is different across the servers multisites then this will not save server resources as a different file will be built due to AdvAgg having different settings. Note that $base_path is used in the hash value so in some multisite cases it will be impossible to use this setting.', array(
      '@multisite' => 'https://drupal.org/documentation/install/multi-site',
      '@info' => url($config_path . '/advagg/info'),
      '%value' => advagg_get_current_hooks_hash(),
    )),
  );

  // Make sure the multisite_dir is writable.
  $form['#validate'][] = 'advagg_mod_admin_settings_form_validate';

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_mod_admin_settings_form_submit';

  return system_settings_form($form);
}

// Validate callback.
/**
 * Make sure the unified multisite directory was created correctly.
 */
function advagg_mod_admin_settings_form_validate($form, &$form_state) {
  $multisite_dir = rtrim($form_state['values']['advagg_mod_unified_multisite_dir'], '/');
  // Return if unified_multisite_dir is not set.
  if (empty($multisite_dir)) {
    return;
  }

  // Prepare directory.
  $css_dir = $multisite_dir . '/advagg_css';
  $js_dir = $multisite_dir . '/advagg_js';
  if (   !file_prepare_directory($css_dir, FILE_CREATE_DIRECTORY)
      || !file_prepare_directory($js_dir, FILE_CREATE_DIRECTORY)
        ) {
    if (!is_dir($multisite_dir) || !is_writable($multisite_dir)) {
      form_set_error('advagg_mod_unified_multisite_dir', t('%dir is not a directory or can not be written to. The shared directory needs to have the same permissions as the "Public file system path" found on the <a href="@file_system_link">File System configuration page</a>.', array(
        '%dir' => $multisite_dir,
        '@file_system_link' => url('admin/config/media/file-system'),
      )));
      return;
    }
  }
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 */
function advagg_mod_admin_settings_form_submit($form, &$form_state) {
  $cache_bins = advagg_flush_caches();
  foreach ($cache_bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
  }

  // If unified_multisite_dir has changed, flush menu router at the end of the
  // request.
  $multisite_dir = rtrim($form_state['values']['advagg_mod_unified_multisite_dir'], '/');
  $dir = rtrim(variable_get('advagg_mod_unified_multisite_dir', ''), '/');
  if ($multisite_dir != $dir) {
    register_shutdown_function('advagg_get_root_files_dir', TRUE);
    register_shutdown_function('menu_rebuild');
  }
}

/**
 * Test all CSS files seeing if any string translations do anything.
 *
 * @return
 *   An array with the filename key and the before => after translation value.
 */
function advagg_mod_admin_test_css_files() {
  $output = array();
  // Get list of files.
  $query_files = db_select('advagg_files', 'af')
    ->fields('af', array('filename_hash', 'filename'))
    ->condition('af.filetype', 'css')
    ->orderBy('filename', 'DESC')
    ->execute()
    ->fetchAllKeyed();
  $files = array_values($query_files);
  // Exit if no files were found.
  if (empty($files)) {
    return $output;
  }

  foreach ($files as $filename) {
    // Skip missing files.
    if (!file_exists($filename)) {
      continue;
    }
    // Load CSS file.
    $file_contents = drupal_load_stylesheet_content(file_get_contents($filename), TRUE);

    // Code taken from drupal_load_stylesheet_content().
    // Regexp to match double quoted strings.
    $double_quot = '"[^"\\\\]*(?:\\\\.[^"\\\\]*)*"';
    // Regexp to match single quoted strings.
    $single_quot = "'[^'\\\\]*(?:\\\\.[^'\\\\]*)*'";
    // Extract all content inside of quotes.
    $css_content_pattern = "/content:.*?($double_quot|$single_quot|(\\;|\\})).*?(?:\\;|\\})/";

    // Get strings inside of quotes of the content attribute.
    preg_match_all($css_content_pattern, $file_contents, $matches);
    // Skip if no matches.
    if (empty($matches[1])) {
      continue;
    }

    foreach ($matches[1] as $value) {
      // Skip if equal to ; or }.
      if ($value == ';' || $value = '}') {
        continue;
      }
      // Remove quotes for t function.
      $before = substr($value, 1, -1);
      // Only test if it contains A-Za-z.
      if (!preg_match('/[A-Za-z]/', $before)) {
        continue;
      }
      // Only test if it contains characters other than unicode.
      $css_unicode_pattern = '/\\\\[0-9a-fA-F]{1,6}(?:\\r\\n|[ \\t\\r\\n\\f])?/';
      $unicode_removed = preg_replace($css_unicode_pattern, '', $before);
      if (empty($unicode_removed)) {
        continue;
      }
      // Run t function.
      $after = t($before);

      // Only include it if strings are different.
      if ($before !== $after) {
        if (!isset($output[$filename])) {
          $output[$filename] = '';
        }
        $output[$filename] .= $before . ' => ' . $after;
      }
    }
  }
  return $output;
}
