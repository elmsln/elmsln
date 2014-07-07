<?php

/**
 * @file
 * Contains the administrative functions of the EPUB version module.
 *
 * This file is included by the EPUB version module, and includes the
 * settings form.
 *
 * @ingroup print
 */

/**
 * Form constructor for the EPUB version module settings form.
 *
 * @ingroup forms
 */
function print_epub_settings() {
  $epub_tools = array();
  drupal_alter('print_epub_available_libs', $epub_tools);

  if (!empty($epub_tools)) {
    $link = print_epub_print_link();

    $current_epub_tool = variable_get('print_epub_epub_tool', PRINT_EPUB_EPUB_TOOL_DEFAULT);
    $epub_tool_default =  array_key_exists($current_epub_tool, $epub_tools) ? $current_epub_tool : PRINT_EPUB_EPUB_TOOL_DEFAULT;

    $form['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('EPUB options'),
    );

    $form['settings']['print_epub_epub_tool'] = array(
      '#type' => 'radios',
      '#title' => t('EPUB generation tool'),
      '#options' => $epub_tools,
      '#default_value' => $epub_tool_default,
      '#description' => t('This option selects the EPUB generation tool being used by this module to create the EPUB version.'),
    );

    $form['settings']['print_epub_images_via_file'] = array(
      '#type' => 'checkbox',
      '#title' => t('Access images via local file access'),
      '#default_value' => variable_get('print_epub_images_via_file', PRINT_EPUB_IMAGES_VIA_FILE_DEFAULT),
      '#description' => t("Enabling this option will make the tool use local file access for image files. This option is not recommended to use in conjunction with modules like imagecache which generate the image after it's first accessed. However, it may be necessary in low-end hosting services where the web server is not allowed to open URLs and the user can't modify that configuration setting."),
    );

    $form['settings']['print_epub_filename'] = array(
      '#type' => 'textfield',
      '#title' => t('EPUB filename'),
      '#default_value' => variable_get('print_epub_filename', PRINT_EPUB_FILENAME_DEFAULT),
      '#description' => t("If left empty the generated filename defaults to the node's path. Tokens may be used to build the filename (see following list). The .epub extension will be appended automatically."),
    );
    if (module_exists('token')) {
      $form['settings']['print_epub_filename_patterns'] = array(
        '#type' => 'fieldset',
        '#title' => t('Replacement patterns'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['settings']['print_epub_filename_patterns']['descriptions'] = array(
        '#theme' => 'token_tree',
        '#token_types' => array('node'),
      );
    }

    $form['settings']['print_epub_display_sys_urllist'] = array(
      '#type' => 'checkbox',
      '#title' => t('Printer-friendly URLs list in system pages'),
      '#default_value' => variable_get('print_epub_display_sys_urllist', PRINT_TYPE_SYS_URLLIST_DEFAULT),
      '#description' => t('Enabling this option will display a list of printer-friendly destination URLs at the bottom of the page.'),
    );

    $form['settings']['link_text'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom link text'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['settings']['link_text']['print_epub_link_text_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable custom link text'),
      '#default_value' => variable_get('print_epub_link_text_enabled', PRINT_TYPE_LINK_TEXT_ENABLED_DEFAULT),
    );
    $form['settings']['link_text']['print_epub_link_text'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('print_epub_link_text', $link['text']),
      '#description' => t('Text used in the link to the EPUB version.'),
    );

    $form['#validate'][] = '_print_epub_settings_validate';
  }
  else {
    variable_set('print_epub_epub_tool', PRINT_EPUB_EPUB_TOOL_DEFAULT);

    $form['settings'] = array(
      '#type' => 'markup',
      '#markup' => '<p>' . t("No EPUB generation tool found! Please download a supported PHP EPUB generation tool. Check this module's INSTALL.txt for more details.") . '</p>',
    );
  }

  return system_settings_form($form);
}

/**
 * Form validation handler for print_epub_settings().
 *
 * @see print_epub_settings()
 * @ingroup forms
 */
function _print_epub_settings_validate($form, &$form_state) {
  if (empty($form_state['values']['print_epub_epub_tool'])) {
    form_set_error('print_epub_epub_tool', t("No EPUB tool selected"));
  }
}
