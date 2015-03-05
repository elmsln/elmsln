<?php

/**
 * @file
 * Form and utility functions for the theme settings provided by this module.
 */

/**
 * Implements hook_form_alter()-ish.
 *
 * Called from within the magic.module's implementation for hook_form_alter.
 */
function magic_form_system_theme_settings(&$form, &$form_state, $theme) {
  // Magic Performance Vertical Tabs set
  $form['magic'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 100,
  );

  // CSS Magic Grouping
  $form['magic']['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Enhancements'),
  );

  // CSS Exclude Options
  $form['magic']['css']['magic_css_excludes'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude CSS files'),
    '#description' => t("<p>One entry per line.</p> <p>The <strong><code>*</code></strong> character is a wildcard to match all similar items, for instance <code>system/*.css</code> will remove all CSS provided by the System module. <p>The <strong><code>~</code></strong> character is a reserved character to keep all similar items if they would otherwise be removed, for instance <code>~system/system.menus.css</code> to keep System module's menu CSS even if we remove the rest of System module's CSS. </p> <p>You may use: <br><strong><code>:all</code></strong> to target all CSS files. <br><strong><code>:core</code></strong> to target all Core provided CSS files. <br><strong><code>:contrib</code></strong> to target all Contrib provided CSS files. <br><strong><code>:base-theme</code></strong> to target all base theme provided CSS files. <br><strong><code>:current-theme</code></strong> to target all CSS files provided by the current theme."),
    '#default_value' => theme_get_setting('magic_css_excludes', $theme),
  );

  // JavaScript Magic Grouping
  $form['magic']['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('JavaScript Enhancements'),
  );

  // Footer JavaScript Option
  $form['magic']['js']['magic_footer_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move JavaScript to the Footer'),
    '#description' => t("Will move all JavaScript to the bottom of your page. This can be overridden on an individual basis by setting the <code>'force header' => true</code> option in <code>drupal_add_js</code> or by using <code>hook_js_alter</code> to add the option to other JavaScript files."),
    '#default_value' => theme_get_setting('magic_footer_js', $theme),
  );

  // Keep Libraries in Head JavaScript Option
  $form['magic']['js']['magic_library_head'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep Libraries in the Head'),
    '#description' => t("If you have JavaScript inline in the body of your document, such as if you are displaying ads, you may need to keep Drupal JS Libraries in the head instead of moving them to the footer. This will keep Drupal libraries in the head while still moving all other JavaScript to the footer."),
    '#default_value' => theme_get_setting('magic_library_head', $theme),
    '#states' => array(
      'visible' => array(
        ':input[name=magic_footer_js]' => array('checked' => TRUE),
      ),
    ),
  );

  // Experimental JavaScript Option
  $form['magic']['js']['magic_experimental_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Experimental JavaScript Handling'),
    '#description' => t("This will enable additional options for JavaScript, including browser options, <code>async</code> and <code>defer</code> attributes, and optional additional attributes."),
    '#default_value' => theme_get_setting('magic_experimental_js', $theme),
  );

  // JavaScript Exclude Options
  $form['magic']['js']['magic_js_excludes'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude JavaScript files'),
    '#description' => t("<p>One entry per line.</p> <p>The <strong><code>*</code></strong> character is a wildcard to match all similar items, for instance <code>overlay/*.js</code> will remove all JS provided by the Overlay module.</p> <p>The <strong><code>~</code></strong> character is a reserved character to keep all similar items if they would otherwise be removed, for instance <code>~overlay/overlay-child.js</code> to keep Overlay module's overlay-child JS even if we remove the rest of Overlay module's JS.</p> <p>You may use: <br><strong><code>:all</code></strong> to target all JS files. <br><strong><code>:core</code></strong> to target all Core provided JS files. <br><strong><code>:contrib</code></strong> to target all Contrib provided JS files. <br><strong><code>:base-theme</code></strong> to target all base theme provided JS files. <br><strong><code>:current-theme</code></strong> to target all JS files provided by the current theme. <br><strong><code>:settings</code></strong> to remove the settings array."),
    '#default_value' => theme_get_setting('magic_js_excludes', $theme),
  );

  // Add export button to export current theme settings
  $form['actions']['export'] = array(
    '#type' => 'submit',
    '#value' => t('Save and export configuration'),
  );

  // We need a custom submit handler to store the CSS and JS paths as arrays.
  array_unshift($form['#submit'], 'magic_form_system_theme_settings_submit');

  return $form;
}

/**
 * Submit handler for the theme settings form.
 *
 * This form will take the theme settings, and for the css and js excludes,
 * create the regex that will be required to remove the css and js files at
 * will. It will then selectively clear the caches for those specific cache
 * items.
 */
function magic_form_system_theme_settings_submit($form, &$form_state) {
  // Remove the active tab (vertical tabs) element from the settings array.
  unset($form_state['values']['magic__active_tab']);
  $theme = $form_state['build_info']['args'][0];

  // If the triggering element is the 'export' button, redirect to the export
  // form.
  if ($form_state['triggering_element']['#value'] == t('Save and export configuration')) {
    $form_state['redirect'] = "admin/appearance/settings/$theme/export";
  }

  // Clear the cache entries maintained by this module.
  magic_clear_cache($theme);
}
