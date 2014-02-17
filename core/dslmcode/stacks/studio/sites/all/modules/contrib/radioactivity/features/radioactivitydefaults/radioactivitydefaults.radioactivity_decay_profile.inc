<?php
/**
 * @file
 * radioactivitydefaults.radioactivity_decay_profile.inc
 */

/**
 * Implements hook_default_radioactivity_decay_profile().
 */
function radioactivitydefaults_default_radioactivity_decay_profile() {
  $export = array();

  $radioactivity_decay_profile = new stdClass();
  $radioactivity_decay_profile->disabled = FALSE; /* Edit this to true to make a default radioactivity_decay_profile disabled initially */
  $radioactivity_decay_profile->api_version = 1;
  $radioactivity_decay_profile->machine_name = 'default_daily';
  $radioactivity_decay_profile->name = 'Default daily';
  $radioactivity_decay_profile->description = '';
  $radioactivity_decay_profile->enable_decay = 1;
  $radioactivity_decay_profile->granularity = '60';
  $radioactivity_decay_profile->half_life = 43200;
  $radioactivity_decay_profile->cut_off = '10';
  $radioactivity_decay_profile->storage = 'Live';
  $export['default_daily'] = $radioactivity_decay_profile;

  $radioactivity_decay_profile = new stdClass();
  $radioactivity_decay_profile->disabled = FALSE; /* Edit this to true to make a default radioactivity_decay_profile disabled initially */
  $radioactivity_decay_profile->api_version = 1;
  $radioactivity_decay_profile->machine_name = 'default_now';
  $radioactivity_decay_profile->name = 'Default now';
  $radioactivity_decay_profile->description = '';
  $radioactivity_decay_profile->enable_decay = 1;
  $radioactivity_decay_profile->granularity = '1';
  $radioactivity_decay_profile->half_life = 450;
  $radioactivity_decay_profile->cut_off = '10';
  $radioactivity_decay_profile->storage = 'Live';
  $export['default_now'] = $radioactivity_decay_profile;

  $radioactivity_decay_profile = new stdClass();
  $radioactivity_decay_profile->disabled = FALSE; /* Edit this to true to make a default radioactivity_decay_profile disabled initially */
  $radioactivity_decay_profile->api_version = 1;
  $radioactivity_decay_profile->machine_name = 'default_weekly';
  $radioactivity_decay_profile->name = 'Default weekly';
  $radioactivity_decay_profile->description = '';
  $radioactivity_decay_profile->enable_decay = 1;
  $radioactivity_decay_profile->granularity = '60';
  $radioactivity_decay_profile->half_life = 432000;
  $radioactivity_decay_profile->cut_off = '50';
  $radioactivity_decay_profile->storage = 'Live';
  $export['default_weekly'] = $radioactivity_decay_profile;

  return $export;
}
