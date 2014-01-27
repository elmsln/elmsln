<?php

function login_shadowbox_login() {

  _login_shadowbox_js_css();

  // LOGIN FORM BEGIN
  $login_form = '<div id="shadowbox_login" class="shadowbox_login_wrapper">';

  $login_form .= '<button class="shadowbox_login_close_button">x</button>';

  // add login form
  $form = drupal_get_form("user_login");
  $login_form .= drupal_render($form);

  // add the registration and reset password links
  if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
    $items[] = l(t('Create new account'), 'user/register', array('attributes' => array('title' => t('Create a new user account.'))));
  }
  $items[] = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
  $links['links'] = array('#markup' => theme('item_list', array('items' => $items)));
  $login_form .= drupal_render($links);

  $login_form .= '</div>';
  // LOGIN FORM END

  print theme('login_shadowbox_page', array(
    'title'    => 'Login',
    'content'  => $login_form,
  ));

  return NULL;
}

function login_shadowbox_register() {

  _login_shadowbox_js_css();

  // REGISTRATION FORM BEGIN
  $register_form = '<div id="shadowbox_register" class="shadowbox_login_wrapper">';
  $register_form .= '<button class="shadowbox_login_close_button">x</button>';
  if (user_register_access()) $register_form .= drupal_render(drupal_get_form("user_register_form"));
  $register_form .= '</div>';
  // REGISTRATION FORM END

  print theme('login_shadowbox_page', array(
    'title'    => 'Registration',
    'content'  => $register_form,
  ));

  return NULL;
}

function login_shadowbox_password() {

  _login_shadowbox_js_css();

  // RESET PASSWORD FORM BEGIN
  module_load_include('inc', 'user', 'user.pages');
  $password_form = '<div id="shadowbox_password" class="shadowbox_login_wrapper">';
  $password_form .= '<button class="shadowbox_login_close_button">x</button>';
  $password_form .= drupal_render(drupal_get_form("user_pass"));
  $password_form .= '</div>';
  // RESET PASSWORD FORM END

  print theme('login_shadowbox_page', array(
    'title'    => 'Registration',
    'content'  => $password_form,
  ));

  return NULL;
}

function _login_shadowbox_js_css() {
  $path = drupal_get_path('module', 'login_shadowbox');
  $css_path = variable_get('login_shadowbox_css', $path . '/css/login_shadowbox.css');
  drupal_add_css($css_path, array('group' => 'CSS_DEFAULT'));
  drupal_add_js($path . '/scripts/login_shadowbox_messages.js');
}
