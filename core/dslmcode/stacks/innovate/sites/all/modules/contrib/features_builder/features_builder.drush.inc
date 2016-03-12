<?php

/**
 * @file
 * Features Builder Drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function features_builder_drush_command() {
  $commands['features-build'] = array(
    'description' => dt('Build Features from current config.'),
    'aliases' => array('fb'),
    'options' => array(
      'enable' => dt('Enable the features after building.'),
    ),
  );

  return $commands;
}

/**
 * Drush command to build Features.
 */
function drush_features_builder_features_build() {
  if (!drush_confirm(dt('Are you sure you want to build your features?'))) {
    return drush_user_abort();
  }

  $options['enable'] = drush_get_option('enable', FALSE);
  $batch = features_builder_prep_batch($options);
  $batch['progressive'] = FALSE;
  batch_set($batch);
  drush_backend_batch_process();
}
