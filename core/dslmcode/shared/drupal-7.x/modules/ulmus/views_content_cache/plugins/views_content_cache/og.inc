<?php
/**
 * @file
 * Provides the Views content cache OG plugin.
 */

/**
 * Views content cache plugin for Organic Groups.
 *
 * This plugin allows using OG as a cache segment, views caching can depend on
 * the current group context, and/or all the groups that the current user
 * belongs to.
 */
class views_content_cache_key_og extends views_content_cache_key {
  function options_form($value, &$handler = NULL) {
    return array(
      '#title' => t('Organic Groups'),
      '#description' => t('Checks for updates related to Organic Groups'),
      '#type' => 'checkboxes',
      '#options' => array_merge(array(
        'current' => t('Current group'),
        'user' => t("Member's groups")
      ), $this->additional_options_for_arguments($handler->view)),
      '#default_value' => $value,
    );
  }

  function content_key($object, $object_type) {
    $keys = array();
    if ($object_type === 'node' && !empty($object->og_groups)) {
      foreach ($object->og_groups as $gid) {
        $keys[] = $gid;
      }
    }
    elseif ($object_type === 'comment' && !empty($object->nid) && ($node = node_load($object->nid)) && !empty($node->og_groups)) {
      foreach ($node->og_groups as $gid) {
        $keys[] = $gid;
      }
    }
    return $keys;
  }

  function view_key($values, &$handler) {
    $values = array_filter($values);
    $groups = array();
    if (!empty($values['current']) && ($current = og_get_group_context())) {
      $groups[] = $current->nid;
    }
    if (!empty($values['user'])) {
      global $user;
      if (!empty($user->og_groups)) {
        $groups = array_merge($groups, array_keys($user->og_groups));
      }
    }
    unset($values['current'], $values['user']);
    // Add in the arguments.
    foreach ($this->view_key_replace_arguments($values, $handler) as $gid) {
      $groups[] = $gid;
    }
    return array_unique($groups);
  }

  function view_key_from_arguments() {
    return array('og_views_handler_argument_og_group_nid');
  }
}
