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
    $vars['photo'] = '<img src="' . base_path() . drupal_get_path('theme', 'foundation_access') . '/img/user.png" class="ferpa-protect circle" />';
  }
  if (!empty($vars['field_user_banner'])) {
    $vars['banner'] = $vars['user_profile']['field_user_banner'];
  }
  else {
    $vars['banner'] = '<img class="background" src="http://materializecss.com/images/office.jpg" alt="">';
  }
}