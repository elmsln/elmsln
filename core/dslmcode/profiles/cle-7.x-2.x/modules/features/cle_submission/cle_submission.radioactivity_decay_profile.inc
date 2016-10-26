<?php
/**
 * @file
 * cle_submission.radioactivity_decay_profile.inc
 */

/**
 * Implements hook_default_radioactivity_decay_profile().
 */
function cle_submission_default_radioactivity_decay_profile() {
  $export = array();

  $radioactivity_decay_profile = new stdClass();
  $radioactivity_decay_profile->disabled = FALSE; /* Edit this to true to make a default radioactivity_decay_profile disabled initially */
  $radioactivity_decay_profile->api_version = 1;
  $radioactivity_decay_profile->machine_name = 'cle_half_week';
  $radioactivity_decay_profile->name = 'CLE half week';
  $radioactivity_decay_profile->description = 'This decay occurs bi-weekly as most assignments have a window of a week.';
  $radioactivity_decay_profile->enable_decay = 2;
  $radioactivity_decay_profile->granularity = '120';
  $radioactivity_decay_profile->half_life = 302400;
  $radioactivity_decay_profile->cut_off = '5';
  $radioactivity_decay_profile->storage = 'Live';
  $export['cle_half_week'] = $radioactivity_decay_profile;

  return $export;
}
