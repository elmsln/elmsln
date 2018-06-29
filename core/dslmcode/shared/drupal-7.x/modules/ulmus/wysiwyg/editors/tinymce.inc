<?php

/**
 * @file
 * Editor integration functions for TinyMCE.
 */

/**
 * Plugin implementation of hook_editor().
 *
 * @todo wysiwyg_<editor>_alter() to add/inject optional libraries like gzip.
 */
function wysiwyg_tinymce_editor() {
  $editor['tinymce'] = array(
    'title' => 'TinyMCE',
    'vendor url' => 'https://www.tinymce.com',
    'download url' => 'https://www.tinymce.com/download',
    'library path' => wysiwyg_get_path('tinymce'),
    'libraries' => array(
      '' => array(
        'title' => 'Minified',
        'files' => array('tiny_mce.js'),
      ),
      'src' => array(
        'title' => 'Source',
        'files' => array('tiny_mce_src.js'),
      ),
    ),
    'version callback' => 'wysiwyg_tinymce_version',
    'verified version range' => array('3.3.9.2', '4.5.7'),
    'themes callback' => 'wysiwyg_tinymce_themes',
    'settings form callback' => 'wysiwyg_tinymce_settings_form',
    'init callback' => 'wysiwyg_tinymce_init',
    'settings callback' => 'wysiwyg_tinymce_settings',
    'plugin callback' => '_wysiwyg_tinymce_plugins',
    'plugin meta callback' => '_wysiwyg_tinymce_plugin_meta',
    'migrate settings callback' => '_wysiwyg_tinymce_migrate_settings',
    'proxy plugin' => array(
      'drupal' => array(
        'load' => TRUE,
        'proxy' => TRUE,
      ),
    ),
    'proxy plugin settings callback' => '_wysiwyg_tinymce_proxy_plugin_settings',
    'versions' => array(
      '3.3' => array(
        'js files' => array('tinymce-3.js'),
        'library path' => wysiwyg_get_path('tinymce') . '/jscripts/tiny_mce',
        'css files' => array('tinymce-3.css'),
        'libraries' => array(
          '' => array(
            'title' => 'Minified',
            'files' => array(
              // Some versions can not be aggregated.
              'tiny_mce.js' => array('preprocess' => FALSE),
            ),
          ),
          'jquery' => array(
            'title' => 'jQuery',
            'files' => array('tiny_mce_jquery.js'),
          ),
          'src' => array(
            'title' => 'Source',
            'files' => array('tiny_mce_src.js'),
          ),
        ),
      ),
      '4' => array(
        'js files' => array('tinymce-4.js'),
        'css files' => array('tinymce-4.css'),
        'library path' => wysiwyg_get_path('tinymce') . '/js/tinymce',
        'libraries' => array(
          'min' => array(
            'title' => 'Minified',
            'files' => array('tinymce.min.js'),
          ),
        ),
      ),
    ),
  );
  return $editor;
}

/**
 * Detect editor version.
 *
 * @param $editor
 *   An array containing editor properties as returned from hook_editor().
 *
 * @return
 *   The installed editor version.
 */
function wysiwyg_tinymce_version($editor) {
  $script = $editor['library path'] . '/jscripts/tiny_mce/tiny_mce.js';
  if (!file_exists($script)) {
    $script = $editor['library path'] . '/js/tinymce/tinymce.min.js';
    if (!file_exists($script)) {
      return;
    }
  }
  $script = fopen($script, 'r');
  // Version is contained in the first 200 chars.
  $line = fgets($script, 200);
  fclose($script);
  // 2.x: this.majorVersion="2";this.minorVersion="1.3"
  // 3.x: majorVersion:'3',minorVersion:'2.0.1'
  // 4.x: 4.0b2 (2013-04-24)
  if (preg_match('@majorVersion[=:]["\'](\d).+?minorVersion[=:]["\']([\d\.]+)@', $line, $version) || preg_match('@(\d)\.([\d\.\w]+) @', $line, $version)) {
    return $version[1] . '.' . $version[2];
  }
}

/**
 * Determine available editor themes or check/reset a given one.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $profile
 *   A wysiwyg editor profile.
 *
 * @return
 *   An array of theme names. The first returned name should be the default
 *   theme name.
 */
function wysiwyg_tinymce_themes($editor, $profile) {
  /*
  $themes = array();
  $dir = $editor['library path'] . '/themes/';
  if (is_dir($dir) && $dh = opendir($dir)) {
    while (($file = readdir($dh)) !== FALSE) {
      if (!in_array($file, array('.', '..', 'CVS', '.svn')) && is_dir($dir . $file)) {
        $themes[$file] = $file;
      }
    }
    closedir($dh);
    asort($themes);
  }
  return $themes;
  */
  if (version_compare($editor['installed version'], '4', '>=')) {
    return array('modern');
  }
  else {
    return array('advanced', 'simple');
  }
}

/**
 * Enhances the editor profile settings form for TinyMCE.
 *
 * @see http://www.tinymce.com/wiki.php/Configuration
 */
