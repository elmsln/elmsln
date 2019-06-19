<?php

/**
 * @file
 * Administration functions for UUID Service module.
 */

/**
 * Settings form for UUID Services.
 *
 * @return array
 *   Configuration form structure.
 */
function uuid_services_settings() {
  $form['uuid_services_support_all_entity_types'] = array(
    '#type' => 'checkbox',
    '#title' => t('Support all UUID entity types'),
    '#description' => t('Check this box to automatically provide Services integration for all entity types with UUID support.'),
    '#default_value' => variable_get('uuid_services_support_all_entity_types', FALSE),
  );
  $form['uuid_services_allowed_media_mimes'] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed Media Mime type'),
    '#default_value' => variable_get('uuid_services_allowed_media_mimes', UUID_SERVICES_DEFAULT_ALLOWED_MEDIA_MIMES),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one mime type per line you wish to allow in the system without extension. Example mime type '<em>video/brightcove</em>'."),
  );
  return system_settings_form($form);
}
