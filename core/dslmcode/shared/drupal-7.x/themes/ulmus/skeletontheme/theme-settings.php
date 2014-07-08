<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function skeletontheme_form_system_theme_settings_alter(&$form, &$form_state) {

  $form['mtt_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Skeleton Theme Settings'),
    '#collapsible' => FALSE,
	'#collapsed' => FALSE,
  );

  $form['mtt_settings']['tabs'] = array(
    '#type' => 'vertical_tabs',
  );

 $form['mtt_settings']['tabs']['responsive_menu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Responsive menu'),
    '#collapsible' => TRUE,
	'#collapsed' => TRUE,
  );
  
 $form['mtt_settings']['tabs']['responsive_menu']['responsive_menu_state'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable responsive menu'),
  	'#description'   => t('Use the checkbox to enable the plugin which transforms the Main menu of your site to a dropdown select list when your browser is at mobile widths.'),
	'#default_value' => theme_get_setting('responsive_menu_state', 'skeletontheme'),
  );
  
 $form['mtt_settings']['tabs']['responsive_menu']['responsive_menu_switchwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Switch width (px)'),
  	'#description'   => t('Set the width (in pixels) at which the Main menu of the site will change to a dropdown select list.'),
	'#default_value' => theme_get_setting('responsive_menu_switchwidth', 'skeletontheme'),
  );
  
  $form['mtt_settings']['tabs']['responsive_menu']['responsive_menu_topoptiontext'] = array(
    '#type' => 'textfield',
    '#title' => t('Top option text'),
  	'#description'   => t('Set the very first option display text.'),
	'#default_value' => theme_get_setting('responsive_menu_topoptiontext', 'skeletontheme'),
  );
  
}