function wysiwyg_tinymce_settings_form(&$form, &$form_state) {
  $version = $form_state['wysiwyg']['editor']['installed version'];
  $profile = $form_state['wysiwyg_profile'];
  $settings = $profile->settings;
  $default_settings = array(
    'convert_fonts_to_spans' => TRUE,
    'paste_convert_middot_lists' => TRUE,
    'paste_max_consecutive_linebreaks' => 2,
    'paste_retain_style_properties' => 'none',
    'paste_remove_styles' => TRUE,
    'paste_remove_styles_if_webkit' => TRUE,
    'paste_strip_class_attributes' => 'mso',
    'paste_text_linebreaktype' => 'combined',
    'verify_html' => TRUE,
  );
  if (version_compare($version, '3.2.5', '>=')) {
    $default_settings['autoresize_min_height'] = NULL;
    $default_settings['autoresize_max_height'] = NULL;
  }
  if (version_compare($version, '3.3', '>=')) {
    $default_settings['style_formats'] = '';
    $default_settings['formats'] = '';
  };
  if (version_compare($version, '3.4b1', '>=')) {
    $default_settings['indent'] = FALSE;
  }
  else {
    $default_settings['apply_source_formatting'] = FALSE;
  }
  if (version_compare($version, '4', '>=')) {
    $default_settings += array(
      'block_formats' => '',
      'image_advtab' => FALSE,
      'paste_as_text' => FALSE,
      'paste_data_images' => FALSE,
      'resize' => TRUE,
      'menu' => NULL,
    );
  }
  else {
    $default_settings += array(
      'paste_auto_cleanup_on_paste' => TRUE,
      'preformatted' => FALSE,
      'remove_linebreaks' => TRUE,
      // Also available, but buggy in TinyMCE 2.x: blockquote,code,dt,dd,samp.
      'theme_advanced_blockformats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'theme_advanced_path' => TRUE,
      'theme_advanced_statusbar_location' => 'bottom',
      'theme_advanced_styles' => '',
      'theme_advanced_resize_horizontal' => FALSE,
      'theme_advanced_resizing' => TRUE,
      'theme_advanced_toolbar_align' => 'left',
      'theme_advanced_toolbar_location' => 'top',
    );
  }

  $settings += $default_settings;

  if (version_compare($version, '3.4b1', '<')) {
    $form['output']['apply_source_formatting'] = array(
      '#type' => 'checkbox',
      '#title' => t('Apply source formatting'),
      '#default_value' => $settings['apply_source_formatting'],
      '#return_value' => 1,
      '#description' => t('If enabled, the editor will re-format the HTML source code. Disabling this option could avoid conflicts with other input filters.') . ' ' . _wysiwyg_tinymce_get_setting_description('apply_source_formatting'),
    );
  }
  else {
    $form['output']['indent'] = array(
      '#type' => 'checkbox',
      '#title' => t('Indent source'),
      '#default_value' => $settings['indent'],
      '#return_value' => 1,
      '#description' => t('If enabled, the editor will re-format the HTML source code. Disabling this option could avoid conflicts with other input filters.'),
    );
  }

  $form['output']['verify_html'] = array(
    '#type' => 'checkbox',
    '#title' => t('Verify HTML'),
    '#default_value' => $settings['verify_html'],
    '#return_value' => 1,
    '#description' => t('If enabled, potentially malicious code like <code>&lt;HEAD&gt;</code> tags will be removed from HTML contents.') . (_wysiwyg_tinymce_is_v3() ? ' ' . _wysiwyg_tinymce_get_setting_description('verify_html') : ''),
  );

  $form['output']['convert_fonts_to_spans'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert &lt;font&gt; tags to styles'),
    '#default_value' => $settings['convert_fonts_to_spans'],
    '#return_value' => 1,
    '#description' => t('If enabled, HTML tags declaring the font size, font family, font color and font background color will be replaced by inline CSS styles.') . ' ' . _wysiwyg_tinymce_get_setting_description('convert_fonts_to_spans', 'content-filtering'),
  );

  if (version_compare($version, '4', '<')) {
    $form['appearance']['theme_advanced_toolbar_location'] = array(
      '#type' => 'select',
      '#title' => t('Toolbar location'),
      '#default_value' => $settings['theme_advanced_toolbar_location'],
      '#options' => array('bottom' => t('Bottom'), 'top' => t('Top')),
      '#description' => t('This option controls whether the editor toolbar is displayed above or below the editing area.') . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_toolbar_location'),
    );

    $form['appearance']['theme_advanced_toolbar_align'] = array(
      '#type' => 'select',
      '#title' => t('Button alignment'),
      '#default_value' => $settings['theme_advanced_toolbar_align'],
      '#options' => array('center' => t('Center'), 'left' => t('Left'), 'right' => t('Right')),
      '#description' => t('This option controls the alignment of icons in the editor toolbar.') . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_toolbar_align'),
    );

    $form['appearance']['theme_advanced_statusbar_location'] = array(
      '#type' => 'select',
      '#title' => t('Status bar location'),
      '#default_value' => $settings['theme_advanced_statusbar_location'],
      '#options' => array('none' => t('Hide'), 'top' => t('Top'), 'bottom' => t('Bottom')),
      '#description' => t('This option enables you to specify where the element statusbar with the path and resize tool should be located.') . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_statusbar_location'),
    );

    $form['appearance']['theme_advanced_path'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable the element path'),
      '#default_value' => $settings['theme_advanced_path'],
      '#return_value' => 1,
      '#description' => t('This option gives you the ability to enable/disable the element path.') . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_path'),
      '#states' => array(
        'invisible' => array(
          ':input[name="theme_advanced_statusbar_location"]' => array('value' => 'none'),
        ),
      ),
    );

    $form['appearance']['theme_advanced_resizing'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable resizing button'),
      '#default_value' => $settings['theme_advanced_resizing'],
      '#return_value' => 1,
      '#description' => t('This option gives you the ability to enable/disable the resizing button.') . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_resizing'),
      '#states' => array(
        'invisible' => array(
          ':input[name="theme_advanced_statusbar_location"]' => array('value' => 'none'),
        ),
      ),
    );

    $form['appearance']['theme_advanced_resize_horizontal'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable horizontal resizing'),
      '#default_value' => $settings['theme_advanced_resize_horizontal'],
      '#return_value' => 1,
      '#description' => t('This option gives you the ability to enable/disable the horizontal resizing. If enabled, the Path location toolbar must be set to "Top" or "Bottom" in order to display the resize icon.') . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_resize_horizontal'),
    );

    $form['output']['remove_linebreaks'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove linebreaks'),
      '#default_value' => $settings['remove_linebreaks'],
      '#return_value' => 1,
      '#description' => t('If enabled, the editor will remove most linebreaks from contents. Disabling this option could avoid conflicts with other input filters.') . ' ' . _wysiwyg_tinymce_get_setting_description('remove_linebreaks'),
    );

    $form['output']['preformatted'] = array(
      '#type' => 'checkbox',
      '#title' => t('Preformatted'),
      '#default_value' => $settings['preformatted'],
      '#return_value' => 1,
      '#description' => t('If enabled, the editor will insert TAB characters on tab and preserve other whitespace characters just like a PRE element in HTML does.') . ' ' . _wysiwyg_tinymce_get_setting_description('preformatted'),
    );

    $form['css']['theme_advanced_blockformats'] = array(
      '#type' => 'textfield',
      '#title' => t('Block formats'),
      '#default_value' => $settings['theme_advanced_blockformats'],
      '#size' => 40,
      '#maxlength' => 250,
      '#description' => t('Comma separated list of HTML block formats. Possible values: <code>@format-list</code>.', array('@format-list' => 'p,h1,h2,h3,h4,h5,h6,div,blockquote,address,pre,code,dt,dd')) . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_blockformats'),
      '#element_validate' => array('wysiwyg_tinymce_settings_form_validate_blockformats'),
      '#weight' => 30,
    );

    $form['css']['theme_advanced_styles'] = array(
      '#type' => 'textarea',
      '#title' => t('CSS classes'),
      '#default_value' => $settings['theme_advanced_styles'],
      '#description' => t('Optionally define CSS classes for the "Font style" dropdown list.<br />Enter one class on each line in the format: !format. Example: !example<br />If left blank, CSS classes are automatically imported from all loaded stylesheet(s).',
        array(
          '!format' => '<code>[title]=[class]</code>',
          '!example' => 'My heading=header1',
        )
      ) . ' ' . _wysiwyg_tinymce_get_setting_description('theme_advanced_styles'),
      '#weight' => 40,
    );
  }

  if (version_compare($version, '3.3', '>=')) {
    if (version_compare($version, '4', '>=')) {
      $form['css']['theme_advanced_styles']['#access'] = FALSE;
    }
    else {
      $form['css']['theme_advanced_styles']['#description'] .= '<br />' . t('This setting is only used if <em>Style formats</em> is empty.');
    }

    $form['css']['style_formats'] = array(
      '#type' => 'textarea',
      '#title' => t('Style formats'),
      '#default_value' => $settings['style_formats'],
      '#description' => t('A JSON object containing advanced style formats for text and other elements to add to the editor. The value will be rendered as styles in the Formats dropdown.') . ' ' . _wysiwyg_tinymce_get_setting_description('style_formats', 'content-formatting'),
      '#element_validate' => array('_wysiwyg_tinymce_settings_form_validate_style_formats'),
      '#weight' => 40,
    );

    $form['css']['formats'] = array(
      '#type' => 'textarea',
      '#title' => t('Formats'),
      '#default_value' => $settings['formats'],
      '#description' => t('This option enables you to override and add custom formats. A format is for example the style that get applied when you press the bold button inside the editor. TinyMCE has some built in formats that you can override, see the editor documentation for the complete list. The value to put in should be a JSON object containing format definitions.') . ' ' . _wysiwyg_tinymce_get_setting_description('formats', 'content-formatting'),
      '#element_validate' => array('_wysiwyg_tinymce_settings_form_validate_formats'),
      '#weight' => 50,
    );
  }

  if (version_compare($version, '4', '>=')) {
    $form['image'] = array(
      '#type' => 'fieldset',
      '#title' => t('Image plugin'),
      '#description' => t('Settings for the <a href="@url">@plugin</a> plugin.', array('@plugin' => 'image', '@url' => _wysiwyg_tinymce_get_plugin_url('image'))),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'advanced',
    );
    $form['image']['image_advtab'] = array(
      '#type' => 'checkbox',
      '#title' => t('Advanced tab'),
      '#default_value' => $settings['image_advtab'],
      '#return_value' => 1,
      '#description' => t('Enable the advanced tab in the image dialog.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('image', 'image_advtab'),
    );

    if (version_compare($version, '4.0.13', '>=')) {
      $form['css']['style_formats_merge'] = array(
        '#type' => 'checkbox',
        '#title' => t('Merge style formats'),
        '#default_value' => !empty($settings['style_formats_merge']),
        '#return_value' => 1,
        '#description' => t('Append the styles formats to the default set instead of replacing it completely.') . ' ' . _wysiwyg_tinymce_get_setting_description('style_formats_merge', 'content-formatting'),
        '#weight' => 41,
      );
    }

    $form['css']['block_formats'] = array(
      '#type' => 'textfield',
      '#title' => t('Block formats'),
      '#default_value' => $settings['block_formats'],
      '#size' => 40,
      '#maxlength' => 250,
      '#description' => t('Semi-colon separated list of block formats for the block listbox. The format is: <code>@format-list</code>.', array('@format-list' => 'Paragraph=p;Header 1=h1;Header 2=h2;Header 3=h3')) . ' ' . _wysiwyg_tinymce_get_setting_description('block_formats', 'content-formatting'),
      '#weight' => 20,
    );
  }

  $form['paste'] = array(
    '#type' => 'fieldset',
    '#title' => t('Paste plugin'),
    '#description' => t('Settings for the <a href="@url">@plugin</a> plugin.', array('@plugin' => 'paste', '@url' => _wysiwyg_tinymce_get_plugin_url('paste'))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'advanced',
  );

  if (version_compare($version, '4', '<')) {
    $form['paste']['paste_auto_cleanup_on_paste'] = array(
      '#type' => 'checkbox',
      '#title' => t('Process contents on paste'),
      '#default_value' => !empty($settings['paste_auto_cleanup_on_paste']),
      '#return_value' => 1,
      '#description' => t('If enabled, contents will be automatically processed when you paste using Ctrl+V or similar methods. Cleaning up contents from MS Word or pasting as plain text will <strong>not</strong> work without this.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_auto_cleanup_on_paste'),
      '#element_validate' => array('wysiwyg_tinymce_settings_form_validate_blockformats'),
    );
  }

  $form['paste']['paste_auto_cleanup_on_paste'] = array(
    '#type' => 'checkbox',
    '#title' => t('Process contents on paste'),
    '#default_value' => !empty($settings['paste_auto_cleanup_on_paste']),
    '#return_value' => 1,
    '#description' => t('If enabled, contents will be automatically processed when you paste using Ctrl+V or similar methods. Cleaning up contents from MS Word or pasting as plain text will <strong>not</strong> work without this.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_auto_cleanup_on_paste'),
  );

  $form['paste']['paste_block_drop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Block drag/drop'),
    '#default_value' => !empty($settings['paste_block_drop']),
    '#return_value' => 1,
    '#description' => t('If enabled, blocks drag/drop from/to the editor and inside it.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_block_drop'),
  );

  $form['paste']['paste_retain_style_properties'] = array(
    '#type' => 'textfield',
    '#title' => t('Retain style properties'),
    '#default_value' => $settings['paste_retain_style_properties'],
    '#description' => t('Comma separated list of style properties to retain during the paste operation from Word. For example: "font-size,color". If you want to remove all style properties use an empty string "" or "none". If you want to keep all style properties, use "all" or "*".') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_retain_style_properties'),
  );

  $form['paste']['paste_strip_class_attributes'] = array(
    '#type' => 'select',
    '#title' => t('Strip class attributes'),
    '#options' => array(
      'none' => t('None'),
      'all' => t('All'),
      'mso' => t('MS Office'),
    ),
    '#default_value' => $settings['paste_strip_class_attributes'],
    '#description' => t('Enables you to strip the class attributes when pasted.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_strip_class*attributes'),
  );

  $form['paste']['paste_remove_spans'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove spans'),
    '#default_value' => !empty($settings['paste_remove_spans']),
    '#return_value' => 1,
    '#description' => t('If enabled, removes all span elements when pasting.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_remove_spans'),
  );

  $form['paste']['paste_remove_styles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove styles'),
    '#default_value' => !empty($settings['paste_remove_styles']),
    '#return_value' => 1,
    '#description' => t('If enabled, removes all style information when pasting, regardless of browser type. Pasting from Word 2000 will cause TinyMCE to error.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_remove_styles'),
  );

  $form['paste']['paste_remove_styles_if_webkit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove styles in WebKit'),
    '#default_value' => !empty($settings['paste_remove_styles_if_webkit']),
    '#return_value' => 1,
    '#description' => t('If enabled, removes all style information when pasting in WebKit since it has a serious paste bug.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_remove_styles_if_webkit'),
  );

  $form['paste']['paste_convert_middot_lists'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert Word lists'),
    '#default_value' => !empty($settings['paste_convert_middot_lists']),
    '#return_value' => 1,
    '#description' => t('If enabled, the paste plugin tries to convert Word lists into semantic XHTML list elements.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_convert_middot_lists'),
  );

  $form['paste']['paste_convert_headers_to_strong'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert headers to strong'),
    '#default_value' => !empty($settings['paste_convert_headers_to_srong']),
    '#return_value' => 1,
    '#description' => t('If enabled, the paste plugin tries to convert Word headers to strong tags.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_convert_headers_to_strong'),
  );

  $form['paste']['paste_max_consecutive_linebreaks'] = array(
    '#type' => 'textfield',
    '#title' => t('Max consecutive linebreaks'),
    '#size' => 5,
    '#maxlength' => '10',
    '#default_value' => !empty($settings['paste_max_consecutive_linebreaks']),
    '#description' => t('The maximum number of consecutive linebreaks to use.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_max_consecutive_linebreaks'),
  );

  $form['paste']['paste_text_use_dialog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use dialog'),
    '#default_value' => !empty($settings['paste_text_use_dialog']),
    '#return_value' => 1,
    '#description' => t('If enabled, uses legacy mode for the Paste as Text button. Will use a dialog instead of treating the button as a toggle.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_text_use_dialog'),
  );

  $form['paste']['paste_text_sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sticky "Paste text" button'),
    '#default_value' => !empty($settings['paste_text_sticky']),
    '#return_value' => 1,
    '#description' => t('If enabled, keeps the "Paste text" button selected after pasting. Requires the "Paste text" button and "Process contents on paste" to be enabled.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_text_sticky'),
  );

  $form['paste']['paste_text_sticky_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Paste as plain text by default'),
    '#default_value' => !empty($settings['paste_text_sticky_default']),
    '#return_value' => 1,
    '#description' => t('If enabled, the "Paste text" button is selected when the editor starts. Requires the "Paste text" button and "Process contents on paste" to be enabled.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_text_sticky_default'),
  );

  $form['paste']['paste_text_notifyalways'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always notify when pasting plain text'),
    '#default_value' => !empty($settings['paste_text_notifyalways']),
    '#return_value' => 1,
    '#description' => t('If enabled, users will be notified each time plain text pasting mode is enabled.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_text_notifyalways'),
  );

  $form['paste']['paste_text_linebreaktype'] = array(
    '#type' => 'select',
    '#title' => t('Linebreak type'),
    '#options' => array(
      'combined' => t('Combined'),
      'p' => t('<p>'),
      'br' => t('<br>'),
    ),
    '#default_value' => $settings['paste_text_linebreaktype'],
    '#description' => t('Converts plain text linebreaks to br or p elements.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_text_linebreaktype'),
  );

  if (version_compare($version, '4', '>=')) {
    $form['appearance']['menu'] = array(
      '#title' => t('Menu'),
      '#type' => 'textarea',
      '#default_value' => $settings['menu'],
      '#description' => t('The options to use in the menu, as a JSON&star; structure. The <a href="@controls">available controls</a> and format for this setting can be found in the official settings description. Note: You must make sure the plugin providing a control is also enabled.', array('@controls' => url('https://www.tinymce.com/docs/advanced/editor-control-identifiers/#menucontrols'))) . ' ' . _wysiwyg_tinymce_get_setting_description('menu', 'editor-appearance'),
      '#element_validate' => array('wysiwyg_tinymce_settings_form_validate_menu'),
    );

    $form['appearance']['resize'] = array(
      '#type' => 'select',
      '#title' => t('Resizing'),
      '#description' => t('This option gives you the ability to disable the resize handle or set it to resize both horizontal and vertically.') . ' ' . _wysiwyg_tinymce_get_setting_description('resize', 'editor-appearance'),
      '#options' => array(
        FALSE => t('Disabled'),
        TRUE => t('Vertical'),
        'both' => t('Horizontal and vertical'),
      ),
      '#default_value' => $settings['resize'],
    );

    $form['paste']['paste_as_text'] = array(
      '#type' => 'checkbox',
      '#title' => t('Paste as text'),
      '#default_value' => !empty($settings['paste_as_text']),
      '#return_value' => 1,
      '#description' => t('If enabled, the default state of the "Paste as text" edit menu option is enabled.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('paste', 'paste_as_text'),
    );
    $form['paste']['paste_data_images'] = array(
      '#type' => 'checkbox',
      '#title' => t('Paste inline images'),
      '#default_value' => !empty($settings['paste_data_images']),
      '#return_value' => 1,
      '#description' => t('If enabled, users will be allowed to paste data:url (inline) images, embedding the actual images data with the text contents. This is normally not something people want, since say embedding a 600kb image will take a long time to upload, store the image in the database, block page loads, and prevent caching the image across multiple pages. Firefox is known to allow embedding images through pasting or drag and drop.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('plugin', 'paste_data_images'),
    );
  }
  if (version_compare($version, '3.2.5', '>=')) {
    $form['autoresize'] = array(
      '#type' => 'fieldset',
      '#title' => t('Autoresize plugin'),
      '#description' => t('Settings for the <a href="@url">@plugin</a> plugin.', array('@plugin' => 'autoresize', '@url' => _wysiwyg_tinymce_get_plugin_url('autoresize'))),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'advanced',
    );
    $form['autoresize']['autoresize_min_height'] = array(
      '#title' => t('Min height'),
      '#type' => 'textfield',
      '#default_value' => $settings['autoresize_min_height'],
      '#size' => 10,
      '#description' => t('Minimum height value of the editor when it auto resizes.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('autoresize', 'autoresize_min_height'),
    );
    $form['autoresize']['autoresize_max_height'] = array(
      '#title' => t('Max height'),
      '#type' => 'textfield',
      '#default_value' => $settings['autoresize_max_height'],
      '#size' => 10,
      '#description' => t('Maximum height value of the editor when it auto resizes.') . ' ' . _wysiwyg_tinymce_get_plugin_setting_description('autoresize', 'autoresize_max_height'),
    );
  }
}

/**
 * #element_validate handler for theme_advanced_blockformats element added by wysiwyg_tinymce_settings_form().
 */
function wysiwyg_tinymce_settings_form_validate_blockformats($element, &$form_state) {
  // Remove any white-space from 'theme_advanced_blockformats' setting, since
  // the editor relies on a comma-separated list to explode().
  form_set_value($element, preg_replace('@\s+@', '', $element['#value']), $form_state);
}

/**
 * #element_validate handler for formats element added by wysiwyg_tinymce_settings_form().
 */
function _wysiwyg_tinymce_settings_form_validate_formats($element, &$form_state) {
  $helper = _wysiwyg_settings_form_validate_json_object($element, $form_state);
  if (!$helper['valid']) {
    form_error($element, t('The specified formats must be a valid JSON object.') . '&nbsp;&star;');
  }
}

/**
 * #element_validate handler for style_formats element added by wysiwyg_tinymce_settings_form().
 */
function _wysiwyg_tinymce_settings_form_validate_style_formats($element, &$form_state) {
  $helper = _wysiwyg_settings_form_validate_json_object($element, $form_state);
  if (!$helper['valid']) {
    form_error($element, t('The specified style formats must be a valid JSON object.') . '&nbsp;&star;');
  }
}

/**
 * #element_validate handler for menu element added by wysiwyg_tinymce_settings_form().
 */
function wysiwyg_tinymce_settings_form_validate_menu($element, &$form_state) {
  $helper = _wysiwyg_settings_form_validate_json_object($element, $form_state);
  if (!$helper['valid']) {
    form_error($element, t('The specified menu structure must be a valid JSON object.') . '&nbsp;&star;');
  }
}

/**
 * Returns an initialization JavaScript for this editor library.
 *
 * @param array $editor
 *   The editor library definition.
 * @param string $library
 *   The library variant key from $editor['libraries'].
 * @param object $profile
 *   The (first) wysiwyg editor profile.
 *
 * @return string
 *   A string containing inline JavaScript to execute before the editor library
 *   script is loaded.
 */
function wysiwyg_tinymce_init($editor, $library) {
  // TinyMCE unconditionally searches for its library filename in SCRIPT tags on
  // on the page upon loading the library in order to determine the base path to
  // itself. When JavaScript aggregation is enabled, this search fails and all
  // relative constructed paths within TinyMCE are broken. The library has a
  // tinyMCE.baseURL property, but it is not publicly documented and thus not
  // reliable. The official support forum suggests to solve the issue through
  // the global window.tinyMCEPreInit variable also used by various serverside
  // compressor scrips available from the official website.
  // @see http://www.tinymce.com/forum/viewtopic.php?id=23286
  $settings = drupal_json_encode(array(
    'base' => base_path() . $editor['library path'],
    'suffix' => (strpos($library, 'src') !== FALSE || strpos($library, 'dev') !== FALSE ? '_src' : (strpos($library, 'min') !== FALSE ? '.min' : '')),
    'query' => '',
  ));
  return <<<EOL
window.tinyMCEPreInit = $settings;
EOL;
}

/**
 * Return runtime editor settings for a given wysiwyg profile.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $config
 *   An array containing wysiwyg editor profile settings.
 * @param $theme
 *   The name of a theme/GUI/skin to use.
 *
 * @return
 *   A settings array to be populated in
 *   Drupal.settings.wysiwyg.configs.{editor}
 */
function wysiwyg_tinymce_settings($editor, $config, $theme) {
  $version = $editor['installed version'];
  $settings = array(
    // @todo Add a setting for this.
    'button_tile_map' => TRUE,
    'document_base_url' => base_path(),
    'mode' => 'none',
    'plugins' => array(),
    'theme' => $theme,
    'width' => '100%',
    // Strict loading mode must be enabled; otherwise TinyMCE would use
    // document.write() in IE and Chrome.
    'strict_loading_mode' => TRUE,
    // TinyMCE's URL conversion magic breaks Drupal modules that use a special
    // syntax for paths. This makes 'relative_urls' obsolete.
    'convert_urls' => FALSE,
    // The default entity_encoding ('named') converts too many characters in
    // languages (like Greek). Since Drupal supports Unicode, we only convert
    // HTML control characters and invisible characters. TinyMCE always converts
    // XML default characters '&', '<', '>'.
    'entities' => '160,nbsp,173,shy,8194,ensp,8195,emsp,8201,thinsp,8204,zwnj,8205,zwj,8206,lrm,8207,rlm',
  );
  if (version_compare($version, '4', '<')) {
    $settings += array(
      'theme_advanced_toolbar_location' => 'top',
    );
  }
  $check_if_set = array(
    'apply_source_formatting',
    'autoresize_min_height',
    'autoresize_max_height',
    'convert_fonts_to_spans',
    'font_styles_merge',
    'image_advtab',
    'indent',
    'language',
    'paste_as_text',
    'paste_auto_cleanup_on_paste',
    'paste_block_drop',
    'paste_convert_middot_lists',
    'paste_convert_headers_to_strong',
    'paste_data_images',
    'paste_max_consecutive_linebreaks',
    'paste_remove_spans',
    'paste_remove_styles',
    'paste_remove_styles_if_webkit',
    'paste_retain_style_properties',
    'paste_strip_class_attributes',
    'paste_text_linebreaktype',
    'paste_text_notifyalways',
    'paste_text_use_dialog',
    'paste_text_sticky',
    'paste_text_sticky_default',
    'preformatted',
    'remove_linebreaks',
    'resize',
    'style_formats_merge',
    'theme_advanced_blockformats',
    'theme_advanced_path',
    'theme_advanced_resize_horizontal',
    'theme_advanced_resizing',
    'theme_advanced_statusbar_location',
    'theme_advanced_toolbar_location',
    'theme_advanced_toolbar_align',
  );
  foreach ($check_if_set as $setting_name) {
    if (isset($config[$setting_name])) {
      $settings[$setting_name] = $config[$setting_name];
    }
  }

  if (!empty($settings['language']) && $settings['language'] == 'en') {
    unset($settings['language']);
  }

  if (isset($config['verify_html'])) {
    // TinyMCE performs a type-agnostic comparison on this particular setting.
    $settings['verify_html'] = (bool) $config['verify_html'];
  }

  if (!empty($config['style_formats'])) {
    $settings['style_formats'] = json_decode($config['style_formats']);
  }
  if (!empty($config['theme_advanced_styles'])) {
    $settings['theme_advanced_styles'] = implode(';', array_filter(explode("\n", str_replace("\r", '', $config['theme_advanced_styles']))));
  }

  if (!empty($config['menu'])) {
    $settings['menu'] = json_decode($config['menu']);
  }

  if (isset($config['css_setting'])) {
    if ($config['css_setting'] == 'theme') {
      $settings['content_css'] = implode(',', wysiwyg_get_css(isset($config['css_theme']) ? $config['css_theme'] : ''));
    }
    elseif ($config['css_setting'] == 'self' && isset($config['css_path'])) {
      $settings['content_css'] = strtr($config['css_path'], array(
        '%b' => base_path(),
        '%t' => drupal_get_path('theme', variable_get('theme_default', NULL)),
        '%q' => variable_get('css_js_query_string', ''),
      ));
    }
  }

  // Find the enabled buttons and the button row they belong on.
  // Also map the plugin metadata for each button.
  // @todo What follows is a pain; needs a rewrite.
  // $settings['buttons'] are stacked into $settings['theme_advanced_buttons1']
  // later.
  $settings['buttons'] = array();
  if (!empty($config['buttons']) && is_array($config['buttons'])) {
    // Only array keys in $settings['extensions'] matter; added to
    // $settings['plugins'] later.
    $settings['extensions'] = array();
    // $settings['extended_valid_elements'] are just stacked, unique'd later,
    // and transformed into a comma-separated string in
    // wysiwyg_add_editor_settings().
    // @todo Needs a complete plugin API redesign using arrays for
    //   tag => attributes definitions and array_merge_recursive().
    $settings['extended_valid_elements'] = array();

    $plugins = wysiwyg_get_plugins($editor['name']);
    foreach ($config['buttons'] as $plugin => $buttons) {
      foreach ($buttons as $button => $enabled) {
        // Iterate separately over buttons and extensions properties.
        foreach (array('buttons', 'extensions') as $type) {
          // Skip unavailable plugins.
          if (!isset($plugins[$plugin][$type][$button])) {
            continue;
          }
          // Add buttons.
          if ($type == 'buttons') {
            if (!empty($plugins[$plugin]['proxy'])) {
              $settings['buttons'][] = 'drupal_' . $button;
            }
            else {
              $settings['buttons'][] = $button;
            }
          }
          // Add external Drupal plugins to the list of extensions.
          if ($type == 'buttons' && !empty($plugins[$plugin]['proxy'])) {
            $settings['extensions'][_wysiwyg_tinymce_plugin_name('add', 'drupal_' . $button)] = 1;
          }
          // Add external plugins to the list of extensions.
          elseif ($type == 'buttons' && empty($plugins[$plugin]['internal'])) {
            $settings['extensions'][_wysiwyg_tinymce_plugin_name('add', $plugin)] = 1;
          }
          // Add internal buttons that also need to be loaded as extension.
          elseif ($type == 'buttons' && !empty($plugins[$plugin]['load'])) {
            $settings['extensions'][$plugin] = 1;
          }
          // Add plain extensions.
          elseif ($type == 'extensions' && !empty($plugins[$plugin]['load'])) {
            $settings['extensions'][$plugin] = 1;
          }
          // Allow plugins to add valid HTML elements.
          if (!empty($plugins[$plugin]['extended_valid_elements'])) {
            $settings['extended_valid_elements'] = array_merge($settings['extended_valid_elements'], $plugins[$plugin]['extended_valid_elements']);
          }
          // Allow plugins to add or override global configuration settings.
          if (!empty($plugins[$plugin]['options'])) {
            $settings = array_merge($settings, $plugins[$plugin]['options']);
          }
        }
      }
    }
    // Clean-up.
    $settings['extended_valid_elements'] = array_unique($settings['extended_valid_elements']);
    if ($settings['extensions']) {
      $settings['plugins'] = array_keys($settings['extensions']);
    }
    unset($settings['extensions']);
  }

  if (version_compare($version, '4', '>=')) {
    if (isset($settings['buttons'])) {
      // @todo Allow to sort/arrange editor buttons.
      for ($i = 0; $i < count($settings['buttons']); $i++) {
        $settings['toolbar'][] = $settings['buttons'][$i];
      }
    }
    // TinyMCE 3 allowed the callback to be the name of a function. Convert it
    // to a reference to keep compatibility with IMCE Wysiwyg bridge module.
    // Both isset() and is_string() needed, generates a notice if undefined.
    if (isset($settings['file_browser_callback']) && is_string($settings['file_browser_callback'])) {
      $settings['file_browser_callback'] = wysiwyg_wrap_js_callback($settings['file_browser_callback']);
    }
  }

  // Add theme-specific settings.
  switch ($theme) {
    case 'advanced':
      $settings += array(
        'theme_advanced_resizing_use_cookie' => FALSE,
      );
      if (isset($settings['buttons'])) {
        // These rows explicitly need to be set to be empty, otherwise TinyMCE
        // loads its default buttons of the advanced theme for each row.
        $settings += array(
          'theme_advanced_buttons1' => array(),
          'theme_advanced_buttons2' => array(),
          'theme_advanced_buttons3' => array(),
        );
        // @todo Allow to sort/arrange editor buttons.
        for ($i = 0; $i < count($settings['buttons']); $i++) {
          $settings['theme_advanced_buttons1'][] = $settings['buttons'][$i];
        }
      }
      break;
  }
  unset($settings['buttons']);

  // Convert the config values into the form expected by TinyMCE.
  $csv_settings = array('toolbar', 'plugins', 'extended_valid_elements', 'theme_advanced_buttons1', 'theme_advanced_buttons2', 'theme_advanced_buttons3');
  foreach ($csv_settings as $key) {
    if (isset($settings[$key]) && is_array($settings[$key])) {
      $settings[$key] = implode(',', $settings[$key]);
    }
  }

  return $settings;
}

/**
 * Callback to migrate settings between known TinyMCE versions.
 */
function _wysiwyg_tinymce_migrate_settings(&$settings, $editor, $profile_version, $installed_version) {
  $version_diff = version_compare($installed_version, $profile_version);
  // Default to no changes needed.
  $migrated_version = TRUE;
  if ($version_diff === 1) {
    // Upgrading, starting at the profile version going up.
    if (version_compare($profile_version, '3.4b1', '<') && version_compare($installed_version, '3.4b1', '>=')) {
      if (isset($settings['apply_source_formatting'])) {
        $settings['indent'] = $settings['apply_source_formatting'];
        unset($settings['apply_source_formatting']);
      }
      $migrated_version = '3.4b1';
    }
    if (version_compare($profile_version, '4', '<') && version_compare($installed_version, '4', '>=')) {
      if (isset($settings['buttons']['advimage']['advimage']) && $settings['buttons']['advimage']['advimage']) {
        $settings['image_advtab'] = TRUE;
      }
      if (isset($settings['theme']) && ($settings['theme'] === 'advanced' || $settings['theme'] === 'simple')) {
        $settings['theme'] = 'modern';
      }
      if (isset($settings['theme_advanced_blockformats'])) {
        $formats = array();
        foreach (explode(',', $settings['theme_advanced_blockformats']) as $block) {
          switch ($block[0]) {
            case 'p':
              $formats[] = 'Paragraph=p';
              break;

            case 'h':
              $formats[] = 'Heading ' . $block[1] . '=' . $block;
              break;

            default:
              $formats[] = strtoupper($block[0]) . substr($block, 1) . '=' . $block;
          }
        }
        $settings['block_formats'] = implode(';', $formats);
        unset($settings['theme_advanced_blockformats']);
      }

      $settings['resize'] = FALSE;
      if (!empty($settings['theme_advanced_resizing'])) {
        if (!empty($settings['theme_advanced_resize_horizontal'])) {
          $settings['resize'] = 'both';
        }
        else {
          $settings['resize'] = TRUE;
        }
      }
      unset($settings['theme_advanced_resizing'], $settings['theme_advanced_resize_horizontal'], $settings['theme_advanced_toolbar_location'], $settings['theme_advanced_toolbar_align'], $settings['theme_advanced_statusbar_location'], $settings['theme_advanced_styles']);

      $fixed_buttons = array();
      foreach ($settings['buttons'] as $plugin => $buttons) {
        foreach ($buttons as $button => $enabled) {
          $converted = _wysiwyg_tinymce_3_to_4_plugin_remap($plugin, $button);
          if ($converted) {
            $fixed_buttons[$converted[0]][$converted[1]] = $enabled;
          }
        }
      }
      $settings['buttons'] = $fixed_buttons;
      $migrated_version = '4.0.0';
    }
    if (version_compare($profile_version, '4.5.0', '<') && version_compare($installed_version, '4.5.0', '>=')) {
      // The list buttons now require the lists plugin.
      if (!empty($settings['buttons']['default']['bullist'])) {
        $settings['buttons']['lists']['bullist'] = 1;
      }
      if (!empty($settings['buttons']['default']['numlist'])) {
        $settings['buttons']['lists']['numlist'] = 1;
      }
      unset($settings['buttons']['default']['bullist'], $settings['buttons']['default']['numlist']);
      $migrated_version = '4.5.0';
    }
  }
  else {
    // Downgrading, starting at the profile version going down.
    if (version_compare($profile_version, '4.5.0', '>=') && version_compare($installed_version, '4.5.0', '<')) {
      unset($settings['buttons']['toc']);
      if (!empty($settings['buttons']['lists']['bullist'])) {
        $settings['buttons']['default']['bullist'] = 1;
      }
      if (!empty($settings['buttons']['lists']['numlist'])) {
        $settings['buttons']['default']['numlist'] = 1;
      }
      unset($settings['buttons']['lists']);
      $migrated_version = '4.5.0';
    }
    if (version_compare($profile_version, '4.3.0', '>=') && version_compare($installed_version, '4.3.0', '<')) {
      unset($settings['buttons']['codesample']);
      $migrated_version = '4.2.7';
    }
    if (version_compare($profile_version, '4', '>=') && version_compare($installed_version, '4', '<')) {
      if (isset($settings['theme']) && $settings['theme'] === 'modern') {
        $settings['theme'] = 'advanced';
      }
      if (!isset($settings['block_formats'])) {
        $formats = array();
        foreach (explode(';', $settings['block_formats']) as $block) {
          $parts = explode('=', $block, 2);
          $formats[] = $parts[1];
        }
        $settings['theme_advanced_blockformats'] = implode(',', $formats);
        unset($settings['block_formats']);
      }

      $settings['theme_advanced_resizing'] = $settings['theme_advanced_resize_horizontal'] = FALSE;
      if ($settings['resize'] == 'both' || $settings['resize'] == TRUE) {
        $settings['theme_advanced_resizing'] = TRUE;
        if ($settings['resize'] == 'both') {
          $settings['theme_advanced_resize_horizontal'] = TRUE;
        }
      }
      unset($settings['resize']);
      $fixed_buttons = array();
      foreach ($settings['buttons'] as $plugin => $buttons) {
        foreach ($buttons as $button => $enabled) {
          $converted = _wysiwyg_tinymce_4_to_3_plugin_remap($plugin, $button);
          if (is_array($converted[0])) {
            foreach ($converted as $sub_converted) {
              $fixed_buttons[$sub_converted[0]][$sub_converted[1]] = $enabled;
            }
          }
          else {
            if ($converted) {
              $fixed_buttons[$converted[0]][$converted[1]] = $enabled;
            }
          }
        }
      }
      $settings['buttons'] = $fixed_buttons;

      if (!empty($settings['image_advtab'])) {
        $settings['buttons']['advimage']['advimage'] = 1;
        unset($settings['image_advtab']);
      }
      $migrated_version = '4.0';
    }
    if (version_compare($profile_version, '3.4b1', '>=') && version_compare($installed_version, '3.4b1', '<')) {
      if (isset($settings['indent'])) {
        $settings['apply_source_formatting'] = $settings['indent'];
        unset($settings['indent']);
      }
      $migrated_version = '3.4b1';
    }
  }
  return $migrated_version;
}

/**
 * Build a JS settings array with global metadata for native external plugins.
 */
function _wysiwyg_tinymce_plugin_meta($editor, $plugin) {
  $meta = NULL;
  if (!empty($plugin['load'])) {
    // Add path for native external plugins; internal ones are loaded
    // automatically.
    if (empty($plugin['internal']) && isset($plugin['filename'])) {
      $meta = base_path() . $plugin['path'] . '/' . $plugin['filename'];
    }
  }
  return $meta;
}

/**
 * Add or remove leading hiven to/of external plugin names.
 *
 * TinyMCE requires that external plugins, which should not be loaded from
 * its own plugin repository are prefixed with a hiven in the name.
 *
 * @param string $op
 *   Operation to perform, 'add' or 'remove' (hiven).
 * @param string $name
 *   A plugin name.
 */
function _wysiwyg_tinymce_plugin_name($op, $name) {
  if ($op == 'add') {
    if (strpos($name, '-') !== 0) {
      return '-' . $name;
    }
    return $name;
  }
  elseif ($op == 'remove') {
    if (strpos($name, '-') === 0) {
      return substr($name, 1);
    }
    return $name;
  }
}

/**
 * Build a JS settings array for Drupal plugins loaded via the proxy plugin.
 */
function _wysiwyg_tinymce_proxy_plugin_settings($editor, $profile, $plugins) {
  $settings = array();
  foreach ($plugins as $name => $plugin) {
    // Just need a list of all enabled plugins for each instance.
    $settings[$name] = TRUE;
  }
  return $settings;
}

/**
 * Return internal plugins for this editor; semi-implementation of hook_wysiwyg_plugin().
 */
function _wysiwyg_tinymce_plugins($editor) {
  // Buttons which have no icons and only work as menu items. (TinyMCE 4)
  // visualaid - Visual aid
  // selectall - Select All https://github.com/tinymce/tinymce/issues/634

  // Start with a list matching 3.x and modify to match the installed version.
  $plugins = array(
    'default' => array(
      'path' => $editor['library path'] . '/themes/advanced',
      'buttons' => array(
        'bold' => t('Bold'), 'italic' => t('Italic'), 'underline' => t('Underline'),
        'strikethrough' => t('Strikethrough'),
        'justifyleft' => t('Align left'), 'justifycenter' => t('Align center'), 'justifyright' => t('Align right'), 'justifyfull' => t('Align full'),
        'bullist' => t('Unordered list'), 'numlist' => t('Ordered list'),
        'outdent' => t('Outdent'), 'indent' => t('Indent'),
        'undo' => t('Undo'), 'redo' => t('Redo'),
        'link' => t('Link'), 'unlink' => t('Unlink'), 'anchor' => t('Anchor'),
        'image' => t('Image'),
        'cleanup' => t('Cleanup messy code'),
        'forecolor' => t('Select text color'), 'backcolor' => t('Select background color'),
        'formatselect' => t('Block format'), 'styleselect' => t('Styles'),
        'fontselect' => t('Font'), 'fontsizeselect' => t('Font size'),
        'sup' => t('Superscript'), 'sub' => t('Subscript'),
        'blockquote' => t('Blockquote'), 'code' => t('Edit HTML Source'),
        'hr' => t('Insert horizontal ruler'),
        'cut' => t('Cut'), 'copy' => t('Copy'), 'paste' => t('Paste'),
        'visualaid' => t('Toggle guidelines/invisible elements'),
        'removeformat' => t('Remove formatting'),
        'charmap' => t('Insert custom character'),
        'help' => t('Help'),
      ),
    ),
    'advhr' => array(
      'buttons' => array('advhr' => t('Advanced horizontal rule')),
      'extended_valid_elements' => array('hr[class|width|size|noshade]'),
      'url' => _wysiwyg_tinymce_get_plugin_url('advhr'),
    ),
    'advimage' => array(
      'extensions' => array('advimage' => t('Advanced image')),
      'extended_valid_elements' => array('img[src|alt|title|align|width|height|usemap|hspace|vspace|border|style|class|onmouseover|onmouseout|id|name|longdesc]'),
      'url' => _wysiwyg_tinymce_get_plugin_url('advimage'),
    ),
    'advlink' => array(
      'extensions' => array('advlink' => t('Advanced link')),
      'extended_valid_elements' => array('a[name|href|target|title|class|onfocus|onblur|onclick|ondlbclick|onmousedown|onmouseup|onmouseover|onmouseout|onkeypress|onkeydown|onkeyup|id|style|rel]'),
      'url' => _wysiwyg_tinymce_get_plugin_url('advlink'),
    ),
    'autosave' => array(
      'extensions' => array('autosave' => t('Auto save')),
      'url' => _wysiwyg_tinymce_get_plugin_url('autosave'),
    ),
    'bbcode' => array(
      'extensions' => array('bbcode' => t('BBCode')),
      'url' => _wysiwyg_tinymce_get_plugin_url('bbcode'),
    ),
    'contextmenu' => array(
      'extensions' => array('contextmenu' => t('Context menu')),
      'url' => _wysiwyg_tinymce_get_plugin_url('contextmenu'),
    ),
    'directionality' => array(
      'buttons' => array('ltr' => t('Left-to-right'), 'rtl' => t('Right-to-left')),
      'url' => _wysiwyg_tinymce_get_plugin_url('directionality'),
    ),
    'emotions' => array(
      'buttons' => array('emotions' => t('Emotions')),
      'url' => _wysiwyg_tinymce_get_plugin_url('emotions'),
    ),
    'fullscreen' => array(
      'buttons' => array('fullscreen' => t('Fullscreen')),
      'url' => _wysiwyg_tinymce_get_plugin_url('fullscreen'),
    ),
    'inlinepopups' => array(
      'extensions' => array('inlinepopups' => t('Inline popups')),
      'options' => array(
        'dialog_type' => array('modal'),
      ),
      'url' => _wysiwyg_tinymce_get_plugin_url('inlinepopups'),
    ),
    'insertdatetime' => array(
      'buttons' => array('insertdate' => t('Insert date'), 'inserttime' => t('Insert time')),
      'options' => array(
        'plugin_insertdate_dateFormat' => '%Y-%m-%d',
        'plugin_insertdate_timeFormat' => '%H:%M:%S',
      ),
      'url' => _wysiwyg_tinymce_get_plugin_url('insertdatetime'),
    ),
    'media' => array(
      'buttons' => array('media' => t('Media')),
      'url' => _wysiwyg_tinymce_get_plugin_url('media'),
    ),
    'nonbreaking' => array(
      'buttons' => array('nonbreaking' => t('Insert nonbreaking space')),
      'url' => _wysiwyg_tinymce_get_plugin_url('nonbreaking'),
    ),
    'paste' => array(
      'buttons' => array('pastetext' => t('Paste text'), 'pasteword' => t('Paste from Word'), 'selectall' => t('Select all')),
      'url' => _wysiwyg_tinymce_get_plugin_url('paste'),
    ),
    'preview' => array(
      'buttons' => array('preview' => t('Preview')),
      'url' => _wysiwyg_tinymce_get_plugin_url('preview'),
    ),
    'print' => array(
      'buttons' => array('print' => t('Print')),
      'url' => _wysiwyg_tinymce_get_plugin_url('print'),
    ),
    'safari' => array(
      'path' => $editor['library path'] . '/plugins/safari',
      'extensions' => array('safari' => t('Safari compatibility')),
    ),
    'searchreplace' => array(
      'buttons' => array('search' => t('Search'), 'replace' => t('Replace')),
      'url' => _wysiwyg_tinymce_get_plugin_url('searchreplace'),
    ),
    'style' => array(
      'buttons' => array('styleprops' => t('Advanced CSS styles')),
      'url' => _wysiwyg_tinymce_get_plugin_url('style'),
    ),
    'table' => array(
      'buttons' => array('tablecontrols' => t('Table')),
      'url' => _wysiwyg_tinymce_get_plugin_url('table'),
    ),
    'visualchars' => array(
      'buttons' => array('visualchars' => t('Show invisible characters')),
      'url' => _wysiwyg_tinymce_get_plugin_url('visualchars'),
    ),
  );
  if (version_compare($editor['installed version'], '2.0.6', '>')) {
    $plugins['media'] = array(
      'path' => $editor['library path'] . '/plugins/media',
      'buttons' => array('media' => t('Media')),
      'url' => 'http://www.tinymce.com/wiki.php/Plugin:media',
      'internal' => TRUE,
      'load' => TRUE,
    );
    $plugins['xhtmlxtras'] = array(
      'path' => $editor['library path'] . '/plugins/xhtmlxtras',
      'buttons' => array('cite' => t('Citation'), 'del' => t('Deleted'), 'abbr' => t('Abbreviation'), 'acronym' => t('Acronym'), 'ins' => t('Inserted'), 'attribs' => t('HTML attributes')),
      'url' => _wysiwyg_tinymce_get_plugin_url('xhtmlxtras'),
    );
  }
  if (version_compare($editor['installed version'], '3.2.5', '>=')) {
    $plugins['autoresize'] = array(
      'extensions' => array('autoresize' => t('Auto resize')),
      'url' => _wysiwyg_tinymce_get_plugin_url('autoresize'),
    );
    if (version_compare($editor['installed version'], '3.2.6', '>=')) {
      $plugins['wordcount'] = array(
        'extensions' => array('wordcount' => t('Word count')),
        'url' => _wysiwyg_tinymce_get_plugin_url('wordcount'),
      );
      if (version_compare($editor['installed version'], '3.3', '>=')) {
        unset($plugins['safari']);
        $plugins['advlist'] = array(
          'extensions' => array('advlist' => t('Advanced list')),
          'url' => _wysiwyg_tinymce_get_plugin_url('advlist'),
        );
        if (version_compare($editor['installed version'], '3.4.1', '>=')) {
          $plugins['lists'] = array(
            'extensions' => array('lists' => t('List normalizer')),
            'url' => 'http://www.tinymce.com/wiki.php/Plugin:lists',
            'extended_valid_elements' => array(
              'li[class|dir|id|lang|onclick|ondblclick|onkeydown|onkeypress|onkeyup|onmousedown|onmousemove|onmouseout|onmouseover|onmouseup|style|title|type|value]',
              'ol[class|compact|dir|id|lang|onclick|ondblclick|onkeydown|onkeypress|onkeyup|onmousedown|onmousemove|onmouseout|onmouseover|onmouseup|start|style|title|type]',
              'ul[class|compact|dir|id|lang|onclick|ondblclick|onkeydown|onkeypress|onkeyup|onmousedown|onmousemove|onmouseout|onmouseover|onmouseup|style|title|type]',
            ),
          );
          if (version_compare($editor['installed version'], '3.5.b1', '>=')) {
            $plugins['visualblocks'] = array(
              'buttons' => array('visualblocks' => t('Show blocks')),
              'url' => (version_compare($editor['installed version'], '4.0', '>') ? _wysiwyg_tinymce_get_plugin_url('visualblocks') : NULL),
            );
          }
        }
      }
    }
  }
  if (version_compare($editor['installed version'], '4', '>=')) {

    $removed_plugins = array('advhr', 'advimage', 'advlink', 'inlinepopups', 'style', 'emotions', 'xhtmlxtras');
    foreach ($removed_plugins as $plugin) {
      unset($plugins[$plugin]);
    }
    $removed_default_buttons = array('link', 'unlink', 'anchor', 'image', 'justifyleft', 'justifycenter', 'justifyright', 'justifyfull', 'forecolor', 'backcolor', 'sup', 'sub', 'code', 'charmap', 'cleanup', 'hr');
    foreach ($removed_default_buttons as $button) {
      unset($plugins['default']['buttons'][$button]);
    }

    unset($plugins['insertdatetime']['buttons']['insertdate']);

    $plugins['paste']['buttons'] = array(
      'pastetext' => t('Paste text'),
    );
    unset($plugins['paste']['buttons']['pasteword']);
    $plugins['searchreplace']['buttons'] = array(
      'searchreplace' => t('Search & Replace'),
    );
    $plugins['table']['buttons'] = array(
      'table' => t('table'),
    );

    $plugins['hr'] = array(
      'buttons' => array('hr' => t('Insert horizontal rule')),
      'extended_valid_elements' => array('hr[class|width|size|noshade]'),
      'url' => _wysiwyg_tinymce_get_plugin_url('hr'),
    );
    $plugins['charmap'] = array(
      'buttons' => array('charmap' => t('Insert special character')),
      'url' => _wysiwyg_tinymce_get_plugin_url('charmap'),
    );
    $plugins['anchor'] = array(
      'buttons' => array('anchor' => t('Insert anchor/bookmark')),
      'url' => _wysiwyg_tinymce_get_plugin_url('anchor'),
    );
    $plugins['image'] = array(
      'buttons' => array('image' => t('Insert image')),
      'url' => _wysiwyg_tinymce_get_plugin_url('image'),
    );
    $plugins['link'] = array(
      'buttons' => array('link' => t('Insert link'), 'unlink' => t('Remove link')),
      'url' => _wysiwyg_tinymce_get_plugin_url('link'),
    );
    $plugins['emoticons'] = array(
      'buttons' => array('emoticons' => t('Insert emoticons')),
      'url' => _wysiwyg_tinymce_get_plugin_url('emoticons'),
    );
    $plugins['code'] = array(
      'buttons' => array('code' => t('Source code')),
      'url' => _wysiwyg_tinymce_get_plugin_url('code'),
    );
    $plugins['textcolor'] = array(
      'buttons' => array('forecolor' => t('Text color'), 'backcolor' => t('Background color')),
      'url' => _wysiwyg_tinymce_get_plugin_url('textcolor'),
    );
    $plugins['default']['buttons'] += array(
      'subscript' => t('Subscript'), 'superscript' => t('Superscript'),
      'alignleft' => t('Align left'), 'aligncenter' => t('Align center'),
      'alignright' => t('Align right'), 'alignjustify' => t('Justify'),
      'selectall' => t('Select all')
    );

    if (version_compare($editor['installed version'], '4.3.0', '>=')) {
      $plugins['codesample'] = array(
        'buttons' => array('codesample' => t('Insert/edit code sample')),
        'url' => _wysiwyg_tinymce_get_plugin_url('codesample'),
      );
    }
    if (version_compare($editor['installed version'], '4.5.0', '>=')) {
      $plugins['toc'] = array(
        'buttons' => array('toc' => t('Table of Contents')),
        'url' => _wysiwyg_tinymce_get_plugin_url('toc'),
      );
      // The list buttons now require the lists plugin.
      $plugins['lists']['buttons'] = array('bullist' => t('Unordered list'), 'numlist' => t('Ordered list'));
      unset($plugins['default']['buttons']['bullist'], $plugins['default']['buttons']['numlist']);
    }
  }

  foreach ($plugins as &$plugin) {
    // All the plugins are internal and need explicit loading.
    $plugin['internal'] = TRUE;
    $plugin['load'] = TRUE;
  }
  $plugins['default']['load'] = FALSE;
  return $plugins;
}

/**
 * Helper to get the URL for a plugin.
 *
 * @param $plugin_name
 *   Internal name of the plugin.
 */
function _wysiwyg_tinymce_get_plugin_url($plugin_name) {
  static $is_v3 = NULL;
  if (!isset($is_v3)) {
    $is_v3 = _wysiwyg_tinymce_is_v3();
  }
  return ($is_v3 ? "https://www.tinymce.com/docs-3x/reference/plugins/Plugin3x@$plugin_name/" : "https://www.tinymce.com/docs/plugins/$plugin_name/");
}

/**
 * Helper to get the URL for a plugin settings.
 *
 * @param $plugin_name
 *   Internal name of the plugin.
 * @param $setting_name
 *   Internal name of the setting.
 */
function _wysiwyg_tinymce_get_plugin_setting_description($plugin_name, $setting_name) {
  static $is_v3 = NULL;
  if (!isset($is_v3)) {
    $is_v3 = _wysiwyg_tinymce_is_v3();
  }
  return t('Uses the <a href="@url">@setting</a> setting internally.', array(
    '@setting' => $setting_name,
    '@url' => _wysiwyg_tinymce_get_plugin_url($plugin_name) . ($is_v3 ? '' : "#$setting_name"),
  ));
}

/**
 * Helper to get the URL for a general setting.
 *
 * @param $setting_name
 *   Internal name of the setting.
 */
function _wysiwyg_tinymce_get_setting_description($setting_name, $section_name = NULL) {
  static $is_v3 = NULL;
  if (!isset($is_v3)) {
    $is_v3 = _wysiwyg_tinymce_is_v3();
  }
  return t('Uses the <a href="@url">@setting</a> setting internally.', array(
    '@setting' => $setting_name,
    '@url' => ($is_v3 ? url("https://www.tinymce.com/docs-3x/reference/configuration/Configuration3x@$setting_name/")
      : url("https://www.tinymce.com/docs/configure/$section_name/#$setting_name")),
  ));
}

/**
 * Check if the installed major version is 3.
 *
 * @return bool
 *   TRUE if the installed major version is 3.
 */
function _wysiwyg_tinymce_is_v3() {
  static $is_v3 = NULL;
  if (!isset($is_v3)) {
    $editor = wysiwyg_get_editor('tinymce');
    if (!empty($editor['installed version'])) {
      $is_v3 = version_compare($editor['installed version'], '4.0.0', '<');
    }
    else {
      $is_v_3 = FALSE;
    }
  }
  return $is_v3;
}

/**
 * Helper for converting plugins and buttons between TinyMCE 3 and 4.
 */
function _wysiwyg_tinymce_3_to_4_plugin_remap($plugin, $button) {
  switch ($button) {
    case 'link':
    case 'unlink':
      return array('link', $button);
    case 'justifyleft':
      return array('default', 'alignleft');
    case 'justifyright':
      return array('default', 'alignright');
    case 'justifycenter':
      return array('default', 'aligncenter');
    case 'justifyfull':
      return array('default', 'alignjustify');
    case 'anchor':
    case 'image':
    case 'code':
    case 'charmap':
    case 'cleanup':
    case 'hr':
      return array($button, $button);
    case 'forecolor':
    case 'backcolor':
      return array('textcolor', $button);
    case 'search':
    case 'replace':
      return array('searchreplace', 'searchreplace');
    case 'emotions':
      return array('emoticons', 'emoticons');
    case 'sup':
      return array('default', 'superscript');
    case 'sub':
      return array('default', 'subscript');
    case 'selectall':
      return array('default', 'selectall');
    case 'tablecontrols':
      return array('table', 'table');
    case 'pasteword':
      return array('paste', 'paste');
    default:
      return array($plugin, $button);
  }
}

/**
 * Helper for converting plugins and buttons between TinyMCE 4 and 3.
 */
function _wysiwyg_tinymce_4_to_3_plugin_remap($plugin, $button) {
  switch ($button) {
    case 'link':
    case 'unlink':
    case 'anchor':
    case 'image':
    case 'code':
    case 'charmap':
    case 'cleanup':
    case 'hr':
      return array('default', $button);
    case 'alignleft':
      return array('default', 'justifyleft');
    case 'alignright':
      return array('default', 'justifyright');
    case 'aligncenter':
      return array('default', 'justifycenter');
    case 'alignjustify':
      return array('default', 'justifyfull');
    case 'forecolor':
    case 'backcolor':
      return array('default', $button);
    case 'searchreplace':
      return array(array('searchreplace', 'search'), array('searchreplace', 'replace'));
    case 'emoticons':
      return array('emotions', 'emotions');
    case 'superscript':
      return array('default', 'sup');
    case 'subscript':
      return array('default', 'sub');
    case 'selectall':
      return array('paste', 'selectall');
    case 'table':
      return array(array('table', 'table'), array('table', 'tablecontrols'));
    default:
      return array($plugin, $button);
  }
}
