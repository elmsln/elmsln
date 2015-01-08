<?php

/**
 * @file
 * drush integration for Harmony core.
 */

/**
 * Implements hook_drush_command().
 */
function harmony_core_drush_command() {
  $items = array();

  $items['harmony-rebuild-thread-post-uris'] = array(
    'callback' => 'harmony_core_drush_rebuild_thread_post_uris',
    'description' => dt('Rebuilds the thread last post uri property on all threads.'),
  );

  $items['harmony-rebuild-counts'] = array(
    'callback' => 'harmony_core_drush_rebuild_counts',
    'description' => dt('Rebuilds all of the thread and posts counts.'),
    'arguments' => array(
      'targets' => dt('A space delimited list of places to rebuild the counts. Optional, if omitted all counts will be rebuilt. If rebuilding categories this uses counts from threads so perhaps rebuild that as well.'),
    ),
    'examples' => array(
      'drush harmony-rebuild-counts' => 'Rebuild all the counts! threads (post count), users (thread & post counts) and categories (thread & post counts).',
      'drush harmony-rebuild-counts threads users' => 'Rebuild counts for threads and users.',
      'drush harmony-rebuild-counts threads categories' => 'Rebuild counts for threads and categories.',
    ),
  );

  /*$items['harmony-rebuild-thread-meta'] = array(
    'callback' => 'harmony_core_drush_rebuild_thread_meta',
    'description' => dt('Rebuilds all of the thread meta data (Post URIs, First and Last thread entity references and Last user to update).'),
  );*/

  $items['harmony-rebuild-thread-first-last'] = array(
    'callback' => 'harmony_core_drush_rebuild_thread_first_last',
    'description' => dt('Rebuilds the thread first and last entity references on all threads and the first_post and last_post properties on post entites. Also rebuilds thread last post URIs.'),
  );

  $items['harmony-rebuild-thread-ownership'] = array(
    'callback' => 'harmony_core_drush_rebuild_thread_ownership',
    'description' => dt('In the case where threads have been migrated and in error set their owner to be User 1 or another user. This rebuild command will load all threads and check that their owner matches that of the first post author, if not it will set it.'),
  );

  $items['harmony-rebuild-thread-updated'] = array(
    'callback' => 'harmony_core_drush_rebuild_thread_updated',
    'description' => dt('Run through all threads and set their updated property to match the last posts created date.'),
  );

  return $items;
}

/*function harmony_core_drush_rebuild_thread_meta() {

}*/

function harmony_core_drush_rebuild_thread_post_uris() {
  if (drush_confirm('Are you sure you want to rebuild all of the Thread last post URIs?')) {
    module_load_include('module', 'harmony_core', 'harmony_core');
    harmony_core_admin_rebuild_execute('last_post_uris');
    drush_backend_batch_process();
  }
  else {
    drush_user_abort();
  }
}

function harmony_core_drush_rebuild_counts() {
  $args = func_get_args();

  if (!empty($args)) {
    if (!(in_array('threads', $args) && count($args) === 1)) {
      // Check arguments.
      $new_args = array();

      // If threads is present, make it first.
      if (in_array('threads', $args)) {
        $new_args[] = 'threads';
        $key = array_search('threads', $args);
        unset($args[$key]);
      }

      if (!empty($args)) {
        foreach ($args as $arg) {
          if ($arg != 'users' && $arg != 'categories') {
            drush_set_error(dt('Invalid argument: @arg', array('@arg' => $arg)));
          }
          else {
            $new_args[] = $arg;
          }
        }
      }

      $args = $new_args;
    }
  }
  else {
    $args = array(
      'users',
      'threads',
      'categories',
    );
  }

  if (drush_confirm(dt('Are you sure you want to rebuild the internal counts for @args?', array('@args' => implode(', ', $args))))) {
    module_load_include('module', 'harmony_core', 'harmony_core');
    harmony_core_admin_rebuild_execute('counts', array('target' => $args));
    drush_backend_batch_process();
  }
  else {
    drush_user_abort();
  }
}

function harmony_core_drush_rebuild_thread_first_last() {
  if (drush_confirm('Are you sure you want to rebuild all of the Thread first and last post properties?')) {
    module_load_include('module', 'harmony_core', 'harmony_core');
    harmony_core_admin_rebuild_execute('thread_first_last');
    drush_backend_batch_process();
  }
  else {
    drush_user_abort();
  }
}

function harmony_core_drush_rebuild_thread_ownership() {
  if (drush_confirm('Are you sure you want to check and fix thread ownership? Potentially long process innit.')) {
    module_load_include('module', 'harmony_core', 'harmony_core');
    harmony_core_admin_rebuild_execute('thread_ownership');
    drush_backend_batch_process();
  }
  else {
    drush_user_abort();
  }
}

function harmony_core_drush_rebuild_thread_updated() {
  if (drush_confirm('Are you sure you want to re-set all threads updated date property.')) {
    module_load_include('module', 'harmony_core', 'harmony_core');
    harmony_core_admin_rebuild_execute('thread_updated');
    drush_backend_batch_process();
  }
  else {
    drush_user_abort();
  }
}
