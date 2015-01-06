<?php

/**
 * @file
 * harmony_core.pathauto.inc
 * Code for integrating with Pathauto!
 */

/**
 * Implements hook_path_alias_types().
 */
function harmony_core_path_alias_types() {
  return array(
    'thread/' => t('Threads'),
  );
}

/**
 * Implements hook_pathauto().
 */
function harmony_core_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings =  array(
        'module' => 'harmony_core',
        'token_type' => 'harmony_thread',
        'groupheader' => t('Thread paths'),
        'patterndescr' => t('This pattern applies to all threads.'),
        'patterndefault' => 'thread/[harmony_thread:thread-id]/[harmony_thread:title]',
        'batch_update_callback' => 'harmony_core_thread_pathauto_bulk_update_batch_process',
        'batch_file' => drupal_get_path('module', 'harmony_core') . '/includes/harmony_core.pathauto.inc',
      );

      $languages = array();
      if (module_exists('locale')) {
        $languages = array(LANGUAGE_NONE => t('language neutral')) + locale_language_list('name');
      }

      foreach (harmony_core_get_thread_types() as $type => $info) {
        // @todo i18n support.
        /*if (count($languages) && variable_get('language_content_type_' . $node_type, 0)) {
          $settings['patternitems'][$node_type] = t('Default path pattern for @node_type (applies to all @node_type content types with blank patterns below)', array('@node_type' => $node_name));
          foreach ($languages as $lang_code => $lang_name) {
            $settings['patternitems'][$node_type . '_' . $lang_code] = t('Pattern for all @language @node_type paths', array('@node_type' => $node_name, '@language' => $lang_name));
          }
        }
        else {*/
          $settings['patternitems'][$type] = t('Pattern for all @thread_type paths', array('@thread_type' => $info->label));
        //}
      }

      return (object) $settings;
  }
}

/**
 * Batch processing callback; Generate aliases for threads.
 */
function harmony_core_thread_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('harmony_thread', 't');
  $query->leftJoin('url_alias', 'ua', "CONCAT('thread/', t.thread_id) = ua.source");
  $query->addField('t', 'thread_id');
  $query->isNull('ua.source');
  $query->condition('t.thread_id', $context['sandbox']['current'], '>');
  $query->orderBy('t.thread_id');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'harmony_thread');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no threads to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $thread_ids = $query->execute()->fetchCol();

  harmony_core_thread_update_alias_multiple($thread_ids, 'bulkupdate');
  $context['sandbox']['count'] += count($thread_ids);
  $context['sandbox']['current'] = max($thread_ids);
  $context['message'] = t('Updated alias for thread @thread_id.', array('@thread_id' => end($thread_ids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}

/**
 * Update the URL aliases for an individual thread.
 */
function harmony_core_thread_update_alias($thread, $op, array $options = array()) {
  // Skip processing if the user has disabled pathauto for the thread.
  if (isset($thread->path['pathauto']) && empty($thread->path['pathauto'])) {
    return;
  }

  $options += array('language' => pathauto_entity_language('harmony_thread', $thread));

  // Weird but you pass the module name that specified hook_path_alias_types().
  // Skip processing if the node has no pattern.
  if (!pathauto_pattern_load_by_entity('harmony_core', '', $options['language'])) {
    return;
  }

  module_load_include('inc', 'pathauto');
  $uri = entity_uri('harmony_thread', $thread);
  pathauto_create_alias('harmony_core', $op, $uri['path'], array('harmony_thread' => $thread), $thread->type, $options['language']);
}

/**
 * Update the URL aliases for multiple threads.
 */
function harmony_core_thread_update_alias_multiple(array $thread_ids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $threads = harmony_thread_load_multiple($thread_ids);
  foreach ($threads as $thread) {
    harmony_core_thread_update_alias($thread, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($thread_ids), 'Updated URL alias for 1 thread.', 'Updated URL aliases for @count threads.'));
  }
}

/**
 * Update action wrapper for harmony_core_thread_update_alias_action().
 */
function harmony_core_thread_update_alias_action($thread, $context = array()) {
  harmony_core_thread_update_alias($thread, 'bulkupdate', array('message' => TRUE));
}
