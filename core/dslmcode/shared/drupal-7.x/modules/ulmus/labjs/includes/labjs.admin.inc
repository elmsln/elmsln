<?php
/**
 * @file
 *   LABjs module admin settings
 */

/**
 * Form for configuring the module.
 */
function labjs_admin_settings_form() {
  $form = array();

  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page specific LABjs settings'),
    '#collapsible' => TRUE,
  );
  $form['pages']['labjs_pages_choice'] = array(
    '#type' => 'radios',
    '#title' => t('Enable LABjs on specific pages'),
    '#options' => array(t('Enable on every page except the listed pages.'), t('Enable on only the listed pages.')),
    '#default_value' => variable_get('labjs_pages_choice', 0),
  );
  $form['pages']['labjs_pages_list'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#default_value' => variable_get('labjs_pages_list', ''),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  return system_settings_form($form);
}