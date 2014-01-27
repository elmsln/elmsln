<?php

/**
 * @file
 * Creates the default configuration profiles.
 */

/**
 * Create core profiles.
 */
function imce_install_profiles() {
  $profiles = variable_get('imce_profiles', array());

  //already installed
  if (isset($profiles[1]) && !empty($profiles[1])) {
    return TRUE;
  }

  $profiles[1] = imce_user1_profile();
  $profiles[2] = imce_sample_profile();
  variable_set('imce_profiles', $profiles);

  return TRUE;
}

/**
 * Construct a profile based on arguments.
 */
function imce_construct_profile($n, $u, $f, $q, $tq, $e, $d, $fn, $ds, $ts) {
  $profile = array('name' => $n, 'usertab' => $u, 'filesize' => $f, 'quota' => $q, 'tuquota' => $tq, 'extensions' => $e, 'dimensions' => $d, 'filenum' => $fn, 'directories' => array(), 'thumbnails' => array());
  foreach ($ds as $d) {
    $profile['directories'][] = array('name' => $d[0], 'subnav' => $d[1], 'browse' => $d[2], 'upload' => $d[3], 'thumb' => $d[4], 'delete' => $d[5], 'resize' => $d[6]);
  }
  foreach ($ts as $t) {
    $profile['thumbnails'][] = array('name' => $t[0], 'dimensions' => $t[1], 'prefix' => $t[2], 'suffix' => $t[3]);
  }
  return $profile;
}

/**
 * User1's profile.
 */
function imce_user1_profile() {
  $profiles = variable_get('imce_profiles', array());
  if (isset($profiles[1])) {
    return $profiles[1];
  }
  return  imce_construct_profile('User-1', 1, 0, 0, 0, '*', '1200x1200', 0, array(array('.', 1, 1, 1, 1, 1, 1)), array(array('Small', '90x90', 'small_', ''), array('Medium', '120x120', 'medium_', ''), array('Large', '180x180', 'large_', '')));
}

/**
 * Default profile.
 */
function imce_sample_profile() {
  return imce_construct_profile('Sample profile', 1, 1, 2, 0, 'gif png jpg jpeg', '800x600', 1, array(array('u%uid', 0, 1, 1, 1, 0, 0)), array(array('Thumb', '90x90', 'thumb_', '')));
}
