<?php

/**
 * @file
 * Provide Harmony specific Rules actions and events.
 */

/**
 * Implements hook_rules_action_info().
 */
function harmony_core_rules_action_info() {
  return array(
    'harmony_thread_meta_save' => array(
      'label' => t('Thread meta save'),
      'parameter' => array(
        'thread' => array(
          'type' => 'harmony_thread',
          'label' => t('Thread'),
        ),
      ),
      'group' => t('Harmony'),
    ),
    'harmony_post_meta_save' => array(
      'label' => t('Post meta save'),
      'parameter' => array(
        'thread' => array(
          'type' => 'harmony_post',
          'label' => t('Post'),
        ),
      ),
      'group' => t('Harmony'),
    ),
  );
}

/**
 * Implements hook_rules_event_info().
 */
function harmony_core_rules_event_info() {
  $items = array(
    'harmony_thread_insert_skip' => array(
      'label' => t('After saving a new thread (skip save)'),
      'group' => t('Harmony'),
      'variables' => array(
        'harmony_thread' => array(
          'type' => 'harmony_thread',
          'label' => t('saved thread'),
          'skip save' => TRUE,
        ),
      ),
    ),
    'harmony_thread_update_skip' => array(
      'label' => t('After updating an existing thread (skip save)'),
      'group' => t('Harmony'),
      'variables' => array(
        'harmony_thread' => array(
          'type' => 'harmony_thread',
          'label' => t('saved thread'),
          'skip save' => TRUE,
        ),
        'harmony_thread_unchanged' => array(
          'type' => 'harmony_thread',
          'label' => t('unchanged thread'),
          'handler' => 'rules_events_entity_unchanged',
        ),
      ),
    ),
    'harmony_post_insert_skip' => array(
      'label' => t('After saving a new post (skip save)'),
      'group' => t('Harmony'),
      'variables' => array(
        'harmony_post' => array(
          'type' => 'harmony_post',
          'label' => t('saved post'),
          'skip save' => TRUE,
        ),
      ),
    ),
    'harmony_post_update_skip' => array(
      'label' => t('After updating an existing post (skip save)'),
      'group' => t('Harmony'),
      'variables' => array(
        'harmony_post' => array(
          'type' => 'harmony_post',
          'label' => t('saved post'),
          'skip save' => TRUE,
        ),
        'harmony_post_unchanged' => array(
          'type' => 'harmony_post',
          'label' => t('unchanged post'),
          'handler' => 'rules_events_entity_unchanged',
        ),
      ),
    ),
  );

  return $items;
}
