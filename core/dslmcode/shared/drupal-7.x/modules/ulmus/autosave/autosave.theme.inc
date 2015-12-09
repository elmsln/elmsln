<?php
/**
 * Theme related fuctions.
 */

/**
 * Implements hook_theme().
 */
function autosave_theme() {
  return array(
    // Keys in 'autosave' are: form_id, url, period, timeout,
    // q, hidden, theme, savedTimestamp, savedDate, form_token. There's
    // no access check, watch out what these theme functions return!
    'autosave_saved_popup' => array(
      'template' => 'autosave_saved_popup',
      'path' => drupal_get_path('module', 'autosave'),
      'variables' => array(
        'autosave' => array(),
      ),
    ),
    'autosave_restore_popup' => array(
      'template' => 'autosave_restore_popup',
      'path' => drupal_get_path('module', 'autosave'),
      'variables' => array(
        'autosave' => array(),
      ),
    ),
  );
}

/**
 * Theme preprocess function.
 */
function autosave_preprocess_autosave_restore_popup(&$vars) {
  $options = array(
    'external' => TRUE, // Needed for an empty anchor without a beginning slash.
    'fragment' => FALSE, // Needed for an empty anchor
    'attributes' => array(
      'class' => array(
        'ignore-link',
       ),
      'title' => t('Ignore/Delete saved form'),
     ),
   );
  $vars['ignore_link'] = l(t('Ignore'), NULL, $options);

  $options = array(
    'attributes' => array(
      'class' => array(
        'use-ajax',
        'restore-link'
       ),
      'title' => t('Restore saved form'),
     ),
  );
  $callback_path = 'autosave/restore/' . $vars['autosave']['form_id'] . '/' . $vars['autosave']['savedTimestamp'] . '/' . $vars['autosave']['form_token'] . '/' . $vars['autosave']['theme'];
  $vars['restore_link'] = l(t('Restore'), $callback_path, $options);
}

/**
 * Delivery callback.
 */
function autosave_delivery_callback($page_callback_result) {
  print $page_callback_result;
}

/**
 * Menu pages callback.
 */
function autosave_popup($theme) {
  if (in_array($theme, array('autosave_saved_popup', 'autosave_restore_popup'))) {
    return theme($theme, array('autosave' => $_POST));
  }
}

/**
 * Menu access callback.
 *
 * Mostly autosave_save_access().
 */
function autosave_popup_access() {
  $form_id = str_replace('-', '_', $_POST['form_id']);
  $token = isset($_POST['form_token'], $form_id) && drupal_valid_token($_POST['form_token'], $form_id);
  // If we are just about to show the Form autosaved popup, it's
  // enough to verify the form token. We don't know the form path anyway.
  if ($_GET['q'] == 'autosave/popup/autosave_saved_popup') {
    return $token;
  }

  $_POST['autosave_form_path'] = $_POST['q'];
  $path = $_POST['q'];
  $menu_item = autosave_menu_get_item($path);
  $menu = isset($menu_item['access']) ? $menu_item['access'] : FALSE;

  return $token && $menu;
}
