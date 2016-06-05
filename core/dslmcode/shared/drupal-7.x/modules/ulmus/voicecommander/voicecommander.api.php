<?php
/**
 * @file
 * Voice commander API documentation
 */

/**
 * Implements hook_voice_command().
 *
 * This allows you to add new commands to be recognized by annyang and
 * have drupal act on them via a javascript front-end handler.
 *
 * @return array  an array of commands that this makes available
 */
function hook_voice_command() {
  return array(
    // key that's for the project, this just has to be unique relative to others
    'cacheclear' => array(
      // the js file that contains possible callback extentions needed to process this
      // command on the front-end
      'file' => drupal_get_path('module', 'voicecommander') . '/js/voicecommander-cache.js',
      // a list of commands that you want to make available
      'commands' => array(
        // key here is the phase someone would speak
        // annyang syntax allows for () to be optional for conversational speach
        // %phrase can be used to support the site defined trigger word like 'drupal'
        '%phrase (clear) cache' => array(
          // the javascript callback to be activated when the command is recognized.
          // this will be passed the phrase key so that any properties added to this
          // array would be recognized. It is recommended you use data for any custom
          // data that needs passed down but is not required.
          'callback' => 'Drupal.voicecommander.clearCache'
        ),
        '%phrase goto CNN' => array(
          'callback' => 'Drupal.voicecommander.goToCNN',
          'data' => url('http://cnn.com'),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_voice_command_alter().
 * @param  array &$commands a list of commands that are available
 */
function hook_voice_command_alter(&$commands) {
  $commands['cacheclear']['file'] = 'mycustom-cache-clear-override.js';
}
