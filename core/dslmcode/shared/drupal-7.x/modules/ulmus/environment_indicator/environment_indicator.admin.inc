<?php

/**
 * @file
 * Administrative interface for environment indicator configuration.
 */

/**
 * Module settings form.
 */
function environment_indicator_settings() {
  $form['environment_indicator_suppress_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Turn off Environment Indicator on these pages'),
    '#default_value' => variable_get('environment_indicator_suppress_pages', ""),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );
  $integrations = array(
    'toolbar' => t('Toolbar module'),
    'admin_menu' => t('Admin Menu module'),
    'navbar' => t('Mobile Friendly Navigation Toolbar'),
  );
  $form['environment_indicator_integration'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Integrate with'),
    '#options' => $integrations,
    '#default_value' => variable_get('environment_indicator_integration', array('toolbar' => 'toolbar', 'admin_menu' => 'admin_menu', 'navbar' => 'navbar')),
    '#description' => t("If you integrate with a module that provides a toolbar then that toolbar will be colorized and the environment name added to it instead of adding a new bar."),
  );
  $form['environment_indicator_git_support'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add GIT support'),
    '#description' => t('If this is checked, the GIT branch name will be displayed along with the environment indicator name.'),
    '#default_value' => variable_get('environment_indicator_git_support', TRUE),
  );
  $form['environment_indicator_favicon_overlay'] = array(
    '#type' => 'checkbox',
    '#title' => t("Change the site's favicon for users who can see the environment indicator"),
    '#description' => t('Puts a colored overlay in the bottom-right corner of the favicon, with the first letter of the environment name.'),
    '#default_value' => variable_get('environment_indicator_favicon_overlay', TRUE),
  );
  $form['#submit'][] = 'environment_indicator_settings_submit';
  return system_settings_form($form);
}

/**
 * Submit callback for the environment_indicator_settings form.
 */
function environment_indicator_settings_submit($form, $form_state) {
  if (module_exists('admin_menu')) {
    // Clear admin menu caches.
    admin_menu_flush_caches();
  }
  cache_clear_all('environment_indicator', 'cache');
}
