<?php
/**
 * @file
 * Declare and handle FontFolio specific theme settings
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @TODO
 *   Add validation to Css color value
 */
function fontfolio_form_system_theme_settings_alter(&$form, $form_state) {

  // fontfolio theme settings section (fieldset).
  $form['fontfolio'] = array(
    '#type'        => 'vertical_tabs',
    '#title'       => t('FontFolio theme settings'),
    '#description' => t('Layout'),
    '#weight'      => -10,
    // Attach fontfolio custom Css file - to be used when extending and
    // beautifying the theme-settings form.
    '#attached'    => array(
      'css' => array(drupal_get_path('theme', 'fontfolio') . '/styles/ff.settings.form.css'),
    ),
  );
  
  // Social Urls.
  $form['fontfolio']['general'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('General'),
    '#collapsible' => TRUE,
  );
  
  // Show/Hide page titles on taxonomy term pages. 
  $form['fontfolio']['general']['hide_page_tile'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Hide page title on Taxonomy term pages'),
    '#default_value' => theme_get_setting('hide_page_tile'),
    '#description'   => t("By default, In fontfolio theme, we don't display the page title on taxonomy term pages. If you want to display The title uncheck this checkbox."),
  );
  
  $form['fontfolio']['general']['show_lang_links'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Multilingual - Display languages links in Main menu'),
    '#default_value' => theme_get_setting('show_lang_links'),
    '#description'   => t("By default, FontFolio dispalys in main menu link to homepage of each enabled language. Uncheck this checkbox and Language links will not auto displayed."),
  );
  
  /* Temporary commented out the background-color option
   *  @TODO integrate more complete solution using the Color module
   *  while supplying few pre configured color schemes
   
  // Body background color. 
  $form['fontfolio']['general']['body_bg_color'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Background Color'),
    '#default_value' => theme_get_setting('body_bg_color'),
    '#description'   => t('Optionaly: set CSS background-color for whole page. Use valid css colors'),
  );
  */ // End temp commented out bg-color

  // Social Urls.
  $form['fontfolio']['social'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Social Media URLs'),
    '#collapsible' => TRUE,
  );

  $form['fontfolio']['social']['facebook'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Facebook Link'),
    '#default_value'    => theme_get_setting('facebook'),
    '#description'      => t('Your Facebook page link'),
    '#element_validate' => array('fontfolio_social_url_validate'),
  );

  $form['fontfolio']['social']['twitter'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Twitter Link'),
    '#default_value' => theme_get_setting('twitter'),
    '#description'   => t('Your Twitter page link'),
    '#element_validate' => array('fontfolio_social_url_validate'),
  );

  $form['fontfolio']['social']['dribble'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Dribble Link'),
    '#default_value' => theme_get_setting('dribble'),
    '#description'   => t('Your Dribble page link'),
    '#element_validate' => array('fontfolio_social_url_validate'),
  );

  $form['fontfolio']['social']['plus'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Google+ Link'),
    '#default_value' => theme_get_setting('plus'),
    '#description'   => t('Your Google+ page link'),
    '#element_validate' => array('fontfolio_social_url_validate'),
  );
}

/**
 * Validate social urls with valid_url();
 */
function fontfolio_social_url_validate($element, &$form_state, $form) {
  if ($element['#value'] && !valid_url($element['#value'], TRUE)) {
    form_set_error($element['#name'], t('The @social_url is not valid URL. Please try to copy/paste it one more time.', array('@social_url' => $element['#title'])));
  }
}
