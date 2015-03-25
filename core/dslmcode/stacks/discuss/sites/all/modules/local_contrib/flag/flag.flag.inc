<?php

/**
 * @file
 * Contains implementations of flag info hooks.
 */

/**
 * Implements hook_flag_type_info().
 *
 * Defines the flag types this module implements.
 *
 * @return
 *   An "array of arrays", keyed by object type. The 'handler' slot
 *   should point to the PHP class implementing this flag.
 */
function flag_flag_type_info() {
  // Entity types we specifically cater for.
  $definitions = array(
    'node' => array(
      'title' => t('Nodes'),
      'description' => t("Nodes are a Drupal site's primary content."),
      'handler' => 'flag_node',
    ),
    'user' => array(
      'title' => t('Users'),
      'description' => t('Users who have created accounts on your site.'),
      'handler' => 'flag_user',
    ),
  );

  if (module_exists('comment')) {
    $definitions['comment'] = array(
      'title' => t('Comments'),
      'description' => t('Comments are responses to node content.'),
      'handler' => 'flag_comment',
      'module' => 'comment',
    );
  }

  if (module_exists('taxonomy')) {
    $definitions['taxonomy_term'] = array(
      'title' => t('Taxonomy Terms'),
      'description' => t('Taxonomy terms are used to categorize content.'),
      'handler' => 'flag_entity',
      'module' => 'taxonomy',
    );
  }

  return $definitions;
}

/**
 * Implements hook_flag_type_info_alter().
 *
 * Step in and add flag types for any entities not yet catered for, using the
 * basic flag_entity handler. This allows other modules to provide more
 * specialized handlers for entities in hook_flag_type_info() as normal.
 */
function flag_flag_type_info_alter(&$definitions) {
  foreach (entity_get_info() as $entity_type => $entity_info) {
    // Only add flag support for entities that don't yet have them, and which
    // are non-config entities.
    if (!isset($definitions[$entity_type]) && empty($entity_info['configuration'])) {
      // We deliberately exclude taxonomy vocabularies from the list of
      // supported entity types because they aren't fieldable or directly
      // viewable, which makes them impossible to flag.
      if ($entity_type === 'taxonomy_vocabulary') {
        continue;
      }

      $definitions[$entity_type] = array(
        'title' => $entity_info['label'],
        'description' => t('@entity-type entity', array('@entity-type' => $entity_info['label'])),
        'handler' => 'flag_entity',
      );
    }
  }
}

/**
 * Implements hook_flag_link_type_info().
 */
function flag_flag_link_type_info() {
  return array(
    'toggle' => array(
      'title' => t('JavaScript toggle'),
      'description' => t('An AJAX request will be made and degrades to type "Normal link" if JavaScript is not available.'),
      'uses standard js' => TRUE,
      'uses standard css' => TRUE,
    ),
    'normal' => array(
      'title' => t('Normal link'),
      'description' => t('A normal non-JavaScript request will be made and the current page will be reloaded.'),
      'uses standard js' => FALSE,
      'uses standard css' => FALSE,
    ),
    'confirm' => array(
      'title' => t('Confirmation form'),
      'description' => t('The user will be taken to a confirmation form on a separate page to confirm the flag.'),
      'options' => array(
        'flag_confirmation' => '',
        'unflag_confirmation' => '',
      ),
      'uses standard js' => FALSE,
      'uses standard css' => FALSE,
      'provides form' => TRUE,
    ),
  );
}
