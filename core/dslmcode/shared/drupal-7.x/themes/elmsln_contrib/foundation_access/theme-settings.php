<?php
/**
 * Implements hook_form_FORM_ID_alter().
 */
function foundation_access_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['zurb_foundation']['foundation_access'] = array(
    '#type' => 'fieldset',
    '#title' => t('Foundation Access'),
  );
  // system label
  $distro = variable_get('install_profile', 'standard');
  $reg = _cis_connector_build_registry($distro);
  $system = theme_get_setting('foundation_access_system_label');
  $form['zurb_foundation']['foundation_access']['foundation_access_system_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Service label'),
    '#description' => t('The name displayed at the top left to indicate to users what system they are using. Defaults to the one provided by the registry.'),
    '#default_value' => (empty($system) ? $reg['default_title'] : $system),
  );
  // allow for jquery colorpicker selection widget
  if (module_exists('jquery_colorpicker')) {
    $fieldtype = 'jquery_colorpicker';
  }
  else {
    $fieldtype = 'textfield';
  }
  $form['zurb_foundation']['foundation_access']['foundation_access_primary_color'] = array(
    '#type' => $fieldtype,
    '#size' => 6,
    '#maxlength' => 6,
    '#title' => t('Primary Color'),
    '#description' => t('Primary color to apply throughout the system'),
    '#default_value' => theme_get_setting('foundation_access_primary_color'),
    '#id' => 'foundation_access_primary_color',
    '#suffix' => '<div>' . l(t('Clear'), '#', array('html' => TRUE, 'attributes' => array('onclick' => 'jQuery(\'#foundation_access_primary_color\').val(\'\'); jQuery(\'#foundation_access_primary_color\').parents(\'.color_picker\').css("backgroundColor", "#FFF"); return false'))) . '</div>',
  );
  $form['zurb_foundation']['foundation_access']['foundation_access_secondary_color'] = array(
    '#type' => $fieldtype,
    '#size' => 6,
    '#maxlength' => 6,
    '#title' => t('Secondary Color'),
    '#description' => t('A Secondary color to apply throughout the system'),
    '#default_value' => theme_get_setting('foundation_access_secondary_color'),
    '#id' => 'foundation_access_secondary_color',
    '#suffix' => '<div>' . l(t('Clear'), '#', array('html' => TRUE, 'attributes' => array('onclick' => 'jQuery(\'#foundation_access_secondary_color\').val(\'\'); jQuery(\'#foundation_access_secondary_color\').parents(\'.color_picker\').css("backgroundColor", "#FFF"); return false'))) . '</div>',
  );
  $form['zurb_foundation']['foundation_access']['foundation_access_required_color'] = array(
    '#type' => $fieldtype,
    '#size' => 6,
    '#maxlength' => 6,
    '#title' => t('Required Color'),
    '#description' => t('Tasks and lists that are required will pick up this color'),
    '#default_value' => theme_get_setting('foundation_access_required_color'),
    '#id' => 'foundation_access_required_color',
    '#suffix' => '<div>' . l(t('Clear'), '#', array('html' => TRUE, 'attributes' => array('onclick' => 'jQuery(\'#foundation_access_required_color\').val(\'\'); jQuery(\'#foundation_access_required_color\').parents(\'.color_picker\').css("backgroundColor", "#FFF"); return false'))) . '</div>',
  );
  $form['zurb_foundation']['foundation_access']['foundation_access_optional_color'] = array(
    '#type' => $fieldtype,
    '#size' => 6,
    '#maxlength' => 6,
    '#title' => t('Optional Color'),
    '#description' => t('Tasks and lists that are optional will pick up this color'),
    '#id' => 'foundation_access_optional_color',
    '#suffix' => '<div>' . l(t('Clear'), '#', array('html' => TRUE, 'attributes' => array('onclick' => 'jQuery(\'#foundation_access_optional_color\').val(\'\'); jQuery(\'#foundation_access_optional_color\').parents(\'.color_picker\').css("backgroundColor", "#FFF"); return false'))) . '</div>',
  );
  $form['zurb_foundation']['foundation_access']['foundation_access_logo_options'] = array(
    '#type' => 'radios',
    '#options' => array(
      'fullwidth' => 'Full Width',
      'left' => 'Left',
      'center' => 'Center',
      'right' => 'Right',
    ),
    '#title' => t('Logo Style Options'),
    '#description' => t('Choose a logo style that you prefer.'),
    '#default_value' => theme_get_setting('foundation_access_logo_options'),
  );
}