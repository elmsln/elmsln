<?php

/**
 * @file
 * Contains the flag_user class.
 */

/**
 * Implements a user flag.
 */
class flag_user extends flag_entity {
  function options() {
    $options = parent::options();
    $options += array(
      'show_on_profile' => TRUE,
      'access_uid' => '',
    );
    return $options;
  }

  /**
   * Options form extras for user flags.
   */
  function options_form(&$form) {
    parent::options_form($form);
    $form['access']['types'] = array(
      // A user flag doesn't support node types.
      // TODO: Maybe support roles instead of node types.
      '#type' => 'value',
      '#value' => array(0 => 0),
    );
    $form['access']['access_uid'] = array(
      '#type' => 'checkbox',
      '#title' => t('Users may flag themselves'),
      '#description' => t('Disabling this option may be useful when setting up a "friend" flag, when a user flagging themself does not make sense.'),
      '#default_value' => $this->access_uid ? 0 : 1,
    );
    $form['display']['show_on_profile'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display link on user profile page'),
      '#description' => t('Show the link formatted as a user profile element.'),
      '#default_value' => $this->show_on_profile,
      // Put this above 'show on entity'.
      '#weight' => -1,
    );
  }

  function form_input($form_values) {
    parent::form_input($form_values);
    // The access_uid value is intentionally backwards from the UI, to avoid
    // confusion caused by checking a box to disable a feature.
    $this->access_uid = empty($form_values['access_uid']) ? 'others' : '';
  }

  function type_access($entity_id, $action, $account) {
    // Prevent users from flagging themselves.
    if ($this->access_uid == 'others' && $entity_id == $account->uid) {
      return FALSE;
    }
  }

  function type_access_multiple($entity_ids, $account) {
    $access = array();

    // Exclude anonymous.
    if (array_key_exists(0, $entity_ids)) {
      $access[0] = FALSE;
    }

    // Prevent users from flagging themselves.
    if ($this->access_uid == 'others' && array_key_exists($account->uid, $entity_ids)) {
      $access[$account->uid] = FALSE;
    }

    return $access;
  }

  function get_flag_action($entity_id) {
    $flag_action = parent::get_flag_action($entity_id);
    $user = $this->fetch_entity($entity_id);
    $flag_action->content_title = $user->name;
    $flag_action->content_url = $this->_flag_url('user/' . $user->uid);
    return $flag_action;
  }

  function get_relevant_action_objects($entity_id) {
    return array(
      'user' => $this->fetch_entity($entity_id),
    );
  }

  function get_views_info() {
    $views_info = parent::get_views_info();
    $views_info['title field'] = 'name';
    return $views_info;
  }
}
