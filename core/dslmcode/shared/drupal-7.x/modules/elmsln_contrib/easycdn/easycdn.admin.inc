<?php
/**
 * @file
 * EasyCDN administration UI.
 */

/**
 * Form definition; general settings.
 */
function easycdn_admin_general_settings_form($form, &$form_state) {
  $form = array();
  $rows = array();
  $header = array();
  $versions = array();
  $cdnjs_format_versions = array();
  $jsdelivr_format_versions = array();
  $libraries = libraries_detect();
  foreach ($libraries as $machine_name => $library) {
    array_push($header, $libraries[$machine_name]['machine name']);
    $versions = getVersions($libraries[$machine_name]['machine name']);
    $form['easycdn']['explanation'] = array(
      '#title' => t('Choose from the libraries below and adjust its settings to choose to serve its files from a cdn or locally.'),
      );
    $form['easycdn'][$machine_name] = array(
      '#type' => 'fieldset',
      '#title' => t($machine_name),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      );
      
    $form['easycdn'][$machine_name]['easycdn_cdn_' . $machine_name] = array(
      '#title' => t('CDN Choice'),
      '#type' => 'select',
      '#options' => array(
        'CDN_NONE' => t('Local'),
        'CDN_JSDELIVR' => t('jsDelivr (Supported in China)'),
        'CDN_CDNJS' => t('CDNJS (Limited China Support)'),
        'RAWGIT' => t('RawGit'),
        ),
      '#default_value' => variable_get('easycdn_cdn_' . $machine_name, ''),
    );
    $form['easycdn'][$machine_name]['easycdn_version_' . $machine_name] = array(
      '#title' => t('Version'),
      '#type' => 'select',
      '#default_value' => variable_get('easycdn_version_'. $machine_name, ''),
    );
    if (variable_get('easycdn_cdn_' . $libraries[$machine_name]['machine name']) === 'CDN_JSDELIVR'){
      $jsdelivr_format_versions = $versions;
      $form['easycdn'][$machine_name]['easycdn_version_' . $machine_name]['#options'] = $jsdelivr_format_versions;
    }
    elseif (variable_get('easycdn_cdn_' . $libraries[$machine_name]['machine name']) === 'CDN_CDNJS'){
      // Push the local version first so we never have a blank array
      $jsdelivr_format_versions = $versions;
      foreach ($versions as $version => $value) {
        array_push($cdnjs_format_versions, $versions[$version]['version']);
      }
      $form['easycdn'][$machine_name]['easycdn_version_' . $machine_name]['#options'] = $cdnjs_format_versions;
    }
    elseif (variable_get('easycdn_cdn_' . $libraries[$machine_name]['machine name']) === 'RAWGIT'){
      //version logic for file loading...it'll be ELMS:LN version specific (for now)
      array_push($versions, $libraries[$machine_name]['version'] . ' =  local version');
      $form['easycdn'][$machine_name]['easycdn_version_' . $machine_name]['#options'] = $versions;
    }
    else {
      array_push($versions, $libraries[$machine_name]['version'] . ' =  local version');
      $form['easycdn'][$machine_name]['easycdn_version_' . $machine_name]['#options'] = $versions;
    }
  }
  return system_settings_form($form);
}
