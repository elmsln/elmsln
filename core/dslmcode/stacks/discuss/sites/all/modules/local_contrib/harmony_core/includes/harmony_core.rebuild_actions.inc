<?php

/**
 * @file
 * harmony_core.rebuild_actions.inc
 *
 * Operation and Finished callbacks for the rebuild batch actions.
 */

/**
 * Generalised batch rebuild finished function to output standard messages.
 */
function _harmony_core_rebuild_finished($success, $results, $operations, $action_id) {
  $actions = harmony_core_rebuild_actions();
  $action = $actions[$action_id];

  if ($success) {
    drupal_set_message(t('Rebuild of the @title has been completed.', array('@title' => $action['title'])));
    $actions = variable_get('harmony_core_rebuild_actions', array());
    if (($key = array_search($action_id, $actions)) !== FALSE) {
      unset($actions[$key]);
    }
    variable_set('harmony_core_rebuild_actions', $actions);
  }
  else {
    drupal_set_message(t("Something's gone wrong with the @title rebuild, please check the error log.", array('@title' => $action['title'])), 'error');
  }
}

/**
 * Operation callback which batch rebuilds the Last post URI property for
 * Thread entities.
 */
function _harmony_core_rebuild_last_post_uris_operation(&$context) {
  if (empty($context['sandbox'])) {
    // Initiate multistep processing.
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_entity_id'] = 0;
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT thread_id) FROM {harmony_thread}')->fetchField();
  }

  // Process the next 20 threads.
  $limit = 20;
  $thread_ids = db_query_range("SELECT thread_id FROM {harmony_thread} WHERE thread_id > :entity_id ORDER BY thread_id ASC", 0, $limit, array(':entity_id' => $context['sandbox']['current_entity_id']))->fetchCol();
  $threads = harmony_thread_load_multiple($thread_ids, array(), TRUE);

  foreach ($threads as $thread_id => $thread) {
    if (!empty($thread)) {
      $thread_posts_stored = array();
      $thread_posts = harmony_core_get_thread_posts($thread->thread_id);

      $thread_posts_stored['all'] = $thread_posts;
      $thread_posts_stored['first'] = array_shift($thread_posts);
      $thread_posts_stored['last'] = !empty($thread_posts) ? array_pop($thread_posts) : $thread_posts_stored['first'];
      $thread_posts_stored['other'] = $thread_posts;

      if ($thread_posts_stored['last']) {
        $last_post = harmony_post_load($thread_posts_stored['last']);
        $thread->last_post_uri = harmony_core_post_thread_url($thread->thread_id, $last_post->post_id, TRUE);
        harmony_thread_meta_save($thread);
      }
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['current_entity_id'] = $thread_id;
  }

  // Multistep processing : report progress.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback for the Last post URI rebuild action.
 */
function _harmony_core_rebuild_last_post_uris_finished($success, $results, $operations) {
  _harmony_core_rebuild_finished($success, $results, $operations, 'last_post_uris');
}

/**
 * Operation callback for rebuilding the first and last post entity references
 * along with the first and last post properties on post entities.
 */
function _harmony_core_rebuild_thread_first_last_operation(&$context) {
  if (empty($context['sandbox'])) {
    // Initiate multistep processing.
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_entity_id'] = 0;
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT thread_id) FROM {harmony_thread}')->fetchField();
  }

  // Process the next 20 threads.
  $limit = 20;
  $thread_ids = db_query_range("SELECT thread_id FROM {harmony_thread} WHERE thread_id > :entity_id ORDER BY thread_id ASC", 0, $limit, array(':entity_id' => $context['sandbox']['current_entity_id']))->fetchCol();
  $threads = harmony_thread_load_multiple($thread_ids, array(), TRUE);

  foreach ($threads as $thread_id => $thread) {
    if (!empty($thread)) {
      harmony_thread_rebuild_first_last_posts($thread);
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['current_entity_id'] = $thread_id;
  }

  // Multistep processing : report progress.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback for the first last post reference rebuild action.
 */
function _harmony_core_rebuild_thread_first_last_finished($success, $results, $operations) {
  _harmony_core_rebuild_finished($success, $results, $operations, 'thread_first_last');
}

/**
 * Rebuild the count fields on certain entities in batches. Can be triggered
 * via the UI or Drush.
 */
function _harmony_core_rebuild_counts_operation($target, &$context) {
  if (empty($context['sandbox'])) {
    // Initiate multistep processing.
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['limit'] = 20;
    $context['sandbox']['current_entity_id'] = 0;

    // Setup vars to be used during execution, and work out the maximum
    // number of items we'll be dealing with.
    switch ($target) {
      case 'users':
        $context['sandbox']['entity_type'] = 'user';
        $context['sandbox']['entity_table'] = 'users';
        $context['sandbox']['id_key'] = 'uid';
        $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT uid) FROM {users} WHERE uid > 0')->fetchField();
        break;

      case 'threads':
        $context['sandbox']['entity_type'] = 'harmony_thread';
        $context['sandbox']['entity_table'] = 'harmony_thread';
        $context['sandbox']['id_key'] = 'thread_id';
        $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT thread_id) FROM {harmony_thread}')->fetchField();
        break;

      case 'categories':
        $context['sandbox']['entity_type'] = 'taxonomy_term';
        $context['sandbox']['entity_table'] = 'taxonomy_term_data';
        $context['sandbox']['id_key'] = 'tid';
        $harmony_vocabulary = variable_get('harmony_core_category_vocabulary', 'harmony_category');
        $vocabulary = taxonomy_vocabulary_machine_name_load($harmony_vocabulary);
        $context['sandbox']['vid'] = $vocabulary->vid;
        $context['sandbox']['limit'] = 1;
        $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT tid) FROM {taxonomy_term_data} WHERE vid = :vid', array(':vid' => $vocabulary->vid))->fetchField();
        break;
    }
  }

  // Process the next set of items, this could be a dynamic query but they're
  // slow and we know that the input is internal.
  $table = $context['sandbox']['entity_table'];
  $id_key = $context['sandbox']['id_key'];
  $query_extra = NULL;

  // Taxonomy count rebuild is a special case which needs an extra level of
  // specificity to the query.
  if ($context['sandbox']['entity_type'] === 'taxonomy_term') {
    $query_extra = ' AND vid = ' . $context['sandbox']['vid'];
  }

  $entity_ids = db_query_range('SELECT ' . $id_key . ' FROM {' . $table . '} WHERE ' . $id_key . ' > :entity_id' . $query_extra . ' ORDER BY ' . $id_key . ' ASC', 0, $context['sandbox']['limit'], array(
    ':entity_id' => $context['sandbox']['current_entity_id']
  ))->fetchCol();
  $entities = entity_load($context['sandbox']['entity_type'], $entity_ids, array(), TRUE);

  foreach ($entities as $entity_id => $entity) {
    if (!empty($entity)) {
      harmony_core_rebuild_meta_count($context['sandbox']['entity_type'], $entity_id, $entity);
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['current_entity_id'] = $entity_id;
  }

  // Multistep processing : report progress.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback for the counts rebuild action.
 */
function _harmony_core_rebuild_counts_finished($success, $results, $operations) {
  _harmony_core_rebuild_finished($success, $results, $operations, 'counts');
}

/**
 * Operation callback for checking and correcting thread ownership.
 */
function _harmony_core_rebuild_thread_owner_operation(&$context) {
  if (empty($context['sandbox'])) {
    // Initiate multistep processing.
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_entity_id'] = 0;
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT thread_id) FROM {harmony_thread}')->fetchField();
  }

  // Process the next 20 threads.
  $limit = 20;
  $thread_ids = db_query_range("SELECT thread_id FROM {harmony_thread} WHERE thread_id > :entity_id ORDER BY thread_id ASC", 0, $limit, array(':entity_id' => $context['sandbox']['current_entity_id']))->fetchCol();
  $threads = harmony_thread_load_multiple($thread_ids, array(), TRUE);

  foreach ($threads as $thread_id => $thread) {
    if (!empty($thread)) {
      // Load the threads first post if we can.
      $wrapper = entity_metadata_wrapper('harmony_thread', $thread);

      if ($wrapper->field_harmony_first_post->value()) {
        $first_post = harmony_post_load($wrapper->field_harmony_first_post->post_id->value());

        if ($first_post && $thread->uid != $first_post->uid) {
          $thread->uid = $first_post->uid;
          // Meta save to bypass all other hooks, and for speeeed.
          harmony_thread_meta_save($thread);
        }
      }

      // Unset the things.
      unset($wrapper);
      unset($thread);
      unset($first_post);
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['current_entity_id'] = $thread_id;
  }

  // Multistep processing : report progress.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback for the thread ownership rebuild action.
 */
function _harmony_core_rebuild_thread_owner_finished($success, $results, $operations) {
  _harmony_core_rebuild_finished($success, $results, $operations, 'thread_ownership');
}

/**
 * Operation callback for checking and correcting all threads updated property.
 */
function _harmony_core_rebuild_thread_updated_operation(&$context) {
  if (empty($context['sandbox'])) {
    // Initiate multistep processing.
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_entity_id'] = 0;
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT thread_id) FROM {harmony_thread}')->fetchField();
  }

  // Process the next 20 threads.
  $limit = 20;
  $thread_ids = db_query_range("SELECT thread_id FROM {harmony_thread} WHERE thread_id > :entity_id ORDER BY thread_id ASC", 0, $limit, array(':entity_id' => $context['sandbox']['current_entity_id']))->fetchCol();
  $threads = harmony_thread_load_multiple($thread_ids, array(), TRUE);

  foreach ($threads as $thread_id => $thread) {
    if (!empty($thread)) {
      // Load the threads first post if we can.
      $wrapper = entity_metadata_wrapper('harmony_thread', $thread);

      if ($wrapper->field_harmony_last_post->value()) {
        $last_post = harmony_post_load($wrapper->field_harmony_last_post->post_id->value());

        if ($last_post) {
          $thread->updated = $last_post->created;
          // Meta save to bypass all other hooks, and for continued speeeed.
          harmony_thread_meta_save($thread);
        }
      }

      // Unset the things.
      unset($wrapper);
      unset($thread);
      unset($last_post);
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['current_entity_id'] = $thread_id;
  }

  // Multistep processing : report progress.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finished callback for the thread ownership rebuild action.
 */
function _harmony_core_rebuild_thread_updated_finished($success, $results, $operations) {
  _harmony_core_rebuild_finished($success, $results, $operations, 'thread_updated');
}

