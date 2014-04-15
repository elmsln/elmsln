<?php
// @file API definitions for working with user_progress

/**
 * Implements hook_user_progress_define_types().
 * The only required fields are the machine name and name
 * data / default handlers help ensure data integrity in dev
 * int, string, blob and time are all valid handler types
 *
 * @return  an array describing how to handle a type of transaction
 */
function hook_user_progress_define_types() {
  return array(
    '{machine_name}' => array(
      'name' => t('{Title}'),
      'data1_handler' => '{type}', // data1 through data16 are available
      'default_handler' => '{type}', //default can also optionally be defined
    ),
  );
}

/**
 * Implements hook_user_progress_define_types_alter().
 * Modify hooks defined by other modules
 * @param  $types array of defined types and data handlers
 */
function hook_user_progress_define_types_alter($types) {
  // example to unset the default handler for content tracker
  unset($types['up_content']['default_handler']);
}


// Javascript API
// User progress also has a structured function for ajax calls to set data
// direction is either get/set
// what you want is defined in _user_progress_get or _user_progress_set
// the required parameters for each call can be found in those functions
  Drupal.user_progress.ajax_call('{direction}', '{what you want}', {additional parameters per call});
// There is an example of user_progress.js being invoked in jwplayer.js
// send data to user progress, you have up to 16 data points
// upregid is not required but user_progress_jwplayer.module gives an
// example of how to do more advanced data transmissions
  var params = 'data1='+ myvalue1 +'&data2='+ myvalue2 +'&data3='+ myvalue3 +'&upregid='+ Drupal.settings.user_progress.upregid;
  // this is the standard call to set values
  Drupal.user_progress.ajax_call('set', 'value', params);
  // this is an example of how you would get data back from up records
  // this will rely on params being set correctly
  Drupal.user_progress.ajax_call('get', 'numtries', params);
