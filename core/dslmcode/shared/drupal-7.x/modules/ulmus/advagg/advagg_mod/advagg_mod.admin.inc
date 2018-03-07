<?php

/**
 * @file
 * Admin page callbacks for the advagg bundler module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_mod_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Modifications'));
  advagg_display_message_if_requirements_not_met();
  $config_path = advagg_admin_config_root_path();
  $form = array();

  $options = array(
    0 => t('Use default (safe) settings'),
    2 => t('Use recommended (optimized) settings'),
    4 => t('Use customized settings'),
  );
  $form['advagg_mod_admin_mode'] = array(
    '#type' => 'radios',
    '#title' => t('AdvAgg Settings'),
    '#default_value' => variable_get('advagg_mod_admin_mode', ADVAGG_MOD_ADMIN_MODE),
    '#options' => $options,
    '#description' => t("Default settings will mirror core as closely as possible. <br>Recommended settings are optimized for speed."),
  );
  $form['global_container'] = array(
    '#type' => 'container',
    '#hidden' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="advagg_mod_admin_mode"]' => array('value' => '4'),
      ),
    ),
  );

  // Tell user to update library if a new version is available.
  $library_name = 'loadCSS';
  $module_name = 'advagg_mod';
  list($description) = advagg_get_version_description($library_name, $module_name);
  if (!empty($description)) {
    $form['global_container']['advagg_version_msg'] = array(
      '#markup' => "<p>{$description}</p>",
    );
  }
  $form['global_container']['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS'),
  );
  $form['global_container']['js']['advagg_mod_js_preprocess'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable preprocess on all JS (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_preprocess', ADVAGG_MOD_JS_PREPROCESS),
    '#description' => t('Force all JavaScript to have the preprocess attribute be set to TRUE. All JavaScript files will be aggregated if enabled.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['advagg_mod_js_remove_unused'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove unused JavaScript if possible'),
    '#default_value' => variable_get('advagg_mod_js_remove_unused', ADVAGG_MOD_JS_REMOVE_UNUSED),
    '#description' => t('This will scan all included JS files for references to jquery and drupal. If none are found then the core JavaScript (jquery.js, drupal.js, Drupal.settings) is removed and not loaded on that page. If you have a site that does not use a lot of Javascript this might be helpful as it could prevent unused JavaScript from being executed, thus speeding up your sites frontend performance. Enabling this usually has negative backend performance impact.'),
  );
  $form['global_container']['js']['advagg_mod_js_no_ajaxpagestate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove ajaxPageState CSS and JS data if ajax.js is not used on this page (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_no_ajaxpagestate', ADVAGG_MOD_JS_NO_AJAXPAGESTATE),
    '#description' => t('This assumes that the only thing that uses Drupal.settings.ajaxPageState.css and Drupal.settings.ajaxPageState.js is ajax.js.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['advagg_mod_js_inline_resource_hints'] = array(
    '#type' => 'checkbox',
    '#title' => t('Resource hint src attributes found in the HTML content (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_inline_resource_hints', ADVAGG_MOD_JS_INLINE_RESOURCE_HINTS),
    '#description' => t('Scan any JavaScript that was added to the content part of the page incorrectly for a src attribute; if found use the advagg <a href="@url">resource hints settings</a> for faster loading.', array('@url' => url($config_path . '/advagg', array('fragment' => 'edit-resource-hints')))),
    '#disabled' => !variable_get('advagg_resource_hints_dns_prefetch', ADVAGG_RESOURCE_HINTS_DNS_PREFETCH) && !variable_get('advagg_resource_hints_preconnect', ADVAGG_RESOURCE_HINTS_PRECONNECT) && !variable_get('advagg_resource_hints_preload', ADVAGG_RESOURCE_HINTS_PRELOAD),
    '#recommended_value' => TRUE,
  );
  if ($form['global_container']['js']['advagg_mod_js_inline_resource_hints']['#disabled']) {
    $form['global_container']['js']['advagg_mod_js_inline_resource_hints']['#description'] .= ' ' . t('Currently disabled; to enable check the desired checkboxes under Resource Hints on the <a href="@url">configuration page</a>', array('@url' => url($config_path . '/advagg', array('fragment' => 'edit-resource-hints'))));
  }
  // Optimize JavaScript Ordering.
  $form['global_container']['js']['adjust_sort'] = array(
    '#type' => 'fieldset',
    '#title' => t('Optimize JavaScript Ordering'),
    '#description' => t('The settings in here might change the order in which the JavaScript is loaded. It will move the scripts around so that more optimal aggregates are built. In most cases enabling these checkboxes will cause no negative side effects.'),
  );
  $form['global_container']['js']['adjust_sort']['advagg_mod_js_head_extract'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move JavaScript added by drupal_add_html_head() into drupal_add_js() (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_head_extract', ADVAGG_MOD_JS_HEAD_EXTRACT),
    '#description' => t('This will move JavaScript added incorrectly to Drupal into the top of the drupal_add_js() queue.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['adjust_sort']['advagg_mod_js_adjust_sort_external'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all external scripts to the top of the execution order (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_adjust_sort_external', ADVAGG_MOD_JS_ADJUST_SORT_EXTERNAL),
    '#description' => t('This will group all external JavaScript files to be above all other JavaScript.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['adjust_sort']['advagg_mod_js_adjust_sort_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all inline scripts to the bottom of the execution order (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_adjust_sort_inline', ADVAGG_MOD_JS_ADJUST_SORT_INLINE),
    '#description' => t('This will group all inline JavaScript to be below all other JavaScript.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['adjust_sort']['advagg_mod_js_adjust_sort_browsers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all browser conditional JavaScript to the bottom of the group (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_adjust_sort_browsers', ADVAGG_MOD_JS_ADJUST_SORT_BROWSERS),
    '#description' => t('This will group all browser conditional JavaScript to be in the lowest group of that conditional rule.'),
    '#recommended_value' => TRUE,
  );
  if (module_exists('googleanalytics')
    && is_callable('googleanalytics_api')
    && is_callable('_googleanalytics_cache')
  ) {
    $form['global_container']['js']['adjust_sort']['expert'] = array(
      '#type' => 'fieldset',
      '#title' => t('Experimental Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => !variable_get('advagg_mod_ga_inline_to_file', ADVAGG_MOD_GA_INLINE_TO_FILE),
    );
    $form['global_container']['js']['adjust_sort']['expert']['advagg_mod_ga_inline_to_file'] = array(
      '#type' => 'checkbox',
      '#title' => t('Move Google Analytics analytics.js code from inline to be a file'),
      '#default_value' => variable_get('advagg_mod_ga_inline_to_file', ADVAGG_MOD_GA_INLINE_TO_FILE),
      '#description' => t('The AdvAgg Relocate module is more capable. Recommend using it if you are using this functionality. This setting will soon be deprecated.'),
    );
    $form['global_container']['js']['adjust_sort']['expert']['advagg_mod_prefetch'] = array(
      '#type' => 'checkbox',
      '#title' => t('Prefetch stats.g.doubleclick.net/robots.txt'),
      '#default_value' => variable_get('advagg_mod_prefetch', ADVAGG_MOD_PREFETCH),
      '#description' => t('Opens a connection to stats.g.doubleclick.net in order to speed up the round trip time. If the browser supports preconnect and under Resource Hints on the <a href="@url">configuration page</a>, preconnect is enabled (currently %state), then it will use preconnect instead of this robots.txt hack.', array(
        '@url' => url($config_path . '/advagg', array('fragment' => 'edit-resource-hints')),
        '%state' => variable_get('advagg_resource_hints_preconnect', ADVAGG_RESOURCE_HINTS_PRECONNECT) ? t('enabled') : t('disabled'),
      )),
    );
  }

  // Adjust javascript location and execution.
  $form['global_container']['js']['placement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Adjust javascript location and execution'),
    '#description' => t('Most of the time adjusting the settings are safe but in some rare cases adjusting these can cause serious JavaScript issues with your site.'),
  );
  $form['global_container']['js']['placement']['advagg_mod_js_footer'] = array(
    '#type' => 'radios',
    '#title' => t('Move JS to the footer'),
    '#default_value' => variable_get('advagg_mod_js_footer', ADVAGG_MOD_JS_FOOTER),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('All but JavaScript Libraries'),
      3 => t('All but what is in the $all_in_footer_list (recommended)'),
      2 => t('All (might break things)'),
    ),
    '#description' => t("If you have JavaScript inline in the body of your document, such as if you are displaying ads, you may need to keep Drupal JS Libraries in the head instead of moving them to the footer. This will keep all JS added with the JS_LIBRARY group in the head while still moving all other JavaScript to the footer."),
    '#recommended_value' => 3,
  );
  $form['global_container']['js']['placement']['advagg_mod_js_defer'] = array(
    '#type' => 'radios',
    '#title' => t('Deferred JavaScript Execution: Add The defer Tag To All Script Tags'),
    '#default_value' => variable_get('advagg_mod_js_defer', ADVAGG_MOD_JS_DEFER),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('All but external scripts (recommended)'),
      1 => t('All (might break things)'),
    ),
    '#description' => t('This will delay the script execution until the HTML parser has finished. This will have a similar effect to moving all JavaScript to the footer. This might break javascript (especially inline); only use after extensive testing! <a href="@link">More Info</a>', array(
      '@link' => 'http://peter.sh/experiments/asynchronous-and-deferred-javascript-execution-explained/',
    )),
    '#recommended_value' => 2,
  );
  $form['global_container']['js']['placement']['advagg_mod_js_async_in_header'] = array(
    '#type' => 'checkbox',
    '#title' => t('Asynchronous JavaScript Execution: Group together in the header (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_async_in_header', ADVAGG_MOD_JS_ASYNC_IN_HEADER),
    '#description' => t('This will move all async JavaScript code to the header in the same group.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['placement']['advagg_mod_js_footer_inline_alter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Put a wrapper around inline JS if it was added in the content section incorrectly (recommended)'),
    '#default_value' => variable_get('advagg_mod_js_footer_inline_alter', ADVAGG_MOD_JS_FOOTER_INLINE_ALTER),
    '#description' => t('This will put a wrapper around any inline JavaScript that was added to the content part of the page incorrectly. The wrapper will check every 250ms until window.Drupal.settings and window.jQuery are defined; at that point the inlined code will then run.'),
    '#recommended_value' => TRUE,
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_mod_js_footer"]' => array('value' => '0'),
        ':input[name="advagg_mod_js_defer"]' => array('value' => '0'),
        ':input[name="advagg_mod_js_async"]' => array('checked' => FALSE),
      ),
    ),
  );
  $advagg_mod_wrap_inline_js_skip_list = trim(variable_get('advagg_mod_wrap_inline_js_skip_list', ADVAGG_MOD_WRAP_INLINE_JS_SKIP_LIST));
  $advagg_mod_wrap_inline_js_xpath = variable_get('advagg_mod_wrap_inline_js_xpath', ADVAGG_MOD_WRAP_INLINE_JS_XPATH);
  $form['global_container']['js']['placement']['advagg_mod_wrap_inline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inline Wrapper Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($advagg_mod_wrap_inline_js_skip_list) && empty($advagg_mod_wrap_inline_js_xpath),
    '#states' => array(
      'visible' => array(
        ':input[name="advagg_mod_js_footer_inline_alter"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['global_container']['js']['placement']['advagg_mod_wrap_inline']['advagg_mod_wrap_inline_js_skip_list'] = array(
    '#type' => 'textarea',
    '#title' => t('Inline skip list for wrapper code'),
    '#default_value' => variable_get('advagg_mod_wrap_inline_js_skip_list', ADVAGG_MOD_WRAP_INLINE_JS_SKIP_LIST),
    '#description' => t("If the inline JavaScript matches a given string then the whole inline script will not be wrapped. Enter one per line. Useful for things like conversion.js from the Google tracking code, as this is not async friendly (conversion.js needs global variables that were previously defined). In that case enter <code>@code</code> or equivalent above, where you replace %replace with the actual ID. Ideally you'd want to fix the code by using <a href='@url'>async friendly JS</a> but this is not always possible with 3rd party code.", array(
      '@code' => 'var google_conversion_id = XXX;',
      '%replace' => 'XXX',
      '@url' => 'https://developers.google.com/adwords-remarketing-tag/asynchronous/',
    )),
  );
  $form['global_container']['js']['placement']['advagg_mod_wrap_inline']['advagg_mod_wrap_inline_js_xpath'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use XPath instead of regex when searching for inline scripts'),
    '#default_value' => variable_get('advagg_mod_wrap_inline_js_xpath', ADVAGG_MOD_WRAP_INLINE_JS_XPATH),
    '#description' => t('In general this should be disabled due to the unpredictable nature of parsing html snippets using DOMDocument loadHTML(). Only enable if you have script tags inside a textarea that have not been ran through htmlentities().'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['placement']['advagg_mod_js_defer_inline_alter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Deferred inline JavaScript Execution: Put a wrapper around inline JS so it runs from a setTimeout call (recommended).'),
    '#default_value' => variable_get('advagg_mod_js_defer_inline_alter', ADVAGG_MOD_JS_DEFER_INLINE_ALTER),
    '#description' => t('This will put a wrapper around any inline JavaScript.'),
    '#recommended_value' => TRUE,
  );
  $advagg_mod_defer_inline_js_skip_list = trim(variable_get('advagg_mod_defer_inline_js_skip_list', ADVAGG_MOD_DEFER_INLINE_JS_SKIP_LIST));
  $form['global_container']['js']['placement']['advagg_mod_defer_inline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Deferred Inline Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($advagg_mod_defer_inline_js_skip_list),
    '#states' => array(
      'visible' => array(
        ':input[name="advagg_mod_js_defer_inline_alter"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['global_container']['js']['placement']['advagg_mod_defer_inline']['advagg_mod_defer_inline_js_skip_list'] = array(
    '#type' => 'textarea',
    '#title' => t('Inline skip list for wrapper code'),
    '#default_value' => variable_get('advagg_mod_defer_inline_js_skip_list', ADVAGG_MOD_DEFER_INLINE_JS_SKIP_LIST),
    '#description' => t("If the inline JavaScript matches a given string then the whole inline script will not be wrapped. Enter one per line."),
  );
  $form['global_container']['js']['placement']['expert'] = array(
    '#type' => 'fieldset',
    '#title' => t('Experimental Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => !variable_get('advagg_mod_js_async', ADVAGG_MOD_JS_ASYNC),
  );
  $form['global_container']['js']['placement']['expert']['advagg_mod_js_async'] = array(
    '#type' => 'checkbox',
    '#title' => t('Here there be dragons! Asynchronous JavaScript Execution: Add The async Tag To All Script Tags'),
    '#default_value' => variable_get('advagg_mod_js_async', ADVAGG_MOD_JS_ASYNC),
    '#description' => t('This will cause the script to be downloaded in the background and executed out of order. This will break most javascript as most code is not async safe; only use after extensive testing! <a href="@link">More Info</a>', array(
      '@link' => 'http://peter.sh/experiments/asynchronous-and-deferred-javascript-execution-explained/',
    )),
  );
  // Outdated settings.
  $form['global_container']['js']['old'] = array(
    '#type' => 'fieldset',
    '#title' => t('Outdated settings that should not be used'),
    '#collapsible' => TRUE,
    '#collapsed' => !variable_get('advagg_mod_js_async_shim', ADVAGG_MOD_JS_ASYNC_SHIM),
  );
  $form['global_container']['js']['old']['advagg_mod_js_async_shim'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rewrite asynchronous script tags to inline, old-browser-compatible scripts.'),
    '#default_value' => variable_get('advagg_mod_js_async_shim', ADVAGG_MOD_JS_ASYNC_SHIM),
    '#description' => t('Rewrites all scripts in the page with an "async" attribute to an inline JavaScript loading the script asynchronously in an old browser compatible way. List of <a href="@link">supported browsers</a>. Once all commonly used browsers support the "async" attribute you can happily disable this checkbox.', array('@link' => 'http://caniuse.com/script-async')),
  );

  $form['global_container']['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
  );
  $form['global_container']['css']['advagg_mod_css_preprocess'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable preprocess on all CSS (recommended)'),
    '#default_value' => variable_get('advagg_mod_css_preprocess', ADVAGG_MOD_CSS_PREPROCESS),
    '#description' => t('Force all CSS to have the preprocess attribute be set to TRUE. All CSS files will be aggregated if enabled.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['css']['advagg_mod_css_preprocess']['#description'] .= module_exists('advagg_bundler') ? ' ' . t('You might want to increase the <a href="@link">CSS Bundles Per Page</a> if this is checked.', array('@link' => url($config_path . '/advagg/bundler'))) : '';
  if (is_callable('omega_extension_enabled')
    && is_callable('omega_theme_get_setting')
    && omega_extension_enabled('development')
    && omega_theme_get_setting('omega_livereload', TRUE)
  ) {
    $form['global_container']['css']['advagg_mod_css_preprocess']['#description'] .= ' ' . t('The omega theme is in development mode and livereload is also enabled. This setting combination disables CSS aggregation. If you wish to have CSS aggregation turned on, go to the <a href="@url">theme settings page</a>, select the Omega theme/subtheme and turn off LiveReload and/or turn off the Development extension.', array('@url' => url('admin/appearance/settings')));
  }
  // Only test the translate option if
  // the locale function is defined OR
  // the locale_custom_strings variable is not empty.
  $locale_custom_strings = variable_get('locale_custom_strings_' . isset($GLOBALS['language']->language) ? $GLOBALS['language']->language : 'en', array());
  if (function_exists('locale') || !empty($locale_custom_strings)) {
    // Only show option if something comes back translated.
    $files = advagg_mod_admin_test_css_files('css');
    if (!empty($files)) {
      $form['global_container']['css']['advagg_mod_css_translate'] = array(
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
  // Optimize CSS Ordering.
  $form['global_container']['css']['adjust_sort'] = array(
    '#type' => 'fieldset',
    '#title' => t('Optimize CSS Ordering'),
    '#description' => t('The settings in here might change the order in which the CSS is loaded. It will move the CSS around so that more optimal aggregates are built. In most cases enabling these checkboxes will cause no negative side effects.'),
  );
  $form['global_container']['css']['adjust_sort']['advagg_mod_css_head_extract'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move CSS added by drupal_add_html_head() into drupal_add_css() (recommended)'),
    '#default_value' => variable_get('advagg_mod_css_head_extract', ADVAGG_MOD_CSS_HEAD_EXTRACT),
    '#description' => t('This will move CSS added incorrectly to Drupal into the top of the drupal_add_css() queue.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['css']['adjust_sort']['advagg_mod_css_adjust_sort_external'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all external CSS to the top of the execution order (recommended)'),
    '#default_value' => variable_get('advagg_mod_css_adjust_sort_external', ADVAGG_MOD_CSS_ADJUST_SORT_EXTERNAL),
    '#description' => t('This will group all external CSS files to be above all other CSS.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['css']['adjust_sort']['advagg_mod_css_adjust_sort_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all inline CSS to the bottom of the execution order (recommended)'),
    '#default_value' => variable_get('advagg_mod_css_adjust_sort_inline', ADVAGG_MOD_CSS_ADJUST_SORT_INLINE),
    '#description' => t('This will group all inline CSS to be below all other CSS.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['css']['adjust_sort']['advagg_mod_css_adjust_sort_browsers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move all browser conditional CSS to the bottom of the group (recommended)'),
    '#default_value' => variable_get('advagg_mod_css_adjust_sort_browsers', ADVAGG_MOD_CSS_ADJUST_SORT_BROWSERS),
    '#description' => t('This will group all browser conditional CSS to be in the lowest group of that conditional rule.'),
    '#recommended_value' => TRUE,
  );
  // Adjust CSS location and execution.
  $form['global_container']['css']['placement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Adjust CSS location and execution'),
    '#collapsible' => TRUE,
    '#collapsed' => !variable_get('advagg_mod_css_defer', ADVAGG_MOD_CSS_DEFER),
  );
  $form['global_container']['css']['placement']['advagg_mod_css_defer'] = array(
    '#type' => 'radios',
    '#title' => t('Deferred CSS Execution: Use JS to load CSS'),
    '#default_value' => variable_get('advagg_mod_css_defer', ADVAGG_MOD_CSS_DEFER),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('All in head, above js'),
      3 => t('All in head'),
      4 => t('All in head, use link rel="preload" (recommended)'),
      5 => t('All in footer except for JS loading code'),
      7 => t('All in footer'),
    ),
    '#description' => t('This will try to optimize CSS delivery by using JavaScript to load the CSS. This might break CSS on different browsers and will cause a flash of unstyled content (FOUC). Only enable after extensive testing! <a href="@link">More Info</a>', array(
      '@link' => 'http://stackoverflow.com/questions/19374843/css-delivery-optimization-how-to-defer-css-loading',
    )),
    '#recommended_value' => 4,
  );
  // Taken from block_admin_configure().
  $access = user_access('use PHP for settings');
  $css_defer_pages = variable_get('advagg_mod_css_defer_pages', '');
  $visibility_defer = variable_get('advagg_mod_css_defer_visibility', ADVAGG_MOD_VISIBILITY_LISTED);
  $options = array(
    ADVAGG_MOD_VISIBILITY_NOTLISTED => t('All pages except those listed (blacklist)'),
    ADVAGG_MOD_VISIBILITY_LISTED => t('Only the listed pages (whitelist)'),
  );
  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
    '%blog' => 'blog',
    '%blog-wildcard' => 'blog/*',
    '%front' => '<front>',
  ));

  if (module_exists('php') && $access) {
    $options += array(ADVAGG_MOD_VISIBILITY_PHP => t('Pages on which this PHP code returns <code>TRUE</code> (experts only)'));
    $title = t('Pages or PHP code');
    $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
  }
  else {
    $title = t('Pages');
  }
  $options += array(ADVAGG_MOD_VISIBILITY_FILE_CONTROLLED => t('File Controlled (Recommended).'));

  if ($visibility_defer == ADVAGG_MOD_VISIBILITY_PHP && !$access) {
    $form['global_container']['css']['placement']['visibility_all'] = array(
      '#type' => 'value',
      '#value' => $visibility_defer,
    );
    $form['global_container']['css']['placement']['pages_all'] = array(
      '#type' => 'value',
      '#value' => $css_defer_pages,
    );
  }
  else {
    $form['global_container']['css']['placement']['advagg_mod_css_defer_visibility'] = array(
      '#type' => 'radios',
      '#title' => t('Defer CSS only on specific pages'),
      '#options' => $options,
      '#default_value' => $visibility_defer,
      '#description' => t('Apply the above CSS setting only on specific pages. On other pages it will act as being Disabled. File Controlled will only use loadCSS() if a critical css file has been found and can be inlined.'),
      '#states' => array(
        'disabled' => array(
          ':input[name="advagg_mod_css_defer"]' => array('value' => '0'),
        ),
      ),
      '#recommended_value' => ADVAGG_MOD_VISIBILITY_FILE_CONTROLLED,
    );
    $form['global_container']['css']['placement']['advagg_mod_css_defer_pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $css_defer_pages,
      '#description' => $description,
      '#states' => array(
        'disabled' => array(
          ':input[name="advagg_mod_css_defer"]' => array('value' => '0'),
        ),
        'invisible' => array(
          ':input[name="advagg_mod_css_defer_visibility"]' => array('value' => '3'),
        ),
      ),
    );
    list(, $params) = advagg_mod_find_critical_css_file();
    list($dirs) = $params;
    $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL)) . '/';
    $form['global_container']['css']['placement']['advagg_mod_css_defer_visibility_file_explained'] = array(
      '#type' => 'item',
      '#markup' => t('Valid example file locations for this page: <p><code>@line1</code><br><code>@line2</code><br><code>@line3</code></p> valid example file locations for the "front" page: <p><code>@line4</code><br><code>@line5</code><br><code>@line6</code></p> valid example file locations for "node/1" (<a href="@url">current_path()</a>) page: <p><code>@line7</code><br><code>@line8</code><br><code>@line9</code></p> valid example file locations for the node type of "page": <p><code>@line10</code><br><code>@line11</code><br><code>@line12</code></p>', array(
        '@url' => 'https://api.drupal.org/api/drupal/includes%21path.inc/function/current_path/7.x',
        '@line1' => "{$dirs[0]}{$dirs[1]}{$dirs[2]}{$dirs[4]}{$dirs[6]}.css",
        '@line2' => "{$dirs[0]}{$dirs[1]}anonymous/{$dirs[4]}{$dirs[6]}.css",
        '@line3' => "{$dirs[0]}{$dirs[1]}{$dirs[3]}{$dirs[4]}{$dirs[6]}.css",
        '@line4' => "{$theme_path}{$dirs[1]}{$dirs[2]}{$dirs[4]}front.css",
        '@line5' => "{$theme_path}{$dirs[1]}anonymous/{$dirs[4]}front.css",
        '@line6' => "{$theme_path}{$dirs[1]}{$dirs[3]}{$dirs[4]}front.css",
        '@line7' => "{$theme_path}{$dirs[1]}{$dirs[2]}{$dirs[4]}node/1.css",
        '@line8' => "{$theme_path}{$dirs[1]}anonymous/{$dirs[4]}node/1.css",
        '@line9' => "{$theme_path}{$dirs[1]}{$dirs[3]}{$dirs[4]}node/1.css",
        '@line10' => "{$theme_path}{$dirs[1]}{$dirs[2]}{$dirs[5]}page.css",
        '@line11' => "{$theme_path}{$dirs[1]}anonymous/{$dirs[5]}page.css",
        '@line12' => "{$theme_path}{$dirs[1]}{$dirs[3]}{$dirs[5]}page.css",
      )),
      '#states' => array(
        'visible' => array(
          ':input[name="advagg_mod_css_defer_visibility"]' => array('value' => '3'),
        ),
      ),
    );
  }
  $form['global_container']['css']['placement']['advagg_mod_css_defer_skip_first_file'] = array(
    '#type' => 'radios',
    '#title' => t('Do not defer the first css file'),
    '#default_value' => variable_get('advagg_mod_css_defer_skip_first_file', ADVAGG_MOD_CSS_DEFER_SKIP_FIRST_FILE),
    '#description' => t('Link Stylesheet will make the first css file be blocking. Inline CSS will inline up to @size of the first CSS files.', array('@size' => advagg_mod_admin_byte2human(variable_get('advagg_mod_css_defer_inline_size_limit', ADVAGG_MOD_CSS_DEFER_INLINE_SIZE_LIMIT)))),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('Link Stylesheet'),
      4 => t('Inline CSS (no more than @size)', array('@size' => advagg_mod_admin_byte2human(variable_get('advagg_mod_css_defer_inline_size_limit', ADVAGG_MOD_CSS_DEFER_INLINE_SIZE_LIMIT)))),
    ),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_mod_css_defer"]' => array('value' => '0'),
      ),
      'invisible' => array(
        ':input[name="advagg_mod_css_defer_visibility"]' => array('value' => '3'),
      ),
    ),
  );
  $form['global_container']['css']['placement']['advagg_mod_css_defer_js_code'] = array(
    '#type' => 'radios',
    '#title' => t('How to include the JS loading code'),
    '#default_value' => variable_get('advagg_mod_css_defer_js_code', ADVAGG_MOD_CSS_DEFER_JS_CODE),
    '#options' => array(
      0 => t('Inline javascript loader library (recommended)'),
      2 => t('Local file included in aggregate'),
      4 => t('Externally load the latest from github'),
    ),
    '#description' => t('The <a href="@link">loadCSS</a> library can be included in various ways.', array(
      '@link' => 'https://github.com/filamentgroup/loadCSS',
    )),
    '#recommended_value' => 0,
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_mod_css_defer"]' => array('value' => '0'),
      ),
    ),

  );
  $form['global_container']['css']['placement']['advagg_mod_css_defer_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use JS to load CSS in the admin theme'),
    '#default_value' => variable_get('advagg_mod_css_defer_admin', ADVAGG_MOD_CSS_DEFER_ADMIN),
    '#description' => t('This will optimize CSS delivery with JavaScript when viewing the admin theme'),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_mod_css_defer"]' => array('value' => '0'),
      ),
      'invisible' => array(
        ':input[name="advagg_mod_css_defer_visibility"]' => array('value' => '3'),
      ),
    ),
  );

  $pages_all = variable_get('advagg_mod_inline_pages', '');
  $pages_css = variable_get('advagg_mod_inline_css_pages', '');
  $pages_js = variable_get('advagg_mod_inline_js_pages', '');
  unset($options[ADVAGG_MOD_VISIBILITY_NOTLISTED], $options[ADVAGG_MOD_VISIBILITY_FILE_CONTROLLED]);
  $form['global_container']['landing_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inline CSS/JS on specific pages'),
    '#description' => t('For most people these are settings that should not be used. This will prevent all local CSS and/or JavaScript files from being downloaded; instead the contents of them will all be inlined. This will cause the raw HTML downloaded to be a lot bigger but it will cause less connections to your webserver from being created. This can sometimes be useful for certain landing pages.'),
    '#collapsible' => TRUE,
    '#collapsed' => ($pages_all || $pages_css || $pages_js) ? FALSE : TRUE,
  );
  $visibility_all = variable_get('advagg_mod_inline_visibility', ADVAGG_MOD_VISIBILITY_LISTED);
  if ($visibility_all == ADVAGG_MOD_VISIBILITY_PHP && !$access) {
    $form['global_container']['landing_page']['path']['visibility_all'] = array(
      '#type' => 'value',
      '#value' => $visibility_all,
    );
    $form['global_container']['landing_page']['path']['pages_all'] = array(
      '#type' => 'value',
      '#value' => $pages_all,
    );
  }
  else {
    $form['global_container']['landing_page']['path']['advagg_mod_inline_visibility'] = array(
      '#type' => 'radios',
      '#title' => t('Inline CSS and JS on specific pages'),
      '#options' => $options,
      '#default_value' => $visibility_all,
    );
    $form['global_container']['landing_page']['path']['advagg_mod_inline_pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $pages_all,
      '#description' => $description,
    );
  }

  $visibility_css = variable_get('advagg_mod_inline_css_visibility', ADVAGG_MOD_VISIBILITY_LISTED);
  if ($visibility_css == ADVAGG_MOD_VISIBILITY_PHP && !$access) {
    $form['global_container']['landing_page']['path']['visibility_all'] = array(
      '#type' => 'value',
      '#value' => $visibility_css,
    );
    $form['global_container']['landing_page']['path']['pages_all'] = array(
      '#type' => 'value',
      '#value' => $pages_css,
    );
  }
  else {
    $form['global_container']['landing_page']['path']['advagg_mod_inline_css_visibility'] = array(
      '#type' => 'radios',
      '#title' => t('Inline CSS on specific pages'),
      '#options' => $options,
      '#default_value' => $visibility_css,
    );
    $form['global_container']['landing_page']['path']['advagg_mod_inline_css_pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $pages_css,
      '#description' => $description,
    );
  }
  $visibility_js = variable_get('advagg_mod_inline_js_visibility', ADVAGG_MOD_VISIBILITY_LISTED);
  if ($visibility_js == ADVAGG_MOD_VISIBILITY_PHP && !$access) {
    $form['global_container']['landing_page']['path']['visibility_all'] = array(
      '#type' => 'value',
      '#value' => $visibility_js,
    );
    $form['global_container']['landing_page']['path']['pages_all'] = array(
      '#type' => 'value',
      '#value' => $pages_js,
    );
  }
  else {
    $form['global_container']['landing_page']['path']['advagg_mod_inline_js_visibility'] = array(
      '#type' => 'radios',
      '#title' => t('Inline JS on specific pages'),
      '#options' => $options,
      '#default_value' => $visibility_js,
    );
    $form['global_container']['landing_page']['path']['advagg_mod_inline_js_pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $pages_js,
      '#description' => $description,
    );
  }

  $form['global_container']['unified_multisite'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unified Multisite'),
    '#description' => t('For most people this is a setting that should not be used.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['global_container']['unified_multisite']['advagg_mod_unified_multisite_dir'] = array(
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

/**
 * Validate callback, check that the unified multisite directory was created.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_mod_admin_settings_form_validate($form, &$form_state) {
  // Unified Mmultisite.
  $multisite_dir = rtrim($form_state['values']['advagg_mod_unified_multisite_dir'], '/');
  if (!empty($multisite_dir)) {
    // Prepare directory.
    $css_dir = $multisite_dir . '/advagg_css';
    $js_dir = $multisite_dir . '/advagg_js';
    if (!file_prepare_directory($css_dir, FILE_CREATE_DIRECTORY)
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

  // Use JS to load CSS.
  if ($form_state['values']['advagg_mod_css_defer']) {
    if ($form_state['values']['advagg_mod_css_defer_visibility'] == ADVAGG_MOD_VISIBILITY_LISTED
      && empty($form_state['values']['advagg_mod_css_defer_pages'])
    ) {
      form_set_error('advagg_mod_css_defer_pages', t('The Deferred CSS Execution setting will run only on specific pages. On other pages it will act as being Disabled. Please input what pages you wish to have the CSS be deferred. Currently none are selected.'));
    }
    if ($form_state['values']['advagg_mod_css_defer_visibility'] == ADVAGG_MOD_VISIBILITY_NOTLISTED
      && $form_state['values']['advagg_mod_css_defer_pages'] === '*'
    ) {
      form_set_error('advagg_mod_css_defer_pages', t('The Deferred CSS Execution setting will run only on specific pages. On other pages it will act as being Disabled. Please input what pages you wish to have the CSS not be deferred. Currently all pages are disabled (*).'));
    }
  }
}

/**
 * Submit callback, clear out the advagg cache bin.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_mod_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();

  // Reset this form to defaults or recommended values; also show what changed.
  advagg_set_admin_form_defaults_recommended($form_state, 'advagg_mod_admin_mode');

  // If file controlled, turn off skip first file turn on admin defer.
  if ($form_state['values']['advagg_mod_css_defer_visibility'] == 3) {
    $form_state['values']['advagg_mod_css_defer_skip_first_file'] = 0;
    $form_state['values']['advagg_mod_css_defer_admin'] = TRUE;
  }

  // If unified_multisite_dir has changed, flush menu router at the end of the
  // request.
  $multisite_dir = rtrim($form_state['values']['advagg_mod_unified_multisite_dir'], '/');
  $dir = rtrim(variable_get('advagg_mod_unified_multisite_dir', ''), '/');
  if ($multisite_dir != $dir) {
    register_shutdown_function('advagg_get_root_files_dir', TRUE);
    register_shutdown_function('menu_rebuild');
  }

  if (empty($form_state['values']['advagg_mod_js_defer_inline_alter']) && !empty($form_state['values']['advagg_mod_js_defer_jquery'])) {
    $form_state['values']['advagg_mod_js_defer_jquery'] = FALSE;
  }
}

/**
 * Test all CSS files seeing if any string translations do anything.
 *
 * @return array
 *   An array with the filename key and the before => after translation value.
 */
function advagg_mod_admin_test_css_files() {
  $output = array();
  // Get list of files.
  $query_files = db_select('advagg_files', 'af')
    ->fields('af', array('filename_hash', 'filename'))
    ->condition('filetype', 'css')
    ->orderBy('filename', 'ASC')
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
    $file_contents = advagg_load_stylesheet_content((string) @advagg_file_get_contents($filename), TRUE);

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
      if ($value === ';' || $value === '}') {
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
      // @codingStandardsIgnoreLine
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

/**
 * Converts a number of bytes into human readable format.
 *
 * @param string $bytes
 *   Number to convert into a more human readable format.
 * @param int $precision
 *   Number of decimals to output.
 *
 * @return string
 *   Human readable format of the bytes.
 */
function advagg_mod_admin_byte2human($bytes, $precision = 0) {
  $units = array('', 'K', 'M', 'G', 'T');

  $bytes = max($bytes, 0);
  $pow = floor(($bytes ? log($bytes) : 0) / log(1024));
  $pow = min($pow, count($units) - 1);
  $bytes /= (1 << (10 * $pow));

  $output = ceil(round($bytes, $precision + 2) * 10) / 10;
  return $output . '' . $units[$pow];
}
