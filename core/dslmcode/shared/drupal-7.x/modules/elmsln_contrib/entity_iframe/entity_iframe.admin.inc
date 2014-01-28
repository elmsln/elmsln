<?php
/**
 * @file
 * Administration settings page for entity iframe.
 */

/**
 * Implements hook_admin_settings().
 */
function entity_iframe_admin_settings() {
  $form = array();
  $themes = array();
  // build a list of themes from system data
  $theme_list = system_rebuild_theme_data();
  foreach ($theme_list as &$theme) {
    // skip themes that are marked hidden from usage
    if (!empty($theme->info['hidden'])) {
      continue;
    }
    $themes[$theme->name] = $theme->info['name'];
  }
  $form['entity_iframe_theme'] = array(
    '#type' => 'select',
    '#title' => t('Default iframe theme'),
    '#description' => t('Theme to use when its in iframe'),
    '#default_value' => variable_get('entity_iframe_theme', ENTITY_IFRAME_THEME),
    '#options' => $themes,
  );
  // assemble a list of known entity types
  $type_options = _entity_iframe_entity_types();
  $default_types = variable_get('entity_iframe_types', array_keys($type_options));
  $form['entity_iframe_types_wrapper'] = array(
    '#title' => t('Entity types'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // build checkboxes for the entity types
  $form['entity_iframe_types_wrapper']['entity_iframe_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Entity types'),
    '#description' => t('Show on these entity types.'),
    '#multiple' => TRUE,
    '#options' => $type_options,
    '#default_value' => $default_types,
  );
  $form['bundles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Type bundles'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // helps account for initially unset issue prior to array populated by form save
  $bundle_types = variable_get('entity_iframe_types', $type_options);
  // build a list of possible bundles based on those items currently selected
  foreach ($bundle_types as $key => $selected) {
    if ($selected) { 
      // load listing of field bundles for this type
      $bundles = field_info_bundles($key);
      $bundle_options = array();
      foreach ($bundles as $bundle_machine => $bundle) {
        $label = $bundle_machine;
        // account for 1 to 1 ratio bundles that are fieldable but not bundle-able
        if (isset($bundle['label'])) {
          $label = $bundle['label'];
        }
        $bundle_options[$bundle_machine] = $label;
      }
      // additional wrapper for the bundles to make it cleaner to work with lots of entity types
      $form['bundles']['bundle_wrapper_' . $key] = array(
        '#type' => 'fieldset',
        '#title' => t('@type types', array('@type' => $type_options[$key])),
        '#description' => t('Select the @type types to enable iframe embed on.', array('@type' => $type_options[$key])),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['bundles']['bundle_wrapper_' . $key]['entity_iframe_bundle_' . $key] = array(
        '#type' => 'checkboxes',
        '#title' => $type_options[$key],
        '#description' => t('Show on these entity types.'),
        '#multiple' => TRUE,
        '#options' => $bundle_options,
        '#default_value' => variable_get('entity_iframe_bundle_' . $key, array_keys($bundle_options)),
      );
    }
  }
  $form['entity_iframe_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add Link on entity view'),
    '#description' => t('Show a shortcut link on entity view.'),
    '#default_value' => variable_get('entity_iframe_link', ENTITY_IFRAME_LINK),
  );
  $form['entity_iframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('iframe embed'),
    '#description' => t('Customize the embedded iframe if enabled'),
    '#collapsible' => FALSE,
  );
  $form['entity_iframe']['entity_iframe_embed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Embed code'),
    '#description' => t('Show iframe embed code on entity view.'),
    '#default_value' => variable_get('entity_iframe_embed', ENTITY_IFRAME_EMBED),
  );
  $form['entity_iframe']['entity_iframe_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Default width for the embed code.'),
    '#default_value' => variable_get('entity_iframe_width', ENTITY_IFRAME_WIDTH),
    '#states' => array(
      'visible' => array(
        array(':input[name="entity_iframe_embed"]' => array('checked' => TRUE)),
      ),
    ),
  );
  $form['entity_iframe']['entity_iframe_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('Default height for the embed code.'),
    '#default_value' => variable_get('entity_iframe_height', ENTITY_IFRAME_HEIGHT),
    '#states' => array(
      'visible' => array(
        array(':input[name="entity_iframe_embed"]' => array('checked' => TRUE)),
      ),
    ),
  );
  $form['#submit'][] = 'entity_iframe_admin_settings_submit';
  return system_settings_form($form);
}

/**
 * Form callback for admin_settings.
 */
function entity_iframe_admin_settings_submit($form, &$form_state) {
  // make sure the admin theme is enabled
  $theme = $form_state['values']['entity_iframe_theme'];
  if (!_entity_iframe_theme_exists($theme)) {
    theme_enable(array($theme));
  }
}