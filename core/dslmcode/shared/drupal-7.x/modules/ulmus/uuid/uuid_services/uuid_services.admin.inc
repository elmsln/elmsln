<?php

/**
 * Settings form for UUID Services.
 */
function uuid_services_settings() {
  $form['uuid_services_support_all_entity_types'] = array(
    '#type' => 'checkbox',
    '#title' => t('Support all UUID entity types'),
    '#description' => t('Check this box to automatically provide Services integration for all entity types with UUID support.'),
    '#default_value' => variable_get('uuid_services_support_all_entity_types', FALSE),
  );
  return system_settings_form($form);
}
