<?php

/**
 * @file
 * Provides form for changing settings
 */

/**
 * Implementation of the former hook_settings().
 */
function expire_admin_settings_form() {
  drupal_set_title(t('Cache Expiration'));
  $form['expire'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('What to expire'),
  );

  $form['expire']['expire_flush_front'] = array(
    '#type'        => 'checkbox',
    '#title'       => t('Expire front page'),
    '#default_value' => variable_get('expire_flush_front', EXPIRE_FLUSH_FRONT),
    '#description'   => t('When expiring a node: if promoted to front page, expire front page.'),
  );

  if (module_exists('taxonomy')) {
    $form['expire']['expire_flush_node_terms'] = array(
      '#type'          => 'checkbox',
      '#title'         => t('Expire node term pages'),
      '#default_value' => variable_get('expire_flush_node_terms', EXPIRE_FLUSH_NODE_TERMS),
      '#description'   => t('When expiring a node: expire taxonomy pages for its terms.'),
    );
  }

  if (module_exists('menu')) {
    $form['expire']['expire_flush_menu_items'] = array(
      '#type'          => 'radios',
      '#title'         => t('Expire menus'),
      '#options'       => array(0 => t('No'), EXPIRE_FLUSH_MENU_ITEMS => t('Family'), 2 => t('Entire menu')),
      '#default_value' => variable_get('expire_flush_menu_items', EXPIRE_FLUSH_MENU_ITEMS),
      '#description'   => t('When expiring a node: expire related menu items or entire menu'),
    );
  }

  if (module_exists('node_reference')) {
    $form['expire']['expire_flush_node_references'] = array(
      '#type'          => 'checkbox',
      '#title'         => t('Expire node references'),
      '#default_value' => variable_get('expire_flush_node_references', EXPIRE_FLUSH_NODE_REFERENCES),
      '#description'   => t('When expiring a node: expire its node references and nodes containing it in their own node references.'),
    );
  }

  $form['format'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Expire protocol'),
  );

  $form['format']['expire_include_base_url'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Include base URL in expires'),
    '#default_value' => variable_get('expire_include_base_url', EXPIRE_INCLUDE_BASE_URL),
    '#description'   => t('Include the base URL in expire requests. Compatible with Domain Access'),
  );

  return system_settings_form($form);
}
