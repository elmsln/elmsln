<?php

/**
 * Implements template_preprocess_user_profile.
 */
function cpr_foundation_access_preprocess_user_profile(&$vars) {
  $vars['displayname'] = '';
  if (isset($vars['field_first_name'][0]['safe_value'])) {
    $vars['displayname'] .= $vars['field_first_name'][0]['safe_value'] . ' ';
  }
  if (isset($vars['field_last_name'][0]['safe_value'])) {
    $vars['displayname'] .= $vars['field_last_name'][0]['safe_value'];
  }
  if (isset($vars['field_display_name'][0]['safe_value'])) {
    $vars['displayname'] .= ' | ' . $vars['field_display_name'][0]['safe_value'];
  }
  if (empty($vars['displayname'])) {
    $vars['displayname'] = $vars['user_name'];
  }
  if (!empty($vars['field_user_photo'])) {
    $vars['field_user_photo'][0]['attributes'] = array(
      'class' => array('circle', 'ferpa-protect'),
    );
    $vars['field_user_photo'][0]['alt'] = t('Picture of @name', array('@name' => $vars['displayname']));
    $vars['field_user_photo'][0]['path'] = $vars['field_user_photo'][0]['uri'];
    $vars['photo'] = theme('image', $vars['field_user_photo'][0]);
  }
  else {
    $photolink = url(drupal_get_path('theme', 'foundation_access') . '/img/user.png', array('absolute' => TRUE));
    $vars['photo'] = '<img src="' . $photolink . '" class="ferpa-protect circle" />';
  }
  if (!empty($vars['field_user_banner'])) {
    $vars['banner'] = $vars['user_profile']['field_user_banner'][0];
  }
  else {
    $vars['banner'] = '<img class="background" src="http://materializecss.com/images/office.jpg" alt="">';
  }
  // load up related user data
  $blockObject = block_load('elmsln_core', 'elmsln_core_user_xapi_data');
  $vars['user_data'] = _block_get_renderable_array(_block_render_blocks(array($blockObject)));
  // load bio in
  $bio = '';
  if (isset($vars['user_profile']['field_bio'])) {
    $bio = $vars['user_profile']['field_bio'];
  }
  $vars['tabs'] = array(
    'bio' => t('About'),
    'xapidata' => t('Activity data'),
  );
  $vars['tabs_content'] = array(
    'bio' => $bio,
    'xapidata' => $vars['user_data'],
  );
}