<?php
/**
 * @file
 * Admin forms and functionality for CSS Delivery Optimization.
 */

/**
 * General configuration settings form.
 */
function css_delivery_admin_settings($form, $form_state) {
  $form = array();
  $css_aggregation = (variable_get('preprocess_css', FALSE) && module_exists('advagg') && advagg_enabled()) ? TRUE : FALSE;

  drupal_set_title(t('CSS Delivery configuration'));

  if (!variable_get('css_delivery_build_mode', CSS_DELIVERY_BUILD_MODE) && !$css_aggregation) {
    drupal_set_message(t('It seems that aggregation of CSS files is NOT TURNED ON. In order to benefit from optimized CSS delivery, enable it on the Performance tab.'), 'warning', FALSE);
  }
  else {
    if (variable_get('css_delivery_build_mode', CSS_DELIVERY_BUILD_MODE) && variable_get('preprocess_css', FALSE)) {
      drupal_set_message(t('It seems that aggregation of CSS files is TURNED ON. For builder mode to work it is recommended that both aggregation and CSS delivery optimization are turned off.'), 'warning', FALSE);
    }
  }

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General options'),
    '#collapsible' => FALSE,
  );
  $form['general']['css_delivery_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable CSS Delivery Optimization'),
    '#default_value' => variable_get('css_delivery_enabled', CSS_DELIVERY_ENABLED),
    '#description' => t('Enable CSS delivery optimization features.'),
  );
  $form['general']['css_delivery_source'] = array(
    '#type' => 'radios',
    '#title' => t('Critical CSS source'),
    '#default_value' => variable_get('css_delivery_source', CSS_DELIVERY_SOURCE),
    '#options' => array(
      1 => t('User-defined CSS'),
      2 => t('CSS specified in theme'),
    ),
    '#description' => t('Enable CSS delivery optimization features.'),
  );
  $form['general']['css_delivery_noscript'] = array(
    '#type' => 'checkbox',
    '#title' => t('Load CSS if JavaScript is disabled'),
    '#default_value' => variable_get('css_delivery_noscript', CSS_DELIVERY_NOSCRIPT),
    '#description' => t('If enabled, traditional CSS link tags will be added and wrapped around in noscript This ensures that CSS is loaded when JavaScript is disabled in the browser.'),
  );
  $form['general']['css_delivery_test_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Testing mode'),
    '#default_value' => variable_get('css_delivery_test_mode', CSS_DELIVERY_TEST_MODE),
    '#description' => t('When testing mode is turned on, asynchronous loading of external CSS files is disabled. This enables the testing of the critical CSS only.'),
  );

  $options = array(t('On every page except the listed pages.'), t('On the listed pages only.'));
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.",
    array(
      '%blog' => 'blog',
      '%blog-wildcard' => 'blog/*',
      '%front' => '<front>',
    )
  );
  $pages = variable_get('css_delivery_pages', '');
  $visibility = variable_get('css_delivery_visibility', 0);

  $form['general']['css_delivery_visibility_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page specific settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['general']['css_delivery_visibility_settings']['css_delivery_visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Optimize CSS delivery on'),
    '#options' => $options,
    '#default_value' => $visibility,
  );
  $form['general']['css_delivery_visibility_settings']['css_delivery_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#default_value' => $pages,
    '#description' => $description,
    '#wysiwyg' => FALSE,
  );

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('User defined Critical CSS'),
    '#collapsible' => TRUE,
    '#collapsed' => (variable_get('css_delivery_source', CSS_DELIVERY_SOURCE) == 1) ? FALSE : TRUE,
    '#description' => t('Define custom Critical CSS rules here. This CSS will be added when "Critical CSS source" is set to "User-defined CSS" above.'),
  );
  $form['css']['css_delivery_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Critical CSS code'),
    '#rows' => 20,
    '#default_value' => variable_get('css_delivery_css', CSS_DELIVERY_CSS),
    '#description' => t('<p>Build mode enables the automatic generation of critical css via a JavaScript run in the browser.</p><p>This is an experimental feature and it only works in Google Chrome.</p>'),
  );

  $form['build'] = array(
    '#type' => 'fieldset',
    '#title' => t('Build Critical CSS'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('<p>Build mode enables the automatic generation of critical css via a JavaScript run in the browser.</p><p>This is an EXPERIMENTAL feature and it only works in Google Chrome.</p><p>It is highly recommended that CSS is served from the same origin as the page itself.</p>'),
  );
  $form['build']['css_delivery_build_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Build mode'),
    '#default_value' => variable_get('css_delivery_build_mode', CSS_DELIVERY_BUILD_MODE),
    '#description' => t('Turn this on for an automatic critical CSS generation in the browser.'),
  );
  $form['build']['config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Critical CSS generation options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['build']['config']['css_delivery_build_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow non-external styles in Critical CSS'),
    '#default_value' => variable_get('css_delivery_build_inline', CSS_DELIVERY_BUILD_INLINE),
    '#description' => t('Enabling this will include style rules which do not originate from an external location. These styles include inline CSS on the page or any style attributes, whether set by JavaScript or already in the markup.'),
  );
  $form['build']['config']['css_delivery_build_exclude_selectors'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude the following CSS selectors'),
    '#default_value' => variable_get('css_delivery_build_exclude_selectors', ''),
    '#description' => t('Add a patterns per line. Exclude selectors matching these pattern from the critical CSS.'),
  );

  return system_settings_form($form);
}
