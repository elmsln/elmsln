<?php

/**
 * @file
 * harmony_core.devel.inc
 *
 * Page and callbacks for devel tabs and generate stuff.
 * Code has been gleaned from devel_entity.
 */

function harmony_core_entity_load_object($entity_type, $entity, $name) {
  module_load_include('inc', 'entity', 'includes/entity.form');

  return kdevel_print_object($entity);
}

function harmony_core_render_object($entity_type, $entity, $name) {
  module_load_include('inc', 'entity', 'includes/entity.form');
  $build = $entity->view();
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);

  return kdevel_print_object($build);
}

/**
 * Generates Harmony entities using FormAPI.
 */
function harmony_core_devel_generate_form() {
  $harmony_thread_types = harmony_core_get_thread_types_flat();

  $form['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Generate threads &amp; posts for these thread types'),
    '#options' => $harmony_thread_types,
    '#default_value' => array('harmony_thread'),
    '#required' => TRUE,
  );

  $form['num_threads'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of threads to generate'),
    '#default_value' => 50,
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['num_posts'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of posts to generate per thread'),
    '#description' => t('The number generated will be between the number entered and half of it.'),
    '#default_value' => 20,
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['title_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of words in thread title'),
    '#default_value' => 4,
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['kill'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete existing threads and posts before generating new ones.'),
    '#default_value' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
  );

  return $form;
}

/**
 * FormAPI submission to generate harmony entities.
 */
function harmony_core_devel_generate_form_submit($form, &$form_state) {
  $operations = array();

  // Add setup operations.
  $operations[] = array('harmony_core_devel_generate_batch_pre_add', array($form_state['values']));

  // Delete the old stuff.
  if ($form_state['values']['kill']) {
    $ids = array();
    $results = db_select('harmony_thread', 'ht')
                ->fields('ht', array('thread_id'))
                ->condition('type', $form_state['values']['types'], 'IN')
                ->execute();

    foreach ($results as $result) {
      $operations[] = array('harmony_thread_delete', array($result->thread_id));
    }
  }

  // Add the operations for creating threads.
  for ($num = 0; $num < $form_state['values']['num_threads']; $num++) {
    $operations[] = array('harmony_core_devel_generate_batch_thread_add', array());

    // And its posts, -1 as when a thread is created, so is the first post.
    for ($post_num = 0; $post_num < ($form_state['values']['num_posts'] - 1); $post_num++) {
      $operations[] = array('harmony_core_devel_generate_batch_post_add', array());
    }
  }

  // Start the batch.
  $batch = array(
    'title' => t('Generating Harmony entities'),
    'operations' => $operations,
    'finished' => 'harmony_core_devel_generate_batch_finished',
    'file' => drupal_get_path('module', 'harmony_core') . '/includes/harmony_core.devel.inc',
  );
  batch_set($batch);
}

function harmony_core_devel_generate_batch_pre_add($vars, &$context) {
  $context['results'] = $vars;
  $context['results']['num_threads'] = 0;
  $context['results']['last_thread'] = NULL;
  $context['results']['thread_ids'] = array();
  harmony_core_devel_generate_pre_add($context['results']);
}

function harmony_core_devel_generate_pre_add(&$results) {
  // Get users.
  $users = array();
  $result = db_query_range('SELECT uid FROM {users} WHERE uid > 0 AND status = 1', 0, 50);
  foreach ($result as $record) {
    $users[] = $record->uid;
  }

  $results['users'] = $users;
}

function harmony_core_devel_generate_batch_thread_add(&$context) {
  module_load_include('inc', 'devel_generate', 'devel_generate');

  $users = $context['results']['users'];
  // Filter out the unselected thread types.
  $thread_types = array_filter($context['results']['types']);

  $thread = (object) array(
    'type' => array_rand($thread_types),
    'uid' => $users[array_rand($users)],
    'language' => LANGUAGE_NONE,
    'status' => HARMONY_PUBLISHED,
    'created' => REQUEST_TIME,
    'updated' => REQUEST_TIME,
    'pinned' => HARMONY_NOT_PINNED,
    'locked' => HARMONY_NOT_LOCKED,
    'hidden' => HARMONY_NOT_HIDDEN,
    'is_new' => TRUE,
  );

  if ($context['results']['title_length'] < 2) {
    $thread->title = devel_create_greeking(1, TRUE);
  }
  else {
    $thread->title = devel_create_greeking(mt_rand(1, $context['results']['title_length']), TRUE);
  }

  // Save it.
  $thread = harmony_thread_save($thread);

  // Create the first post and then reference it.
  $post = (object) array(
    'title' => $thread->title,
    'uid' => $thread->uid,
    'language' => LANGUAGE_NONE,
    'status' => HARMONY_PUBLISHED,
    'created' => REQUEST_TIME,
    'updated' => REQUEST_TIME,
    'locked' => HARMONY_NOT_LOCKED,
    'hidden' => HARMONY_NOT_HIDDEN,
    'is_new' => TRUE,
    'first_post' => TRUE,
  );

  $post_wrapper = entity_metadata_wrapper('harmony_post', $post);
  $post_wrapper->field_harmony_text->set(array('value' => devel_create_content(), 'format' => 'harmony_filtered'));
  $post_wrapper->field_harmony_thread->set($thread->thread_id);

  // Save the post.
  $post = harmony_post_save($post);

  // Set up the first post reference on the thread.
  $wrapper = entity_metadata_wrapper('harmony_thread', $thread);
  $wrapper->field_harmony_first_post->set($post->post_id);
  $wrapper->save();

  $thread->post_ids = array($post->post_id);

  $context['results']['last_thread'] = $thread;
  $context['results']['thread_ids'] = array();
  $context['results']['num_threads']++;
}

function harmony_core_devel_generate_batch_post_add(&$context) {
  module_load_include('inc', 'devel_generate', 'devel_generate');

  $thread = $context['results']['last_thread'];
  $users = $context['results']['users'];

  $post = (object) array(
    'title' => $thread->title,
    'uid' => $users[array_rand($users)],
    'language' => LANGUAGE_NONE,
    'status' => HARMONY_PUBLISHED,
    'created' => REQUEST_TIME,
    'updated' => REQUEST_TIME,
    'locked' => HARMONY_NOT_LOCKED,
    'hidden' => HARMONY_NOT_HIDDEN,
    'is_new' => TRUE,
  );

  $post_wrapper = entity_metadata_wrapper('harmony_post', $post);
  $post_wrapper->field_harmony_text->set(array('value' => devel_create_content(), 'format' => 'harmony_filtered'));
  $post_wrapper->field_harmony_thread->set($thread->thread_id);

  // Determine if we're replying to another post within this thread,
  // chances are 1 in 4.
  if (!empty($context['results']['last_thread']->post_ids) && rand(1, 4) === 1) {
    $thread_post_ids = $context['results']['last_thread']->post_ids;
    $post_wrapper->field_harmony_post_is_reply_to->set($thread_post_ids[array_rand($thread_post_ids)]);
  }

  // Save the post.
  $post = harmony_post_save($post);

  $context['results']['last_thread']->post_ids[] = $post->post_id;
}

function harmony_core_devel_generate_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural($results['num_threads'], 'Finished! 1 thread created.', 'Finished! @count threads created.');
  }
  else {
    $message = t('Finished with an error.');
  }

  drupal_set_message($message);
}
