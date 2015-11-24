<?php

define('EC_DRUPAL_VERSION', 7);

/***************************************************************
 * D7 VERSION 
 ***************************************************************/

function _dcf_hook_boot($module) {
  return true;
}

function _dcf_hook_init($module) {
  return true;
}
  
function _dcf_hook_menu($items, $maycache) {
  return $items;
}

function _dcr_render_array($output) {
  return $output;
}

function _dcr_form(&$form) {
  return $form;
}

function _dcf_internal_path($path) {
  return $path;
}

function _dcf_t($string) {
  return $string;
}

function _dco_watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL) { // WARN d7 changed WATCHDOG_ costants
  return watchdog($type, $message, $variables, $severity, $link);
}

function _dco_l($text, $path, array $options = array()) {
  return l($text, $path, $options);
}

function _dcf_form_validate(&$form, &$form_state) {
  return array('form' => &$form, 'form_state' => &$form_state);
}

function _dco_theme($name, $args) {
  return theme($name, $args);
}

function _dcf_theme_signature($args) {
  return array();
}

function _dcr_hook_theme($specs) { 
  return $specs;
}

function _dcf_theme_form(&$args) {
  return array( 'variables' => $args );
}

/***************************************************************
 * D7 EXTRA FUNCTIONS 
 ***************************************************************/

function drupal_module_get_min_weight($except_module = false) {
  return !$except_module ? db_query("select min(weight) from {system}")->fetchField() :
    db_query("select min(weight) from {system} where name != :name", array(':name' => $except_module))->fetchField();
}

function drupal_module_get_weight($name) {
  return db_query("select weight from {system} where name = :name", array(':name' => $name))->fetchField();  
}

function drupal_module_set_weight($name, $weight) {
  db_update('system')->fields(array('weight' => $weight))->condition('name', $name)->execute();
}
