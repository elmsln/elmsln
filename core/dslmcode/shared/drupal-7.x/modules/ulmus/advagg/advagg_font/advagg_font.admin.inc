<?php

/**
 * @file
 * Admin page callbacks for the advagg font module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_font_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Async Font Loader'));
  advagg_display_message_if_requirements_not_met();
  $form = array();

  $library = advagg_get_library('fontfaceobserver', 'advagg_font');
  $version = advagg_get_remote_libraries_version('fontfaceobserver', $library);
  $options = array(
    0 => t('Disabled'),
    6 => t('Externally load the latest from github (version: @version)', array('@version' => $version)),
  );
  $description = t('This will use the fallback font until the font has been downloaded. See <a href="@link">fontfaceobserver</a> for more info.', array(
    '@link' => $library['vendor url'],
  ));
  if (function_exists('libraries_info')) {
    if ($library['installed']) {
      $options += array(
        2 => t('Inline javascript (version: @version)', array('@version' => $library['version'])),
        4 => t('Local file included in aggregate (version: @version)', array('@version' => $library['version'])),
      );
    }
    elseif (!is_readable('sites/all/libraries/fontfaceobserver/fontfaceobserver.js')) {
      $description .= ' ' . t('To use fontfaceobserver locally fontfaceobserver needs to be placed inside the sites/all/libraries directory so sites/all/libraries/fontfaceobserver/fontfaceobserver.js and package.json can be found at that location.', array(
        '@url' => 'https://www.drupal.org/project/libraries',
      ));
    }
    else {
      $description .= ' ' . t('Go to the <a href="@url">library report page</a> and make sure fontfaceobserver is installed correctly.', array(
        '@url' => url('admin/reports/libraries'),
      ));
    }
  }
  elseif (is_readable('sites/all/libraries/fontfaceobserver/fontfaceobserver.js')) {
    $description .= ' ' . t('To use fontfaceobserver locally the <a href="@url">libraries api module</a> needs to be installed.', array(
      '@url' => 'https://www.drupal.org/project/libraries',
    ));
  }
  else {
    $description .= ' ' . t('To use fontfaceobserver locally the <a href="@url">libraries api module</a> needs to be installed and then fontfaceobserver needs to be placed inside the sites/all/libraries directory so sites/all/libraries/fontfaceobserver/fontfaceobserver.js and package.json can be found at that location.', array(
      '@url' => 'https://www.drupal.org/project/libraries',
    ));
  }

  ksort($options);
  $form['advagg_font_fontfaceobserver'] = array(
    '#type' => 'radios',
    '#title' => t('Use font face observer to load fonts asynchronously.'),
    '#default_value' => variable_get('advagg_font_fontfaceobserver', ADVAGG_FONT_FONTFACEOBSERVER),
    '#options' => $options,
    '#description' => $description,
  );

  $form['container'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        ':input[name="advagg_font_fontfaceobserver"]' => array('value' => '0'),
      ),
    ),
  );
  $form['container']['advagg_font_storage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use localStorage so the flash of unstyled text (FOUT) only happens once.'),
    '#default_value' => variable_get('advagg_font_storage', ADVAGG_FONT_STORAGE),
    '#description' => t('Data is stored in localStorage under advagg_fonts. If this is a problem you can disable localStorage from being used; if doing so the FOUT (Flash of Unstyled Text) will happen on every page load if cookies is also not being used.', array('@cookie' => 'advaggfont_pt-sans=PT Sans')),
  );
  $form['container']['advagg_font_cookie'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set a cookie so the flash of unstyled text (FOUT) only happens once.'),
    '#default_value' => variable_get('advagg_font_cookie', ADVAGG_FONT_COOKIE),
    '#description' => t('Cookies are name like <code>@cookie</code>. If this is a problem you can disable cookies from being set; if doing so the FOUT (Flash of Unstyled Text) will happen on every page load if localStorage is also not being used.', array('@cookie' => 'advaggfont_pt-sans=PT Sans')),
  );
  $form['container']['advagg_font_no_fout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prevent the Flash of Unstyled Text.'),
    '#default_value' => variable_get('advagg_font_no_fout', ADVAGG_FONT_NO_FOUT),
    '#description' => t('The font will not be changed unless the browser already has the font downloaded. Font gets downloaded on the first page view.', array('@cookie' => 'advaggfont_pt-sans=PT Sans')),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-font-cookie' => array('checked' => FALSE),
        '#edit-advagg-font-storage' => array('checked' => FALSE),
      ),
    ),
  );

  // Get all css files and scan for quoted fonts.
  $form['fonts'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Async Loaded fonts in CSS'),
    '#description' => t('Assumes quoted fonts will be downloaded and unquoted fonts are fallbacks.'),
  );
  $form['fonts_not_async'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('NOT Async Loaded in CSS'),
    '#description' => t('Assumes quoted fonts will be downloaded and unquoted fonts are fallbacks. If there is no fallback it will apear below.'),
  );
  // Get filename, filename_hash, and changes.
  $results = db_select('advagg_files', 'af')
    ->fields('af', array('filename', 'filename_hash', 'changes'))
    ->condition('filetype', 'css')
    ->orderBy('filename', 'ASC')
    ->execute();
  while ($row = $results->fetchAssoc()) {
    if (!file_exists($row['filename'])) {
      continue;
    }
    // Get the file contents.
    $file_contents = (string) @advagg_file_get_contents($row['filename']);
    // Get font names.
    list($replacements, $fonts_with_no_replacements) = advagg_font_get_replacements_array($file_contents);
    if (!empty($replacements)) {
      $fonts = array();
      foreach ($replacements as $key => $replacement) {
        // Do not display !important after the fallback font name.
        $replacement[5] = str_replace(' !important', '', $replacement[5]);
        $fonts[$key . ' ' . $replacement[3]] = $replacement[5];
      }

      $form['fonts'][$row['filename_hash']] = array(
        '#markup' => '<div>' . t('%file - <code>@replacements</code><br />', array(
          '@replacements' => str_ireplace('array', '', print_r($fonts, TRUE)),
          '%file' => $row['filename'],
        )) . '</div>',
      );
    }
    if (!empty($fonts_with_no_replacements)) {
      $fonts = array();
      foreach ($fonts_with_no_replacements as $key => $replacement) {
        // Do not display !important after the fallback font name.
        $replacement = str_replace(' !important', '', $replacement);
        $fonts[$key . ' ' . $replacement] = $replacement;
      }

      $form['fonts_not_async'][$row['filename_hash']] = array(
        '#markup' => '<div>' . t('%file - <code>@replacements</code><br />', array(
          '@replacements' => str_ireplace('array', '', print_r($fonts, TRUE)),
          '%file' => $row['filename'],
        )) . '</div>',
      );
    }
  }
  $children = element_children($form['fonts']);

  // If no fonts are found; disable this module.
  if (count($children) == 0) {
    $form['advagg_font_fontfaceobserver']['#default_value'] = 0;
    $form['advagg_font_fontfaceobserver']['#disabled'] = TRUE;

    if (empty($results)) {
      $form['fonts'] = array(
        '#type' => 'fieldset',
        '#title' => t('No CSS files have been aggregated.'),
        '#description' => t('You need to enable aggregation. No css files where found in the advagg_files table.'),
      );
    }
    else {
      $form['fonts'] = array(
        '#type' => 'fieldset',
        '#title' => t('No CSS files with external fonts found.'),
        '#description' => t('Currently this module is not doing anything. Recommend uninstalling it as advagg is not processing any css files that use an external font file.'),
      );
    }
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_font_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Submit callback, clear out the advagg cache bin.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_font_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();

  // Disable cookie and local storage if ffo is disabled.
  if (empty($form_state['values']['advagg_font_fontfaceobserver'])) {
    $form_state['values']['advagg_font_cookie'] = 0;
    $form_state['values']['advagg_font_storage'] = 0;
  }
  // Disable no fout if cookies and local storage are disabled.
  if (empty($form_state['values']['advagg_font_cookie'])
    && empty($form_state['values']['advagg_font_storage'])
  ) {
    $form_state['values']['advagg_font_no_fout'] = 0;
  }
}
