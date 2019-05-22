<?php
/**
 * @file
 * Documentation for Webcomponents to bring new components into scope.
 */

/**
 * Implements hook_register_component_format_alter().
 */
function hook_register_component_format_alter(&$formats) {
  // allow modidying a process hook to implement your own processing methodology
}

/**
 * Implements hook_webcomponents_alter().
 */
function hook_webcomponents_alter($components) {
  // add / remove files you might not want pulled in as legit components
}

/**
 * Implements hook_webcomponent_attached_files_alter().
 * @param  array   array of webcomponents keyed by file location
 */
function hook_webcomponent_attached_files_alter(&$webcomponents) {
  // add or remove components from being included in the current page build
  unset($webcomponents['my-thing-i-dont-want-here.html']);
}
