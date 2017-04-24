<?php

/**
 * @file
 * Declare Media WYSIWYG variables.
 */

/**
 * Implements hook_variable_group_info().
 */
function media_wysiwyg_variable_group_info() {
  $groups['media_wysiwyg'] = array(
    'title' => t('Media WYSIWYG'),
    'description' => t('Settings for Media WYSIWYG integration.'),
    'access' => 'administer media browser',
    'path' => 'admin/config/media/browser',
  );

  return $groups;
}

/**
* Implements hook_variable_info().
*/
function media_wysiwyg_variable_info($options) {
  $variables['media_wysiwyg_wysiwyg_title'] = array(
    'type' => 'string',
    'title' => t('WYSIWYG Title', array(), $options),
    'default' => t('Media browser', array(), $options),
    'description' => t('The WYSIWYG media plugin title.', array(), $options),
    'group' => 'media_wysiwyg',
  );
  $variables['media_wysiwyg_wysiwyg_icon_title'] = array(
    'type' => 'string',
    'title' => t('WYSIWYG Icon Title', array(), $options),
    'default' => t('Add media', array(), $options),
    'description' => t('The WYSIWYG media button title to display on hover.', array(), $options),
    'group' => 'media_wysiwyg',
  );

  return $variables;
}
