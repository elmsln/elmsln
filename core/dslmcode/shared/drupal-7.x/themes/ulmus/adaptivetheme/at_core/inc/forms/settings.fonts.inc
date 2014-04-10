<?php

/**
 * @file
 * Generate form elments for the font settings.
 */
function at_core_fonts_form(&$form) {
  // Get the font elements array, this holds options and settings for each font type
  $form_elements = font_elements();

  // Get the font size lists
  $font_sizes_em = font_sizes('em');
  $font_sizes_p  = font_sizes('p');

  // Get the google charsets and styles
  $google_charsets = google_font_charsets();
  $google_styles = google_font_styles();

  // Build a message for fonts depending on what is enabled
  $fonts_message = t('<h3>Fonts</h3><p>First select the font type&thinsp;&mdash;&thinsp;websafe, google or custom&thinsp;&mdash;&thinsp;then select or enter the required information depending on the type. Adaptivetheme can also support any font supplied by the <a href="!module_fyf" target="_blank">@font-your-face module</a>, new settings and instructions will appear after you have installed @font-your-face.</p><p>To preview and gather required information for adding Google fonts see: <a href="!gwf" target="_blank">google.com/webfonts</a>. If you are adding extra styles or character sets these must exist for the specified font&thinsp;&mdash;&thinsp;use the <em>Quick-use</em> feature in Google fonts to check this information.</p>',
  array(
    '!gwf' => 'http://www.google.com/webfonts',
    '!cfs' => 'http://coding.smashingmagazine.com/2009/09/22/complete-guide-to-css-font-stacks/',
    '!module_fyf' => 'http://drupal.org/project/fontyourface',
    )
  );

  // Build a list of font type options
  $font_type_options = array(
    '<none>' => 'None',
    '' => 'Websafe fonts',
    'gwf' => 'Basic Google font',
    'cfs' => 'Custom font stack',
  );

  // Do some stuff if @font-your-face is enabled
  $font_your_face_enabled = FALSE;
  if (module_exists('fontyourface')) {
    // add an option to the font type settings
    $font_your_face_enabled = font_your_face_fonts_enabled();
    if ($font_your_face_enabled == TRUE) {
      $fyf_type = array('fyf' => '@font-your-face');
      $font_type_options = array_merge($font_type_options, $fyf_type);
    }

    // Special message once font your face in installed
    $browse_fyf = l(t('@font-your-face library'), 'admin/appearance/fontyourface/browse', array('attributes' => array('target' => array('_blank'))));
    $settings_fyf = l(t('"add selector in theme CSS"'), 'admin/appearance/fontyourface', array('attributes' => array('target' => array('_blank'))));
    $fonts_message = t('<h3>Fonts</h3><p>First select the font type&thinsp;&mdash;&thinsp;websafe, google, custom or @font-your-face&thinsp;&mdash;&thinsp;then select or enter the required information depending on the type. To use @font-your-face you must first enable fonts in the !browse_fyf, then set those fonts to !settings_fyf. When you have done this the @font-your-face fonts will be availble here for you to apply to your content and titles. @font-your-face integration has only been tested with Google and Font Squirrel.</p><p>To preview and gather required information for adding Google fonts see: <a href="!gwf" target="_blank">google.com/webfonts</a>. If you are adding extra styles or character sets these must exist for the specified font&thinsp;&mdash;&thinsp;use the <em>Quick-use</em> feature in Google fonts to check this information.</p>',
    array(
      '!gwf' => 'http://www.google.com/webfonts',
      '!cfs' => 'http://coding.smashingmagazine.com/2009/09/22/complete-guide-to-css-font-stacks/',
      '!browse_fyf' => $browse_fyf,
      '!settings_fyf' => $settings_fyf,
      )
    );
  }

  // Some re-usable strings, fixing things in multiple places annoys me
  $google_font_description = t('Paste the Google font name, e.g. <code>Open Sans Condensed</code>. Only add one font.');
  $custom_stack_description = t("Enter a comma seperated list of fonts, with no trailing comma. Names with spaces should be wrapped in single quotes, for example <code>'Times New Roman'</code>.");

  // Fonts
  $form['at']['font'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fonts'),
    '#description' => $fonts_message,
    '#attributes' => array('class' => array('font-element-wrapper')),
    '#weight' => -110,
  );

  // Base font - global font family unless overridden by a more specific selector
  $form['at']['font']['base-font'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default font'),
  );
  $form['at']['font']['base-font']['base_font_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => $font_type_options,
    '#default_value' => at_get_setting('base_font_type'),
  );
  $form['at']['font']['base-font']['base_font'] = array(
    '#type' => 'select',
    '#title' => t('Font'),
    '#default_value' => at_get_setting('base_font'),
    '#options' => str_replace("'", "", font_list('wsf', 'bf')),
    '#states' => array('visible' => array('select[name="base_font_type"]' => array('value' => ''))),
  );

  // Google web font
  $form['at']['font']['base-font']['base_font_gwf'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Font Name'),
    '#default_value' => filter_xss_admin(at_get_setting('base_font_gwf')),
    '#description' => $google_font_description,
    '#states' => array('visible' => array('select[name="base_font_type"]' => array('value' => 'gwf'))),
  );
  $form['at']['font']['base-font']['base_font_gwf_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Google Font Styles'),
    '#states' => array('visible' => array('select[name="base_font_type"]' => array('value' => 'gwf'))),
  );
  $form['at']['font']['base-font']['base_font_gwf_styles']['base_font_gwf_add_styles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Styles'),
    '#default_value' => at_get_setting('base_font_gwf_add_styles'),
  );
  foreach ($google_styles as $style_key => $style_value) {
    $form['at']['font']['base-font']['base_font_gwf_styles']["base_font_gwf_add_styles_$style_key"] = array(
      '#type' => 'checkbox',
      '#title' => t($style_value),
      '#default_value' => at_get_setting("base_font_gwf_add_styles_$style_key"),
      '#states' => array('visible' => array('input[name="base_font_gwf_add_styles"]' => array('checked' => TRUE))),
    );
  }
  $form['at']['font']['base-font']['base_font_gwf_charsets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Google Font Character Sets'),
    '#states' => array('visible' => array('select[name="base_font_type"]' => array('value' => 'gwf'))),
  );
  $form['at']['font']['base-font']['base_font_gwf_charsets']['base_font_gwf_add_charsets'] = array(
    '#type' => 'checkbox',
    '#title' => t('Character Sets'),
    '#default_value' => at_get_setting('base_font_gwf_add_charsets'),
    '#states' => array('visible' => array('select[name="base_font_type"]' => array('value' => 'gwf'))),
  );
  foreach ($google_charsets as $charset_key => $charset_value) {
    $form['at']['font']['base-font']['base_font_gwf_charsets']["base_font_gwf_add_charsets_$charset_key"] = array(
      '#type' => 'checkbox',
      '#title' => t($charset_value),
      '#default_value' => at_get_setting("base_font_gwf_add_charsets_$charset_key"),
      '#states' => array('visible' => array('input[name="base_font_gwf_add_charsets"]' => array('checked' => TRUE))),
    );
  }

  // Custom font stack
  $form['at']['font']['base-font']['base_font_cfs'] = array(
    '#type' => 'textfield',
    '#title' => t('Font'),
    '#default_value' => filter_xss_admin(at_get_setting('base_font_cfs')),
    '#description' => $custom_stack_description,
    '#states' => array(
      'visible' => array('select[name="base_font_type"]' => array('value' => 'cfs')),
      'required' => array('select[name="base_font_type"]' => array('value' => 'cfs')),
    )
  );

  // Font your face
  if ($font_your_face_enabled == TRUE) {
    $form['at']['font']['base-font']['base_font_fyf'] = array(
      '#type' => 'select',
      '#title' => t('Font'),
      '#default_value' => at_get_setting('base_font_fyf'),
      '#options' => font_list('fyf', 'bf'),
      '#states' => array('visible' => array('select[name="base_font_type"]' => array('value' => 'fyf'))),
    );
  }

  // Size
  $form['at']['font']['base-font']['base_font_size'] = array(
    '#type' => 'select',
    '#title' => t('Size'),
    '#options' => $font_sizes_p,
    '#description' => t('The default font size is set on the HTML element. All elements, margins, padding and widths using a relative unit such as em or % will scale relative to this value. Use "Not set" if you prefer to set this in your CSS. You can override this value in your responsive stylesheets also, to use a larger or smaller default size for different device types.'),
    '#default_value' => at_get_setting('base_font_size'),
    '#attributes' => array('class' => array('font-size-wrapper')),
  );

  // Titles
  $form['at']['font']['titles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Titles'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  foreach ($form_elements as $key => $value) {

    $form_type = $key;
    $font_element_type = $value['type'];

    if ($font_element_type === 'title') {

      $element  = $value['element'];  // e.g. "bf" (base-font), this is used to set array keys
      $setting  = $value['setting'];  // the theme setting used to retrieve the font values, e.g. "site_name_font"

      $setting_container = str_replace('_', '-', $setting) . '-selector'; // a nicer string for fielset classes
      $title = str_replace('_', ' ', drupal_ucfirst($form_type)); // use the key for titles, it doesnt have "font" in it

      // Set easy reusable variables
      $setting_type = $setting . '_type';
      $setting_font = $setting . '_font';
      $setting_gwf  = $setting . '_gwf';
      $setting_cfs  = $setting . '_cfs';
      $setting_yfy  = $setting . '_fyf';
      $setting_size = $setting . '_size';

      $form['at']['font']['titles'][$setting_container] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
      );
      $form['at']['font']['titles'][$setting_container][$setting_type] = array(
        '#type' => 'select',
        '#title' => t('Type'),
        '#options' => $font_type_options,
        '#default_value' => at_get_setting($setting_type),
      );
      $form['at']['font']['titles'][$setting_container][$setting] = array(
        '#type' => 'select',
        '#title' => t('Font'),
        '#default_value' => at_get_setting($setting),
        '#options' => str_replace("'", "", font_list('wsf', $element)),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => ''))),
      );

      // Google web fonts
      $form['at']['font']['titles'][$setting_container][$setting_gwf] = array(
        '#type' => 'textfield',
        '#title' => t('Google Font Name'),
        '#default_value' => filter_xss_admin(at_get_setting($setting_gwf)),
        '#description' => $google_font_description,
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $title_styles_setting = $setting_gwf . '_add_styles';
      $form['at']['font']['titles'][$setting_container][$setting_container . '_gwf_styles'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add Google Font Styles'),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $form['at']['font']['titles'][$setting_container][$setting_container . '_gwf_styles'][$title_styles_setting] = array(
        '#type' => 'checkbox',
        '#title' => t('Styles'),
        '#default_value' => at_get_setting($title_styles_setting),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      foreach ($google_styles as $style_key => $style_value) {
        $form['at']['font']['titles'][$setting_container][$setting_container . '_gwf_styles'][$title_styles_setting . '_' . $style_key] = array(
          '#type' => 'checkbox',
          '#title' => t($style_value),
          '#default_value' => at_get_setting($title_styles_setting . '_' . $style_key),
          '#states' => array('visible' => array(":input[name=$title_styles_setting]" => array('checked' => TRUE))),
        );
      }
      $title_charsets_setting = $setting_gwf . '_add_charsets';
      $form['at']['font']['titles'][$setting_container][$setting_container . '_gwf_charsets'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add Google Font Character Sets'),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $form['at']['font']['titles'][$setting_container][$setting_container . '_gwf_charsets'][$title_charsets_setting] = array(
        '#type' => 'checkbox',
        '#title' => t('Character Sets'),
        '#default_value' => at_get_setting($title_charsets_setting),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      foreach ($google_charsets as $charset_key => $charset_value) {
        $form['at']['font']['titles'][$setting_container][$setting_container . '_gwf_charsets'][$title_charsets_setting . '_' . $charset_key] = array(
          '#type' => 'checkbox',
          '#title' => t($charset_value),
          '#default_value' => at_get_setting($title_charsets_setting . '_' . $charset_key),
          '#states' => array('visible' => array(":input[name=$title_charsets_setting]" => array('checked' => TRUE))),
        );
      }

      // Custom font stack
      $form['at']['font']['titles'][$setting_container][$setting_cfs] = array(
        '#type' => 'textfield',
        '#title' => t('Font'),
        '#default_value' => drupal_strip_dangerous_protocols(at_get_setting($setting_cfs)),
        '#description' => $custom_stack_description,
        '#states' => array(
          'visible' => array('select[name=' . $setting_type . ']' => array('value' => 'cfs')),
          'required' => array('select[name=' . $setting_type . ']' => array('value' => 'cfs')),
        ),
      );

      // Font your face
      if ($font_your_face_enabled == TRUE) {
        $form['at']['font']['titles'][$setting_container][$setting_yfy] = array(
          '#type' => 'select',
          '#title' => t('Font'),
          '#default_value' => at_get_setting($setting_yfy),
          '#options' => font_list('fyf', $element),
          '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'fyf'))),
        );
      }

      // Size
      $form['at']['font']['titles'][$setting_container][$setting_size] = array(
        '#type' => 'select',
        '#title' => t('Size'),
        '#options' => $font_sizes_em,
        '#default_value' => at_get_setting($setting_size),
        '#attributes' => array('class' => array('font-size-wrapper')),
      );
    }
  }

  // In Content Headings
  $form['at']['font']['headings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Headings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  foreach ($form_elements as $key => $value) {

    $form_type = $key;
    $font_element_subtype = $value['subtype'];

    // we have to handle subgroups seperatly
    if ($font_element_subtype === 'heading_group') {

      // e.g. "bf" (base-font), this is used to set array keys
      $element  = $value['element'];

      // the theme setting used to retrieve the font values, e.g. "site_name_font"
      $setting  = $value['setting'];

      // a nicer string for fielset classes
      $setting_container = str_replace('_', '-', $setting) . '-selector';

      // Custom titles
      if ($element === 'h1h4') {
        $title = 'h1 to h4';
      }
      else {
        $title = 'h5 and h6';
      }

      // Set easy reusable variables
      $setting_type = $setting . '_type';
      $setting_font = $setting . '_font';
      $setting_gwf  = $setting . '_gwf';
      $setting_cfs  = $setting . '_cfs';
      $setting_yfy  = $setting . '_fyf';

      $form['at']['font']['headings'][$setting_container] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
      );
      $form['at']['font']['headings'][$setting_container][$setting_type] = array(
        '#type' => 'select',
        '#title' => t('Type'),
        '#options' => $font_type_options,
        '#default_value' => at_get_setting($setting_type),
      );
      $form['at']['font']['headings'][$setting_container][$setting] = array(
        '#type' => 'select',
        '#title' => t('Font'),
        '#default_value' => at_get_setting($setting),
        '#options' => str_replace("'", "", font_list('wsf', $element)),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => ''))),
      );

      // Google web fonts
      $form['at']['font']['headings'][$setting_container][$setting_gwf] = array(
        '#type' => 'textfield',
        '#title' => t('Google Font Name'),
        '#default_value' => filter_xss_admin(at_get_setting($setting_gwf)),
        '#description' => $google_font_description,
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $headings_styles_setting = $setting_gwf . '_add_styles';
      $form['at']['font']['headings'][$setting_container][$setting_container . '_gwf_styles'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add Google Font Styles'),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $form['at']['font']['headings'][$setting_container][$setting_container . '_gwf_styles'][$headings_styles_setting] = array(
        '#type' => 'checkbox',
        '#title' => t('Styles'),
        '#default_value' => at_get_setting($headings_styles_setting),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      foreach ($google_styles as $style_key => $style_value) {
        $form['at']['font']['headings'][$setting_container][$setting_container . '_gwf_styles'][$headings_styles_setting . '_' . $style_key] = array(
          '#type' => 'checkbox',
          '#title' => t($style_value),
          '#default_value' => at_get_setting($headings_styles_setting . '_' . $style_key),
          '#states' => array('visible' => array(":input[name=$headings_styles_setting]" => array('checked' => TRUE))),
        );
      }
      $headings_charsets_setting = $setting_gwf . '_add_charsets';
      $form['at']['font']['headings'][$setting_container][$setting_container . '_gwf_charsets'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add Google Font Character Sets'),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $form['at']['font']['headings'][$setting_container][$setting_container . '_gwf_charsets'][$headings_charsets_setting] = array(
        '#type' => 'checkbox',
        '#title' => t('Character Sets'),
        '#default_value' => at_get_setting($headings_charsets_setting),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      foreach ($google_charsets as $charset_key => $charset_value) {
        $form['at']['font']['headings'][$setting_container][$setting_container . '_gwf_charsets'][$headings_charsets_setting . '_' . $charset_key] = array(
          '#type' => 'checkbox',
          '#title' => t($charset_value),
          '#default_value' => at_get_setting($headings_charsets_setting . '_' . $charset_key),
          '#states' => array('visible' => array(":input[name=$headings_charsets_setting]" => array('checked' => TRUE))),
        );
      }

      // Custom font stacks
      $form['at']['font']['headings'][$setting_container][$setting_cfs] = array(
        '#type' => 'textfield',
        '#title' => t('Font'),
        '#default_value' => filter_xss_admin(at_get_setting($setting_cfs)),
        '#description' => $custom_stack_description,
        '#states' => array(
          'visible' => array('select[name=' . $setting_type . ']' => array('value' => 'cfs')),
          'required' => array('select[name=' . $setting_type . ']' => array('value' => 'cfs')),
        ),
      );

      // Font your face
      if ($font_your_face_enabled == TRUE) {
        $form['at']['font']['headings'][$setting_container][$setting_yfy] = array(
          '#type' => 'select',
          '#title' => t('Font'),
          '#default_value' => at_get_setting($setting_yfy),
          '#options' => font_list('fyf', $element),
          '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'fyf'))),
        );
      }
    }
  }

  // Size for in-content headings
  $form['at']['font']['headings']['sizes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Size'),
    '#attributes' => array('class' => array('font-element-wrapper'))
  );
  foreach ($form_elements as $key => $value) {

    $form_type = $key;
    $font_element_subtype = $value['subtype'];

    // we have to handle subgroups seperatly
    if ($font_element_subtype === 'heading_level') {

      // e.g. "bf" (base-font), this is used to set array keys
      $element  = $value['element'];

      // the theme setting used to retrieve the font values, e.g. "site_name_font"
      $setting  = $value['setting'];

      // Set easy reusable variables
      $setting_type = $setting . '_type';
      $setting_size = $setting . '_size';

      $form['at']['font']['headings']['sizes'][$setting_size] = array(
        '#type' => 'select',
        '#title' => t($element), // element as title is fine in this context
        '#options' => $font_sizes_em,
        '#default_value' => at_get_setting($setting_size),
        '#attributes' => array('class' => array('font-size-wrapper')),
       );
    }
  }

  // Menus
  $form['at']['font']['menus'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menus'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  foreach ($form_elements as $key => $value) {

    $form_type = $key;
    $font_element_type = $value['type'];

    if ($font_element_type === 'menu') {

      // e.g. "bf" (base-font), this is used to set array keys
      $element  = $value['element'];

      // the theme setting used to retrieve the font values, e.g. "site_name_font"
      $setting  = $value['setting'];

      // a nicer string for fielset classes
      $setting_container = str_replace('_', '-', $setting) . '-selector';

      // use the key for titles, it doesnt have "font" in it
      $title = str_replace('_', ' ', drupal_ucfirst($form_type));

      // Set easy reusable variables
      $setting_type = $setting . '_type';
      $setting_font = $setting . '_font';
      $setting_gwf  = $setting . '_gwf';
      $setting_cfs  = $setting . '_cfs';
      $setting_yfy  = $setting . '_fyf';
      $setting_size = $setting . '_size';

      $form['at']['font']['menus'][$setting_container] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
      );
      $form['at']['font']['menus'][$setting_container][$setting_type] = array(
        '#type' => 'select',
        '#title' => t('Type'),
        '#options' => $font_type_options,
        '#default_value' => at_get_setting($setting_type),
      );
      $form['at']['font']['menus'][$setting_container][$setting] = array(
        '#type' => 'select',
        '#title' => t('Font'),
        '#default_value' => at_get_setting($setting),
        '#options' => str_replace("'", "", font_list('wsf', $element)),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => ''))),
      );

      // Google web fonts
      $form['at']['font']['menus'][$setting_container][$setting_gwf] = array(
        '#type' => 'textfield',
        '#title' => t('Google Font Name'),
        '#default_value' => filter_xss_admin(at_get_setting($setting_gwf)),
        '#description' => $google_font_description,
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $menus_styles_setting = $setting_gwf . '_add_styles';
      $form['at']['font']['menus'][$setting_container][$setting_container . '_gwf_styles'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add Google Font Styles'),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $form['at']['font']['menus'][$setting_container][$setting_container . '_gwf_styles'][$menus_styles_setting] = array(
        '#type' => 'checkbox',
        '#title' => t('Styles'),
        '#default_value' => at_get_setting($menus_styles_setting),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      foreach ($google_styles as $style_key => $style_value) {
        $form['at']['font']['menus'][$setting_container][$setting_container . '_gwf_styles'][$menus_styles_setting . '_' . $style_key] = array(
          '#type' => 'checkbox',
          '#title' => t($style_value),
          '#default_value' => at_get_setting($menus_styles_setting . '_' . $style_key),
          '#states' => array('visible' => array(":input[name=$menus_styles_setting]" => array('checked' => TRUE))),
        );
      }
      $menus_charsets_setting = $setting_gwf . '_add_charsets';
      $form['at']['font']['menus'][$setting_container][$setting_container . '_gwf_charsets'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add Google Font Character Sets'),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      $form['at']['font']['menus'][$setting_container][$setting_container . '_gwf_charsets'][$menus_charsets_setting] = array(
        '#type' => 'checkbox',
        '#title' => t('Character Sets'),
        '#default_value' => at_get_setting($menus_charsets_setting),
        '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'gwf'))),
      );
      foreach ($google_charsets as $charset_key => $charset_value) {
        $form['at']['font']['menus'][$setting_container][$setting_container . '_gwf_charsets'][$menus_charsets_setting . '_' . $charset_key] = array(
          '#type' => 'checkbox',
          '#title' => t($charset_value),
          '#default_value' => at_get_setting($menus_charsets_setting . '_' . $charset_key),
          '#states' => array('visible' => array(":input[name=$menus_charsets_setting]" => array('checked' => TRUE))),
        );
      }

      // Custom font stacks
      $form['at']['font']['menus'][$setting_container][$setting_cfs] = array(
        '#type' => 'textfield',
        '#title' => t('Font'),
        '#default_value' => filter_xss_admin(at_get_setting($setting_cfs)),
        '#description' => $custom_stack_description,
        '#states' => array(
          'visible' => array('select[name=' . $setting_type . ']' => array('value' => 'cfs')),
          'required' => array('select[name=' . $setting_type . ']' => array('value' => 'cfs')),
        ),
      );

      // Font your face
      if ($font_your_face_enabled == TRUE) {
        $form['at']['font']['menus'][$setting_container][$setting_yfy] = array(
          '#type' => 'select',
          '#title' => t('Font'),
          '#default_value' => at_get_setting($setting_yfy),
          '#options' => font_list('fyf', $element),
          '#states' => array('visible' => array('select[name=' . $setting_type . ']' => array('value' => 'fyf'))),
        );
      }

      // Size
      $form['at']['font']['menus'][$setting_container][$setting_size] = array(
        '#type' => 'select',
        '#title' => t('Size'),
        '#options' => $font_sizes_em,
        '#default_value' => at_get_setting($setting_size),
        '#attributes' => array('class' => array('font-size-wrapper')),
      );
    }
  }

  // Custom CSS selectors
  $form['at']['font']['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Selectors'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['at']['font']['css']['selectors_font_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => $font_type_options,
    '#default_value' => at_get_setting('selectors_font_type')
  );
  $form['at']['font']['css']['selectors_font'] = array(
    '#type' => 'select',
    '#title' => t('Font'),
    '#default_value' => at_get_setting('selectors_font'),
    '#options' => font_list('wsf', 'css'),
    '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => ''))),
  );

  // Google fonts
  $form['at']['font']['css']['selectors_font_gwf'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Font Name'),
    '#default_value' => filter_xss_admin(at_get_setting('selectors_font_gwf')),
    '#description' => $google_font_description,
    '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => 'gwf'))),
  );
  $css_styles_setting = 'selectors_font_add_styles';
  $form['at']['font']['css']['selectors_font_gwf_styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Google Font Styles'),
    '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => 'gwf'))),
  );
  $form['at']['font']['css']['selectors_font_gwf_styles'][$css_styles_setting] = array(
    '#type' => 'checkbox',
    '#title' => t('Styles'),
    '#default_value' => at_get_setting($css_styles_setting),
    '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => 'gwf'))),
  );
  foreach ($google_styles as $style_key => $style_value) {
    $form['at']['font']['css']['selectors_font_gwf_styles'][$css_styles_setting . '_' . $style_key] = array(
      '#type' => 'checkbox',
      '#title' => t($style_value),
      '#default_value' => at_get_setting($css_styles_setting . '_' . $style_key),
      '#states' => array('visible' => array(":input[name=$css_styles_setting]" => array('checked' => TRUE))),
    );
  }
  $css_charsets_setting = 'selectors_font_add_charsets';
  $form['at']['font']['css']['selectors_font_gwf_charsets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Google Font Character Sets'),
    '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => 'gwf'))),
  );
  $form['at']['font']['css']['selectors_font_gwf_charsets'][$css_charsets_setting] = array(
    '#type' => 'checkbox',
    '#title' => t('Character Sets'),
    '#default_value' => at_get_setting($css_charsets_setting),
    '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => 'gwf'))),
  );
  foreach ($google_charsets as $charset_key => $charset_value) {
    $form['at']['font']['css']['selectors_font_gwf_charsets'][$css_charsets_setting . '_' . $charset_key] = array(
      '#type' => 'checkbox',
      '#title' => t($charset_value),
      '#default_value' => at_get_setting($css_charsets_setting . '_' . $charset_key),
      '#states' => array('visible' => array(":input[name=$css_charsets_setting]" => array('checked' => TRUE))),
    );
  }

  // Custom font stacks
  $form['at']['font']['css']['selectors_font_cfs'] = array(
    '#type' => 'textfield',
    '#title' => t('Font'),
    '#default_value' => filter_xss_admin(at_get_setting('selectors_font_cfs')),
    '#description' => $custom_stack_description,
    '#states' => array(
      'visible' => array('select[name="selectors_font_type"]' => array('value' => 'cfs')),
      'required' => array('select[name="selectors_font_type"]' => array('value' => 'cfs')),
    )
  );

  // Font your face
  if ($font_your_face_enabled == TRUE) {
    $form['at']['font']['css']['selectors_font_fyf'] = array(
      '#type' => 'select',
      '#title' => t('Font'),
      '#default_value' => at_get_setting('selectors_font_fyf'),
      '#options' => font_list('fyf', 'css'),
      '#states' => array('visible' => array('select[name="selectors_font_type"]' => array('value' => 'fyf'))),
    );
  }

  // CSS selectors
  $form['at']['font']['css']['selectors_css'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS Selectors'),
    '#rows' => 3,
    '#default_value' => filter_xss_admin(at_get_setting('selectors_css')),
    '#description' => t("Enter a comma seperated list of valid CSS selectors, with no trailing comma, such as <code>.node-content, .block-content</code>. Note that due to security reason you cannot use the greater than symbol (>) as a child combinator selector."),
    '#states' => array('disabled' => array('select[name="selectors_font_type"]' => array('value' => '<none>'))),
  );
}
